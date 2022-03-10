#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include "core/engine/mainengine.h"
#include "structs/info.h"
#include <QElapsedTimer>

class QEngine : public QObject
{
    Q_OBJECT
public:
    explicit QEngine(QObject *parent = nullptr);

    int nStep() const;
    void sendData()const;

public slots:
    void loop();
    int step();
    void stop();

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

public:
    bool m_start;
    int m_step;
};

#endif // ENGINE_H
