#include "numerito.h"
#include <QLine>
#include <QPoint>
#include <QFontMetrics>
#include <QDebug>

Numerito::Numerito(QWidget *parent) : QWidget(parent)
{

}

void Numerito::paintEvent(QPaintEvent *)  {
    QPainter painter( this );
    painter.fillRect( 0, 0, this->width(), this->height(), QColor( 0, 0, 0 ) );
    painter.drawRect( 0, 0, this->width(), this->height() );

    QPen pen( QColor( 255, 255, 255 ) );

#ifdef Q_OS_ANDROID
    pen.setWidth( 6 );
#else
    pen.setWidth( 2 );
#endif
    painter.setPen( pen );

    QFontMetrics fm( QFont( "BethHand" ) );
    int altoFuente = fm.height();

    QFont font("BethHand", altoFuente );
    painter.setFont(font);

    painter.drawText( 0, 0, this->width(), this->height(), Qt::AlignCenter, this->texto);
}

void Numerito::mousePressEvent(QMouseEvent *)
{
    emit this->signal_numero( this->texto );
}

void Numerito::setTexto(const QString &value)
{
    texto = value;
}
