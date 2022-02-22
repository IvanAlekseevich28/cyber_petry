#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_engineThread.reset(new QThread(this));

    m_LCD = new QLCDNumber();

    auto button_start = new QPushButton("Start");
    auto button_step = new QPushButton("Step");
    auto button_stop = new QPushButton("Stop");
    //     connect(button, SIGNAL(clicked()), this, SLOT(slotGetNumber()));
    connect(button_start, SIGNAL(clicked()), this, SLOT(onStart()));
    connect(button_step, SIGNAL(clicked()), this, SLOT(onStep()));
    connect(button_stop, SIGNAL(clicked()), this, SLOT(onStop()));
    connect(&m_eng, SIGNAL(newData(int)), m_LCD, SLOT(display(int)));
    connect(button_stop, SIGNAL(clicked()), m_engineThread.get(), SLOT(quit()));


    auto layout_buttons = new QVBoxLayout(this);
    layout_buttons->addWidget(m_LCD);
    layout_buttons->addWidget(button_start);
    layout_buttons->addWidget(button_step);
    layout_buttons->addWidget(button_stop);

    layout_buttons->addSpacing(100);
    ui->centralwidget->setLayout(layout_buttons);
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
    connect(&m_eng, SIGNAL(newData(int)), m_engineThread.get(), SLOT(quit()));

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

