#pragma once

#include <QObject>
#include "core/engine/mainengine.h"
#include "draw/fieldcolor.h"
#include "core/tools/inputengine.h"
#include <QElapsedTimer>
#include "gamescreen.h"
#include "structs/info.h"
#include "structs/size.h"
#include "gui/infomonitor.h"

struct SimParametrs
{
    unsigned FPSLimit=30;
    unsigned countCores=1;
    TSize matrixSize;
    TSize screenSize;
    int seed=time(0);
};

struct StepInfo
{
    long long duration=0;
    bool wasDraw=false;
};

struct LoopInfo
{
    long stepsPerSecond = 0;
    long framesPerSecond = 0;
    long msDuration=1000;
    void reset();
};

class Simulation : public QObject
{
    Q_OBJECT
public:
    explicit Simulation(const SimParametrs& settings, PQGameScreen pScreen = {},
                        PQInfoMonitor pInfoM = {}, QObject *parent = nullptr);


public slots:
    void loop();
    void step(StepInfo &si);
    void stop();
    void reset();

    void askDraw();

private:
    bool needDraw()const;
    Info::Performance calcPerformnce(LoopInfo& li)const;
    void draw()const;


signals:
    void newPerf(Info::Performance perf)const;
    void iteration(int)const;

private:
    SimParametrs m_simPar;

    Eng::InputEngine m_engInput;
    Eng::MainEngine m_engSim;

    PWeakQGameScreen m_pScreen;
    PWeakQInfoMonitor m_pInfoMonitor;

    mutable QElapsedTimer m_FPSTimerLastFrame;
    mutable QElapsedTimer m_secTimer;
    long long m_simDurationTime=0;

    bool m_isLoop;
};

