#ifndef CAMPOTEXTO_H
#define CAMPOTEXTO_H

#include <QWidget>
#include <QPainter>
#include <QPalette>
#include <QFont>

class Numerito : public QWidget
{
    Q_OBJECT
public:
    explicit Numerito(QWidget *parent = 0) : QWidget(parent)  {
        QPalette palette = this->palette();
        palette.setColor( QPalette::WindowText, QColor( 255, 255, 255 ) );
        this->setPalette( palette );

        QFont font("Angelina", this->width()/15, QFont::Bold);
        //ui->lTexto->setFont(font);

    }

protected:
    void paintEvent(QPaintEvent *)  {
        QPainter painter( this );

    }

    void mousePressEvent(QMouseEvent *)  {
        emit signal_clic();
    }

signals:
    void signal_clic();

public slots:
};


class CampoTexto : public QWidget
{
    Q_OBJECT
public:
    explicit CampoTexto(QWidget *parent = 0);

signals:

public slots:
};

#endif // CAMPOTEXTO_H
