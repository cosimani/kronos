#include "datamanager.h"

#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

DataManager *DataManager::instance = NULL;

DataManager::DataManager( QObject *parent ) :
    QObject( parent ),
    manager( new QNetworkAccessManager( this ) ),
    availableManager( true )
{

}

bool DataManager::doQuery( QVector< QStringList >params )
{
    if( !this->applyForManager() ) return false;

    QString query( "http://www.vayra.com.ar/kronos/kronos_osi.php?" );
    query.append( "apiKey=kr0n05" );

    for( int i = 0; i < params.size(); i++ )
    {
        if( params.at( i ).size() < 2 )
        {
            continue;
        }
        query.append( "&" + params.at( i ).at( 0 ) + "=" + params.at( i ).at( 1 ) );
    }

    qDebug() << query;

    manager->get( QNetworkRequest( QUrl( query ) ) );
    return true;
}


void DataManager::showErrorAndFinish()
{
    qDebug() << "Verifica tu conexión a internet y reinicia la aplicación";
}

void DataManager::showNoActiveAndFinish()
{
    qDebug() << "La competencia aun no está activa, consulte a los organizadores!";
}

void DataManager::showFinishedAndFinish()
{
    qDebug() << "Felicitaciones! Completaste todas las preguntas, espera los resultados!";
}

DataManager *DataManager::getInstance()
{
    if( !instance )
    {
        instance = new DataManager();
    }
    return instance;
}

DataManager::~DataManager()
{
    delete instance;
}

bool DataManager::getAvailableManager() const
{
    return availableManager;
}

void DataManager::setAvailableManager( bool value )
{
    availableManager = value;
}

bool DataManager::applyForManager()
{
    if( !this->getAvailableManager() )
    {
        qDebug() << "El manager tiene una solicitud en curso";
        return false;
    }
    this->setAvailableManager( false );
    return true;
}

/**
 * @brief DataManager::leaveManager Desconecta todo lo que tenga conectado
 */
void DataManager::leaveManager()
{
    disconnect( manager, SIGNAL( finished( QNetworkReply* ) ), NULL, NULL );
    this->setAvailableManager( true );
}

bool DataManager::requestLogin( QString dni,
                                QString password )
{
    QVector< QStringList >params;
    params.append( QStringList() << "action" << "login" );
    params.append( QStringList() << "dni" << dni );
    params.append( QStringList() << "password" << password );

    if( !this->doQuery( params ) ) return false;
    connect( manager, SIGNAL( finished( QNetworkReply* ) ), SLOT( responseLogin( QNetworkReply* ) ) );
    return true;
}

bool DataManager::requestIn( QString guardId,
                             QString time )
{
    QVector< QStringList >params;
    params.append( QStringList() << "action" << "in" );
    params.append( QStringList() << "guardId" << guardId );
    params.append( QStringList() << "time" << time );

    if( !this->doQuery( params ) ) return false;
    connect( manager, SIGNAL( finished( QNetworkReply* ) ), SLOT( responseIn( QNetworkReply* ) ) );
    return true;
}

bool DataManager::requestOut( QString guardId,
                              QString time )
{
    QVector< QStringList >params;
    params.append( QStringList() << "action" << "out" );
    params.append( QStringList() << "guardId" << guardId );
    params.append( QStringList() << "time" << time );

    if( !this->doQuery( params ) ) return false;
    connect( manager, SIGNAL( finished( QNetworkReply* ) ), SLOT( responseOut( QNetworkReply* ) ) );
    return true;
}

bool DataManager::requestInit( QString usuario,
                               QString password,
                               QString nombre,
                               QString apellido,
                               QString mail,
                               QString id_dentista )
{
    QVector< QStringList >params;
    params.append( QStringList() << "action" << "init" );
    params.append( QStringList() << "usuario" << usuario );
    params.append( QStringList() << "password" << password );
    params.append( QStringList() << "nombre" << nombre );
    params.append( QStringList() << "apellido" << apellido );
    params.append( QStringList() << "mail" << mail );
    params.append( QStringList() << "id_dentista" << id_dentista );

    if( !this->doQuery( params ) ) return false;
    connect( manager, SIGNAL( finished( QNetworkReply* ) ), SLOT( responseInit( QNetworkReply* ) ) );
    return true;
}

bool DataManager::requestFotoDentista( QString usuario,
                                       QString password )
{
    QVector< QStringList >params;
    params.append( QStringList() << "action" << "foto_dentista" );
    params.append( QStringList() << "usuario" << usuario );
    params.append( QStringList() << "password" << password );

    if( !this->doQuery( params ) ) return false;
    connect( manager, SIGNAL( finished( QNetworkReply* ) ), SLOT( responseFotoDentista( QNetworkReply* ) ) );
    return true;
}

bool DataManager::requestListaDentistas()
{
    QVector< QStringList >params;
    params.append( QStringList() << "action" << "dentistas" );

    if( !this->doQuery( params ) ) return false;
    connect( manager, SIGNAL( finished( QNetworkReply* ) ), SLOT( responseListaDentistas( QNetworkReply* ) ) );
    return true;
}

QString DataManager::eliminaAcentos( QString s )  {
    // Performance: Eliminate characters you do not wish to have.
    s.remove(QRegularExpression("[" + QRegularExpression::escape("'!*,?|¡¿") + "]"));
    qDebug().noquote() << "Before:\t" << s;

    // Performance: Check for characters
    if (s.contains(QRegularExpression("[" + QRegularExpression::escape("$/:ÀÁÄÙÛÜàáäçèéêëïñóöùûü") + "]")))
    {
        // Special Characters
        // Escape function is a safety measure in case you accidentally insert "^" in the square brackets.
        s.replace(QRegularExpression("[" + QRegularExpression::escape(":/") + "]"), "-");
        s.replace(QRegularExpression("[$]"), "s");

        // Upper Case
        s.replace(QRegularExpression("[ÁÀ]"),   "A");
        s.replace(QRegularExpression("[Ä]"),    "Ae");
        s.replace(QRegularExpression("[ÜÛÙ]"),  "U");

        // Lower Case
        s.replace(QRegularExpression("[áà]"),   "a");
        s.replace(QRegularExpression("[ä]"),    "ae");
        s.replace(QRegularExpression("[ç]"),    "c");
        s.replace(QRegularExpression("[ëêéè]"), "e");
        s.replace(QRegularExpression("[ï]"),    "i");
        s.replace(QRegularExpression("[ñ]"),    "n");
        s.replace(QRegularExpression("[óö]"),   "o");
        s.replace(QRegularExpression("[ûù]"),   "u");
        s.replace(QRegularExpression("[ü]"),    "ue");
    }

    return s;
}

void DataManager::responseLogin( QNetworkReply *reply )
{
    QByteArray ba = reply->readAll();

    qDebug() << "entra a DataManager::responseLogin" << ba;

    if( ! reply->bytesAvailable() )  {
        qDebug() << "void DataManager::responseLogin( QNetworkReply *reply ) showErrorAndFinish";
//        emit readyLoginMensaje( "desconocido" );

        this->showErrorAndFinish();
    }

    this->leaveManager();

    QString replyString( QString::fromLatin1( ba ) );

    qDebug() << "entra a DataManager::responseLogin replyString=" << replyString;

    if( replyString.isEmpty() )
    {
        qDebug() << "Error, algun error al guardar u obtener los datos del servidor 1";
        emit readyLoginMensaje( "desconocido" );
        return;
    }
    else  {
        QJsonDocument d = QJsonDocument::fromJson(replyString.toUtf8());
        QJsonObject sett2 = d.object();
        QJsonValue valueStatus = sett2.value(QString("status"));
        QJsonValue valueId = sett2.value(QString("id"));

        QString status = valueStatus.toString();
        QString id = QString::number(valueId.toInt());

        if ( ! status.isEmpty() )  {
            if ( valueStatus.toString() == "few_parameters" )  {
                emit readyLoginMensaje( "few_parameters" );
            }
            else if ( valueStatus.toString() == "invalid_login" )  {
                emit readyLoginMensaje( "invalid_login" );
            }
            else  {
                emit readyLoginMensaje( "desconocido" );
            }
        }
        else if ( ! id.isEmpty() )  {
            emit readyLoginMensaje( id );
        }
        else  {
            emit readyLoginMensaje( "desconocido" );
        }
    }
}

void DataManager::responseIn( QNetworkReply *reply )
{

    QByteArray ba = reply->readAll();

    qDebug() << "entra a DataManager::responseIn" << ba;

    if( ! reply->bytesAvailable() )  {
        qDebug() << "void DataManager::responseIn( QNetworkReply *reply ) showErrorAndFinish";
//        emit readyIn( false );

        this->showErrorAndFinish();
    }

    this->leaveManager();

    QString replyString( QString::fromLatin1( ba ) );

    qDebug() << "entra a DataManager::responseIn replyString=" << replyString;

    if( replyString.isEmpty() )
    {
        qDebug() << "Error, algun error al guardar u obtener los datos del servidor 1";
        emit readyIn( false );
        return;
    }
    else  {
        QJsonDocument d = QJsonDocument::fromJson(replyString.toUtf8());
        QJsonObject sett2 = d.object();
        QJsonValue valueStatus = sett2.value(QString("status"));

        QString status = valueStatus.toString();

        qWarning() << "/////////////////" << status;

        if ( ! status.isEmpty() )  {
            if ( valueStatus.toString() == "few_parameters" )  {
                emit readyIn( false );
            }
            else if ( valueStatus.toString() == "invalid_in" )  {
                emit readyIn( false );
            }
            else if ( valueStatus.toString() == "in_ok" )  {
                emit readyIn( true );
            }
            else  {
                emit readyIn( false );
            }
        }
    }
}


void DataManager::responseOut( QNetworkReply *reply )
{

    QByteArray ba = reply->readAll();

    qDebug() << "entra a DataManager::responseOut" << ba;

    if( ! reply->bytesAvailable() )  {
        qDebug() << "void DataManager::responseOut( QNetworkReply *reply ) showErrorAndFinish";
//        emit readyIn( false );

        this->showErrorAndFinish();
    }

    this->leaveManager();

    QString replyString( QString::fromLatin1( ba ) );

    qDebug() << "entra a DataManager::responseOut replyString=" << replyString;

    if( replyString.isEmpty() )
    {
        qDebug() << "Error, algun error al guardar u obtener los datos del servidor 1";
        emit readyOut( false );
        return;
    }
    else  {
        QJsonDocument d = QJsonDocument::fromJson(replyString.toUtf8());
        QJsonObject sett2 = d.object();
        QJsonValue valueStatus = sett2.value(QString("status"));

        QString status = valueStatus.toString();

        qWarning() << "/////////////////" << status;

        if ( ! status.isEmpty() )  {
            if ( valueStatus.toString() == "few_parameters" )  {
                emit readyOut( false );
            }
            else if ( valueStatus.toString() == "invalid_out" )  {
                emit readyOut( false );
            }
            else if ( valueStatus.toString() == "out_ok" )  {
                emit readyOut( true );
            }
            else  {
                emit readyOut( false );
            }
        }
    }
}


void DataManager::responseInit( QNetworkReply *reply )
{
    if( !reply->bytesAvailable() ) this->showErrorAndFinish();

    this->leaveManager();  // Desconecta todas las conexiones del QNetworkAccessManager

    QString replyString( QString::fromLatin1( reply->readAll() ) );

    if( replyString == "n" )
    {
        emit availableName( false );
        return;
    }
    else
    {
        QStringList results( replyString.split( "," ) );

        if( results.size() != 6 ||
            results.contains( "Database Error", Qt::CaseInsensitive ) )
        {
            qDebug() << "Error, algun error al guardar u obtener los datos del servidor 3";
            emit availableName( false );
            return;
        }

        emit availableName( true );
        emit readyInit( results.at( 0 ), // Puede ser: exito o error
                        results.at( 1 ), results.at( 2 ),
                        results.at( 3 ), results.at( 4 ) );
    }

}

void DataManager::responseFotoDentista( QNetworkReply *reply )
{
    if( !reply->bytesAvailable() ) this->showErrorAndFinish();

    this->leaveManager();  // Desconecta todas las conexiones del QNetworkAccessManager

    QString replyString( QString::fromLatin1( reply->readAll() ) );

    if( replyString == "n" )
    {
        qDebug() << "Este usuario no tiene dentista asignado";
        return;
    }
    else
    {
        QStringList results( replyString.split( "||" ) );

        qDebug() << "ssssssssssss" << results;

        if( results.size() != 4 ||
            results.contains( "Database Error", Qt::CaseInsensitive ) )
        {
            qDebug() << "Error, algun error al guardar u obtener los datos del servidor 4";
            return;
        }

        // Emite lo siguiente: nombre || apellido || mail || urlFoto
        emit readyFotoDentista( results.at( 0 ), results.at( 1 ), results.at( 2 ), results.at( 3 ) );
    }

}

void DataManager::responseListaDentistas( QNetworkReply *reply )
{
    if( !reply->bytesAvailable() ) this->showErrorAndFinish();

    this->leaveManager();  // Desconecta todas las conexiones del QNetworkAccessManager

    QString replyString( QString::fromLatin1( reply->readAll() ) );

    if( replyString == "n" )
    {
        qDebug() << "No hay dentistas cargados";
        return;
    }
    else
    {
        QStringList results( replyString.split( "&&" ) );

        if( results.contains( "Database Error", Qt::CaseInsensitive ) )
        {
            qDebug() << "Error, algun error al guardar u obtener los datos del servidor 5";
            return;
        }

        // Emite un QStringList donde cada elemento es algo asi: 1||Sergio||Castro
        emit readyListaDentistas( results );
    }

}
