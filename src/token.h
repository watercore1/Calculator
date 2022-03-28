#ifndef TOKEN_H
#define TOKEN_H

#include <QString>



class Token {
 public:
  Token() = delete;
  Token(TokenType type, QString value);
  TokenType GetType() { return type_; }
  QString GetValue() { return value_; }

 private:
  TokenType type_;
  QString value_;
};

#endif  // TOKEN_H
