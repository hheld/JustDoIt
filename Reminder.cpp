#include "Reminder.h"
#include "ui_Reminder.h"

#include "TaskTableModel.h"

Reminder::Reminder(TaskTableModel *model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Reminder),
    model(model)
{
    ui->setupUi(this);

    ui->tableView->setModel(model);
}

Reminder::~Reminder()
{
    delete ui;
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
