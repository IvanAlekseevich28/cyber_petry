#include "engine.h"
#include <unistd.h>
#include "engine/fluidenginetools.h"


QEngine::QEngine(QObject *parent) : QObject(parent),
    eng(Eng::SimParams(true))
{
    Eng::FluidEngineTools()
}

int QEngine::step()
{
    Eng::PtrField pField = eng.step(1);
//    usleep(1000*5); // 0.5 sec
    emit newData(pField);
    emit newStep(pField->index);
    return pField->index;
}

void QEngine::stop()
{
    start = false;
}

int QEngine::nStep() const
{
    return pGameMatrix->getIndex();
}

void QEngine::loop()
{
    start = true;
    while (start)
    {
        step();
    }

}
