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

#include <QtGui/QApplication>
#include <QDir>
#include <QProcessEnvironment>
#include <QSettings>

// #include <QxtGlobalShortcut>

#include "MainWindow.h"
#include "TaskXmlReader.h"
#include "UserData.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //------------------------------------------------

    QDir homeDir = QDir::homePath();

    if(!homeDir.exists(".justdoit"))
    {
        homeDir.mkdir(".justdoit");
    }

    QDir savePath = homeDir.absolutePath() + "/.justdoit";

    TaskXmlReader myReader(savePath.absolutePath() + "/tasks.xml");

    UserData *myUd = 0;

    if(savePath.exists("tasks.xml"))
    {
        myReader.readDocument();
        myUd = myReader.uData();
    }
    else
    {
        myUd = new UserData(QProcessEnvironment::systemEnvironment().value("USER"));
    }

    //------------------------------------------------

    MainWindow w;

    QSettings settings("JustDoIt", "JustDoIt");

    settings.beginGroup("MainWindow");
    bool startVisible = settings.value("isVisibleOnStart").toBool();
    settings.endGroup();

//    QxtGlobalShortcut* shortcut = new QxtGlobalShortcut(&w);
//    QObject::connect(shortcut, SIGNAL(activated()), &w, SLOT(toggleVisibility()));
//    shortcut->setShortcut(QKeySequence("Ctrl+Shift+F11"));

    w.setUsrData(myUd);
    w.setSaveFileName(savePath.absolutePath() + "/tasks.xml");

    if(startVisible)
    {
        w.show();
    }

    return a.exec();
}
