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

#include "PropertiesDialogue.h"
#include <QFileIconProvider>

#include <string>

PropertiesDialogue::PropertiesDialogue(SystemCalls* inSystemcalls, QString inFileName, QWidget* parent) :
systemcalls(inSystemcalls), fileName(inFileName), QDialog(parent), ui(new Ui_Dialog)
{
    ui->setupUi(this);
}


void PropertiesDialogue::Init(QFileInfo& info)
{
    const QSize iconSize = QSize( 40, 65 );//TODO: consts
    QFileIconProvider iconProvider;
    QIcon icon = iconProvider.icon( info );
    QLabel* iconLabel = new QLabel();
    iconLabel->setPixmap(icon.pixmap(iconSize));
    ui->horizontalLayout_2->insertWidget( 0, iconLabel );
    connect(ui->pushButton_3, SIGNAL (pressed()), this, SLOT (Ok()));
    connect(ui->pushButton_2, SIGNAL (pressed()), this, SLOT (Cancel()));
    connect(ui->pushButton, SIGNAL (pressed()), this, SLOT (Apply()));
}


void PropertiesDialogue::FillWindows()
{
    QFileInfo fileInfo = systemcalls->GetFileInfo(fileName);
    Init( fileInfo );
    this->setWindowTitle(fileName);
    ui->lineEdit->setText(fileName);
    ui->label_4->setText(fileInfo.absoluteFilePath());
    QString fileType = "Unknown";//TODO: to dictionary
    if( fileInfo.isDir() )
    {
        fileType = "Folder";//TODO: to dictionary
    }
    else
    {
        std::string stdFileName = fileName.toStdString();
        std::string extention = stdFileName.substr(stdFileName.find_last_of(".") + 1);
        if( extention.size() != 0 )
        {
            fileType = extention.c_str();
        }
    }

    ui->label_2->setText(fileType);

    size_t fileSizeNumber = systemcalls->GetFileSize(fileInfo.absoluteFilePath());
    QString measure[] = {"bytes", "kbytes", "mbytes", "gbytes", "tbytes"};//TODO: to dictionary
    const size_t byteMeasureConst = 1024;
    size_t iteration = 0;
    while( fileSizeNumber > byteMeasureConst )
    {
        iteration++;
        fileSizeNumber /= byteMeasureConst;
    }
    
    
    QString fileSize = (std::to_string(fileSizeNumber)).c_str();
    ui->label_6->setText(fileSize + QString("") + measure[iteration]);
}


void PropertiesDialogue::Ok()
{
    //TODO: implementation
}


void PropertiesDialogue::Cancel()
{
    this->close();
}


void PropertiesDialogue::Apply()
{
    //TODO: implementation
}


#include "PropertiesDialogue.moc"
