#include "ButtonLogic.h"

void ButtonLogic::SetFileSystemCall( SystemCalls* inSystemcalls )
{
    systemcalls = inSystemcalls;
}

void ButtonLogic::SetMainFormUpdate( QWidget* inForm )
{
    //TODO: implementation
}

void ButtonLogic::UpFolderButton()
{
    systemcalls->SetCurrentDirectory("", true);
}
void ButtonLogic::mousePressEvent(QMouseEvent* event)
{
    //TODO: implementation
}
