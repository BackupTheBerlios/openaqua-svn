/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    MemberInfo

\brief    Information about a group of properties
          The  properties of an internal data structure representation in ODABA2
          are grouped as follows:
          	ab BaseStructures
          	ab Attributes
          	ab References
          	ab Relationships
          The  class  MemberInfo  provides  information  about  such  a group as
          number  of properties in  the group and  offset of the data within the
          internal and external data area.

\date     $Date: 2006/06/05 13:22:45,15 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "MemberInfo"

#include  <popa7.h>
#include  <sMemberInfo.hpp>


/******************************************************************************/
/**
\brief  MemberInfo - 



\param  mcount - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MemberInfo"

     MemberInfo :: MemberInfo (int16 mcount )
                     :  count(mcount), int_position(0),
 ext_position(0)
{



}

/******************************************************************************/
/**
\brief  SetPosition - 



\param  intpos - 
\param  extpos - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPosition"

void MemberInfo :: SetPosition (int32 &intpos, int32 &extpos )
{

  int_position = intpos;
  ext_position = extpos;

}

/******************************************************************************/
/**
\brief  get_count - Number of properties in the property group
        The function retrieves the number of properties for the property group.
        for the data structure.
        The  function provides the offset of  the first property of the property
        group within the internal data area.

\return prop_count - Number of properties

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_count"

int32 MemberInfo :: get_count ( )
{


  return(count);
}

/******************************************************************************/
/**
\brief  get_int_position - Position in the internal data area
        Data  for the  properties of  a group  are stored together within a data
        area for the data structure.
        The  function provides the offset of  the first property of the property
        group within the internal data area.

\return position - Position

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_int_position"

uint32 MemberInfo :: get_int_position ( )
{


  return(int_position);
}

/******************************************************************************/
/**
\brief  inc_count - 


\return memcnt - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "inc_count"

int16 MemberInfo :: inc_count ( )
{

  return ( ++count );

}

/******************************************************************************/
/**
\brief  set_count - 


\return memcnt - 

\param  memcnt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_count"

int16 MemberInfo :: set_count (int16 memcnt )
{

  return ( count = memcnt );

}


