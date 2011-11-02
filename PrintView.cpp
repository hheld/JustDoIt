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

#include <QTextTable>
#include <QPrintDialog>
#include <QPrinter>
#include <QtAlgorithms>

#include "PrintView.h"
#include "ui_PrintView.h"
#include "Task.h"

bool TaskLessThan(Task* const t1, Task* const t2)
{
    return t1->dueDate() < t2->dueDate();
}

PrintView::PrintView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrintView),
    allTasks(0)
{
    ui->setupUi(this);

    connect(ui->radioButton_all, SIGNAL(clicked()), this, SLOT(recreatePage()));
    connect(ui->radioButton_week, SIGNAL(clicked()), this, SLOT(recreatePage()));
    connect(ui->radioButton_month, SIGNAL(clicked()), this, SLOT(recreatePage()));
}

PrintView::~PrintView()
{
    delete ui;
}

void PrintView::changeEvent(QEvent *e)
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

void PrintView::setTasks(QVector<Task *> &tasks)
{
    allTasks = &tasks;

    createPage();
}

void PrintView::createPage() const
{
    QTextCursor cursor(ui->textEdit->textCursor());

    QTextCharFormat format(cursor.charFormat());
    format.setFontFamily("Times");

    QTextCharFormat boldFormat = format;
    boldFormat.setFontWeight(QFont::Bold);

    unsigned int numOfTasks = numOfOpenTasks();

    if(!numOfTasks)
    {
        cursor.insertText(tr("There are currently no open tasks."), format);

        return;
    }
    else
    {
        cursor.insertText(tr("Open tasks as of %1\n\n").arg(QDateTime::currentDateTime().toString()), format);
    }

    // sort tasks ascending according to their due dates
    qSort(allTasks->begin(), allTasks->end(), TaskLessThan);

    QTextTableFormat tableFormat;
    tableFormat.setCellPadding(10.);
    tableFormat.setCellSpacing(0.);
    tableFormat.setHeaderRowCount(1);

    int rows = numOfTasks + 1/*allTasks.size()+1*/, columns = 6;
    QTextTable *table = cursor.insertTable(rows, columns, tableFormat);

    QTextTableCell cell;
    QTextCursor cellCursor;

    for (int column=0; column<columns; ++column)
    {
        cell = table->cellAt(0, column);
        cellCursor = cell.firstCursorPosition();

        switch(column)
        {
        case 0:
            cellCursor.insertText(tr("Due date"), boldFormat);
            break;

        case 1:
            cellCursor.insertText(tr("Title"), boldFormat);
            break;

        case 2:
            cellCursor.insertText(tr("Description"), boldFormat);
            break;

        case 3:
            cellCursor.insertText(tr("Category"), boldFormat);
            break;

        case 4:
            cellCursor.insertText(tr("Location"), boldFormat);
            break;

        case 5:
            cellCursor.insertText(tr("Done"), boldFormat);
            break;
        }
    }

    int actualRow = 0;

    // as radio buttons they are exclusive, therefore we don't need a flag for the third 'all' option
    bool showWeek = ui->radioButton_week->isChecked();
    bool showMonth = ui->radioButton_month->isChecked();

    for (int row=0; row<allTasks->size(); ++row)
    {
        if(allTasks->at(row)->done())
        {
            continue;
        }

        if(showWeek)
        {
            if(allTasks->at(row)->dueDate()>QDateTime::currentDateTime().addDays(7))
            {
                continue;
            }
        }
        else if(showMonth)
        {
            if(allTasks->at(row)->dueDate()>QDateTime::currentDateTime().addDays(30))
            {
                continue;
            }
        }

        for (int column=0; column<columns; ++column)
        {
            cell = table->cellAt(actualRow+1, column);
            cellCursor = cell.firstCursorPosition();

            switch(column)
            {
            case 0:
                cellCursor.insertText(allTasks->at(row)->dueDate().toString(), format);
                break;

            case 1:
                cellCursor.insertText(allTasks->at(row)->title(), format);
                break;

            case 2:
                cellCursor.insertText(allTasks->at(row)->description(), format);
                break;

            case 3:
                cellCursor.insertText(allTasks->at(row)->category(), format);
                break;

            case 4:
                cellCursor.insertText(allTasks->at(row)->location(), format);
                break;
            }
        }

        ++actualRow;
    }
}

unsigned int PrintView::numOfOpenTasks() const
{
    unsigned int noot = 0;

    unsigned int numOfTasks = allTasks->size();

    for(unsigned int i=0; i<numOfTasks; ++i)
    {
        // as radio buttons they are exclusive, therefore we don't need a flag for the third 'all' option
        bool showWeek = ui->radioButton_week->isChecked();
        bool showMonth = ui->radioButton_month->isChecked();

        if(showWeek)
        {
            if(allTasks->at(i)->dueDate()>QDateTime::currentDateTime().addDays(7))
            {
                continue;
            }
        }
        else if(showMonth)
        {
            if(allTasks->at(i)->dueDate()>QDateTime::currentDateTime().addDays(30))
            {
                continue;
            }
        }

        if(!allTasks->at(i)->done())
        {
            ++noot;
        }
    }

    return noot;
}

void PrintView::on_pushButton_print_clicked()
{
    QPrinter printer;

    QPrintDialog printDialog(&printer, this);

    if (printDialog.exec() == QDialog::Accepted)
    {
        ui->textEdit->print(&printer);
    }
}

void PrintView::recreatePage()
{
    ui->textEdit->clear();
    createPage();
}
