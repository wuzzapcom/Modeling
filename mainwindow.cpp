#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new ModelingModel)
{

    this->resize(620, 600);

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

    QAction *addRod = new QAction(tr("Pendulum"), this);
    addRod->setShortcut(QKeySequence::Open);
    addRod->setStatusTip("Add math pendulum");
    addRod->setIcon(QIcon(":pendulum.png"));
    connect(addRod, &QAction::triggered, this, &MainWindow::addRod);

    QAction *addStationaryPoint = new QAction(tr("Stationary point"), this);
    addStationaryPoint->setShortcut(QKeySequence::Open);
    addStationaryPoint->setStatusTip("Add stationary point");
    addStationaryPoint->setIcon(QIcon(":stationaryPoint"));
    connect(addStationaryPoint, &QAction::triggered, this, &MainWindow::addStationaryPoint);

    playPauseAction = new QAction(tr("Play/Pause"), this);
    playPauseAction->setShortcut(QKeySequence::Open);
    playPauseAction->setStatusTip("Start moving");
    playPauseAction->setIcon(QIcon(":/play.png"));
    connect(playPauseAction, &QAction::triggered, this, &MainWindow::changePlayPauseState);

    figuresToolbar = new QToolBar(this);
    figuresToolbar->setObjectName(QStringLiteral("testToolbar"));
    figuresToolbar->addAction(addMatPointAction);
    figuresToolbar->addAction(addSpringAction);
    figuresToolbar->addAction(addRod);
    figuresToolbar->addAction(addStationaryPoint);
    figuresToolbar->addAction(playPauseAction);
    figuresToolbar->setMovable(false);
    this->addToolBar(Qt::LeftToolBarArea, figuresToolbar);

}

void MainWindow::createCentralWidget(){

    QWidget *centralWidget = new OpenGLWidget(this, model);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    centralWidget->setMouseTracking(true);//qwidget::mapfromglobal
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

    openAction = new QAction(tr("&Load"), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Load saved file"));
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

    propertiesDock = new QDockWidget(tr("Properties"), this);

    propertiesDock->setAllowedAreas(Qt::RightDockWidgetArea);
    propertiesDock->setTitleBarWidget(new QWidget());
    propertiesDock->setFixedSize(80, 240); //about 60 pixels for 1 spin and 1 label

    QWidget *multiWidget = new QWidget();

    spin1 = new QSpinBox;
    label1 = new QLabel;
    label1->setText(tr("label1"));

    spin2 = new QSpinBox;
    label2 = new QLabel;
    label2->setText(tr("label2"));

    spin3 = new QSpinBox;
    label3 = new QLabel;
    label3->setText(tr("label3"));

    spin4 = new QSpinBox;
    label4 = new QLabel;
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

    propertiesDock->setVisible(false);

}

void MainWindow::mousePressEvent(QMouseEvent *event){

    if (event->button() == Qt::LeftButton){
        qInfo("left button pressed");

        Point point = getPointInOpenGLCoordinateFromMouseEvent(event);

        QVector<DrawableObject*> drawableObjects = this->model->getDrawableObjects();//assembleDrawableObjectVector();

        bool isCursorInObject = false;

        this->model->completeModel();

        for(int i = 0; i < drawableObjects.length(); i++){

            if (drawableObjects[i]->checkCursorInObject(point)){

                qInfo("Found cursor in object");

                if(this->model->getIncompletedObject() != nullptr
                        && drawableObjects[i] != this->model->getIncompletedObject()){

                    model->connectObjects(
                                drawableObjects[i],
                                this->model->getIncompletedObject()
                                );

                }

                this->model->setSelectedObject(drawableObjects[i]);
                this->centralWidget()->update();
                isCursorInObject = true;
                this->hideRightDock();
                this->addPropertiesToRightDockBySelectedObject();

                break;

            }
        }

        if (!isCursorInObject){

            this->hideRightDock();

            this->model->setSelectedObject(nullptr);

            this->centralWidget()->update();
        }

    }

    this->centralWidget()->update();

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

    qInfo("MainWindow::mouseMoveEvent()");

    Point point = getPointInOpenGLCoordinateFromMouseEvent(event);

    QVector<Spring*> springs = this->model->getSprings();
    for (int i = 0; i < springs.size(); i++)
        springs[i]->update();

    QVector<Rod*> rods = this->model->getRods();
    for (int i = 0; i < rods.size(); i++)
        rods[i]->update();

    if(this->model->getSelectedObject() != nullptr){

        this->model->getSelectedObject()->moveTo(point);
        this->centralWidget()->update();

    }

}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{

    qInfo("MainWindow::mouseReleaseEvent");

    this->centralWidget()->update();

}

void MainWindow::save()
{
    qInfo("MainWindow::save()");
    this->model->save();
}

void MainWindow::open(){
    qInfo("MainWindow::open()");
    this->model->load();
    this->centralWidget()->update();
}

void MainWindow::help(){}

void MainWindow::copy(){}

void MainWindow::paste(){}

void MainWindow::addMatPoint()
{
    qInfo("MainWindow::addMatPoint");

    this->model->addMaterialPoint();
    this->centralWidget()->update();

    addMatPointPropertiesToRightDock();
}

void MainWindow::addSpring()
{
    qInfo("MainWindow::addSpring");

    this->model->addSpring();
    this->centralWidget()->update();

    addSpringPropertiesToRightDock();
}

void MainWindow::addRod()
{
    qInfo("MainWindow::addRod");

    this->model->addRod();
    this->centralWidget()->update();
}

void MainWindow::addStationaryPoint()
{
    qInfo("MainWindow::addStationaryPoint");

    this->model->addStationalPoint();
    this->centralWidget()->update();
}

void MainWindow::changePlayPauseState()
{
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

void MainWindow::addPropertiesToRightDockBySelectedObject()
{
    if (this->model->getSelectedObject() == nullptr)
        return;

    switch(this->model->getSelectedObject()->getType()){
    case MATERIAL_POINT:
        addMatPointPropertiesToRightDock();
        break;
    case SPRING:
        addSpringPropertiesToRightDock();
        break;
    default:
        qInfo() << "MainWindow::addPropertienToRightDockBySelectedObject(). Object has no properties";
        break;
    }
}

void MainWindow::addMatPointPropertiesToRightDock()
{
    this->showRightDock();
    propertiesDock->setFixedSize(80, 120);

    spin1->setVisible(true);
    label1->setVisible(true);

    spin2->setVisible(true);
    label2->setVisible(true);

    spin1->disconnect();
    spin1->setValue(5);
    label1->setText("Radius");
    connect(spin1, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
        [=](int i){
        if (i > 5) spin1->setValue(5);
        else if (i < 1) spin1->setValue(1);
        else{
            if (this->model->getSelectedObject() == nullptr ||
                    this->model->getSelectedObject()->getType() != MATERIAL_POINT)
            {
                return;
            }
            ((MaterialPoint*)this->model->getSelectedObject())->setRadius(((float)i) / 10);
            this->centralWidget()->update();
        }

    });

    spin2->disconnect();
    spin2->setValue(5);
    label2->setText("Weight");
    connect(spin2, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
        [=](int i){
        if (i > 10) spin1->setValue(10);
        else if (i < 1) spin1->setValue(1);
        else{
            if (this->model->getSelectedObject() == nullptr ||
                    this->model->getSelectedObject()->getType() != MATERIAL_POINT)
            {
                return;
            }
            ((MaterialPoint*)this->model->getSelectedObject())->setWeight(i);
            this->centralWidget()->update();
        }

    });

    spin3->setVisible(false);
    label3->setVisible(false);

    spin4->setVisible(false);
    label4->setVisible(false);

}

void MainWindow::addSpringPropertiesToRightDock()
{
    this->showRightDock();
    propertiesDock->setFixedSize(80, 65);

    spin1->setVisible(true);
    label1->setVisible(true);

    spin1->disconnect();
    spin1->setValue(5);
    label1->setText("Rigidity");
    connect(spin1, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            [=](int i){
        if (i > 100) spin1->setValue(100);
        else if (i < 1) spin1->setValue(1);
        else{
            if (this->model->getSelectedObject() == nullptr ||
                    this->model->getSelectedObject()->getType() != SPRING)
            {
                return;
            }
            ((Spring*)this->model->getSelectedObject())->setRigidity((float)i);
            this->centralWidget()->update();
        }
    });

    spin2->setVisible(false);
    label2->setVisible(false);

    spin3->setVisible(false);
    label3->setVisible(false);

    spin4->setVisible(false);
    label4->setVisible(false);
}

void MainWindow::hideRightDock()
{
    if(!this->propertiesDock->isVisible())
        return;

    this->propertiesDock->setVisible(false);
    this->resize(this->size().width() - 80, this->size().height());

}

void MainWindow::showRightDock()
{
    if(this->propertiesDock->isVisible())
        return;

    this->resize(this->size().width() + 80, this->size().height());
    this->propertiesDock->setVisible(true);

}

Point MainWindow::getPointInOpenGLCoordinateFromMouseEvent(QMouseEvent *event)
{

    QPoint p = event->globalPos();

    p = centralWidget()->mapFromGlobal(p);

    return Point((((float)p.x()) / centralWidget()->contentsRect().width() - 0.5) * 2,
        (0.5 - ((float)p.y()) / centralWidget()->contentsRect().height()) * 2);

}

MainWindow::~MainWindow()
{
    delete ui;
}
