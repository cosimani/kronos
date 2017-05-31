#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>

class Registro;

namespace Ui {
class Ventana;
}

class Ventana : public QWidget
{
    Q_OBJECT

public:
    explicit Ventana(QWidget *parent = 0);
    ~Ventana();

    void configurarWidgets();

protected:
//    void closeEvent(QCloseEvent *e);
//    void resizeEvent(QResizeEvent *);

    void mousePressEvent(QMouseEvent *e);
//    void keyPressEvent(QKeyEvent * e);

private:
    Ui::Ventana *ui;

    Registro * registro;


//    bool isConfigurado;  // Para que se llame a configurarWidgets() solo la primera vez


private slots:
    void slot_cambioFoco();
    void slot_mostrarTecladito( bool mostrar );

    void slot_registrarIngreso();
    void slot_registrarSalida();

    void slot_mensajeIn(bool ready );
    void slot_mensajeOut(bool ready);
    void slot_mensajeLogin(QString mensaje);
};

#endif // VENTANA_H
