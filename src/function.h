#ifndef FUNCTION_H
#define FUNCTION_H

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QVector>

struct Parameter {
  QString name;
  QString description;
};

// 将函数有关的函数集成为一个类
class Function {
 public:
  Function() = delete;
  Function(const QString& name, const QString& description,
           const QVector<Parameter>& parameters, const QString& expression);

  const QString& GetName() const { return name_; }
  const QString& GetDescription() const { return description_; }
  const QVector<Parameter>& GetParameters() const { return parameters_; }
  const QString& GetExpression() const { return expression_; }
  int GetParameterIndex(const QString& name) const;
  // 从 JSON 文件转化为 Functions
  static QVector<Function> GetFunctions(const QString& filepath);
  // 从一个 JSON 对象转化为 Function
  static Function GetFunction(const QJsonObject& object_function);
  // 根据函数名字得到函数
  static Function FindFunction(const QVector<Function>& functions,
                               const QString& name);
  // 根据函数名字查找函数
  static bool IfFunctionExist(const QVector<Function>& functions,
                              const QString& name);
  // 将 functions 保存为 JSON 文件
  static void SavaFunctionsFile(const QVector<Function>& functions,
                                const QString& filepath);

 private:
  QString name_;
  QString description_;
  QVector<Parameter> parameters_;
  QString expression_;
};

#endif  // FUNCTION_H
