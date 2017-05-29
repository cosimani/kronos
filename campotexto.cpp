#include "campotexto.h"
#include <QLine>
#include <QPoint>
#include <QFontMetrics>

CampoTexto::CampoTexto(QWidget *parent) : QWidget(parent),
                                          timer( new QTimer( this ) ),
                                          isCursorVisible( false ),
                                          foco( false )
{
    timer->start( 550 );

    connect( timer, SIGNAL( timeout() ), this, SLOT( repaint() ) );
}

void CampoTexto::slot_escribir( QString texto )
{
    if ( texto == "Borrar" )  {
        this->texto.chop( 1 );
    }
    else if ( texto == "Enter" )  {
        foco = false;
        emit signal_foco( false );
    }
    else
        this->texto.append( texto );

    this->repaint();
}

void CampoTexto::paintEvent(QPaintEvent *)  {
    QPainter painter( this );
    painter.fillRect( 0, 0, this->width(), this->height(), QColor( 255, 255, 255) );

    QPen pen( QColor( 0, 0, 0 ) );

#ifdef Q_OS_ANDROID
    pen.setWidth( 6 );
#else
    pen.setWidth( 2 );
#endif
    painter.setPen( pen );

//    QFont font = painter.font();
//    font.setPixelSize( this->height() );
//    painter.setFont(font);

    QFontMetrics fm( QFont( "BethHand" ) );
    int altoFuente = fm.height();

    QFont font("BethHand", altoFuente );
    painter.setFont(font);


    painter.drawText( 0, 0, this->width(), this->height(), Qt::AlignVCenter, this->texto);

    if ( ! this->isCursorVisible && this->getFoco() )  {  // Hace que titile el cursor
//    if ( ! this->isCursorVisible )  {  // Hace que titile el cursor
        QFontMetrics fm(font);
        int finalDelTexto = fm.width( this->texto );

        int espacioCursor = this->height() / 6;  // Es el espacio que se deja arriba y abajo

#ifdef Q_OS_ANDROID
        finalDelTexto = qMax( finalDelTexto, 10 );
#else
        finalDelTexto = qMax( finalDelTexto, 3 );
#endif

        QLine line( QPoint( finalDelTexto, espacioCursor ),
                    QPoint( finalDelTexto, this->height() - espacioCursor ) );

        painter.drawLine( line );
    }

    this->isCursorVisible ? this->isCursorVisible = false : this->isCursorVisible = true;

    if ( ! this->getFoco() && this->texto.isEmpty() )  {
//    if ( this->texto.isEmpty() )  {
//        QFont font = painter.font();
//        font.setPixelSize( this->height() / 2 );
//        painter.setFont(font);

        QPen pen( QColor( 150, 150, 150 ) );
        painter.setPen( pen );

        painter.drawText( 0, 0,
                          this->width(), this->height(),
                          Qt::AlignLeft | Qt::AlignVCenter, "Escriba su DNI aquí ...");

    }

}

void CampoTexto::mousePressEvent(QMouseEvent *)
{
    this->setFoco( true );
}

void CampoTexto::keyPressEvent(QKeyEvent *e)
{
    int key = e->key();

    switch( key )  {
        case Qt::Key_0:  this->texto.append( "0" );  break;
        case Qt::Key_1:  this->texto.append( "1" );  break;
        case Qt::Key_2:  this->texto.append( "2" );  break;
        case Qt::Key_3:  this->texto.append( "3" );  break;
        case Qt::Key_4:  this->texto.append( "4" );  break;
        case Qt::Key_5:  this->texto.append( "5" );  break;
        case Qt::Key_6:  this->texto.append( "6" );  break;
        case Qt::Key_7:  this->texto.append( "7" );  break;
        case Qt::Key_8:  this->texto.append( "8" );  break;
        case Qt::Key_9:  this->texto.append( "9" );  break;
        case Qt::Key_Backspace:  this->texto.chop( 1 );  break;
        case Qt::Key_Delete:  this->texto.chop( 1 );  break;
        default:;
    }

    this->repaint();
}

QString CampoTexto::getTexto() const
{
    return texto;
}

bool CampoTexto::getFoco() const
{
    return foco;
}

void CampoTexto::setFoco(bool value)
{
    foco = value;
    emit signal_foco( foco );
}
