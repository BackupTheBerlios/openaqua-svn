#ifndef __AB_Error_h__
#define __AB_Error_h__

//#include "AquaBase.h"
#include <QObject>

class Error;
namespace AquaBase
{

   /**
   @brief A general Error object

   This object holds happend errors and provides simple access methods.
   The Object just holds errors. The Object itself does nothing from itself.

   Old Comments:
   The error object is used to store and pass error information to the
   application. Errors are identified by error class and eror number.

   In addition the class and function name detecting the problem and a
   short error explanation can be provided. Moreover, an error may
   include upto 6 context depending error variables that can be
   displayed in the error message.

   Usually error messages are written to a log file (error.lst)
   which is stored in a folder addressed by the TRACE environment
   or ini-file variable. It is, however, also possible to display errors
   on the terminal.

   Usually errors should be reset in all functions that may signal an error.
   Otherwise the calling function may not be able to determine whether the
   error signaled is an old error or has just been signaled in the
   called function. This strategy requires, on the other hand, that
   signaled errors have to be saved when other functions are called
   in the error handling thet might generate errors again, since
   those functions will reset the error. You can use the Copy()
   function to save the error.

   The way errors are presented in the application depends on
   the error handler installed (ErroerHandle). Usually errors are
   written to the console output for console applications and
   shown in a message box for windows applications.

   */
   class AB_Error: public QObject
   {
      Q_OBJECT
      Q_PROPERTY( QString title READ title WRITE setTitle RESET setTitle STORED true );
      Q_PROPERTY( QString description READ description WRITE setDescription RESET setDescription STORED true );
      Q_PROPERTY( QString module READ module WRITE setModule RESET setModule STORED true );
      Q_PROPERTY( QString object READ object WRITE setObject RESET setObject STORED true );
      Q_PROPERTY( QString threadId READ threadId WRITE setThreadId RESET setThreadId STORED true );

   public:
      AB_Error( QObject *const parent );
      void reset();

   protected:
      AB_Error( QObject *const parent, Error * const error );

   public:
      virtual ~AB_Error();

      const QString title() const;
      void setTitle(const QString& = QString());

      const QString description() const;
      void setDescription(const QString& = QString());

      const QString module() const;
      void setModule(const QString& = QString());


      const QString object() const;
      void setObject(const QString& = QString());


      const int threadId() const;
      void setThreadId(const int = 0);
      void setThreadId(const QString&);


   private:
      friend class AB_Connection;
      QString m_title;
      QString m_description;
      QString m_module;
      QString m_object;
      int m_threadId;

      AB_Error( );
   };
};
#endif //__AB_Error_h__

