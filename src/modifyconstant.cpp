#include "modifyconstant.h"
#include "ui_modifyconstant.h"

ModifyConstant::ModifyConstant(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyConstant)
{
    ui->setupUi(this);
}

ModifyConstant::~ModifyConstant()
{
    delete ui;
}
