#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QDir>
#include<QMessageBox>
#include<QDateTime>
#include<QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Browse_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Libre Office File"), "",tr("Libre Office File (*.odt);;All Files (*)"));
    ui->lineEdit->setText(fileName);
}

void MainWindow::on_pushButton_upload_clicked()
{
    //current working directory
    QString location = QDir::currentPath() + "/uploads";
    qDebug() << "Current working Dir:" +location ;

    //create directory if not exist
    if (! QDir(location).exists())
    {
        QDir().mkdir(location);
        qDebug() << "Creating Path:" +location ;
    }

    //source path
    QString source = ui->lineEdit->text();

    //get file name to append to destination path
    QFileInfo fi(source);
    QString name = fi.fileName();

    //to make filename unique appending timestamp
    QString time = QString::number(QDateTime::currentMSecsSinceEpoch());

    //make to be full destination file path
    QString destination = QDir(location).filePath(time + "_" + name);

    qDebug() << "Destination:" +destination;

    bool status =  QFile::copy(ui->lineEdit->text(),destination);
    if(status)
    {
        QMessageBox::information(this,"Upload Status","File Uploaded Successfully at " + location);
        ui->lineEdit->setText("");
    }else{
        QMessageBox::warning(this,"Upload Status","File Upload at " + location + " Failed");
    }
}
