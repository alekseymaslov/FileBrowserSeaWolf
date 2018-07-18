#include <QtGui/QApplication>
#include "MainForm.h"
#include "BaseManager.h"

#include <iostream>

int main(int argc, char** argv)
{
    int appResult = 0;
    try
    {
        QApplication app(argc, argv);
        MainForm mainform;
        BaseManager basemanager( mainform );
        mainform.show();
        basemanager.RunManager();
        appResult = app.exec();
    }
    catch(std::exception const& exp)
    {
        //TODO: create dialog with this error
#if DEBUG
        std::cout<<exp.what()<<std::endl;
#endif
    }
    return appResult;
}
