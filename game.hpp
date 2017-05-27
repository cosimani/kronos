#ifndef GAME_HPP
#define GAME_HPP

#include <QWidget>
#include <QLabel>
#include <QList>

#include <QWidget>
#include <QDir>

namespace Ui
{
    class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game( QWidget *parent = NULL );
    ~Game();

private:
    Ui::Game *ui;

private slots:


};

#endif // GAME_HPP
