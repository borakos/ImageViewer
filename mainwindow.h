#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openImageMenu_triggered();

    void on_savePathMenu_triggered();

    void on_loadImageMenu_triggered();

    void on_imageWindowMenu_triggered();

    void on_settingsWindowMenu_triggered();

    void on_delete_path(int, QString, bool);

private:
    Ui::MainWindow *ui;
    QImage mainImage;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *item;
    QString actualPath;
    QStringList savedPath;
    QWidget **savedPathEdit;
    int windowState;
    void setDefaultImage(QImage *);
    void setMainImage(QString);
    void out(QString);
    void loadSavedPaths();
    void saveSavedPaths();
    void changeWindowState(int );
    void placePathEdit();

protected:
    void resizeEvent(QResizeEvent *);
};

#endif // MAINWINDOW_H
