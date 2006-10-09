/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/20|15:35:34,34}|(REF)
\class    sHTMLDescriptor



\date     $Date: 2006/04/24 11:56:38,35 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sHTMLDescriptor"

#include  <padkctxi.h>
#include  <ssHTMLDescriptor.hpp>


/******************************************************************************/
/**
\brief  Create

\return rc - 

\param  strctx_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sHTMLDescriptor :: Create (CTX_Structure **strctx_ptrp )
{

  *strctx_ptrp = new sHTMLDescriptor();
  return(NO);


}

/******************************************************************************/
/**
\brief  DBRead

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBRead"

logical sHTMLDescriptor :: DBRead ( )
{

  SetupClass();
  return(NO);
}

/******************************************************************************/
/**
\brief  DBStore

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBStore"

logical sHTMLDescriptor :: DBStore ( )
{

  SetupClass();
  return(NO);
}

/******************************************************************************/
/**
\brief  SetupClass

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupClass"

logical sHTMLDescriptor :: SetupClass ( )
{
  PropertyHandle   *ph = GetPropertyHandle();
  char             *prop_path;
  char             *strname;
  DictionaryHandle  dictptr = ph->GetDictionary();
  DBStructDef      *struct_def;
  fmcb             *fmcbptr;
  int32             offset = 0;

  if ( GetPropertyHandle()->IsWrite() )
  {
    if ( strname = ph->GetParentProperty()->GetString("class") )
    {
      if ( *ph->GetString("source") != '*' )
      {
        if ( (struct_def = dictptr.GetStructDef(strname)) &&
             (fmcbptr = struct_def->SearchField(ph->GetString("source"),&offset)) )
          strname = fmcbptr->fmcbtype;
        else
          strname = NULL;
      }
    }
  
    *GetPropertyHandle("class") = (char*)(strname ? strname : "");
  }
  return(NO);
}

/******************************************************************************/
/**
\brief  sHTMLDescriptor


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sHTMLDescriptor"

                        sHTMLDescriptor :: sHTMLDescriptor ( )
                     : CTX_Structure ()
{



}

/******************************************************************************/
/**
\brief  ~sHTMLDescriptor


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sHTMLDescriptor"

                        sHTMLDescriptor :: ~sHTMLDescriptor ( )
{



}


