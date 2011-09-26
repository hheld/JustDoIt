#ifndef REMINDER_H
#define REMINDER_H

#include <QtGui/QWidget>

class TaskTableModel;
class ReminderFilterProxyModel;
class TaskTableColorDoneDelegate;

class QTimer;

namespace Ui {
    class Reminder;
}

class Reminder : public QWidget
{
    Q_OBJECT

public:
    Reminder(TaskTableModel *model, QWidget *parent = 0);
    ~Reminder();

    qint32 numOfDueTasks() const;

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Reminder *ui;

    TaskTableModel *model;
    ReminderFilterProxyModel *proxyModel;
    TaskTableColorDoneDelegate *doneDelegate;

    QTimer *timer_invalidate;
};

#endif // REMINDER_H
