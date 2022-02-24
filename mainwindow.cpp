#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLayout>
#include <QPushButton>
#include <QMetaType>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto m_screen = new QGameScreen(this, 600, 600);
    auto layout_screen = new QHBoxLayout(this);
    layout_screen->addWidget(m_screen);


    m_engineThread.reset(new QThread(this));

    qRegisterMetaType<PtrGMat>();
    m_LCD = new QLCDNumber();
    m_LCD->setFixedHeight(100);

    auto button_start = new QPushButton("Start");
    auto button_step = new QPushButton("Step");
    auto button_stop = new QPushButton("Stop");
    //     connect(button, SIGNAL(clicked()), this, SLOT(slotGetNumber()));
    connect(button_start, SIGNAL(clicked()), this, SLOT(onStart()));
    connect(button_step, SIGNAL(clicked()), this, SLOT(onStep()));
    connect(button_stop, SIGNAL(clicked()), this, SLOT(onStop()));
    connect(&m_eng, SIGNAL(newStep(int)), m_LCD, SLOT(display(int)));
    connect(&m_eng, SIGNAL(newData(PtrGMat)), m_screen, SLOT(draw(PtrGMat)));
    connect(button_stop, SIGNAL(clicked()), m_engineThread.get(), SLOT(quit()));


    auto layout_buttons = new QVBoxLayout(this);
    layout_buttons->addWidget(m_LCD);
    layout_buttons->addWidget(button_start);
    layout_buttons->addWidget(button_step);
    layout_buttons->addWidget(button_stop);

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
    disconnect(m_engineThread.get(), SIGNAL(started()), &m_eng, nullptr);
    m_eng.moveToThread(m_engineThread.get());
    connect(m_engineThread.get(), SIGNAL(started()), &m_eng, SLOT(loop()));

    m_engineThread->start();
}

void MainWindow::onStep()
{
    onStop();
    m_engineThread->quit();

    disconnect(m_engineThread.get(), SIGNAL(started()), &m_eng, nullptr);
    m_eng.moveToThread(m_engineThread.get());
    connect(m_engineThread.get(), SIGNAL(started()), &m_eng, SLOT(step()));
    connect(&m_eng, SIGNAL(newData(PtrGMat)), m_engineThread.get(), SLOT(quit()));

    m_engineThread->start();
}

void MainWindow::onStop()
{
    m_eng.start = false;
}

void MainWindow::setLCD(int num)
{
    m_LCD->display(num);
}

