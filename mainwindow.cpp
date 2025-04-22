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

    ui->stackedWidget->setCurrentIndex(0);
    rechercher();
}

//############################################################################################################
MainWindow::~MainWindow()
{
    delete ui;
}

//############################################################################################################

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

        if ( ui->checkBoxRealisateur->isChecked() )
            ajouterConditionRealisateur(requete);

        if ( ui->checkBoxTitre->isChecked() )
            ajouterConditionTitre(requete);

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
// ajoute la condition pour le réalisateur
void MainWindow::ajouterConditionRealisateur( QString & requete)
{
    requete.push_back( QString(" AND realisateur LIKE"));
    requete.push_back( ui->realisateurEdit->text());
    requete.push_back( QString("'"));
}

//############################################################################################################
// ajoute la condition pour le titre
void MainWindow::ajouterConditionTitre( QString & requete){
    requete.push_back( QString(" AND titre LIKE '"));
    requete.push_back( ui->titreEdit->text());
    requete.push_back( QString("'"));
}


//############################################################################################################
// appui du boutton pushButtonRechercher
void MainWindow::on_pushButtonRechercher_clicked()
{
    rechercher();
}

//############################################################################################################

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

//############################################################################################################

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

//############################################################################################################

void MainWindow::on_reponseTable_cellClicked(int row, int column)
{
    QString titre = ui->reponseTable->item(row, 1)->text();
    ui->label_titre_film->setText( titre );

    QString realisateur = ui->reponseTable->item(row, 2)->text();
    ui->label_realisateur->setText( realisateur );

    QString genre = ui->reponseTable->item(row, 3)->text();
    ui->label_genre->setText( genre );

    QString annee = ui->reponseTable->item(row, 4)->text();
    ui->label_annee->setText( annee );

    QString duree = ui->reponseTable->item(row, 5)->text();
    ui->label_duree->setText("<b>Duree :</b> " + duree + " min");

    QString resume = ui->reponseTable->item(row, 6)->text();
    ui->label_resume->setText( "Resume : " + resume );

    ui->stackedWidget->setCurrentIndex(1);
}

