#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include "core/engine/mainengine.h"
#include "structs/size.h"
#include "structs/info.h"
#include <QElapsedTimer>
#include <chrono>

class QEngine : public QObject
{
    Q_OBJECT
public:
    explicit QEngine(TSize matSize, QObject *parent = nullptr);

    int nStep() const;
    void sendData()const;

public slots:
    void loop();
    int step();
    void stop();
    void reset();

signals:
    void newData(Eng::PField field)const;
    void newStep(int index)const;
    void newPerf(Info::Performance perf)const;

private:
    void calcPerformance(int countSteps);

private:
    Eng::MainEngine m_eng;
    Info::Performance m_perf;
    QElapsedTimer m_timer;
    qint64 m_spentTime=0;
    TSize m_matSize;

public:
    bool m_start;
    int m_step;

private:
    unsigned m_FPSLimit=24;
    QElapsedTimer m_FPSTimerLastFrame;

private:
    double m_realFPS;
    std::chrono::high_resolution_clock::time_point m_lastFrameTime;
};

#endif // ENGINE_H
