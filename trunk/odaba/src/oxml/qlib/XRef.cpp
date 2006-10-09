/********************************* Class Source Code ***************************/
/**
\package  OXML - 
\class    XRef

\brief    


\date     $Date: 2006/06/29 12:07:40,17 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "XRef"

#include  <pOXML.h>
#include  <sBinTree.hpp>
#include  <sDBIndex.hpp>
#include  <sLACObject.hpp>
#include  <sXMLElement.hpp>
#include  <sXRef.hpp>


/******************************************************************************/
/**
\brief  GetCount - 


\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 XRef :: GetCount ( )
{
  int32   count;
BEGINSEQ
  if ( !this || !xdata )                            ERROR
  
  count = xdata->GetElementCount();
RECOVER
  count = ERIC;
ENDSEQ
  return(count);
}

/******************************************************************************/
/**
\brief  GetID - 


\return ebsnum - 

\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number XRef :: GetID (int32 lindx0 )
{
  OXMLBase    xbase( GetElement(lindx0) );

  return(xbase);
}

/******************************************************************************/
/**
\brief  GetIndex - 


\return lindx0 - 
-------------------------------------------------------------------------------
\brief  REFNGT_K - 


\param  skey - 
\param  ebsnum - 
\param  exact - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIndex"

int32 XRef :: GetIndex (char *skey, EB_Number ebsnum, logical exact )
{
  BTIterator   bti(tree);
  int32        lindx0 = AUTO;
BEGINSEQ
  if ( !tree )                                      ERROR

  lindx0 = bti.GetPosition(skey,exact);
RECOVER
  lindx0 = AUTO;
ENDSEQ
  return(lindx0);
}

/******************************************************************************/
/**
\brief  i1 - 


\param  ebsnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIndex"

int32 XRef :: GetIndex (EB_Number ebsnum )
{
  XMLElement   *xelement = XElement(ebsnum);
  XMLElement   *xlm;
  int32         lindx0 = 0;
BEGINSEQ
  if ( !xelement )                                  ERROR
  
  while ( xlm = GetElement(lindx0) )
    if ( xlm != xelement ) 
      break;
    else
      lindx0++;
  
  if ( !xlm )                                       ERROR
RECOVER
  lindx0 = AUTO;
ENDSEQ
  return(lindx0);
}

/******************************************************************************/
/**
\brief  Reset - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical XRef :: Reset ( )
{
  logical   term;
  if ( refrex )
    *refrex = 0;
  *(OXMLBase *)this = EB_Number();  
  
  ref::Reset();
  return(term);
}

/******************************************************************************/
/**
\brief  Setup - 


\return term - 

\param  extref - 
\param  clnumb - 
\param  w_mbnumber - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

logical XRef :: Setup (EB_Number *extref, EB_Number clnumb, int16 w_mbnumber )
{
  XMLElement  *xelement = NULL;
  int32        indx0    = 0;
  logical      term     = NO;
  Reset();
  
  *refrex = *extref;
  *(OXMLBase *)this = *extref;  

// when a key has been defined, index must be filled now

  stssfil();

  return(term);
}

/******************************************************************************/
/**
\brief  XRef - 



\param  lobhandle - 
\param  akcbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "XRef"

     XRef :: XRef (LACObject *lobhandle, DBIndex *akcbptr )
                     : ref(lobhandle,NULL,UNDEF,akcbptr,NO),
OXMLBase(NULL),
  tree(NULL)
{

  refrex = new EB_Number();

}

/******************************************************************************/
/**
\brief  ~XRef - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~XRef"

     XRef :: ~XRef ( )
{

  delete refrex;
  refrex = 0;

}


