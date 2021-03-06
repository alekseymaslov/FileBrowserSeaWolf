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

#include "FileLabel.h"
#include "FileWidget.h"
#include <QLineEdit>
#include <QCursor>
#include <QDrag>
#include <QMimeData>

#include <iostream>


void FileLabel::SetSelection(bool select)
{
    if(select)
    {
        const QPixmap* currentPixmap = pixmap();
        QIcon iconClear(*currentPixmap);
        setPixmap( iconClear.pixmap(iconSize, QIcon::Selected) );
    }
    else
    {
        setPixmap( storedIcon.pixmap(iconSize) );
    }
}


void FileLabel::mousePressEvent(QMouseEvent* event)
{
    if(nullptr != parent())
    {
        FileWidget* parentWidget = static_cast<FileWidget*>(parent());
        parentWidget->mousePressButtonEvent(event);
    }
}


void FileLabel::mouseMoveEvent(QMouseEvent* event)
{
    std::cout<<"FileLabel::mouseMoveEvent"<<std::endl;
    if( nullptr != parent() )
    {
        FileWidget* parentWidget = static_cast<FileWidget*>(parent());
        parentWidget->mouseMoveButtonEvent(event);
    }
}


void FileLabel::mouseReleaseEvent(QMouseEvent* event)
{
    if( nullptr != parent() )
    {
        FileWidget* parentWidget = static_cast<FileWidget*>(parent());
        parentWidget->mouseReleaseButtonEvent(event);
    }
}


void FileLabel::mouseDoubleClickEvent(QMouseEvent* event)
{
    if((event->button() == Qt::LeftButton) && (nullptr != parent()))
    {
        FileWidget* parentWidget = static_cast<FileWidget*>(parent());
        parentWidget->mouseDoubleClickButtonEvent(event);
    }
}


void FileLabel::contextMenuEvent(QContextMenuEvent* event)
{
    if(nullptr != parent())
    {
        FileWidget* parentWidget = static_cast<FileWidget*>(parent());
        parentWidget->contextMenuButtonEvent(event);
    }
}
