#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QTextStream>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QScrollBar>
#include "qextendedpushbutton.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->settingsMenu->setVisible(false);
    windowState = 0;
    setDefaultImage(&mainImage);
    scene = new QGraphicsScene();
    item = new QGraphicsPixmapItem(QPixmap::fromImage(mainImage));
    scene->addItem(item);
    ui->mainImageView->setScene(scene);
    loadSavedPaths();
}

MainWindow::~MainWindow(){
    saveSavedPaths();
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
    switch (windowState) {
        case 0: ui->mainImageView->resize(this->width(),this->height()-21);break;
        case 1: ui->settingsMenu->resize(this->width(),this->height()-21);break;
    }
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
    inputFile.open(QIODevice::ReadOnly);
    if(inputFile.isOpen()){
        QTextStream stream(&inputFile);
        QString line = stream.readLine();
        while(!line.isNull()){
            savedPath.append(line);
            line = stream.readLine();
        }
        inputFile.close();
    }else{
        QMessageBox messageBox;
        messageBox.warning(this,"Warning","Cannot load saved paths.");
        messageBox.setFixedSize(500,200);
    }
}


void MainWindow::saveSavedPaths(){
    QFile outputFile("Resources/saved_paths.txt");
    outputFile.open(QIODevice::WriteOnly | QIODevice::Text);
    if(outputFile.isOpen()){
        QTextStream stream(&outputFile);
        for(int i=0;i<savedPath.length();i++){
            stream << savedPath[i] << endl;
        }
        outputFile.close();
    }else{
        QMessageBox messageBox;
        messageBox.warning(this,"Warning","Cannot save saved paths.");
        messageBox.setFixedSize(500,200);
    }
}

void MainWindow::changeWindowState(int state){
    windowState = state;
    switch (state) {
        case 0: {
            ui->mainImageView->resize(this->width(),this->height()-21);
            ui->mainImageView->setVisible(true);
            ui->settingsMenu->setVisible(false);
        }break;
        case 1: {
            placePathEdit();
            ui->settingsMenu->resize(this->width(),this->height()-21);
            ui->settingsMenu->setVisible(true);
            ui->mainImageView->setVisible(false);
        }break;
    }
}

void MainWindow::placePathEdit(){
    QTextEdit *text;
    QWidget *item;
    QExtendedPushButton *button;
    for(int i=0;i<10;i++){
        item = new QWidget();
        text = new QTextEdit();
        button = new QExtendedPushButton(item,i);
        text->setText("Hello");
        text->resize(200,25);
        text->setParent(item);
        button->setText("Delete");
        button->resize(50,25);
        button->move(205,0);
        connect(button,SIGNAL(buttonClicked(int, QString, bool)),this,SLOT(on_delete_path(int, QString, bool)));
        item->move(0,i*30);
        item->setParent(ui->listWidget);
    }
}

void MainWindow::on_delete_path(int place, QString value, bool logic){
    out(QString::number(place));
}

void MainWindow::on_imageWindowMenu_triggered()
{
    changeWindowState(0);
}

void MainWindow::on_settingsWindowMenu_triggered()
{
    changeWindowState(1);
}
