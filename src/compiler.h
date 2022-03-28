#ifndef COMPILER_H
#define COMPILER_H

#include <QString>
#include <QVector>

// 词法分析中的四种状态
enum State {
  // 准备读操作数
  kStateWaitOperand,
  // 准备读操作符
  kStateWaitOperator,
  // 当前正在读标识符
  kStateInIdentifier,
  // 当前正在读数
  kStateInNumber,
};

// token的类型
enum TokenType {
  // 数
  kNumber,
  // 标识符
  kIdentifier,
  // 操作符
  kOperator,
  // 左括号
  kLeftBracket,
  // 右括号
  kRightBracket,
  // 结束符
  kEnd,
};

struct Token {
  TokenType type;
  QString value;
  Token(TokenType t, QString s) : type(t), value(s) {}
};

// 将词法分析相关函数集成为一个类
class Compiler {
 public:
  Compiler();
  const QVector<Token>& LexicalAnalysis(const QString& expresstion);
  const QVector<Token>& GetTokens() const { return tokens_; }
  static bool IsIdentifier(QString name);
  static bool IsValue(QString value);

 private:
  State state_;
  // 当前分析的表达式
  QString expression_;
  // 当前字符所在位置
  int pos_;
  // 左括号+1，右括号-1，最后应为0
  int bracket_num_;
  // 一个数前的负号数
  int minus_num_;
  // token 内容
  QString token_string_;
  // 将 tokens 设置为私有变量使得各个函数可以简单访问
  QVector<Token> tokens_;

  void ReadCharAsWaitOperand(QChar ch);
  void ReadCharAsWaitOperator(QChar ch);
  void ReadCharAsInNumber(QChar ch);
  void ReadCharAsInIdentifier(QChar ch);
  void AddToken(TokenType t, QChar ch);
  void AddToken(TokenType t, QString& s);
  void ThrowLexicalError(QChar ch);

  // 将所有运算符整合为一个字符串
  static const QString oprator_;
};

#endif  // COMPILER_H
