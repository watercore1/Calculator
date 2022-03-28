#ifndef MODIFYFUNCTION_H
#define MODIFYFUNCTION_H

#include <QWidget>

namespace Ui {
class ModifyFunction;
}

class ModifyFunction : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyFunction(QWidget *parent = nullptr);
    ~ModifyFunction();

private:
    Ui::ModifyFunction *ui;
};

#endif // MODIFYFUNCTION_H
