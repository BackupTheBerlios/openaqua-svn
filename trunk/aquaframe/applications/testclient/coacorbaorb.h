#ifndef __CoaCorbaOrb_h__
#define __CoaCorbaOrb_h__

#include <CoaMakros>
#include <cassert>
#include "contactC.h"

/**

*/

class CoaCorbaOrb: public QObject {
Q_OBJECT
public:
   //explicit CoaCorbaOrb (QObject *const parent = 0);
   //virtual ~CoaCorbaOrb ();
   virtual bool isValid() const;
   CORBA::ORB_var& getOrbInterface() throw (CORBA::Exception);
   CORBA::Object_var getCorbaObject(const CoaString&) throw (CORBA::Exception);

private:
   CORBA::ORB_var m_orb;
   bool m_valid;
      
   
   COAMAKRO_DEKLARE_SINGLETONMETHODS ( CoaCorbaOrb );
   COAMAKRO_NO_COPYCONSTRUCTOR(CoaCorbaOrb);
   COAMAKRO_NO_COMPARE(CoaCorbaOrb);

};







#endif //__CoaCorbaOrb_h__

