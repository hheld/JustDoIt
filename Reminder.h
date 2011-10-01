#ifndef REMINDER_H
#define REMINDER_H

#include <QtGui/QWidget>

class TaskTableModel;
class ReminderFilterProxyModel;
class TaskTableColorDoneDelegate;
class MainWindow;

class QTimer;

namespace Ui {
    class Reminder;
}

class Reminder : public QWidget
{
    Q_OBJECT

public:
    Reminder(TaskTableModel *model, MainWindow *mw, QWidget *parent = 0);
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

    MainWindow *mainWin;

public slots:
    void setCheckboxState(bool shouldNotBeChecked);
};

#endif // REMINDER_H
