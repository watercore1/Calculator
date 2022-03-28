#include "function.h"

Function::Function(const QString& name, const QString& description,
                   const QVector<Parameter>& parameters,
                   const QString& expression)
    : name_(name),
      description_(description),
      parameters_(parameters),
      expression_(expression) {}

int Function::GetParameterIndex(const QString& name) const {
  for (int i = 0; i < parameters_.count(); i++) {
    if (parameters_[i].name == name) {
      return i;
    }
  }
  return -1;
}

QVector<Function> Function::GetFunctions(const QString& filepath) {
  QVector<Function> functions;

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
        QJsonObject object_function = array.at(i).toObject();
        functions.append(Function::GetFunction(object_function));
      }
    }
  }
  file.close();
  return functions;
}

Function Function::GetFunction(const QJsonObject& object_funtion) {
  QString name = object_funtion.value("Name").toString();
  QString description = object_funtion.value("Description").toString();
  QString expression = object_funtion.value("Expression").toString();
  QVector<Parameter> parameters;
  QJsonArray array_parameters = object_funtion.value("Parameters").toArray();
  for (int i = 0; i < array_parameters.size(); ++i) {
    QJsonObject object_parameter = array_parameters.at(i).toObject();
    Parameter parameter;
    parameter.description = object_parameter.value("Description").toString();
    parameter.name = object_parameter.value("Name").toString();
    parameters.append(parameter);
  }

  return Function(name, description, parameters, expression);
}

Function Function::FindFunction(const QVector<Function>& functions, const QString& name) {
  foreach (auto function, functions) {
    if (function.GetName() == name) {
      return function;
    }
  }
  throw QString("找不到函数 ") + name;
}

bool Function::IfFunctionExist(const QVector<Function>& functions, const QString& name) {
  foreach (auto function, functions) {
    if (function.GetName() == name) {
      return true;
    }
  }
  return false;
}

void Function::SavaFunctionsFile(const QVector<Function>& functions,
                       const QString& filepath) {
  QFile file(filepath);
  if (!file.open(QIODevice::WriteOnly)) {
    qDebug() << "File open failed";
  } else {
    qDebug() << "File open successfully";
  }
  QJsonDocument document;
  QJsonArray array;
  QJsonObject object_function;

  foreach (auto function, functions) {
    object_function["Name"] = function.GetName();
    object_function["Description"] = function.GetDescription();
    QJsonArray array_para;
    QJsonObject object_para;
    foreach (auto para, function.GetParameters()) {
      object_para["Name"] = para.name;
      object_para["Description"] = para.description;
      array_para.append(object_para);
    }
    object_function["Parameters"] = array_para;
    object_function["Expression"] = function.GetExpression();
    array.append(object_function);
  }
  document.setArray(array);
  file.write(document.toJson(
      QJsonDocument::Indented));  // Indented:表示自动添加/n回车符
  file.close();
}
