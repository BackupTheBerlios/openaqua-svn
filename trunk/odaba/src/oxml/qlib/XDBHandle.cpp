/********************************* Class Source Code ***************************/
/**
\package  OXML - 
\class    XDBHandle

\brief    


\date     $Date: 2006/08/26 12:57:43,26 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "XDBHandle"

#include  <pOXML.h>
#include  <sDBExtend.hpp>
#include  <sDictionary.hpp>
#include  <sOXMLBase.hpp>
#include  <igvtx.h>
#include  <smvli.hpp>
#include  <snode.hpp>
#include  <sXDBHandle.hpp>


/******************************************************************************/
/**
\brief  AddExtendRef - 



\return extref - 

\param  dbextdef - Extent definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddExtendRef"

EB_Number *XDBHandle :: AddExtendRef (DBExtend *dbextdef )
{
  char          names[ID_SIZE+1];
  EB_Number *   extref = NULL;
BEGINSEQ
  if ( !dbextdef )                                  ERROR
  gvtxbts(names,dbextdef->fmcbname,sizeof(names)-1);

  OXMLBase    ext(xs.AddElement(names));
  temp_extend_list->AddExt(ext,dbextdef->GetNameKey(),UNDEF);

  extref = GetExtendRef(dbextdef->GetNameKey());
RECOVER
  extref = NULL;
ENDSEQ
  return(extref);
}

/******************************************************************************/
/**
\brief  GetExtent - 



\return ext_name - 

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtent"

char *XDBHandle :: GetExtent (int32 indx0 )
{

  return( dictionary->GetExtent(indx0) );

}

/******************************************************************************/
/**
\brief  InitExtents - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitExtents"

logical XDBHandle :: InitExtents ( )
{
  XMLElement *xelement = NULL;
  XMLElement *xextent  = NULL;
  TypeKey     tkey;
  int32       indx0 = 0;
  char       *ename;
  logical     term = NO;
BEGINSEQ
  if ( CreateTempExtentList() )                      ERROR

  xs.ResetCurrent();
  while ( xelement = xs.GetNextElement() )
  {
    indx0 = 0;
    xelement->ResetCurrent();
    while ( xextent = xelement->GetNextElement() )                    // get extents
    {
      tkey.Initialize(xextent->GetName(),0);
      temp_extend_list->AddExt(EB_Number((int64)xextent),tkey,UNDEF);
    }
  }


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Initialize - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  dict_ptr - Dictionary handle
\param  cpath - Complete path
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void XDBHandle :: Initialize (Dictionary *dict_ptr, char *cpath, PIACC accopt )
{

BEGINSEQ
  SDBCERR

  DBHandle::Initialize(dict_ptr,cpath,accopt,NO);
  LACObject::Initialize(this,accopt);

  SDBEV1("",UNDEF)
  if ( !cpath || !*cpath )                           SDBERR(5)
  SDBEV1(cpath,UNDEF)
  if ( xs.Open(cpath) )                              ERROR
  
  if ( InitExtents() )                               ERROR
  CreateContext();

  if ( context && context->ExecuteAction(DBP_Open) )
  {
    SDBCERR
    SDBCTXCERR
    SDBERR(99)
  }

// die ressource muß noch angelegt werden!
  if ( context )
  {
    context->ExecuteAction(DBO_Opened);
    context->SetProcessState(PRC_Opened);
  }
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i01 - 



\param  dict_ptr - Dictionary handle
\param  accopt - Access mode
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void XDBHandle :: Initialize (Dictionary *dict_ptr, PIACC accopt, uint16 version_nr )
{



}

/******************************************************************************/
/**
\brief  IsXMLBase - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsXMLBase"

logical XDBHandle :: IsXMLBase ( )
{
  logical   cond = YES;

  return(cond);
}

/******************************************************************************/
/**
\brief  XDBHandle - 




\param  dict_ptr - Dictionary handle
\param  cpath - Complete path
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "XDBHandle"

     XDBHandle :: XDBHandle (Dictionary *dict_ptr, char *cpath, PIACC accopt )
                     : DBHandle(),
LACObject (),
ACObject(), 
  xs()
{

BEGINSEQ
  SDBCERR
  
  XDBHandle::Initialize(dict_ptr,cpath,accopt);
RECOVER

ENDSEQ

}


