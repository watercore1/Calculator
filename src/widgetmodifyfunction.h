#ifndef WIDGETMODIFYFUNCTION_H
#define WIDGETMODIFYFUNCTION_H

#include <QMessageBox>
#include <QWidget>
#include "calculator.h"
#include "compiler.h"
#include "constant.h"
#include "function.h"

namespace Ui {
class WidgetModifyFunction;
}

class WidgetModifyFunction : public QWidget {
  Q_OBJECT

 public:
  explicit WidgetModifyFunction(QWidget *parent = nullptr);
  WidgetModifyFunction(const Function& function, QWidget *parent = nullptr);
  ~WidgetModifyFunction();
 signals:
  void SendFunction(Function function);
 private slots:
  void on_pushButton_modify_clicked();

  void on_pushButton_delete_clicked();

 private:
  Ui::WidgetModifyFunction *ui;
  QString name;
  QString description;
  QVector<Parameter> parameters;
  QString expression;
};

#endif  // WIDGETMODIFYFUNCTION_H
