#include "activite.h"
#include<QString>
#include<QSqlQuery>
#include "QDebug"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include "QMessageBox"
activite::activite(int idevent, QString nomevent, QString typeevent, QString date_event, QString placeevent, int nb_inv)
{
    this->idevent = idevent;
    this->nomevent = nomevent;
    this->typeevent = typeevent;
    this->date_event = date_event;
    this->placeevent = placeevent;
    this->nb_inv = nb_inv;
}

bool activite::ajouterEV()
{
    QSqlQuery query;
    query.prepare("INSERT INTO evenement (idevent, nomevent, typeevent, date_event, placeevent, nb_inv) "
                  "VALUES (:idevent, :nomevent, :typeevent, :date_event, :placeevent, :nb_inv)");
    query.bindValue(":idevent", idevent);
    query.bindValue(":nomevent", nomevent);
    query.bindValue(":typeevent", typeevent);
    query.bindValue(":date_event", date_event);
    query.bindValue(":placeevent", placeevent);
    query.bindValue(":nb_inv", nb_inv);
    return query.exec();
}

QSqlQueryModel * activite::afficherEV()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM evenement");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("idevent"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nomevent"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("typeevent"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_event"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("placeevent"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nb_inv"));

    return model;
}

bool activite::supprimerEV(int id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM evenement WHERE idevent=:id");
    query.bindValue(":id", id);
    return query.exec();
}

bool activite::modifierEV(int idevent)
{
    QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery query;
    query.prepare("UPDATE evenement SET nomevent = :nomevent, typeevent = :typeevent, date_event = :date_event, placeevent = :placeevent, nb_inv = :nb_inv WHERE idevent = :idevent");
    query.bindValue(":nomevent", nomevent);
    query.bindValue(":typeevent", typeevent);
    query.bindValue(":date_event", date_event);
    query.bindValue(":placeevent", placeevent);
    query.bindValue(":nb_inv", nb_inv);
    query.bindValue(":idevent", idevent);

    return query.exec();
}
QSqlQueryModel* activite::chercher_event(int idevent, QString nomevent, QString typeevent)
{
    QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery query;

        query.prepare("SELECT idevent, nomevent, typeevent, date_event, placeevent, nb_inv FROM EVENEMENT WHERE "
                      "(IDEVENT = :idevent OR :idevent = 0) AND "
                      "(NOMEVENT LIKE :nomevent OR :nomevent = '') AND "
                      "(TYPEEVENT LIKE :typeevent OR :typeevent = '')");
        query.bindValue(":idevent", idevent);
        query.bindValue(":nomevent", '%' + nomevent + '%');
        query.bindValue(":typeevent", '%' + typeevent + '%');
        if (!query.exec()) {
            qDebug() << "Query error:" << query.lastError().text();
            delete model;
            return nullptr;
        }
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("idevent"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nomevent"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("typeevent"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_event"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("placeevent"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("nb_inv"));
        return model;

}

QSqlQueryModel * activite::triAscEVENT(){
QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("SELECT * FROM EVENEMENT ORDER BY IDEVENT ASC");
return model;
}
QSqlQueryModel * activite::triDscEVENT(){
QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("SELECT * FROM EVENEMENT ORDER BY IDEVENT DESC");
return model;
}
QSqlQueryModel * activite::trinb_inv(){
QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("SELECT * FROM EVENEMENT ORDER BY NB_INV ASC");
return model;
}
