#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <iostream>
#include <QTableWidgetItem>

//############################################################################################################
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

//############################################################################################################
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::rechercher()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); // QSQLITE
    db.setDatabaseName("../MiniProjetn2_FemyIlham/BiblioMovie_FemyIlham.db");

    if( ! db.open() )
        std::cout << "La base de données n'a pas été ouverte" << std::endl;
    else
    {        std::cout << "La base de données a  été ouverte" << std::endl;

        QSqlQuery query;

        QString requete("SELECT * FROM film WHERE 1");

        if ( ui->checkBoxAnnee->isChecked() )
            ajouterConditionAnnnee(requete);

        std::cout << requete.toStdString() << std::endl;
        query.prepare( requete );

        if( !query.exec() )
        {
            // Error Handling, check query.lastError(), probably return
        }

        afficherResultat(query);

        db.close();
    }
}

//############################################################################################################
// affichage du résultat d'une requête donnée en paramètre
void MainWindow::afficherResultat( QSqlQuery query )
{
    QSqlRecord record = query.record();

    ui->reponseTable->clear(); // on efface toute la table
    ui->reponseTable->setRowCount(0); // on enlève toutes les lignes
    ui->reponseTable->setColumnCount( record.count() ); // on initialise le nombre de colonnes de la table de réponse

    // affichage des titres de colonnes
    for ( int colonne = 0; colonne != record.count(); ++colonne )
        ui->reponseTable->setHorizontalHeaderItem(colonne, new QTableWidgetItem(record.fieldName(colonne)) );

    // ajout des lignes
    int ligne = 0;
    while( query.next() )
    {
        ui->reponseTable->insertRow(ligne); // on ajoute une ligne

        // pour chaque colonne, on ajoute la valeur
        for ( int colonne = 0; colonne != record.count(); ++colonne )
        {
            QString valeur = query.value( colonne ).toString(); // récupération de la valeur
            ui->reponseTable->setItem(ligne, colonne, new QTableWidgetItem(valeur) ); // ajout de la valeur dans la table
        }

        ligne++;
    }
}


//############################################################################################################
// ajoute la condition sur l'année de sortie
void MainWindow::ajouterConditionAnnnee( QString & requete)
{
    requete.push_back( QString(" and annee >= "));
    requete.push_back( QString::number( ui->annee_min->value() ));
    requete.push_back( QString(" and annee <= " ));
    requete.push_back( QString::number( ui->annee_max->value() ));
}


//############################################################################################################
// appui du boutton pushButtonRechercher
void MainWindow::on_pushButtonRechercher_clicked()
{
    rechercher();
}
