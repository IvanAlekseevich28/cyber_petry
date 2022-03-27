#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLayout>
#include <QPushButton>
#include <QMetaType>
#include <QMenu>

#define FIELDSIZE 950
#define SCRSIZE 950

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SimParametrs spar;
    spar.matrixSize = TSize(FIELDSIZE);
    spar.screenSize = TSize(SCRSIZE);
    spar.countCores = std::thread::hardware_concurrency() - 1;
    if (spar.countCores < 1)
        spar.countCores = 1;

    m_pSimulation.reset(new Simulation(spar, nullptr));
    m_pScreen = m_pSimulation->initGameScreen();
    m_pImonitor = m_pSimulation->initInfoMonitor(TSize(180, 360));

    auto layout_game = new QVBoxLayout(this);
    auto layout_screen = new QHBoxLayout(this);
    layout_game->addWidget(m_pScreen.get());

    auto layout_under_gs = new QHBoxLayout(this);

    auto button_draw_param = new QDrawSettings(this);
    layout_under_gs->addWidget(button_draw_param);
    layout_game->addLayout(layout_under_gs);
    layout_screen->addLayout(layout_game);
    connect(button_draw_param, SIGNAL(newFlags(int)), m_pScreen.get(), SLOT(setDrawFlags(int)));


    m_engineThread.reset(new QThread(this));

    qRegisterMetaType<Eng::PField>();
    qRegisterMetaType<Info::Performance>();
    m_LCD = new QLCDNumber();
    m_LCD->setFixedHeight(100);

    auto button_start = new QPushButton("Start");
    auto button_step = new QPushButton("Step");
    auto button_stop = new QPushButton("Stop");
    auto button_reset = new QPushButton("Reset");
    //     connect(button, SIGNAL(clicked()), this, SLOT(slotGetNumber()));
    connect(button_start, SIGNAL(clicked()), this, SLOT(onStart()));
    connect(button_step, SIGNAL(clicked()), this, SLOT(onStep()));
    connect(button_stop, SIGNAL(clicked()), this, SLOT(onStop()));
    connect(button_reset, SIGNAL(clicked()), this, SLOT(onReset()));

    connect(m_pSimulation.get(), SIGNAL(iteration(int)), m_LCD, SLOT(display(int)));
    m_pImonitor->update();
    connect(button_stop, SIGNAL(clicked()), m_engineThread.get(), SLOT(quit()));


    auto layout_buttons = new QVBoxLayout(this);
    layout_buttons->addWidget(m_LCD);
    layout_buttons->addWidget(m_pImonitor.get());
    layout_buttons->addWidget(button_start);
    layout_buttons->addWidget(button_step);
    layout_buttons->addWidget(button_stop);
    layout_buttons->addWidget(button_reset);

    layout_buttons->addSpacing(100);
    layout_screen->addLayout(layout_buttons);
    ui->centralwidget->setLayout(layout_screen);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onStart()
{
    disconnect(m_engineThread.get(), SIGNAL(started()), m_pSimulation.get(), nullptr);
    m_pSimulation->moveToThread(m_engineThread.get());
    connect(m_engineThread.get(), SIGNAL(started()), m_pSimulation.get(), SLOT(loop()));

    m_engineThread->start();
}

void MainWindow::onStep()
{
    onStop();
    m_engineThread->quit();

    disconnect(m_engineThread.get(), SIGNAL(started()), m_pSimulation.get(), nullptr);
    m_pSimulation->moveToThread(m_engineThread.get());
    connect(m_engineThread.get(), SIGNAL(started()), m_pSimulation.get(), SLOT(step()));

    m_engineThread->start();
}

void MainWindow::onStop()
{
    m_pSimulation->stop();
}

void MainWindow::onReset()
{
    m_pSimulation->reset();
    m_LCD->display(0);
}

void MainWindow::setLCD(int num)
{
    m_LCD->display(num);
}

