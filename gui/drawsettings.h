#pragma once

#include <QPushButton>
#include <QAction>
#include <QMenu>
#include "../draw/paintflags.h"

typedef std::shared_ptr<QAction> PQAction;
typedef std::pair<Draw::eDrawObjects, PQAction> Flag;

class QDrawSettings : public QPushButton
{
    Q_OBJECT
public:
    QDrawSettings(QWidget *parent = nullptr);
private:
    void addAction(QString name, Draw::eDrawObjects dr);

private slots:
    void sendFlags();

signals:
    void newFlags(int);

private:
    std::vector<Flag> m_actFlags;
    QMenu* m_pMenu=nullptr;
};

