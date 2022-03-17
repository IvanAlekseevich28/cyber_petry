#pragma once

#include <QOpenGLWidget>
#include <QPainter>
#include <structs/size.h>
#include "core/entities/field.h"
#include "draw/fieldcolor.h"

class QGameScreen : public QOpenGLWidget
{
    Q_OBJECT
public:
    QGameScreen(const TSize& scrSize, const TSize& matSize, QWidget *parent = nullptr);

public slots:
    void draw(Eng::PField pField);

protected:
    virtual void initializeGL() ;
    virtual void resizeGL(int nWidth, int nHeight);
    virtual void paintGL();
    void drawSquare(const QColor &clr, double x1, double y1, double sidelength);
    void drawMatrix();

private:
    TSize m_matSize;
    Eng::PField m_pField;
    Draw::CellColor m_CellClr;
    Draw::PClrField m_pLastClrField;
};

