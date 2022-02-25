#ifndef QGAMESCREEN_H
#define QGAMESCREEN_H

#include <QOpenGLWidget>
#include <QObject>
#include "common.h"

class QGameScreen : public QOpenGLWidget
{
    Q_OBJECT
public:
    QGameScreen(QWidget *parent = nullptr, UShort w = 1200, UShort h = 1200);

public slots:
    void draw(PtrGMat pmat);

protected:
    virtual void initializeGL() ;
    virtual void resizeGL(int nWidth, int nHeight);
    virtual void paintGL();
    void drawSquare(double x1, double y1, double sidelength);
    void drawPixSquare(UShort val, int x, int y, int size, MaxMin mmv);
    void drawMatrix();

private:
    PtrGMat pGameMatrix;
};

#endif // QGAMESCREEN_H
