/*
 * Copyright 2018 <copyright holder> <email>
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

#ifndef PROPERTIESDIALOGUE_H
#define PROPERTIESDIALOGUE_H

#include <QFileInfo>
#include "ui_dialog_properties.h"
#include <QDialog>
#include <QString>

#include "SystemCalls.h"

#include <iostream>
#include <memory>

class PropertiesDialogue : public QDialog
{
    Q_OBJECT
    SystemCalls* systemcalls = nullptr;
    Ui_Dialog* ui = nullptr;
    QString fileName;

    void Init(QFileInfo& info);
public:
    PropertiesDialogue( SystemCalls* inSystemcalls, QString inFileName, QWidget* parent = nullptr);
    void FillWindows();


private slots:
    void Ok();
    void Cancel();
    void Apply();
};

#endif // PROPERTIESDIALOGUE_H
