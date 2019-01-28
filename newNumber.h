#pragma once
#include<QFrame>
#include<QHBoxLayout>
#include<QLineEdit>
#include<QPushButton>

class newNumber : public QFrame
{
  Q_OBJECT

  public:
    newNumber();
  
  signals:
    void numberEntered(QString name, QString number);

  private slots:
    void addPress();

  private:
    QLineEdit* nameEdit;
    QLineEdit* numberEdit;
    QPushButton* addButton;
};
