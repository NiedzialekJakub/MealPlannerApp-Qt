#ifndef FRIDGEVIEW_H
#define FRIDGEVIEW_H

#include <QWidget>
#include <QShowEvent>

class DatabaseManager;
class MainWindow;

namespace Ui {
class FridgeView;
}

class FridgeView : public QWidget
{
    Q_OBJECT

public:
    explicit FridgeView(QWidget *parent = nullptr);
    ~FridgeView();

private:
    Ui::FridgeView *ui;

    DatabaseManager *db;
    MainWindow *host;

    QStringList integreintsList;
    QStringList integreintsPL;
    QStringList integreintsEN;

private slots:
    void on_btnDodaj_clicked();
    void on_btnAdd_clicked();
    void on_btnPrzepis_clicked();
    void on_btnRecipe_clicked();
    void on_btnBack_clicked();
    void on_btnCzysc_clicked();
    void on_btnClear_clicked();

protected:
    void showEvent(QShowEvent *event) override;
};

#endif // FRIDGEVIEW_H
