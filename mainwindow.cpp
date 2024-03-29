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

    configureTimer();
    initializeRungeCutta();
}


#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);

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

    QAction *clearSpeedsAction = new QAction(tr("Clear speeds"), this);
    clearSpeedsAction->setStatusTip("Clear material point`s speeds");
    clearSpeedsAction->setIcon(QIcon(":/Speed.png"));
    connect(clearSpeedsAction, &QAction::triggered, this, &MainWindow::clearSpeeds);

    QAction *resetSystemAction = new QAction(tr("Reset system"), this);
    resetSystemAction->setStatusTip("Deletes all user input");
    resetSystemAction->setIcon(QIcon(":/Reset.png"));
    connect(resetSystemAction, &QAction::triggered, this, &MainWindow::resetSystem);

    switchGravitationAction = new QAction(tr("Switch gravitation"), this);
    switchGravitationAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    switchGravitationAction->setStatusTip("Switch gravitation");
    switchGravitationAction->setIcon(QIcon(":/Gravitation_OFF.png"));
    connect(switchGravitationAction, &QAction::triggered, this, &MainWindow::switchGravitation);

    playPauseAction = new QAction(tr("Play/Pause"), this);
    playPauseAction->setShortcut(QKeySequence::Open);
    playPauseAction->setStatusTip("Start moving");
    playPauseAction->setIcon(QIcon(":/pause.png"));
    connect(playPauseAction, &QAction::triggered, this, &MainWindow::changePlayPauseState);

    figuresToolbar = new QToolBar(this);
    figuresToolbar->setObjectName(QStringLiteral("testToolbar"));
    figuresToolbar->addAction(addMatPointAction);
    figuresToolbar->addAction(addSpringAction);
    figuresToolbar->addAction(addRod);
    figuresToolbar->addAction(addStationaryPoint);
    figuresToolbar->addAction(clearSpeedsAction);
    figuresToolbar->addAction(resetSystemAction);
    figuresToolbar->addAction(switchGravitationAction);
    figuresToolbar->addAction(playPauseAction);
    figuresToolbar->setMovable(false);
    this->addToolBar(Qt::LeftToolBarArea, figuresToolbar);

}

void MainWindow::createCentralWidget(){

    QWidget *centralWidget = new OpenGLWidget(this, model);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    centralWidget->setMouseTracking(true);
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

    editMenu->addAction(deleteAction);
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

    deleteAction = new QAction(tr("&Delete"), this);
    deleteAction->setShortcut(QKeySequence::Delete);
    deleteAction->setStatusTip(tr("Deletes selected object"));
    connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteObject);

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

void MainWindow::configureTimer()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateScene()));
    timer->start(17); //for about 60 FPS
}

void MainWindow::initializeRungeCutta()
{
    this->rungeCutta = new RungeCutta();
}

void MainWindow::updateRungeCutta()
{
    if (this->model->isModelCompleted())
        return;
    this->rungeCutta->resetState(
                this->model->createAccelerations(),
                this->model->getConnectablesPosition()
                );

}

void MainWindow::mousePressEvent(QMouseEvent *event){

    if (event->button() == Qt::LeftButton){
        qInfo("left button pressed");

        Point point = getPointInOpenGLCoordinateFromMouseEvent(event);

        QVector<DrawableObject*> drawableObjects = this->model->getDrawableObjects();

        bool isCursorInObject = false;

        this->model->completeModel();

        for(int i = 0; i < drawableObjects.length(); i++){

            if (drawableObjects[i]->checkCursorInObject(point)){

                qInfo("Found cursor in object");

                if(this->model->getIncompletedObject() != nullptr
                        && drawableObjects[i] != this->model->getIncompletedObject()){

                    this->model->connectObjects(
                                drawableObjects[i],
                                this->model->getIncompletedObject()
                                );
                    qInfo() << "CONNECT OBJECTS";
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
    this->updateRungeCutta();

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    qInfo("MainWindow::mouseMoveEvent()");

    Point point = getPointInOpenGLCoordinateFromMouseEvent(event);

    this->model->updateSpringsAndRods(true);

    if (this->model->getSelectedObject() != nullptr &&
            this->model->getSelectedObject()->getType() == MATERIAL_POINT &&
            this->model->getSpeedVectorArrow() != nullptr)
    {
        std::valarray<double> speed = this->model->getSpeedVectorArrow()->updateState(true, point);
        ((MaterialPoint*)this->model->getSelectedObject())->setSpeed(speed[0], speed[1]);
        this->centralWidget()->update();
    }
    else if (this->model->getSelectedObject() != nullptr)
    {
        this->model->getSelectedObject()->moveTo(point);
        this->centralWidget()->update();
    }
    this->updateRungeCutta();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    qInfo("MainWindow::mouseReleaseEvent");

    this->centralWidget()->update();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control)
    {
        qInfo("MainWindow::keyPressEvent(). Ctrl pressed");

        if (this->model->getSelectedObject() == nullptr ||
                this->model->getSelectedObject()->getType() != MATERIAL_POINT)
            return;

        Arrow *arrow = new Arrow();
        arrow->setConnected((MaterialPoint*) this->model->getSelectedObject());

        this->model->setSpeedVectorArrow(arrow);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control)
    {
        this->model->setSpeedVectorArrow(nullptr);
        delete this->model->getSpeedVectorArrow();
        this->centralWidget()->update();
    }
}

void MainWindow::save()
{
    qInfo("MainWindow::save()");
    this->model->save();
}

void MainWindow::open()
{
    qInfo("MainWindow::open()");
    this->model->load();
    updateRungeCutta();
    this->centralWidget()->update();
}

void MainWindow::deleteObject()
{
    qInfo("MainWindow::deleteObject()");
    if (this->model->getSelectedObject() != nullptr)
    {
        if (this->model->getSelectedObject()->getType() == MATERIAL_POINT ||
                this->model->getSelectedObject()->getType() == STATIONARY_POINT)
        {
            ConnectableObject *conn = (ConnectableObject*) this->model->getSelectedObject();
            QVector<PointableObject*> pointables = conn->getPointableObjects();

            for (PointableObject *pointable: pointables)
            {
                if (pointable->getFirstConnectable() == conn)
                    pointable->setFirstConnectable(nullptr);
                if (pointable->getSecondConnectable() == conn)
                    pointable->setSecondConnectable(nullptr);
            }
        }else if (this->model->getSelectedObject()->getType() == SPRING ||
                  this->model->getSelectedObject()->getType() == ROD)
        {
            PointableObject *pointable = (PointableObject*) this->model->getSelectedObject();
            if (pointable->getFirstConnectable() != nullptr)
            {
                for (PointableObject *p: pointable->getFirstConnectable()->getPointableObjects())
                {
                    if (p == pointable)
                        pointable->getFirstConnectable()->removeFromPointableObjects(p);//->getPointableObjects().removeOne(p);
                }
            }
            if (pointable->getSecondConnectable() != nullptr)
            {
                for (PointableObject *p: pointable->getSecondConnectable()->getPointableObjects())
                {
                    if (p == pointable)
                        pointable->getSecondConnectable()->removeFromPointableObjects(p);//getPointableObjects().removeOne(p);
                }
            }
        }
        this->model->removeObjectFromVectors(this->model->getSelectedObject());
        delete this->model->getSelectedObject();
    }

    this->centralWidget()->update();
    this->updateRungeCutta();
}

void MainWindow::help(){}

void MainWindow::copy(){}

void MainWindow::paste(){}

void MainWindow::addMatPoint()
{
    if (this->model->getIsPlaying()){
        this->changePlayPauseState();
        return;
    }
    qInfo("MainWindow::addMatPoint");

    this->model->addMaterialPoint();
    this->centralWidget()->update();

    addMatPointPropertiesToRightDock();

    this->updateRungeCutta();
}

void MainWindow::addSpring()
{
    if (this->model->getIsPlaying()){
        this->changePlayPauseState();
        return;
    }
    qInfo("MainWindow::addSpring");

    this->model->addSpring();
    this->centralWidget()->update();

    addSpringPropertiesToRightDock();
    this->updateRungeCutta();
}

void MainWindow::addRod()
{
    if (this->model->getIsPlaying()){
        this->changePlayPauseState();
        return;
    }
    qInfo("MainWindow::addRod");

    this->model->addRod();
    this->centralWidget()->update();
    this->updateRungeCutta();
}

void MainWindow::addStationaryPoint()
{
    if (this->model->getIsPlaying()){
        this->changePlayPauseState();
        return;
    }
    qInfo("MainWindow::addStationaryPoint");

    this->model->addStationalPoint();
    this->centralWidget()->update();
    this->updateRungeCutta();
}

void MainWindow::changePlayPauseState()
{
    if (model->getIsPlaying()){
        model->setPlaying(false);
        playPauseAction->setIcon(QIcon(":/pause.png"));
        playPauseAction->setStatusTip("Stop moving");
        this->model->getLogger()->stopLogging();
    }
    else{
        if (this->model->isModelCorrect())
        {
            this->updateRungeCutta();
            model->setPlaying(true);
            playPauseAction->setIcon(QIcon(":/play.png"));
            playPauseAction->setStatusTip("Start moving");
            this->model->getLogger()->startLogging(this->model->getMaterialPoints().size());
        }
        else
        {
            playPauseAction->setStatusTip("Model is not correct");
            this->update();
        }

    }
}

void MainWindow::switchGravitation()
{
    if (this->model->getIsPlaying()){
        this->changePlayPauseState();
        return;
    }
    bool isEnabled = this->model->switchGravitation();
    if (isEnabled)
    {
        switchGravitationAction->setIcon(QIcon(":/Gravitation_ON.png"));
    }
    else
    {
        switchGravitationAction->setIcon(QIcon(":/Gravitation_OFF.png"));
    }
    this->updateRungeCutta();
}

void MainWindow::clearSpeeds()
{
    if (this->model->getIsPlaying()){
        this->changePlayPauseState();
        return;
    }
    this->model->resetMaterialPointsSpeeds();
}

void MainWindow::resetSystem()
{
    if (this->model->getIsPlaying()){
        this->changePlayPauseState();
        return;
    }
    delete this->model;
    delete this->rungeCutta;
    this->model = new ModelingModel();
    this->rungeCutta = new RungeCutta();
    delete this->centralWidget();
    this->createCentralWidget();
    switchGravitationAction->setIcon(QIcon(":/Gravitation_OFF.png"));
    this->centralWidget()->update();
}

void MainWindow::updateScene()
{
    this->model->updateSpringsAndRods(false);

    if (!this->model->getIsPlaying())
        return;

    this->rungeCutta->updateStates(this->model->getConnectablesPosition());
    std::valarray<double> res = this->rungeCutta->rungeCutta();

    this->model->getLogger()->log(
                res,
                this->model->countKineticEnergy(),
                this->model->countPotentialEnergy()
                );

    this->model->applySpeedsAndCoordinatesToModel(res);
    this->model->updateSpringsAndRods(false);

    this->centralWidget()->update();
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
    spin1->setValue(1);
    label1->setText("Radius");
    connect(spin1, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
        [=](int i){
        if (i > 5) spin1->setValue(5);
        else if (i < 1) spin1->setValue(1);
        else{
            if (this->model->getIsPlaying()){
                this->changePlayPauseState();
                return;
            }
            if (this->model->getSelectedObject() == nullptr ||
                    this->model->getSelectedObject()->getType() != MATERIAL_POINT)
            {
                return;
            }
            ((MaterialPoint*)this->model->getSelectedObject())->setRadius(((double)i) / 10);
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
            if (this->model->getIsPlaying()){
                this->changePlayPauseState();
                return;
            }
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
    propertiesDock->setFixedSize(80, 70/*120*/);

    spin1->setVisible(true);
    label1->setVisible(true);

    spin1->disconnect();
    spin1->setValue(20);
    label1->setText("Rigidity");
    connect(spin1, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            [=](int i){
        if (i > 100) spin1->setValue(100);
        else if (i < 1) spin1->setValue(1);
        else{
            if (this->model->getIsPlaying()){
                this->changePlayPauseState();
                return;
            }
            if (this->model->getSelectedObject() == nullptr ||
                    this->model->getSelectedObject()->getType() != SPRING)
            {
                return;
            }
            ((Spring*)this->model->getSelectedObject())->setRigidity((double)i);
            this->centralWidget()->update();
        }
    });

    spin2->setVisible(false);
    label2->setVisible(false);

    /*
    spin2->setVisible(true);
    label2->setVisible(true);

    spin2->disconnect();
    spin2->setValue(1);
    label2->setText("Default length");
    connect(spin2, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            [=](int i){
        if (i > 10) spin2->setValue(10);
        else if (i < 1) spin2->setValue(1);
        else{
            if (this->model->getSelectedObject() == nullptr ||
                    this->model->getSelectedObject()->getType() != SPRING)
            {
                return;
            }
            //((Spring*) this->model->getSelectedObject())->setDefaultLength((double)i);
            this->centralWidget()->update();
        }
    });
    */

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

    return Point((((double)p.x()) / centralWidget()->contentsRect().width() - 0.5) * 2,
        (0.5 - ((double)p.y()) / centralWidget()->contentsRect().height()) * 2);

}

MainWindow::~MainWindow()
{
    delete model;
    delete rungeCutta;
    delete ui;
}
