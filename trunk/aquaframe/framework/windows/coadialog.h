#ifndef __CoaDialog_h__
#define __CoaDialog_h__

#include <QDialog>
#include <QString>

class CoaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CoaDialog ( const QString& objectName, QWidget * parent = 0, Qt::WFlags flags = 0 );
    virtual ~CoaDialog();

   virtual void readSettings();
   virtual void writeSettings();



private slots:

private:


};

#endif //__CoaDialog_h__
