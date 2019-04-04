#include "qextendedpushbutton.h"

QExtendedPushButton::QExtendedPushButton(QWidget *parent, int place, QString value, bool logic):
    QPushButton(parent),
    place(place),
    value(value),
    logic(logic)
{
    connect(this,SIGNAL(clicked()),this,SLOT(handleClick()));
}

void QExtendedPushButton::handleClick(){
    emit buttonClicked(place,value,logic);
}
