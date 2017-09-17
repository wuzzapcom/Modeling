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
#include "modelingmodel.h"
#include "openglwidget.h"

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

    QStatusBar *statusBar;

    QToolBar *figuresToolbar;

    QMenuBar *menuBar;

    QMenu *menuModeling;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;

    QActionGroup *alignmedGroup;

    QAction *saveAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *helpAction;
    QAction *openAction;
    QAction *playPauseAction;


    void createStatusBar();
    void createCentralWidget();
    void createToolbar();
    void createMenus();
    void createPlayPause();
    void createPropertiesWidget();
    void createActions();
    void createRightDock();
    void createBottomDock();

private slots:

    void save();
    void copy();
    void paste();
    void help();
    void open();

    void addMatPoint();
    void addSpring();

    void changePlayPauseState();

};

#endif // MAINWINDOW_H
