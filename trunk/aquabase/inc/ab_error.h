#ifndef __Odaba_Error_h__
#define __Odaba_Error_h__

#include "AquaBase.h"


class Error;
namespace AquaBase
{
   class AB_Error: public QObject
   {
      Q_OBJECT
      Q_PROPERTY( QString title READ title WRITE setTitle RESET resetTitle STORED true );
      Q_PROPERTY( QString description READ description WRITE setDescription RESET resetDescription STORED true );

   public:
      AB_Error( QObject *const parent );
   protected:
      AB_Error( QObject *const parent, Error * const error );

   public:
      virtual ~AB_Error();

      const QString title() const;
      void setTitle(const QString& );
      void resetTitle();

      const QString description() const;
      void setDescription(const QString&);
      void resetDescription();


   private:
      friend class AB_Connection;
      QString m_title;
      QString m_description;

      AB_Error( );
   };
};
#endif //__Odaba_Error_h__

