/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Mon Aug 25 18:16:29 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionControlWidget;
    QAction *actionDeleteEdge;
    QAction *actionSaveTerrain;
    QAction *actionSaveRoads;
    QAction *actionPropertyWidget;
    QAction *actionLoadRoads;
    QAction *actionLoadAreas;
    QAction *actionSaveAreas;
    QAction *actionSaveImage;
    QAction *actionGenerateAll;
    QAction *actionLoadCamera;
    QAction *actionSaveCamera;
    QAction *actionSaveImageHD;
    QAction *actionOpen;
    QAction *actionModeDefault;
    QAction *actionModeBlock;
    QAction *actionLoadBlocks;
    QAction *actionSaveBlocks;
    QAction *actionGenerateBlocks;
    QAction *actionNewTerrain;
    QAction *actionOpenTerrain;
    QAction *actionClearRoads;
    QAction *actionGenerateParcels;
    QAction *actionGenerateBuildings;
    QAction *actionGenerateVegetation;
    QAction *actionModeParcel;
    QAction *actionModePlaceType;
    QAction *actionLoadPlaceTypes;
    QAction *actionCameraDefault;
    QAction *actionCameraCar;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *fileToolBar;
    QToolBar *modeToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1006, 800);
        MainWindow->setMinimumSize(QSize(1000, 800));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionControlWidget = new QAction(MainWindow);
        actionControlWidget->setObjectName(QString::fromUtf8("actionControlWidget"));
        actionDeleteEdge = new QAction(MainWindow);
        actionDeleteEdge->setObjectName(QString::fromUtf8("actionDeleteEdge"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/MainWindow/Resources/Delete_24x24.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDeleteEdge->setIcon(icon);
        actionSaveTerrain = new QAction(MainWindow);
        actionSaveTerrain->setObjectName(QString::fromUtf8("actionSaveTerrain"));
        actionSaveRoads = new QAction(MainWindow);
        actionSaveRoads->setObjectName(QString::fromUtf8("actionSaveRoads"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/MainWindow/Resources/Save_24x24.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveRoads->setIcon(icon1);
        actionPropertyWidget = new QAction(MainWindow);
        actionPropertyWidget->setObjectName(QString::fromUtf8("actionPropertyWidget"));
        actionLoadRoads = new QAction(MainWindow);
        actionLoadRoads->setObjectName(QString::fromUtf8("actionLoadRoads"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/MainWindow/Resources/Open_24x24.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoadRoads->setIcon(icon2);
        actionLoadAreas = new QAction(MainWindow);
        actionLoadAreas->setObjectName(QString::fromUtf8("actionLoadAreas"));
        actionSaveAreas = new QAction(MainWindow);
        actionSaveAreas->setObjectName(QString::fromUtf8("actionSaveAreas"));
        actionSaveImage = new QAction(MainWindow);
        actionSaveImage->setObjectName(QString::fromUtf8("actionSaveImage"));
        actionGenerateAll = new QAction(MainWindow);
        actionGenerateAll->setObjectName(QString::fromUtf8("actionGenerateAll"));
        actionLoadCamera = new QAction(MainWindow);
        actionLoadCamera->setObjectName(QString::fromUtf8("actionLoadCamera"));
        actionSaveCamera = new QAction(MainWindow);
        actionSaveCamera->setObjectName(QString::fromUtf8("actionSaveCamera"));
        actionSaveImageHD = new QAction(MainWindow);
        actionSaveImageHD->setObjectName(QString::fromUtf8("actionSaveImageHD"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionModeDefault = new QAction(MainWindow);
        actionModeDefault->setObjectName(QString::fromUtf8("actionModeDefault"));
        actionModeDefault->setCheckable(true);
        actionModeBlock = new QAction(MainWindow);
        actionModeBlock->setObjectName(QString::fromUtf8("actionModeBlock"));
        actionModeBlock->setCheckable(true);
        actionLoadBlocks = new QAction(MainWindow);
        actionLoadBlocks->setObjectName(QString::fromUtf8("actionLoadBlocks"));
        actionSaveBlocks = new QAction(MainWindow);
        actionSaveBlocks->setObjectName(QString::fromUtf8("actionSaveBlocks"));
        actionGenerateBlocks = new QAction(MainWindow);
        actionGenerateBlocks->setObjectName(QString::fromUtf8("actionGenerateBlocks"));
        actionNewTerrain = new QAction(MainWindow);
        actionNewTerrain->setObjectName(QString::fromUtf8("actionNewTerrain"));
        actionOpenTerrain = new QAction(MainWindow);
        actionOpenTerrain->setObjectName(QString::fromUtf8("actionOpenTerrain"));
        actionClearRoads = new QAction(MainWindow);
        actionClearRoads->setObjectName(QString::fromUtf8("actionClearRoads"));
        actionGenerateParcels = new QAction(MainWindow);
        actionGenerateParcels->setObjectName(QString::fromUtf8("actionGenerateParcels"));
        actionGenerateBuildings = new QAction(MainWindow);
        actionGenerateBuildings->setObjectName(QString::fromUtf8("actionGenerateBuildings"));
        actionGenerateVegetation = new QAction(MainWindow);
        actionGenerateVegetation->setObjectName(QString::fromUtf8("actionGenerateVegetation"));
        actionModeParcel = new QAction(MainWindow);
        actionModeParcel->setObjectName(QString::fromUtf8("actionModeParcel"));
        actionModePlaceType = new QAction(MainWindow);
        actionModePlaceType->setObjectName(QString::fromUtf8("actionModePlaceType"));
        actionLoadPlaceTypes = new QAction(MainWindow);
        actionLoadPlaceTypes->setObjectName(QString::fromUtf8("actionLoadPlaceTypes"));
        actionCameraDefault = new QAction(MainWindow);
        actionCameraDefault->setObjectName(QString::fromUtf8("actionCameraDefault"));
        actionCameraCar = new QAction(MainWindow);
        actionCameraCar->setObjectName(QString::fromUtf8("actionCameraCar"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1006, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menuBar);
        fileToolBar = new QToolBar(MainWindow);
        fileToolBar->setObjectName(QString::fromUtf8("fileToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, fileToolBar);
        modeToolBar = new QToolBar(MainWindow);
        modeToolBar->setObjectName(QString::fromUtf8("modeToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, modeToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "FBC Designer", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionControlWidget->setText(QApplication::translate("MainWindow", "Control Widget", 0, QApplication::UnicodeUTF8));
        actionDeleteEdge->setText(QApplication::translate("MainWindow", "Delete Edge", 0, QApplication::UnicodeUTF8));
        actionDeleteEdge->setShortcut(QApplication::translate("MainWindow", "Del", 0, QApplication::UnicodeUTF8));
        actionSaveTerrain->setText(QApplication::translate("MainWindow", "Save Terrain", 0, QApplication::UnicodeUTF8));
        actionSaveTerrain->setShortcut(QString());
        actionSaveRoads->setText(QApplication::translate("MainWindow", "Save Roads", 0, QApplication::UnicodeUTF8));
        actionPropertyWidget->setText(QApplication::translate("MainWindow", "Property Widget", 0, QApplication::UnicodeUTF8));
        actionLoadRoads->setText(QApplication::translate("MainWindow", "Load Roads", 0, QApplication::UnicodeUTF8));
        actionLoadRoads->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionLoadAreas->setText(QApplication::translate("MainWindow", "Load Areas", 0, QApplication::UnicodeUTF8));
        actionLoadAreas->setShortcut(QApplication::translate("MainWindow", "Ctrl+A", 0, QApplication::UnicodeUTF8));
        actionSaveAreas->setText(QApplication::translate("MainWindow", "Save Areas", 0, QApplication::UnicodeUTF8));
        actionSaveImage->setText(QApplication::translate("MainWindow", "Save Image", 0, QApplication::UnicodeUTF8));
        actionSaveImage->setShortcut(QApplication::translate("MainWindow", "Ctrl+L", 0, QApplication::UnicodeUTF8));
        actionGenerateAll->setText(QApplication::translate("MainWindow", "Generate All", 0, QApplication::UnicodeUTF8));
        actionLoadCamera->setText(QApplication::translate("MainWindow", "Load Camera", 0, QApplication::UnicodeUTF8));
        actionLoadCamera->setShortcut(QApplication::translate("MainWindow", "Ctrl+1", 0, QApplication::UnicodeUTF8));
        actionSaveCamera->setText(QApplication::translate("MainWindow", "Save Camera", 0, QApplication::UnicodeUTF8));
        actionSaveCamera->setShortcut(QApplication::translate("MainWindow", "Ctrl+2", 0, QApplication::UnicodeUTF8));
        actionSaveImageHD->setText(QApplication::translate("MainWindow", "Save Image HD", 0, QApplication::UnicodeUTF8));
        actionSaveImageHD->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
        actionModeDefault->setText(QApplication::translate("MainWindow", "Default", 0, QApplication::UnicodeUTF8));
        actionModeBlock->setText(QApplication::translate("MainWindow", "Block", 0, QApplication::UnicodeUTF8));
        actionLoadBlocks->setText(QApplication::translate("MainWindow", "Load Blocks", 0, QApplication::UnicodeUTF8));
        actionSaveBlocks->setText(QApplication::translate("MainWindow", "Save Blocks", 0, QApplication::UnicodeUTF8));
        actionGenerateBlocks->setText(QApplication::translate("MainWindow", "Generate Blocks", 0, QApplication::UnicodeUTF8));
        actionNewTerrain->setText(QApplication::translate("MainWindow", "New Terrain", 0, QApplication::UnicodeUTF8));
        actionOpenTerrain->setText(QApplication::translate("MainWindow", "Open Terrain", 0, QApplication::UnicodeUTF8));
        actionClearRoads->setText(QApplication::translate("MainWindow", "Clear Roads", 0, QApplication::UnicodeUTF8));
        actionGenerateParcels->setText(QApplication::translate("MainWindow", "Generate Parcels", 0, QApplication::UnicodeUTF8));
        actionGenerateBuildings->setText(QApplication::translate("MainWindow", "Generate Buildings", 0, QApplication::UnicodeUTF8));
        actionGenerateVegetation->setText(QApplication::translate("MainWindow", "Generate Vegetation", 0, QApplication::UnicodeUTF8));
        actionModeParcel->setText(QApplication::translate("MainWindow", "Parcel", 0, QApplication::UnicodeUTF8));
        actionModePlaceType->setText(QApplication::translate("MainWindow", "Place Type", 0, QApplication::UnicodeUTF8));
        actionLoadPlaceTypes->setText(QApplication::translate("MainWindow", "Load Place Types", 0, QApplication::UnicodeUTF8));
        actionCameraDefault->setText(QApplication::translate("MainWindow", "Default", 0, QApplication::UnicodeUTF8));
        actionCameraCar->setText(QApplication::translate("MainWindow", "Car", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
