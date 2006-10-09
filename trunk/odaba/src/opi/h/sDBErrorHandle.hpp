/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/15|17:41:08,71}|(REF)
\class    DBErrorHandle

\brief    Database Error Handle
          The  database error handle provides  extended documentation for errors
          detected  in  the  system.  In  contrast  to the basic ErrorHandle the
          DBErrorHandle  locates  signaled  errors  in the system or application
          database and provides detailled information for the error detected. 
          A  application  specific  error  handle  can  be  defined  and set for
          enabling application specific error handling (-> ErrorHandle).

\date     $Date: 2006/03/19 20:59:26,85 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBErrorHandle_HPP
#define   DBErrorHandle_HPP
#include "copadll.h"

class     DBErrorHandle;

class     Error;
#include  <sDBObjectHandle.hpp>
#include  <sErrorHandle.hpp>
#pragma pack(8)

class  DBErrorHandle :public ErrorHandle
{
protected  :         DBObjectHandle                               ob_handle ATTR_ALIGN(4);                                   

public     :
                     DBObjectHandle                              &get_ob_handle() { return(ob_handle); }
public     :         OPIImpExp                                           DBErrorHandle (DBObjectHandle &object_handle );
public     : virtual OPIImpExp                   logical DisplayMessage (Error *error_obj );
public     : virtual OPIImpExp                   char GetError (Error *error_obj, void *error_source );
public     : virtual OPIImpExp                   int32 GetErrorHelpID (Error *error_obj );
public     :         OPIImpExp                   DBObjectHandle &GetObjectHandle ( );
public     :         OPIImpExp                   void SetObjectHandle (DBObjectHandle &obhandle );
public     : virtual OPIImpExp                                           ~DBErrorHandle ( );
};

#pragma pack()
#endif
