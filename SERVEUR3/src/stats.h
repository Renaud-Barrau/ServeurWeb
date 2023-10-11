#ifndef STATS_H
#define STATS_H


#include <QDialog>

#include <iostream>

#include <QObject>

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE


//using namespace std;


class Stats : public QDialog
{
    Q_OBJECT


public :

    Stats(QWidget *parent = 0);


    int nb_requete;
    int nb_requete_traite;

    int nb_erreur;
    int nb_erreur_403;
    int nb_erreur_404;
    int nb_erreur_503;


    int nb_client;
    int nb_octets;
    std::string requete_serveur;
    std::string nom_fichier1;
    std::string nom_fichier2;
    std::string nom_fichier3;
    std::string nom_fichier4;
    std::string nom_fichier5;
    std::string nom_fichier6;
    int nb_fichier_dl;
    int pourcentage_cache_utilise;


    int etat_activate;

private :

    QPushButton *activate_button;


    QLabel *affichage_nb_requete;
    QLabel *affichage_nb_erreur;
    QLabel *affichage_nb_erreur_403;
    QLabel *affichage_nb_erreur_404;
    QLabel *affichage_nb_erreur_503;



public slots :
    void compteur_requete();
    void compteur_erreur();
    void compteur_erreur_403();
    void compteur_erreur_404();
    void compteur_erreur_503();
    void activate_serv();


};


#endif // STATS_H


