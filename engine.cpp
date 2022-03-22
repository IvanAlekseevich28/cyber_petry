#include "engine.h"
#include <unistd.h>
#include "core/tools/fieldtools.h"
#include <QDateTime>


QEngine::QEngine(TSize matSize, QObject *parent) : QObject(parent),
    m_eng(Eng::initField(matSize)), m_matSize(matSize), m_step(0)
{
    reset();
}

int QEngine::step()
{
    const int countThreads = 14;
    m_perf.coac = countThreads;

    auto t1 = std::chrono::high_resolution_clock::now();
    m_eng.step(countThreads);
    auto t2 = std::chrono::high_resolution_clock::now();
    long duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    calcPerformance(duration);
    m_step += 1;
//    usleep(1000*5); // 0.5 sec

    const qint64 timeForNextFrame = 1000 / m_FPSLimit;
    if (m_FPSTimerLastFrame.isValid() == false)
    {
        m_FPSTimerLastFrame.start();
        sendData();
    } else if (m_FPSTimerLastFrame.elapsed() >= timeForNextFrame)
    {
        m_FPSTimerLastFrame.restart();
        sendData();
    } else if (m_start == false)
        sendData();

    m_perf.coac = 0;
    return nStep();
}

void QEngine::stop()
{
    m_start = false;
    m_perf.coac = 0;
    sendData();
}

void QEngine::reset()
{
    m_spentTime=0;
    m_step=0;
    m_start=false;
    m_eng.setState(Eng::initField(m_matSize));

    Eng::FieldTools etool(m_eng.getState());
//    etool.fillFieldByLiquid(Eng::LT_water, 0x0FFFFFFF);
//    for (int i = 0; i < 4096; i++)
//        etool.addRandomLiquid(0x00FFFFFF);
//    etool.addRandomLiquid(0x04FFFFFFF, Eng::LT_carbon);
//    etool.addRandomLiquid(0x04FFFFFFF, Eng::LT_organic);
//    etool.addRandomLiquid(0x0FFFFFFFF, Eng::LT_acid);
//    etool.addLiquid(Eng::Point(0,0), Eng::LT_water, 100);
//    for (int i = 0; i < 4; i++)
    for (int i = 0; i < 6; i++)
        etool.addRandomWaveHeight(0x8000);
//    etool.addRandomWaveHeight(0x4000);
//    etool.addRandomWaveHeight(0x100000);
}

void QEngine::calcPerformance(int duration)
{
    if (m_eng.getState()->m.empty())
        return;

    const int countCells = m_eng.getState()->m.size() * m_eng.getState()->getH();
    m_spentTime += duration;

    m_perf.ctis = m_spentTime / 1000000;
    m_perf.ups = 1.0 / ((double)duration / 1000000);
    m_perf.cups = m_perf.ups * countCells;
}

int QEngine::nStep() const
{
    return m_step;
}

void QEngine::sendData() const
{
//    auto curTime = std::chrono::high_resolution_clock::now();
    emit newData(m_eng.getState());
    emit newStep(nStep());
    emit newPerf(m_perf);
//    m_lastFrameTime = curTime;
}

void QEngine::loop()
{
    m_start = true;
    while (m_start)
    {
        step();
    }

}
