#ifndef STARTERVIEW_H
#define STARTERVIEW_H

#include <QWidget>
#include "databasemanager.h"

class MainWindow;

namespace Ui {
class StarterView;
}

class StarterView : public QWidget
{
    Q_OBJECT

public:
    explicit StarterView(QWidget *parent = nullptr);
    ~StarterView();

private:
    Ui::StarterView *ui;

    DatabaseManager dbManager;
    MainWindow *host;

    void switchToRecipeView(int id);

private slots:
    void on_btnChicken_clicked();
    void on_btnBreakfrast_clicked();
    void on_btnBeef_clicked();
    void on_btnPork_clicked();
    void on_btnSandwich_clicked();
    void on_btnSoup_clicked();
    void on_btnSeaFood_clicked();
    void on_btnDesserts_clicked();
    void on_btnFastFood_clicked();
    void on_btnPasta_clicked();

    void on_btnFridge_clicked();
};

#endif // STARTERVIEW_H
