/****************************************************************************
**
** Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the example classes of the Qt Toolkit.
**
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License versions 2.0 or 3.0 as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file.  Please review the following information
** to ensure GNU General Public Licensing requirements will be met:
** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
** http://www.gnu.org/copyleft/gpl.html.  In addition, as a special
** exception, Nokia gives you certain additional rights. These rights
** are described in the Nokia Qt GPL Exception version 1.3, included in
** the file GPL_EXCEPTION.txt in this package.
**
** Qt for Windows(R) Licensees
** As a special exception, Nokia, as the sole copyright holder for Qt
** Designer, grants users of the Qt/Eclipse Integration plug-in the
** right for the Qt/Eclipse Integration to link to functionality
** provided by Qt Designer and its related libraries.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
****************************************************************************/

#include "MySocketClient.h"
#include "stats.h"

#include "cache.h"
#include "Fstat.h"
#include "FstatManager.h"


#include <QtNetwork>
#include <QVector>
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>


#include <QHostAddress>
#include <QFileInfo>


using namespace std::chrono;

int ind;
QMimeDatabase mimDatabase;
QMimeType mimeType;
bool cacheableFile = 1;
bool realFile = 1;
QVector<QNetworkCookie> cookieJar;
bool admin = 0;


MySocketClient::MySocketClient(int socketDescriptor, QObject *parent, Stats *statistiques,MyCache* _cache, FstatManager* _StatMng,bool* _ServiceAvailability )
    : QThread(parent), socketDescriptor(socketDescriptor), statistiques(statistiques)
{
    cache = _cache;
    StatMng = _StatMng;
    ServiceAvailability = _ServiceAvailability;


}

inline string removeEndLine(string s){
        while( s.at(s.length()-1) == '\r' ||
                        s.at(s.length()-1) == '\n' ){
                s = s.substr(0, s.length()-1);
        }
        return s;
}

void MySocketClient::run()
{
        //statistiques->activate_serv();
        *ServiceAvailability = statistiques->etat_activate;
        cout << statistiques->etat_activate << endl;
        cout << "Starting MySocketClient::run()" << endl;
     admin = 0;
    cookieJar.clear();
    // ON CREE UN LIEN AVEC LA CLASSE STATS
    connect(this, SIGNAL(new_requete()), statistiques, SLOT(compteur_requete()));
    connect(this, SIGNAL(new_erreur()), statistiques, SLOT(compteur_erreur()));
    connect(this, SIGNAL(new_erreur_403()), statistiques, SLOT(compteur_erreur_403()));
    connect(this, SIGNAL(new_erreur_404()), statistiques, SLOT(compteur_erreur_404()));
    connect(this, SIGNAL(new_erreur_503()), statistiques, SLOT(compteur_erreur_503()));
    connect(this, SIGNAL(changement_etat()), statistiques, SLOT(activate_serv()) );


    QTcpSocket tcpSocket;

    // ON RECUPERE LE LIEN DE COMMUNICATION AVEC LE CLIENT ET ON QUITTE EN CAS
    // DE PROBLEME...
    if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
                emit error(tcpSocket.error());
                statistiques->nb_erreur++;
                emit new_erreur();

                return;
    }

    // SI LE CLIENT N'A PAS EU LE TEMPS DE NOUS TRANSMETTRE SA REQUETE,
    // ON SE MET EN ATTENTE PENDANT 1s
    while (tcpSocket.bytesAvailable() < (int)sizeof(quint16)) {
                if (!tcpSocket.waitForReadyRead( 1000 )) {
                    cout << "(EE) Erreur de time out !" << endl;


                    return;
                }
    }

    // SI LE CLIENT N'A PAS EU LE TEMPS DE NOUS TRANSMETTRE SA REQUETE,
    // ON SE MET EN ATTENTE PENDANT 1s
    // LA PREMIERE REQUETE CORRESPOND AU GET NORMALEMENT

    QByteArray Data;
    char tampon[65536];

    // ON RECUPERE LA REQUETE ET SA TAILLE
    int lineLength = tcpSocket.readLine(tampon, 65536);

    // ON TRANSFORME LA REQUETE SOUS FORME DE STRING
    string ligne(tampon);

    cout << "coucouc"<< endl;
    if (ligne.length()!=0){
        ligne = removeEndLine(ligne);
    }
    // ON AFFICHE LA COMMANDE A L'ECRAN...
    cout << "COMMANDE : =>" << ligne << "<=" << endl;

    int pos1 = ligne.find(" ");
    string cmde = ligne.substr(0, pos1);
    ligne = ligne.substr(pos1+1, ligne.length()-pos1);

    cout << "1. : " << cmde  << endl;
    cout << "2. : " << ligne << endl;

    int pos2 = ligne.find(" ");
    string file = ligne.substr(0, pos2);
    ligne = ligne.substr(pos2+1, ligne.length()-pos2);

    cout << "3. : " << file  << endl;
    cout << "4. : '" << ligne << "'" << endl;

    while( tcpSocket.bytesAvailable() > 0 ){
        int lineLength = tcpSocket.readLine(tampon, 65536);
        ligne = tampon;
        cout << ligne << endl;
        pos1 = ligne.find(":");
        string reqCat = ligne.substr(0, pos1);
        //  cout << ligne << endl;
        if(reqCat == "Cookie"){
            pos2 = ligne.find("=");
            QString name = QString::fromStdString(ligne.substr(pos1+2,pos2-2 - pos1));
            pos1 = ligne.find(":");
            QString value ;
            QNetworkCookie cookie;
            cookie.setName(name.toUtf8());
            // cout << name.toStdString() << endl;
            pos1 = ligne.find(";");

            if(pos1 != -1){
                value = QString::fromStdString(ligne.substr(pos2+1,pos1-2 - pos2));
                cookie.setValue(value.toUtf8());
                cookieJar.append(cookie);
                cout << cookie.toRawForm().toStdString() << endl;
                // cookieJar.append(cookie);
                while(pos1 != -1 ){
                    //pos1 = ligne.find(";",pos1+1);
                    //cookieJar.append()

                    pos2 = ligne.find("=",pos1);
                    name = QString::fromStdString(ligne.substr(pos1+2,pos2-2 - pos1));
                    cout << "name "<< name.toStdString() << endl;
                    //int postemp = pos1;
                    pos1 = ligne.find(";",pos1+1);

                    if(pos1 != -1){
                        value = QString::fromStdString(ligne.substr(pos2+1,pos1-3 - pos2));
                    }else{
                        value = QString::fromStdString(ligne.substr(pos2+1,ligne.length()-2 - pos2));
                    }

                    cout << "value "<< value.toStdString() << endl;
                    cookie.setName(name.toUtf8());
                    cookie.setValue(value.toUtf8());
                    cookieJar.append(cookie);

                    cout << cookie.toRawForm().toStdString() << endl;
                }
            }else{
                pos1 = ligne.find("=");
                value = QString::fromStdString(ligne.substr(pos1+1,ligne.length()-2 - pos1));
                cookie.setValue(value.toUtf8());
                cookieJar.append(cookie);
            }
            // cout << value.toStdString() << endl;

            //EXTRAIRE COOKIES
        }




        if (lineLength != -1 &&  lineLength != 0) {
            //cout << "C" << lineLength << " :: " << tampon;
        }else if(lineLength != -1 ){
            cout << "Nothing for the moment !" << endl;
        }
    }



    // LECTURE DE L'ADRESSE IP DU CLIENT
    QHostAddress adresseIP_client;
    QHostAddress adresseIP_host;

    QString port_client;
    QString port_host;

    QString nom_client;

    adresseIP_client = tcpSocket.peerAddress();
    adresseIP_host = tcpSocket.localAddress();

    port_client = QString::number(tcpSocket.peerPort());
    port_host = QString::number(tcpSocket.localPort());

    nom_client = tcpSocket.peerName();

    cout << "IP du client : " << (adresseIP_client.toString()).toStdString() << endl;
    cout << "IP du serveur : " << (adresseIP_host.toString()).toStdString() << endl;

    cout << "Port du client : " << port_client.toStdString() << endl;
    cout << "Port du serveur : " << port_host.toStdString() << endl;

    cout << "Nom du client : " << nom_client.toStdString() << endl;

    if(cmde == "POST"){
        // dernière ligne de tampon = les identifiants
        string rq(tampon);
        int pos3 = rq.find("email=")+6;
        int pos4 = rq.find("&");
        int pos5 = rq.find("password=")+9;
        string username = rq.substr(pos3,pos4-pos3);
        string password = rq.substr(pos5,rq.length()-pos5);
        cout << "------ IDENTIFIANTS CONNECTION ------ " << endl;
        cout << "- USERNAME : " << username << endl;
        cout << "- PASSWORD : " << password << endl;
        cout << "------------------------------------- " << endl;

        if(username == "jesse" && password == "pinkman"){
            // Cookie admin à envoyer;

            string cookieName = "jesse";
            string cookieVal = "pinkman";
            string cookieLigne;
            string age = "1200";
            cookieLigne= "Set-Cookie: " + cookieName + "=" + cookieVal +"; Max-Age=" +age + "\r\n\r\n";
            tcpSocket.write("HTTP/1.1 200 OK \r\nContent-Type: text/html\r\n");
            tcpSocket.write(cookieLigne.c_str());
            tcpSocket.write("<!DOCTYPE html> \r\n<html>\r\n<head>\r\n\r\n<h1><meta http-equiv=\"refresh\" content=\"0; URL=http://localhost:8080/successAuth.html\">\r\n</head>\r\n</html> \r\n");
        }
        else{
            tcpSocket.write("HTTP/1.1 200 OK \r\nContent-Type: text/html\r\n\r\n");
            tcpSocket.write("<!DOCTYPE html> \r\n<html>\r\n<head>\r\n\r\n<h1><meta http-equiv=\"refresh\" content=\"0; URL=http://localhost:8080/failAuth.html\">\r\n</head>\r\n</html> \r\n");
        }
    }

    else if(cmde == "GET"){

        pos1 = file.find("/",2);
        //pos11 = file.find ("/",2);
        string folder = file.substr(0,pos1);
        cout << "BALISE TEST " << folder <<endl;

        if(folder == "/private"){
            cout << "PRIVATE FOLDER" << endl;
            for(int i = 0; i<cookieJar.length(); i++){
                // cout << "cookie reçus "<< cookieJar[i].toRawForm().toStdString().c_str() << endl;

                if(strcmp(cookieJar[i].toRawForm().toStdString().c_str() , "jesse=pinkman\r") == 0){
                    admin = 1;
                }

            }
            if(admin == 0){
                statistiques->nb_erreur++;
                emit new_erreur();
                statistiques->nb_erreur_403++;
                emit new_erreur_403();

                tcpSocket.write("HTTP/1.1 403 ACCESS FORBIDDEN \r\nContent-Type: text/html\r\n\r\n");
                tcpSocket.write("<!DOCTYPE html> \r\n<html>\r\n<head>\r\n\r\n<h1><meta http-equiv=\"refresh\" content=\"0; URL=http://localhost:8080/403.html\">\r\n</head>\r\n</html> \r\n");
                tcpSocket.disconnectFromHost();
                tcpSocket.waitForDisconnected();
                cout << "Finishing MySocketClient::run()" << endl;
                return;
            }
        }

        if(strcmp(file.c_str(), "/private/clear_cache.html") == 0){
            cacheableFile = 0;
            realFile = 1;
            cache->clearCache();
        }else if(strcmp(file.c_str(), "/private/desactivate.html") == 0){
            realFile = 0;
            cacheableFile = 0;
            *ServiceAvailability = 0;
            emit changement_etat();
            //*ServiceAvailability = statistiques->etat_activate;
            tcpSocket.write("HTTP/1.1 200 OK \r\nContent-Type: text/html\r\n\r\n");
            tcpSocket.write("<!DOCTYPE html>\r\n<html> \r\n<body> \r\n<h1>DESACTIVATE</h1> \r\n</body> \r\n</html>");
        }
        else if(strcmp(file.c_str(), "/private/activate.html") == 0){
            tcpSocket.write("HTTP/1.1 200 OK \r\nContent-Type: text/html\r\n\r\n");
            tcpSocket.write("<!DOCTYPE html>\r\n<html> \r\n<body> \r\n<h1>ACTIVATE</h1> \r\n</body> \r\n</html>");
            realFile = 0;
            cacheableFile = 0;
            *ServiceAvailability = 1;
            emit changement_etat();
        }
        else if(strcmp(file.c_str(), "/private/statistiques") == 0){
            // GENERATION DE LA PAGE WEB STATISTIQUES
            cout << "MODE STATISTIQUES" << endl;

            string stat_nb_req = "<tr><td align =\"left\">Nombre de requetes recues par le serveur : </td><td align =\"center\"> " + to_string(statistiques->nb_requete) + "</td></tr>";
            string stat_nb_err = "<tr><td align =\"left\">Nombre d'erreurs totales : </td><td align =\"center\"> " + to_string(statistiques->nb_erreur) + "</td></tr>";
            string stat_nb_err_403 = "<tr><td align =\"left\">Nombre d'erreurs 403 : </td><td align =\"center\"> " + to_string(statistiques->nb_erreur_403) + "</td></tr>";
            string stat_nb_err_404 = "<tr><td align =\"left\">Nombre d'erreurs 404 : </td><td align =\"center\"> " + to_string(statistiques->nb_erreur_404) + "</td></tr>";
            string stat_nb_err_503 = "<tr><td align =\"left\">Nombre d'erreurs 503 : </td><td align =\"center\"> " + to_string(statistiques->nb_erreur_503) + "</td></tr>";

            //string stat_nb_req = "<tr><td>Nombre de requetes recues par le serveur  </td><td> " + to_string(statistiques->nb_requete) + "</td></tr>";
            //string stat_nb_err = "<tr><td>Nombre d'erreurs totales  </td><td> " + to_string(statistiques->nb_erreur) + "</td></tr>";


            string nomfichier1  = "<tr><td>" + statistiques->nom_fichier1  + "</td><td>"+ to_string(5) + "</td><td>a</td></tr>";
            string nomfichier2  = "<tr><td>" + statistiques->nom_fichier2  + "</td><td>"+ to_string(8) + "</td><td>b</td></tr>";
            string nomfichier3  = "<tr><td>" + statistiques->nom_fichier3  + "</td><td>"+ to_string(3) + "</td><td>c</td></tr>";





            // MISE EN FORME DE LA PAGE
            tcpSocket.write("HTTP/1.1 200 OK \r\nContent-Type: text/html\r\n\r\n");
            tcpSocket.write("<!DOCTYPE html><html><script language=\"javascript\">const timo = setTimeout(function(){window.location.reload(1);}, 30000);</script>");


            tcpSocket.write("<head> <meta charset=\"utf-8\"> <title>Statistiques</title> <link rel=\"stylesheet\" href=\"style.css\">");
            //tcpSocket.write("<head>");
            //tcpSocket.write("<script>const compare=(t,e)=>(r,o)=>{var c,l,n,a;let d=(t,e)=>\"\"===t||\"\"===e||isNaN(t)||isNaN(e)?t.toString().localeCompare(e):t-e;return d((c=e?r:o,l=t,c.children[l].textContent),(n=e?o:r,a=t,n.children[a].textContent))},tbody=document.querySelector(\"tbody\"),thx=document.querySelectorAll(\"th\"),trxb=tbody.querySelectorAll(\"tr\");thx.forEach(t=>t.addEventListener(\"click\",()=>{Array.from(trxb).sort(compare(Array.from(thx).indexOf(t),this.asc=!this.asc)).forEach(t=>tbody.appendChild(t))})); </script>");
            //tcpSocket.write("<style>table{border-collapse: collapse}th,td{border: 1px solid black;padding: 10px 20px}</style>");
            //tcpSocket.write("<style>.flecheDesc{width: 0; height: 0; float:right; margin: 10px; border-left: 5px solid transparent; border-right: 5px solid transparent; border-bottom: 5px solid black;}.flecheAsc{width: 0; height: 0; float:right; margin: 10px; border-left: 5px solid transparent; border-right: 5px solid transparent; border-top: 5px solid black;}.tableau{width:100%;table-layout: fixed;border-collapse: collapse;}.tableau td{padding:.3rem}.zebre tbody tr:nth-child(odd){background-color: #d6d3ce;border-bottom:1px solid #ccc;color:#444;}.zebre tbody tr:nth-child(even){background-color: #c6c3bd;border-bottom:1px solid #ccc;color:#444;}.zebre tbody tr:hover:nth-child(odd){background-color: #999690;color:#ffffff;}.zebre tbody tr:hover:nth-child(even){background-color: #999690;color:#ffffff;}.avectri th{text-align:center;padding:5px 0 0 5px;vertical-align: middle;background-color:#999690;color:#444;cursor:pointer;-webkit-touch-callout: none; -webkit-user-select: none; -khtml-user-select: none; -moz-user-select: none; -ms-user-select: none; -o-user-select: none; user-select: none;}.avectri th.selection{background-color:#5d625c;color:#fff;}.avectri th.selection .flecheDesc{border-bottom-color: white;}.avectri th.selection .flecheAsc{border-top-color: white;}.zebre tbody td:nth-child(3){text-align:center;}</style>");


            tcpSocket.write("</head>");

            // PREMIER TABLEAU
            tcpSocket.write("<body style=\"background-color:Cornsilk;\"><h1>Bienvenue sur la page statistiques du serveur</h1><br>");
            tcpSocket.write("<table width=\"500\" border=\"0\">");
            tcpSocket.write("<table>");

            tcpSocket.write("<tr><th colspan=\"5\"><hr></th></tr>");

            tcpSocket.write(stat_nb_req.c_str());
            tcpSocket.write(stat_nb_err.c_str());
            tcpSocket.write(stat_nb_err_403.c_str());
            tcpSocket.write(stat_nb_err_404.c_str());
            tcpSocket.write(stat_nb_err_503.c_str());


            tcpSocket.write("<tr><th colspan=\"5\"><hr></th></tr></table>");

            tcpSocket.write("</table>");

            // DEUXIEME TABLEAU
            //tcpSocket.write("<script>const compare=(t,e)=>(r,o)=>{var c,l,n,a;let d=(t,e)=>\"\"===t||\"\"===e||isNaN(t)||isNaN(e)?t.toString().localeCompare(e):t-e;return d((c=e?r:o,l=t,c.children[l].textContent),(n=e?o:r,a=t,n.children[a].textContent))},tbody=document.querySelector(\"tbody\"),thx=document.querySelectorAll(\"th\"),trxb=tbody.querySelectorAll(\"tr\");thx.forEach(t=>t.addEventListener(\"click\",()=>{Array.from(trxb).sort(compare(Array.from(thx).indexOf(t),this.asc=!this.asc)).forEach(t=>tbody.appendChild(t))})); </script>");
            //tcpSocket.write("<table>");
            //tcpSocket.write("<table class=\"avectri\"><thead>");
            //tcpSocket.write("<tr><th class=\"tri\" data-pos=\"1\" data-tri=\"1\">Nom fichier</th><th class=\"tri\" data-pos=\"2\" data-tri=\"1\">nb de fois DL</th><th class=\"tri\" data-pos=\"1\" data-tri=\"1\">cohee</th></tr></thead>");
            //tcpSocket.write("<tbody>");
            //tcpSocket.write(stat_nb_fichier_dl.c_str());

            //tcpSocket.write("<tbody>");
            // TRI DES FICHIERS PAR ODRE CROISSANT DE TELECHARGEMENT


            //tcpSocket.write("<script> </script>");
            //tcpSocket.write(nomfichier1.c_str());
            //tcpSocket.write(nomfichier2.c_str());
            //tcpSocket.write(nomfichier3.c_str());


            tcpSocket.write("</tbody>");
            tcpSocket.write("</table>");


            // DEUXIEME TABLEAU BIS
            tcpSocket.write("<style>table{border-spacing: 0; width: 100%; border: 1px solid #ddd;}th{cursor: pointer;}th, td{text-align: left; padding: 16px;}</style>");
            //tr:nth-child(even){background-color: #f2f2f2}
            tcpSocket.write("<table id=\"myTable\"> <tr> <th onclick=\"sortTable(0)\">Nom fichier</th> <th onclick=\"sortTable(1)\">total telechargment</th> </tr><tr> <td>Berglunds snabbkop</td><td>870</td></tr><tr> <td>North/South</td><td>999</td></tr><tr><td>Alfreds Futterkiste</td><td>2</td></tr><tr> <td>Koniglich Essen</td><td>20</td></tr><tr> <td>Magazzini Alimentari Riuniti</td><td>66</td></tr><tr> <td>Paris specialites</td><td>54</td></tr><tr> <td>Island Trading</td><td>65</td></tr><tr> <td>Laughing Bacchus Winecellars</td><td>79</td></tr></table><script>function sortTable(n){var table, rows, switching, i, x, y, shouldSwitch, dir, switchcount=0; table=document.getElementById(\"myTable\"); switching=true; dir=\"asc\"; while (switching){switching=false; rows=table.rows; for (i=1; i < (rows.length - 1); i++){shouldSwitch=false;x=rows[i].getElementsByTagName(\"TD\")[n]; y=rows[i + 1].getElementsByTagName(\"TD\")[n]; if (dir==\"asc\"){if (x.innerHTML.toLowerCase() > y.innerHTML.toLowerCase()){shouldSwitch=true; break;}}else if (dir==\"desc\"){if (x.innerHTML.toLowerCase() < y.innerHTML.toLowerCase()){shouldSwitch=true; break;}}}if (shouldSwitch){rows[i].parentNode.insertBefore(rows[i + 1], rows[i]); switching=true; switchcount ++;}else{if (switchcount==0 && dir==\"asc\"){dir=\"desc\"; switching=true;}}}}</script>");
            // code

            //https://www.w3schools.com/howto/tryit.asp?filename=tryhow_js_sort_table_desc

            // SEPARATEUR
            //tcpSocket.write("<tr><th colspan=\"5\"><hr></th></tr>");
            //tcpSocket.write("<script>const compare=(t,e)=>(r,o)=>{var c,l,n,a;let d=(t,e)=>\"\"===t||\"\"===e||isNaN(t)||isNaN(e)?t.toString().localeCompare(e):t-e;return d((c=e?r:o,l=t,c.children[l].textContent),(n=e?o:r,a=t,n.children[a].textContent))},tbody=document.querySelector(\"tbody\"),thx=document.querySelectorAll(\"th\"),trxb=tbody.querySelectorAll(\"tr\");thx.forEach(t=>t.addEventListener(\"click\",()=>{Array.from(trxb).sort(compare(Array.from(thx).indexOf(t),this.asc=!this.asc)).forEach(t=>tbody.appendChild(t))})); </script>");

            //tcpSocket.write("</table>");



            // CAMEMBERT
            tcpSocket.write("<script type=\"text/javascript\" src=\"https://cdnjs.cloudflare.com/ajax/libs/d3/5.7.0/d3.min.js\"></script>");
            //tcpSocket.write("<script type=\"text/javascript\" src=\"diagramme.js\"></script>");
            tcpSocket.write("<svg style=\"width: 213px;height: 213px\"></svg></body><script language=\"javascript\">const color = d3.scaleOrdinal(['#66c2a5', '#fc8d62', '#8da0cb', '#e78ac3', '#a6d854', '#ffd92f']);const data = [2, 3, 8, 10, 13, 21];const radius = 100;const g = d3.select('svg').append('g').attr('transform', `translate(${radius}, ${radius})`);const arc = d3.arc().innerRadius(0).outerRadius(radius);const arcs = d3.pie()(data);g.selectAll('path').data(arcs).enter().append('path').attr('d', arc).style('fill', (d, i) => color(i)).style('stroke', 'white').style('stroke-width', 3);</script>");



            // POURCENTAGE UTIliSATION MEMOIRE CACHE
            tcpSocket.write("<script language=\"javascript\">function setPrc(prc) {document.documentElement.style.setProperty('--prc0', (Math.min(prc, 50) / 50 * 180) + 'deg');document.documentElement.style.setProperty('--prc50', (Math.min(Math.max(prc-50, 0), 50) / 50 * 180) + 'deg');document.getElementsByClassName('numb')[0].innerHTML = prc + '%'}</script>");
            tcpSocket.write("<div class=\"circular\"> <div class=\"inner\"></div><div class=\"outer\"></div><div class=\"numb\"> 0% </div><div class=\"circle\"> <div class=\"bar left\"> <div class=\"progress\"></div></div><div class=\"bar right\"> <div class=\"progress\"></div></div></div></div>");//<script>const numb=document.querySelector(\".numb\"); let counter=0; setInterval(()=>{if(counter==");
            //tcpSocket.write((to_string(statistiques->pourcentage_cache_utilise)).c_str());
            //tcpSocket.write("){clearInterval();}else{counter+=1; numb.textContent=counter + \"%\";}}, 64); </script>");
            tcpSocket.write("Taux d'utilisation du cache");



            tcpSocket.write("<br><address>Cette page s'actualise automatiquement toutes les 30 secondes</address>");
            tcpSocket.write("<script language=\"javascript\">setPrc(");
            cout << "f" << endl;
            if(cache->cacheHit + cache->cacheMiss != 0){
                statistiques->pourcentage_cache_utilise = (100*cache->cacheHit)/(cache->cacheHit + cache->cacheMiss);
            }
            else{
                statistiques->pourcentage_cache_utilise = 0;
            }

            tcpSocket.write(to_string(statistiques->pourcentage_cache_utilise).c_str());
            tcpSocket.write(");</script>");


            tcpSocket.write("</body>");
            tcpSocket.write("<script>function twInitTableau(){[].forEach.call( document.getElementsByClassName(\"avectri\"), function(oTableau){var oEntete=oTableau.getElementsByTagName(\"tr\")[0]; var nI=1;[].forEach.call( oEntete.querySelectorAll(\"th\"), function(oTh){oTh.addEventListener(\"click\", twTriTableau, false); oTh.setAttribute(\"data-pos\", nI); if(oTh.getAttribute(\"data-tri\")==\"1\"){oTh.innerHTML +=\"<span class=\"flecheDesc\"></span>\";}else{oTh.setAttribute(\"data-tri\", \"0\"); oTh.innerHTML +=\"<span class=\"flecheAsc\"></span>\";}if (oTh.className==\"selection\"){oTh.click();}nI++;});});}function twInit(){twInitTableau();}function twPret(maFonction){if (document.readyState !=\"loading\"){maFonction();}else{document.addEventListener(\"DOMContentLoaded\", maFonction);}}twPret(twInit); function twTriTableau(){var nBoolDir=this.getAttribute(\"data-tri\"); this.setAttribute(\"data-tri\", (nBoolDir==\"0\") ? \"1\" : \"0\");[].forEach.call( this.parentNode.querySelectorAll(\"th\"), function(oTh){oTh.classList.remove(\"selection\");}); this.className=\"selection\";this.querySelector(\"span\").className=(nBoolDir==\"0\") ? \"flecheAsc\" : \"flecheDesc\";var oTbody=this.parentNode.parentNode.parentNode.getElementsByTagName(\"tbody\")[0]; var oLigne=oTbody.rows; var nNbrLigne=oLigne.length; var aColonne=new Array(), i, j, oCel; for(i=0; i < nNbrLigne; i++){oCel=oLigne[i].cells; aColonne[i]=new Array(); for(j=0; j < oCel.length; j++){aColonne[i][j]=oCel[j].innerHTML;}}var nIndex=this.getAttribute(\"data-pos\");var sFonctionTri=(this.getAttribute(\"data-type\")==\"num\") ? \"compareNombres\" : \"compareLocale\";aColonne.sort(eval(sFonctionTri));function compareNombres(a, b){return a[nIndex-1] - b[nIndex-1];}function compareLocale(a, b){return a[nIndex-1].localeCompare(b[nIndex-1]);} if (nBoolDir==0) aColonne.reverse();for(i=0; i < nNbrLigne; i++){aColonne[i]=\"<td>\"+aColonne[i].join(\"</td><td>\")+\"</td>\";}oTbody.innerHTML=\"<tr>\"+aColonne.join(\"</tr><tr>\")+\"</tr>\";}</script>");

            tcpSocket.write("</html>");


            tcpSocket.disconnectFromHost();
            tcpSocket.waitForDisconnected();
            cout << "Finishing MySocketClient::run()" << endl;
            return;
        }
        else{
            cacheableFile = 1;
            realFile = 1;
        }





       if (ligne == "GET /private/statistiques HTTP/1.1"){
        }




       else{

        if (ligne == "GET /icons/dossier.png HTTP/1.1"){
            statistiques->nb_fichier_dl--;
            }
        if (ligne == "GET /icons/fichier.png HTTP/1.1"){
            statistiques->nb_fichier_dl--;
        }
        if (ligne == "GET /icons/stats2.png HTTP/1.1"){
            statistiques->nb_fichier_dl--;
        }

            statistiques->nb_requete++;
            emit new_requete();


         cout << file << endl;
       QString str = tr("public_html") + tr(file.c_str());

            steady_clock::time_point t1 = steady_clock::now(); // Mesure du temps 1

            // Regarde dans le cache
            if( *ServiceAvailability == 1 || file == "/login.html"){
            if(realFile == 1 && cacheableFile == 1  && cache->isInCache(str.toStdString()) != 0  ){
                        cout << " dans le cache \n" << endl;

                        mimeType = mimDatabase.mimeTypeForFile(str);
                        string header;
                        if(mimeType.name().toStdString() == "application/x-php"){
                        string a = "text/html " ;
                        header = "HTTP/1.1 200 OK \r\nContent-Type: " + a  + "\r\n\r\n";

                        }
                        else{
                        header = "HTTP/1.1 200 OK \r\nContent-Type: " + mimeType.name().toStdString() + "\r\n\r\n";
                        }
                        //Envoi header
                        tcpSocket.write(header.c_str());
                        //QByteArray da = file->readAll();
                        //steady_clock::time_point t1 = steady_clock::now();

                        //Envoi donnée depuis le cache
                        tcpSocket.write(cache->getFromCache(str.toStdString()));

                        // Augmentation du nb requete correspondant pour les stats
                        // ind = StatMng->exist(str.toStdString());
                        // if(ind > 0){
                        // StatMng->statvect[ind-1].nbReq++;
                        // }

            }

            // Si donnée pas dans le cache
            else if (realFile == 1 ){
                        cout << " pas dans le cache \n"  << endl;



       QFile f( str );
       QDir  d( str );

       cout << " - Chemin du fichier : " << str.toStdString() << endl;
       cout << " - isFile :          : " << f.exists() << endl;
       cout << " - isDirectory       : " << d.exists() << endl;






       if(f.exists() == false &&  d.exists() == false ){


           // ERREUR 404 LE FICHIER N'EXISTE PAS...
           tcpSocket.write("HTTP/1.1 404 NOT FOUND \r\nContent-Type: text/html\r\n\r\n");
           tcpSocket.write("<!DOCTYPE html> \r\n<html>\r\n<head>\r\n\r\n<h1><meta http-equiv=\"refresh\" content=\"0; URL=http://localhost:8080/404.html\">\r\n</head>\r\n</html> \r\n");

           statistiques->nb_erreur++;
           emit new_erreur();
           statistiques->nb_erreur_404++;
           emit new_erreur_404();



       }else if( d.exists() == true ){
            // C'EST UN REPERTOIRE !
            QFileInfoList list =  d.entryInfoList();
            //int TAILLE_DE_LIST = sizeof(list);
                for(int i = 0; i < list.size() ;i++){
                    //cout <<  list[i].fileName().toStdString()<< "\n" << endl;
                }



            // MISE EN FORME
            tcpSocket.write("HTTP/1.1 200 OK \r\nContent-Type: text/html\r\n\r\n");
            tcpSocket.write("<!DOCTYPE html><html><body style=\"background-color:Cornsilk;\"><h1>Vous vous trouvez dans un dossier</h1><br><table width=\"500\" border=\"0\">");



            // ON RECUPERE LE CHEMIN DU DOSSIER COURANT
            string chemin = d.path().toStdString();
            string chemin_pour_reverse = d.path().toStdString();

            // ON ENLEVE LE PUBLIC_HTML


            chemin.erase(0,11);
            //chemin_pour_reverse.erase(0,12);
            cout << "chemin du dossier courant : "<< chemin << endl;

            // SI ON EST PAS A LA RACINE


            if (chemin_pour_reverse.length() > 12){

            reverse(chemin_pour_reverse.begin(), chemin_pour_reverse.end());
            cout << "chemin du dossier courant reverse : "<< chemin_pour_reverse << endl;

            pos1 = chemin_pour_reverse.find("/",2);
            string chemin_reverse_parent = chemin_pour_reverse.substr(pos1);


            cout << "chemin du dossier parent reverse : "<< chemin_reverse_parent << endl;
            chemin_reverse_parent.erase(0,1);
            cout << "chemin du dossier parent reverse : "<< chemin_reverse_parent << endl;

            reverse(chemin_reverse_parent.begin(), chemin_reverse_parent.end());

            cout << "chemin du dossier parent reverse : "<< chemin_reverse_parent << endl;

            chemin_reverse_parent.erase(0,12);
            cout << "chemin du dossier parent reverse : "<< chemin_reverse_parent << endl;

            //string retour = "<tr><td width=\"20\" ><img src=\"/icons/retour.png\" alt=\"[   ]\"></td><td>Retour</td></tr>";
            string retour = "<tr><td width=\"20\" ><img src=\"/icons/retour.png\" alt=\"[   ]\"></td><td><a href=\"/" + chemin_reverse_parent +  "\">" + "Dossier parent" + "</a></td></tr>";

            tcpSocket.write(retour.c_str());
            }



            tcpSocket.write("<tr><th colspan=\"5\"><hr></th></tr>");


            // AFFICHAGE DU CONTENU DU DOSSIER
            for (int i = 0; i < list.size() - 2 ; i++){
                if (list[i + 2].isDir()){
                string dossier = "<tr><td width=\"20\" ><img src=\"/icons/dossier.png\" alt=\"[   ]\"></td><td><a href=\"" + chemin + "/" + list[2 + i].fileName().toStdString() + "\">" + list[2 + i].fileName().toStdString() + "</a></td></tr>";
                 tcpSocket.write(dossier.c_str());
                }
                else if( list[i + 2].isFile()){
                string fichier = "<tr><td width=\"20\" ><img src=\"/icons/fichier.png\" alt=\"[   ]\"></td><td><a href=\"" + chemin + "/" + list[2 + i].fileName().toStdString() + "\">" + list[2 + i].fileName().toStdString() + "</a></td></tr>";
                tcpSocket.write(fichier.c_str());
                }
                else {

                }
            }



           tcpSocket.write("<tr><th colspan=\"5\"><hr></th></tr>");
           string lien_stats = "<tr><td width=\"20\" ><img src=\"/icons/stats2.png\" alt=\"[   ]\"></td><td><a href=\"/private/statistiques\"><Strong> Statistiques du serveur </Strong></a></td></tr>";
            //tcpSocket.write("<tr><td>&nbsp</td></tr>");
            tcpSocket.write(lien_stats.c_str());
           string lien_private = "<tr><td width=\"20\" ><img src=\"/icons/reglages2.png\" alt=\"[   ]\"></td><td><a href=\"/private\"><Strong> Administrateur </Strong></a></td></tr>";
           //tcpSocket.write("<tr><td>&nbsp</td></tr>");
           tcpSocket.write(lien_private.c_str());

           tcpSocket.write("</table><br><address>Serveur web BARRAU / VILLAIN</address></body></html>");

           tcpSocket.disconnectFromHost();
           tcpSocket.waitForDisconnected();

       }else if( f.exists() == true ){

           int posext = file.rfind(".");
           string ext = file.substr(posext);
           cout << ext << endl;

           statistiques->nb_fichier_dl++;

           QFile* file = new QFile( str );
            if (!file->open(QIODevice::ReadOnly))
            {
                    delete file;
                    return;
            }




            if(ext == ".bat"){
                    Data = file->readAll();
                    string script = Data.toStdString() +" > public_html/temp/temp.txt";


                    // tcpSocket.write("<!DOCTYPE html> \r\n<html>\r\n<body>\r\n\r\n<h1>404 Not found</h1>\r\n\r\n</body>\r\n</html> \r\n");
                    // tcpSocket.write("<!DOCTYPE html> \r\n<html>\r\n<head>\r\n\r\n<h1><meta http-equiv=\"refresh\" content=\"0; URL=http://localhost:8080/503.html\">\r\n</head>\r\n</html> \r\n");
                    //tcpSocket.write(temp.txt);

                    system(script.c_str());
                    QFile* fileTemp = new QFile("public_html/temp/temp.txt");
                    if (!fileTemp->open(QIODevice::ReadOnly))
                    {
                delete fileTemp;
                return;
                    }
                    QByteArray dataTemp = fileTemp->readAll();
                    cout << dataTemp.toStdString() << endl;
                    tcpSocket.write("HTTP/1.1 200 OK \r\nContent-Type: text/plain\r\n\r\n");
                    tcpSocket.write(dataTemp);

                    fileTemp->close();

            }
            else{

                // CHOIX DU BON HEADER EN FONCTION DU TYPE DE FICHIER
                //QMimeDatabase mimDatabase;
                //QMimeType mimeType;
                mimeType = mimDatabase.mimeTypeForFile(str);
                string header = "HTTP/1.1 200 OK \r\nContent-Type: " + mimeType.name().toStdString() + +"\r\n\r\n";
                Data = file->readAll();
                //Envoi données
                tcpSocket.write(header.c_str());
                tcpSocket.write( Data );

                if(cacheableFile == 1){
                cache->toCache(str.toStdString(),Data);
                }

                //Desctructions
                file->close();


            //tcpSocket.write("HTTP/1.1 200 OK \r\nContent-Type: text/html\r\n\r\n");
            //tcpSocket.write( file->readAll() );
           // file->close();
            }
       }else{

       }
            }
    //! [2] //! [3]

        /*QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_0);
        out << (quint16)0;
        out << text;
        out.device()->seek(0);
        out << (quint16)(block.size() - sizeof(quint16));
    //! [3] //! [4]

        tcpSocket.write(block);*/
       }
            else if(realFile == 1) {
            tcpSocket.write("HTTP/1.1 503 SERVICE UNAVAILABLE \r\nContent-Type: text/html\r\n\r\n");
            statistiques->nb_erreur++;
            emit new_erreur();
            statistiques->nb_erreur_503++;
            emit new_erreur_503();


            // tcpSocket.write("<!DOCTYPE html> \r\n<html>\r\n<body>\r\n\r\n<h1>404 Not found</h1>\r\n\r\n</body>\r\n</html> \r\n");
            // tcpSocket.write("<!DOCTYPE html> \r\n<html>\r\n<head>\r\n\r\n<h1><meta http-equiv=\"refresh\" content=\"0; URL=http://localhost:8080/503.html\">\r\n</head>\r\n</html> \r\n");
            tcpSocket.write("<!DOCTYPE html>\r\n<html> \r\n<body> \r\n<h1>503 SERVICE UNAVAILABLE</h1> \r\n</body> \r\n</html>");
            }
            //Mesure temps 2
            steady_clock::time_point t2 = steady_clock::now();
            duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

            // Classement des fichiers en fin de requete


            // Affichage classement requetes
            for(int i = 0;i<StatMng->statvect.size() ;i++){
            cout << "NBREQ  "<< StatMng->statvect[i].path << " "<< StatMng->statvect[i].nbReq << endl;
            }

            cout << "---------------- CACHE INFO ----------------" << endl;
            cache->cacheInfo();
            cout << "--------------------------------------------" << endl;
            cout << time_span.count() << endl;


            //! [2] //! [3]

            /*QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << text;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
//! [3] //! [4]

    tcpSocket.write(block);*/
       }
    }
        tcpSocket.disconnectFromHost();
        tcpSocket.waitForDisconnected();
        cout << "Finishing MySocketClient::run()" << endl;

//! [4]


}

