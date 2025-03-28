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
    void ajouterConditionRealisateur( QString & requete);
    void ajouterConditionTitre( QString & requete);

private slots:
    void on_pushButtonRechercher_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_reponseTable_cellClicked(int row, int column);

    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
