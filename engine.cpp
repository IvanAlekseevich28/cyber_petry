#include "engine.h"
#include <unistd.h>
#include "engine/fluid.h"


Engine::Engine(QObject *parent) : QObject(parent)
{
    pGameMatrix = getMat(Point(4,4), 60000);
    pGameMatrix->mat[20][20].water = 50000;
    pGameMatrix->mat[10][35].water = 20000;
    pGameMatrix->mat[22][17].water = 40000;
    pGameMatrix->mat[30][12].water = 60000;
}

int Engine::step()
{
    pGameMatrix = doFluid(pGameMatrix, MSize(MATH, MATW));
//    usleep(1000*5); // 0.5 sec
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
