#ifndef WIDGETADDCONSTANT_H
#define WIDGETADDCONSTANT_H

#include <QMessageBox>
#include <QWidget>
#include "calculator.h"
#include "compiler.h"
#include "constant.h"
#include "function.h"

namespace Ui {
class WidgetAddConstant;
}

class WidgetAddConstant : public QWidget {
  Q_OBJECT

 public:
  explicit WidgetAddConstant(QWidget *parent = nullptr);
  ~WidgetAddConstant();

 signals:
  // 发送 constant 给主窗口
  void SendConstant(Constant constant);

 private slots:
  void on_pushButton_add_clicked();

 private:
  Ui::WidgetAddConstant *ui;
};

#endif  // WIDGETADDCONSTANT_H
