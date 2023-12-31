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

#include <QtWidgets>
#include <QtNetwork>

#include <stdlib.h>

#include "dialog.h"


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    statusLabel = new QLabel;
    requettesOverflow = new QLabel;
    test = new QLabel;

    //statistiques = new Stats;



    quitButton = new QPushButton(tr("Quit"));
    quitButton->setAutoDefault(false);





    if (!server.listen(QHostAddress::Any, 8080)) {
        QMessageBox::critical(this, tr("Small WEB Server"),
                              tr("Unable to start the server: %1.")
                              .arg(server.errorString()));
        close();
        return;
    }

    statusLabel->setText(tr("The server is running on port %1\n"
                            "Use internet navigator now.")
                         .arg(server.serverPort()));
    if(server.hasPendingConnections()){
    requettesOverflow-> setText(tr("Il y a des requetes en attentes"));
    }

    requettesOverflow-> setText(tr("Il n'y a pas de requete en attente"));


    //test->setText(tr("Le serveur a reçu %1 requêtes").arg(server.get_nb_requete(server.compteur_nb_requete, server.socketDescriptor())));



    connect(quitButton,SIGNAL(clicked()), this, SLOT(close()));


    QHBoxLayout *buttonLayout = new QHBoxLayout;
    //buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);
    //buttonLayout->addStretch(1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(statusLabel);
    mainLayout->addLayout(buttonLayout);
    mainLayout -> addWidget(requettesOverflow);
    mainLayout -> addWidget(test);

    setLayout(mainLayout);




    setWindowTitle(tr("Small Web Server"));
}
