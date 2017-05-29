#include "miqlineedit.h"

MiQLineEdit::MiQLineEdit(QWidget *parent) : QLineEdit(parent)
{
    this->installEventFilter( this);
}

MiQLineEdit::MiQLineEdit(const MiQLineEdit &linea) : QLineEdit()  {
    this->setText(linea.text());
}

MiQLineEdit &MiQLineEdit::operator=(const MiQLineEdit &linea)  {
    this->setText(linea.text());
    return *this;
}

void MiQLineEdit::mousePressEvent(QMouseEvent *e)
{
    e->ignore();
}

bool MiQLineEdit::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type() == QEvent::MouseButtonPress) {
        return true;
    }

    if (e->type() == QEvent::KeyPress) {
        return true;
    }

//    if (e->type() == QEvent::FocusIn) {
//        return true;
//    }


    return QWidget::eventFilter(obj, e);
}


