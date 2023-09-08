#ifndef ELEVE_H
#define ELEVE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class eleve
{
    QString nom_el, prenom_el, niveau ;
    float moyenne;
    int idel;
    int event;
public:
    // constructeurs
    eleve() {};
    eleve (QString,QString,QString,float,int,int);
    //getters
    QString getnom_el() {return nom_el;}
    QString get_prenomel() {return prenom_el;}
    QString getniveau() {return niveau;}
    float getmoyenne() {return moyenne;}
    int getidel() {return idel;}
    int getevent() {return event;}

    //setters
    void setnom_el(QString n) {nom_el=n;}
    void setprenom_el(QString p) {prenom_el=p;}
    void setniveau (QString ni) {niveau=ni;}
    void setmoyenne (float mo) {this->moyenne=mo;}
    void setidel(int idel) {this->idel=idel;}
    void setevent (int event) {this->event=event;}
    //fcts relatives
    QSqlQueryModel* chercher_eleve(int idel, const QString& nom_el, const QString& niveau);
    QSqlQueryModel * triA();
    QSqlQueryModel * triD();
    QSqlQueryModel * triMoyenne();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool mettre_aj(int);
    bool supprimer(int);
};


#endif // ELEVE_H
