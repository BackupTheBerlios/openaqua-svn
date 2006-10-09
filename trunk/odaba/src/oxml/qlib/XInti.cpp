/********************************* Class Source Code ***************************/
/**
\package  OXML - 
\class    XInti

\brief    


\date     $Date: 2006/07/16 12:28:10,62 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "XInti"

#include  <pOXML.h>
#include  <sDBStructDef.hpp>
#include  <sLNode.hpp>
#include  <sXMLAttribute.hpp>
#include  <sXMLElement.hpp>
#include  <sfmcb.hpp>
#include  <snode.hpp>
#include  <sref.hpp>
#include  <sXInti.hpp>


/******************************************************************************/
/**
\brief  Cancel - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cancel"

logical XInti :: Cancel ( )
{
  logical   term = NO;
  binti::Cancel();
  Reset();
  return(term);
}

/******************************************************************************/
/**
\brief  Get - 


\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

logical XInti :: Get (EB_Number entnr )
{
  logical   term = NO;
BEGINSEQ
  *(OXMLBase *)this = entnr;

  ResetSubNodes();

  if ( GetData(xdata,struct_def,iselarea) )         ERROR
  
  SetupInst(NO);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 


\param  extinst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

logical XInti :: Get (char *extinst )
{
  logical   term = NO;
BEGINSEQ
  SDBERR(99)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetData - 


\return term - Termination code

\param  xelement - 
\param  strdef - Structure definition
\param  inst_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetData"

logical XInti :: GetData (XMLElement *xelement, DBStructDef *strdef, char *inst_data )
{
  XMLElement   *xlm;
  XMLAttribute *xla;
  int32         indx0  = 0;
  int32         offset = 0;
  fmcb         *fmcbptr;
  logical       term = NO;
  while ( xlm = xelement->GetElement(indx0++) )
  {
    offset = 0;
    if ( fmcbptr = strdef->SearchField(xlm->GetName(),&offset) )
    {
      if ( fmcbptr->GetDescription()->IsPIHandle() )  // R_REFR oder fmcbgentype(PI)
      {
        if ( SetupReference(xlm,fmcbptr,inst_data+offset) ) 
          term = YES;
      }
      else
      {
        if ( SetupAttribute(xlm,fmcbptr,inst_data+offset) )
          term = YES;
      }
    }
  }
  while ( xla = xelement->GetAttribute(indx0++) )
  {
    offset = 0;
    if ( fmcbptr = strdef->SearchField(xlm->GetName(),&offset) )
      if ( SetupAttribute(xla,fmcbptr,inst_data+offset) )
        term = YES;
  }
  return(term);
}

/******************************************************************************/
/**
\brief  GetID - 


\return entnr - 

\param  w_indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number XInti :: GetID (int32 w_indx0 )
{


  return(*this);
}

/******************************************************************************/
/**
\brief  GetSID - 


\return sid - 

\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSID"

int16 XInti :: GetSID (EB_Number entnr )
{
  XMLElement    xelement = NULL;
  int16   sid = UNDF;
  sid = inti::GetSID(entnr);
  return(sid);
}

/******************************************************************************/
/**
\brief  IsPositioned - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPositioned"

logical XInti :: IsPositioned ( )
{

  return ( stscusr1() || xdata ? YES : NO );

}

/******************************************************************************/
/**
\brief  Reset - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void XInti :: Reset ( )
{

  xdata = NULL;

  binti::Reset();

}

/******************************************************************************/
/**
\brief  SetupAttribute - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i00 - 


\param  xattribute - 
\param  fmcbptr - 
\param  inst_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupAttribute"

logical XInti :: SetupAttribute (XMLAttribute *xattribute, fmcb *fmcbptr, char *inst_data )
{
  fld           data(fmcbptr,inst_data);
  logical       term = NO;
BEGINSEQ
  if ( !fmcbptr->fmcbbase() )                       SDBERR(99)

  data = xattribute->GetValue();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  xelement - 
\param  fmcbptr - 
\param  inst_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupAttribute"

logical XInti :: SetupAttribute (XMLElement *xelement, fmcb *fmcbptr, char *inst_data )
{
  DBStructDef  *strdef;
  logical       term = NO;
BEGINSEQ
  if ( fmcbptr->fmcbbase() )
  {
    fld         data(fmcbptr,inst_data+fmcbptr->fmcbposn);
    data = xelement->GetValue();
  }
  else
  {
    if ( !(strdef = DBStructDef::GetDBStruct(fmcbptr->fmcbsmcb)) )
                                                    SDBERR(99)
    if ( GetData(xelement,strdef,inst_data+fmcbptr->fmcbposn) )       ERROR
  }


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupInst - 



\param  update - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupInst"

void XInti :: SetupInst (logical update )
{
  logical   ro;

  ro = context->IsReadOnly();
  
  stssfil();
  stsrini();
  binti::SetupInst(update);
  
  if ( ro != context->IsReadOnly() )
    SetupReadOnly();

}

/******************************************************************************/
/**
\brief  SetupReference - 


\return term - Termination code

\param  xelement - 
\param  fmcbptr - 
\param  inst_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupReference"

logical XInti :: SetupReference (XMLElement *xelement, fmcb *fmcbptr, char *inst_data )
{
  node         *nodeptr = *(node **)(inst_data+fmcbptr->fmcbposn);
  EB_Number     entnr((int64)xelement);
  logical       term = NO;
BEGINSEQ
  if ( fmcbptr->fmcbbase() )                        SDBERR(99)

  if ( !((LNode *)nodeptr)->get_noderefp() )
    if ( nodeptr->Check(YES,NO) )                   ERROR

 ((LNode *)nodeptr)->get_noderefp()->Setup(&entnr,UNDEF,0);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  XInti - 



\param  nodeptr - 
\param  strdefptr - 
\param  instptr - 
\param  crt_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "XInti"

     XInti :: XInti (node *nodeptr, DBStructDef *strdefptr, void *instptr, logical crt_opt )
                     : binti(nodeptr,NULL,strdefptr,instptr,crt_opt),
OXMLBase(NULL)
{



}

/******************************************************************************/
/**
\brief  ~XInti - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~XInti"

     XInti :: ~XInti ( )
{



}


