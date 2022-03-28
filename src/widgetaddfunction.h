#ifndef WIDGETADDFUNCTION_H
#define WIDGETADDFUNCTION_H

#include <QMessageBox>
#include <QWidget>
#include "calculator.h"
#include "compiler.h"
#include "constant.h"
#include "function.h"
#include "widgetaddparameter.h"

namespace Ui {
class WidgetAddFunction;
}

class WidgetAddFunction : public QWidget {
  Q_OBJECT

 public:
  explicit WidgetAddFunction(QWidget *parent = nullptr);
  ~WidgetAddFunction();

 signals:
  // 发送 function 给主窗口
  void SendFunction(Function function);

 private slots:
  void on_pushButton_add_parameter_clicked();
  void on_pushButton_add_function_clicked();
  void AddParameter(Parameter parameter);

 private:
  Ui::WidgetAddFunction *ui;
  QString name;
  QString description;
  QVector<Parameter> parameters;
  QString expression;
};

#endif  // WIDGETADDFUNCTION_H
