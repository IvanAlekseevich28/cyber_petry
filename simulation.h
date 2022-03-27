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
    int countCores=1;
    TSize matrixSize=TSize(0);
    TSize screenSize=TSize(0);
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
    explicit Simulation(const SimParametrs& settings, QObject *parent = nullptr);

    PQGameScreen initGameScreen();
    PQInfoMonitor initInfoMonitor(TSize size);

public slots:
    void loop();
    void step(StepInfo &si);
    void step();
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

    Eng::MainEngine m_engSim;
    Eng::InputEngine m_engInput;

    PWeakQGameScreen m_pScreen;
    PWeakQInfoMonitor m_pInfoMonitor;

    mutable QElapsedTimer m_FPSTimerLastFrame;
    mutable QElapsedTimer m_secTimer;
    long long m_simDurationTime=0;

    bool m_isLoop;
};

typedef std::unique_ptr<Simulation> PSimulation;

