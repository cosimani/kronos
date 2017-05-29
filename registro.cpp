#include "registro.h"
#include "ui_registro.h"

#include <QResizeEvent>
#include <QMessageBox>

Registro::Registro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registro)
{
    ui->setupUi(this);

    ui->fondo->setImage( "background3.jpg", FILL );

    QPalette palette = this->palette();
    palette.setColor( QPalette::WindowText, QColor( 255, 255, 255 ) );
    this->setPalette( palette );

    connect( ui->campoLegajo, SIGNAL( signal_foco( bool ) ), this, SLOT( slot_mostrarTecladito( bool ) ) );

    connect( ui->tecladito, SIGNAL( signal_teclaPulsada( QString ) ),
             ui->campoLegajo, SLOT( slot_escribir( QString ) ) );

}

Registro::~Registro()
{
    ui->scene->apagarCamara();
    delete ui;
}

void Registro::setIngreso()
{
    this->configurarWidgets();
    ui->pbRegistrar->setTexto( "Registrar llegada" );
}

void Registro::setSalida()
{
    this->configurarWidgets();
    ui->pbRegistrar->setTexto( "Registrar salida" );
}

void Registro::closeEvent(QCloseEvent *e)
{
#ifdef Q_OS_ANDROID
    if(e->type() == QEvent::Close)  {

        if ( ui->campoLegajo->getFoco() )  {
            e->ignore();
            ui->campoLegajo->setFoco( false );
        }
        else  {
            int respuesta = QMessageBox::question( this, "Atención!", "¿Desea salir de la aplicación?");

            switch(respuesta)
            {
            case QMessageBox::Yes:
                ui->scene->apagarCamara();
                break;

            case QMessageBox::No:
                e->ignore();
                ui->campoLegajo->setFoco( false );
                break;
            }
        }
    }
#else
    ui->scene->apagarCamara();
#endif
}

void Registro::showEvent(QShowEvent *)
{
    ui->scene->encenderCamara();
}

void Registro::resizeEvent(QResizeEvent *)
{
    this->configurarWidgets();
}

void Registro::mousePressEvent(QMouseEvent *e)
{
    if ( e->pos().x() < ui->campoLegajo->x() ||
         e->pos().x() > ui->campoLegajo->x() + ui->campoLegajo->width() ||
         e->pos().y() < ui->campoLegajo->y() ||
         e->pos().y() > ui->campoLegajo->y() + ui->campoLegajo->height() )
        ui->campoLegajo->setFoco( false );
}

void Registro::keyPressEvent(QKeyEvent *e)
{
    int key = e->key();

//    switch( key )  {
//    case Qt::Key_Back:
//        ui->campoLegajo->setConFoco( false );

//    default:;
//    }

    if( key == Qt::Key_MediaPrevious )
        {
//            int ret = messageBox( QMessageBox::Yes | QMessageBox::No, "¿Desea salir de la aplicación?", QMessageBox::Question);
            int ret = QMessageBox::question( this, "title", "text");

            switch(ret)
            {
            case QMessageBox::Yes:
                this->close();
                break;

            case QMessageBox::No:
                break;
            }
    }
}

void Registro::configurarWidgets()
{
    int altoBoton = this->height() / 10;
    int altoLabel = altoBoton;
    int altoLineEdit = 2 * altoBoton / 3;
//    int altoTecladito = altoLineEdit;

#ifdef Q_OS_ANDROID
    int altoTextoLabel = altoLabel / 5;
#else
    int altoTextoLabel = 2 * altoLabel / 5;
#endif

    int altoCamara = 2 * this->height() / 3;
    int anchoPantalla = this->width();
    int altoPantalla = this->height();
    int borde = this->width() / 100;

    QFont font("Angelina", altoTextoLabel, QFont::Bold);
    ui->label->setFont(font);
    ui->label->setText( "Registre su ingreso y salida" );

    ui->pbRegistrar->setFont( font );
    ui->pbRegistrar->setColor( "#9c27b0" );
//    ui->pbRegistrar->setTexto( "Ingresar" );

    ui->label->setGeometry( QRect( 0, 0,
                                   anchoPantalla, altoLabel ) );

    ui->scene->setGeometry( QRect( 0, altoLabel,
                                   anchoPantalla, altoCamara ) );

    ui->campoLegajo->setGeometry( QRect( borde,
                                         altoLabel + altoCamara,
                                         anchoPantalla - 2 * borde,
                                         altoLineEdit ) );

//    ui->tecladito->setGeometry( QRect( borde,
//                                       altoLabel + altoCamara + altoLineEdit,
//                                       anchoPantalla - 2 * borde,
//                                       altoTecladito ) );
    ui->tecladito->dimensionarTeclado();
    ui->tecladito->hide();

    ui->pbRegistrar->setGeometry( QRect( borde,
                                         altoPantalla - altoBoton,
                                         this->width() - 2 * borde,
                                         altoBoton ) );

}

void Registro::slot_cambioFoco()
{

}

void Registro::slot_mostrarTecladito(bool mostrar)
{
    int desplazamientoTecladito = ui->campoLegajo->geometry().height() * 2;

    if ( mostrar )  {
        if ( ui->tecladito->isHidden() )  {
            ui->campoLegajo->setGeometry( QRect( ui->campoLegajo->geometry().x(),
                                                 ui->campoLegajo->geometry().y() - desplazamientoTecladito,
                                                 ui->campoLegajo->geometry().width(),
                                                 ui->campoLegajo->geometry().height() ) );

            ui->tecladito->setGeometry( QRect(
                    ui->campoLegajo->geometry().x(),
                    ui->campoLegajo->geometry().y() + ui->campoLegajo->geometry().height(),
                    ui->campoLegajo->geometry().width(),
                    ui->campoLegajo->geometry().height() * 2
                                            ) );
            ui->tecladito->dimensionarTeclado();
            ui->tecladito->show();
        }
    }
    else  {
        if ( ui->tecladito->isVisible() )  {
            ui->campoLegajo->setGeometry( QRect( ui->campoLegajo->geometry().x(),
                                                 ui->campoLegajo->geometry().y() + desplazamientoTecladito,
                                                 ui->campoLegajo->geometry().width(),
                                                 ui->campoLegajo->geometry().height() ) );
            ui->tecladito->hide();
        }

    }
}
