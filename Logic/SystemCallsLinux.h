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

#ifndef SYSTEMCALLSLINUX_H
#define SYSTEMCALLSLINUX_H

#include "SystemCalls.h"

class SystemCallsLinux : public SystemCalls
{
    size_t flodersContentSize = 0;
public:
    SystemCallsLinux();
    void SetStartDirectory();
    bool MoveToTrash( QString& inNewDirectory );
    void GetTreePaths( QMap<QString, QString>& map );
    bool MoveFileOrFolder( QString inDirectory, QString inFileName );
    size_t GetFileSize( const QString& fileName );
};

#endif // SYSTEMCALLSLINUX_H
