#include "calculator.h"

QVector<Function> Calculator::functions;
QVector<Constant> Calculator::constants;
Calculator::Calculator() {}

double Calculator::Calculate(const QVector<Token>& tokens) {
  cur_priority = 0;
  operands.clear();
  operators.clear();

  for (int i = 0; i < tokens.size(); i++) {
    QString value = tokens[i].value;
    switch (tokens[i].type) {
      // 处理数字
      case kNumber: {
        TokenNumber(value);
        break;
      }
      // 处理标识符分为常数和函数两种情况
      case kIdentifier: {
        bool is_positive = true;
        if (value.front() == '-') {
          value.remove(0, 1);
          is_positive = false;
        }
        if (Constant::IfConstantExist(constants, value)) {
          TokenConstant(value, is_positive);
          break;
        }
        if (Function::IfFunctionExist(functions, value)) {
          TokenFunction(value, tokens, i, is_positive);
          break;
        }
        throw QString("标识符 %1 未找到定义").arg(value);
      }
      // 处理运算符
      case kOperator: {
        TokenOperator(value);
        break;
      }
      // 处理左括号
      case kLeftBracket: {
        TokenLeftBracket();
        break;
      }
      // 处理右括号
      case kRightBracket: {
        TokenRightBracket();
        break;
      }
      // 处理结束符:依次计算双桟元素
      case kEnd: {
        TokenEnd();
        break;
      }
    }
  }
  if (operands.empty()) return 0;
  return operands.pop();
}

double Calculator::Calculate(double arg1, double arg2, QChar op) {
  double result = 0;
  switch (op.unicode()) {
    case u'+': {
      result = arg1 + arg2;
      break;
    }

    case u'-': {
      result = arg1 - arg2;
      break;
    }

    case u'*': {
      result = arg1 * arg2;
      break;
    }

    case u'/': {
      result = arg1 / arg2;
      break;
    }

    case u'%': {
      result = qRound(arg1) % qRound(arg2);
      break;
    }

    case u'^': {
      result = qPow(arg1, arg2);
      break;
    }
  }
  return result;
}

void Calculator::TokenNumber(const QString& value) {
  bool ok;
  operands.push(value.toDouble(&ok));
  if (ok == false) throw QString("数 %1 不合法。").arg(value);
}

void Calculator::TokenConstant(const QString& name, bool is_positive) {
  Constant constant = Constant::FindConstant(constants, name);
  if (is_positive)
    operands.push(constant.GetValue().toDouble());
  else
    operands.push(-1 * constant.GetValue().toDouble());
}

void Calculator::TokenFunction(const QString& name,
                               const QVector<Token>& tokens, int& i,
                               bool is_positive) {
  Function function = Function::FindFunction(functions, name);
  if (tokens[i + 1].type == kLeftBracket) {
    // 将参数都计算成 double
    QVector<double> double_paras;
    // 注意：一个参数对应一个 tokens
    QVector<Token> para_tokens;
    // 参数内的括号对数
    int bracket_num = 0;
    int j;
    for (j = i + 2; j < tokens.size(); j++) {
      // 如果读到逗号且括号数量对齐
      // 说明读取完一个参数，将其计算为 double 后加入到参数中
      if (tokens[j].value == "," && bracket_num == 0) {
        para_tokens.append(Token(kEnd, "#"));
        // 使用递归的思想计算
        Calculator sub_calculator;
        double_paras.append(sub_calculator.Calculate(para_tokens));
        para_tokens.clear();
        continue;
      }
      if (tokens[j].type == kLeftBracket) {
        bracket_num++;
      }
      if (tokens[j].type == kRightBracket) {
        if (bracket_num == 0) {
          // 如果读到右括号且括号数量对齐
          // 说明所有参数已读取完毕
          if (para_tokens.count() > 0) {
            para_tokens.append(Token(kEnd, "#"));
            Calculator sub_calculator;
            double_paras.append(sub_calculator.Calculate(para_tokens));
            para_tokens.clear();
          }
          break;
        }
        bracket_num--;
      }
      // 除了逗号和结束右括号，都放入参数tokens中
      para_tokens.append(tokens[j]);
    }
    if (double_paras.count() != function.GetParameters().count()) {
      throw QString("函数 %1 参数个数不匹配。").arg(function.GetName());
    }
    if (is_positive)
      operands.push(GetFunctionResult(function, double_paras));
    else
      operands.push(-1 * GetFunctionResult(function, double_paras));
    i = j;
  } else
    throw QString("函数 %1 后应为括号。").arg(function.GetName());
}

void Calculator::TokenOperator(const QString& op) {
  int priority = cur_priority;
  // 这三个运算符优先级加一
  if (op == "*" || op == "/" || op == "%") {
    priority += 1;
  }
  // 乘方运算符加二
  if (op == "^") {
    priority += 2;
  }

  // 如果运算符栈中栈顶运算符的优先级更高
  // 则取出操作数栈顶两个运算数进行计算
  while (operators.size() > 0 && operators.last().priorit > priority)
    CalculateOnce();

  operators.push(PriorityOp(priority, op.front()));
}

void Calculator::TokenLeftBracket() { cur_priority += 100; }

void Calculator::TokenRightBracket() { cur_priority -= 100; }

void Calculator::TokenEnd() {
  while (operators.size() > 0) CalculateOnce();
}

double Calculator::GetFunctionResult(const Function& function,
                                     const QVector<double>& double_paras) {
  Compiler compiler;
  QVector<Token> tokens = compiler.LexicalAnalysis(function.GetExpression());

  for (int i = 0; i < tokens.size(); i++) {
    if (tokens[i].type == kIdentifier) {
      int index = function.GetParameterIndex(tokens[i].value);
      if (index > -1 && index < function.GetParameters().count()) {
        // 使用 double 替代 token 中的 identifier
        tokens[i].type = kNumber;
        tokens[i].value = QString::number(double_paras[index]);
      }
    }
  }
  // 计算新 tokens 时定义一个新的计算器对象
  Calculator sub_calculator;
  return sub_calculator.Calculate(tokens);
}

void Calculator::CalculateOnce() {
  double arg2 = operands.pop();
  double arg1 = operands.pop();
  operands.push(Calculate(arg1, arg2, operators.pop().op));
}
