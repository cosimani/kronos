#include "registro.h"
#include "ui_registro.h"

#include <QResizeEvent>
#include <QMessageBox>

#include "datamanager.h"
#include "database.hpp"

#include <QDateTime>

Registro::Registro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registro)
{
    ui->setupUi(this);

    ui->fondo->setImage( "background3.jpg", FILL );

    QPalette palette = this->palette();
    palette.setColor( QPalette::WindowText, QColor( 255, 255, 255 ) );
    this->setPalette( palette );

//    connect(ui->pbRegistrar, SIGNAL(clic()), this, SLOT(slot_registrar()));

//    connect(DataManager::getInstance(), SIGNAL(readyIn(bool)),
//            this, SLOT(slot_mensajeIn(bool)));

//    connect(DataManager::getInstance(), SIGNAL(readyOut(bool)),
//            this, SLOT(slot_mensajeOut(bool)));



}

Registro::~Registro()
{
    ui->scene->apagarCamara();
    delete ui;
}

void Registro::setIngreso()
{
    ui->label->setText( "Registrar llegada" );
    Database::getInstance()->setMarcarQue( "llegada" );

}

void Registro::setSalida()
{
    ui->label->setText( "Registrar salida" );
    Database::getInstance()->setMarcarQue( "salida" );
}

void Registro::closeEvent(QCloseEvent *e)
{
#ifdef Q_OS_ANDROID
    if(e->type() == QEvent::Close)  {

        int respuesta = QMessageBox::question( this, "Atención!", "¿Desea salir de la aplicación?");

        switch(respuesta)
        {
        case QMessageBox::Yes:
            ui->scene->apagarCamara();
            break;

        case QMessageBox::No:
            e->ignore();
//            ui->campoLegajo->setFoco( false );
            break;
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

}

void Registro::setIdGuardia(int value)
{
    idGuardia = value;
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

    int altoCamara = this->height() - altoBoton - altoLabel;
    int anchoPantalla = this->width();
    int altoPantalla = this->height();
    int borde = this->width() / 100;

    QFont font("Angelina", altoTextoLabel, QFont::Bold);
    ui->label->setFont(font);
//    ui->label->setText( "Registre su ingreso y salida" );

//    ui->pbRegistrar->setFont( font );
//    ui->pbRegistrar->setColor( "#9c27b0" );
//    ui->pbRegistrar->setTexto( "Ingresar" );

    ui->label->setGeometry( QRect( 0, 0,
                                   anchoPantalla, altoLabel ) );

    ui->scene->setGeometry( QRect( 0, altoLabel,
                                   anchoPantalla, altoCamara ) );


//    ui->pbRegistrar->setGeometry( QRect( borde,
//                                         altoPantalla - altoBoton,
//                                         this->width() - 2 * borde,
//                                         altoBoton ) );

}

void Registro::slot_cambioFoco()
{

}


void Registro::slot_registrar()
{

//    QDateTime now = QDateTime::currentDateTime();

//    QString time = now.toString("yyyy-MM-dd hh:mm:ss");

//    if (ui->label->getTexto() == "Registrar llegada" )  {

//        if( !DataManager::getInstance()->requestIn( ui->campoLegajo->getTexto(),
//                                                    ui->campoLegajo->getTexto(),
//                                                    time ) )
//        {
//            qDebug() << "Solicitud inicial incorrecta";
//        }
//        else
//        {
//            qDebug() << "Solicitud inicial correcta";
//        }
//    }

//    if (ui->label->getTexto() == "Registrar salida" )  {
//        if( !DataManager::getInstance()->requestOut( ui->campoLegajo->getTexto(),
//                                                     ui->campoLegajo->getTexto(),
//                                                     time ) )
//        {
//            qDebug() << "Solicitud inicial incorrecta";
//        }
//        else
//        {
//            qDebug() << "Solicitud inicial correcta";
//        }

//    }
}

void Registro::slot_mensajeIn( bool ready )
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

void Registro::slot_mensajeOut( bool ready )
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
