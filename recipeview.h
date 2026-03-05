#ifndef RECIPEVIEW_H
#define RECIPEVIEW_H

#include <QWidget>
#include <QShowEvent>
#include "opinioncount.h"

class DatabaseManager;
class MainWindow;

namespace Ui {
class RecipeView;
}

class RecipeView : public QWidget
{
    Q_OBJECT

public:
    explicit RecipeView(QWidget *parent = nullptr);
    ~RecipeView();

    int recipeIndex;

private:
    Ui::RecipeView *ui;

    DatabaseManager *db;

    MainWindow *host;

    OpinionCount oc;
    void displayOpinionPercentage();
    void displayCalories();
    void displayPrepareTime();

private slots:
    void on_btnBack_clicked();
    void on_btnDLike_clicked();
    void on_btnLike_clicked();

protected:
    void showEvent(QShowEvent *event) override;
};

#endif // RECIPEVIEW_H
