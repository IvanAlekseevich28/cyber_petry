#include "gamescreen.h"
#include <iostream>

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QPainter>

#include <chrono>

QGameScreen::QGameScreen(const TSize &scrSize, const TSize &matSize, QWidget *parent) :
    QOpenGLWidget(parent),
    m_matSize(matSize),
    m_drawFlags(Draw::DO__All)
{
    setFixedSize(scrSize.w,scrSize.h);
    update();
    //    m_pLastClrField = Draw::initClrField(w,h);
}

void QGameScreen::draw(const Eng::PCField& pField, unsigned countCores)
{
    m_countCores = countCores;
    m_pField = pField;
    update();
}

void QGameScreen::setDrawFlags(int flags)
{
    m_drawFlags = flags;
    update();
}

void QGameScreen::getEnginePerformance(Info::Performance perf)
{
    m_perf = perf;
}

void QGameScreen::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit newCoordCell(scaleClick(event->pos()));
//    std::cout << event->pos().rx() << " " << event->pos().ry() << "\n";
}

void QGameScreen::initializeGL()
{
    glLoadIdentity();
    glTranslatef(-1,1,0);
    glRotatef(180, 1,0,0);
    glScalef(2.0/m_matSize.w, 2.0/m_matSize.h, 1);
    QOpenGLFunctions* pFunc = QOpenGLContext::currentContext()->functions();
    pFunc->glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

void QGameScreen::resizeGL(int nWidth, int nHeight)
{
    glViewport(0, 0, nWidth, nHeight);
}

void QGameScreen::paintGL()
{
    if (m_pField.get())
        drawMatrix();

    emit ready();

}

void QGameScreen::drawSquare(const QColor& clr, double x1, double y1, double sidelength)
{
    glColor3d(clr.redF(),clr.greenF(),clr.blueF());

    glVertex2d(x1, y1);
    glVertex2d(x1 + sidelength, y1);
    glVertex2d(x1 + sidelength, y1 + sidelength);
    glVertex2d(x1, y1 + sidelength);

}

void QGameScreen::drawMatrix()
{
    if (m_pField.get() == nullptr)
    {
       std::cerr << "Terrible nullptr!\n";
       return;
    }
    const auto vCellsCount = m_pField->m.size();
    const auto hCellsCount = vCellsCount ? m_pField->getH() : 1;

    m_CellClr.setFDraw(m_drawFlags);
    Draw::PClrField matrixClr;
    try
    {
         matrixClr = Draw::convertField2Clr(m_pField, m_CellClr, m_countCores);
    }  catch (...) {
        std::cerr << "Terrible mistake!\n";
        matrixClr = Draw::initClrField(vCellsCount, hCellsCount);
    }

    if (m_pLastClrField.get() == nullptr)
        m_pLastClrField = Draw::initClrField(vCellsCount, hCellsCount);

    //    glPushMatrix();
    glBegin(GL_QUADS);
    for (unsigned x = 0; x < vCellsCount; x++) {
        for (unsigned y = 0; y < hCellsCount; y++)
        {
            const auto& curPixel = (*matrixClr)[x][y];
            //            if (curPixel != (*m_pLastClrField)[x][y])
            drawSquare(curPixel,x,y, 1);
        }
    }
    glEnd();
    //    glPopMatrix();

    m_pLastClrField = std::move(matrixClr);
}

void QGameScreen::calcPerformance(long duration)
{
    m_perf.fps = 1000000.0 / duration;
    emit newPerf(m_perf);
}

QPoint QGameScreen::scaleClick(const QPoint &coord) const
{
    double multX = static_cast<double>(m_matSize.w) / width();
    double multY = static_cast<double>(m_matSize.h) / height();
    QPoint scoord(static_cast<int>(multX * coord.x()),
                  static_cast<int>(multY * coord.y()));
    return scoord;
}
