#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QModelIndex>

class UserData;
class QStringListModel;

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

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

    UserData *uData;

    QStringListModel *model_realms;
    QStringListModel *model_locations;

    QString saveFileName;

public slots:
    void saveXML(const QString &fileName = QString());

private slots:
    void on_button_save_clicked();
    void realmData_changed();
    void locationData_changed();
    void on_button_addRealm_clicked();
    void on_button_insertRealm_clicked();
    void on_button_deleteRealm_clicked();
};

#endif // MAINWINDOW_H
