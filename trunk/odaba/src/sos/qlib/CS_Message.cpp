/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    CS_Message

\brief    


\date     $Date: 2006/03/12 19:21:27,35 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CS_Message"

#include  <pdefault.h>
#include  <sCS_Buffer.hpp>
#include  <sCS_Handle.hpp>
#include  <sCS_Message.hpp>


/******************************************************************************/
/**
\brief  CS_Message


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CS_Message"

                        CS_Message :: CS_Message ( )
                     : capacity(0),
  conn_handle(),
  class_id(0),
  function_id(0),
  length(0),
  data(NULL),
  owning_data(YES),
  flush(NO)
{



}

/******************************************************************************/
/**
\brief  Copy


\param  cs_msg -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

void CS_Message :: Copy (CS_Message *cs_msg )
{

  conn_handle = *cs_msg->GetHandle();
  class_id    = cs_msg->class_id;
  function_id = cs_msg->function_id;
  SetData(cs_msg->GetData());
  SetLength(cs_msg->GetLength());

}

/******************************************************************************/
/**
\brief  Flush - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Flush"

void CS_Message :: Flush ( )
{

  flush = YES;

}

/******************************************************************************/
/**
\brief  GetData

\return datarea -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetData"

char *CS_Message :: GetData ( )
{


  return(data);
}

/******************************************************************************/
/**
\brief  GetHandle

\return handle -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHandle"

CS_Handle *CS_Message :: GetHandle ( )
{

  return(&conn_handle);

}

/******************************************************************************/
/**
\brief  GetLength

\return inst_len - Instance size

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLength"

int32 CS_Message :: GetLength ( )
{

return( length );

}

/******************************************************************************/
/**
\brief  Reset

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical CS_Message :: Reset ( )
{
  logical                 term = NO;
  if ( !owning_data )
  {
    capacity = 0;
    length = 0;
    data = NULL;
    owning_data = YES;
  }

  return(term);
}

/******************************************************************************/
/**
\brief  SetData


\param  datarea -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetData"

void CS_Message :: SetData (char *datarea )
{

  if( owning_data && data != NULL ) free( data );
  data = datarea;
  owning_data= data ? NO : YES;

}

/******************************************************************************/
/**
\brief  SetLength - 



\param  inst_len - Instance size
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLength"

void CS_Message :: SetLength (int32 inst_len )
{

if( owning_data && ( capacity > 4096 || inst_len > capacity ) )
{
    if( data != NULL ) free( data );
    data= (char*) malloc( capacity= inst_len );
}
length= inst_len;


}

/******************************************************************************/
/**
\brief  ~CS_Message


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CS_Message"

                        CS_Message :: ~CS_Message ( )
{

if( owning_data && data != NULL ) free( data );
data = NULL;
capacity = 0;
owning_data = NO;

}


