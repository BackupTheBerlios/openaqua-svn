/********************************* Class Declaration ***************************/
/**
\package  OPI
\class    Key

\brief    Key Handle
          Key  handles are used to pass and return keys. Instead of a key handle
          a  (char *) area can be passed, that is automatically converted into a
          key. The key area is allocated and freed by the application.

\date     $Date: 2006/05/14 11:55:21,76 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   Key_HPP
#define   Key_HPP

#include "copadll.h"
class     Key;

#include  <sKeyClass.hpp>
#pragma pack(8)

class  Key
{
protected  :         char                                        *datarea;                                                   

public     :
                     char                                        *get_datarea() { return(datarea); }
public     :                  OPIImpExp             char *GetData ( );
public     :                  OPIImpExp                  Key (char *keyarea );
public     :                  OPIImpExp                  Key ( );
public     :                  OPIImpExp                  Key (int32 &int32_ref );
public     : static           OPIImpExp             Key __cdecl NewAutoident ( );
public     :                                        char *SetData (char *keyarea );
public     :                  OPIImpExp             NOTYPE operator char* ( );
public     :                  OPIImpExp             char *operator& ( );
public     :                  OPIImpExp             Key &operator= (const Key &key_refc );
};

#pragma pack()
#endif
