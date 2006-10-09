#ifndef __CoaDebugThread_h__
#define __CoaDebugThread_h__


#include <CoaBaseThread>
#include <CoaDebug>
#include <CoaMakros>
#include <CoaSettings>

#include <QMap>
#include <QWriteLocker>
#include <cassert>





/**
@brief singleton as a global reachable object to set and get the currently used debug level

@warning the instance needs a already working CoaApplication object!

@todo support for output to file

The class stores settings after each modification of settings (like DebugLevel).
For that the class use a CoaSettings object. The settings object will be initialized
with the application and organization name from the CoaApplication object. So the CoaDebugThread
class needs a working (instantiated CoaApplication object).

*/
class CoaDebugThread: public CoaBaseThread {
   Q_OBJECT
   COAMAKRO_DEKLARE_SINGLETONMETHODS ( CoaDebugThread );

public:

   CoaDebug::DebugLevel getDebugLevel(void) const;
   bool isDebuggingEnabled(void) const;
   bool showTimeInOutput(void) const;

   //!@brief Return the stored debuglevel for a give file
   CoaDebug::DebugLevel getDebugLevelForFile(const QString& filename) const;

   QMap <QString, CoaDebug::DebugLevel> getKnownFiles();


private slots:
   void enableDebugging(bool);
   void setDebugLevel(int);
   void showTimeInOutput(bool);
   void setIndent (int);

   void debug   (   const QString file,
                    int  line,
                    int level,
                    const QString message,
                    int indent
                );

   //! set a special debug level for a file
   void setDebugLevelForFile(const QString filename, int level);

   //! get a special debug level for a file
   CoaDebug::DebugLevel debugLevelForFile(const QString filename);

   //! remove a special debug level for a file
   void remDebugLevelForFile(const QString filename);

signals:
   void gotNewFileForDebugging(QString file, int level);


private:

   //store the settings in a config file
   void readMainSettings();
   void writeMainSettings();

   CoaDebug::DebugLevel readFileSettings(const QString& file);
   void removeFileSettings(const QString& file);
   void writeFileSettings(const QString& file, const CoaDebug::DebugLevel);

private:
   typedef QMap<QString, CoaDebug::DebugLevel> MapLevelForFiles;

   QReadWriteLock               m_lock;
   CoaDebug::DebugLevel         m_debugLevel;
   bool                         m_isEnabled;
   bool                         m_showTimeInOutput;
   MapLevelForFiles             m_mapFiles;
   int                          m_indent;
   CoaSettings                  m_settings;


   //not implemented
   COAMAKRO_NO_COPYCONSTRUCTOR(CoaDebugThread);
   COAMAKRO_NO_COMPARE(CoaDebugThread);
};


inline void CoaDebugThread::setIndent (int i) {
   m_indent = i;
}



#endif //__CoaDebugThread_h__

