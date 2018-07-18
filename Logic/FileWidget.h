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

#ifndef FILEWIDGET_H
#define FILEWIDGET_H

#include <qt4/QtGui/QWidget>
#include <QLabel>
#include <QDir>
#include <QLineEdit>
#include <QPicture>
#include <QFrame>

#include "SystemCalls.h"
#include <QTextEdit>

class FileWidget : public QFrame
{
    Q_OBJECT;

    QString fileName = "";
    size_t id;
    QLabel* labelImage = nullptr;
    QTextEdit* labeltitle = nullptr;
    const QFileInfo& fileInfo;
    //FileInputHandler* inputhandler = nullptr;
    SystemCalls* systemcalls       = nullptr;
    const QWidget* mainWidget      = nullptr;
    QTextEdit* qTextEdit = nullptr;
    int  textLineHeight            = 0;
    int  originalBaseWidgetHeight  = 0;
    int  originalFileWidgetHeight  = 0;
    int  originalLabelTitleMaxHeight = 0;
    int  originalLabelTitleHeight  = 0;
    QPixmap normalLabel;
    bool selectedColorActive = false;
    bool selected = false;
    bool clickedFlag = false;
    bool dragActive = false;
public:
    explicit FileWidget(const QFileInfo& inFileInfo, const QWidget* mainWidget,
                        size_t inId, QWidget* parent = nullptr,
                        Qt::WindowFlags f = Qt::WindowFlags(),
                        QString inFileName = QString("") );



    virtual ~FileWidget();

    void SetParts( QLabel* labelImage, QTextEdit* labeltitle );
    //void SetInputHandler( FileInputHandler* handler );
    void SetFileSystemCalls( SystemCalls* systemcalls );

    void SetSelection(bool ignoreOthers = false);
    void SetSelectionColor();
    void ResetSelection(bool resetFromForm = false);
    void ResetSelectionColor();

    void mousePressButtonEvent(QMouseEvent* event);

    void mouseMoveButtonEvent(QMouseEvent * event);

    void mouseReleaseButtonEvent(QMouseEvent * event);

    void mouseDoubleClickButtonEvent(QMouseEvent* event);

    void contextMenuButtonEvent(QContextMenuEvent *event);

    void mouseDragEvent( QDragMoveEvent *event );

    void SetTextLineHeight( int inTextLineHeight );


    QTextEdit* GetTitle();

    void UpdateForm( bool forceUpdate = false );

    void RenameFileInInternalRepresentation( QString oldName, QString newName );

    bool IsDirectory();
signals:
    void clicked();
private slots:
//     void handleDrag(QWidget*);

//     void s(QDragMoveEvent *event) override;

protected:

//     void mousePressEvent(QMouseEvent* ) override;
//     void dragEnterEvent(QDragEnterEvent*) override;
//     void dragMoveEvent(QDragMoveEvent*) override;
//     void dragLeaveEvent(QDragLeaveEvent*) override;

//     void mousePressEvent(QMouseEvent* event);
//     void mouseDoubleClickEvent(QMouseEvent* event);
private:
};

#endif // FILEWIDGET_H
