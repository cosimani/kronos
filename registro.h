#ifndef REGISTRO_H
#define REGISTRO_H

#include <QWidget>

namespace Ui {
class Registro;
}

class Registro : public QWidget
{
    Q_OBJECT

public:
    explicit Registro(QWidget *parent = 0);
    ~Registro();

    void setIngreso();
    void setSalida();

protected:
    void closeEvent(QCloseEvent *e);
    void showEvent(QShowEvent *);
    void resizeEvent(QResizeEvent *);

    void mousePressEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent * e);

private:
    Ui::Registro *ui;

    void configurarWidgets();


private slots:
    void slot_cambioFoco();
    void slot_mostrarTecladito( bool mostrar );

    void slot_registrar();

    void slot_mensajeIn(bool ready );
    void slot_mensajeOut(bool ready);
};

#endif // REGISTRO_H
