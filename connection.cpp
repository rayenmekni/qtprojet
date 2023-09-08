#include "connection.h"

Connection::Connection()
{
}

bool Connection::createconnect()
{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("projet2A");
    db.setUserName("rayen");//inserer nom de l'utilisateur
    db.setPassword("55015712");//inserer mot de passe de cet utilisateur

    if (db.open())
        test=true;





    return  test;
}
void Connection::closeconnect(){ db.close(); }
