#include "engine.h"
#include <unistd.h>
#include "engine/fluidenginetools.h"


QEngine::QEngine(QObject *parent) : QObject(parent),
    m_eng(Eng::SimParams(true)), m_step(0)
{
    Eng::FluidEngineTools etool(m_eng);
//    etool.fillFieldByLiquid(Eng::LT_water, 0x0FFFFFFF);
    for (int i = 0; i < 8; i++)
        etool.addRandomLiquid(0x0FFFFFFF);
}

int QEngine::step()
{
    m_perf.coac = 1;
    m_timer.start();
    const int countSteps = 1;
    Eng::PtrField pField = m_eng.step(countSteps);
    calcPerformance(countSteps);
    m_step += countSteps;
//    usleep(1000*5); // 0.5 sec
    sendData();
    m_perf.coac = 0;
    return nStep();
}

void QEngine::stop()
{
    m_start = false;
    m_perf.coac = 0;
}

void QEngine::calcPerformance(int countSteps)
{
    const qint64 spentTime = m_timer.elapsed();

    if (m_eng.getField()->m.empty())
        return;

    const int countCells = m_eng.getField()->m.size() * m_eng.getField()->m[0].size();
    m_spentTime += spentTime;

    m_perf.ctis = m_spentTime / 1000;
    m_perf.fups = 1.0 / ((double)spentTime / 1000 / countSteps);
    m_perf.cups = m_perf.fups * countCells;
}

int QEngine::nStep() const
{
    return m_step;
}

void QEngine::sendData() const
{
    emit newData(m_eng.getField());
    emit newStep(nStep());
    emit newPerf(m_perf);
}

void QEngine::loop()
{
    m_start = true;
    while (m_start)
    {
        step();
    }

}
