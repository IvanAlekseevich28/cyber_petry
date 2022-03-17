#pragma once

#include <QObject>
#include <QElapsedTimer>

class ScreenController : public QObject
{
    Q_OBJECT
public:
    explicit ScreenController(QObject *parent = nullptr);

signals:

private:
    unsigned m_FPSLimit=24;
    QElapsedTimer m_FPSTimerLastFrame;
};
