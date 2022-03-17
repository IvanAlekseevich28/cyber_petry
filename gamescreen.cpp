#include "gamescreen.h"

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QPainter>

QGameScreen::QGameScreen(QWidget *parent, int w, int h) : QOpenGLWidget(parent)
{
    setFixedSize(w,h);
//    m_pLastClrField = Draw::initClrField(w,h);
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


void QGameScreen::drawSquare(const QColor& clr, double x1, double y1, double sidelength)
{

        glColor3d(clr.redF(),clr.greenF(),clr.blueF());
        glBegin(GL_TRIANGLE_FAN);

        glVertex2d(x1, y1);
        glVertex2d(x1 + sidelength, y1);
        glVertex2d(x1 + sidelength, y1 + sidelength);
        glVertex2d(x1, y1 + sidelength);

        glEnd();
}

void QGameScreen::drawPixSquare(const QColor& clr, int x, int y, int size)
{
    m_painter.setPen(clr);
    m_painter.setBrush(clr);
    //    p.drawLine(rect().topLeft(), rect().bottomRight());
    m_painter.drawRect(x, y, size, size);
}

void QGameScreen::drawMatrix()
{
    const auto vCellsCount = m_pField->m.size();
    const auto hCellsCount = vCellsCount ? m_pField->getH() : 1;

    auto matrixClr = Draw::convertField2Clr(m_pField, m_CellClr, 2);
    if (m_pLastClrField.get() == nullptr)
        m_pLastClrField = Draw::initClrField(vCellsCount, hCellsCount);

    glLoadIdentity();
    glTranslatef(-1,1,0);
    glRotatef(180, 1,0,0);
    glScalef(2.0/vCellsCount, 2.0/hCellsCount, 1);

    for (unsigned x = 0; x < vCellsCount; x++) {
        for (unsigned y = 0; y < hCellsCount; y++)
        {
            const auto& curPixel = (*matrixClr)[x][y];
//            if (curPixel != (*m_pLastClrField)[x][y])
                drawSquare(curPixel,x,y, 1);
        }
    }
    m_pLastClrField = std::move(matrixClr);
}
