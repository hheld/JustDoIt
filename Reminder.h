/*
 * This file is part of JustDoIt.
 *
 * Copyright 2011 Harald Held <harald.held@gmail.com>
 *
 * JustDoIt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * JustDoIt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with JustDoIt.  If not, see <http://www.gnu.org/licenses/>.
 */

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
