#ifndef WIDGETMODIFYCONSTANT_H
#define WIDGETMODIFYCONSTANT_H

#include <QMessageBox>
#include <QWidget>
#include "calculator.h"
#include "compiler.h"
#include "constant.h"
#include "function.h"

namespace Ui {
class WidgetModifyConstant;
}

class WidgetModifyConstant : public QWidget {
  Q_OBJECT

 public:
  explicit WidgetModifyConstant(QWidget *parent = nullptr);
  WidgetModifyConstant(const Constant& constant, QWidget *parent = nullptr);
  ~WidgetModifyConstant();
 signals:
  void SendConstant(Constant constant);
 private slots:
  void on_pushButton_modify_clicked();

  void on_pushButton_delete_clicked();

 private:
  Ui::WidgetModifyConstant *ui;
};

#endif  // WIDGETMODIFYCONSTANT_H
