#ifndef TASKTABLEVIEW_H
#define TASKTABLEVIEW_H

#include <QTableView>

class TaskTableView : public QTableView
{
    Q_OBJECT
public:
    explicit TaskTableView(QWidget *parent = 0);

    bool viewportEvent(QEvent *event);
};

#endif // TASKTABLEVIEW_H
