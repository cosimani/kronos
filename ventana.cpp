#include "ventana.h"
#include "ui_ventana.h"

#include "registro.h"

#include <QResizeEvent>
#include <QMessageBox>

#include "datamanager.h"
#include "database.hpp"

#include <QDateTime>


Ventana::Ventana(QWidget *parent) : QWidget(parent),
                                    ui(new Ui::Ventana),
                                    registro( new Registro )
{
    ui->setupUi(this);

    ui->fondo->setImage( "background3.jpg", FILL );

    QPalette palette = this->palette();
    palette.setColor( QPalette::WindowText, QColor( 255, 255, 255 ) );
    this->setPalette( palette );

    connect( ui->campoDni, SIGNAL( signal_foco( bool ) ), this, SLOT( slot_mostrarTecladito( bool ) ) );

    connect( ui->tecladito, SIGNAL( signal_teclaPulsada( QString ) ),
             ui->campoDni, SLOT( slot_escribir( QString ) ) );

    connect(ui->bIngreso, SIGNAL(clic()), this, SLOT(slot_registrarIngreso()));
    connect(ui->bSalida, SIGNAL(clic()), this, SLOT(slot_registrarSalida()));
//    connect(ui->campoDni, SIGNAL(signal_enter()), this, SLOT(slot_registrar()));

    connect(DataManager::getInstance(), SIGNAL(readyLoginMensaje(QString)),
            this, SLOT(slot_mensajeLogin(QString)));

    connect(DataManager::getInstance(), SIGNAL(readyIn(bool)),
            this, SLOT(slot_mensajeIn(bool)));

    connect(DataManager::getInstance(), SIGNAL(readyOut(bool)),
            this, SLOT(slot_mensajeOut(bool)));


//    this->configurarWidgets();
}

Ventana::~Ventana()
{
    delete ui;
}

//void Ventana::closeEvent(QCloseEvent *e)
//{
//#ifdef Q_OS_ANDROID
//    if(e->type() == QEvent::Close)  {

//        if ( ui->campoDni->getFoco() )  {
//            e->ignore();
//            ui->campoDni->setFoco( false );
//        }
//        else  {
//            int respuesta = QMessageBox::question( this, "Atención!", "¿Desea salir de la aplicación?");

//            switch(respuesta)
//            {
//            case QMessageBox::Yes:
////                ui->scene->apagarCamara();
//                break;

//            case QMessageBox::No:
//                e->ignore();
//                ui->campoDni->setFoco( false );
//                break;
//            }
//        }
//    }
//#else
////    ui->scene->apagarCamara();
//#endif
//}


//void Ventana::resizeEvent(QResizeEvent *)
//{
//    qDebug() << "resizeEvent(QResizeEvent *)";

//    this->configurarWidgets();

//}

void Ventana::mousePressEvent(QMouseEvent *e)
{
    if ( e->pos().x() < ui->campoDni->x() ||
         e->pos().x() > ui->campoDni->x() + ui->campoDni->width() ||
         e->pos().y() < ui->campoDni->y() ||
         e->pos().y() > ui->campoDni->y() + ui->campoDni->height() )
        ui->campoDni->setFoco( false );

}

//void Ventana::keyPressEvent(QKeyEvent *e)
//{
//    int key = e->key();

////    switch( key )  {
////    case Qt::Key_Back:
////        ui->campoLegajo->setConFoco( false );

////    default:;
////    }

//    if( key == Qt::Key_MediaPrevious )
//        {
////            int ret = messageBox( QMessageBox::Yes | QMessageBox::No, "¿Desea salir de la aplicación?", QMessageBox::Question);
//            int ret = QMessageBox::question( this, "title", "text");

//            switch(ret)
//            {
//            case QMessageBox::Yes:
//                this->close();
//                break;

//            case QMessageBox::No:
//                break;
//            }
//    }
//}

void Ventana::configurarWidgets()
{

    int altoBoton = this->height() / 10;
    int altoLabel = altoBoton;
    int altoCampoDni = 2 * altoBoton / 3;
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

    ui->bIngreso->setFont( font );
    ui->bIngreso->setColor( "#9c27b0" );

    ui->bSalida->setFont( font );
    ui->bSalida->setColor( "#9c27b0" );

    ui->bIngreso->setTexto( "Ingreso" );
    ui->bSalida->setTexto( "Salida" );

    ui->label->setGeometry( QRect( 0, 0,
                                   anchoPantalla, altoLabel ) );

//    ui->scene->setGeometry( QRect( 0, altoLabel,
//                                   anchoPantalla, altoCamara ) );

    ui->campoDni->setGeometry( QRect( borde,
                                      altoLabel + altoCamara,
                                      anchoPantalla - 2 * borde,
                                      altoCampoDni ) );

//    ui->tecladito->setGeometry( QRect( borde,
//                                       altoLabel + altoCamara + altoLineEdit,
//                                       anchoPantalla - 2 * borde,
//                                       altoTecladito ) );
    ui->tecladito->dimensionarTeclado();
    ui->tecladito->hide();

    ui->bIngreso->setGeometry( QRect( borde,
                                      altoPantalla - altoBoton,
                                      this->width() / 2 - 2 * borde,
                                      altoBoton ) );

    ui->bSalida->setGeometry( QRect( borde + this->width() / 2,
                                     altoPantalla - altoBoton,
                                     this->width() / 2 - 2 * borde,
                                     altoBoton ) );

}

void Ventana::slot_cambioFoco()
{

}

void Ventana::slot_mostrarTecladito(bool mostrar)
{
    int desplazamientoTecladito = ui->campoDni->geometry().height() * 2;

    if ( mostrar )  {
        if ( ui->tecladito->isHidden() )  {
            ui->campoDni->setGeometry( QRect( ui->campoDni->geometry().x(),
                                              ui->campoDni->geometry().y() - desplazamientoTecladito,
                                              ui->campoDni->geometry().width(),
                                              ui->campoDni->geometry().height() ) );

            ui->tecladito->setGeometry( QRect(
                    ui->campoDni->geometry().x(),
                    ui->campoDni->geometry().y() + ui->campoDni->geometry().height(),
                    ui->campoDni->geometry().width(),
                    ui->campoDni->geometry().height() * 2
                                            ) );
            ui->tecladito->dimensionarTeclado();
            ui->tecladito->show();
        }
    }
    else  {
        if ( ui->tecladito->isVisible() )  {
            ui->campoDni->setGeometry( QRect( ui->campoDni->geometry().x(),
                                              ui->campoDni->geometry().y() + desplazamientoTecladito,
                                              ui->campoDni->geometry().width(),
                                              ui->campoDni->geometry().height() ) );
            ui->tecladito->hide();
        }

    }
}

void Ventana::slot_registrarIngreso()
{
    Database::getInstance()->setDni_guardia( ui->campoDni->getTexto() );

    if( !DataManager::getInstance()->requestLogin( ui->campoDni->getTexto(),
                                                   ui->campoDni->getTexto() ) )
    {
        qDebug() << "Solicitud inicial incorrecta";
    }
    else
    {
        qDebug() << "Solicitud inicial correcta";
    }

    registro->setIngreso();
}

void Ventana::slot_registrarSalida()
{
    Database::getInstance()->setDni_guardia( ui->campoDni->getTexto() );

    if( !DataManager::getInstance()->requestLogin( ui->campoDni->getTexto(),
                                                   ui->campoDni->getTexto() ) )
    {
        qDebug() << "Solicitud inicial incorrecta";
    }
    else
    {
        qDebug() << "Solicitud inicial correcta";
    }

    registro->setSalida();
}

void Ventana::slot_mensajeLogin(QString mensaje)
{
    if ( mensaje == "desconocido" || mensaje == "few_parameters" || mensaje == "invalid_login" )  {

        QMessageBox::information( this, "Atención!", "Verifique su DNI, compruebe que "
                                  "está conectado a internet e intente de nuevo.");
    }
    else  {
        //    Si no se hace close() ni hide(), entonces con el boto atras de celu, se vuelve a mostrar el widget anterior
    //    this->close();  // Ojo que al estar seteado con this->setAttribute(Qt::WA_DeleteOnClose); se destruye con close()
        this->hide();  // Se oculta pero no se destruye, y con el boton atras del celu, no vuelve sino que se cierra

        registro->setIdGuardia( mensaje.toInt() );
        Database::getInstance()->setId_guardia( mensaje );

        qWarning() << "El guardia tiene id =" << mensaje.toInt();
        registro->show();
    //    registro->configurarWidgets();
    }
}


void Ventana::slot_mensajeIn(bool ready)
{
    if ( ready )  {
        QMessageBox::information( this, "Listo!", "El ingreso fue registrado con éxito!");
        qApp->quit();
    }
    else
        QMessageBox::information( this, "Atención!", "No se pudo registrar el ingreso. "
                                  "Verifique su DNI, compruebe que está conectado a internet"
                                  " e intente de nuevo.");

}

void Ventana::slot_mensajeOut(bool ready)
{
    if ( ready )  {
        QMessageBox::information( this, "Listo!", "La salida fue registrada con éxito!");
        qApp->quit();
    }
    else
        QMessageBox::information( this, "Atención!", "No se pudo registrar la salida. "
                                  "Verifique su DNI, compruebe que está conectado a internet"
                                  " e intente de nuevo.");

}
