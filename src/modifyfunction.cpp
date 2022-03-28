#include "modifyfunction.h"
#include "ui_modifyfunction.h"

ModifyFunction::ModifyFunction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyFunction)
{
    ui->setupUi(this);
}

ModifyFunction::~ModifyFunction()
{
    delete ui;
}
