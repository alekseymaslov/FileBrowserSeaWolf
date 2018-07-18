/*
 * Copyright 2017 <copyright holder> <email>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MAINFORMTREEVIEW_H
#define MAINFORMTREEVIEW_H

#include <QTreeWidget>
#include <QObject>
#include <QWidget>

#include "SystemCalls.h"

class MainFormTreeView : public QObject
{
    Q_OBJECT

    QMap<QString, QString> mainTreeMap;
    QTreeWidget* mainTreeWidget = nullptr;
    SystemCalls* systemcalls = nullptr;
    QString changedDirectory = "";
    QWidget* mainForm = nullptr;

public:
    MainFormTreeView(){}
    ~MainFormTreeView(){}

    void Init( SystemCalls* inSystemCalls, QTreeWidget* inTreeWidget, QWidget* inMainForm );

    void Update();
private slots:
    void handleUserSelectionMainTree( QTreeWidgetItem * item, int column );
private:
    void UpdateTreeView();
};

#endif // MAINFORMTREEVIEW_H
