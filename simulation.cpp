#include "simulation.h"
#include <iostream>

Simulation::Simulation(const SimParametrs& settings, QObject *parent) :
    QObject(parent), m_simPar(settings),
    m_engSim(Eng::initField(m_simPar.matrixSize)),
    m_engInput(m_engSim.getState())
{
    qRegisterMetaType<Info::Performance>();
    reset();
}

PQGameScreen Simulation::initGameScreen()
{
    auto pScreen = new QGameScreen(m_simPar.screenSize, m_simPar.matrixSize, dynamic_cast<QWidget*>(parent()));
    PQGameScreen screen(pScreen);
    m_pScreen = screen;
    draw();

    return screen;
}

PQInfoMonitor Simulation::initInfoMonitor(TSize size)
{
    PQInfoMonitor monitor(new QInfoMonitor(size, dynamic_cast<QWidget*>(parent())));
    m_pInfoMonitor = monitor;
    connect(this, &Simulation::newPerf, monitor.get(), &QInfoMonitor::newInfoPerformance);

    return monitor;
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
            m_secTimer.start();
            emit newPerf(calcPerformnce(li));
            li.reset();
        }
    }
}

void Simulation::step(StepInfo& si)
{
    auto t1 = std::chrono::high_resolution_clock::now();

    try {
        m_engInput.input(m_engSim.getState());
        m_engSim.step(m_simPar.countCores);

        if (needDraw())
        {
            draw();
            si.wasDraw = true;
        }
    }  catch (...) {
        std::cerr << "Simulation is broken!\n";
    }


    //  performace
    auto t2 = std::chrono::high_resolution_clock::now();
    si.duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
}

void Simulation::step()
{
    StepInfo si;
    step(si);
}

void Simulation::stop()
{
    m_isLoop = false;
    draw();
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
    perf.cups = perf.ups * m_engSim.getConstState()->getResolution();

    return perf;
}

void Simulation::draw() const
{
    const auto state = m_engSim.getConstState();
    if (m_pScreen.expired() == false)
        m_pScreen.lock()->draw(state, m_simPar.countCores);

    emit iteration(state->index);
    m_FPSTimerLastFrame.start();
}

void LoopInfo::reset()
{
    stepsPerSecond = 0;
    framesPerSecond = 0;
    msDuration = 1000;
}
