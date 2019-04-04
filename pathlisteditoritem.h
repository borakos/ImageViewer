#ifndef PATHLISTEDITORITEM_H
#define PATHLISTEDITORITEM_H

#include <QTextEdit>
#include <QWidget>
#include "qextendedpushbutton.h"

class PathListEditorItem{
    QWidget *item, *parent;
    QTextEdit *text;
    QExtendedPushButton *deleteButton, *saveButton;
    int place, height, widthText, widthButton, spacing;

public:
    PathListEditorItem(QWidget *parent, QString text, int place, int height = 25, int widthText = 250, int widthButton = 50, int spacing = 5);
    ~PathListEditorItem();
};

#endif // PATHLISTEDITORITEM_H
