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

/**
 * @brief executeLinuxCmd
 * @param strCmd
 * @return
 */
QString executeLinuxCmd(QString strCmd)
{
    QProcess p;
    p.start("bash", QStringList() <<"-c" << strCmd);
    p.waitForFinished();
    QString strResult = p.readAllStandardOutput();
    return strResult;
}

/**
 * @brief MainWindow::on_choosePath_clicked
 */
void MainWindow::on_choosePath_clicked()
{
    QString dirpath = QFileDialog::getExistingDirectory(this, "选择目录", "/home/", QFileDialog::ShowDirsOnly);
    ui->pathShow->setText(dirpath);
}

/**
 * @brief isPath
 * @param path
 * @return
 */
bool isPath(QString path){
    if(path.isEmpty()){
        return false;
    }
    // 确定文件和文件夹是否存在和访问权限
    // _AccessMode参数：  00表示只判断是否存在
    //                   02表示文件是否可执行
    //                   04表示文件是否可写
    //                   06表示文件是否可读
    // 有指定访问权限则返回0，否则函数返回-1
    if(access(path.toStdString().data(),00)==-1){
        return false;
    }
    return true;
}

/**
 * @brief MainWindow::on_gitAdd_clicked
 */
void MainWindow::on_gitAdd_clicked()
{
    if(!isPath(ui->pathShow->text())){
        ui->statusMsg->setText("path error!");
        return;
    }
    QString strResult = executeLinuxCmd("git -C " + ui->pathShow->text() + " add .");
    ui->statusMsg->setText(strResult);
}

/**
 * @brief MainWindow::on_gitStatus_clicked
 */
void MainWindow::on_gitStatus_clicked()
{
    if(!isPath(ui->pathShow->text())){
        ui->statusMsg->setText("path error!");
        return;
    }
    QString strResult = executeLinuxCmd("git status");
    ui->statusMsg->setText(strResult);
}

/**
 * @brief MainWindow::on_gitCommit_clicked
 */
void MainWindow::on_gitCommit_clicked()
{
    QString commit_msg = ui->commitMsg->text();
    if(commit_msg.isEmpty()){
        ui->statusMsg->setText("commit context is empty!");
        return;
    }
    QString strResult = executeLinuxCmd("git -C " + ui->pathShow->text() + " commit -m \""+commit_msg+"\"");
    ui->statusMsg->setText(strResult);
}

/**
 * @brief MainWindow::on_gitPush_clicked
 */
void MainWindow::on_gitPush_clicked()
{
    QString strResult = executeLinuxCmd("git -C " + ui->pathShow->text() + " push -u");
    ui->statusMsg->setText(strResult);
}
