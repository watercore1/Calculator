#include "widgetmodifyfunction.h"
#include "ui_widgetmodifyfunction.h"

WidgetModifyFunction::WidgetModifyFunction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetModifyFunction)
{
    ui->setupUi(this);
}

WidgetModifyFunction::WidgetModifyFunction(const Function& function,QWidget *parent):QWidget(parent),
    ui(new Ui::WidgetModifyFunction)
{
    ui->setupUi(this);
    name = function.GetName();
    description = function.GetDescription();
    parameters =function.GetParameters();
    expression = function.GetExpression();

    ui->lineEdit_name->setText(name);
    ui->lineEdit_description->setText(description);
    QString text;
    text += "(";
    foreach(auto para,function.GetParameters()){
    text += para.name + ",";
    }
    text.chop(1);
    text+=")";
    ui->lineEdit_parameters->setText(text);
    ui->lineEdit_expression->setText(expression);
}

WidgetModifyFunction::~WidgetModifyFunction()
{
    delete ui;
}

void WidgetModifyFunction::on_pushButton_modify_clicked()
{
  name = ui->lineEdit_name->text();
  description = ui->lineEdit_description->text();
  expression = ui->lineEdit_expression->text();

  // 检验函数是否满足要求
  if (not Compiler::IsIdentifier(name)) {
    QMessageBox::warning(this, "警告", "标识符 " + name + " 非法。");
    return;
  }
  if (Constant::IfConstantExist(Calculator::constants, name) ||
      Function::IfFunctionExist(Calculator::functions, name)) {
    QMessageBox::warning(this, "警告", "标识符 " + name + " 已存在。");
    return;
  }
  if (parameters.empty()) {
    QMessageBox::warning(this, "警告", "参数不能为空");
    return;
  }
  try {
    Compiler compiler;
    compiler.LexicalAnalysis(expression);
  } catch (QString s) {
    QMessageBox::warning(this, "警告", s);
    return;
  }
  Function function(name, description, parameters, expression);
  emit SendFunction(function);
  this->close();
}


void WidgetModifyFunction::on_pushButton_delete_clicked()
{
    this->close();
}

