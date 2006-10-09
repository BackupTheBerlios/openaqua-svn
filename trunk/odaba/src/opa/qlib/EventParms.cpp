/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EventParms

\brief    


\date     $Date: 2006/03/12 19:17:33,50 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EventParms"

#include  <popa7.h>
#include  <sEventParms.hpp>


/******************************************************************************/
/**
\brief  EventParms - Konstruktor



\param  is_inst -
\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EventParms"

                        EventParms :: EventParms (logical is_inst, EB_Number entnr )
                     :   term(0)
{

  is_instance = is_inst ? 'Y' : 'N';
  gvtxltp((char *)memset(identity,'9',sizeof(identity)),entnr.get_ebsnum(),sizeof(identity));


}

/******************************************************************************/
/**
\brief  GetID - 


\return identity - Local Instance identity (LOID)

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

uint64 EventParms :: GetID ( )
{

  return(this ? atol(identity) : 0);

}

/******************************************************************************/
/**
\brief  IsInstance - 


\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsInstance"

logical EventParms :: IsInstance ( )
{

  return(this ? is_instance == 'Y' : NO);

}

/******************************************************************************/
/**
\brief  ~EventParms - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~EventParms"

                        EventParms :: ~EventParms ( )
{



}


