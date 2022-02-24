#ifndef QGAMESCREEN_H
#define QGAMESCREEN_H

#include <QOpenGLWidget>
#include <QObject>

class QGameScreen : public QOpenGLWidget
{
    Q_OBJECT
public:
    QGameScreen(QWidget *parent = nullptr);

public slots:
    void draw(int data);

protected:
    virtual void initializeGL() ;
    virtual void resizeGL(int nWidth, int nHeight);
    virtual void paintGL();
    void drawSquare(double x1, double y1, double sidelength);
    void drawPixSquare(int x, int y, int size);

private:
    int data = 0;
};

#endif // QGAMESCREEN_H
