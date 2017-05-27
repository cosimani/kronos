#include "principal.h"
#include "ui_principal.h"

#include "game.hpp"

Principal::Principal(QWidget *parent) : QWidget(parent),
                                        ui(new Ui::Principal),
                                        game( NULL )
{
    ui->setupUi(this);

    ui->background->setImage( "background3.jpg", FILL );

    ui->pbMiDentista->setColor( "#e91e63" );  ui->pbMiDentista->setTexto( "" );
    ui->pbVisitas->setColor( "#9c27b0" );  ui->pbVisitas->setTexto( "Registrar ingreso" );
    ui->b3->setColor( "#673ab7" );  ui->b3->setTexto( "" );
    ui->b4->setColor( "#3f51b5" );  ui->b4->setTexto( "" );
    ui->b5->setColor( "#009688" );  ui->b5->setTexto( "Registrar salida" );

    connect(ui->pbVisitas, SIGNAL(clic()), this, SLOT(showGame()));

    QPalette palette = this->palette();
    palette.setColor( QPalette::WindowText, QColor( 255, 255, 255 ) );
    this->setPalette( palette );

    QFont font("Angelina", this->width()/15);
}

Principal::~Principal()
{
    delete ui;
}

void Principal::resizeEvent( QResizeEvent* )
{
}

void Principal::showGame()
{
    //    Si no se hace close() ni hide(), entonces con el boto atras de celu, se vuelve a mostrar el widget anterior
    this->close();  // Ojo que al estar seteado con this->setAttribute(Qt::WA_DeleteOnClose); se destruye con close()
//    this->hide();  // Se oculta pero no se destruye, y con el boton atras del celu, no vuelve sino que se cierra

    if ( game == NULL )  // Para crearlo solo la primera vez
        game = new Game;

    game->show();

}
