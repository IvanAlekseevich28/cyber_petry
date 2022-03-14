#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamescreen.h"
#include "gui/infomonitor.h"
#include <QThread>
#include <QLCDNumber>
#include <memory>
#include "engine.h"


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
    QEngine m_eng;
    std::unique_ptr<QThread> m_engineThread;
    QGameScreen* m_screen;
    QInfoMonitor* m_imonitor;

};
#endif // MAINWINDOW_H
