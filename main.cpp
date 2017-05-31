#include <QApplication>
#include <QSurfaceFormat>

#include <QQuickView>
#include <QQmlContext>
#include <QQuickImageProvider>
#include <QDebug>
#include "squircle.h"
#include "database.hpp"

#include "principal.h"
#include "ventana.h"

#include <QTimer>
#include <QFontDatabase>

int main( int argc, char **argv )
{
    Q_INIT_RESOURCE( files );

    QApplication application( argc, argv );

    QFontDatabase::addApplicationFont(":/resources/fuentes/angelina.TTF");
    QFontDatabase::addApplicationFont(":/resources/fuentes/Bethhrg_.ttf");

//    QFontDatabase baseFuentes;
//    qDebug() << baseFuentes.families();


    QQuickView * view = NULL;

//    Principal * principal = NULL;
    Ventana * ventana = NULL;

    switch( Database::getInstance()->checkLogin() )
    {
    case 0:
        QTimer::singleShot(30000, &application, SLOT(quit()));

        qmlRegisterType<Squircle>("OpenGLUnderQML", 1, 0, "Squircle");

        view = new QQuickView;
        view->setResizeMode(QQuickView::SizeRootObjectToView);
        view->setSource(QUrl("qrc:///openglunderqml.qml"));
        view->show();

        break;
    case -1:
        qDebug() << "Si se devolvio un -1 es porque no anda la base. Seguimos y que sea lo que Dios quiera.";

    case 1:
        qDebug() << "Ya entro antes";

//        principal = new Principal();
        ventana = new Ventana();

        ventana->show();

        ventana->configurarWidgets();

//        principal->show();

        break;

    default:

        break;
    }

    return application.exec();
}
