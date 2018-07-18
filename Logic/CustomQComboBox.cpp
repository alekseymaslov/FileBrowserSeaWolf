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

#include "CustomQComboBox.h"
#include <QTimer>
#include <QObject>
#include <QCoreApplication>
#include <QKeyEvent>
#include <QLineEdit>


bool CustomQComboBox::eventFilter(QObject* watched, QEvent* event)
{
    if (event->type() == QEvent::KeyPress)
    {
         QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
         QKeyEvent* newEvent = new QKeyEvent(keyEvent->type(), keyEvent->key(), keyEvent->modifiers(), 
                                             keyEvent->text(), keyEvent->isAutoRepeat(), keyEvent->count());

         QFocusEvent* focusEvent = new QFocusEvent(QEvent::FocusIn, Qt::OtherFocusReason);
         QCoreApplication::postEvent(lineEdit(), focusEvent);
         QCoreApplication::postEvent(lineEdit(), newEvent);
    }

    return false;
}

