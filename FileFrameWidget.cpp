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

#include "FileFrameWidget.h"
#include "MainForm.h"
#include <QMouseEvent>
#include <QLabel>
#include <QLayout>
#include <QMenu>
#include <QPoint>
#include <QApplication>

#include <iostream>

#include "ContextMenu.h"
#include "FileWidget.h"
#include "FileLabel.h"
#include "FileTitle.h"



void FileFrameWidget::SetSystemsCall( SystemCalls* systemcalls )
{
    //TODO: check on nullptr and if error throw exeption
    this->systemcalls = systemcalls;
}


void FileFrameWidget::mousePressEvent(QMouseEvent* event)
{
    std::cout<<"FileFrameWidget::mousePressEvent"<<std::endl;

    if(!QApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
    {
        const MainForm* mainForm =  static_cast<const MainForm*>(mainFormWidget);
        if( nullptr != mainForm )
        {
            const_cast<MainForm*> (mainForm)->ResetSelection();
        }
    }
}


void FileFrameWidget::mouseMoveEvent(QMouseEvent* event)
{
    std::cout<<"FileFrameWidget::mouseMoveEvent"<<std::endl;

    if( nullptr == selectionFrame )
    {
        selectionFrame = new QFrame(this);
        selectionStart = QPoint(event->pos());
        std::cout<<"nullptr == selectionFrame"<<std::endl;
        selectionFrame->move(event->pos());
        QPalette Pal(palette());
        QColor backgroundColor = palette().light().color();
        backgroundColor.setRed(colorArray[0]);
        backgroundColor.setBlue(colorArray[1]);
        backgroundColor.setAlpha(colorArray[2]);
        Pal.setColor(QPalette::Background, backgroundColor);
        selectionFrame->setAutoFillBackground(true);
        selectionFrame->setPalette(Pal);
    }

    int x = qMin(selectionStart.x(), event->pos().x());
    int y = qMin(selectionStart.y(), event->pos().y());
    int w = abs(selectionStart.x() - event->pos().x());
    int h = abs(selectionStart.y() - event->pos().y());

    selectionFrame->setGeometry(x, y, w, h);

    selectionFrame->show();

    const MainForm* mainForm =  static_cast<const MainForm*>(mainFormWidget);
    if( nullptr != mainForm )
    {
        const_cast<MainForm*> (mainForm)->ResetSelection();
    }

    if( nullptr != this->layout() )
    {
        for (size_t i = 0; i < this->layout()->count(); ++i)
        {
            std::cout<<"Widget cout:"<<i<<std::endl;
            QWidget *widget =  this->layout()->itemAt(i)->widget();
            FileWidget* fileWidget = nullptr;
            if( nullptr != widget )
            {
                fileWidget = dynamic_cast<FileWidget*>(widget);
            }

            if (nullptr != fileWidget)
            {
                QRect currentFrame(selectionStart, event->pos());
                bool isIn = widget->geometry().intersects( currentFrame );
                if(isIn)
                {
#if DEBUG
                    std::cout<<"Widget detected:"<<i<<std::endl;
#endif
                    fileWidget->SetSelection(true);
                }
            }
        }
    }
}


void FileFrameWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if( nullptr != selectionFrame )
    {
        selectionFrame->close();
        selectionFrame = nullptr;
    }

    if((nullptr != event) && (event->button() == Qt::RightButton))
    {
        //TODO: multy selection widget
        QWidget* mainForm = const_cast<QWidget*>(mainFormWidget);
        ContextMenu contextmenu(ContextMenu::eFormMenu, nullptr, systemcalls);
        contextmenu.InitMenu(mainForm);
        contextmenu.setGeometry( QRect(QPoint(event->globalX(), event->globalY()),
                                 QPoint(event->globalX() - 80, event->globalY() - 100)) );

        contextmenu.exec();
    }
}



void FileFrameWidget::StartDrag(QMouseEvent* event, QPixmap& localPixmap, QFrame* sender)
{
    FileWidget* child = dynamic_cast<FileWidget*>(sender);
    if ( (nullptr == child) || (nullptr == sender) || (nullptr != dropFileCandidate) )
    {
        return ;
    }

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << localPixmap << QPoint(event->pos() );

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag* drag = new QDrag(this);

    drag->setMimeData(mimeData);
    drag->setHotSpot(event->pos() );
    drag->setPixmap(localPixmap);

    dropFileCandidate = sender;
    drag->exec( Qt::CopyAction | Qt::MoveAction, Qt::CopyAction );

    if(hasBeenDroped)
    {
        sender->close();
        const MainForm* mainForm =  static_cast<const MainForm*>(mainFormWidget);
        const_cast<MainForm*> (mainForm)->NotifyUpdate();
    }
}



void FileFrameWidget::dragEnterEvent(QDragEnterEvent* event)
{
#if DEBUG
    std::cout<<"FileFrameWidget::dragEnterEvent"<<std::endl;
#endif
    if (event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        if (event->source() == this) 
        {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
        else 
        {
            event->acceptProposedAction();
        }
    } 
    else 
    {
        event->ignore();
    }
}


void FileFrameWidget::dragMoveEvent(QDragMoveEvent* event)
{
    std::cout<<"FileFrameWidget::dragMoveEvent"<<std::endl;
    FileWidget* child = nullptr;
    FileLabel* label = dynamic_cast<FileLabel*>(childAt(event->pos()));
    if( (nullptr != label) && (nullptr != label->parent()) )
    {
        child = dynamic_cast<FileWidget*>(label->parent());
    }

    if( (nullptr != child) && (child->IsDirectory()) && (child != dropFileCandidate) )
    {
        if( (dropToFolderCandidate != child) && (nullptr != dropToFolderCandidate) )
        {
            FileWidget* dropToFolderCandidateWidget = static_cast<FileWidget*>(dropToFolderCandidate);
            dropToFolderCandidateWidget->ResetSelectionColor();
        }
        child->SetSelectionColor();
#if DEBUG
        std::cout<<"dropToFolderCandidate is "<< child->GetTitle()->toPlainText().toStdString() <<std::endl;
#endif
        dropToFolderCandidate = child;
    }
    else if (nullptr != dropToFolderCandidate)
    {
#if DEBUG
        std::cout<<"dropToFolderCandidate else "<<std::endl;
#endif
        FileWidget* dropToFolderCandidateWidget = static_cast<FileWidget*>(dropToFolderCandidate);
        dropToFolderCandidateWidget->ResetSelectionColor();
        dropToFolderCandidate = nullptr;
    }
}


void FileFrameWidget::dragLeaveEvent(QDragLeaveEvent* event)
{
#if DEBUG
    std::cout<<"FileFrameWidget::dragLeaveEvent"<<std::endl;
#endif
}


void FileFrameWidget::dropEvent(QDropEvent* event)
{
#if DEBUG
    std::cout<<"FileFrameWidget::dropEvent:"<< dropFileCandidate<< "  " <<dropToFolderCandidate <<std::endl;
#endif
    if( (nullptr != dropFileCandidate) && 
        (nullptr != dropToFolderCandidate) &&
        (nullptr != systemcalls) )
    {
        FileWidget* dropToFolderCandidateWidget = static_cast<FileWidget*>(dropToFolderCandidate);
        FileWidget* dropFileCandidateWidget = static_cast<FileWidget*>(dropFileCandidate);

        QTextEdit* titleFolder = dropToFolderCandidateWidget->GetTitle();
        QTextEdit* titleFile = dropFileCandidateWidget->GetTitle();
        if( (nullptr != titleFolder) && (nullptr != titleFile) )
        {
            systemcalls->MoveFileOrFolder( titleFolder->toPlainText(), titleFile->toPlainText() );
            hasBeenDroped = true;
        }
        dropToFolderCandidateWidget->ResetSelection();
        dropFileCandidateWidget->ResetSelection();
    }
    dropToFolderCandidate = nullptr;
    dropFileCandidate = nullptr;
}

