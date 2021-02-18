#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString executeLinuxCmd(QString strCmd)
{
    QProcess p;
    p.start("bash", QStringList() <<"-c" << strCmd);
    p.waitForFinished();
    QString strResult = p.readAllStandardOutput();
    return strResult;
}

void MainWindow::on_choosePath_clicked()
{
    QString dirpath = QFileDialog::getExistingDirectory(this, "选择目录", "/home/", QFileDialog::ShowDirsOnly);
    ui->pathShow->setText(dirpath);
}

void MainWindow::on_gitAdd_clicked()
{
    QString strResult = executeLinuxCmd("git -C " + ui->pathShow->text() + " add .");
    ui->statusMsg->setText(strResult);
}

void MainWindow::on_gitStatus_clicked()
{
    QString strResult = executeLinuxCmd("git status");
    ui->statusMsg->setText(strResult);
}
