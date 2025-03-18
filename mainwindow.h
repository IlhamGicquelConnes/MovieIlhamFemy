#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QtSql>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void rechercher();
    void afficherResultat( QSqlQuery query );
    void ajouterConditionAnnnee( QString & requete);

private slots:
    void on_pushButtonRechercher_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
