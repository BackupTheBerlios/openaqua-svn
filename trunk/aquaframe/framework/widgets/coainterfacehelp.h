#ifndef __CoaInterfaceHelp_h__
#define __CoaInterfaceHelp_h__

class CoaInterfaceHelp: public QObject
{
Q_OBJECT
Q_PROPERTY(int helpId READ helpId WRITE setHelpId STORED false)
public:
   CoaInterfaceHelp(QObject *const parent = 0);
   virtual ~CoaInterfaceHelp();

   virtual const int helpId() const  =0;
   virtual void setHelpId(const int helpId = 0) =0;

private:
   int   m_helpid;
};

#endif //__CoaInterfaceHelp_h__

