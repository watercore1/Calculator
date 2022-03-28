#ifndef CONSTANT_H
#define CONSTANT_H

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QVector>

// 将常量有关的函数集成为一个类
class Constant {
 public:
  Constant() = delete;
  Constant(const QString& name, const QString& description,
           const QString& value);
  const QString& GetName() const { return name_; }
  const QString& GetDescription() const { return description_; }
  const QString& GetValue() const { return value_; }
  // 从 JSON 文件转化为 Constants
  static QVector<Constant> GetConstants(const QString& filepath);
  // 从一个 JSON 对象转化为 Constant
  static Constant GetConstant(const QJsonObject& object_constant);
  // 根据常量名字得到常量
  static Constant FindConstant(const QVector<Constant>& constants,
                               const QString& name);
  // 根据常量名字查找常量是否存在
  static bool IfConstantExist(const QVector<Constant>& constants,
                              const QString& name);
  // 从 Constants 转化为 JSON 文件
  static void SaveConstantsFile(const QVector<Constant>& constants,
                                const QString& filepath);

 private:
  QString name_;
  QString description_;
  QString value_;
};

#endif  // CONSTANT_H
