#pragma once

#include <QOpenGLWidget>
#include <QWidget>
#include "structs/info.h"
#include "structs/size.h"

class QInfoMonitor : public QOpenGLWidget
{
    Q_OBJECT
public:
    enum eMod
    {
        M_performance
    };
    QInfoMonitor(QWidget* parent = nullptr, int w = 160, int h = 160);
    QInfoMonitor(TSize size, QWidget* parent = nullptr);

public slots:
    void nextMod();
    void prevMode();
    void setMod(eMod newMod);
    void newInfoPerformance(Info::Performance perf);

protected:
    virtual void initializeGL() ;
    virtual void resizeGL(int nWidth, int nHeight);
    virtual void paintGL();

    virtual void drawPerformance(Info::Performance perf);
    virtual void drawParametr(const QString& name, double val);
    virtual void drawParametr(const QString& name, int val);
    virtual void drawParametr(const QString& name, const QString& val);

private:
    eMod m_mod;

    Info::Performance m_perfomance;

    int m_yStep=20;
    int m_xStep=0;
    int m_curx=10;
    int m_cury=20;
};

typedef std::shared_ptr<QInfoMonitor> PQInfoMonitor;
typedef std::weak_ptr<QInfoMonitor> PWeakQInfoMonitor;
