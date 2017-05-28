#include "registro.h"
#include "ui_registro.h"

#include <QResizeEvent>

Registro::Registro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registro)
{
    ui->setupUi(this);

    ui->fondo->setImage( "background3.jpg", FILL );

    QPalette palette = this->palette();
    palette.setColor( QPalette::WindowText, QColor( 255, 255, 255 ) );
    this->setPalette( palette );

    this->configurarWidgets();
}

Registro::~Registro()
{
    ui->scene->apagarCamara();
    delete ui;
}

void Registro::setIngreso()
{
    ui->pbRegistrar->setTexto( "Ingresar" );
}

void Registro::setSalida()
{
    ui->pbRegistrar->setTexto( "Salir" );
}

void Registro::closeEvent(QCloseEvent *)
{
    ui->scene->apagarCamara();
}

void Registro::showEvent(QShowEvent *)
{
    ui->scene->encenderCamara();
}

void Registro::resizeEvent(QResizeEvent *)
{
    this->configurarWidgets();
}

void Registro::configurarWidgets()
{

    int altoBoton = this->height() / 10;
    int altoLabel = altoBoton;
#ifdef DESKTOP
    int altoTextoLabel = 2 * altoLabel / 5;
#else
    int altoTextoLabel = altoLabel / 5;
#endif
    int altoCamara = 2 * this->height() / 3;
    int anchoPantalla = this->width();
    int altoPantalla = this->height();

    QFont font("Angelina", altoTextoLabel, QFont::Bold);
    ui->label->setFont(font);
    ui->label->setText( "Registre su ingreso" );

    ui->pbRegistrar->setFont( font );
    ui->pbRegistrar->setColor( "#9c27b0" );
    ui->pbRegistrar->setTexto( "Ingresar" );

    ui->label->setGeometry( QRect( 0, 0, anchoPantalla, altoLabel ) );
    ui->scene->setGeometry( QRect( 0, altoLabel, anchoPantalla, altoCamara ) );
    ui->pbRegistrar->setGeometry( QRect( 6, altoPantalla - altoBoton, this->width() - 6, altoBoton ) );

}
