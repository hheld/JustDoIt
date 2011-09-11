#ifndef TASKTABLEDATETIMEDELEGATE_H
#define TASKTABLEDATETIMEDELEGATE_H

#include <QStyledItemDelegate>

class TaskTableDateTimeDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TaskTableDateTimeDelegate(QObject *parent = 0);

signals:

public slots:

};

#endif // TASKTABLEDATETIMEDELEGATE_H
