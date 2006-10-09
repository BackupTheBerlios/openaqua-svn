/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:09:46,17}|(REF)
\class    Instance

\brief    Instance Handle
          Instance  handles  are  used  to  pass  and return structured database
          instances.  Instead  of  an  instance  handle  a  (void *) area can be
          passed,  that is automatically converted  into an instance handle. The
          instance area is allocated and freed by the application.

\date     $Date: 2006/03/12 19:10:30,01 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "Instance"

#include  <pdefault.h>
#include  <sInstance.hpp>


/******************************************************************************/
/**
\brief  GetArea - Get Instance area
        The function returns a (char *) pointer to the instance area.

\return inst_area - Instance area

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetArea"

char *Instance :: GetArea ( ) const
{

  return((char *)datarea);

}

/******************************************************************************/
/**
\brief  GetData - Get data area
        The function returns a (void *) pointer to the instance area.

\return inst_area - Instance area

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetData"

void *Instance :: GetData ( ) const
{

  return(datarea);

}

/******************************************************************************/
/**
\brief  Instance - Constructor
        An  instance handle is  contructed with the  instance area passed to the
        constructor.

-------------------------------------------------------------------------------
\brief i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Instance"

                        Instance :: Instance ( )
                     : datarea(NULL)
{



}

/******************************************************************************/
/**
\brief i01


\param  inst_area - Instance area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Instance"

                        Instance :: Instance (void *inst_area )
                     : datarea(inst_area)
{



}

/******************************************************************************/
/**
\brief i02


\param  cinst_ref - Instance reference
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Instance"

                        Instance :: Instance (const Instance &cinst_ref )
                     : datarea(cinst_ref.GetData())
{



}

/******************************************************************************/
/**
\brief  SetData - Set instance area
        The function allows assigning a new instance area to the key handle.

\return inst_area - Instance area

\param  inst_area - Instance area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetData"

void *Instance :: SetData (void *inst_area )
{

  return(datarea = inst_area);

}

/******************************************************************************/
/**
\brief  operator logical - Type conversion
        The  operator converts the instance handle  into a logical (bool) value.
        The  value is  true (YES)  when the  handle has an instance area pointer
        and  false (NO) when  the instance area  pointer is false. This operator
        allows using instance handles in logical operations.

\return notype -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator logical"

NOTYPE Instance :: operator logical ( )
{

  return datarea ? YES : NO;

}

/******************************************************************************/
/**
\brief  operator& - Address operator
        The operator returns the instance area.

\return inst_area - Instance area

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator&"

void *Instance :: operator& ( )
{


  return(datarea);
}

/******************************************************************************/
/**
\brief  operator= - Assignment operator
        The  operator  allows  assigning  a  new  instance  area from the passed
        instance handle to the instance handle.

\return inst_ref
-------------------------------------------------------------------------------
\brief i00


\param  cinst_ref - Instance reference
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

Instance Instance :: operator= (const Instance &cinst_ref )
{

  datarea = cinst_ref.GetData();
  return(*this);
}

/******************************************************************************/
/**
\brief i01


\param  datarea -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

Instance Instance :: operator= (void *datarea )
{

  this->datarea = datarea;
  return(*this);
}

/******************************************************************************/
/**
\brief  ~Instance - Destructor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~Instance"

                        Instance :: ~Instance ( )
{



}


