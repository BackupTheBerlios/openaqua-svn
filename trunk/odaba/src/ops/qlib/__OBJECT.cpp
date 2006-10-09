/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    __OBJECT

\brief    Database object
          Relevant  objects  can  be  defined  as database objects by inheriting
          from  this class. The  class provides two  essential features. The one
          is  the  support  for  update  timestamps, which is automatically set,
          whenever  a  modification  of  an  instance,  which type inherits from
          __OBJECT, is stored. 
          The  other feature  supported is  the global unique object identifier,
          which  is created for  each object instance,  which inherits from this
          type. 
          When   using   shared   inheritance   (multiple   derivation),  shared
          inheriting  instances should have an own  __OBJECT base class to get a
          separate  GUID  and  a  separate  update time stamp. Otherwise, shared
          instances  will  inherit  the  GUID  and the update timestamp from the
          shared base instance.

\date     $Date: 2006/03/13 21:30:24,54 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "__OBJECT"

#include  <pops7.h>
#include  <OGUIDdef.h>
#include  <sdttm.hpp>
#include  <sguid.hpp>
#include  <s__OBJECT.hpp>


/******************************************************************************/
/**
\brief  SetTimeStamp - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTimeStamp"

void __OBJECT :: SetTimeStamp ( )
{

  __LAST_UPDATE.SetCurrent();

}

/******************************************************************************/
/**
\brief  __OBJECT - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "__OBJECT"

                        __OBJECT :: __OBJECT ( )
                     :   __LAST_UPDATE()
{

  memset((void *)&__GUID,0,sizeof(__GUID));

}


