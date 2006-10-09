/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_CSEntry

\brief    Enumerator instance
          An  enumerator  value  consists  of  a  numerical  value,  an optional
          category  type,  which  defines  the  object  type  for  the sub-class
          created by the category, and the category definition.
          When  using  the  category  as  discriminator or delineating variable,
          enumerators are associated with a type.

\date     $Date: 2006/03/13 21:30:18,62 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SDB_CSEntry"

#include  <pops7.h>
#include  <sSDB_CSEntry.hpp>


/******************************************************************************/
/**
\brief  SDB_CSEntry - 


-------------------------------------------------------------------------------
\brief  i0


\param  cs_value -
\param  cs_string -
\param  cs_type -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_CSEntry"

                        SDB_CSEntry :: SDB_CSEntry (int32 cs_value, char *cs_string, char *cs_type )
                     : value(cs_value)
{

  if ( cs_type )
    gvtxstb(type,cs_type,sizeof(type));
  else
    memset(type,' ',sizeof(type));

  memset(string,0,sizeof(string));
  if ( cs_string )
    strncpy(string,cs_string,sizeof(string)-1);


}

/******************************************************************************/
/**
\brief  i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_CSEntry"

                        SDB_CSEntry :: SDB_CSEntry ( )
                     :   value(0)
{

  memset(type,' ',sizeof(type));
  memset(string,0,sizeof(string));

}


