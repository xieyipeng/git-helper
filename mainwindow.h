#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_choosePath_clicked();

    void on_gitAdd_clicked();

    void on_gitStatus_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
