#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

class StarterView;
class ChickenView;
class RecipeView;
class FridgeView;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    enum ViewIndex{
        START_VIEW = 0,
        CHICKEN_VIEW = 1,
        RECIPE_VIEW = 2,
        FRIDGE_VIEW = 3
    };

    void switchToView(int index);

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QStackedWidget *stackedWidget;
    StarterView *startView = nullptr;
    ChickenView *chickenView = nullptr;
    RecipeView *recipeView = nullptr;
    FridgeView *fridgeview = nullptr;
};
#endif // MAINWINDOW_H
