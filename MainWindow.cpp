#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "UserData.h"
#include "TaskXmlWriter.h"

#include <QStringListModel>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    uData(0),
    model_realms(0),
    model_locations(0)
{
    ui->setupUi(this);

    model_realms = new QStringListModel(this);
    model_locations = new QStringListModel(this);

    ui->listView_realms->setModel(model_realms);
    ui->listView_locations->setModel(model_locations);

    connect(model_realms, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(realmData_changed()));
    connect(model_locations, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(locationData_changed()));
}

MainWindow::~MainWindow()
{
    delete ui;

    delete uData; uData = 0;
    delete model_realms; model_realms = 0;
    delete model_locations; model_locations = 0;
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
}

void MainWindow::saveXML(const QString &fileName)
{
    TaskXmlWriter myWriter(fileName);

    myWriter.uData(uData);

    myWriter.writeDocument();
}

void MainWindow::on_button_save_clicked()
{
    saveXML("mySavedFile.xml");
}

void MainWindow::realmData_changed()
{
    uData->realms() = model_realms->stringList();
}

void MainWindow::locationData_changed()
{
    uData->locations() = model_locations->stringList();
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
