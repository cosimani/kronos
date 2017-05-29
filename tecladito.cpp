#include "tecladito.h"
#include <QLine>
#include <QPoint>
#include <QFontMetrics>

Tecladito::Tecladito(QWidget *parent) : QWidget(parent),
                                        num0( new Numerito( this ) ),
                                        num1( new Numerito( this ) ),
                                        num2( new Numerito( this ) ),
                                        num3( new Numerito( this ) ),
                                        num4( new Numerito( this ) ),
                                        num5( new Numerito( this ) ),
                                        num6( new Numerito( this ) ),
                                        num7( new Numerito( this ) ),
                                        num8( new Numerito( this ) ),
                                        num9( new Numerito( this ) ),
                                        numEnter( new Numerito( this ) ),
                                        numBorrar( new Numerito( this ) )
{

    connect( num0, SIGNAL( signal_numero( QString ) ), this, SLOT( slot_numeritoPulsado( QString ) ) );
    connect( num1, SIGNAL( signal_numero( QString ) ), this, SLOT( slot_numeritoPulsado( QString ) ) );
    connect( num2, SIGNAL( signal_numero( QString ) ), this, SLOT( slot_numeritoPulsado( QString ) ) );
    connect( num3, SIGNAL( signal_numero( QString ) ), this, SLOT( slot_numeritoPulsado( QString ) ) );
    connect( num4, SIGNAL( signal_numero( QString ) ), this, SLOT( slot_numeritoPulsado( QString ) ) );
    connect( num5, SIGNAL( signal_numero( QString ) ), this, SLOT( slot_numeritoPulsado( QString ) ) );
    connect( num6, SIGNAL( signal_numero( QString ) ), this, SLOT( slot_numeritoPulsado( QString ) ) );
    connect( num7, SIGNAL( signal_numero( QString ) ), this, SLOT( slot_numeritoPulsado( QString ) ) );
    connect( num8, SIGNAL( signal_numero( QString ) ), this, SLOT( slot_numeritoPulsado( QString ) ) );
    connect( num9, SIGNAL( signal_numero( QString ) ), this, SLOT( slot_numeritoPulsado( QString ) ) );
    connect( numEnter, SIGNAL( signal_numero( QString ) ), this, SLOT( slot_numeritoPulsado( QString ) ) );
    connect( numBorrar, SIGNAL( signal_numero( QString ) ), this, SLOT( slot_numeritoPulsado( QString ) ) );
}

void Tecladito::dimensionarTeclado()
{
    num0->setTexto( "0" );
    num1->setTexto( "1" );
    num2->setTexto( "2" );
    num3->setTexto( "3" );
    num4->setTexto( "4" );
    num5->setTexto( "5" );
    num6->setTexto( "6" );
    num7->setTexto( "7" );
    num8->setTexto( "8" );
    num9->setTexto( "9" );
    numEnter->setTexto( "Enter" );
    numBorrar->setTexto( "Borrar" );

    int anchoNum = this->width() / 10;
    int altoNum = this->height() / 2;

    num0->setGeometry( QRect( 0 * anchoNum, 0, anchoNum, altoNum ) );
    num1->setGeometry( QRect( 1 * anchoNum, 0, anchoNum, altoNum ) );
    num2->setGeometry( QRect( 2 * anchoNum, 0, anchoNum, altoNum ) );
    num3->setGeometry( QRect( 3 * anchoNum, 0, anchoNum, altoNum ) );
    num4->setGeometry( QRect( 4 * anchoNum, 0, anchoNum, altoNum ) );
    num5->setGeometry( QRect( 5 * anchoNum, 0, anchoNum, altoNum ) );
    num6->setGeometry( QRect( 6 * anchoNum, 0, anchoNum, altoNum ) );
    num7->setGeometry( QRect( 7 * anchoNum, 0, anchoNum, altoNum ) );
    num8->setGeometry( QRect( 8 * anchoNum, 0, anchoNum, altoNum ) );
    num9->setGeometry( QRect( 9 * anchoNum, 0, anchoNum, altoNum ) );
    numBorrar->setGeometry( QRect( 0, altoNum, 3 * anchoNum, altoNum ) );
    numEnter->setGeometry(  QRect( 3 * anchoNum, altoNum, 7 * anchoNum, altoNum ) );
}

void Tecladito::paintEvent(QPaintEvent *)  {
    QPainter painter( this );
    painter.fillRect( 0, 0, this->width(), this->height(), QColor( 128, 128, 128 ) );
}

void Tecladito::slot_numeritoPulsado(QString key)
{
    emit signal_teclaPulsada( key );
}

