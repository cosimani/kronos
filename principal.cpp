#include "principal.h"
#include "ui_principal.h"

#include "registro.h"

Principal::Principal(QWidget *parent) : QWidget(parent),
                                        ui(new Ui::Principal),
                                        registro( NULL )
{
    ui->setupUi(this);

    ui->background->setImage( "background3.jpg", FILL );

    connect(ui->pbIngreso, SIGNAL(clic()), this, SLOT(showIngreso()));
    connect(ui->pbSalida, SIGNAL(clic()), this, SLOT(showSalida()));

    QPalette palette = this->palette();
    palette.setColor( QPalette::WindowText, QColor( 255, 255, 255 ) );
    this->setPalette( palette );

    this->configurarWidgets();
}

Principal::~Principal()
{
    delete ui;
}

void Principal::resizeEvent( QResizeEvent* )
{
    this->configurarWidgets();
}

void Principal::showIngreso()
{
    //    Si no se hace close() ni hide(), entonces con el boto atras de celu, se vuelve a mostrar el widget anterior
    this->close();  // Ojo que al estar seteado con this->setAttribute(Qt::WA_DeleteOnClose); se destruye con close()
//    this->hide();  // Se oculta pero no se destruye, y con el boton atras del celu, no vuelve sino que se cierra

    if ( registro == NULL )  // Para crearlo solo la primera vez
        registro = new Registro;

    registro->setIngreso();
    registro->show();
}

void Principal::showSalida()
{
    //    Si no se hace close() ni hide(), entonces con el boto atras de celu, se vuelve a mostrar el widget anterior
    this->close();  // Ojo que al estar seteado con this->setAttribute(Qt::WA_DeleteOnClose); se destruye con close()
//    this->hide();  // Se oculta pero no se destruye, y con el boton atras del celu, no vuelve sino que se cierra

    if ( registro == NULL )  // Para crearlo solo la primera vez
        registro = new Registro;

    registro->setSalida();
    registro->show();
}

void Principal::configurarWidgets()
{
    int altoBoton = this->height() / 10;
    int altoLabel = altoBoton;

#ifdef DESKTOP
    int altoTextoLabel = 2 * altoLabel / 5;
#else
    int altoTextoLabel = altoLabel / 5;
#endif

    QFont font("Angelina", altoTextoLabel, QFont::Bold);

    ui->label->setFont(font);
    ui->label->setText( "Kronos" );

    ui->boton1->setColor( "#e91e63" );  ui->boton1->setTexto( "Boton 1" );
    ui->boton1->setFont(font);
    ui->pbIngreso->setColor( "#9c27b0" );  ui->pbIngreso->setTexto( "Registrar ingreso" );
    ui->pbIngreso->setFont(font);
    ui->boton3->setColor( "#673ab7" );  ui->boton3->setTexto( "Boton 3" );
    ui->boton3->setFont(font);
    ui->pbSalida->setColor( "#009688" );  ui->pbSalida->setTexto( "Registrar salida" );
    ui->pbSalida->setFont(font);

}


