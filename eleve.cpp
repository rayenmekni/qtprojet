#include "eleve.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "QDebug"
#include <QMessageBox>
#include"connection.h"

eleve::eleve(QString nom_el,QString prenom_el,QString niveau,float moyenne,int idel,int event )
{
    this->idel=idel;
    this->nom_el=nom_el;
    this->prenom_el=prenom_el;
    this->niveau=niveau;
    this->moyenne=moyenne;
    this->event=event;
}

bool eleve::ajouter() {
    QSqlQuery query;
    QString res = QString::number(idel);
    QString moyenneFormatted = QString::number(moyenne, 'f', 2);
    QString resCC = QString::number(event);
    query.prepare("INSERT INTO eleve (idel, nom_el, prenom_el, niveau, moyenne, event) "
                  "VALUES (:idel, :nomel, :prenomel, :niveau, :moyenne, :event)");
    query.bindValue(":idel", res);
    query.bindValue(":nomel", nom_el);
    query.bindValue(":prenomel", prenom_el);
    query.bindValue(":niveau", niveau);
    query.bindValue(":moyenne", moyenneFormatted);
    query.bindValue(":event", resCC);

    bool success = query.exec();
    if (!success) {
        qDebug() << "Query execution failed.";
        qDebug() << "Query error:" << query.lastError().text();
        qDebug() << "Executed SQL:" << query.executedQuery();
    }

    return success;
}

bool eleve::supprimer(int idel){
    QSqlQuery query;
    QString res=QString::number(idel);
    query.prepare("Delete from ELEVE where IDEL= :idel");
    query.bindValue(":idel",res);
    return query.exec();
}
QSqlQueryModel * eleve::afficher(){
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from ELEVE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDEL"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_EL"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM_EL"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("NIVEAU"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("MOYENNE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("EVENT"));
    return model;
}
bool eleve:: mettre_aj(int idel) {
    QSqlQuery query;
    QString res = QString::number(idel);
    QString moyenneFormatted = QString::number(moyenne, 'f', 2);
    QString resCC = QString::number(event);
    query.prepare("Update ELEVE SET idel=:idel, nom_el=:nom_el, prenom_el=:prenom_el, niveau=:niveau, moyenne=:moyenne, event=:event WHERE IDEL= :idel ");
    query.bindValue(":idel",res);
    query.bindValue(":nom_el",nom_el);
    query.bindValue(":prenom_el",prenom_el);
    query.bindValue(":niveau",niveau);
    query.bindValue(":moyenne",moyenneFormatted);
    query.bindValue(":event",resCC);
    return query.exec();
}
QSqlQueryModel* eleve::chercher_eleve(int idel, const QString& nom_el, const QString& niveau) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT IDEL, NOM_EL, PRENOM_EL, NIVEAU, MOYENNE, EVENT FROM ELEVE WHERE "
                  "(IDEL = :idel OR :idel = 0) AND "
                  "(NOM_EL LIKE :nom_el OR :nom_el = '') AND "
                  "(NIVEAU LIKE :niveau OR :niveau = '')");
    query.bindValue(":idel", idel);
    query.bindValue(":nom_el", '%' + nom_el + '%');
    query.bindValue(":niveau", '%' + niveau + '%');

    if (!query.exec()) {
        qDebug() << "Query error:" << query.lastError().text();
        delete model;
        return nullptr;
    }

    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDEL"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_EL"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM_EL"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NIVEAU"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("MOYENNE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("EVENT"));

    return model;
}


QSqlQueryModel * eleve::triA()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM ELEVE ORDER BY IDEL ASC");
    return model;
}
QSqlQueryModel * eleve::triD()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM ELEVE ORDER BY IDEL DESC");
    return model;
}
QSqlQueryModel * eleve::triMoyenne(){
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM ELEVE ORDER BY MOYENNE ASC");
    return model;
}
