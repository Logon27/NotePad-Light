#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    setWindowTitle("Notepad Light");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
    setWindowTitle("Notepad Light");
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    //retrieve file info
    QFileInfo fileInfo(file.fileName());
    //pull the file name without the path
    QString filename(fileInfo.fileName());
    currentFile = fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
        //QMessageBox::warning(this, "Warning", &"Cannot open file : " [ file.error()]);
        return;
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    QFile file(currentFile);
    if(!file.exists()) {
        return;
    }
    //retrieve file info
    QFileInfo fileInfo(file.fileName());
    //pull the file name without the path
    QString filename(fileInfo.fileName());
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        //QMessageBox::warning(this, "Warning", &"Cannot save file : " [ file.error()]);
        return;
    }
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
    QMessageBox::information(this, "Alert", "Your file has been saved.");
}

void MainWindow::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);
    //retrieve file info
    QFileInfo fileInfo(file.fileName());
    //pull the file name without the path
    QString filename(fileInfo.fileName());
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        //QMessageBox::warning(this, "Warning", &"Cannot save file : " [ file.error()]);
        return;
    }
    currentFile = fileName;
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
    QMessageBox::information(this, "Alert", "Your file has been saved.");
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

