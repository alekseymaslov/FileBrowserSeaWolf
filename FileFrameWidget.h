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

#ifndef FILEFRAMEWIDGET_H
#define FILEFRAMEWIDGET_H

#include <qt4/QtGui/QWidget>
#include <QLabel>
#include <QDir>
#include <QDrag>
#include <QFrame>
#include "SystemCalls.h"
#include <iostream>


class FileFrameWidget : public QFrame
{
    SystemCalls*    systemcalls    = nullptr;
    const QWidget*  mainFormWidget = nullptr;
public:
    explicit FileFrameWidget( const QWidget* inMainForm, QWidget* parent = nullptr,
                              Qt::WindowFlags f = Qt::WindowFlags() ) :
                              mainFormWidget(inMainForm), QFrame(parent, f)
                            {
                                setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
                                setAcceptDrops(true);
                            };

    virtual ~FileFrameWidget(){std::cout<<"delete FileFrameWidget"<<std::endl;};

    void SetSystemsCall( SystemCalls* systemcalls );

    void StartDrag(QMouseEvent* event, QPixmap& localPixmap, QFrame* sender);
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void dragEnterEvent(QDragEnterEvent*) override;
    void dragMoveEvent(QDragMoveEvent*) override;
    void dragLeaveEvent(QDragLeaveEvent*) override;
    void dropEvent(QDropEvent *) override;
private:
    QFrame* dropFileCandidate = nullptr;
    QFrame* dropToFolderCandidate = nullptr;
    bool    hasBeenDroped = false;
    QFrame* selectionFrame = nullptr;
    QPoint  selectionStart;
    uint8_t colorArray[] = {100, 20, 100};
};

#endif // FILEFRAMEWIDGET_H
