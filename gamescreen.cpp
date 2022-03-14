#include "gamescreen.h"

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QPainter>

QGameScreen::QGameScreen(QWidget *parent, int w, int h) : QOpenGLWidget(parent)
{
    setFixedSize(w,h);
}

void QGameScreen::draw(Eng::PField pField)
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

void QGameScreen::drawPixSquare(const QColor& clr, int x, int y, int size)
{
    QPainter p(this);
    p.setPen(clr);
    p.setBrush(QBrush(clr));
    //    p.drawLine(rect().topLeft(), rect().bottomRight());
    p.drawRect(x, y, size, size);
}

void QGameScreen::drawMatrix()
{
    const auto vCellsCount = m_pField->m.size();
    const auto hCellsCount = vCellsCount ? m_pField->getH() : 1;
    const auto vPixCount = height();
    const auto hPixCount = width();
    const auto vPixCellSize = vPixCount / vCellsCount;
    const auto hPixCellSize = hPixCount / hCellsCount;

    auto matrixClr = Draw::convertField2Clr(m_pField, m_CellClr, 8);
    for (unsigned x = 0; x < vCellsCount; x++)
        for (unsigned y = 0; y < hCellsCount; y++)
            drawPixSquare((*matrixClr)[x][y], x*vPixCellSize, y*hPixCellSize, vPixCellSize);
}
