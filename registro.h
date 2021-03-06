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

    void configurarWidgets();

    void setIdGuardia(int value);

protected:
    void closeEvent(QCloseEvent *e);
    void showEvent(QShowEvent *);
    void resizeEvent(QResizeEvent *);

    void mousePressEvent(QMouseEvent *e);
//    void keyPressEvent(QKeyEvent * e);

private:
    Ui::Registro *ui;

    int idGuardia;


private slots:
    void slot_cambioFoco();

    void slot_registrar();

    void slot_mensajeIn(bool ready );
    void slot_mensajeOut(bool ready);
};

#endif // REGISTRO_H
