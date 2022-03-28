#include "widgetaddfunction.h"
#include "ui_widgetaddfunction.h"

WidgetAddFunction::WidgetAddFunction(QWidget *parent)
    : QWidget(parent), ui(new Ui::WidgetAddFunction) {
  ui->setupUi(this);
}

WidgetAddFunction::~WidgetAddFunction() { delete ui; }

void WidgetAddFunction::on_pushButton_add_parameter_clicked() {
  WidgetAddParameter *new_widget = new WidgetAddParameter();
  new_widget->show();
  connect(new_widget, &WidgetAddParameter::SendParameter, this,
          &WidgetAddFunction::AddParameter);
}

void WidgetAddFunction::on_pushButton_add_function_clicked() {
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
    QMessageBox::warning(this, "警告", "参数不能为空。");
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

void WidgetAddFunction::AddParameter(Parameter parameter) {
  if (parameters.empty()) {
    parameters.append(parameter);
    QString text = "(" + parameter.name + ")";
    ui->lineEdit_parameters->setText(text);
    QMessageBox::information(this, "提示", "添加参数成功");
  }

  else {
    // 首先判断是否存在同名参数
    foreach (auto para, parameters) {
      if (para.name == parameter.name) {
        QMessageBox::warning(this, "警告",
                             "参数 " + parameter.name + " 已存在。");
        return;
      }
    }

    // 如果不存在则添加参数
    parameters.append(parameter);
    QString text = ui->lineEdit_parameters->text().replace(
        ")", "," + parameter.name + ")");
    ui->lineEdit_parameters->setText(text);
    QMessageBox::information(this, "提示", "添加参数成功");
  }
}

