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
//#include "modelingmodel.h"
#include "openglwidget.h"
#include <QtDebug>
//#include "springableobject.h"

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
    QAction *playPauseAction;

    //Right dock widgets
    QSpinBox *spin1;
    QLabel *label1;
    QSpinBox *spin2;
    QLabel *label2;
    QSpinBox *spin3;
    QLabel *label3;
    QSpinBox *spin4;
    QLabel *label4;

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
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

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
    void paste();
    void help();
    void open();

    void addMatPoint();
    void addSpring();
    void addRod();
    void addStationaryPoint();

    void changePlayPauseState();


};

#endif // MAINWINDOW_H
