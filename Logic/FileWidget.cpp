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
 * 
 */


#include "iostream"
#include "../Forms/MainForm.h"
#include <QCoreApplication>
#include <QMouseEvent>
#include <QDesktopServices>
#include <QLayout>
#include <QApplication>
#include <QPoint>
#include <QRegion>
#include <QDrag>

#include "QUrl"
#include "FileLabel.h"
#include "ContextMenu.h"
#include "FileWidget.h"
#include "FileTitle.h"
#include "FileFrameWidget.h"


FileWidget::FileWidget(const QFileInfo& inFileInfo, const QWidget* mainWidget,
                       size_t inId, QWidget* parent, Qt::WindowFlags f, QString inFileName):
fileInfo(inFileInfo), id(inId), mainWidget(mainWidget), QFrame(parent, f), fileName(inFileName)
{
    //TODO: clear it
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::transparent);
    setAutoFillBackground(true);
    setPalette(Pal);
}

FileWidget::~FileWidget()
{
    const MainForm* mainForm = static_cast<const MainForm*>(mainWidget);
    const_cast<MainForm*>(mainForm)->DiselectItem(fileName, this);
}


void FileWidget::SetParts(QLabel* labelImage, QTextEdit* labeltitle)
{
    this->labelImage = labelImage;
    this->labeltitle = labeltitle;
}


void FileWidget::SetFileSystemCalls(SystemCalls* systemcalls)
{
    this->systemcalls = systemcalls;
}


void FileWidget::SetSelection(bool ignoreOthers)
{
    const MainForm* mainForm =  static_cast<const MainForm*>(mainWidget);
    if( nullptr != mainForm )
    {
        if( QApplication::keyboardModifiers().testFlag(Qt::ControlModifier) && 
            const_cast<MainForm*> (mainForm)->IsSelected(fileName) )
        {
            ResetSelection();
        }
        else if( !selected )
        {
            selected = true;
            const_cast<MainForm*> (mainForm)->SetItemSelected( fileName, this, ignoreOthers );
            SetSelectionColor();
        }
    }
}


void FileWidget::SetSelectionColor()
{
    if( selectedColorActive )
    {
        return ;
    }

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::lightGray);


    if( nullptr != labeltitle )
    {
        labeltitle->setAutoFillBackground(true);
        labeltitle->setPalette(Pal);
    }

    if( nullptr != labelImage )
    {
        static_cast<FileLabel*>(labelImage)->SetSelection(true);
    }
    selectedColorActive = true;
}

void FileWidget::ResetSelection(bool resetFromForm)
{
    selected = false;
    if( (nullptr != mainWidget) && (resetFromForm) )
    {
        const MainForm* mainForm =  static_cast<const MainForm*>(mainWidget);
        const_cast<MainForm*> (mainForm)->DiselectItem(fileName, this);
    }

    ResetSelectionColor();
}


void FileWidget::ResetSelectionColor()
{
    selectedColorActive = false;
    if( nullptr != labeltitle )
    {
        labeltitle->setAutoFillBackground(false);
    }
    if( nullptr != labelImage )
    {
        static_cast<FileLabel*>(labelImage)->SetSelection(false);
    }
}



void FileWidget::mousePressButtonEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        if( nullptr != labeltitle )
        {
            SetSelection();
        }
    }
}


void FileWidget::mouseMoveButtonEvent(QMouseEvent* event)
{
    if(!dragActive)
    {
        dragActive = true;
        if( nullptr  != parent() )
        {
            this->rect();
            QPixmap localPixmap(this->size()); 
            localPixmap.fill(Qt::transparent);
            this->render(&localPixmap, QPoint(0, 0), QRegion(this->rect()));
            static_cast<FileFrameWidget*>(parent())->StartDrag(event, localPixmap, this);
        }
        dragActive = false;
    }
}



void FileWidget::mouseReleaseButtonEvent(QMouseEvent* event)
{
    //TODO: implementation
}

void FileWidget::mouseDoubleClickButtonEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        if( nullptr != systemcalls )
        {
            if( fileInfo.isDir() )
            {
                systemcalls->SetCurrentDirectory( fileInfo.absoluteFilePath(), true );
                UpdateForm();
            }
            else if( fileInfo.isFile() )
            {
                QUrl qurl( fileInfo.filePath().toStdString().c_str() );
                QDesktopServices::openUrl( qurl );
            }
        }
    }
}


void FileWidget::contextMenuButtonEvent(QContextMenuEvent* event)
{
    SetSelection();
    ContextMenu contextmenu(ContextMenu::eFileMenu, nullptr, systemcalls);
    contextmenu.InitMenu( labeltitle );
    contextmenu.setGeometry( QRect(QPoint(event->globalX(), event->globalY()),//TODO: check this
                             QPoint(event->globalX() - globalXCorrection, event->globalY() - globalYCorrection)) );
    contextmenu.exec();
}


static int iteratorTest = 0;

void FileWidget::mouseDragEvent(QDragMoveEvent* event)
{
     std::cout<<"FileWidget::mouseDragEvent:"<<iteratorTest<<std::endl;
     iteratorTest++;
}



void FileWidget::SetTextLineHeight(int inTextLineHeight)
{
    textLineHeight = inTextLineHeight;
}


QTextEdit * FileWidget::GetTitle()
{
    return labeltitle;
}


void FileWidget::UpdateForm(bool forceUpdate)
{
    if( nullptr != mainWidget )
    {
        const MainForm* mainForm =  static_cast<const MainForm*>(mainWidget);
        const_cast<MainForm*>(mainForm)->NotifyUpdate();
    }
}

void FileWidget::RenameFileInInternalRepresentation(QString oldName, QString newName)
{
    systemcalls->RenameDirectory( oldName, newName );
    UpdateForm();
}


bool FileWidget::IsDirectory()
{
    return fileInfo.isDir();
}


#include "FileWidget.moc"
