#include "scene.h"
#include "ui_scene.h"
#include <QQmlContext>
#include <QQuickItem>
#include <QDebug>

#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickImageProvider>
#include <QDebug>
#include <QDir>
#include <QFileInfo>

#include <QResource>
#include <QMessageBox>
#include <QBuffer>
#include <QDateTime>
#include "database.hpp"


Scene::Scene(QWidget *parent) : QWidget(parent),
                                ui(new Ui::Scene),
                                manager( new QNetworkAccessManager(this) ),
                                placeTimer( new QTimer(this) )
{
    ui->setupUi(this);

#define CAMERA_PARAMETERS_FILE_RESOURCE ":/CameraParameters.yml"
#define CAMERA_PARAMETERS_FILE_LOCAL "./CameraParameters.yml"

    QResource yml( CAMERA_PARAMETERS_FILE_RESOURCE );

    QFile ymlFileResource(yml.absoluteFilePath());

    if (!ymlFileResource.open(QIODevice::ReadOnly | QIODevice::Text))  {
        qDebug() << "No se pudo iniciar camara 2 / Problema con parametros de la camara";
    }

    QTextStream in(&ymlFileResource);
    QString content = in.readAll();

        // Creo un archivo nuevo para almacenarlo
    QFile ymlFileLocal(CAMERA_PARAMETERS_FILE_LOCAL);
    if (!ymlFileLocal.open(QIODevice::WriteOnly | QIODevice::Text))  {
        qDebug() << "No se pudo iniciar camara / Problema con parametros de la camara";
    }

    QTextStream out(&ymlFileLocal);
    out << content;

    ymlFileLocal.close();

    ui->quickWidget->setSource(QUrl("qrc:///qmlcamera.qml"));

    QObject *rect = dynamic_cast<QObject*>(ui->quickWidget->rootObject());

    QObject::connect(rect, SIGNAL(signal_imageProcessing(QString)), this, SLOT(slot_imageProcessing(QString)));
    QObject::connect(rect, SIGNAL(signal_imagePath(QString)), this, SLOT(slot_imagePath(QString)));

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_uploadFinished(QNetworkReply*)));

    connect( placeTimer, SIGNAL( timeout() ), SLOT( showPlaceAgain() ) );

}

Scene::~Scene()
{
    delete ui;
}

void Scene::slot_imageProcessing( const QString& path )  {

    QUrl imageUrl(path);
    QQmlEngine* engine = ui->quickWidget->engine();
    QQmlImageProviderBase* imageProviderBase = engine->imageProvider(imageUrl.host());
    QQuickImageProvider* imageProvider = static_cast<QQuickImageProvider*>(imageProviderBase);

    QSize imageSize;
    QString imageId = imageUrl.path().remove(0,1);
    QImage image = imageProvider->requestImage(imageId, &imageSize, imageSize);

    image = image.convertToFormat(QImage::Format_RGB888);
//    image = image.convertToFormat(QImage::Format_RGB32);

    image = image.scaled(480, 640, Qt::KeepAspectRatio);

    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    image.save(&buffer, "JPG"); // writes the image in PNG format inside the buffer
//    QString imageBase64 = QString::fromLatin1(byteArray.toBase64().data());

//    qDebug() << imageBase64;


    QStringList data( Database::getInstance()->readData() );

    QString dni = data.at(0);
    QString nombreFoto = dni + "_" + QString::number(QDateTime::currentMSecsSinceEpoch());

    QString sUrl( "http://www.vayra.com.ar/registro/upload.php?" );
    sUrl.append( "key=r3gistro" );
    sUrl.append( "&file=" + nombreFoto + ".txt" );

    QNetworkRequest request;
    request.setUrl(QUrl(sUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

//    QByteArray baDatos = "{\"encodedImage\": \"" + imageBase64.toUtf8() + "\"}";

    QByteArray baDatos = "{\"encodedImage\": \"" + byteArray.toBase64() + "\"}";

    manager->post(request, baDatos);

}

void Scene::slot_imagePath(const QString &path)
{
//    qDebug() << " Se borro la imagen " << path << QFile::remove(path);

}

void Scene::slot_uploadFinished(QNetworkReply *reply)
{
    QByteArray ba = reply->readAll();
    qDebug() << ba;

    if ( ! ba.contains("200") )  {
        emit mensaje( "No se subió la foto, intente de nuevo!!" );
        placeTimer->start( 4000 );
    }
    else  {
        emit mensaje( "La foto se tomó con éxito!!!" );
        placeTimer->start( 4000 );
    }

}

void Scene::showPlaceAgain()
{
    placeTimer->stop();
    emit mensaje( "Logre fotos de tarjetas personales" );
}



