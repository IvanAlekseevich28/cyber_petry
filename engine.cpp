#include "engine.h"
#include <unistd.h>
#include "engine/fluid.h"


Engine::Engine(QObject *parent) : QObject(parent)
{
    pGameMatrix = getMat(Point(4,4), 10000);
}

int Engine::step()
{
    pGameMatrix = doFluid(pGameMatrix, MSize(MATH, MATW));
    usleep(1000*5); // 0.5 sec
    emit newData(pGameMatrix);
    emit newStep(pGameMatrix->getIndex());
    return pGameMatrix->getIndex();
}

void Engine::stop()
{
    start = false;
}

int Engine::nStep() const
{
    return pGameMatrix->getIndex();
}

void Engine::loop()
{
    start = true;
    while (start)
    {
        step();
    }

}
