#include "game.hpp"
#include "ui_game.h"

Game::Game( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::Game )
{
    ui->setupUi( this );

    ui->pbRegistrarse->setColor( "#e91e63" );  ui->pbRegistrarse->setTexto( "Registrarse" );

    QPalette palette = this->palette();
    palette.setColor( QPalette::WindowText, QColor( 255, 255, 255 ) );
    palette.setColor( QPalette::Background, QColor( "#A90230" ) );
    this->setPalette( palette );

}

Game::~Game()
{
    delete ui;
}

