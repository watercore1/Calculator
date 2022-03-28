#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include "calculator.h"
#include "compiler.h"
#include "function.h"
#include "widgetaddconstant.h"
#include "widgetaddfunction.h"
#include "widgetmodifyconstant.h"
#include "widgetmodifyfunction.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_listWidget_constants_itemClicked(QListWidgetItem *item);
  void on_listWidget_functions_itemClicked(QListWidgetItem *item);
  void on_listWidget_constants_itemDoubleClicked(QListWidgetItem *item);
  void on_listWidget_functions_itemDoubleClicked(QListWidgetItem *item);
  void on_pushButton_add_constant_clicked();
  void on_pushButton_add_function_clicked();
  void on_pushButton_modify_clicked();
  void on_pushButton_calculate_clicked();

  void AddNewConstant(Constant constant);
  void AddNewFunction(Function function);

 private:
  Ui::MainWindow *ui;
  Compiler compiler;
  Calculator calculator;
  // 判断当前选中的项是常量还是函数
  // 常量为 1，函数为 -1
  int selected_type = 0;
};
#endif  // MAINWINDOW_H
