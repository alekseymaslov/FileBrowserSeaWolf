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

#include "BaseManager.h"
#include "SystemCallsFactory.h"
#include "iostream"

using namespace std;

void BaseManager::RunManager()
{
    SystemCallsFactory systemCallFactory;
    try
    {
        systemCall = systemCallFactory.CreateSystemCalls();
        if( nullptr == systemCall )
        {
            throw runtime_error( "undefined system!" );
        }
        systemCall->SetStartDirectory();
        mainform.SetupForm( systemCall );
        mainform.UpdateDirectoriesView();
    }
    catch( std::exception const& exp )
    {
        //TODO: handle the exception
#if DEBUG
        cout<<exp.what()<<endl;
#endif
    }
}
