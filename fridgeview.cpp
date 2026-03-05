#include "fridgeview.h"
#include "ui_fridgeview.h"
#include "databasemanager.h"
#include "mainwindow.h"
#include "recipenumber.h"

FridgeView::FridgeView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FridgeView)
{
    ui->setupUi(this);

    host = dynamic_cast<MainWindow*>(window());

    this->setAttribute(Qt::WA_StyledBackground, true);
}

FridgeView::~FridgeView()
{
    delete ui;
}

void FridgeView::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    ui->listPL->clear();
    ui->listEN->clear();
    ui->listRecipesEN->clear();
    ui->listRecipesPL->clear();
    ui->ingredientEN->clear();
    ui->ingredientPL->clear();

    ui->listPL->addItems(db->getAllPLIngredients());
    ui->listEN->addItems(db->getAllENIngredients());

    integreintsList.clear();
    integreintsEN.clear();
    integreintsPL.clear();
}

void FridgeView::on_btnDodaj_clicked()
{
    ui->listRecipesPL->clear();
    ui->listRecipesEN->clear();
    ui->ingredientEN->clear();
    ui->ingredientPL->clear();

    int rowNumber = ui->listPL->currentRow();
    if(rowNumber == -1){
        return;
    }

    QString nameIngredient = ui->listEN->item(rowNumber)->text();

    qDebug() << "skladnik: " << nameIngredient;
    integreintsList.append(nameIngredient);
    qDebug() << "skladniki wszystkie: " << integreintsList;
    ui->listRecipesPL->addItems(db->getRecipesByIngredientsPL(integreintsList));
    ui->listRecipesEN->addItems(db->getRecipesByIngredientsEN(integreintsList));
    qDebug() << "potrawy pasujace: " << db->getRecipesByIngredientsPL(integreintsList);

    QString ingredientPL = ui->listPL->item(rowNumber)->text();
    integreintsPL.append(ingredientPL);
    QString ingredientsOneLinePL = integreintsPL.join(", ");
    ui->ingredientPL->setText(ingredientsOneLinePL);
    QString ingredientEN = ui->listEN->item(rowNumber)->text();
    integreintsEN.append(ingredientEN);
    QString ingredientsOneLineEN = integreintsEN.join(", ");
    ui->ingredientEN->setText(ingredientsOneLineEN);
}
void FridgeView::on_btnAdd_clicked()
{
    ui->listRecipesEN->clear();
    ui->listRecipesPL->clear();
    ui->ingredientEN->clear();
    ui->ingredientPL->clear();

    int rowNumber = ui->listEN->currentRow();
    if(rowNumber == -1){
        return;
    }

    QString nameIngredient = ui->listEN->item(rowNumber)->text();

    qDebug() << "skladnik: " << nameIngredient;
    integreintsList.append(nameIngredient);
    qDebug() << "skladniki wszystkie: " << integreintsList;
    ui->listRecipesEN->addItems(db->getRecipesByIngredientsEN(integreintsList));
    ui->listRecipesPL->addItems(db->getRecipesByIngredientsPL(integreintsList));

    QString ingredientsOneLine = integreintsList.join(", ");
    ui->ingredientPL->setText(ingredientsOneLine);

    QString ingredientPL = ui->listPL->item(rowNumber)->text();
    integreintsPL.append(ingredientPL);
    QString ingredientsOneLinePL = integreintsPL.join(", ");
    ui->ingredientPL->setText(ingredientsOneLinePL);
    QString ingredientEN = ui->listEN->item(rowNumber)->text();
    integreintsEN.append(ingredientEN);
    QString ingredientsOneLineEN = integreintsEN.join(", ");
    ui->ingredientEN->setText(ingredientsOneLineEN);
}

void FridgeView::on_btnPrzepis_clicked()
{
    int rowNumber = ui->listRecipesPL->currentRow();
    QString recipeName = ui->listRecipesPL->item(rowNumber)->text();
    int id = db->ReturnIDByRecipeName(recipeName);
    qDebug() << id;

    RecipeNumber::getInstance().recipeIdToDisplay = id;
    if(host){
        host->switchToView(MainWindow::RECIPE_VIEW);
    }
}
void FridgeView::on_btnRecipe_clicked()
{
    int rowNumber = ui->listRecipesEN->currentRow();
    QString recipeName = ui->listRecipesEN->item(rowNumber)->text();
    int id = db->ReturnIDByRecipeName(recipeName);
    qDebug() << id;

    RecipeNumber::getInstance().recipeIdToDisplay = id;
    if(host){
        host->switchToView(MainWindow::RECIPE_VIEW);
    }
}

void FridgeView::on_btnBack_clicked()
{
    if(host){
        host->switchToView(MainWindow::START_VIEW);
    }
}

void FridgeView::on_btnCzysc_clicked()
{
    ui->ingredientEN->clear();
    ui->ingredientPL->clear();
    ui->listRecipesPL->clear();
    ui->listRecipesEN->clear();
    integreintsPL.clear();
    integreintsEN.clear();
}
void FridgeView::on_btnClear_clicked()
{
    ui->ingredientEN->clear();
    ui->ingredientPL->clear();
    ui->listRecipesPL->clear();
    ui->listRecipesEN->clear();
    integreintsPL.clear();
    integreintsEN.clear();
}
