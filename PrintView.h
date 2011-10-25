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

#ifndef PRINTVIEW_H
#define PRINTVIEW_H

#include <QtGui/QWidget>
#include <QVector>

class Task;

namespace Ui {
    class PrintView;
}

class PrintView : public QWidget
{
    Q_OBJECT

public:
    explicit PrintView(QWidget *parent = 0);
    ~PrintView();

    void setTasks(const QVector<Task*> &tasks);

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_pushButton_print_clicked();

public slots:
    void recreatePage();

private:
    Ui::PrintView *ui;

    const QVector<Task*> *allTasks;

    void createPage() const;
    unsigned int numOfOpenTasks() const;
};

#endif // PRINTVIEW_H
