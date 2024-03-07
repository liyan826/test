#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QString>
#include <QObject>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QNetworkAccessManager manager;
    QObject::connect(&manager, &QNetworkAccessManager::finished,
                     &a, [&](QNetworkReply *reply) {
        if (reply->error()) {
            qDebug() << reply->errorString();
            return;
        }
        QString answer = reply->readAll();
        qDebug() << answer;
    });

    // Replace with your InfluxDB URL and port
    QUrl url("http://localhost:8086/write?db=demo");
    QNetworkRequest request(url);
    int value=0;
    char dat[100]="";
    // Construct the data string: "measurement,tag=value field=value"
    // Replace with your actual sensor data
    for(int i=0;i<100;i++){
        value=value++;
        sprintf(dat,"temperature,sensor_id=1 value=%d",value);
        QByteArray data = dat;

        // Send POST request
        QNetworkReply *reply = manager.post(request, data);
    }
//    QByteArray data = dat;

//    // Send POST request
//    QNetworkReply *reply = manager.post(request, data);
    return a.exec();
}

