/********************************* Class Source Code ***************************/
/**
\package  OPI
\class    Key

\brief    Key Handle
          Key  handles are used to pass and return keys. Instead of a key handle
          a  (char *) area can be passed, that is automatically converted into a
          key. The key area is allocated and freed by the application.

\date     $Date: 2006/05/22 13:09:22,64 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "Key"

#include  <pdefault.h>
#include  <sKeyClass.hpp>


/******************************************************************************/
/**
\brief  GetData - Provide key area
        The function returns the key instance area as (char *) pointer.

\return keyarea - Key area

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetData"

char *Key :: GetData ( )
{

  return(datarea);

}

/******************************************************************************/
/**
\brief  Key - Konstruktor
        A key handle is contructed with the key area passed to the handle.

-------------------------------------------------------------------------------
\brief  i0


\param  keyarea - Key area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Key"

     Key :: Key (char *keyarea )
                     :   datarea(keyarea)
{
}

/******************************************************************************/
/**
\brief  i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Key"

     Key :: Key ( )
                     :   datarea(NULL)
{
}

/******************************************************************************/
/**
\brief  i02


\param  int32_ref
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Key"

     Key :: Key (int32 &int32_ref )
                     :   datarea((char *)&int32_ref)
{
}

/******************************************************************************/
/**
\brief  NewAutoident

\return key - Key value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NewAutoident"

Key __cdecl Key :: NewAutoident ( )
{
  static int32   empty_autoident = 0;

  return ( Key((char *)&empty_autoident) );

}

/******************************************************************************/
/**
\brief  SetData - Set key area
        The function allows assigning a new key area to the key handle.

\return keyarea - Key area

\param  keyarea - Key area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetData"

char *Key :: SetData (char *keyarea )
{
  return(datarea = keyarea);
}

/******************************************************************************/
/**
\brief  operator char* - Type conversion
        The  operator supports implicite type  conversion from (char *) pointers
        into key handles.

\return notype - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator char*"

NOTYPE Key :: operator char* ( )
{

  return (datarea);

}

/******************************************************************************/
/**
\brief  operator& - Adress operator
        The operator returns the key area.

\return keyarea - Key area

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator&"

char *Key :: operator& ( )
{

  return(datarea);

}

/******************************************************************************/
/**
\brief  operator= - Assignment operator
        The  operator allows assigning a new key area from the passed key handle
        to the key handle.

\return key_ref

\param  key_refc
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

Key &Key :: operator= (const Key &key_refc )
{

  datarea = key_refc.datarea;
  return(*this);
}


