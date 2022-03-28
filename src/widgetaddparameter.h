#ifndef WIDGETADDPARAMETER_H
#define WIDGETADDPARAMETER_H

#include <QMessageBox>
#include <QWidget>
#include "calculator.h"
#include "constant.h"
#include "function.h"

namespace Ui {
class WidgetAddParameter;
}

class WidgetAddParameter : public QWidget {
  Q_OBJECT

 public:
  explicit WidgetAddParameter(QWidget *parent = nullptr);
  ~WidgetAddParameter();

 signals:
  // 发送 parameter 给函数窗口
  void SendParameter(Parameter parameter);

 private slots:
  void on_pushButton_add_parameter_clicked();

 private:
  Ui::WidgetAddParameter *ui;
};

#endif  // WIDGETADDPARAMETER_H
