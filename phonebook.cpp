#include"phonebook.h"

PhoneBook::PhoneBook()
{
  // Set Up Layout
  newnum = new newNumber;
  
  connect(newnum, SIGNAL(numberEntered(QString, QString)),
  	this, SLOT(enterNumber(QString, QString)));

  layout = new QVBoxLayout;
  layout->addWidget(newnum);

  QWidget* main = new QWidget;
  main->setLayout(layout);
  setCentralWidget(main);

  
  openAction = new QAction("&Open", this);
  connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

  saveAction = new QAction("&Save", this);
  connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

  quitAction = new QAction("&Quit",this);
  connect(quitAction, SIGNAL(triggered()), this, SLOT(quit()));
  
  menuBar()->setNativeMenuBar(false);
  
  fileMenu = menuBar()->addMenu("&File");
  fileMenu->addAction(openAction);    
  fileMenu->addAction(saveAction);  
  fileMenu->addAction(quitAction);  

  modified = false;
}

void PhoneBook::save()
{
  QString fileName = QFileDialog::getSaveFileName(
      this, // Parent
      "Save File", // Dialog Title
      "", // Directory
      "All Files (*)" // File Type Filters
    );

  if(fileName != "")
  {
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
    {
      QMessageBox::critical(
          this, // Parent
          "Error", // Dialog Title
          "Could not write to file" // Dialog Text
        );
    }
    else
    {
      QTextStream out(&file);
      
      out << this->serialize();
      modified = false;
      file.close();
    }
  }
}

void PhoneBook::open()
{
  QString fileName = QFileDialog::getOpenFileName(
      this, // Parent
      "Open File", // Dialog Title
      "", // Directory
      "All Files (*)" // File Type Filters
    );

  if(fileName != "")
  {
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
      QMessageBox::critical(
          this, // Parent
          "Error", // Dialog Title
          "Could not open file" // Dialog Text
        );
    }
    else
    {
      QTextStream in(&file);
      
      QString temp = "";
      QString full = "";
      while(!in.atEnd())
      {
        temp = in.readLine();
        full += temp;
        full += ";";
      } 
      this->deserialize(full);
        
      file.close();
    }
  }
}

void PhoneBook::quit()
{
  if(modified == true) 
  { 
    QMessageBox messageBox;
    messageBox.setWindowTitle("Quit?");
    messageBox.setText("You have unsaved data. Are you sure you want to quit?");
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messageBox.setDefaultButton(QMessageBox::No); 
    if(messageBox.exec() == QMessageBox::Yes)
    {
      qApp->quit();
    }
  }
  else
  {
    qApp->quit();
  }
}

QString PhoneBook::serialize()
{
  QString data = "";
  for(unsigned int i = 0; i < entries.size(); i++)
  {
    Entry* e = entries[i];
    data.append(e->getName() + ";" + e->getNumber() + "\n");
  }

  return data;
}

void PhoneBook::deserialize(QString data)
{
  // Clear all the phone numbers
  for(unsigned int i = 0; i < entries.size(); i++)
  {
    layout->removeWidget(entries[i]);
    delete entries[i];
  }
  entries.clear();

  QStringList split = data.split("\n",QString::SkipEmptyParts);
  for(int i = 0; i < split.size(); i++)
  {
    QStringList vals = split[i].split(";");
    for(int k =0; k <= vals.size();k+=2)
    {
      QString name = vals[k];
      QString number = vals[k+1];
    
      Entry* temp = new Entry(name,number);
      entries.push_back(temp);
      layout->addWidget(entries.back());
    }
  }
}
void PhoneBook :: enterNumber(QString name, QString num)
{
  Entry* a= new Entry(name, num);
  entries.push_back(a);
  layout->addWidget(entries.back());
  modified = true;
}
