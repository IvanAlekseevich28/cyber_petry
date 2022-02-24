#include "gamescreen.h"
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QPainter>

QGameScreen::QGameScreen(QWidget *parent) : QOpenGLWidget(parent)
{

}

void QGameScreen::draw(int data)
{
    this->data = data;
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
    //    QOpenGLWidget::resizeGL(nWidth, nHeight);
    //    glMatrixМode(GL_PROJECTION);
    //    glLoadidentity();
    //    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
    //    glOrtho(0, 100, 100, 0, -1, 1);
}

void QGameScreen::paintGL()
{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    glBegin(GL_QUADS);
//    glColor3f(1.0, 0.0, 0.0);
//    glVertex3f(-0.5, -0.5, 0);

//    glColor3f(0.0, 1.0, 0.0);
//    glVertex3f(0.5, -0.5, 0);

//    glColor3f(0.0, 0.0, 1.0);
//    glVertex3f(-0.5, 0.5, 0);

//    glColor3f(0.0, 1.0, 1.0);
//    glVertex3f(0.5, 0.5, 0);
//    glEnd();
    drawPixSquare(data*20, data*20, 20);

}

void QGameScreen::drawSquare(double x1, double y1, double sidelength)
{
    double halfside = sidelength / 2;

    glColor3d(0,1,0);
    glBegin(GL_POLYGON);

    glVertex2d(x1 + halfside, y1 + halfside);
    glVertex2d(x1 + halfside, y1 - halfside);
    glVertex2d(x1 - halfside, y1 - halfside);
    glVertex2d(x1 - halfside, y1 + halfside);

    glEnd();
}

void QGameScreen::drawPixSquare(int x, int y, int size)
{
    QPainter p(this);
    p.setPen(Qt::blue);
    p.setBrush(QBrush(Qt::black));
//    p.drawLine(rect().topLeft(), rect().bottomRight());
    p.drawRect(x, y, size, size);
}
