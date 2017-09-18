#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new ModelingModel)
{

    this->resize(600, 600);

    createCentralWidget();
    createStatusBar();
    createToolbar();
    createActions();
    createMenus();
    createRightDock();

    this->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));

}


#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(copyAction);
    menu.addAction(pasteAction);

    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU


void MainWindow::createStatusBar()
{

    statusBar = new QStatusBar(this);
    statusBar->setObjectName(QStringLiteral("statusBar"));
    this->setStatusBar(statusBar);
    this->statusBar->showMessage("Hello world");

}

void MainWindow::createToolbar()
{

    QAction *addMatPointAction = new QAction(tr("Mat. point"), this);
    addMatPointAction->setShortcut(QKeySequence::Open);
    addMatPointAction->setStatusTip("Add material point");
    addMatPointAction->setIcon(QIcon(":/matPoint.png"));
    connect(addMatPointAction, &QAction::triggered, this, &MainWindow::addMatPoint);

    QAction *addSpringAction = new QAction(tr("Spring"), this);
    addSpringAction->setShortcut(QKeySequence::Open);
    addSpringAction->setStatusTip("Add spring");
    addSpringAction->setIcon(QIcon(":/spring.png"));
    connect(addSpringAction, &QAction::triggered, this, &MainWindow::addSpring);

    playPauseAction = new QAction(tr("Play/Pause"), this);
    playPauseAction->setShortcut(QKeySequence::Open);
    playPauseAction->setStatusTip("Start moving");
    playPauseAction->setIcon(QIcon(":/play.png"));
    connect(playPauseAction, &QAction::triggered, this, &MainWindow::changePlayPauseState);

    figuresToolbar = new QToolBar(this);
    figuresToolbar->setObjectName(QStringLiteral("testToolbar"));
    figuresToolbar->addAction(addMatPointAction);
    figuresToolbar->addAction(addSpringAction);
    figuresToolbar->addAction(playPauseAction);
    figuresToolbar->setMovable(false);
    this->addToolBar(Qt::LeftToolBarArea, figuresToolbar);

}

void MainWindow::createCentralWidget(){

    QWidget *centralWidget = new OpenGLWidget(this, model);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    setCentralWidget(centralWidget);

}

void MainWindow::createMenus()
{

    menuBar = new QMenuBar(this);
    menuBar->setObjectName(QStringLiteral("menuBar"));

    menuModeling = new QMenu(menuBar);
    menuModeling->setObjectName(QStringLiteral("menuModeling"));
    this->setMenuBar(menuBar);

    menuModeling->setTitle(QApplication::translate("MainWindow", "Modeling", Q_NULLPTR));

    fileMenu = menuBar->addMenu(tr("&File"));

    fileMenu->addAction(saveAction);
    fileMenu->addAction(openAction);

    editMenu = menuBar->addMenu(tr("&Edit"));

    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);

    helpMenu = menuBar->addMenu(tr("&Help"));

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

void MainWindow::createRightDock(){

    QDockWidget *propertiesDock = new QDockWidget(tr("Properties"), this);

    propertiesDock->setAllowedAreas(Qt::RightDockWidgetArea);
    propertiesDock->setTitleBarWidget(new QWidget());
    propertiesDock->setFixedSize(80, 240); //about 60 pixels for 1 spin and 1 label

    QWidget *multiWidget = new QWidget();

    QSpinBox *spin1 = new QSpinBox;
    QLabel *label1 = new QLabel;
    label1->setText(tr("label1"));
    QSpinBox *spin2 = new QSpinBox;
    QLabel *label2 = new QLabel;
    label2->setText(tr("label2"));
    QSpinBox *spin3 = new QSpinBox;
    QLabel *label3 = new QLabel;
    label3->setText(tr("label3"));
    QSpinBox *spin4 = new QSpinBox;
    QLabel *label4 = new QLabel;
    label4->setText(tr("label4"));

    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(label1);
    layout->addWidget(spin1);
    layout->addWidget(label2);
    layout->addWidget(spin2);
    layout->addWidget(label3);
    layout->addWidget(spin3);
    layout->addWidget(label4);
    layout->addWidget(spin4);

    multiWidget->setLayout(layout);

    propertiesDock->setWidget(multiWidget);

    this->addDockWidget(Qt::RightDockWidgetArea, propertiesDock);

}

void MainWindow::save(){}

void MainWindow::open(){}

void MainWindow::help(){}

void MainWindow::copy(){}

void MainWindow::paste(){}

void MainWindow::addMatPoint(){}

void MainWindow::addSpring(){}

void MainWindow::changePlayPauseState(){

    if (model->getIsPlaying()){
        model->setPlaying(false);
        playPauseAction->setIcon(QIcon(":/pause.png"));
        playPauseAction->setStatusTip("Stop moving");
    }
    else{
        model->setPlaying(true);
        playPauseAction->setIcon(QIcon(":/play.png"));
        playPauseAction->setStatusTip("Start moving");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
