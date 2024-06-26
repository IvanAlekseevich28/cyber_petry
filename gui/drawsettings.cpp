#include "drawsettings.h"

QDrawSettings::QDrawSettings(QWidget* parent):
    QPushButton(parent)
{
    this->setText("settings");
    m_pMenu = new QMenu(this);

    addAction("water",      Draw::DO_water);
    addAction("oxygen",     Draw::DO_oxygen);
    addAction("carbon",     Draw::DO_carbon);
    addAction("nitrogen",   Draw::DO_nitrogen);
    addAction("acid",       Draw::DO_acid);
    addAction("organic",    Draw::DO_organic);
    addAction("waves",      Draw::DO_waves);

    for (const auto& act : m_actFlags)
        m_pMenu->addAction(act.second.get());

    setMenu(m_pMenu);
}

void QDrawSettings::addAction(QString name, Draw::eDrawObjects dr)
{
    PQAction pAction (new QAction(name));
    pAction->setCheckable(true);
    pAction->setChecked(true);
    connect(pAction.get(), SIGNAL(triggered()), this, SLOT(sendFlags()));
    m_actFlags.emplace_back(std::make_pair(dr, pAction));
}

void QDrawSettings::sendFlags()
{
    int flags = Draw::DO_none;
    for (unsigned i = 0; i < m_actFlags.size() ; i++)
    {
        auto& flag = m_actFlags[i];
        if (flag.second->isChecked())
            flags += (int)flag.first;
    }

    emit newFlags(flags);
}
