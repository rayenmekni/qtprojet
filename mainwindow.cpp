#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QrCode.hpp"
#include <QVector>
#include <QtSql>
#include <QDebug>
#include <QMessageBox>
#include <QDataStream>
#include <QMessageBox>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QDataStream>
#include <QFile>
#include <QFileDialog>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QDesktopServices>
#include <QDialog>
#include"QrCode.hpp"
#include "qcustomplot.h"
using namespace qrcodegen;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tveleve->setModel(ptmp.afficher()); //aff eleve
    ui->tvactivite->setModel(ptmp2.afficherEV()); //aff act
    MainWindow::makePlot(); //stats

}

MainWindow::~MainWindow()
{
    delete ui;
}

//------------------------------------------------//
//--------------GESTION ELEVES--------------------//
//------------------------------------------------//

void MainWindow::on_AjouterET_6_clicked()
{
    QString nom_el, prenom_el, niveau;
    float moyenne;
    int idel;
    int event;

    nom_el=ui->nomeleve->text().trimmed();
    prenom_el=ui->prenomeleve->text().trimmed();
    niveau=ui->niveau->text().trimmed();
    moyenne=ui->moyenne->text().toFloat();
    idel=ui->ideleve->text().toInt();
    event=ui->idclasse2->text().toInt();
    eleve el (nom_el,prenom_el,niveau,moyenne,idel,event);

    if(nom_el.isEmpty() || prenom_el.isEmpty() || niveau.isEmpty()){
        QMessageBox::critical(0,qApp->tr("ERREUR"),qApp->tr("Veuillez remplir les champs vides."),QMessageBox::Cancel);

    }
    else{
        bool test= el.ajouter();
        if(test){
            ui->tveleve->setModel(ptmp.afficher());
            QMessageBox::information(nullptr,QObject::tr("Enregistrer"),tr("Ajout Effectué Avec Success"));

        }
        else
        {
            QMessageBox::critical(nullptr,QObject::tr("erreur!!"),tr("Ajout Non Effectué!!"));
        }
    }
}


void MainWindow::on_modifier_6_clicked()
{
    QString nom_el, prenom_el, niveau;
    float moyenne;
    int idel;
    int event;

    nom_el=ui->nomeleve->text();
    prenom_el=ui->prenomeleve->text();
    niveau=ui->niveau->text();
    moyenne=ui->moyenne->text().toFloat();
    idel=ui->ideleve->text().toInt();
    event=ui->idclasse2->text().toInt();
    eleve el (nom_el,prenom_el,niveau,moyenne,idel,event);

    if(nom_el.isEmpty() || prenom_el.isEmpty() || niveau.isEmpty()){
        QMessageBox::critical(0,qApp->tr("ERREUR"),qApp->tr("Veuillez remplir les champs vides."),QMessageBox::Cancel);

    }
    else{
        bool test= el.mettre_aj(idel);
        if(test){
            ui->tveleve->setModel(ptmp.afficher());
            QMessageBox::information(nullptr,QObject::tr("Enregistrer"),tr("Modification Effectué Avec Success"));

        }
        else
        {
            QMessageBox::critical(nullptr,QObject::tr("erreur!!"),tr("Modification Non Effectué!!"));
        }
    }
}



void MainWindow::on_supprbtn_6_clicked()
{
    int idel=ui->suppridel->text().toInt();
    bool test=ptmp.supprimer(idel);
    if(test){
        ui->tveleve->setModel(ptmp.afficher());
        QMessageBox::information(nullptr,QObject::tr("success"),tr("Suppression Effectuée Avec Success"));
    }
    else {

        QMessageBox::critical(nullptr,QObject::tr("erreur!!"),tr("Suppression Non Effectuée!!"));
    }
}


void MainWindow::on_qrcodegen_6_clicked()
{
    int tveleve = ui->tveleve->currentIndex().row();
    QVariant idelVariant = ui->tveleve->model()->data(ui->tveleve->model()->index(tveleve, 0));
    int idel = idelVariant.toInt(); // Convert QVariant to int
    QSqlQuery qry;
    qry.prepare("SELECT * FROM ELEVE");
    qry.exec();

    QString nom_el, prenom_el, niveau;
    float moyenne;
    int event;

    while (qry.next()) {
        if (qry.value(0).toInt() == idel) { // Assuming column 0 contains IDEL
            nom_el = qry.value(1).toString();
            prenom_el = qry.value(2).toString();
            niveau = qry.value(3).toString();
            moyenne = qry.value(4).toFloat();
            event = qry.value(5).toInt(); // Assuming that the value is stored as an integer in the database
            break; // Exit the loop after finding the matching record
        }
    }

    QString id = "IDEL:\t" + QString::number(idel) +
                 " NOM_EL:\t" + nom_el +
                 " PRENOM_EL:\t" + prenom_el +
                 " NIVEAU:\t" + niveau +
                 " MOYENNE:\t" + QString::number(moyenne) +
                 " EVENT:\t" + QString::number(event);

    QrCode qr = QrCode::encodeText(id.toUtf8().constData(), QrCode::Ecc::HIGH);

    // Read the black & white pixels
    QImage im(qr.getSize(), qr.getSize(), QImage::Format_RGB888);
    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            int color = qr.getModule(x, y);  // 0 for white, 1 for black

            // You need to modify this part
            if (color == 0)
                im.setPixel(x, y, qRgb(254, 254, 254));
            else
                im.setPixel(x, y, qRgb(0, 0, 0));
        }
    }
    im = im.scaled(200, 200);
    ui->qrcodecommande_6->setPixmap(QPixmap::fromImage(im));
}


void MainWindow::on_chercherE_6_clicked()
{

    int idel=ui->rechidel->text().toInt();
    QString nom_el=ui->rechnomel->text();
    QString niveau=ui->rechprenomel->text();

    ui->tveleve->setModel(ptmp.chercher_eleve(idel,nom_el,niveau));
}


void MainWindow::on_trinbblcs_5_clicked()
{

    eleve el;
    ui->tveleve->setModel(ptmp.triMoyenne());
}


void MainWindow::on_triasc_5_clicked()
{
    eleve el;
    ui->tveleve->setModel(ptmp.triA());
}


void MainWindow::on_tridesc_5_clicked()
{

    eleve el;
    ui->tveleve->setModel(ptmp.triD());
}
void MainWindow::on_pdfeleve_clicked()
{
    QPdfWriter pdf("mypdfEleve.pdf");
    QPainter painter(&pdf);
    int i = 4000;

    // Titre
    painter.setPen(Qt::darkBlue); // Couleur du texte
    painter.setFont(QFont("Arial", 25, QFont::Bold)); // Police en gras
    // Récupérer la largeur de la page
    int pageWidth = pdf.width();

    // Calculer la position horizontale pour centrer le texte
    int textWidth = painter.fontMetrics().width("Liste Des Eleves Disponibles");
    int xPosition = (pageWidth - textWidth) / 2;

    // Dessiner le texte centré horizontalement
    painter.drawText(xPosition, 1400, "Liste Des Eleves Disponibles");
    // Rectangle d'en-tête
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 15));
    painter.drawRect(100, 100, 9400, 2500);
    painter.drawRect(100, 3000, 9400, 500);

    // En-tête des colonnes
    painter.setFont(QFont("Arial", 9, QFont::Bold)); // Police en gras
    painter.drawText(400, 3300, "IDEL");
    painter.drawText(1000, 3300, "NOM_EL");
    painter.drawText(2200, 3300, "PRENOM_EL");
    painter.drawText(3400, 3300, "NIVEAU");
    painter.drawText(5900, 3300, "MOYENNE");
    painter.drawText(8100, 3300, "EVENT ASSIGNED");

    // Lignes
    painter.drawRect(100, 3000, 9400, 9000);

    QSqlQuery query;
    query.prepare("select * from ELEVE");
    query.exec();
    while (query.next())
    {
        painter.setPen(Qt::black); // Réinitialiser la couleur du texte
        painter.setFont(QFont("Arial", 9)); // Réinitialiser la police
        painter.drawText(400, i, query.value(0).toString());
        painter.drawText(1000, i, query.value(1).toString());
        painter.drawText(2300, i, query.value(2).toString());
        painter.drawText(3400, i, query.value(3).toString());
        painter.drawText(5900, i, query.value(4).toString());
        painter.drawText(6700, i, query.value(5).toString());

        i = i + 350;
    }

    // Message de confirmation
    QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
                             QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}

//------------------------------------------------//
//--------------GESTION ACTIVITES-----------------//
//------------------------------------------------//


void MainWindow::on_AjouterET_7_clicked()
{
    int idevent;
    QString nomevent,typeevent,date_event,placeevent;
    int nb_inv;

    idevent=ui->idevent->text().toInt();
    nomevent=ui->nomevent->text();
    typeevent=ui->typeevent->text();
    date_event=ui->date_event->text();
    placeevent=ui->placeevent->text();
    nb_inv=ui->nb_inv->text().toInt();
    activite ac (idevent,nomevent,typeevent,date_event,placeevent,nb_inv);

    if(nomevent.isEmpty() || typeevent.isEmpty() || date_event.isEmpty() || placeevent.isEmpty() ){
        QMessageBox::critical(0,qApp->tr("ERREUR"),qApp->tr("Veuillez remplir les champs vides."),QMessageBox::Cancel);

    }
    else{
        bool test= ac.ajouterEV();
        if(test){
            ui->tvactivite->setModel(ptmp2.afficherEV());
            QMessageBox::information(nullptr,QObject::tr("Enregistrer"),tr("Ajout Effectué Avec Success"));

        }
        else
        {
            QMessageBox::critical(nullptr,QObject::tr("erreur!!"),tr("Ajout Non Effectué!!"));
        }
    }

}



void MainWindow::on_modifier_7_clicked()
{
    int idevent;
    QString nomevent,typeevent,date_event,placeevent;
    int nb_inv;

    idevent=ui->idevent->text().toInt();
    nomevent=ui->nomevent->text();
    typeevent=ui->typeevent->text();
    date_event=ui->date_event->text();
    placeevent=ui->placeevent->text();
    nb_inv=ui->nb_inv->text().toInt();
    activite ac (idevent,nomevent,typeevent,date_event,placeevent,nb_inv);

    if(nomevent.isEmpty() || typeevent.isEmpty() || date_event.isEmpty() || placeevent.isEmpty() ){
        QMessageBox::critical(0,qApp->tr("ERREUR"),qApp->tr("Veuillez remplir les champs vides."),QMessageBox::Cancel);

    }
    else{
        bool test= ac.modifierEV(idevent);
        if(test){
            ui->tvactivite->setModel(ptmp2.afficherEV());
            QMessageBox::information(nullptr,QObject::tr("Enregistrer"),tr("Modification Effectué Avec Success"));

        }
        else
        {
            QMessageBox::critical(nullptr,QObject::tr("erreur!!"),tr("Modification Non Effectué!!"));
        }
    }

}



void MainWindow::on_qrcodegen_7_clicked()
{

    int tvactivite = ui->tvactivite->currentIndex().row();
    QVariant idetVariant = ui->tvactivite->model()->data(ui->tvactivite->model()->index(tvactivite, 0));
    int idevent = idetVariant.toInt(); // Convertir en int

    QSqlQuery qry;
    qry.prepare("SELECT * FROM EVENEMENT");
    qry.exec();
    QString nomevent,typeevent,date_event,placeevent;
    int nb_inv;
    while (qry.next()) {
        int currentIdet = qry.value(0).toInt();
        if (currentIdet == idevent) { // Rechercher la ligne correspondante
            idevent = currentIdet; // Mise à jour de la valeur idet
            nomevent = qry.value(1).toString();
            typeevent = qry.value(2).toString();
            date_event = qry.value(3).toString();
            placeevent = qry.value(4).toString();
            nb_inv = qry.value(5).toInt();
            break; // Sortir de la boucle une fois que la ligne est trouvée
        }
    }

    QString id = "IDEVENT:\t" + QString::number(idevent) + "\nNOMEVENT:\t" + nomevent + "\nTYPEEVENT:\t" + typeevent + "\nDATE_EVENT:\t" + date_event + "\nPLACEEVENT:\t" + placeevent + "\nNB_INV:\t" + QString::number(nb_inv);

    QrCode qr = QrCode::encodeText(id.toUtf8().constData(), QrCode::Ecc::HIGH);

    // Read the black & white pixels
    QImage im(qr.getSize(), qr.getSize(), QImage::Format_RGB888);
    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            int color = qr.getModule(x, y);  // 0 for white, 1 for black

            // You need to modify this part
            if (color == 0)
                im.setPixel(x, y, qRgb(254, 254, 254));
            else
                im.setPixel(x, y, qRgb(0, 0, 0));
        }
    }
    im = im.scaled(200, 200);
    ui->qrcodecommande_7->setPixmap(QPixmap::fromImage(im));
}


void MainWindow::on_supprbtn_7_clicked()
{
    int idevent=ui->suppridevent->text().toInt();
    bool test=ptmp2.supprimerEV(idevent);
    if(test){
        ui->tvactivite->setModel(ptmp2.afficherEV());
        QMessageBox::information(nullptr,QObject::tr("success"),tr("Suppression Effectuée Avec Success"));
    }
    else {

        QMessageBox::critical(nullptr,QObject::tr("erreur!!"),tr("Suppression Non Effectuée!!"));
    }
}



void MainWindow::on_chercherE_7_clicked()
{

    int idevent=ui->rechidevent->text().toInt();
    QString nomevent=ui->rechnomevent->text();
    QString typeevent=ui->rechtype->text();

    ui->tvactivite->setModel(ptmp2.chercher_event(idevent,nomevent,typeevent));
}


void MainWindow::on_trinbblcs_6_clicked()
{
    activite ac;
    ui->tvactivite->setModel(ptmp2.trinb_inv());
}


void MainWindow::on_triasc_6_clicked()
{
    activite ac;
    ui->tvactivite->setModel(ptmp2.triAscEVENT());
}


void MainWindow::on_tridesc_6_clicked()
{

    activite ac;
    ui->tvactivite->setModel(ptmp2.triDscEVENT());
}


void MainWindow::on_pdfeleve_2_clicked() //PDF ACTIVITE
{
    QPdfWriter pdf("mypdfEvenement.pdf");
    QPainter painter(&pdf);
    int i = 4000;

    // Titre
    painter.setPen(Qt::darkBlue); // Couleur du texte
    painter.setFont(QFont("Arial", 25, QFont::Bold)); // Police en gras

    // Récupérer la largeur de la page
    int pageWidth = pdf.width();

    // Calculer la position horizontale pour centrer le texte
    int textWidth = painter.fontMetrics().width("Liste Des Evenements Disponibles");
    int xPosition = (pageWidth - textWidth) / 2;

    // Dessiner le texte centré horizontalement
    painter.drawText(xPosition, 1400, "Liste Des Evenements Disponibles");

    // Rectangle d'en-tête
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 15));
    painter.drawRect(100, 100, 9400, 2500);
    painter.drawRect(100, 3000, 9400, 500);

    // En-tête des colonnes
    painter.setFont(QFont("Arial", 9, QFont::Bold)); // Police en gras
    painter.drawText(400, 3300, "IDEVENT");
    painter.drawText(1000, 3300, "NOMEVENT");
    painter.drawText(2200, 3300, "TYPEEVENT");
    painter.drawText(3400, 3300, "DATE_EVENT");
    painter.drawText(5900, 3300, "PLACEEVENT");
    painter.drawText(8100, 3300, "NB_INV");

    // Lignes
    painter.drawRect(100, 3000, 9400, 9000);

    QSqlQuery query;
    query.prepare("SELECT * FROM evenement"); // Utilisez le nom de la table "evenement"
    query.exec();
    while (query.next())
    {
        painter.setPen(Qt::black); // Réinitialiser la couleur du texte
        painter.setFont(QFont("Arial", 9)); // Réinitialiser la police
        painter.drawText(400, i, query.value(0).toString());
        painter.drawText(1000, i, query.value(1).toString());
        painter.drawText(2300, i, query.value(2).toString());
        painter.drawText(3400, i, query.value(3).toString());
        painter.drawText(5900, i, query.value(4).toString());
        painter.drawText(6700, i, query.value(5).toString());

        i = i + 350;
    }

    // Message de confirmation
    QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
                             QObject::tr("PDF Enregistré!.\n" "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
}


//------------------------------------------------//
//---------------------STATS----------------------//
//------------------------------------------------//
void MainWindow::makePlot() {
    // Step 1: Retrieve Data
    QSqlQuery query;
    query.prepare("SELECT idel, event FROM ELEVE");
    query.exec();

    QMap<int, QVector<int>> studentToEventMap;
    while (query.next()) {
        int studentId = query.value(0).toInt();
        int eventId = query.value(1).toInt();
        studentToEventMap[studentId].append(eventId);
    }

    // Step 2: Calculate Statistics
    QVector<double> classIds;
    QVector<double> studentCounts;

    for (auto it = studentToEventMap.begin(); it != studentToEventMap.end(); ++it) {
        int studentId = it.key();
        QVector<int> studentEvents = it.value();
        int eventCount = studentEvents.size();

        // Handle event assignment and decrementing nb_inv
        for (int eventId : studentEvents) {
            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE EVENEMENT SET nb_inv = nb_inv - 1 WHERE idevent = :eventId");
            updateQuery.bindValue(":eventId", eventId);
            if (!updateQuery.exec()) {
                qDebug() << "Error updating nb_inv for event " << eventId;
            }
        }

        classIds.push_back(static_cast<double>(studentId));
        studentCounts.push_back(static_cast<double>(eventCount));
    }

    // Step 3: Prepare Data for Plotting
    if (classIds.isEmpty() || studentCounts.isEmpty()) {
        qDebug() << "No data retrieved from the database.";
        return;
    }

    // Step 4: Create and Customize the Plot
    QCPBars *bars = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    bars->setData(classIds, studentCounts);

    // Customize plot appearance:
    ui->customPlot->xAxis->setLabel("Student ID");
    ui->customPlot->yAxis->setLabel("Number of Assigned Events");
    ui->customPlot->xAxis->setRange(0.5, classIds.size() + 0.5);
    ui->customPlot->yAxis->setRange(0, *std::max_element(studentCounts.constBegin(), studentCounts.constEnd()) + 1);
    ui->customPlot->replot();
}
