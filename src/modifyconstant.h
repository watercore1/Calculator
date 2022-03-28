#ifndef MODIFYCONSTANT_H
#define MODIFYCONSTANT_H

#include <QWidget>

namespace Ui {
class ModifyConstant;
}

class ModifyConstant : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyConstant(QWidget *parent = nullptr);
    ~ModifyConstant();

private:
    Ui::ModifyConstant *ui;
};

#endif // MODIFYCONSTANT_H
