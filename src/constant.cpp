#include "constant.h"

Constant::Constant(const QString& name, const QString& description,
                   const QString& value)
    : name_(name), description_(description), value_(value) {}

QVector<Constant> Constant::GetConstants(const QString& filepath) {
  QVector<Constant> constants;

  QFile file(filepath);
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "File open failed";
  } else {
    qDebug() << "File open successfully";
  }

  QJsonParseError jsonError;
  QJsonDocument doucment =
      QJsonDocument::fromJson(file.readAll(), &jsonError);  // 转化为 JSON 文档
  if (!doucment.isNull() &&
      (jsonError.error == QJsonParseError::NoError)) {  // 解析未发生错误
    if (doucment.isArray()) {                           // JSON 文档为数组
      QJsonArray array = doucment.array();              // 转化为数组
      for (int i = 0; i < array.size(); ++i) {          // 遍历数组
        // 一个 value 对应一个函数，类型为 object
        QJsonObject object_constant = array.at(i).toObject();
        constants.append(Constant::GetConstant(object_constant));
      }
    }
  }
  file.close();
  return constants;
}

Constant Constant::GetConstant(const QJsonObject& object_constant) {
  QString name = object_constant.value("Name").toString();
  QString description = object_constant.value("Description").toString();
  QString value = object_constant.value("Value").toString();

  return Constant(name, description, value);
}

Constant Constant::FindConstant(const QVector<Constant>& constants, const QString& name) {
  foreach (auto constant, constants) {
    if (constant.GetName() == name) {
      return constant;
    }
  }
  throw QString("找不到常量 ") + name;
}

bool Constant::IfConstantExist(const QVector<Constant>& constants, const QString& name) {
  foreach (auto constant, constants) {
    if (constant.GetName() == name) {
      return true;
    }
  }
  return false;
}

void Constant::SaveConstantsFile(const QVector<Constant>& constants,
                       const QString& filepath) {
  QFile file(filepath);
  if (!file.open(QIODevice::WriteOnly)) {
    qDebug() << "File open failed";
  } else {
    qDebug() << "File open successfully";
  }

  QJsonDocument document;
  QJsonArray array;
  QJsonObject object_constant;

  foreach (auto constant, constants) {
    object_constant["Name"] = constant.GetName();
    object_constant["Description"] = constant.GetDescription();
    object_constant["Value"] = constant.GetValue();
    array.append(object_constant);
  }
  document.setArray(array);
  file.write(document.toJson(
      QJsonDocument::Indented));  // Indented:表示自动添加/n回车符
  file.close();
}
