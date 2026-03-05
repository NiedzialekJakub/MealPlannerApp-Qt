#ifndef BREKFASTVIEW_H
#define BREKFASTVIEW_H

#include <QWidget>

class DatabaseManager;
class MainWindow;

namespace Ui {
class BrekfastView;
}

class BrekfastView : public QWidget
{
    Q_OBJECT

public:
    explicit BrekfastView(QWidget *parent = nullptr);
    ~BrekfastView();

private:
    Ui::BrekfastView *ui;

    DatabaseManager *db;
    MainWindow *host;

private slots:
    void on_btnPrzepis_clicked();
    void on_btnRecipe_clicked();
    void on_btnBack_clicked();
};

#endif // BREKFASTVIEW_H
