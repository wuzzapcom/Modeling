#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>

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
    QToolBar *figuresToolbar;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;

    QActionGroup *alignmedGroup;

    QAction *saveAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *helpAction;
    QAction *openAction;


    void createStatusBar();
    void createCentralWidget();
    void createToolbar();
    void createMenus();
    void createPlayPause();
    void createPropertiesWidget();
    void createActions();

private slots:

    void save();
    void copy();
    void paste();
    void help();
    void open();

};

#endif // MAINWINDOW_H
