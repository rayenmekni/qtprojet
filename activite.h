#ifndef ACTIVITE_H
#define ACTIVITE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class activite
{
    int idevent;
    QString nomevent, typeevent, date_event, placeevent;
    int nb_inv;

public:
    activite(){}
    activite(int, QString, QString, QString, QString, int); // Mise à jour du constructeur

    int getIdevent() { return idevent; }
    QString getNomevent() { return nomevent; }
    QString getTypeevent() { return typeevent; }
    QString getDate_event() { return date_event; }
    QString getPlaceevent() { return placeevent; }
    int getNb_inv() { return nb_inv; }

    // setters
    void setNomevent(QString nomevent) { this->nomevent = nomevent; }
    void setTypeevent(QString typeevent) { this->typeevent = typeevent; }
    void setDate_event(QString date_event) { this->date_event = date_event; }
    void setPlaceevent(QString placeevent) { this->placeevent = placeevent; }
    void setNb_inv(int nb_inv) { this->nb_inv = nb_inv; }

    bool ajouterEV();
    QSqlQueryModel *afficherEV();
    bool supprimerEV(int);
    bool modifierEV(int);
    QSqlQueryModel* chercher_event(int idevent, QString nomevent, QString typeevent);
    QSqlQueryModel * triAscEVENT();
    QSqlQueryModel * triDscEVENT();
    QSqlQueryModel * trinb_inv();

};

#endif // ACTIVITE_H
