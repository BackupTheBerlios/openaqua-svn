/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    CS_Handle

\brief    


\date     $Date: 2006/03/12 19:21:26,87 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CS_Handle"

#include  <pdefault.h>
#include  <sCS_Handle.hpp>


/******************************************************************************/
/**
\brief  CS_Handle


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CS_Handle"

                        CS_Handle :: CS_Handle ( )
{

  SetClientObject(0);
  SetServerObject(0);

}

/******************************************************************************/
/**
\brief  GetClientObject

\return client_handle -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClientObject"

int64 CS_Handle :: GetClientObject ( )
{
  int64      result;
  LoadBigInt(result,&client_object);
  return( result );

}

/******************************************************************************/
/**
\brief  GetClientPointer

\return client_ptr -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClientPointer"

void *CS_Handle :: GetClientPointer ( )
{
  int64      result;
  LoadBigInt(result,&client_object);
  return(*(void **)&result);

}

/******************************************************************************/
/**
\brief  GetServerObject

\return server_handle -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetServerObject"

int64 CS_Handle :: GetServerObject ( )
{
  int64      result;
  LoadBigInt(result,&server_object);
  return(result);

}

/******************************************************************************/
/**
\brief  GetServerPointer

\return server_ptr -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetServerPointer"

void *CS_Handle :: GetServerPointer ( )
{
  int64      result;
  LoadBigInt(result,&server_object);
  return(*(void **)&result);

}

/******************************************************************************/
/**
\brief  SetClientObject


\param  client_obj -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetClientObject"

void CS_Handle :: SetClientObject (int64 client_obj )
{

  if ( this )
    StoreBigInt(&client_object,client_obj);

}

/******************************************************************************/
/**
\brief  SetClientPointer


\param  client_ptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetClientPointer"

void CS_Handle :: SetClientPointer (void *client_ptr )
{

  if ( sizeof(void *) == 8 )
  {
    StoreBigInt(&client_object,client_ptr);
  }
  else
  {
    StoreLong(&client_object,client_ptr);
  }

}

/******************************************************************************/
/**
\brief  SetServerObject


\param  server_obj -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetServerObject"

void CS_Handle :: SetServerObject (int64 server_obj )
{

  if ( this )
    StoreBigInt(&server_object,server_obj);

}

/******************************************************************************/
/**
\brief  SetServerPointer


\param  server_ptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetServerPointer"

void CS_Handle :: SetServerPointer (void *server_ptr )
{

  if ( sizeof(void *) == 8 )
  {
    StoreBigInt(&server_object,server_ptr);
  }
  else
  {
    StoreLong(&server_object,server_ptr);
  }

}

/******************************************************************************/
/**
\brief  operator= - 


\return handle_ref -

\param  handle_refc
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

CS_Handle &CS_Handle :: operator= (const CS_Handle &handle_refc )
{

  memcpy(this,&handle_refc,sizeof(CS_Handle));
  return(*this);
}

/******************************************************************************/
/**
\brief  operator==

\return cond - Return value

\param  handle_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical CS_Handle :: operator== (CS_Handle &handle_ref )
{
  int64    server, rserver;
  int64    client, rclient;
  LoadBigInt(server,&server_object);
  LoadBigInt(client,&client_object);
  LoadBigInt(rserver,&handle_ref.server_object);
  LoadBigInt(rclient,&handle_ref.client_object);
  
  return ( server == rserver && client == rclient ? YES : NO );

}


