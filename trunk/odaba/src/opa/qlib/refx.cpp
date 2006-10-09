/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|18:19:36,78}|(REF)
\class    refx

\brief    


\date     $Date: 2006/03/31 16:55:38,39 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "refx"

#include  <popa7.h>
#include  <sDBHandle.hpp>
#include  <sDBIndex.hpp>
#include  <sEB_Number.hpp>
#include  <sLACObject.hpp>
#include  <sexd.hpp>
#include  <sinti.hpp>
#include  <srefx.hpp>


/******************************************************************************/
/**
\brief  AddExt - 


\return lindx0 - 

\param  ebsnum - 
\param  skey - 
\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddExt"

int32 refx :: AddExt (EB_Number ebsnum, char *skey, int32 lindx0 )
{

BEGINSEQ
  if ( !refrex->IsEmpty(ob_handle->get_pif()) && *refrex != ebsnum )
  {
    SetKeyErrorVariables(NULL);
    SDBERR(64)
  }

  *refrex = ebsnum;
  refcuri = 0;
  stssmod();

RECOVER
  refcuri = AUTO;
ENDSEQ
  return(refcuri);

}

/******************************************************************************/
/**
\brief  AddID - 


\return term - Termination code

\param  intiptr - 
\param  entnr - 
\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddID"

logical refx :: AddID (inti *intiptr, EB_Number entnr, int32 lindx0 )
{

  return ( AddExt(entnr,NULL,AUTO) == AUTO );

}

/******************************************************************************/
/**
\brief  CheckWProtect - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckWProtect"

logical refx :: CheckWProtect ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DelExt - 


\return term - Termination code

\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DelExt"

logical refx :: DelExt (int32 lindx0 )
{

  // wenn wir kein deletereference machen, ist immer gesichert, daß in der EBI-Nummer ein gültiger Wert steht. 
  // statt dessen müßte der ebi allerdings zurückgesetzt werden (new oder delete)

  DeleteReference();
  *refrex = 0;
  stssmod();

  return(NO);
}

/******************************************************************************/
/**
\brief  DeleteID - 


\return term - Termination code

\param  intiptr - 
\param  oldinst - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteID"

logical refx :: DeleteID (inti *intiptr, void *oldinst, EB_Number entnr )
{
  logical   term = NO;
BEGINSEQ
//  if ( entnr != *refrex )                            ERROR
  if ( DelExt(refcuri) )                             ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetCount - 


\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 refx :: GetCount ( )
{

  return ( !refrex || refrex->IsEmpty() ? 0 : 1);


}

/******************************************************************************/
/**
\brief  GetID - 


\return ebsnum - 

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number refx :: GetID (int32 indx0 )
{

  return ( indx0 == 0 && refrex ? *refrex : EB_Number(0) );


}

/******************************************************************************/
/**
\brief  GetIndex - 


\return lindx0 - 

\param  skey - 
\param  ebsnum - 
\param  exact - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIndex"

int32 refx :: GetIndex (char *skey, EB_Number ebsnum, logical exact )
{

  refcuri = ebsnum.IsEmpty() || !refrex || *refrex != ebsnum 
            ? AUTO : 0;
  return(refcuri);
}

/******************************************************************************/
/**
\brief  UpdateID - 


\return term - Termination code

\param  intiptr - 
\param  oldinst - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateID"

logical refx :: UpdateID (inti *intiptr, void *oldinst, EB_Number entnr )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  refx - 



\param  lobhandle - 
\param  extref - 
\param  clnumb - 
\param  akcbptr - 
\param  globind - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "refx"

                        refx :: refx (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, logical globind )
                     : ref(lobhandle,extref,clnumb,akcbptr,globind)

{



}

/******************************************************************************/
/**
\brief  refxsup - 



\param  rexptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "refxsup"

void refx :: refxsup (EB_Number *rexptr )
{

  refrex   = rexptr;
  refcuri  = AUTO;
  refmod   = NO;


}

/******************************************************************************/
/**
\brief  ~refx - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~refx"

                        refx :: ~refx ( )
{



}


