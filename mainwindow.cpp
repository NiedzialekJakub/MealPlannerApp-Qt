#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "starterview.h"
#include "chickenview.h"
#include "recipeview.h"
#include "fridgeview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    startView = new StarterView(this);
    chickenView = new ChickenView(this);
    recipeView = new RecipeView(this);
    fridgeview = new FridgeView(this);

    stackedWidget->addWidget(startView);
    stackedWidget->addWidget(chickenView);
    stackedWidget->addWidget(recipeView);
    stackedWidget->addWidget(fridgeview);

    stackedWidget->setCurrentIndex(START_VIEW);


    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::switchToView(int index)
{
    stackedWidget->setCurrentIndex(index);
}
