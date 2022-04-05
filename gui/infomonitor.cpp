#include "infomonitor.h"
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <QPainter>
#include "../utils/strnum.h"

QInfoMonitor::QInfoMonitor(QWidget* parent, int w, int h) :
    QOpenGLWidget(parent)
{
    setFixedSize(w,h);
    m_mod = M_cellInfo;
    qRegisterMetaType<Eng::PosCell>();
}

QInfoMonitor::QInfoMonitor(TSize size, QWidget *parent) :
    QOpenGLWidget(parent)
{
    setFixedSize(size.w, size.h);
}

void QInfoMonitor::nextMod()
{
    switch (m_mod)
    {
    case M_performance:
        m_mod = M_cellInfo;
        break;
    default:
        m_mod = M_performance;
    }
}

void QInfoMonitor::prevMode()
{
    switch (m_mod)
    {
    case M_performance:
        m_mod = M_cellInfo;
        break;
    default:
        m_mod = M_performance;
    }
}

void QInfoMonitor::setMod(eMod newMod)
{
    m_mod = newMod;
}

void QInfoMonitor::newInfoPerformance(Info::Performance perf)
{
    m_perfomance = perf;
    update();
}

void QInfoMonitor::newCell(Eng::PosCell cell)
{
    m_optPoscell = cell;
    update();
}

void QInfoMonitor::initializeGL()
{
    QOpenGLFunctions* pFunc = QOpenGLContext::currentContext()->functions();
    pFunc->glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void QInfoMonitor::resizeGL(int nWidth, int nHeight)
{
    glViewport(0, 0, nWidth, nHeight);
}

void QInfoMonitor::paintGL()
{
    m_cury = m_yStep;
    switch (m_mod)
    {
    case M_cellInfo:
        drawCellInfo();
        break;
    case M_performance:
    default:
        drawCellInfo();
    }
}

void QInfoMonitor::drawPerformance(Info::Performance perf)
{
    drawParametr(" CUPS", QString::fromStdString(Utils::bigLong2Str(perf.cups)));
    drawParametr("  UPS", perf.ups);
    drawParametr("  FPS", QString::fromStdString(Utils::bigLong2Str(perf.fps)));
    drawParametr(" Time", QString::fromStdString(Utils::secondsToTime(perf.ctis)));
    drawParametr("Cores", perf.coac);
}

void QInfoMonitor::drawCellInfo()
{
    if (m_optPoscell.has_value() == false)
    {
        drawString("none");
        return;
    }
    Eng::CPosCell cell = m_optPoscell.value();
    QString coord = "(" + QString::number(cell.x) + ", " + QString::number(cell.y) + ")";
    drawParametr("Point", coord);

    drawParametr("wave val", cell.wave);
    drawParametr("wave spd", cell.wave1 - cell.wave2);

    const auto countLiquds = cell.countLiquids();
    drawParametr("Value", countLiquds);

    drawProcent("   water", countLiquds, cell.arrLiquids[Eng::LT_water]);
    drawProcent("  oxygen", countLiquds, cell.arrLiquids[Eng::LT_oxygen]);
    drawProcent("  carbon", countLiquds, cell.arrLiquids[Eng::LT_carbon]);
    drawProcent("nitrogen", countLiquds, cell.arrLiquids[Eng::LT_nitrogen]);
    drawProcent("    acid", countLiquds, cell.arrLiquids[Eng::LT_acid]);
    drawProcent(" organic", countLiquds, cell.arrLiquids[Eng::LT_organic]);
}

void QInfoMonitor::drawProcent(const QString &name, TNumber den, TNumber num)
{
    if (num == 0) return;

    double procent = static_cast<double>(num) / den * 100;
    QString strProcent = QString::number(procent,'f', 3) + "%";
    drawParametr(name, strProcent);
}

void QInfoMonitor::drawParametr(const QString &name, double val)
{
    drawParametr(name, QString::number(val,'f', 2));

}

void QInfoMonitor::drawParametr(const QString &name, int val)
{
    drawParametr(name, QString::number(val));
}

void QInfoMonitor::drawParametr(const QString &name, const QString &val)
{
    QString display = name + ": " + val;
    drawString(display);
}

void QInfoMonitor::drawString(QString display)
{
    display.resize(size().width() / 9 , ' ');
    QPainter p(this);
    p.setPen(Qt::white);
    p.drawText(m_curx, m_cury, display);
    m_cury += m_yStep;
}
