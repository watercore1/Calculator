#include "widgetaddconstant.h"
#include "ui_widgetaddconstant.h"

WidgetAddConstant::WidgetAddConstant(QWidget *parent)
    : QWidget(parent), ui(new Ui::WidgetAddConstant) {
  ui->setupUi(this);
}

WidgetAddConstant::~WidgetAddConstant() { delete ui; }

void WidgetAddConstant::on_pushButton_add_clicked() {
  QString name = ui->lineEdit_name->text();
  QString description = ui->lineEdit_description->text();
  QString value = ui->lineEdit_value->text();

  // 测试是否满足要求
  if (not Compiler::IsIdentifier(name)) {
    QMessageBox::warning(this, "警告", "标识符 " + name + " 非法。");
    return;
  }
  if (Constant::IfConstantExist(Calculator::constants, name) ||
      Function::IfFunctionExist(Calculator::functions, name)) {
    QMessageBox::warning(this, "警告", "标识符 " + name + " 已存在。");
    return;
  }
  if (not Compiler::IsValue(value)) {
    QMessageBox::warning(this, "警告", "数值 " + value + " 非法。");
    return;
  }
  Constant constant(name, description, value);
  emit SendConstant(constant);
  this->close();
}


