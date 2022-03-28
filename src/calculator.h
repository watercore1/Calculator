#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QStack>
#include <QString>
#include <QVector>
#include <QtMath>
#include "compiler.h"
#include "constant.h"
#include "function.h"

// 操作符=优先级+字符
struct PriorityOp {
  int priorit;
  QChar op;
  PriorityOp() {}
  PriorityOp(int p, QChar o) : priorit(p), op(o) {}
};

class Calculator {
 public:
  Calculator();
  // 所有计算器共用一个函数库和常量库
  static QVector<Function> functions;
  static QVector<Constant> constants;
  double Calculate(const QVector<Token>& tokens);
  double Calculate(double arg1, double arg2, QChar op);

 private:
  // token 处的优先级
  int cur_priority = 0;
  // 双桟法
  QStack<double> operands;
  QStack<PriorityOp> operators;

  void TokenNumber(const QString& value);
  void TokenConstant(const QString& name, bool is_positive);
  void TokenFunction(const QString& name, const QVector<Token>& tokens, int& i,
                     bool is_positive);
  void TokenOperator(const QString& op);
  void TokenLeftBracket();
  void TokenRightBracket();
  void TokenEnd();

  // 当得到函数参数的double值后，计算函数
  double GetFunctionResult(const Function& function,
                           const QVector<double>& double_paras);
  // 弹出两个操作数和一个操作符计算一次，将结果放回操作数栈
  void CalculateOnce();
};

#endif  // CALCULATOR_H
