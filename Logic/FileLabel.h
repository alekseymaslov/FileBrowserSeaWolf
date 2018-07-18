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

#ifndef FILELABEL_H
#define FILELABEL_H

#include <QLabel>
#include <QIcon>
#include <QWidget>
#include <QMouseEvent>


class FileLabel : public QLabel
{
    QIcon storedIcon;
    const QSize iconSize;
public:
    explicit FileLabel( const QIcon& inIcon, const QSize& inIconSize, QWidget* parent = nullptr,
                        Qt::WindowFlags f = Qt::WindowFlags() ) :
    storedIcon(inIcon), iconSize(inIconSize), QLabel(parent, f) 
    {
        setPixmap( storedIcon.pixmap(iconSize) );
        setWindowIcon( storedIcon );
    };

    virtual ~FileLabel(){}

    void SetSelection( bool select );

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent* ) override;
    void mouseReleaseEvent(QMouseEvent * ) override;
    void mouseDoubleClickEvent(QMouseEvent*) override;
    void contextMenuEvent(QContextMenuEvent*) override;
};

#endif // FILELABEL_H
