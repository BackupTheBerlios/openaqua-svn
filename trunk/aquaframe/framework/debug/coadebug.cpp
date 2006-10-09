#include "coadebug.h"
#include <cassert>
#include <iostream>
#include <CoaIoStream>
#include <CoaAction>


#include <QMutex>

using namespace std;


COAMAKRO_DEFINE_SINGLETONTHREADMETHODS(CoaDebug);

CoaDebug::CoaDebug()
: CoaBaseThread("dbg_prox")
{
}



CoaDebug::~CoaDebug()
{
   INSTANCE=0;
}





//////////////////////////////////////////////////////////////
CoaDebugMethod::CoaDebugMethod( char const *const file,
                                int line,
                                const QString& message)
: m_file(file)
, m_line(0) //will be set in Result methods
, m_result("")
{

   //QString msg = message + " {";
   m_debugger = CoaDebug::getInstance();

   if (m_debugger != 0) {
      m_debugger->debug(file, line, CoaDebug::DBG, message + "{ ", 3);
   }
}


CoaDebugMethod::~CoaDebugMethod()
{
   //Hint: Line will be printed as 0. Cause the line number of the destructor call is not known
   if (m_debugger == 0) return;

   if (m_result.isEmpty()) {
      m_debugger->debug(m_file, m_line, CoaDebug::DBG,  "} ", -3);
   } else {
      m_debugger->debug(m_file, m_line, CoaDebug::DBG,  "} = " + m_result, -3);
   }
}


QString CoaDebugMethod::Result ( const int  line, const QString& string)
{
   m_line = line;
   m_result = string;
   return string;
}



int CoaDebugMethod::Result ( const int  line, const int integer)
{
   m_line = line;
   m_result = QString("%1").arg(integer);
   return integer;
}

unsigned int CoaDebugMethod::Result (  const int line,  const unsigned int integer)
{
   m_line = line;
   m_result = QString("%1").arg(integer);
   return integer;
}

QObject* CoaDebugMethod::Result ( const int  line, QObject * obj)
{
   m_line = line;
   if (obj != 0)
      m_result = obj->objectName();
   else
      m_result ="<NULL>";
   return obj;
}

CoaAction* CoaDebugMethod::Result (  const int line,  CoaAction *obj)
{
   m_line = line;
   if (obj != 0)
      m_result = obj->objectName();
   else
      m_result ="<NULL>";
   return obj;
}




QWidget* CoaDebugMethod::Result (  const int line,  QWidget *obj)
{
   m_line = line;
   if (obj != 0)
      m_result = obj->objectName();
   else
      m_result ="<NULL>";
   return obj;
}





bool CoaDebugMethod::Result ( const int  line, const bool boolean)
{
   m_line = line;

   if (boolean == true) {
      m_result = "true";
   } else {
      m_result = "false";
   }
   return boolean;
}


QRect       CoaDebugMethod::Result (  const int line,  const QRect& r)
{
   m_line = line;
   m_result = QString("%1").arg(QVariant(r).toString());
   return r;
}


QSize       CoaDebugMethod::Result (  const int line,  const QSize& r)
{
   m_line = line;
   m_result = QString("%1").arg(QVariant(r).toString());
   return r;
}


QPoint      CoaDebugMethod::Result (  const int line,  const QPoint& r)
{
   m_line = line;
   m_result = QString("%1").arg(QVariant(r).toString());
   return r;
}

QVariant    CoaDebugMethod::Result (  const int line,  const QVariant& r)
{
   m_line = line;
   m_result = QString("%1").arg(r.toString());
   return r;
}

QModelIndex CoaDebugMethod::Result (  const int line,  const QModelIndex& r)
{
   m_line = line;
   if (! r.isValid() ) {
      m_result = "index.valid=false";
   } else {
      m_result = CoaString("index.valid=true row=%1 col=%2").arg(r.row()).arg(r.column());
   }
   return r;
}



QRegion CoaDebugMethod::Result (  const int line,  const QRegion& r)
{
   m_line = line;
   m_result = "QRegion(xxxx)";
   return r;
}



void CoaDebug::debug( const QString& file, int  line, int level, const QString& message,  int indent) {
#if 0
   //print the name of the executing thread
   QThread * currentThread = QThread::currentThread ();
   if (currentThread == 0) {
      cout << "currend thread = GUI" <<endl;
   }else {
      QString o(currentThread->objectName());
      if (!o.isEmpty())
         cout << "currend thread = " << o <<endl;
   }
#endif
   emit signalDebug(file, line, level, message, indent);
}


void CoaDebug::setDebugLevel(DebugLevel level)
{
   emit signalSetDebugLevel       (level);
}


void CoaDebug::enableDebugging(bool enabled)
{
   emit signalEnableDebugging     (enabled);
}


void CoaDebug::showTimeInOutput(bool enabled)
{
   emit signalShowTimeInOutput    (enabled);
}


void CoaDebug::setDebugLevelForFile(const QString& filename, DebugLevel level)
{
   emit signalSetDebugLevelForFile(filename, level);
}


void CoaDebug::remDebugLevelForFile(const QString& filename)
{
   emit signalRemDebugLevelForFile(filename);
}

void CoaDebug::setDebugLevel(const QString& level)
{
   setDebugLevel(mapStringToLevel(level));
}

void CoaDebug::setDebugLevelForFile(const QString& filename, const QString& level)
{
   setDebugLevelForFile(filename, mapStringToLevel(level));
}




const CoaDebug::DebugLevel  CoaDebug::mapStringToLevel(const QString& s)
{
   CoaDebug::DebugLevel level;

   if (s.startsWith("O", Qt::CaseInsensitive)){
      level = CoaDebug::OFF;
   } else if (s.startsWith("E", Qt::CaseInsensitive)){
      level = CoaDebug::ERR;
   } else if (s.startsWith("W", Qt::CaseInsensitive)){
      level = CoaDebug::WRN;
   } else if (s.startsWith("I", Qt::CaseInsensitive)){
      level = CoaDebug::INF;
   } else if (s.startsWith("DB", Qt::CaseInsensitive)){
      level = CoaDebug::DBG;
   } else if (s.startsWith("DEB", Qt::CaseInsensitive)){
      level = CoaDebug::DBG;
   } else {
      level = CoaDebug::DEFAULT;
   }

   return level;
}



const QString CoaDebug::mapLevelToString(const CoaDebug::DebugLevel level)
{
   switch(level){
        case CoaDebug::DEFAULT: return QString("DEFAULT");
        case CoaDebug::OFF:     return QString("OFF");
        case CoaDebug::ERR:     return QString("ERR");
        case CoaDebug::WRN:     return QString("WRN");
        case CoaDebug::INF:     return QString("INF");
        case CoaDebug::DBG:     return QString("DBG");
     //no default, for enabled compiler warnings!
   }
   //should never be reached
   return ("DEFAULT");
}

const CoaDebug::DebugLevel CoaDebug::mapIntToLevel(const int iLevel)
{
   switch(iLevel)
   {
      case 0: return CoaDebug::OFF;
      case 1: return CoaDebug::ERR;
      case 2: return CoaDebug::WRN;
      case 3: return CoaDebug::INF;
      case 4: return CoaDebug::DBG;
      default: return CoaDebug::DEFAULT;
   }
   return CoaDebug::DEFAULT;
}




