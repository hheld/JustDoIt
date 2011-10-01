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

#include "Reminder.h"
#include "ui_Reminder.h"

#include <QTimer>

#include "TaskTableModel.h"
#include "ReminderFilterProxyModel.h"
#include "TaskTableColorDoneDelegate.h"
#include "MainWindow.h"

Reminder::Reminder(TaskTableModel *model, MainWindow *mw, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Reminder),
    model(model),
    proxyModel(0),
    doneDelegate(0),
    timer_invalidate(0)
{
    ui->setupUi(this);

    mainWin = mw;

    proxyModel = new ReminderFilterProxyModel(this);
    proxyModel->setSourceModel(model);

    ui->tableView->setModel(proxyModel);

    doneDelegate = new TaskTableColorDoneDelegate(this);
    ui->tableView->setItemDelegateForColumn(0, doneDelegate);

    ui->tableView->resizeColumnsToContents();

    connect(proxyModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), ui->tableView, SLOT(doItemsLayout()));

    connect(ui->checkBox_noMoreReminders, SIGNAL(clicked(bool)), mainWin, SLOT(disableReminders(bool)));

    // invalidate the filter every minute to get accurate reminders
    timer_invalidate = new QTimer(this);
    connect(timer_invalidate, SIGNAL(timeout()), proxyModel, SLOT(invalidate()));
    timer_invalidate->start(1000 * 60);
}

Reminder::~Reminder()
{
    delete ui;
    delete proxyModel; proxyModel = 0;
    delete doneDelegate; doneDelegate = 0;
    delete timer_invalidate; timer_invalidate = 0;
}

void Reminder::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

qint32 Reminder::numOfDueTasks() const
{
    return proxyModel->rowCount();
}

void Reminder::setCheckboxState(bool shouldNotBeChecked)
{
    ui->checkBox_noMoreReminders->setChecked(!shouldNotBeChecked);
}
