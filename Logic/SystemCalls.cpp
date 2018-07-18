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

#include "SystemCalls.h"
#include <iostream>
#include <exception>


SystemCalls::SystemCalls()
{
    list = qdir.entryInfoList();
}


QString SystemCalls::GetCurrentDirectory()
{
    return qdir.absolutePath();
}

bool SystemCalls::UpCurrentDirectory( bool remeberPath )
{
    bool changed = false;
    QString currentPath = qdir.absolutePath();
    changed = qdir.cdUp();
    if( changed )
    {
        if(remeberPath)
        {
            previosPath.push_back( currentPath );
        }
        list = qdir.entryInfoList();
    }

    return changed;
}

bool SystemCalls::SetCurrentDirectory(QString inDirectory, bool remeberPath)
{
    bool changed = false;
    QString currentPath = qdir.absolutePath();
    changed = qdir.cd( inDirectory );
    if( changed )
    {
        if(remeberPath)
        {
            previosPath.push_back( currentPath );
        }
        qdir.refresh();
        list.clear();
        list = qdir.entryInfoList();
    }

    return changed;
}

bool SystemCalls::PreviosDirectory()
{
    bool changed = false;
    if( !previosPath.empty() )
    {
        QString previosDirectory = previosPath.at( previosPath.size() - 1 );
        nextPath.push_back( qdir.absolutePath() );
        changed = SetCurrentDirectory( previosDirectory, false );
        if( changed )
        {
            previosPath.pop_back();
        }
    }
    return changed;
}


bool SystemCalls::NextDirectory()
{
    bool changed = false;
    if( !nextPath.empty() )
    {
        QString nextDirectory = nextPath.at( nextPath.size() - 1 );
        changed = SetCurrentDirectory( nextDirectory, true );
        if( changed )
        {
            nextPath.pop_back();
        }
    }
    return changed;
}


bool SystemCalls::RenameDirectory(QString inDirectory, QString newName)
{
    bool internalResult = qdir.rename( inDirectory, newName );
    if( !internalResult )
    {
        throw std::logic_error("SystemCalls::RenameDirectory:\
                                it is not possible to change a directory name!" );
    }

    qdir.refresh();
    list = qdir.entryInfoList();
    return internalResult;
}


const QFileInfoList& SystemCalls::GetCurrentDirectoryContent()
{
    return list;
}


bool SystemCalls::CreateDirectory( QString& inNewDirectory )
{
    size_t dublicatNumber = 1;
    list = qdir.entryInfoList();
    for(size_t i = 0; i < list.size(); i++)
    {
        //NOTE: possible bug
        if( inNewDirectory == list.at(i).fileName() )
        {
            inNewDirectory += QString("(");
            inNewDirectory += QString( std::to_string(dublicatNumber).c_str() );
            inNewDirectory += QString(")");
            dublicatNumber++;
        }
    }

    bool creationResult = qdir.mkdir( inNewDirectory );
    std::cout<<"files list size: "<<list.size()<<std::endl;
    if( creationResult )
    {
        qdir.refresh();
        list = qdir.entryInfoList();
    }
#if DEBUG
    std::cout<<"files list size: "<<list.size()<<std::endl;
#endif
    return creationResult;
}

//FIXME: bug folder is deleting properly
bool SystemCalls::DeleteFolderOrFile( QString& fileToDelete )
{
    bool wereDeleted = false;
    QFileInfo fileInfo(qdir, fileToDelete);
    if( fileInfo.isFile() )
    {
        QString filePath = qdir.path() + "//" + fileToDelete;
        QFile file (filePath);
        wereDeleted = file.remove();
    }
    else
    {
        wereDeleted = qdir.rmdir( fileToDelete );
    }

    if( wereDeleted )
    {
        qdir.refresh();
        list = qdir.entryInfoList();
    }

    return wereDeleted;
}

QString SystemCalls::GetCurrentFolderName()
{
    return qdir.dirName();
}


bool SystemCalls::MoveFileOrFolder(QString inDirectory, QString inFileName)
{
#if DEBUG
    std::cout<<"MoveFileOrFolder: "<<inDirectory.toStdString()<< " "<< inFileName.toStdString() <<std::endl;
#endif
    QString filePath = qdir.path() + QString("/") + inFileName;
    QString destinationPath = qdir.path() + QString("/") + inDirectory;

    QDir fileToMove(filePath);
#if DEBUG
    std::cout<<filePath.toStdString()<<std::endl;
    std::cout<<destinationPath.toStdString()<<std::endl;
#endif
    if( /*!fileToMove.rename( filePath, destinationPath )*/ fileToMove.setCurrent(destinationPath) )
    {
        std::cout<<"move failed"<<std::endl;
    }
    qdir.refresh();
    list = qdir.entryInfoList();
}


QFileInfo SystemCalls::GetFileInfo(const QString& fileName)
{
    QFileInfo fileInfo;
    if(qdir.dirName() == fileName)
    {
        QString dirPath = qdir.absolutePath();
        fileInfo = QFileInfo(dirPath);
    }
    else
    {
        fileInfo = QFileInfo(qdir, fileName);
    }
    return fileInfo;
}


size_t SystemCalls::GetFileSize(const QString& fileName)
{
    return 0;
}


void SystemCalls::TraverseFolders(const QString& inDirPath, std::function<void(const QFileInfo&)>&& callback )
{
    QDir currentDir(inDirPath);
    QFileInfoList listInfo = currentDir.entryInfoList();
    for( auto i : listInfo  )
    {
        //FIXME: remove from here linux dependences
        if( (i.baseName().isEmpty()) ||
            (QString(".") == i.baseName()) || 
            (QString("..") == i.baseName()) )
        {
            continue;
        }

        if(i.isDir())
        {
            TraverseFolders(i.absolutePath() + QString("/") + i.baseName(), std::move(callback));
            callback(i);
        }
        else
        {
            callback(i);
        }
    }
}

