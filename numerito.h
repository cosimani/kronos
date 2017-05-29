#ifndef NUMERITO_H
#define NUMERITO_H

#include <QWidget>
#include <QPainter>
#include <QFont>
#include <QColor>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>

class Numerito : public QWidget
{
    Q_OBJECT
public:
    explicit Numerito(QWidget *parent = 0);

    void setTexto(const QString &value);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    QString texto;

signals:
    void signal_numero( QString );

public slots:
};

#endif // NUMERITO_H
