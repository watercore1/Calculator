#include "compiler.h"

const QString Compiler::oprator_("+-*/^%,");

Compiler::Compiler() {}

const QVector<Token>& Compiler::LexicalAnalysis(const QString& expresstion) {
  // 初始化
  pos_ = 0;
  bracket_num_ = 0;
  minus_num_ = 0;
  state_ = kStateWaitOperand;
  token_string_.clear();
  tokens_.clear();

  expression_ = expresstion + '#';

  // 逐字符分析
  foreach (QChar ch, expression_) {
    pos_++;
    switch (state_) {
      case kStateWaitOperand:
        ReadCharAsWaitOperand(ch);
        break;
      case kStateWaitOperator:
        ReadCharAsWaitOperator(ch);
        break;
      case kStateInIdentifier:
        ReadCharAsInIdentifier(ch);
        break;
      case kStateInNumber:
        ReadCharAsInNumber(ch);
        break;
    }
  }

  if (bracket_num_ != 0) {
    throw QString("括号不匹配");
  }

  return tokens_;
}

void Compiler::ReadCharAsWaitOperand(QChar ch) {
  if (ch == ' ' || ch == '+') {
    return;
  }
  if (ch == '-') {
    // 记录负号数
    minus_num_++;
    return;
  }
  if (ch.isDigit()) {
    // 保证数前只有一个负号
    if (minus_num_ % 2 == 1) token_string_ += '-';
    minus_num_ = 0;
    token_string_ += ch;
    state_ = kStateInNumber;
    return;
  }
  if (ch.isLetter()) {
    // 标识符前可能会有一个负号，需要在计算时特殊处理
    if (minus_num_ % 2 == 1) token_string_ += '-';
    minus_num_ = 0;
    token_string_ += ch;
    state_ = kStateInIdentifier;
    return;
  }
  if (ch == '(') {
    bracket_num_++;
    AddToken(kLeftBracket, ch);
    return;
  }
  if (ch == '#') {
    AddToken(kEnd, ch);
    return;
  }
  ThrowLexicalError(ch);
}

void Compiler::ReadCharAsWaitOperator(QChar ch) {
  if (ch == ' ') {
    return;
  }
  if (Compiler::oprator_.contains(ch)) {
    AddToken(kOperator, ch);
    state_ = kStateWaitOperand;
    return;
  }
  if (ch == ')') {
    bracket_num_--;
    AddToken(kRightBracket, ch);
    return;
  }
  if (ch == '#') {
    AddToken(kEnd, ch);
    return;
  }
  ThrowLexicalError(ch);
}

void Compiler::ReadCharAsInNumber(QChar ch) {
  if (ch == ' ') {
    AddToken(kNumber, token_string_);
    state_ = kStateWaitOperator;
    return;
  }
  if (ch.isDigit()) {
    token_string_ += ch;
    return;
  }
  if (ch == '.') {
    token_string_ += ch;
    return;
  }
  if (ch == 'e' || ch == 'E') {
    token_string_ += ch;
    state_ = kStateWaitOperand;
    return;
  }
  if (ch == ')') {
    bracket_num_--;
    AddToken(kNumber, token_string_);
    AddToken(kRightBracket, ch);
    state_ = kStateWaitOperator;
    return;
  }
  if (Compiler::oprator_.contains(ch)) {
    AddToken(kNumber, token_string_);
    AddToken(kOperator, ch);
    state_ = kStateWaitOperand;
    return;
  }
  if (ch == '#') {
    AddToken(kNumber, token_string_);
    AddToken(kEnd, ch);
    return;
  }
  ThrowLexicalError(ch);
}

void Compiler::ReadCharAsInIdentifier(QChar ch) {
  if (ch == ' ') {
    AddToken(kIdentifier, token_string_);
    state_ = kStateWaitOperator;
    return;
  }
  if (ch.isLetter() || ch.isDigit()) {
    token_string_ += ch;
    return;
  }
  if (ch == '(') {
    bracket_num_++;
    AddToken(kIdentifier, token_string_);
    AddToken(kLeftBracket, ch);
    state_ = kStateWaitOperand;
    return;
  }
  if (ch == ')') {
    bracket_num_--;
    AddToken(kIdentifier, token_string_);
    AddToken(kRightBracket, ch);
    state_ = kStateWaitOperator;
    return;
  }
  if (Compiler::oprator_.contains(ch)) {
    AddToken(kIdentifier, token_string_);
    AddToken(kOperator, ch);
    state_ = kStateWaitOperand;
    return;
  }
  if (ch == '#') {
    AddToken(kIdentifier, token_string_);
    AddToken(kEnd, ch);
    return;
  }
  ThrowLexicalError(ch);
}

void Compiler::AddToken(TokenType t, QChar ch) { tokens_.append(Token(t, ch)); }

void Compiler::AddToken(TokenType t, QString& s) {
  tokens_.append(Token(t, s));
  s.clear();
}

void Compiler::ThrowLexicalError(QChar ch) {
  throw QString("表达式 %1 中位于 %2 处的字符 %3 出现语法错误。")
      .arg(expression_)
      .arg(pos_)
      .arg(ch);
}

bool Compiler::IsIdentifier(QString name) {
  if (!name.front().isLetter()) {
    return false;
  }
  foreach (QChar ch, name) {
    if (not ch.isLetterOrNumber()) {
      return false;
    }
  }
  return true;
}

bool Compiler::IsValue(QString value) {
  bool ok;
  value.toDouble(&ok);
  return ok;
}
