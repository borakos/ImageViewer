#include "pathlisteditoritem.h"

PathListEditorItem::PathListEditorItem(QWidget *parent, QString text, int place, int height, int widthText, int widthButton, int spacing):
    parent(parent),
    place(place),
    height(height),
    widthText(widthText),
    widthButton(widthButton),
    spacing(spacing)
{
    item = new QWidget(parent);
    this->text = new QTextEdit(text,item);
    this->text->setGeometry(0, 0, widthText, height);
    saveButton = new QExtendedPushButton(item, place);
    saveButton->setGeometry(0, widthText+spacing, widthButton, height);
    deleteButton = new QExtendedPushButton(item, place);
    deleteButton->setGeometry(0, widthText+widthButton+2*spacing, widthButton, height);
}

PathListEditorItem::~PathListEditorItem(){
    if(deleteButton != nullptr){
        delete deleteButton;
    }
    if(saveButton != nullptr){
        delete saveButton;
    }
    if(text != nullptr){
        delete text;
    }
    if(item != nullptr){
        delete item;
    }
}
