#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QList>
#include <QString>
#include <unistd.h>
#include <dirent.h>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QList<QString> git_repositories;

    void git_config();
    bool isFileExist(std::string path);
    bool isFloderExist(QString path);
    QString executeLinuxCmd(QString strCmd);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_gitAdd_clicked();

    void on_gitStatus_clicked();

    void on_gitCommit_clicked();

    void on_gitPush_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
