#include <QDebug>
#include <QHelpEvent>
#include <QToolTip>

#include "TaskTableView.h"

TaskTableView::TaskTableView(QWidget *parent) :
    QTableView(parent)
{
}

bool TaskTableView::viewportEvent(QEvent *event)
{
    if(event->type() == QEvent::ToolTip)
    {
        QHelpEvent *hevent = static_cast<QHelpEvent*>(event);

        if(columnAt(hevent->pos().x()) == 7)
        {
            int row = rowAt(hevent->pos().y());

            if(row != -1)
            {
                QModelIndex index = indexAt(hevent->pos());

                QToolTip::showText(hevent->globalPos(), index.data().toString(), this, QRect(0, 0, 1, 1));
            }
            else
            {
                QToolTip::hideText();
                event->ignore();
            }
        }
        else
        {
            QToolTip::hideText();
            event->ignore();
        }

        return true;
    }

    return QTableView::viewportEvent(event);
}
