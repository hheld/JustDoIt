#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "UserData.h"
#include "Task.h"
#include "TaskXmlWriter.h"
#include "TaskTableModel.h"
#include "TaskTableStringListCombobox.h"
#include "TaskTableColorDoneDelegate.h"
#include "TaskSortFilterProxyModel.h"

#include <QStringListModel>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    uData(0),
    model_realms(0),
    model_locations(0),
    realmDelegate(0),
    locationDelegate(0),
    doneColorDelegate(0),
    sortFilterTasksProxy(0)
{
    ui->setupUi(this);

    model_realms = new QStringListModel(this);
    model_locations = new QStringListModel(this);

    ui->listView_realms->setModel(model_realms);
    ui->listView_locations->setModel(model_locations);

    connect(model_realms, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(realmData_changed()));
    connect(model_locations, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(locationData_changed()));

    realmDelegate = new TaskTableStringListComboboxDelegate(this);
    realmDelegate->setModel(model_realms);

    locationDelegate = new TaskTableStringListComboboxDelegate(this);
    locationDelegate->setModel(model_locations);

    doneColorDelegate = new TaskTableColorDoneDelegate(this);
}

MainWindow::~MainWindow()
{
    delete ui;

    delete uData; uData = 0;
    delete model_realms; model_realms = 0;
    delete model_locations; model_locations = 0;
    delete realmDelegate; realmDelegate = 0;
    delete locationDelegate; locationDelegate = 0;
    delete doneColorDelegate; doneColorDelegate = 0;
    delete sortFilterTasksProxy; sortFilterTasksProxy = 0;
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

    model_realms->setStringList(uData->realms());
    model_locations->setStringList(uData->locations());

    model_tasks = new TaskTableModel(uData->tasks(), this);
    connect(model_tasks, SIGNAL(dataChanged(QModelIndex, QModelIndex)), ui->table_tasks, SLOT(resizeColumnsToContents()));
    connect(model_tasks, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(taskData_changed(QModelIndex)));
    connect(model_tasks, SIGNAL(dataChanged(QModelIndex, QModelIndex)), ui->table_tasks->horizontalHeader(), SLOT(doItemsLayout()));

    sortFilterTasksProxy = new TaskSortFilterProxyModel(this);
    connect(ui->checkBox_hideDone, SIGNAL(toggled(bool)), sortFilterTasksProxy, SLOT(hideDoneTasks(bool)));
    connect(ui->checkBox_hideDone, SIGNAL(toggled(bool)), ui->table_tasks, SLOT(resizeColumnsToContents()));
    connect(ui->checkBox_hideDone, SIGNAL(toggled(bool)), ui->table_tasks->horizontalHeader(), SLOT(doItemsLayout()));

    sortFilterTasksProxy->setSourceModel(model_tasks);

    ui->table_tasks->setModel(sortFilterTasksProxy);

    ui->table_tasks->setItemDelegateForColumn(0, locationDelegate);
    ui->table_tasks->setItemDelegateForColumn(1, realmDelegate);
    ui->table_tasks->setItemDelegateForColumn(2, doneColorDelegate);

    permuteColumns();

    ui->table_tasks->resizeColumnsToContents();
}

void MainWindow::saveXML(const QString &fileName)
{
    TaskXmlWriter myWriter(fileName);

    myWriter.uData(uData);

    myWriter.writeDocument();
}

void MainWindow::on_button_save_clicked()
{
    saveXML(saveFileName);
}

void MainWindow::realmData_changed()
{
    uData->realms() = model_realms->stringList();
}

void MainWindow::locationData_changed()
{
    uData->locations() = model_locations->stringList();
}

void MainWindow::taskData_changed(QModelIndex index)
{
    Q_UNUSED(index);
}

void MainWindow::on_button_addRealm_clicked()
{
    int row = model_realms->rowCount();

    model_realms->insertRows(row, 1);

    QModelIndex index = model_realms->index(row);

    ui->listView_realms->setCurrentIndex(index);
    ui->listView_realms->edit(index);
}

void MainWindow::on_button_insertRealm_clicked()
{
    int row = ui->listView_realms->currentIndex().row();
    model_realms->insertRows(row, 1);

    QModelIndex index = model_realms->index(row);

    if(index.row()<0)
    {
        return;
    }

    ui->listView_realms->setCurrentIndex(index);
    ui->listView_realms->edit(index);
}

void MainWindow::on_button_deleteRealm_clicked()
{
    model_realms->removeRows(ui->listView_realms->currentIndex().row(), 1);

    emit realmData_changed();
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

    QModelIndex index = sortFilterTasksProxy->mapFromSource(model_tasks->index(row, 1));

    ui->table_tasks->setCurrentIndex(index);
    ui->table_tasks->edit(index);
}

void MainWindow::on_button_deleteTask_clicked()
{
    if(ui->table_tasks->currentIndex().isValid())
    {
        model_tasks->removeRows(ui->table_tasks->currentIndex().row(), 1);
    }

    emit taskData_changed(ui->table_tasks->currentIndex());
}

void MainWindow::permuteColumns()
{
    QHeaderView *hw = ui->table_tasks->horizontalHeader();

    hw->moveSection(6, 0);
    hw->moveSection(7, 1);
    hw->moveSection(7, 4);

    hw->setSortIndicator(6, Qt::AscendingOrder);
}