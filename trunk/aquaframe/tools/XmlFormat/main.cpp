#include <QApplication>

//#include "mainwindow.h"

#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <iostream>
#include <string>
using namespace std;

/********************************************
********************************************/
std::ostream& operator<< (std::ostream& out, const QString& string)
{

   out << string.toUtf8().data();
   return out;
}



/********************************************
********************************************/
int dealWithStdin(QDomDocument& domDocument)
{
  
    QFile file;
    if (!file.open(stdin,  QIODevice::ReadOnly)) {
       cerr << "Cannot read from stdin: " << file.errorString() << endl;
       return -1;
    }
    
   QString errorStr;
   int errorLine;
   int errorColumn;
   
   
    if (!domDocument.setContent(&file, &errorStr, &errorLine, &errorColumn)) {
         cerr << "Error while reading xml line " << errorLine << " col " << errorColumn << "\n"
              << "Error String:\n"
              << errorStr
              << endl;
        return -2;
    }
    
    
    return 0;

}


/********************************************
********************************************/
int dealWithFiles(QDomDocument& domDocument)
{
    //get the file   
    QString fileName = "";   
    QFile file ( fileName );
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
       cerr << "Cannot open file " << fileName << ": " << file.errorString() << endl;
       return -1;
    }
   
   
    QString errorStr;
    int errorLine;
    int errorColumn;
    
    if (!domDocument.setContent(&file, &errorStr, &errorLine, &errorColumn)) {
         cerr << "Error while reading xml file in line " << errorLine << " col " << errorColumn << "\n"
              << "Error String:\n"
              << errorStr
              << endl;
        return -2;
    }
    return 0;

}


/********************************************
********************************************/
int main(int argc, char *argv[])
{
   
   QDomDocument domDocument;
   int result = -1;
   
   if (argc == 1) {
      result = dealWithStdin(domDocument);
   } else {
      result = dealWithFiles(domDocument);
   }
   

   if (result == 0) {
      cout << domDocument.toString ( 2 );
   }

   return result;
}
