#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QToolBar *figuresToolbar;


    void createStatusBar();
    void createCentralWidget();
    void createToolbar();
    void createMenus();
    void createPlayPause();
    void createPropertiesWidget();

};

#endif // MAINWINDOW_H
