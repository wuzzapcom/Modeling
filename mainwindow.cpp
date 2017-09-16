#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qgroupbox.h"
#include "qpushbutton.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    createCentralWidget();
    createStatusBar();
    createToolbar();
    createMenus();

    this->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));

//    http://doc.qt.io/qt-5/qtwidgets-mainwindows-menus-example.html

    ui->setupUi(this);

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

}

MainWindow::~MainWindow()
{
    delete ui;
}
