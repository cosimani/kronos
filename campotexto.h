#ifndef CAMPOTEXTO_H
#define CAMPOTEXTO_H

#include <QWidget>
#include <QPainter>
#include <QFont>
#include <QColor>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>


class CampoTexto : public QWidget
{
    Q_OBJECT
public:
    explicit CampoTexto(QWidget *parent = 0);

    bool getFoco() const;
    void setFoco(bool value);

    QString getTexto() const;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void keyPressEvent( QKeyEvent * e );

private:
    QString texto;
    QTimer * timer;
    bool isCursorVisible;

    // Es un bool para almacenar si esta en foco este campo. Ya que hay problemas con el manejo de foco
    // con lo de Qt
    bool foco;

signals:
    void signal_foco( bool isFocused );
    void signal_enter();

public slots:
    void slot_escribir( QString texto );
};

#endif // CAMPOTEXTO_H
