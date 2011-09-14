#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "UserData.h"
#include "Task.h"
#include "TaskXmlWriter.h"
#include "TaskTableModel.h"
#include "TaskTableStringListCombobox.h"
#include "TaskTableColorDoneDelegate.h"
#include "TaskSortFilterProxyModel.h"
#include "TaskTableDateTimeDelegate.h"
#include "TaskTableLineEditDelegate.h"
#include "TaskTableTextEditDelegate.h"

#include <QStringListModel>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    uData(0),
    model_groups(0),
    model_locations(0),
    groupDelegate(0),
    locationDelegate(0),
    doneColorDelegate(0),
    sortFilterTasksProxy(0),
    dueDate_delegate(0),
    titleDelegate(0),
    descriptionDelegate(0),
    saveNeeded(false)
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->currentWidget()->setFocus();
    ui->lineEdit_quickTitle->setFocus();

    updateDefaultDueDateTime();
    connect(ui->button_add, SIGNAL(clicked()), this, SLOT(updateDefaultDueDateTime()));

    model_groups = new QStringListModel(this);
    model_locations = new QStringListModel(this);

    ui->listView_groups->setModel(model_groups);
    ui->listView_locations->setModel(model_locations);

    connect(model_groups, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(groupData_changed()));
    connect(model_locations, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(locationData_changed()));

    groupDelegate = new TaskTableStringListComboboxDelegate(this);
    groupDelegate->setModel(model_groups);

    locationDelegate = new TaskTableStringListComboboxDelegate(this);
    locationDelegate->setModel(model_locations);

    doneColorDelegate = new TaskTableColorDoneDelegate(this);

    dueDate_delegate = new TaskTableDateTimeDelegate(this);

    titleDelegate = new TaskTableLineEditDelegate(this);

    descriptionDelegate = new TaskTableTextEditDelegate(this);

    ui->comboBox_quickLocation->setModel(model_locations);
    ui->comboBox_quickGroup->setModel(model_groups);

    // actions
    ui->actionSave->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveData()));
}

MainWindow::~MainWindow()
{
    delete ui;

    delete uData; uData = 0;
    delete model_groups; model_groups = 0;
    delete model_locations; model_locations = 0;
    delete groupDelegate; groupDelegate = 0;
    delete locationDelegate; locationDelegate = 0;
    delete doneColorDelegate; doneColorDelegate = 0;
    delete sortFilterTasksProxy; sortFilterTasksProxy = 0;
    delete dueDate_delegate; dueDate_delegate = 0;
    delete titleDelegate; titleDelegate = 0;
    delete descriptionDelegate; descriptionDelegate = 0;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::setUsrData(UserData *uData)
{
    this->uData = uData;

    model_groups->setStringList(uData->groups());
    model_locations->setStringList(uData->locations());

    model_tasks = new TaskTableModel(uData->tasks(), this);
    connect(model_tasks, SIGNAL(dataChanged(QModelIndex, QModelIndex)), ui->table_tasks, SLOT(resizeColumnsToContents()));
    connect(model_tasks, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(taskData_changed(QModelIndex)));
    connect(model_tasks, SIGNAL(dataChanged(QModelIndex, QModelIndex)), ui->table_tasks->horizontalHeader(), SLOT(doItemsLayout()));
    connect(model_tasks, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(updateStatusMesg()));

    sortFilterTasksProxy = new TaskSortFilterProxyModel(this);
    connect(ui->checkBox_hideDone, SIGNAL(toggled(bool)), sortFilterTasksProxy, SLOT(hideDoneTasks(bool)));
    connect(ui->checkBox_hideDone, SIGNAL(toggled(bool)), ui->table_tasks, SLOT(resizeColumnsToContents()));
    connect(ui->checkBox_hideDone, SIGNAL(toggled(bool)), ui->table_tasks->horizontalHeader(), SLOT(doItemsLayout()));
    connect(ui->lineEdit_searchRegedit, SIGNAL(textEdited(QString)), sortFilterTasksProxy, SLOT(setFilterRegExp(QString)));

    sortFilterTasksProxy->setSourceModel(model_tasks);

    connect(ui->spinBox_dueWithinDays, SIGNAL(valueChanged(int)), sortFilterTasksProxy, SLOT(setNumOfDaysAhead(int)));

    ui->table_tasks->setModel(sortFilterTasksProxy);

    ui->table_tasks->setItemDelegateForColumn(0, locationDelegate);
    ui->table_tasks->setItemDelegateForColumn(1, groupDelegate);
    ui->table_tasks->setItemDelegateForColumn(2, doneColorDelegate);
    ui->table_tasks->setItemDelegateForColumn(5, dueDate_delegate);
    ui->table_tasks->setItemDelegateForColumn(6, titleDelegate);
    ui->table_tasks->setItemDelegateForColumn(7, descriptionDelegate);

    permuteColumns();

    ui->table_tasks->resizeColumnsToContents();

    updateStatusMesg();
}

void MainWindow::saveXML(const QString &fileName)
{
    TaskXmlWriter myWriter(fileName);

    myWriter.uData(uData);

    myWriter.writeDocument();
}

void MainWindow::saveData()
{
    if(saveNeeded)
    {
        saveXML(saveFileName);

        saveNeeded = false;
    }
}

void MainWindow::groupData_changed()
{
    saveNeeded = true;

    uData->groups() = model_groups->stringList();
}

void MainWindow::locationData_changed()
{
    saveNeeded = true;

    uData->locations() = model_locations->stringList();
}

void MainWindow::taskData_changed(QModelIndex index)
{
    Q_UNUSED(index);

    saveNeeded = true;

    uData->tasks() = model_tasks->getTasks();
}

void MainWindow::on_button_addGroup_clicked()
{
    int row = model_groups->rowCount();

    model_groups->insertRows(row, 1);

    QModelIndex index = model_groups->index(row);

    ui->listView_groups->setCurrentIndex(index);
    ui->listView_groups->edit(index);
}

void MainWindow::on_button_insertGroup_clicked()
{
    int row = ui->listView_groups->currentIndex().row();
    model_groups->insertRows(row, 1);

    QModelIndex index = model_groups->index(row);

    if(index.row()<0)
    {
        return;
    }

    ui->listView_groups->setCurrentIndex(index);
    ui->listView_groups->edit(index);
}

void MainWindow::on_button_deleteGroup_clicked()
{
    model_groups->removeRows(ui->listView_groups->currentIndex().row(), 1);

    emit groupData_changed();
}

void MainWindow::setSaveFileName(const QString &xmlOutFileName)
{
    saveFileName = xmlOutFileName;
}

void MainWindow::on_button_addLocation_clicked()
{
    int row = model_locations->rowCount();

    model_locations->insertRows(row, 1);

    QModelIndex index = model_locations->index(row);

    ui->listView_locations->setCurrentIndex(index);
    ui->listView_locations->edit(index);
}

void MainWindow::on_button_insertLocation_clicked()
{
    int row = ui->listView_locations->currentIndex().row();
    model_locations->insertRows(row, 1);

    QModelIndex index = model_locations->index(row);

    if(index.row()<0)
    {
        return;
    }

    ui->listView_locations->setCurrentIndex(index);
    ui->listView_locations->edit(index);
}

void MainWindow::on_button_deleteLocation_clicked()
{
    model_locations->removeRows(ui->listView_locations->currentIndex().row(), 1);

    emit locationData_changed();
}

void MainWindow::on_button_addTask_clicked()
{
    int row = model_tasks->rowCount();

    model_tasks->insertRows(row, 1);

    QModelIndex index = sortFilterTasksProxy->mapFromSource(model_tasks->index(row, 7));

    ui->table_tasks->setCurrentIndex(index);
    ui->table_tasks->edit(index);
}

void MainWindow::on_button_deleteTask_clicked()
{
    QModelIndex index = sortFilterTasksProxy->mapToSource(ui->table_tasks->currentIndex());

    if(index.isValid())
    {
        model_tasks->removeRows(index.row(), 1);
    }

    emit taskData_changed(index);
}

void MainWindow::permuteColumns()
{
    QHeaderView *hw = ui->table_tasks->horizontalHeader();

    hw->moveSection(6, 0);
    hw->moveSection(7, 1);
    hw->moveSection(7, 4);

    hw->setSortIndicator(6, Qt::AscendingOrder);
}

void MainWindow::updateStatusMesg()
{
    ui->statusBar->showMessage(tr("Tasks of user: '%1'; Number of unfinished tasks: %2").arg(uData->name()).arg(QString::number(numOfUnfinishedTasks())));
}

int MainWindow::numOfUnfinishedTasks() const
{
    if(uData)
    {
        int numUndone = 0;

        const QVector<Task*> &allTasks = uData->tasks();
        int numOfTasks = allTasks.size();

        for(int i=0; i<numOfTasks; ++i)
        {
            if(!allTasks.at(i)->done())
            {
                ++numUndone;
            }
        }

        return numUndone;
    }
    else
    {
        return 0;
    }
}

bool MainWindow::event(QEvent *event)
{
    if(event->type() == QEvent::Close && saveNeeded)
    {
        QMessageBox msgBox;
        msgBox.setText(tr("The document has been modified."));
        msgBox.setInformativeText(tr("Do you want to save your changes?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        if(ret == QMessageBox::Save)
        {
            saveData();
        }

        return QMainWindow::event(event);
    }

    return QMainWindow::event(event);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch(index)
    {
    case 0:
        ui->groupBox->setEnabled(false);
        break;

    case 1:
        ui->groupBox->setEnabled(true);
        break;
    }
}

void MainWindow::toggleVisibility()
{
    setVisible(!isVisible());

    if(isVisible())
    {
        ui->tabWidget->setCurrentIndex(0);
        ui->tabWidget->currentWidget()->setFocus();
        ui->lineEdit_quickTitle->setFocus();
    }
}

void MainWindow::on_button_add_clicked()
{
    int row = model_tasks->rowCount();

    model_tasks->insertRows(row, 1);

    QModelIndex indexLocation = model_tasks->index(row, 1);
    QModelIndex indexGroup = model_tasks->index(row, 2);
    QModelIndex indexTitle = model_tasks->index(row, 7);
    QModelIndex indexDescription = model_tasks->index(row, 8);
    QModelIndex indexDueDate = model_tasks->index(row, 6);

    model_tasks->setData(indexLocation, ui->comboBox_quickLocation->currentText());
    model_tasks->setData(indexGroup, ui->comboBox_quickGroup->currentText());
    model_tasks->setData(indexTitle, ui->lineEdit_quickTitle->text());
    model_tasks->setData(indexDescription, ui->plainTextEdit_quickDescription->document()->toPlainText());
    model_tasks->setData(indexDueDate, ui->dateTimeEdit_quickDueDate->dateTime());

    on_button_clear_clicked();
}

void MainWindow::on_button_clear_clicked()
{
    ui->lineEdit_quickTitle->clear();
    ui->plainTextEdit_quickDescription->clear();
    ui->comboBox_quickLocation->setCurrentIndex(-1);
    ui->comboBox_quickGroup->setCurrentIndex(-1);
    ui->lineEdit_quickTitle->setFocus();
}

void MainWindow::updateDefaultDueDateTime()
{
    ui->dateTimeEdit_quickDueDate->setDateTime(QDateTime::currentDateTime());
}
