/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "setup.h"
#include "treemodel.h"
#include "treeitem.h"

#include <QApplication>
#include <QFile>
#include <QTreeView>
#include <QtSql>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQuickView>
#include <QtQml>
#include <QQmlContext>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQuickView>
#include <QtQml>
#include <QQmlContext>
#include <QSqlQuery>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("");
    db.setDatabaseName("");
    db.setPort();
    db.setUserName("");
    db.setPassword("");
    bool ok = db.open();
    qDebug() << "db.open?: " << ok;

    // Container class to avoid startup code in main.cpp
    Setup *setup = new Setup();

    // Start a QML viewer (seperate UI window) as well
    QQuickView *viewer = new QQuickView();
    QQmlContext *context = viewer->rootContext();
    viewer->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    viewer->setTitle("QtQuick/QML UI");
    viewer->show();

    // Instantiate a TreeItem and TreeModel. But, can't we get TreeModel from Setup? ... [TreeModel *treeModel = setup->treeModel2;]
    QList<QVariant> rootData;
    rootData << "Title" << "Summary"; // required?!
    TreeItem *root1 = new TreeItem(rootData);
    TreeModel *treeModel = new TreeModel(root1, QString());

    // Make the instance available to QML/QtQuick
    viewer->rootContext()->setContextProperty("tModel", treeModel);

    // Start the app
    return app.exec();
}
