#include "engine.h"
#include <unistd.h>
#include "core/tools/fieldtools.h"

#define FIELDSIZE 200

QEngine::QEngine(QObject *parent) : QObject(parent),
    m_eng(Eng::initField(FIELDSIZE, FIELDSIZE)), m_step(0)
{
    Eng::FieldTools etool(m_eng.getState());
//    etool.fillFieldByLiquid(Eng::LT_water, 0x0FFFFFFF);
    for (int i = 0; i < 8; i++)
        etool.addRandomLiquid(0x000FFFFF);
    etool.addRandomLiquid(0x04FFFFFFF, Eng::LT_water);
}

int QEngine::step()
{
    const int countThreads = 8;
    m_perf.coac = countThreads;
    m_timer.start();
    Eng::PField pField = m_eng.step(countThreads);
    calcPerformance(1);
    m_step += 1;
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

    if (m_eng.getState()->m.empty())
        return;

    const int countCells = m_eng.getState()->m.size() * m_eng.getState()->getH();
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
    emit newData(m_eng.getState());
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
