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
//  * limitations under the License.
 * 
 */

#include "MainForm.h"
#include "ui_mainform.h"
#include "FileWidget.h"
#include "FileFrameWidget.h"


#include <QLabel>
#include <QDialog>
#include <QFileIconProvider>
#include <QApplication>
#include <QCompleter>
#include <QLineEdit>
#include <QScrollBar>
#include <Qt>
#include <QTreeWidget>
#include <QAction>
#include <QTextEdit>
#include <QMessageBox>
#include <QEvent>

#include <iostream>
#include <exception>

#include "FileLabel.h"
#include "FileTitle.h"


using namespace std;


MainForm::MainForm(QWidget* parent): QWidget(parent), ui(new Ui::MainForm)
{
    this->systemcalls = nullptr;
    ui->setupUi(this);
}


MainForm::~MainForm()
{
    ResetSelection();
    delete signalMapper;
    delete customComboBox;
    delete ui;
}


void MainForm::SetupFileWidget( const QIcon& icon, int fileWidgetWidth, const QString& fileNameString, FileWidget* fileWidget )
{
    fileWidget->setMaximumSize(QSize(fileWidgetWidth, iconSize.height()));
    fileWidget->setMinimumSize(QSize(fileWidgetWidth, iconSize.height()));
    fileWidget->setObjectName( fileNameString );
    fileWidget->SetFileSystemCalls(systemcalls);

    QSize iconActualSize = icon.actualSize(iconSize);
    FileLabel* imageLabel = new FileLabel(icon, iconActualSize);
    imageLabel->setFixedSize(iconActualSize);
    imageLabel->adjustSize();

    imageLabel->setAlignment( Qt::AlignTop | Qt::AlignHCenter );

    FileTitle* fileName = new FileTitle();
    fileName->setText( fileNameString );

    fileName->setReadOnly(true);
    fileName->setFrameStyle(QFrame::NoFrame);
    fileName->setAlignment( Qt::AlignTop | Qt::AlignHCenter );
    fileName->viewport()->setAutoFillBackground(false);
    fileName->setMaximumSize((iconSize.width() * filenameMaximumSizeWidthAmendment),
                              iconSize.height()/filenameMaximumSizeHeightAmendment);
    QScrollBar* scrollBar = fileName->verticalScrollBar();
    scrollBar->setDisabled(true);
    fileName->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    fileName->setTextInteractionFlags(Qt::TextSelectableByMouse);
    fileName->adjustSize();

    QVBoxLayout* fileLayout = new QVBoxLayout( /*fileWidget*/ );
    fileLayout->insertWidget( 0, imageLabel, 0, Qt::AlignCenter );
    fileLayout->insertWidget( 1, fileName );
    fileWidget->SetParts( imageLabel, fileName );
    fileWidget->setLayout( fileLayout );
}


void MainForm::ShowBarFiles( int scrollAreaWidth, QGridLayout* grid )
{
    const QWidget* self = static_cast<const QWidget*>(this);
    QFileIconProvider iconProvider;
    const QFileInfoList& list = systemcalls->GetCurrentDirectoryContent();
    int fileWidgetWidth = iconSize.width() * 2;
    size_t xiterator = 0, yiterator = 0;

    for( size_t i = 0; i < list.count(); i++ )
    {
        bool isDirectory = false;
        auto fileNameString = list.at(i).fileName();
        if( (fileNameString.isEmpty()) ||
            (QString(".") == fileNameString) || //TODO: to user option view of dot folders of linux
            (QString("..") == fileNameString) )
        {
            continue;
        }

        if( list.at(i).isDir() )
        {
            isDirectory = true;
            ui->comboBox->addItem( list.at(i).filePath() );
        }

        QIcon icon = iconProvider.icon( list.at(i) );
        FileWidget* fileWidget = new FileWidget( list.at(i), self, i, grid->widget(), Qt::WindowFlags(), fileNameString );
        SetupFileWidget( icon, fileWidgetWidth, fileNameString, fileWidget );

        if( (fileWidgetWidth * (xiterator + 1)) > scrollAreaWidth )
        {
            yiterator++;
            xiterator = 0;
        }

        if( selector.count( fileNameString )/*nullptr != selector[fileNameString]*/ )
        {
            fileWidget->SetSelectionColor();
            selector[fileNameString] = fileWidget;
        }
        grid->addWidget( fileWidget, yiterator, xiterator );
        xiterator++;
    }
}


void MainForm::handleButton()
{
    if( nullptr != systemcalls )
    {
        if( ui->pushButton_4->isDown() )
        {
            systemcalls->UpCurrentDirectory( true );
        }

        if( ui->pushButton_2->isDown() )
        {
            systemcalls->PreviosDirectory();
        }

        if( ui->pushButton->isDown() )
        {
            systemcalls->NextDirectory();
        }
    }
    UpdateDirectoriesView(true);
}


void MainForm::handlePathEdit()
{
    if( nullptr != systemcalls )
    {
        QString newPath = ui->comboBox->lineEdit()->text();
        QString currenPath = systemcalls->GetCurrentDirectory();
        if( (0 != currenPath.size()) && (currenPath != newPath) )
        {
            bool changed = systemcalls->SetCurrentDirectory( newPath, true );
            if(!changed)
            {
                QString dialogName( QString("Error path ") + newPath + QString(" is not found!") );
                QMessageBox messageBox;
                messageBox.setButtonText(QMessageBox::Ok , tr("Ok"));
                messageBox.setText( dialogName );
                messageBox.exec();
            }
            NotifyUpdate();
        }
    }
    ui->comboBox->clearFocus();
}


void MainForm::paintEvent(QPaintEvent*)
{
    if( updateWithNextPaint )
    {
        updateWithNextPaint = false;
        UpdateDirectoriesView();
    }
}


void MainForm::UpdateDirectoriesView( bool forceUpdate )//TODO: remove update
{
    QScrollArea* scrollArea = ui->scrollArea;
    QString currentFolder = "";

    if( nullptr != systemcalls )
    {
        currentFolder = systemcalls->GetCurrentDirectory();
    }

    if( (formFolder != currentFolder) || (forceUpdate) )
    {
        formFolder = currentFolder;
        selector.clear();
        ui->comboBox->clear();
        ui->comboBox->clearEditText();
        if(0 != currentFolder.size())
        {
            ui->comboBox->addItem(currentFolder);
        }
    }

    const QWidget* self = static_cast<const QWidget*>(this);
    FileFrameWidget* scrollAreaWidgetContents = new FileFrameWidget(self, scrollArea);
    if( (0 != currentFolder.size()) && (nullptr != systemcalls) )
    {
        scrollAreaWidgetContents->SetSystemsCall(systemcalls);
#if DEBUG
        std::cout<<"current directory !"<< currentFolder.toStdString() <<std::endl;
#endif
        if( CatalogType_BAR == currentCatalogType )
        {
            QGridLayout* grid = new QGridLayout(scrollAreaWidgetContents);
            ShowBarFiles( scrollArea->width(), grid );
            grid->setAlignment( Qt::AlignTop );
        }
        else
        {
            throw std::logic_error("not implemented");
        }
        this->setWindowTitle( currentFolder );
    }

    scrollArea->setWidget( scrollAreaWidgetContents );

    mainFormTreeView.Update();
    scrollArea->update();
}


void  MainForm::resizeEvent(QResizeEvent* event)
{
    (void)event;
    UpdateDirectoriesView();
}


void MainForm::SetupForm( SystemCalls* systemcalls )
{
    this->setObjectName(QString::fromUtf8("MainForm"));
    this->systemcalls = systemcalls;

    customComboBox = new CustomQComboBox(ui->comboBox);

    connect(ui->pushButton_4, SIGNAL (pressed()), this, SLOT (handleButton()));
    connect(ui->pushButton_3, SIGNAL (pressed()), this, SLOT (handleButton()));
    connect(ui->pushButton_2, SIGNAL (pressed()), this, SLOT (handleButton()));
    connect(ui->pushButton, SIGNAL (pressed()), this, SLOT (handleButton()));
    connect(ui->comboBox->lineEdit(), SIGNAL (returnPressed()), this, SLOT (handlePathEdit()));//TODO: separate functional

    connect(ui->comboBox, SIGNAL (activated(int)), this, SLOT (handlePathEdit()));

    ui->comboBox->view()->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    ui->comboBox->completer()->setCompletionMode(QCompleter::PopupCompletion);

    QString currentFolder = systemcalls->GetCurrentDirectory();
    ui->comboBox->addItem(currentFolder);

    mainFormTreeView.Init( systemcalls, ui->treeWidget, this );
}


void MainForm::SetItemSelected( QString fileName, const QWidget* item, bool ignoreOther )
{
    if( selector[fileName] != item )
    {
        if( (!ignoreOther) && !QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)  )
        {
            ResetSelection();
            selector.clear();
        }
        selector[fileName] = item;
    }
}


bool MainForm::IsSelected(QString fileName)
{
    if( selector.count( fileName ) )
    {
        if( selector[fileName] != nullptr )
        {
            return true;
        }
    }
    return false;
}


bool MainForm::DiselectItem(QString fileName, const QWidget* item)
{
    if( selector.count(fileName) )
    {
        if( selector[fileName] == item )
        {
            selector[fileName] = nullptr;
        }
    }
}


//FIXME: the is a crash between ResetSelection and UpdateDirectories
void MainForm::ResetSelection()
{
    for( auto i : selector )
    {
        const FileWidget* fileWidget = static_cast<const FileWidget*>(i.second);
        if( nullptr != fileWidget )
        {
            const_cast<FileWidget*>(fileWidget)->ResetSelection(true);
        }
    }
    selector.clear();
}


QWidget* MainForm::GetChildByName( QString name )
{
    QWidget* widget = this->findChild<QWidget*>(name);
    return widget;
}


void MainForm::ClearSelectionMap()
{
    selector.clear();
}


void MainForm::NotifyUpdate()
{
    QEvent* updateEvent = new QEvent(QEvent::Type::Paint);
    //NOTE: sould always istert event to end of queue
    if(QCoreApplication::hasPendingEvents())
    {
        QCoreApplication::postEvent( this, updateEvent, Qt::LowEventPriority );
    }
    else
    {
        QCoreApplication::postEvent( this, updateEvent );
    }
    updateWithNextPaint = true;
}


#include "MainForm.moc"

