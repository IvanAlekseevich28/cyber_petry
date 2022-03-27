#include "simulation.h"

Simulation::Simulation(const SimParametrs& settings, PQGameScreen pScreen, PQInfoMonitor pInfoM, QObject *parent) :
    QObject(parent), m_simPar(settings), m_pScreen(pScreen), m_pInfoMonitor(pInfoM)
{ 
    qRegisterMetaType<Info::Performance>();
    if (m_pInfoMonitor.expired() == false && pInfoM.get() != nullptr)
        connect(this, &Simulation::newPerf, pInfoM.get(), &QInfoMonitor::newInfoPerformance);
}

void Simulation::loop()
{
    m_isLoop = true;
    m_secTimer.start();
    StepInfo si;
    LoopInfo li;

    while (m_isLoop)
    {
        step(si);

        m_simDurationTime += si.duration;
        li.stepsPerSecond++;
        li.framesPerSecond += si.wasDraw;
        li.msDuration = m_secTimer.elapsed();
        if (li.msDuration >= 1000)
        {
            m_secTimer.restart();
            emit newPerf(calcPerformnce(li));
            li.reset();
        }
    }
}

void Simulation::step(StepInfo& si)
{
    auto t1 = std::chrono::high_resolution_clock::now();

    m_engInput.input(m_engSim.getState());
    m_engSim.step(m_simPar.countCores);

    if (needDraw())
    {
        draw();
        si.wasDraw = true;
    }

    //  performace
    auto t2 = std::chrono::high_resolution_clock::now();
    si.duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
}

void Simulation::stop()
{
    m_isLoop = false;
}

void Simulation::reset()
{
    m_simDurationTime = 0;
    if (m_isLoop)
    {
        m_isLoop = false;
        // TODO wait calculations
    }
    m_engSim.setState(Eng::initField(m_simPar.matrixSize));

    m_engInput.reset();
    m_engInput.input(m_engSim.getState());
    draw();

    if(m_pInfoMonitor.expired() == false)
        m_pInfoMonitor.lock()->newInfoPerformance(Info::Performance());
}

void Simulation::askDraw()
{
    // TODO need flags to not draw while step calculating
    draw();
}

bool Simulation::needDraw() const
{
    if (m_pScreen.expired())
        return false;

    if (m_FPSTimerLastFrame.isValid() == false)
        return true;

    const qint64 timeForNextFrame = 1000 / m_simPar.FPSLimit;
    if (m_FPSTimerLastFrame.elapsed() >= timeForNextFrame || m_isLoop == false)
        return true;

    return false;
}

Info::Performance Simulation::calcPerformnce(LoopInfo &li) const
{
    Info::Performance perf;
    perf.fps = static_cast<double>(li.framesPerSecond) / li.msDuration * 1000;
    perf.ups = static_cast<double>(li.stepsPerSecond) / li.msDuration * 1000;
    perf.ctis = m_simDurationTime / 1000000;
    perf.coac = m_simPar.countCores;
    perf.cups = perf.ups * m_engSim.getState()->getResolution();

    return perf;
}

void Simulation::draw() const
{
    if (m_pScreen.expired() == false)
        m_pScreen.lock()->draw(m_engSim.getState(), m_simPar.countCores);

    emit iteration(m_engSim.getState()->index);
    m_FPSTimerLastFrame.restart();
}

void LoopInfo::reset()
{
    stepsPerSecond = 0;
    framesPerSecond = 0;
    msDuration = 1000;
}
