#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QModelIndex>

class UserData;
class QStringListModel;
class TaskTableModel;
class TaskTableStringListComboboxDelegate;
class TaskTableColorDoneDelegate;
class TaskSortFilterProxyModel;
class TaskTableDateTimeDelegate;
class TaskTableLineEditDelegate;
class TaskTableTextEditDelegate;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setUsrData(UserData *uData);
    void setSaveFileName(const QString &xmlOutFileName);

    bool event(QEvent *event);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

    UserData *uData;

    QStringListModel *model_groups;
    QStringListModel *model_locations;
    TaskTableModel *model_tasks;
    TaskTableStringListComboboxDelegate *groupDelegate;
    TaskTableStringListComboboxDelegate *locationDelegate;
    TaskTableColorDoneDelegate *doneColorDelegate;
    TaskSortFilterProxyModel *sortFilterTasksProxy;
    TaskTableDateTimeDelegate *dueDate_delegate;
    TaskTableLineEditDelegate *titleDelegate;
    TaskTableTextEditDelegate *descriptionDelegate;

    QString saveFileName;

    void permuteColumns();
    int numOfUnfinishedTasks() const;

    bool saveNeeded;

public slots:
    void saveXML(const QString &fileName = QString());
    void updateStatusMesg();
    void toggleVisibility();
    void updateDefaultDueDateTime();

private slots:
    void saveData();
    void groupData_changed();
    void locationData_changed();
    void taskData_changed(QModelIndex index);
    void on_button_addGroup_clicked();
    void on_button_insertGroup_clicked();
    void on_button_deleteGroup_clicked();
    void on_button_addLocation_clicked();
    void on_button_insertLocation_clicked();
    void on_button_deleteLocation_clicked();
    void on_button_addTask_clicked();
    void on_button_deleteTask_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_button_add_clicked();
    void on_button_clear_clicked();
};

#endif // MAINWINDOW_H
