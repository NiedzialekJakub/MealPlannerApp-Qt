#ifndef CHICKENVIEW_H
#define CHICKENVIEW_H

#include <QWidget>
#include <QShowEvent>

class DatabaseManager;
class MainWindow;

namespace Ui {
class ChickenView;
}

class ChickenView : public QWidget
{
    Q_OBJECT

public:
    explicit ChickenView(QWidget *parent = nullptr);
    ~ChickenView();

private:
    Ui::ChickenView *ui;

    DatabaseManager *db;
    MainWindow *host;

    int category;

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void on_btnPrzepis_clicked();
    void on_btnRecipe_clicked();
    void on_btnBack_clicked();
};

#endif // CHICKENVIEW_H
