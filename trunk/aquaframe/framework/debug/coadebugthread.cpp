#include "coadebugthread.h"
#include "coadebug.h"
#include <iostream>
#include <iomanip>
#include <cassert>
#include <CoaSettings>
#include <CoaIoStream>


#include <QMutex>
#include <QDateTime>

using namespace std;


COAMAKRO_DEFINE_SINGLETONTHREADMETHODS(CoaDebugThread);


CoaDebugThread::CoaDebugThread()
:   CoaBaseThread("dbg_work")
,  m_indent(0)
{
   readMainSettings();

   CoaDebug *d =  CoaDebug::getInstance();

   if (d != 0){

      connect (d,    SIGNAL(signalDebug(const QString, int, int, const QString, int)),
               this, SLOT(     debug   (const QString, int, int, const QString, int))
#ifdef NDEBUG
               , Qt::QueuedConnection
#endif
              );

      connect (d, SIGNAL(signalSetDebugLevel (int)),
               this, SLOT(setDebugLevel(int))
#ifdef NDEBUG
               , Qt::QueuedConnection
#endif
              );

      connect (d, SIGNAL(signalEnableDebugging     (bool)),
               this, SLOT(enableDebugging(bool))
#ifdef NDEBUG
               , Qt::QueuedConnection
#endif
              );

      connect (d, SIGNAL(signalShowTimeInOutput    (bool)),
               this, SLOT(showTimeInOutput(bool))
#ifdef NDEBUG
               , Qt::QueuedConnection
#endif
              );

      connect (d, SIGNAL(signalSetDebugLevelForFile(const QString, int)),
               this, SLOT(setDebugLevelForFile(const QString, int))
#ifdef NDEBUG
               , Qt::QueuedConnection
#endif
              );


      connect (d, SIGNAL(signalRemDebugLevelForFile(const QString)),
               this, SLOT(remDebugLevelForFile(const QString))
#ifdef NDEBUG
               , Qt::QueuedConnection
#endif
              );
   }

}


CoaDebugThread::~CoaDebugThread()
{
   INSTANCE=0;
   writeMainSettings();
}







void CoaDebugThread::setDebugLevel(int level)
{
   QWriteLocker locker(&m_lock);
   CoaDebug::DebugLevel debugLevel = CoaDebug::mapIntToLevel(level);

   //some checks
   assert(debugLevel != CoaDebug::DEFAULT);
   if (debugLevel == CoaDebug::DEFAULT)
      return;

   m_debugLevel = debugLevel;

   //Output
   switch(debugLevel){
        case CoaDebug::DEFAULT: cout << "LogLevel is set to DEFAULT"<< endl;break;
        case CoaDebug::OFF: cout << "LogLevel is set to OFF"<< endl;break;
        case CoaDebug::ERR: cout << "LogLevel is set to ERR"<< endl;break;
        case CoaDebug::WRN: cout << "LogLevel is set to WRN"<< endl;break;
        case CoaDebug::INF: cout << "LogLevel is set to INF"<< endl;break;
        case CoaDebug::DBG: cout << "LogLevel is set to DBG"<< endl;break;
   }


   writeMainSettings();

}



CoaDebug::DebugLevel CoaDebugThread::getDebugLevel(void) const
{
   return m_debugLevel;
}


void CoaDebugThread::debug(const QString file, int line, int level, const QString message, int indent)
{
   //return if debugging is disabled
   if (! isDebuggingEnabled()) return;

   QWriteLocker locker(&m_lock);

   //some checks
   assert(m_debugLevel != CoaDebug::DEFAULT);
   if (m_debugLevel == CoaDebug::DEFAULT) m_debugLevel = CoaDebug::ERR;
   if (level == CoaDebug::DEFAULT) level = m_debugLevel;


   //return if debug level doesn't match this file
   CoaDebug::DebugLevel fileLevel = debugLevelForFile(file);
   if (fileLevel == CoaDebug::DEFAULT) {
      if (level > m_debugLevel) return;
   } else {
      if (level > fileLevel) return;
   }


   //Show the Time
   if (showTimeInOutput() == true) {
      QDateTime time = QDateTime::currentDateTime ();
      cout.flags(ios::left);
      cout <<  time.toString(Qt::ISODate) << ' ';

   }

   //show the debug level
   switch (level)
   {
      case CoaDebug::ERR:    cout << "ERR ";         break;
      case CoaDebug::WRN:    cout << "WRN ";         break;
      case CoaDebug::INF:    cout << "INF ";         break;
      case CoaDebug::DBG:    cout << "DBG ";         break;
      case CoaDebug::OFF:    cout << "OFF ";         break;
   }


   //print a formated file and line number and indent spaces
   cout  << setw(35) << file << setw(0) << " (" << setw(4) << setfill(' ') <<line << setw(0) << ')';


   //decrease indent level;
   if (indent < 0) m_indent = m_indent + indent;//yes a plus, even if the indent is negativ
   if (m_indent < 0) m_indent = 0;


   //print indent spaces
   cout << QString ("%1").arg(' ', m_indent, QChar(' '));

   //print message it self
   if (message != 0) {
      cout << message << endl;
   } else {
      cout << "<NULL>" << endl;
   }


   //increase indent level;
   if (indent > 0) m_indent = m_indent + indent;

   //bye,bye
   return;
}


void CoaDebugThread::enableDebugging(bool flag)
{
   QWriteLocker locker(&m_lock);

   if (m_isEnabled != flag) {
      m_isEnabled = flag;
      writeMainSettings();
   }

}



void CoaDebugThread::showTimeInOutput(bool flag)
{
   QWriteLocker locker(&m_lock);

   if (m_showTimeInOutput != flag) {
      m_showTimeInOutput = flag;
      writeMainSettings();
   }

}


bool CoaDebugThread::showTimeInOutput(void) const
{
   return m_showTimeInOutput;
}


bool CoaDebugThread::isDebuggingEnabled (void) const
{
   return m_isEnabled;
}


void CoaDebugThread::readMainSettings()
{
   //QWriteLocker locker(&_lock); No Locker here! Lock will be done in sub methods!
   CoaSettings settings;
   settings.beginGroup("Debug");

   //enable debugging?
   m_isEnabled = settings.value("isEnabled", false).toBool();
   m_showTimeInOutput = settings.value("showTimeInOutput", false).toBool();


   //Get the Debug Level
   const QString strLevel (settings.value("defaulLevel", "WRN").toString());
   CoaDebug::DebugLevel level = CoaDebug::mapStringToLevel(strLevel);
   if (level == CoaDebug::DEFAULT) {
      m_debugLevel = CoaDebug::ERR;
   }
   else {
      m_debugLevel = level;
   }


   settings.endGroup();
}




void CoaDebugThread::writeMainSettings()
{
   //QWriteLocker locker(&_lock); No Locker here, will be done in submethods!
   //test the application for correnct init
   CoaSettings settings;

   settings.beginGroup("Debug");

   settings.setValue("isEnabled", m_isEnabled);
   settings.setValue("showTimeInOutput", m_showTimeInOutput);
   settings.setValue("defaulLevel", CoaDebug::mapLevelToString(m_debugLevel));


   settings.endGroup();

}


const QString SETTING_DEBUGFILE = "DebugLevels4Files";

CoaDebug::DebugLevel CoaDebugThread::readFileSettings(const QString& file)
{
   CoaSettings settings;
   settings.beginGroup(SETTING_DEBUGFILE);
   const QString strLevel (settings.value(file, "DEFAULT").toString());
   CoaDebug::DebugLevel level = CoaDebug::mapStringToLevel(strLevel);
   m_mapFiles[file]=level;
   settings.endGroup();

   return level;
}


void CoaDebugThread::writeFileSettings(const QString& file, const CoaDebug::DebugLevel level)
{
   if (level == CoaDebug::DEFAULT) {
      removeFileSettings(file);
   } else {
      CoaSettings settings;
      settings.beginGroup(SETTING_DEBUGFILE);
      QString strLevel = CoaDebug::mapLevelToString(level);
      settings.setValue(file, strLevel);
      settings.endGroup();
   }
}

void CoaDebugThread::removeFileSettings(const QString& file)
{
   CoaSettings settings;
   settings.beginGroup(SETTING_DEBUGFILE);
   settings.remove(file);
   settings.endGroup();
}


void CoaDebugThread::setDebugLevelForFile(const QString filename, int level)
{
   QWriteLocker locker(&m_lock);

   CoaDebug::DebugLevel dbg_level = CoaDebug::mapIntToLevel(level);

   //file allready there ...
   MapLevelForFiles::const_iterator i = m_mapFiles.find(filename);
   if (i == m_mapFiles.end() || i.value() != dbg_level) {
      //either no file in map or different level
      m_mapFiles[filename]=dbg_level;
      writeFileSettings(filename, dbg_level);
   }

}


CoaDebug::DebugLevel CoaDebugThread::debugLevelForFile(const QString filename)
{
   MapLevelForFiles::const_iterator i = m_mapFiles.find(filename);
   if (i == m_mapFiles.end()) {
      CoaDebug::DebugLevel level = readFileSettings(filename);
      emit gotNewFileForDebugging(filename, level);
      return level;
   } else {
      return i.value();
   }

}

void CoaDebugThread::remDebugLevelForFile(const QString filename)
{

   QWriteLocker locker(&m_lock);

   if (m_mapFiles.remove(filename) >0 ) {
      removeFileSettings(filename);
   }

}



QMap <QString, CoaDebug::DebugLevel> CoaDebugThread::getKnownFiles()
{
   return m_mapFiles;
}

