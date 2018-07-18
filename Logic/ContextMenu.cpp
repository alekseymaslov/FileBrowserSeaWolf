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

#include <iostream>
#include <exception>

#include "ContextMenu.h"
#include "FileLabel.h"
#include "FileTitle.h"
#include "FileWidget.h"
#include "PropertiesDialogue.h"
#include "MainForm.h"

//TODO: Create dictionaty

ContextMenu::~ContextMenu()
{
    delete(renameAction);
    delete(newFolderAction);
}



void ContextMenu::createFormMenu()
{
    //TODO: add label of menu to dictionaty
    this->setTitle(tr("Windows menu"));
    this->addMenu(tr("View"));
    this->addMenu(tr("Sort by"));
    this->addAction(tr("Select All"));

    ContextMenu* newFormMenu = new ContextMenu(eNewFileMenu, this, systemcalls);
    newFormMenu->InitMenu(widgetToOperate);
    this->addMenu(newFormMenu);
    this->addAction("Refresh");

    propertyActionForm = new QAction(tr("Properties"), this);
    propertyActionForm->setStatusTip(tr("Properties of the current folder"));
    connect(propertyActionForm, SIGNAL(triggered()), this, SLOT(fileProperties()));

    this->addAction(propertyActionForm);
}


void ContextMenu::createFileMenu()
{
    //TODO: add label of menu to dictionaty
    this->setTitle(tr("File menu"));

    renameAction = new QAction(tr("Raname"), this);
    renameAction->setStatusTip(tr("Give a new name"));
    connect(renameAction, SIGNAL(triggered()), this, SLOT(renameFile()));

    this->addAction(renameAction);

    deleteAction = new QAction(tr("Delete"), this);
    deleteAction->setStatusTip(tr("Delete file"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteFile()));

    this->addAction(deleteAction);

    propertyActionFile = new QAction(tr("Properties"), this);
    propertyActionFile->setStatusTip(tr("Properties of the file"));
    connect(propertyActionFile, SIGNAL(triggered()), this, SLOT(fileProperties()));

    this->addAction(propertyActionFile);
}


void ContextMenu::createNewFileMenu()
{
    //TODO: add label of menu to dictionaty
    this->setTitle(tr("New"));
    newFolderAction = new QAction(tr("Folder"), this);
    newFolderAction->setStatusTip(tr("Create a new folder in current directory"));
    connect(newFolderAction, SIGNAL(triggered()), this, SLOT(newFolder()));
    this->addAction(newFolderAction);
    this->addAction("Text document");
}


void ContextMenu::InitMenu( QWidget* inWidgetToOperate )
{
    widgetToOperate = inWidgetToOperate;
    switch(_menuType)
    {
        case eFormMenu:
            createFormMenu();
            break;
        case eFileMenu:
            createFileMenu();
            break;
        case eNewFileMenu:
            createNewFileMenu();
        break;
        default:
            //TODO: throw exception
            break;
    }
}


void ContextMenu::newFolder()
{
    //TODO: add label of menu to dictionaty
    QString defaultFolderName = "New folder";
    bool creationResult = false;
    if( nullptr != systemcalls )
    {
        creationResult = systemcalls->CreateDirectory( defaultFolderName );
    }

    MainForm* mainForm = static_cast<MainForm*>( widgetToOperate );
    mainForm->UpdateDirectoriesView(true);
    QWidget* createdDirectory = mainForm->GetChildByName( defaultFolderName );
    if( nullptr != createdDirectory )
    {
        FileWidget* newFolderWidget = static_cast<FileWidget*>( createdDirectory );
        newFolderWidget->SetSelection();
        widgetToOperate = newFolderWidget->GetTitle();
        renameFile();
    }

    std::cout<<"newFolder():" << creationResult <<std::endl;
}


void ContextMenu::renameFile()
{
    if( nullptr != widgetToOperate )
    {
        FileTitle* title = static_cast<FileTitle*>( widgetToOperate );
        title->Rename();
    }
}


void ContextMenu::deleteFile()
{
    if( (nullptr == widgetToOperate) || (nullptr == systemcalls) )
    {
        throw std::invalid_argument("ContextMenu::deleteFile: no file to delete or systemcalls is invalid");
    }

    FileTitle* title = static_cast<FileTitle*>( widgetToOperate );
    QString name = title->toPlainText();
    if( !systemcalls->DeleteFolderOrFile( name ) )
    {
        std::cout<<"file was not deleted" <<std::endl;
    }
    else
    {
        FileWidget* file = static_cast<FileWidget*>( title->parent() );
        file->UpdateForm();
    }
}


void ContextMenu::fileProperties()
{
    if( (nullptr == widgetToOperate) || (nullptr == systemcalls) )
    {
        throw std::invalid_argument("ContextMenu::fileProperties: no file to delete or systemcalls is invalid");
    }
#if DEBUG
    std::cout<<"ContextMenu::fileProperties" <<std::endl;
#endif

    QString name = "";
    if( eFileMenu == _menuType )
    {
        FileTitle* title = static_cast<FileTitle*>( widgetToOperate );
        name = title->toPlainText();
    }
    else
    {
        name = systemcalls->GetCurrentFolderName();
    }
    auto fileInfo = systemcalls->GetFileInfo( name );
    PropertiesDialogue* propDialogue = new PropertiesDialogue( systemcalls, name, this );
    propDialogue->show();
    propDialogue->setModal(false);
    propDialogue->FillWindows();
    propDialogue->exec();
}



#include "ContextMenu.moc"
