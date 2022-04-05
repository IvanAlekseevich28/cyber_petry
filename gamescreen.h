#pragma once

#include <QOpenGLWidget>
#include <QPainter>
#include <structs/size.h>
#include "core/entities/field.h"
#include "draw/fieldcolor.h"
#include "structs/info.h"

class QGameScreen : public QOpenGLWidget
{
    Q_OBJECT
public:
    QGameScreen(const TSize& scrSize, const TSize& matSize, QWidget *parent = nullptr);

public slots:
    void draw(const Eng::PCField &pField, unsigned countCores = 1);
    void setDrawFlags(int flags = Draw::DO__All);
    void getEnginePerformance(Info::Performance perf);
    void newMousePos(QMouseEvent *event)const;

signals:
    void ready();
    void newPerf(Info::Performance perf)const;
    void newCoordCell(QPoint p)const;

protected:
    virtual void initializeGL() ;
    virtual void resizeGL(int nWidth, int nHeight);
    virtual void paintGL();
    void drawSquare(const QColor &clr, double x1, double y1, double sidelength);
    void drawMatrix();

    void calcPerformance(long duration);

private:
    TSize m_matSize;
    Eng::PCField m_pField;
    Draw::CellColor m_CellClr;
    Draw::PClrField m_pLastClrField;
    int m_drawFlags;
    unsigned m_countCores=1;

    Info::Performance m_perf;
};

typedef std::shared_ptr<QGameScreen> PQGameScreen;
typedef std::weak_ptr<QGameScreen> PWeakQGameScreen;

