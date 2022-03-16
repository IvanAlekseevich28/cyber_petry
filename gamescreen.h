#pragma once

#include <QOpenGLWidget>
#include <QPainter>
#include "core/entities/field.h"
#include "draw/fieldcolor.h"

class QGameScreen : public QOpenGLWidget
{
    Q_OBJECT
public:
    QGameScreen(QWidget *parent = nullptr, int w = 1200, int h = 1200);

public slots:
    void draw(Eng::PField pField);

protected:
    virtual void initializeGL() ;
    virtual void resizeGL(int nWidth, int nHeight);
    virtual void paintGL();
    void drawSquare(const QColor &clr, double x1, double y1, double sidelength);
    void drawPixSquare(const QColor& clr, int x, int y, int size);
    void drawMatrix();

private:
    QPainter m_painter;
    Eng::PField m_pField;
    Draw::CellColor m_CellClr;
    Draw::PClrField m_pLastClrField;
};

