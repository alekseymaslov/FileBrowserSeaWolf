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


#include "MainFormTreeView.h"
#include <QMap>
#include <QList>

#include <iostream>
#include <exception>

#include "../Forms/MainForm.h"


void MainFormTreeView::Init( SystemCalls* inSystemCalls, QTreeWidget* inTreeWidget, QWidget* inMainForm )
{
    size_t level = 0;
    if( (nullptr == inSystemCalls) && (nullptr == inTreeWidget) && (nullptr != inMainForm) )
    {
        throw std::invalid_argument("MainFormTreeView::Init");
    }

    systemcalls = inSystemCalls;
    mainTreeWidget = inTreeWidget;
    mainForm = inMainForm;

    mainTreeWidget->setColumnCount(1);
    QFont font;
    font.setPixelSize(20);//TODO: to const
    mainTreeWidget->setFont(font);
    QTreeWidgetItem* recent = new QTreeWidgetItem((QTreeWidget*)nullptr, QStringList(QString("Recent")));//TODO: to dictionary
    mainTreeWidget->insertTopLevelItem(0, recent);
    level++;

    systemcalls->GetTreePaths(mainTreeMap);

    auto i = mainTreeMap.constBegin();
    while (i != mainTreeMap.constEnd()) 
    {
        QTreeWidgetItem* current = new QTreeWidgetItem((QTreeWidget*)nullptr, QStringList(i.key()));
        connect(mainTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this,
                SLOT(handleUserSelectionMainTree(QTreeWidgetItem*, int)));
        mainTreeWidget->insertTopLevelItem(level, current);
        level++;
        ++i;
    }
}


void MainFormTreeView::Update()
{
    if( nullptr != systemcalls )
    {
        QString currentFolder = systemcalls->GetCurrentDirectory();
        if( changedDirectory != currentFolder )
        {
            changedDirectory = currentFolder;
            UpdateTreeView();
        }
    }
}


void MainFormTreeView::handleUserSelectionMainTree( QTreeWidgetItem * item, int column )
{
    QString name = item->text(column);
    QString path = mainTreeMap[name];
    if( changedDirectory != path )
    {
        bool changet = systemcalls->SetCurrentDirectory( path, true );
        if( changet )
        {
            changedDirectory = path;
        }
    }

    static_cast<MainForm*>(mainForm)->NotifyUpdate();
}


void MainFormTreeView::UpdateTreeView()
{
    mainTreeWidget->clearSelection();
    auto i = mainTreeMap.constBegin();
    while (i != mainTreeMap.constEnd()) 
    {
        QString currentKey = i.key();
        QString currentValue = i.value();
        if(changedDirectory == currentValue)
        {
            QList<QTreeWidgetItem*> items = mainTreeWidget->findItems(i.key(), Qt::MatchExactly);
            if( 0 != items.count())
            {
                const QTreeWidgetItem* item = *(items.begin());
                mainTreeWidget->setItemSelected(item, true);
            }
        }
        ++i;
    }
}


#include "MainFormTreeView.moc"
