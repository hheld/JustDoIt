#ifndef REMINDER_H
#define REMINDER_H

#include <QtGui/QWidget>

class TaskTableModel;

namespace Ui {
    class Reminder;
}

class Reminder : public QWidget
{
    Q_OBJECT

public:
    Reminder(TaskTableModel *model, QWidget *parent = 0);
    ~Reminder();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Reminder *ui;

    TaskTableModel *model;
};

#endif // REMINDER_H
