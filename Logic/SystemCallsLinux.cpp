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

#include "SystemCallsLinux.h"
#include <QFileSystemWatcher>
#include <QMap>
#include <iostream>
#include <fstream>
#include <experimental/filesystem>

SystemCallsLinux::SystemCallsLinux(){}


void SystemCallsLinux::SetStartDirectory()
{
    qdir.cd( qdir.homePath() );

    list = qdir.entryInfoList();
}


bool SystemCallsLinux::MoveToTrash(QString& inNewDirectory)
{
    bool result = false;
    QString absolutePath = qdir.absolutePath() + inNewDirectory;
    QFileInfo info(absolutePath);
    if( info.isDir() )
    {
        QDir dirToRemove(absolutePath);
        //TODO: generate metafile
    }
    else
    {
        QFile fileToRemove(absolutePath);
    }
    return result;
}


void SystemCallsLinux::GetTreePaths( QMap<QString, QString>& map )
{
    QDir home;
    home.cd( qdir.homePath() );
    //TODO: move to class header and add check if exist
    map["Root"] = qdir.rootPath();
    map["Home"] = home.absolutePath();
    map["Documents"];
    map["Downloads"];
    map["Music"];
    map["Pictures"];

    QFileInfoList listInfo = home.entryInfoList(QDir::AllDirs);
    for( size_t i = 0; i < listInfo.count(); i++ )
    {
        QString currentDir = listInfo.at(i).baseName();
        auto currentKey = map.find(currentDir);
        if( currentKey != map.end() )
        {
            QString currentPath = home.absolutePath() + QString("/") + currentDir;
            currentKey.value() = currentPath;
        }
    }
}


bool SystemCallsLinux::MoveFileOrFolder(QString inDirectory, QString inFileName)
{
namespace fs = std::experimental::filesystem;
    QString filePath = qdir.path() + QString("/") + inFileName;
    QString destinationPath = qdir.path() + QString("/") + inDirectory + QString("/") + inFileName;
#if DEBUG
    std::cout<<"inDirectory: "<<filePath.toStdString()<<"\ninFileName: "<<destinationPath.toStdString()<<std::endl;
#endif
    fs::rename( filePath.toStdString(), destinationPath.toStdString() );
    qdir.refresh();
    list = qdir.entryInfoList();
}


size_t SystemCallsLinux::GetFileSize( const QString& fileName )
{
    size_t fileSize = 0;
    QFileInfo fileInfo(fileName);
    if( fileInfo.isDir() )
    {
        auto lambdaCalculationSize = [&fileSize](const QFileInfo& fileInfo){
                fileSize += fileInfo.size();
        };
        TraverseFolders( fileName, lambdaCalculationSize );
    }
    else
    {
        fileSize += fileInfo.size();
    }
    return fileSize;
}

