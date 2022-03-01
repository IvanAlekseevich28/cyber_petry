#pragma once

#include <QOpenGLWidget>
#include <QObject>
#include "engine/types.h"
#include "draw/colorengine.h"
#include "draw/cellcolor.h"

class QGameScreen : public QOpenGLWidget
{
    Q_OBJECT
public:
    QGameScreen(QWidget *parent = nullptr, int w = 1200, int h = 1200);

public slots:
    void draw(Eng::PtrField pField);

protected:
    virtual void initializeGL() ;
    virtual void resizeGL(int nWidth, int nHeight);
    virtual void paintGL();
    void drawSquare(double x1, double y1, double sidelength);
    void drawPixSquare(Eng::CCell cell, int x, int y, int size);
    void drawMatrix();

private:
    Eng::PtrField m_pField;
    Draw::CellColor m_CellClr;
};

