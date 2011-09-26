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
#include <QSettings>
#include <QDesktopWidget>
#include <QTimer>

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
    sti(0),
    trayIconMenu(0),
    timer(0),
    saveNeeded(false),
    startVisible(true),
    hideToSystemTray(false)
{
    ui->setupUi(this);

    // disable close icon on window
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);

    readSettings();

    sti = new QSystemTrayIcon(this);
    trayIconMenu = new QMenu(this);
    initSystray();

    ui->actionSave->setEnabled(false);

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

    ui->actionPurge->setIcon(style()->standardIcon(QStyle::SP_TrashIcon));

    // center on screen
    center();

    // enable autosave every 5 minutes
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(saveData()));
    timer->start(1000 * 60 * 5);
}

MainWindow::~MainWindow()
{
    delete ui;

    delete uData; uData = 0;
    delete model_groups; model_groups = 0;
    delete model_locations; model_locations = 0;
    delete model_tasks; model_tasks = 0;
    delete sortFilterTasksProxy; sortFilterTasksProxy = 0;
    delete groupDelegate; groupDelegate = 0;
    delete locationDelegate; locationDelegate = 0;
    delete doneColorDelegate; doneColorDelegate = 0;
    delete sortFilterTasksProxy; sortFilterTasksProxy = 0;
    delete dueDate_delegate; dueDate_delegate = 0;
    delete titleDelegate; titleDelegate = 0;
    delete descriptionDelegate; descriptionDelegate = 0;
    delete sti; sti = 0;
    delete trayIconMenu; trayIconMenu = 0;
    delete timer; timer = 0;
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
    connect(ui->table_tasks, SIGNAL(clickedOutsideData()), this, SLOT(deselectAllRows()));
    connect(ui->table_tasks, SIGNAL(clickedOutsideData()), ui->lineEdit_titleDisplay, SLOT(clear()));
    connect(ui->table_tasks, SIGNAL(clickedOutsideData()), ui->lineEdit_groupDisplay, SLOT(clear()));
    connect(ui->table_tasks, SIGNAL(clickedOutsideData()), ui->lineEdit_locationDisplay, SLOT(clear()));
    connect(ui->table_tasks, SIGNAL(clickedOutsideData()), ui->plainTextEdit_descriptionDisplay, SLOT(clear()));
    connect(ui->table_tasks, SIGNAL(clickedOutsideData()), ui->dateTimeEdit_duedateDisplay, SLOT(clear()));

    ui->table_tasks->setModel(sortFilterTasksProxy);

    ui->table_tasks->setItemDelegateForColumn(0, locationDelegate);
    ui->table_tasks->setItemDelegateForColumn(1, groupDelegate);
    ui->table_tasks->setItemDelegateForColumn(2, doneColorDelegate);
    ui->table_tasks->setItemDelegateForColumn(5, dueDate_delegate);
    ui->table_tasks->setItemDelegateForColumn(6, titleDelegate);
    ui->table_tasks->setItemDelegateForColumn(7, descriptionDelegate);

    connect(ui->table_tasks, SIGNAL(clicked(QModelIndex)), this, SLOT(taskRowClicked(QModelIndex)));

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

        ui->actionSave->setEnabled(false);
    }
}

void MainWindow::groupData_changed()
{
    saveNeeded = true;

    ui->actionSave->setEnabled(true);

    uData->groups() = model_groups->stringList();
}

void MainWindow::locationData_changed()
{
    saveNeeded = true;

    ui->actionSave->setEnabled(true);

    uData->locations() = model_locations->stringList();
}

void MainWindow::taskData_changed(QModelIndex index)
{
    Q_UNUSED(index);

    saveNeeded = true;

    ui->actionSave->setEnabled(true);

    uData->tasks() = model_tasks->getTasks();

    updateStatusMesg();

    int currentlySelectedRow = ui->table_tasks->currentIndex().row();

    if(currentlySelectedRow != -1)
    {
        taskRowClicked(ui->table_tasks->currentIndex());
    }
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
    hw->moveSection(5, 0);

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

        if(ret == QMessageBox::Cancel)
        {
            event->ignore();
            return true;
        }

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
    if(isVisible())
    {
        if(!isActiveWindow())
        {
            show();
            raise();
            activateWindow();

            ui->tabWidget->setCurrentIndex(0);
            ui->lineEdit_quickTitle->setFocus();
        }
        else
        {
            setVisible(false);
        }
    }
    else
    {
        setVisible(true);

        show();
        raise();
        activateWindow();

        ui->tabWidget->setCurrentIndex(0);
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

void MainWindow::initSystray()
{
    sti->setIcon(QIcon(":/icons/res/app.svg"));

    trayIconMenu->addAction(tr("Add task"), this, SLOT(trayIcon_addTask_clicked()));
    trayIconMenu->addAction(tr("View/manage tasks"), this, SLOT(trayIcon_manageTasks_clicked()));

    trayIconMenu->addSeparator();

    QAction *actStartVisibility = new QAction(this);
    actStartVisibility->setText(tr("Start visible"));
    actStartVisibility->setCheckable(true);
    actStartVisibility->setChecked(startVisible);
    connect(actStartVisibility, SIGNAL(triggered(bool)), this, SLOT(setStartVisible(bool)));
    trayIconMenu->addAction(actStartVisibility);

    QAction *actHideToSysTray = new QAction(this);
    actHideToSysTray->setText(tr("Hide to system tray"));
    actHideToSysTray->setCheckable(true);
    actHideToSysTray->setChecked(hideToSystemTray);
    connect(actHideToSysTray, SIGNAL(triggered(bool)), this, SLOT(setHideToSystemTray(bool)));
    trayIconMenu->addAction(actHideToSysTray);

    connect(sti, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(sysTrayIconClicked(QSystemTrayIcon::ActivationReason)));

    sti->setContextMenu(trayIconMenu);

    sti->show();
}

void MainWindow::trayIcon_addTask_clicked()
{
    if(!isVisible())
    {
        setVisible(true);

        show();
        raise();
        activateWindow();
    }

    if(!isActiveWindow())
    {
        activateWindow();
    }

    ui->tabWidget->setCurrentIndex(0);
    ui->lineEdit_quickTitle->setFocus();
}

void MainWindow::trayIcon_manageTasks_clicked()
{
    if(!isVisible())
    {
        setVisible(true);

        show();
        raise();
        activateWindow();
    }

    if(!isActiveWindow())
    {
        activateWindow();
    }

    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::setStartVisible(bool visibleOnStart)
{
    startVisible = visibleOnStart;

    writeSettings();
}

void MainWindow::readSettings()
{
    QSettings settings("JustDoIt", "JustDoIt");

    settings.beginGroup("MainWindow");
    startVisible = settings.value("isVisibleOnStart").toBool();
    hideToSystemTray = settings.value("hideToSystemTray").toBool();
    settings.endGroup();
}

void MainWindow::writeSettings()
{
    QSettings settings("JustDoIt", "JustDoIt");

    settings.beginGroup("MainWindow");
    settings.setValue("isVisibleOnStart", startVisible);
    settings.setValue("hideToSystemTray", hideToSystemTray);
    settings.endGroup();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();
}

void MainWindow::hideEvent(QHideEvent *event)
{
    if(hideToSystemTray)
    {
        setVisible(false);
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::setHideToSystemTray(bool hideToSysTray)
{
    hideToSystemTray = hideToSysTray;

    writeSettings();
}

void MainWindow::sysTrayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::Trigger)
    {
        if(!isActiveWindow())
        {
            trayIcon_addTask_clicked();
        }
        else
        {
            hide();
        }
    }
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}

void MainWindow::purgeAllDoneTasks()
{
    if(uData)
    {
        int numDeleted = 0;

        const QVector<Task*> &allTasks = uData->tasks();
        QVector<int> indicesOfTasksToBeDeleted;

        int numOfTasks = allTasks.size();

        for(int i=0; i<numOfTasks; ++i)
        {
            if(allTasks.at(i)->done())
            {
                indicesOfTasksToBeDeleted.append(i);
            }
        }

        int numOfDoneTasks = indicesOfTasksToBeDeleted.size();

        if(!numOfDoneTasks)
        {
            return;
        }

        if(QMessageBox::question(this, "Confirm", "Are you sure that you want to delete all completed tasks?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
        {
            return;
        }

        for(int i=0; i<numOfDoneTasks; ++i)
        {
            // the ascending order of indices here is crucial!!
            QModelIndex index = model_tasks->index(indicesOfTasksToBeDeleted[i] - numDeleted, 0);

            if(index.isValid())
            {
                model_tasks->removeRows(index.row(), 1);

                emit taskData_changed(index);
            }

            ++numDeleted;
        }
    }
}

void MainWindow::on_actionPurge_triggered()
{
    purgeAllDoneTasks();
}

void MainWindow::taskRowClicked(QModelIndex index)
{
    int row = index.row();

    QModelIndex index_title = sortFilterTasksProxy->index(row, 6);
    QModelIndex index_description = sortFilterTasksProxy->index(row, 7);
    QModelIndex index_group = sortFilterTasksProxy->index(row, 1);
    QModelIndex index_location = sortFilterTasksProxy->index(row, 0);
    QModelIndex index_done = sortFilterTasksProxy->index(row, 2);

    QString title = sortFilterTasksProxy->data(index_title, Qt::DisplayRole).toString();
    QString description = sortFilterTasksProxy->data(index_description, Qt::DisplayRole).toString();
    QString group = sortFilterTasksProxy->data(index_group, Qt::DisplayRole).toString();
    QString location = sortFilterTasksProxy->data(index_location, Qt::DisplayRole).toString();
    bool done = sortFilterTasksProxy->data(index_done, Qt::CheckStateRole).toBool();

    ui->lineEdit_titleDisplay->setText(title);
    ui->lineEdit_groupDisplay->setText(group);
    ui->lineEdit_locationDisplay->setText(location);
    ui->plainTextEdit_descriptionDisplay->document()->setPlainText(description);

    if(done)
    {
        QModelIndex index_finishDate = model_tasks->index(row, 5);

        QDateTime finishDate = model_tasks->data(index_finishDate, Qt::DisplayRole).toDateTime();

        ui->dateTimeEdit_duedateDisplay->setDateTime(finishDate);
        ui->label_dueDateDisplay->setText(tr("Finished on"));
    }
    else
    {
        QModelIndex index_dueDate = model_tasks->index(row, 6);

        QDateTime dueDate = model_tasks->data(index_dueDate, Qt::DisplayRole).toDateTime();

        ui->dateTimeEdit_duedateDisplay->setDateTime(dueDate);
        ui->label_dueDateDisplay->setText(tr("Due on"));
    }
}

void MainWindow::deselectAllRows()
{
    ui->table_tasks->clearSelection();

    ui->label_dueDateDisplay->setText(tr("Due date"));
}

void MainWindow::center()
{
    QDesktopWidget *desktop = QApplication::desktop();

    int screenWidth, width;
    int screenHeight, height;
    int x, y;
    QSize windowSize;

    screenWidth = desktop->width();
    screenHeight = desktop->height();

    windowSize = size();
    width = windowSize.width();
    height = windowSize.height();

    x = (screenWidth - width) / 2;
    y = (screenHeight - height) / 2;

    move (x, y);
}
