#pragma once

#include <QOpenGLWidget>
#include <QWidget>
#include "structs/info.h"
#include "structs/size.h"
#include "../core/entities/poscell.h"
#include <optional>

typedef long long TNumber;

class QInfoMonitor : public QOpenGLWidget
{
    Q_OBJECT
public:
    enum eMod
    {
        M_performance,
        M_cellInfo
    };
    QInfoMonitor(QWidget* parent = nullptr, int w = 160, int h = 160);
    QInfoMonitor(TSize size, QWidget* parent = nullptr);

public slots:
    void nextMod();
    void prevMode();
    void setMod(eMod newMod);
    void newInfoPerformance(Info::Performance perf);
    void newCell(Eng::PosCell cell);

protected:
    virtual void initializeGL() ;
    virtual void resizeGL(int nWidth, int nHeight);
    virtual void paintGL();

    virtual void drawPerformance(Info::Performance perf);
    virtual void drawCellInfo();
    virtual void drawProcent (const QString& name, TNumber den, TNumber num);
    virtual void drawParametr(const QString& name, double val);
    virtual void drawParametr(const QString& name, int val);
    virtual void drawParametr(const QString& name, const QString& val);
    virtual void drawString(QString display);

private:
    eMod m_mod;

    Info::Performance m_perfomance;
    std::optional<Eng::PosCell> m_optPoscell;

    int m_yStep=20;
    int m_xStep=0;
    int m_curx=10;
    int m_cury=20;
};

typedef std::shared_ptr<QInfoMonitor> PQInfoMonitor;
typedef std::weak_ptr<QInfoMonitor> PWeakQInfoMonitor;
