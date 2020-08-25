#ifndef SERVER_H
#define SERVER_H

#include "include/aoclient.h"
#include "include/aopacket.h"
#include "include/area_data.h"

#include <QApplication>
#include <QDebug>
#include <QMap>
#include <QSettings>
#include <QString>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>

class Server : public QObject {
  Q_OBJECT

public:
  Server(int p_port, int p_ws_port, QObject *parent = nullptr);
  void start();

signals:

public slots:
  void clientConnected();
  void clientDisconnected();
  void clientData();

private:
  void handlePacket(AOPacket packet, QTcpSocket *socket);
  QTcpSocket *getClient(QString ipid);
  void broadcast(AOPacket packet);

  QTcpServer *server;

  int port;
  int ws_port;

  QMap<QTcpSocket *, AOClient *> clients;
  QString partial_packet;
  bool is_partial;

  int player_count;
  QStringList characters;
  QVector<AreaData*> areas;
};

#endif // SERVER_H
