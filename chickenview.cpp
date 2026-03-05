#include "chickenview.h"
#include "ui_chickenview.h"
#include "databasemanager.h"
#include "recipenumber.h"
#include "mainwindow.h"
#include <QDebug>

ChickenView::ChickenView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChickenView)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);

    host = dynamic_cast<MainWindow*>(window());
}

ChickenView::~ChickenView()
{
    delete ui;
}

void ChickenView::on_btnPrzepis_clicked()
{
    QListWidgetItem *item = ui->listPL->currentItem();

    if(item != nullptr)
    {
        int row = ui->listPL->currentRow();
        qDebug() << "Wybrano: " << row + 1 + ((category - 1) * 20);
        RecipeNumber::getInstance().recipeIdToDisplay = row + 1 + ((category - 1) * 20);
        if(host){
            host->switchToView(MainWindow::RECIPE_VIEW);
        }
    }
    else{
        qDebug() << "Nic nie znaleziono";
    }
}

void ChickenView::on_btnRecipe_clicked()
{
    QListWidgetItem *item = ui->listEN->currentItem();

    if(item != nullptr)
    {
        int row = ui->listEN->currentRow();
        qDebug() << "Wybrano: " << row + 1 + ((category - 1) * 20);
        RecipeNumber::getInstance().recipeIdToDisplay = row + 1 + ((category - 1) * 20);
        if(host){
            host->switchToView(MainWindow::RECIPE_VIEW);
        }
    }
    else{
        qDebug() << "Nic nie znaleziono";
    }
}

void ChickenView::on_btnBack_clicked()
{
    if(host)
    {
        host->switchToView(MainWindow::START_VIEW);
    }
}

void ChickenView::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    ui->listPL->clear();
    ui->listEN->clear();

    category = RecipeNumber::getInstance().categoryID;
    QStringList listPL = db->getAllPLRecipes(category);
    QStringList listEN = db->getAllENRecipes(category);
    ui->listPL->addItems(listPL);
    ui->listEN->addItems(listEN);
    qDebug() << "kategoria to" << category;
}
