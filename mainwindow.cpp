#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setDefaultImage(&mainImage);
    scene = new QGraphicsScene();
    item = new QGraphicsPixmapItem(QPixmap::fromImage(mainImage));
    scene->addItem(item);
    ui->mainImageView->setScene(scene);
}

MainWindow::~MainWindow(){
    delete ui;
    delete item;
    delete scene;
}

void MainWindow::on_openImageMenu_triggered(){
    QUrl url("D:/");
    QString fileName = QFileDialog::getOpenFileUrl(this,"Open image file",url).toString();
    if(fileName != nullptr){
        fileName.replace("file:///","");
        setMainImage(fileName);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event){
    ui->mainImageView->resize(this->width(),this->height()-21);
}

void MainWindow::setMainImage(QString path){
    mainImage = QImage(path);
    if(mainImage.isNull()){
        QMessageBox messageBox;
        messageBox.critical(this,"Error","Cannot read image file, please check the file or the extension");
        messageBox.setFixedSize(500,200);
    }else {
        actualPath=path;
        if(item != nullptr){
            scene->removeItem(item);
            delete item;
        }
        item = new QGraphicsPixmapItem(QPixmap::fromImage(mainImage));
        scene->addItem(item);
    }
}

void MainWindow::setDefaultImage(QImage *image){
    *image = QImage("Resources/default_back.png");
    actualPath = "none";
    if(image->isNull()){
        QMessageBox messageBox;
        messageBox.critical(this,"Error","Cannot read image file, please check the file or the extension");
        messageBox.setFixedSize(500,200);
    }
}

void MainWindow::out(QString string){
    QTextStream out(stdout);
    out << string << endl;
}

void MainWindow::on_savePathMenu_triggered()
{
    if(actualPath != "none"){
        savedPath.append(actualPath);
    }
}

void MainWindow::on_loadImageMenu_triggered()
{
    if(!savedPath.isEmpty()){
        bool ok;
        QString fileName = QInputDialog::getItem(this,"Select file","File paths",savedPath,0,false,&ok);
        if(ok && !fileName.isEmpty()){
            setMainImage(fileName);
        }
    }else{
        QMessageBox messageBox;
        messageBox.information(this,"Information","There is no saved path.");
        messageBox.setFixedSize(500,200);
    }
}

void MainWindow::loadSavedPaths(){
    QFile inputFile("Resources/saved_paths.txt");
    //inputFile.open()
}
