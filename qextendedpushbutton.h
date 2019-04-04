#ifndef QEXTENDEDPUSHBUTTON_H
#define QEXTENDEDPUSHBUTTON_H
#include <QPushButton>
#include <QString>

class QExtendedPushButton : public QPushButton{
    Q_OBJECT
private:
    int place;
    QString value;
    bool logic;

public:
    QExtendedPushButton(QWidget *parent = nullptr, int place = 0, QString value = "", bool logic = false);

 signals:
    void buttonClicked(int, QString, bool);

 private slots:
    void handleClick();
};

#endif // QEXTENDEDPUSHBUTTON_H
