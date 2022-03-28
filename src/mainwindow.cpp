#include "mainwindow.h"
#include <QDebug>
#include <QStack>
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  Calculator::constants = Constant::GetConstants("./res/Constants.json");
  Calculator::functions = Function::GetFunctions("./res/Functions.json");
  foreach (auto constant, calculator.constants) {
    ui->listWidget_constants->addItem(constant.GetName());
  }
  foreach (auto function, calculator.functions) {
    ui->listWidget_functions->addItem(function.GetName());
  }
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_listWidget_constants_itemClicked(QListWidgetItem *item) {
  selected_type = 1;
  Constant constant =
      Calculator::constants[ui->listWidget_constants->currentRow()];

  QString text = QString("名称：%1\n描述：%2\n数值：%3\n")
                     .arg(constant.GetName(), constant.GetDescription(),
                          constant.GetValue());

  ui->textBrowser->setText(text);
}

void MainWindow::on_listWidget_functions_itemClicked(QListWidgetItem *item) {
  selected_type = -1;
  Function function =
      Calculator::functions[ui->listWidget_functions->currentRow()];

  QString text = QString("名称：%1\n函数体：%2\n描述：%3\n")
                     .arg(function.GetName(), function.GetExpression(),
                          function.GetDescription());
  int i = 0;
  foreach (auto parameter, function.GetParameters()) {
    i++;
    text.append(
        QString("参数%1:%2，%3\n")
            .arg(QString::number(i), parameter.name, parameter.description));
  }
  ui->textBrowser->setText(text);
}

void MainWindow::on_listWidget_constants_itemDoubleClicked(
    QListWidgetItem *item) {
  Constant constant =
      Calculator::constants[ui->listWidget_constants->currentRow()];
  QString text = constant.GetName();
  ui->lineEdit_expression->insert(text);
}

void MainWindow::on_listWidget_functions_itemDoubleClicked(
    QListWidgetItem *item) {
  Function function =
      Calculator::functions[ui->listWidget_functions->currentRow()];
  QString text = function.GetName() + '(' +
                 QString(function.GetParameters().count() - 1, ',') + ')';
  ui->lineEdit_expression->insert(text);
}

void MainWindow::on_pushButton_add_constant_clicked() {
  WidgetAddConstant *new_widget = new WidgetAddConstant();
  new_widget->show();
  connect(new_widget, &WidgetAddConstant::SendConstant, this,
          &MainWindow::AddNewConstant);
}

void MainWindow::on_pushButton_add_function_clicked() {
  WidgetAddFunction *new_window = new WidgetAddFunction();
  new_window->show();
  connect(new_window, &WidgetAddFunction::SendFunction, this,
          &MainWindow::AddNewFunction);
}

void MainWindow::on_pushButton_modify_clicked() {
  if (selected_type == 1) {
    // 此时修改常量
    int index = ui->listWidget_constants->currentRow();
    Constant constant = Calculator::constants[index];
    WidgetModifyConstant *new_window = new WidgetModifyConstant(constant);
    Calculator::constants.remove(index);
    Constant::SaveConstantsFile(Calculator::constants, "./res/Constants.json");
    ui->listWidget_constants->takeItem(index);
    new_window->show();
    connect(new_window, &WidgetModifyConstant::SendConstant, this,
            &MainWindow::AddNewConstant);
    return;
  }
  if (selected_type == -1) {
    // 此时修改函数
    int index = ui->listWidget_functions->currentRow();
    Function function = Calculator::functions[index];
    WidgetModifyFunction *new_window = new WidgetModifyFunction(function);
    Calculator::functions.remove(index);
    Function::SavaFunctionsFile(Calculator::functions, "./res/Functions.json");
    ui->listWidget_functions->takeItem(index);
    new_window->show();
    connect(new_window, &WidgetModifyFunction::SendFunction, this,
            &MainWindow::AddNewFunction);
    return;
  }
}

void MainWindow::on_pushButton_calculate_clicked() {
  try {
    compiler.LexicalAnalysis(ui->lineEdit_expression->text());
    double result = calculator.Calculate(compiler.GetTokens());
    ui->lineEdit_result->setText(QString::number(result));
  } catch (QString s) {
    QMessageBox::warning(this, "警告", s);
  }
}

void MainWindow::AddNewConstant(Constant constant) {
  Calculator::constants.append(constant);
  Constant::SaveConstantsFile(Calculator::constants, "./res/Constants.json");
  ui->listWidget_constants->addItem(constant.GetName());
  QMessageBox::information(this, "提示", "添加常量成功");
}

void MainWindow::AddNewFunction(Function function) {
  Calculator::functions.append(function);
  Function::SavaFunctionsFile(Calculator::functions, "./res/Functions.json");
  ui->listWidget_functions->addItem(function.GetName());
  QMessageBox::information(this, "提示", "添加函数成功");
}

