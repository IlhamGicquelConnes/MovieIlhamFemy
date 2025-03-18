#include <QApplication>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QTableView>
#include <QStandardItemModel>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Créer une connexion à la base de données SQLite
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("BiblioMovie_FemyIlham.db"); // Chemin vers ton fichier .db

    // Vérifier si la connexion réussit
    if (!db.open()) {
        QMessageBox::critical(nullptr, "Erreur", "Impossible de se connecter à la base de données.");
        return -1;
    }

    // Fenêtre principale
    QWidget window;
    window.setWindowTitle("Film Rating Application");
    window.resize(800, 600);

    // Création d'un layout pour ajouter la table
    QVBoxLayout *layout = new QVBoxLayout(&window);

    // Créer une vue de table pour afficher les films
    QTableView *tableView = new QTableView(&window);
    QStandardItemModel *model = new QStandardItemModel();

    // Définir les en-têtes de colonnes
    model->setHorizontalHeaderLabels({"ID", "Titre", "Réalisateur", "Genre", "Année", "Durée"});

    // Exécuter une requête pour récupérer les films de la base de données
    QSqlQuery query("SELECT * FROM movies");
    while (query.next()) {
        int id = query.value("id_film").toInt();
        QString titre = query.value("titre").toString();
        QString realisateur = query.value("realisateur").toString();
        QString genre = query.value("genre").toString();
        int annee = query.value("annee").toInt();
        int duree = query.value("duree").toInt();

        QList<QStandardItem*> row;
        row << new QStandardItem(QString::number(id))
            << new QStandardItem(titre)
            << new QStandardItem(realisateur)
            << new QStandardItem(genre)
            << new QStandardItem(QString::number(annee))
            << new QStandardItem(QString::number(duree));

        model->appendRow(row);
    }

    // Lier le modèle à la vue
    tableView->setModel(model);
    tableView->resizeColumnsToContents();

    // Ajouter la table au layout
    layout->addWidget(tableView);

    window.setLayout(layout);
    window.show();

    return app.exec();
}

