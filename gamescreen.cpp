#include "gamescreen.h"

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QPainter>
#include "engine/tools.h"

QGameScreen::QGameScreen(QWidget *parent, int w, int h) : QOpenGLWidget(parent)
{
    setFixedSize(w,h);
}

void QGameScreen::draw(Eng::PtrField pField)
{
    m_pField = pField;
    update();
}

void QGameScreen::initializeGL()
{
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
}

void QGameScreen::drawSquare(double x1, double y1, double sidelength)
{
    double halfside = sidelength / 2;

    glColor3d(0,1,0);
    glBegin(GL_TRIANGLE_FAN);

    glVertex2d(x1 + halfside, y1 + halfside);
    glVertex2d(x1 + halfside, y1 - halfside);
    glVertex2d(x1 - halfside, y1 - halfside);
    glVertex2d(x1 - halfside, y1 + halfside);

    glEnd();
}

void QGameScreen::drawPixSquare(Eng::CCell cell, int x, int y, int size)
{
    QPainter p(this);
    QColor clr = m_CellClr.getQColor(cell);
    p.setPen(clr);
    p.setBrush(QBrush(clr));
    //    p.drawLine(rect().topLeft(), rect().bottomRight());
    p.drawRect(x, y, size, size);
}

void QGameScreen::drawMatrix()
{
    const auto vCellsCount = m_pField->m.size();
    const auto hCellsCount = vCellsCount ? m_pField->m[0].size() : 0;
    const auto vPixCount = height();
    const auto hPixCount = width();
    const auto vPixCellSize = vPixCount / vCellsCount;
    const auto hPixCellSize = hPixCount / hCellsCount;

    Eng::Tools::PointsRange pr(vCellsCount, hCellsCount);
    while (pr.isEnd() == false)
    {
        Eng::CCell cell = m_pField->m[pr.X()][pr.Y()];

        drawPixSquare(cell, pr.X()*vPixCellSize, pr.Y()*hPixCellSize, vPixCellSize);

        ++pr;
    }
}
