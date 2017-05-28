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
    void closeEvent(QCloseEvent *);
    void showEvent(QShowEvent *);
    void resizeEvent(QResizeEvent *);

private:
    Ui::Registro *ui;

    void configurarWidgets();
};

#endif // REGISTRO_H
