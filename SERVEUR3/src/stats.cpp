#include <QtWidgets>
#include "stats.h"
//#include "MySocketServer.h"
//#include "MySocketClient.h"



#include <stdlib.h>

#include <QtNetwork>
#include <stdlib.h>

//using namespace std;

//Stats::Stats(int _nb_requete, int _nb_requete_traite, int _nb_erreur, int _nb_client, int _nb_octets, string _requete_serveur, string _nom_fichiers, int _nb_fichiers_dl){
Stats::Stats(QWidget *parent) : QDialog(parent)
{

    nb_requete = 0;
    nb_requete_traite = 0;

    nb_erreur = 0;
    nb_erreur_403 = 0;
    nb_erreur_404 = 0;
    nb_erreur_503 = 0;

    nb_client = 0;
    nb_octets = 0;
    requete_serveur = "";
    nom_fichier1 = "blabla";
    nom_fichier2 = "gerg";
    nom_fichier3 = "blzzzzzabla";
    nom_fichier4 = "blghgzegzeabla";
    nom_fichier5 = "456zef";
    nom_fichier6 = "aaze";

    nb_fichier_dl = 0;

    pourcentage_cache_utilise = 0;

    etat_activate =  1 ;//_Service_Availability;

    // GESTION DE L'AFFICHAGE

    // LES LABELS (TEXTES)
    affichage_nb_requete = new QLabel;
    affichage_nb_erreur = new QLabel;
    affichage_nb_erreur_403 = new QLabel;
    affichage_nb_erreur_404 = new QLabel;
    affichage_nb_erreur_503 = new QLabel;

    // LEs BOUTONS
    activate_button = new QPushButton(tr("Les requêtes sont autorisées"));
    activate_button -> setStyleSheet("QPushButton { background-color: green; }");




    affichage_nb_requete -> setText(tr("nombre de requêtes reçues par le serveur : 0"));
    affichage_nb_erreur -> setText(tr("nombre total d'erreurs : 0"));
    affichage_nb_erreur_403 -> setText(tr("nombre d'erreurs 403 : 0"));
    affichage_nb_erreur_404 -> setText(tr("nombre d'erreurs 404 : 0"));
    affichage_nb_erreur_503 -> setText(tr("nombre d'erreurs 503 : 0"));

    // PLACEMENT DES WIDGETS
    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->addWidget(activate_button);
    mainLayout->addWidget(affichage_nb_requete);
    mainLayout-> addWidget(affichage_nb_erreur);
    mainLayout-> addWidget(affichage_nb_erreur_403);
    mainLayout-> addWidget(affichage_nb_erreur_404);
    mainLayout-> addWidget(affichage_nb_erreur_503);


    setLayout(mainLayout);
    setWindowTitle(tr("Statistiques"));


    // BOUTON D'ACTIVATION DES REQUETES SERVEURS
    connect(activate_button,SIGNAL(clicked()), this, SLOT(activate_serv()));
    //connect(stop_serv,SIGNAL(clicked()), this, SLOT(close()));



}


// SLOTS RECPETION
void Stats::compteur_requete(){
    //nb_requete = nb_requete + 1;
   //std::cout << "nombre total de requetes : " << nb_requete << "\n" <<std::endl;
    affichage_nb_requete ->setText(tr("nombre de requêtes reçues par le serveur : %1").arg(nb_requete));
}

void Stats::compteur_erreur(){
    //nb_erreur = nb_erreur + 1;
   //std::cout << "nombre total d'erreurs : " << nb_erreur << "\n" <<std::endl;
    affichage_nb_erreur ->setText(tr("nombre total d'erreurs : %1").arg(nb_erreur));
}

void Stats::compteur_erreur_403(){
    affichage_nb_erreur_403 -> setText(tr("nombre d'erreurs 403 : %1").arg(nb_erreur_403));
}

void Stats::compteur_erreur_404(){
    affichage_nb_erreur_404 -> setText(tr("nombre d'erreurs 404 : %1").arg(nb_erreur_404));
}

void Stats::compteur_erreur_503(){
    affichage_nb_erreur_503 -> setText(tr("nombre d'erreurs 503 : %1").arg(nb_erreur_503));
}

void Stats::activate_serv(){
    if(etat_activate == 1){
        etat_activate = 0;
        activate_button -> setText(tr("Les requêtes sont désactivées"));
        activate_button->setStyleSheet("QPushButton { background-color: red; }");
        //tr("Les requêtes sont désactivées")
    }
    else
    {
        etat_activate = 1;
        activate_button -> setText(tr("Les requêtes sont autorisées"));
        activate_button->setStyleSheet("QPushButton { background-color: green; }");
        //tr("Les requêtes sont autorisées")
    }
}

