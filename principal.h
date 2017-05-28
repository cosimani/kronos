#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QWidget>

class Registro;

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
    Registro * registro;

    void configurarWidgets();
private slots:
    void showIngreso();
    void showSalida();
};

#endif // PRINCIPAL_H
