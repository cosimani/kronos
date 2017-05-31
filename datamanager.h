#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QVector>
#include <QStringList>

class DataManager : public QObject {

    Q_OBJECT

private:
    static DataManager *instance;
    explicit DataManager( QObject *parent = NULL );

    QNetworkAccessManager *manager;
    bool availableManager;

    bool checkManager();
    bool doQuery( QVector< QStringList > params );
    void showErrorAndFinish();
    void showNoActiveAndFinish();
    void showFinishedAndFinish();

    QString eliminaAcentos(QString s);
public:
    static DataManager *getInstance();
    ~DataManager();

    bool getAvailableManager() const;
    void setAvailableManager( bool value );
    bool applyForManager();
    void leaveManager();

    bool requestInit(QString usuario,
                      QString password,
                      QString nombre,
                      QString apellido,
                      QString mail , QString id_dentista);

    bool requestFotoDentista( QString usuario, QString password );

    bool requestListaDentistas();

    bool requestIn( QString guardId, QString time );
    bool requestOut(QString guardId, QString time);

    bool requestLogin(QString dni, QString password);


private slots:
    void responseIn( QNetworkReply *reply );
    void responseInit( QNetworkReply *reply );
    void responseFotoDentista( QNetworkReply *reply );
    void responseListaDentistas( QNetworkReply *reply );

    void responseOut(QNetworkReply *reply);
    void responseLogin(QNetworkReply *reply);
signals:
    void readyLogin( bool ok );

    /**
     * @brief readyLoginMensaje Devuelve el mensaje que se interpreta del json devuelto por el webservice
     * @param mensaje 3 opciones:
     *      - id                - Es un numero que representa el id del guardia
     *      - few_parameters    - Faltan parametros en la url
     *      - invalid_login     - No existen esas credenciales de usuario en la base
     *      - desconocido       - Quien sabe
     */
    void readyLoginMensaje( QString mensaje );

    void readyIn( bool ok );
    void readyOut( bool ok );
    void availableName( bool available );
    void readyInit( QString exito, QString usuario, QString password, QString nombre, QString apellido );
    void readyFotoDentista( QString nombre, QString apellido, QString mail, QString urlFoto );
    void readyListaDentistas( QStringList dentistas );
};

#endif // DATAMANAGER_H
