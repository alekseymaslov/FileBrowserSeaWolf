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

#include "FileTitle.h"
#include "FileWidget.h"
#include <QMouseEvent>
#include <iostream>
#include <exception>



void FileTitle::Rename()
{
    originalName = this->toPlainText();
    setReadOnly(false);
    selectAll();
}


void FileTitle::AdjusParentsSize()
{
    //TODO: implementation
}



void FileTitle::mousePressEvent(QMouseEvent* event)
{
    if( nullptr != parent() )
    {
        FileWidget* parentWidget = static_cast<FileWidget*>(parent());
        parentWidget->mousePressButtonEvent(event);
    }
}


void FileTitle::mouseMoveEvent(QMouseEvent* event)
{
    if( nullptr != parent() )
    {
        FileWidget* parentWidget = static_cast<FileWidget*>(parent());
        parentWidget->mouseMoveButtonEvent(event);
    }
}


void FileTitle::mouseReleaseEvent(QMouseEvent* event)
{
    if( nullptr != parent() )
    {
        FileWidget* parentWidget = static_cast<FileWidget*>(parent());
        parentWidget->mouseReleaseButtonEvent(event);
    }
}


void FileTitle::mouseDoubleClickEvent(QMouseEvent* event)
{
    if(nullptr != parent())
    {
        FileWidget* parentWidget = static_cast<FileWidget*>(parent());
        parentWidget->mouseDoubleClickButtonEvent(event);
    }
}

void FileTitle::contextMenuEvent(QContextMenuEvent* event)
{
    if(nullptr != parent())
    {
        FileWidget* parentWidget = static_cast<FileWidget*>(parent());
        parentWidget->contextMenuButtonEvent(event);
    }
}


void FileTitle::focusOutEvent(QFocusEvent* event)
{
    if( (originalName != QString("")) && (nullptr != parent()) )
    {
        QString currentName = this->toPlainText();
        if(originalName != currentName)
        {
            std::cout<<"title was renamed"<<std::endl;
            AdjusParentsSize();
            FileWidget* parentWidget = static_cast<FileWidget*>(parent());
            parentWidget->RenameFileInInternalRepresentation( originalName, currentName );
        }
    }
    setReadOnly(true);
}

