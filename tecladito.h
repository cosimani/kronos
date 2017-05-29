#ifndef TECLADITO_H
#define TECLADITO_H

#include <QWidget>
#include <QPainter>
#include <QFont>
#include <QColor>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>

#include "numerito.h"

class Tecladito : public QWidget
{
    Q_OBJECT
public:
    explicit Tecladito(QWidget *parent = 0);
    void dimensionarTeclado();

protected:
    void paintEvent(QPaintEvent *);

private:
    Numerito * num0, * num1, * num2, * num3, * num4, * num5,
             * num6, * num7, * num8, * num9, * numEnter, * numBorrar;


signals:
    void signal_teclaPulsada( QString );

public slots:
    void slot_numeritoPulsado(QString key);
};

#endif // TECLADITO_H
