#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "eleve.h"
#include "activite.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_AjouterET_6_clicked();

    void on_modifier_6_clicked();

    void on_supprbtn_6_clicked();

    void on_qrcodegen_6_clicked();

    void on_chercherE_6_clicked();

    void on_trinbblcs_5_clicked();

    void on_triasc_5_clicked();

    void on_tridesc_5_clicked();

    void on_pdfeleve_clicked();

    void on_AjouterET_7_clicked();

    void on_modifier_7_clicked();

    void on_qrcodegen_7_clicked();

    void on_supprbtn_7_clicked();

    void on_chercherE_7_clicked();

    void on_trinbblcs_6_clicked();

    void on_triasc_6_clicked();

    void on_tridesc_6_clicked();
    void makePlot();
    void on_pdfeleve_2_clicked();

private:
    Ui::MainWindow *ui;
    eleve ptmp;
    activite ptmp2;
};
#endif // MAINWINDOW_H
