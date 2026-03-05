#include "brekfastview.h"
#include "ui_brekfastview.h"
#include "databasemanager.h"
#include "recipenumber.h"
#include "mainwindow.h"

BrekfastView::BrekfastView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BrekfastView)
{
    ui->setupUi(this);
}

BrekfastView::~BrekfastView()
{
    delete ui;
}
