#include "database.hpp"

Database *Database::instance = NULL;

Database::Database( QObject *parent ) :
    QObject( parent )
{
    database = QSqlDatabase::addDatabase( "QSQLITE" );
}

Database *Database::getInstance()
{
    if( !instance )
    {
        instance = new Database();
    }
    return instance;
}

Database::~Database()
{
    delete instance;
}

bool Database::connectDatabase()
{
    database.setDatabaseName( "db.sqlite" );
    return database.open();
}

void Database::disconnectDatabase()
{
    database.close();
}

QString Database::getMarcarQue() const
{
    return marcarQue;
}

void Database::setMarcarQue(const QString &value)
{
    marcarQue = value;
}

QString Database::getDni_guardia() const
{
    return dni_guardia;
}

void Database::setDni_guardia(const QString &value)
{
    dni_guardia = value;
}

QString Database::getId_guardia() const
{
    return id_guardia;
}

void Database::setId_guardia(const QString &value)
{
    id_guardia = value;
}

int Database::checkLogin()
{
    if( this->connectDatabase() )
    {
        if( database.tables().contains( "inicio_sesion" ) )
        {
            this->disconnectDatabase();
            return 1;
        }
        else
        {
            QSqlQuery query( database );

            QString queryString( "create table inicio_sesion                "
                                 "(                                         "
                                 "    dni       varchar(100)    not null,   "
                                 "    clave     varchar(100)    not null    "
                                 ");" );

            bool ok = query.exec( queryString );

            this->disconnectDatabase();

            return ok ? 0 : -1;
        }
    }
    else
    {
        return -1;
    }
}

bool Database::saveData( QString dni, QString password )
{
    if( this->connectDatabase() )
    {
        QSqlQuery query( database );

        if( !query.exec( "delete from inicio_sesion where 1=1;" ) )
        {
            return false;
        }

        QString queryString( QString( "insert into inicio_sesion ( dni, clave ) values ( '") +
                             QString( dni ) +
                             QString( "', '" ) +
                             QString( password ) +
                             QString( "' );" ) );

        return query.exec( queryString );

        this->disconnectDatabase();
    }
    else
    {
        return false;
    }
}

QStringList Database::readData()
{
    QStringList results;

    if( this->connectDatabase() )
    {
        QSqlQuery query = database.exec( "select dni, clave from inicio_sesion limit 1;" );

        if( query.next() )
        {
            results.append( query.value( 0 ).toString() );
            results.append( query.value( 1 ).toString() );
        }
        else
        {
            results.append( "" );
            results.append( "" );
        }

        this->disconnectDatabase();
    }
    else
    {
        results.append( "" );
        results.append( "" );
    }

    return results;
}
