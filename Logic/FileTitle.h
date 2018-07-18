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

#ifndef FILETITLE_H
#define FILETITLE_H


#include <QTextEdit>
#include <QPlainTextEdit>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>
#include "SystemCalls.h"


class FileTitle : public QTextEdit
{
    QString originalName = "";
public:
    FileTitle(QWidget* parent = nullptr) : QTextEdit(parent) {}

    virtual ~FileTitle(){}

    void Rename();

    void AdjusParentsSize();
signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* ) override;
    void mouseMoveEvent(QMouseEvent* ) override;
    void mouseReleaseEvent(QMouseEvent * ) override;
    void mouseDoubleClickEvent(QMouseEvent* ) override;
    void contextMenuEvent(QContextMenuEvent *) override;
    void focusOutEvent(QFocusEvent *) override;
};

#endif // FILETITLE_H
