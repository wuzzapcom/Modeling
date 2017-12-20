#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include <QDockWidget>
#include <QSpinBox>
#include <QLabel>
#include <QOpenGLWidget>
#include <QContextMenuEvent>
#include <QVBoxLayout>
#include <QTimer>
#include "openglwidget.h"
#include <QtDebug>
#include <thread>
#include "rungecutta.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU

private:
    Ui::MainWindow *ui;

    ModelingModel *model;

    //Bars
    QStatusBar *statusBar;
    QToolBar *figuresToolbar;
    QMenuBar *menuBar;

    //Docks
    QDockWidget *propertiesDock;

    //Menus
    QMenu *menuModeling;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;

    QActionGroup *alignmedGroup;

    //Actions
    QAction *saveAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *helpAction;
    QAction *openAction;
    QAction *switchGravitationAction;
    QAction *playPauseAction;
    QAction *deleteAction;

    //Right dock widgets
    QSpinBox *spin1;
    QLabel *label1;
    QSpinBox *spin2;
    QLabel *label2;
    QSpinBox *spin3;
    QLabel *label3;
    QSpinBox *spin4;
    QLabel *label4;

    QTimer *timer;
    RungeCutta *rungeCutta;

    //configure updating scene
    void configureTimer();
    void initializeRungeCutta();
    void updateRungeCutta();

    //Basic interface creators
    void createStatusBar();
    void createCentralWidget();
    void createToolbar();
    void createMenus();
    void createPlayPause();
    void createPropertiesWidget();
    void createActions();
    void createRightDock();
    void createBottomDock();

    //Mouse events
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    //Configuring right dock
    void addPropertiesToRightDockBySelectedObject();
    void addMatPointPropertiesToRightDock();
    void addSpringPropertiesToRightDock();

    void hideRightDock();
    void showRightDock();

    //helpers functions
    Point getPointInOpenGLCoordinateFromMouseEvent(QMouseEvent *event);
//    QVector<DrawableObject*> assembleDrawableObjectVector();

private slots:

    void save();
    void copy();
    void deleteObject();
    void paste();
    void help();
    void open();

    void updateScene();

    void addMatPoint();
    void addSpring();
    void addRod();
    void addStationaryPoint();

    void changePlayPauseState();
    void switchGravitation();


};

#endif // MAINWINDOW_H
