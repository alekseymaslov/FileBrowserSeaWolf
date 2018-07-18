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

#ifndef MAINFORM_H
#define MAINFORM_H

#include <qt4/QtGui/QWidget>
#include <iostream>
#include <map>
#include <QDir>
#include <QDrag>
#include <QGridLayout>

#include <qsignalmapper.h>
#include "SystemCalls.h"
#include "ButtonLogic.h"
#include "CustomQComboBox.h"
#include "FileFrameWidget.h"
#include "MainFormTreeView.h"


class FileWidget;

namespace Ui
{
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

    enum CatalogType
    {
        CatalogType_BAR,
        CatalogType_List,
    };
    
public:
    explicit MainForm( QWidget* parent = 0 );
    virtual ~MainForm();

private:
    CatalogType      currentCatalogType                 = CatalogType_BAR;
    const QSize      iconSize                           = QSize( 70, 140 );
    const float      filenameMaximumSizeHeightAmendment = 3.5f;
    const float      filenameMaximumSizeWidthAmendment  = 2.0f;
    SystemCalls*     systemcalls                        = nullptr;
    QSignalMapper*   signalMapper                       = nullptr;

    CustomQComboBox* customComboBox                     = nullptr;
    Ui::MainForm*    ui                                 = nullptr;
    QString          formFolder                         = "";
    bool             isAllowUpdateFolderViaReturnButton = false;
    bool             updateWithNextPaint                = false;

    MainFormTreeView mainFormTreeView;
    ButtonLogic      buttonlogic;

    mutable std::map<QString, const QWidget*> selector;

    void SetupFileWidget( const QIcon& icon, int fileWidgetWidth, const QString& fileNameString, FileWidget* fileWidget );

    void ShowBarFiles( int scrollAreaWidth, QGridLayout* grid );

private slots:
    void handleButton();
    void handlePathEdit();

protected:
    void paintEvent(QPaintEvent *);

public:

    void UpdateDirectoriesView( bool forceUpdate = false );
    void resizeEvent(QResizeEvent* event);
    void SetupForm( SystemCalls* systemcalls );

    void SetItemSelected( QString fileName, const QWidget* item, bool ignoreOther = false );
    bool IsSelected( QString fileName );

    bool DiselectItem( QString fileName, const QWidget* item );
    void ResetSelection();

    QWidget* GetChildByName( QString name );

    void ClearSelectionMap();

    void NotifyUpdate();
};

#endif // MAINFORM_H
