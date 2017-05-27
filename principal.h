#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QWidget>

class Game;

namespace Ui {
class Principal;
}

class Principal : public QWidget
{
    Q_OBJECT

public:
    explicit Principal(QWidget *parent = 0);
    ~Principal();

protected:
    void resizeEvent(QResizeEvent *);

private:
    Ui::Principal *ui;
    Game * game;

private slots:
    void showGame();
};

#endif // PRINCIPAL_H
