#ifndef __CoaDebug_h__
#define __CoaDebug_h__


#include <CoaBaseThread>
#include <CoaMakros>
#include <cassert>

#include <QRect>
#include <QSize>
#include <QPoint>
#include <QRegion>
#include <QVariant>
#include <QModelIndex>
#include <QDomNode>
#include <QDomElement>


#define BEGIN         CoaDebugMethod _BEGIN(__FILE__, __LINE__, __PRETTY_FUNCTION__);
#define CONSTRUCT     CoaDebugMethod _BEGIN(__FILE__, __LINE__, __PRETTY_FUNCTION__);
#define DESTRUCT      CoaDebugMethod _BEGIN(__FILE__, __LINE__, __PRETTY_FUNCTION__);
#define DBG(str)      CoaDebug::getInstance()->debug(__FILE__, __LINE__, CoaDebug::DBG, str);
#define INF(str)      CoaDebug::getInstance()->debug(__FILE__, __LINE__, CoaDebug::INF, str);
#define WRN(str)      CoaDebug::getInstance()->debug(__FILE__, __LINE__, CoaDebug::WRN, str);
#define ERR(str)      CoaDebug::getInstance()->debug(__FILE__, __LINE__, CoaDebug::ERR, str);
#define RETURN(var)   return _BEGIN.Result(__LINE__, var)





/**
@brief singleton as a global reachable object to set and get the currently used debug level

@warning the instance needs a already working CoaApplication object!

@todo support for output to file

The class stores settings after each modification of settings (like DebugLevel).
For that the class use a CoaSettings object. The settings object will be initialized
with the application and organization name from the CoaApplication object. So the CoaDebug
class needs a working (instantiated CoaApplication object).

*/

class CoaDebug: public CoaBaseThread {
Q_OBJECT
public:

   enum DebugLevel{
      DEFAULT = -1,
      OFF = 0,
      ERR = 1,
      WRN = 2,
      INF = 3,
      DBG = 4
   };


public slots:
   void setDebugLevel(const QString& level);
   void setDebugLevel(DebugLevel level);
   void enableDebugging(bool);
   void showTimeInOutput(bool);
   void setDebugLevelForFile(const QString& filename, DebugLevel level);
   void setDebugLevelForFile(const QString& filename, const QString&);
   void remDebugLevelForFile(const QString& filename);
   void debug   (          const QString& file,
                           int  line,
                           int level,
                           const QString& message,
                           int indent = 0
                       );

   static const DebugLevel mapStringToLevel(const QString&);
   static const QString    mapLevelToString(const DebugLevel);
   static const DebugLevel mapIntToLevel   (const int iLevel);


signals:
   void signalDebug               (const QString, int, int, const QString, int);
   void signalSetDebugLevel       (int );
   void signalEnableDebugging     (bool);
   void signalShowThreadsInOutput (bool);
   void signalShowTimeInOutput    (bool);
   void signalSetDebugLevelForFile(const QString , int );
   void signalRemDebugLevelForFile(const QString );


private:
   COAMAKRO_DEKLARE_SINGLETONMETHODS ( CoaDebug );
   COAMAKRO_NO_COPYCONSTRUCTOR(CoaDebug);
   COAMAKRO_NO_COMPARE(CoaDebug);

};





class CoaAction;
/**
@brief Used to log the begin and the end of a method
*/
class CoaDebugMethod {
public:
   CoaDebugMethod(char const *const file, int line, const QString& message);
   virtual ~CoaDebugMethod();

   bool        Result (  const int line,  const bool boolean);
   QString     Result (  const int line,  const QString& string);
   int         Result (  const int line,  const int integer);
   unsigned int Result (  const int line,  const unsigned int integer);
   QObject*    Result (  const int line,  QObject *);
   QWidget*    Result (  const int line,  QWidget *);
   CoaAction*  Result (  const int line,  CoaAction *);
   QRect       Result (  const int line,  const QRect& );
   QSize       Result (  const int line,  const QSize& );
   QPoint      Result (  const int line,  const QPoint& );
   QVariant    Result (  const int line,  const QVariant& );
   QModelIndex Result (  const int line,  const QModelIndex& );
   QRegion     Result (  const int line,  const QRegion& );



private:
   const char*const   m_file;
   int                m_line;
   QString            m_result;
   CoaDebug          *m_debugger;

   //not implemented
   CoaDebugMethod();
   CoaDebugMethod(const CoaDebugMethod&);
   void operator=(CoaDebugMethod const&);
};





#endif //__CoaDebug_h__

