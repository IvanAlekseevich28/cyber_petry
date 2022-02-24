#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include "common.h"

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = nullptr);

    int nStep() const;

public slots:
    void loop();
    int step();
    void stop();

signals:
    void newData(PtrGMat pmat);
    void newStep(int index);

private:
    PtrGMat pGameMatrix;

public:
    bool start;
};

#endif // ENGINE_H
