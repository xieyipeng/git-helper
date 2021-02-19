#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    git_config();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::git_config()
{
    MainWindow::git_repositories.append("/home/xieyipeng/code/git-helper");
    MainWindow::git_repositories.append("/home/xieyipeng/code/Ng-DeepLearning");
    MainWindow::git_repositories.append("/home/xieyipeng/code/Ng-MachineLearning");
    ui->comboBox->addItems(MainWindow::git_repositories);
}

/**
 * @brief executeLinuxCmd
 * @param strCmd
 * @return
 */
QString MainWindow::executeLinuxCmd(QString strCmd)
{
    QProcess p;
    p.start("bash", QStringList() << "-c" << strCmd);
    p.waitForFinished();
    QString strResult = p.readAllStandardOutput();
    return strResult;
}

/**
 * @brief isFloderExist
 * @param path
 * @return
 */
bool MainWindow::isFloderExist(QString path)
{
    DIR *dp;
    if ((dp = opendir(path.toStdString().data())) == NULL)
    {
        return false;
    }

    closedir(dp);
    return true;
}

bool MainWindow::isFileExist(std::string path)
{
    if (access(path.data(), F_OK) == -1)
    {
        return false;
    }
    return true;
}

/**
 * @brief MainWindow::on_gitAdd_clicked
 */
void MainWindow::on_gitAdd_clicked()
{
    if (!isFloderExist(ui->comboBox->currentText()))
    {
        ui->statusMsg->setText("path error!");
        return;
    }
    QString strResult = executeLinuxCmd("git -C " + ui->comboBox->currentText() + " add .");
    ui->statusMsg->setText(strResult);
}

/**
 * @brief MainWindow::on_gitStatus_clicked
 */
void MainWindow::on_gitStatus_clicked()
{
    if (!isFloderExist(ui->comboBox->currentText()))
    {
        ui->statusMsg->setText("path error!");
        return;
    }
    QString strResult = executeLinuxCmd("git -C " + ui->comboBox->currentText() + " status");
    ui->statusMsg->setText(strResult);
}

/**
 * @brief MainWindow::on_gitCommit_clicked
 */
void MainWindow::on_gitCommit_clicked()
{
    QString commit_msg = ui->commitMsg->text();
    if (commit_msg.isEmpty())
    {
        ui->statusMsg->setText("commit context is empty!");
        return;
    }
    QString strResult = executeLinuxCmd("git -C " + ui->comboBox->currentText() + " commit -m \"" + commit_msg + "\"");
    ui->statusMsg->setText(strResult);
}

/**
 * @brief MainWindow::on_gitPush_clicked
 */
void MainWindow::on_gitPush_clicked()
{
    QString strResult = executeLinuxCmd("git -C " + ui->comboBox->currentText() + " push -u");
    ui->statusMsg->setText(strResult);
    ui->commitMsg->clear();
}
