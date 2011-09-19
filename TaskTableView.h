#ifndef TASKTABLEVIEW_H
#define TASKTABLEVIEW_H

#include <QTableView>

class TaskTableView : public QTableView
{
    Q_OBJECT
public:
    explicit TaskTableView(QWidget *parent = 0);

    bool viewportEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void clickedOutsideData();
};

#endif // TASKTABLEVIEW_H
