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

#ifndef SYSTEMCALLS_H
#define SYSTEMCALLS_H

#include <iostream>
#include <memory>
#include <functional>
#include <vector>
#include <QDir>
#include <QString>

class SystemCalls
{
protected:
    QDir qdir;
    QString currentDirectory;
    std::vector<QString> previosPath;
    std::vector<QString> nextPath;
    QFileInfoList list;
public:
    static enum eCurrentSystem
    {
        NOT_SET,
        LINUX,
        DARWIN,
        MS_WINDOWS
    }eCurrentSystem;

    SystemCalls();

    virtual void SetStartDirectory() = 0;
    virtual QString GetCurrentDirectory();
    virtual bool UpCurrentDirectory( bool remeberPath );
    virtual bool SetCurrentDirectory( QString inDirectory, bool remeberPath);
    virtual bool PreviosDirectory();
    virtual bool NextDirectory();
    virtual bool RenameDirectory( QString inDirectory, QString newName );
    virtual const QFileInfoList& GetCurrentDirectoryContent();
    virtual bool CreateDirectory( QString& inNewDirectory );
    virtual bool DeleteFolderOrFile( QString& fileToDelete );
    virtual void GetTreePaths( QMap<QString, QString>& map ) = 0;
    virtual QString GetCurrentFolderName();
    virtual bool MoveFileOrFolder( QString inDirectory, QString inFileName );
    QFileInfo GetFileInfo( const QString& fileName );
    virtual size_t GetFileSize( const QString& fileName );

    void TraverseFolders( const QString& inDirPath, std::function<void(const QFileInfo&)>&& callback );
};

#endif // SYSTEMCALLS_H
