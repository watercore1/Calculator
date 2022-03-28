#include "widgetaddparameter.h"
#include "ui_widgetaddparameter.h"

WidgetAddParameter::WidgetAddParameter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetAddParameter)
{
    ui->setupUi(this);
}

WidgetAddParameter::~WidgetAddParameter()
{
    delete ui;
}

void WidgetAddParameter::on_pushButton_add_parameter_clicked()
{
  Parameter parameter;
  parameter.name = ui->lineEdit_name->text();
  parameter.description = ui->lineEdit_description->text();

  // 测试是否满足要求
  if (not Compiler::IsIdentifier(parameter.name)) {
    QMessageBox::warning(this, "警告", "参数 " + parameter.name + " 非法。");
    return;
  }
  emit SendParameter(parameter);
  this->close();
}



