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

#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QMenu>
#include <QAction>
#include <QWidget>
#include "SystemCalls.h"

class ContextMenu : public QMenu
{
    Q_OBJECT

    SystemCalls* systemcalls = nullptr;
    QWidget* widgetToOperate = nullptr;
public:
    enum menuType
    {
        eFormMenu,
        eFileMenu,
        eNewFileMenu,
    };

    ContextMenu( menuType inType, QMenu* parent = nullptr, SystemCalls* inSystemCalls = nullptr ) :
    _menuType(inType), QMenu(parent), systemcalls(inSystemCalls) {}

    virtual ~ContextMenu();

    void InitMenu( QWidget* inWidgetToOperate = nullptr );

private:
    menuType _menuType;

    void createFormMenu();
    void createFileMenu();
    void createNewFileMenu();

    QAction *renameAction = nullptr;
    QAction *newFolderAction = nullptr;
    QAction *deleteAction = nullptr;
    QAction *propertyActionFile = nullptr;
    QAction *propertyActionForm = nullptr;
private slots:
    void newFolder();
    void renameFile();
    void deleteFile();
    void fileProperties();
};

#endif // CONTEXTMENU_H
