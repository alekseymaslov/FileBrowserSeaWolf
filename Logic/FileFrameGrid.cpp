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

#include "FileFrameGrid.h"
#include <QApplication>
#include "ContextMenu.h"
#include "MainForm.h"



void FileFrameGrid::SetSystemsCall(SystemCalls* inSystemcalls)
{
    this->systemcalls = systemcalls;
}

void FileFrameGrid::mousePressEvent(QMouseEvent* event)
{
    if((nullptr != event) && (event->button() == Qt::RightButton))
    {
        QWidget* mainForm = const_cast<QWidget*>(mainFormWidget);
        ContextMenu contextmenu(ContextMenu::eFormMenu, nullptr, systemcalls);
        contextmenu.InitMenu(mainForm);
        //TODO: correction mouse center by icons size
        contextmenu.setGeometry( QRect(QPoint(event->globalX(), event->globalY()),
                                 QPoint(event->globalX() /*- 80*/, event->globalY() /*- 100*/)) );
        contextmenu.exec();
    }
    else if(!QApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
    {
        const MainForm* mainForm =  static_cast<const MainForm*>(mainFormWidget);
        if( nullptr != mainForm )
        {
            const_cast<MainForm*> (mainForm)->ResetSelection();
        }
    }
}
