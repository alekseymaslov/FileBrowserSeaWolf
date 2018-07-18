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

#ifndef BUTTONLOGIC_H
#define BUTTONLOGIC_H

#include "SystemCalls.h"
#include <qt4/QtGui/QWidget>

class ButtonLogic 
{
    SystemCalls* systemcalls = nullptr;
    QWidget*     mainForm    = nullptr;
public:
    explicit ButtonLogic( QWidget* parent = nullptr ){}
    virtual ~ButtonLogic(){}

    void SetFileSystemCall( SystemCalls* inSystemcalls );

    void SetMainFormUpdate( QWidget* inForm );

    void UpFolderButton();

    void mousePressEvent(QMouseEvent* event);
};

#endif // BUTTONLOGIC_H
