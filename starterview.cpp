#include "starterview.h"
#include "ui_starterview.h"
#include "mainwindow.h"
#include "recipenumber.h"

StarterView::StarterView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StarterView)
{
    ui->setupUi(this);

    if(dbManager.init()){
        dbManager.addDumnyData();
    }

    this->setAttribute(Qt::WA_StyledBackground, true);

    host = dynamic_cast<MainWindow*>(window());
}

StarterView::~StarterView()
{
    delete ui;
}

void StarterView::switchToRecipeView(int id)
{
    RecipeNumber::getInstance().categoryID = id;
    if(host){
        host->switchToView(MainWindow::CHICKEN_VIEW);
    }
}

void StarterView::on_btnFridge_clicked()
{
    if(host){
        host->switchToView(MainWindow::FRIDGE_VIEW);
    }
}

void StarterView::on_btnChicken_clicked()
{
    switchToRecipeView(1);
}

void StarterView::on_btnBreakfrast_clicked()
{
    switchToRecipeView(2);
}

void StarterView::on_btnBeef_clicked()
{
    switchToRecipeView(3);
}

void StarterView::on_btnPork_clicked()
{
    switchToRecipeView(4);
}

void StarterView::on_btnSandwich_clicked()
{
    switchToRecipeView(5);
}

void StarterView::on_btnSoup_clicked()
{
    switchToRecipeView(6);
}

void StarterView::on_btnSeaFood_clicked()
{
    switchToRecipeView(7);
}
void StarterView::on_btnDesserts_clicked()
{
    switchToRecipeView(8);
}
void StarterView::on_btnFastFood_clicked()
{
    switchToRecipeView(9);
}
void StarterView::on_btnPasta_clicked()
{
    switchToRecipeView(10);
}
