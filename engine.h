#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include "engine/fluidengine.h"

class QEngine : public QObject
{
    Q_OBJECT
public:
    explicit QEngine(QObject *parent = nullptr);

    int nStep() const;

public slots:
    void loop();
    int step();
    void stop();

signals:
    void newData(Eng::PtrField field);
    void newStep(int index);

private:
    Eng::FluidEngine eng;

public:
    bool start;
};

#endif // ENGINE_H
