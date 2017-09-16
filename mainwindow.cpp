#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qgroupbox.h"
#include "qpushbutton.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    this->resize(600, 600);

    createCentralWidget();
    createStatusBar();
    createToolbar();
    createActions();
    createMenus();

    this->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));

//    http://doc.qt.io/qt-5/qtwidgets-mainwindows-menus-example.html

}

void MainWindow::createStatusBar()
{

    QStatusBar *statusBar = new QStatusBar(this);
    statusBar->setObjectName(QStringLiteral("statusBar"));
    this->setStatusBar(statusBar);
    this->statusBar()->showMessage("Hello world");

}

void MainWindow::createToolbar()
{

    QAction *testAction = new QAction(tr("Close"), this);
    testAction->setShortcut(QKeySequence::Open);
    testAction->setStatusTip("Close");
    connect(testAction, &QAction::triggered, this, &MainWindow::close);


    figuresToolbar = new QToolBar(this);
    figuresToolbar->setObjectName(QStringLiteral("testToolbar"));
    figuresToolbar->addAction(testAction);
    figuresToolbar->setMovable(false);
    this->addToolBar(Qt::LeftToolBarArea, figuresToolbar);

}

void MainWindow::createCentralWidget(){

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    setCentralWidget(centralWidget);

}

void MainWindow::createMenus()
{

    QMenuBar *menuBar = new QMenuBar(this);
    menuBar->setObjectName(QStringLiteral("menuBar"));
    QMenu *menuModeling = new QMenu(menuBar);
    menuModeling->setObjectName(QStringLiteral("menuModeling"));
    this->setMenuBar(menuBar);

    menuModeling->setTitle(QApplication::translate("MainWindow", "Modeling", Q_NULLPTR));

    QMenu *fileMenu = menuBar->addMenu(tr("&File"));

    fileMenu->addAction(saveAction);
    fileMenu->addAction(openAction);

    QMenu *editMenu = menuBar->addMenu(tr("&Edit"));

    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);

    QMenu *helpMenu = menuBar->addMenu(tr("&Help"));

    helpMenu->addAction(helpAction);


}

void MainWindow::createActions(){

    openAction = new QAction(tr("&Open"), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open new file"));
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save file"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::save);

    helpAction = new QAction(tr("&Help"), this);
    helpAction->setShortcut(QKeySequence::HelpContents);
    helpAction->setStatusTip(tr("Show help"));
    connect(helpAction, &QAction::triggered, this, &MainWindow::help);

    copyAction = new QAction(tr("&Copy"), this);
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip("Copy selected objects");
    connect(copyAction, &QAction::triggered, this, &MainWindow::copy);

    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip("Paste objects");
    connect(copyAction, &QAction::triggered, this, &MainWindow::paste);


}

void MainWindow::save(){}

void MainWindow::open(){}

void MainWindow::help(){}

void MainWindow::copy(){}

void MainWindow::paste(){}

MainWindow::~MainWindow()
{
    delete ui;
}
