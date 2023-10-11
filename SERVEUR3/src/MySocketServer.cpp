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

#include "MySocketServer.h"
#include "MySocketClient.h"
#include "Fstat.h"
#include "FstatManager.h"

#include <stdlib.h>

//! [0]
MySocketServer::MySocketServer(QObject *parent)
    : QTcpServer(parent)
{
    // CRATION DES STATISTIQUES (VIT DES QUE LE SERVEUR SE LANCE)
    //Stats *statistiques = new Stats();
    //statistiques.setGeometry(0, 0, 500, 200);
    //statistiques = Stats(&ServiceAvailability);
    statistiques.setGeometry(0, 0,300, 100);
    statistiques.show();
    cache = MyCache(2);
    StatMng = FstatManager();
    ServiceAvailability = 1;


    //statistiques.resize(600, 200);

    }

void MySocketServer::incomingConnection(qintptr socketDescriptor)
{
    cout << "(II) Launching the Network monitor process" << endl;

    // CREATION DE L'OBJET EN CHARGE DES REPONSES RESEAU
    MySocketClient *thread = new MySocketClient(socketDescriptor, this, &statistiques, &cache, &StatMng, &ServiceAvailability);


    //ICI ON VEUT INDIQUER QUE ON A RECU UNE NOUVELLE REQUETE.
    // ON EMET LE SIGNAL NEW_REQUETE POUR INDIQUER QUE L'ON A BIEN RECU UNE NOUVELLE REQUETE

    //emit new_requete();


    //cout << "nouvelle requete recue \n" << endl;

    //
    // ON INDIQUE QUE LORSQU'UN CLIENT SE CONNECTE ON DELEGE LA REPONSE
    // AU PROCESSUS DEFINI CI DESSUS...
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    // ON DEMARRE LE PROCESSUS DE REPONSE POUR LE METTRE EN ATTENTE !
    thread->start();

    // PUIS ON REND LA MAIN EN ATTENTE D'UN CLIENT
    cout << "(II) Network monitor process launch : OK" << endl;
}



