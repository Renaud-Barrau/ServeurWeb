#ifndef STATS_COPY_H
#define STATS_COPY_H


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
    //CONSTRUCTEURS
    //Stats(int _nb_requete, int _nb_requete_traite, int _nb_erreur, int _nb_client, int _nb_octets, string _requete_serveur, string _nom_fichiers, int _nb_fichiers_dl);
    Stats(QWidget *parent = 0);
    //

    int nb_requete;
    int nb_requete_traite;
    int nb_erreur;
    int nb_client;
    int nb_octets;
    std::string requete_serveur;
    std::string nom_fichiers;
    int nb_fichier_dl;

    // METHODES
//    int get_nb_requete(int nb_requete);
//    int get_nb_requete_traite(int nb_requete_traite);
//    int get_nb_erreur(int nb_erreur);
//    int get_nb_client(int nb_client);
//    int get_nb_octets(int nb_octets);
//    std::string get_requete_serveur( std::string requete_serveur);
//    std::string get_nom_fichiers( std::string nom_fichiers);
//    int get_nb_fichier_dl( int nb_fichier_dl);

private :

    //ATTRIBUTS

    //QObject *parent;

    QLabel *affichage_nb_requete;
    QLabel *affichage_nb_erreur;
    //MySocketServer server;
    //MySocketClient *thread;


public slots :
    void compteur_requete();
    void compteur_erreur();

};

//extern Stats Statistiques;

#endif // STATS_COPY_H


