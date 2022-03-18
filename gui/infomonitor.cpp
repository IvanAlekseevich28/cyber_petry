#include "infomonitor.h"
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <QPainter>
#include "../utils/strnum.h"

QInfoMonitor::QInfoMonitor(QWidget* parent, int w, int h) :
    QOpenGLWidget(parent)
{
    setFixedSize(w,h);
}

void QInfoMonitor::nextMod()
{

}

void QInfoMonitor::prevMode()
{

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
    case M_performance:
    default:
        drawPerformance(m_perfomance);
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
    display.resize(size().width() / 9 , ' ');
    QPainter p(this);
    p.setPen(Qt::white);
    p.drawText(m_curx, m_cury, display);
    m_cury += m_yStep;
}
