/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    ODE_SearchReplace

\brief    


\date     $Date: 2006/03/12 19:36:56,56 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODE_SearchReplace"

#include  <pdesign.h>
#include  <sRegExp.hpp>
#include  <sODE_SearchReplace.hpp>


/******************************************************************************/
/**
\brief  ClosePHs


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClosePHs"

void ODE_SearchReplace :: ClosePHs ( )
{

BEGINSEQ
  if ( !IsValid() )                                  LEAVESEQ
  
  search_string.Close();
  replace_string.Close();
  location.Close();
  replace.Close();
  replace_all.Close();
  backwards.Close();
  case_sensitive.Close();
  is_regex.Close();
  
  Close();
ENDSEQ

}

/******************************************************************************/
/**
\brief  Deinit


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deinit"

void ODE_SearchReplace :: Deinit ( )
{

  dictionary = DictionaryHandle();

}

/******************************************************************************/
/**
\brief  GetCaseSensitive

\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCaseSensitive"

logical ODE_SearchReplace :: GetCaseSensitive ( )
{

  return ( case_sensitive.IsTrue() );

}

/******************************************************************************/
/**
\brief  GetData

\return term -

\param  scope -
\param  do_replace -
\param  ctxptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetData"

logical ODE_SearchReplace :: GetData (char *scope, logical do_replace, CTX_GUIBase *ctxptr )
{
  static const RegExp  deregex_search("([][*.^${}()?\\\\])", "\\\\$1");
  static const RegExp  deregex_replace("([\\\\$])","\\\\$1");
  std::string          search;
  std::string          replace;
  logical              term   = NO;
BEGINSEQ
  if ( Initialize(scope,do_replace) )                ERROR
    
  if ( ctxptr->ExecuteWindow(this,"FORM_SearchReplace",
                             do_replace ? "Replace" : "Search",NO) )
                                                     ERROR
  if ( !IsRegExp() )
  {
    search  = GetSearchString();
    replace = GetReplaceString();
    
    deregex_search.Replace(search);
    deregex_replace.Replace(replace);
    
    search_string.SetValue(const_cast<char *>(search.c_str()));
    replace_string.SetValue(const_cast<char *>(replace.c_str()));
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetLocation

\return location

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLocation"

int32 ODE_SearchReplace :: GetLocation ( )
{

  return ( location.GetInt() );

}

/******************************************************************************/
/**
\brief  GetReplace

\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetReplace"

logical ODE_SearchReplace :: GetReplace ( )
{

  return ( replace.IsTrue() );

}

/******************************************************************************/
/**
\brief  GetReplaceAll

\return replace -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetReplaceAll"

logical ODE_SearchReplace :: GetReplaceAll ( )
{

  return ( replace_all.IsTrue() );

}

/******************************************************************************/
/**
\brief  GetReplaceString

\return string

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetReplaceString"

char *ODE_SearchReplace :: GetReplaceString ( )
{

  return ( replace_string.GetString() );

}

/******************************************************************************/
/**
\brief  GetSearchString

\return string

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSearchString"

char *ODE_SearchReplace :: GetSearchString ( )
{

  return ( search_string.GetString() );

}

/******************************************************************************/
/**
\brief  Init


\param  dict_handle -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Init"

void ODE_SearchReplace :: Init (DictionaryHandle &dict_handle )
{

  dictionary = dict_handle;

}

/******************************************************************************/
/**
\brief  Initialize - 


\return term -

\param  scope -
\param  do_replace -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical ODE_SearchReplace :: Initialize (char *scope, logical do_replace )
{
  logical                 term = NO;
BEGINSEQ
  if ( OpenPHs() )                                   ERROR

  if ( !location.GetInt() )
    location = scope;
    
  replace  = do_replace;

  if ( !do_replace )
    replace_all = NO;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsRegExp

\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsRegExp"

logical ODE_SearchReplace :: IsRegExp ( )
{

  return ( is_regex.IsTrue() );

}

/******************************************************************************/
/**
\brief  ODE_SearchReplace - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODE_SearchReplace"

                        ODE_SearchReplace :: ODE_SearchReplace ( )
                     : PropertyHandle (),
  dictionary(),
  search_string(),
  replace_string(),
  location(),
  replace(),
  replace_all(),
  backwards(),
  case_sensitive(),
  is_regex()
{



}

/******************************************************************************/
/**
\brief  OpenPHs

\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenPHs"

logical ODE_SearchReplace :: OpenPHs ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( IsValid() )                                   LEAVESEQ
    
  if ( Open(dictionary,"FORM_SearchReplace") )
  {
    P_SDBCERR
    P_ERR(ODABA_ERROR)
  }
  
  search_string.Open(GPH("search_string"));
  replace_string.Open(GPH("replace_string"));
  location.Open(GPH("location"));
  replace.Open(GPH("replace"));
  replace_all.Open(GPH("replace_all"));
  backwards.Open(GPH("backwards"));
  case_sensitive.Open(GPH("case_sensitive"));
  is_regex.Open(GPH("is_regex"));  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetReplaceAll


\param  do_replace -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReplaceAll"

void ODE_SearchReplace :: SetReplaceAll (logical do_replace )
{

replace_all = do_replace;


}

/******************************************************************************/
/**
\brief  ~ODE_SearchReplace - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODE_SearchReplace"

                        ODE_SearchReplace :: ~ODE_SearchReplace ( )
{

  ClosePHs();

  Deinit();

}


