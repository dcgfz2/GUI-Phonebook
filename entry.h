#pragma once

#include<QFrame>
#include<QHBoxLayout>
#include<QLabel>
#include<QString>

class Entry : public QFrame
{
  Q_OBJECT

  public:
    Entry(QString name, QString number);
    QString getName();
    QString getNumber();

  private:
    QLabel* nameLabel;
    QLabel* numberLabel;
};
