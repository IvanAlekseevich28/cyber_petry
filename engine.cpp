#include "engine.h"
#include <unistd.h>

Engine::Engine(QObject *parent) : QObject(parent), m_nStep(0)
{

}

int Engine::step()
{
    m_nStep++;
    usleep(1000*1000); // 1 sec
    emit newData(m_nStep);
    return m_nStep;
}

void Engine::stop()
{
    start = false;
}

int Engine::nStep() const
{
    return m_nStep;
}

void Engine::loop()
{
    start = true;
    while (start)
    {
        step();
    }

}
