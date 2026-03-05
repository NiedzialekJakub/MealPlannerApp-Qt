#include "recipeview.h"
#include "ui_recipeview.h"
#include "databasemanager.h"
#include "recipenumber.h"
#include "mainwindow.h"

RecipeView::RecipeView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RecipeView)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);

    host = dynamic_cast<MainWindow*>(window());

    QPixmap pl(":/rescources/pl.png");
    QPixmap en(":/rescources/en.png");
    QPixmap clock(":/rescources/clock.png");
    QPixmap kcal(":/rescources/kcal.png");

    ui->pl->setPixmap(pl);
    ui->en->setPixmap(en);
    ui->clock_image->setPixmap(clock);
    ui->kcal_image->setPixmap(kcal);

    ui->pl->setScaledContents(true);
    ui->en->setScaledContents(true);
    ui->clock_image->setScaledContents(true);
    ui->kcal_image->setScaledContents(true);
}

RecipeView::~RecipeView()
{
    delete ui;
}

void RecipeView::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    int index = RecipeNumber::getInstance().recipeIdToDisplay;

    QString recipePL = db->getRecipePL(index);
    recipePL.replace("\n", "<br>");
    QString html = "<div style='line-height:75%;'>" + recipePL + "<div>";
    ui->textRecipePL->setHtml(html);

    QString ingredientsPL = db->getIngredientsPL(index);
    ingredientsPL.replace("\n", "<br>");
    QString html2 = "<div style='line-height:75%;'>" + ingredientsPL + "<div>";
    ui->textIngredientsPL->setHtml(html2);

    QString recipeEN = db->getRecipeEN(index);
    recipeEN = recipeEN.trimmed();
    recipeEN.replace("\n", "<br>");
    QString html3 = "<div style='line-height:75%;'>" + recipeEN + "<div>";
    ui->textRecipeEN->setHtml(html3);

    QString ingredientsEN = db->getIngredientsEN(index);
    ingredientsEN.replace("\n", "<br>");
    QString html4 = "<div style='line-height:75%;'>" + ingredientsEN + "<div>";
    ui->textIngredientsEN->setHtml(html4);

    QString path = ":/rescources/dishes/" + QString::number(index) + ".png";
    QPixmap di(path);
    ui->dish->setPixmap(di);
    //ui->dish->setScaledContents(true);
    displayOpinionPercentage();
    displayCalories();
    displayPrepareTime();

    ui->btnDLike->setEnabled(true);
    ui->btnLike->setEnabled(true);
    ui->btnDLike->show();
    ui->btnLike->show();
}

void RecipeView::on_btnBack_clicked()
{
    if(host)
    {
        host->switchToView(MainWindow::START_VIEW);
    }
}

void RecipeView::displayOpinionPercentage()
{
    int index = RecipeNumber::getInstance().recipeIdToDisplay;
    int likes = db->returnRecipeLikes(index);
    int dlikes = db->returnRecipeDlikes(index);

    double percentage = oc.returnOpinionPercentage(likes, dlikes);
    QString result = QString::number(percentage) + " %";
    ui->liketext->setText(result);
    if(percentage > 50.0){
        ui->liketext->setStyleSheet("color: green;");
    }else{
        ui->liketext->setStyleSheet("color: red;");
    }
}

void RecipeView::displayCalories()
{
    int index = RecipeNumber::getInstance().recipeIdToDisplay;
    int calories = db->returnCalories(index);
    QString result = QString::number(calories);
    ui->calories_count->setText(result);
    qDebug() << result;
}

void RecipeView::displayPrepareTime()
{
    int index = RecipeNumber::getInstance().recipeIdToDisplay;
    int time = db->returnPrepareTime(index);
    QString result = QString::number(time) + " min";
    ui->prepare_time->setText(result);
}

void RecipeView::on_btnDLike_clicked()
{
    int index = RecipeNumber::getInstance().recipeIdToDisplay;
    db->addNegativeOpinion(index);
    displayOpinionPercentage();
    ui->btnDLike->setEnabled(false);
    ui->btnLike->setEnabled(false);
    ui->btnDLike->hide();
    ui->btnLike->hide();
}
void RecipeView::on_btnLike_clicked()
{
    int index = RecipeNumber::getInstance().recipeIdToDisplay;
    db->addPositiveOpinion(index);
    displayOpinionPercentage();
    ui->btnDLike->setEnabled(false);
    ui->btnLike->setEnabled(false);
    ui->btnDLike->hide();
    ui->btnLike->hide();
}
