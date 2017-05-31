#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <QObject>
#include <QDebug>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class Database: public QObject
{
    Q_OBJECT

private:
    static Database *instance;
    explicit Database( QObject *parent = NULL );

    QSqlDatabase database;

    bool connectDatabase();
    void disconnectDatabase();

    // Tambien se almacenara aqui datos comunes
    QString id_guardia, dni_guardia, marcarQue;

public:
    static Database *getInstance();
    ~Database();

    int checkLogin();

    bool saveData( QString teamName, QString password );
    QStringList readData();
    QString getId_guardia() const;
    void setId_guardia(const QString &value);
    QString getDni_guardia() const;
    void setDni_guardia(const QString &value);
    QString getMarcarQue() const;
    void setMarcarQue(const QString &value);
};

#endif // DATABASE_HPP
