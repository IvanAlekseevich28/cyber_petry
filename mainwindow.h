#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamescreen.h"
#include "gui/infomonitor.h"
#include "gui/drawsettings.h"
#include <QThread>
#include <QLCDNumber>
#include <memory>
#include "simulation.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStart();
    void onStep();
    void onStop();
    void onReset();
    void setLCD(int num);


private:
    Ui::MainWindow *ui;
    QLCDNumber *m_LCD;
    std::unique_ptr<QThread> m_engineThread;

    PSimulation m_pSimulation;
    PQGameScreen m_pScreen;
    PQInfoMonitor m_pImonitor;

};
#endif // MAINWINDOW_H
