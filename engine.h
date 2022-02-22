#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = nullptr);

    int nStep() const;

public slots:
    void loop();
    int step();
    void stop();

signals:
    void newData(int data);

private:
    int m_nStep;

public:
    bool start;
};

#endif // ENGINE_H
