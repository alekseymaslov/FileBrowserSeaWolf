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

#ifndef FILEFRAMEGRID_H
#define FILEFRAMEGRID_H


#include <QGridLayout>
#include <QMouseEvent>

#include "SystemCalls.h"


class FileFrameGrid : public QGridLayout
{
    SystemCalls*    systemcalls    = nullptr;
    const QWidget*  mainFormWidget = nullptr;
    int globalXCorrection = 80, globalYCorrection = 100;
public:
    explicit FileFrameGrid( const QWidget* inMainForm, QWidget* parent = nullptr ) :
                            mainFormWidget(inMainForm), QGridLayout(parent){};

    virtual ~FileFrameGrid(){};

    void SetSystemsCall( SystemCalls* inSystemcalls );

signals:
    void clicked();

protected:
    void mousePressEvent( QMouseEvent* event );

};

#endif // FILEFRAMEGRID_H
