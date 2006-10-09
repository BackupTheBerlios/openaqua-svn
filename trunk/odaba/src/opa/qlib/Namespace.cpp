/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    Namespace

\brief    


\date     $Date: 2006/06/14 12:42:35,17 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "Namespace"

#include  <popa7.h>
#include  <sDictionary.hpp>
#include  <sNamespace.hpp>
#include  <sNamespace.hpp>


/******************************************************************************/
/**
\brief  CloseNamespace - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseNamespace"

void Namespace :: CloseNamespace ( )
{
  Namespace        *ns;
  name_spaces.Close();
  while ( ns = children.RemoveTail() )
    delete ns;

  if ( parent )
  {
    if ( dict )
      dict->get_namespace_list().Remove(this);
    parent->get_children().Remove(this);
  }

}

/******************************************************************************/
/**
\brief  Fill - 


\return term - Termination code

\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

logical Namespace :: Fill (PropertyHandle &ph )
{
  logical         term = NO;
BEGINSEQ
if ( dict->get_sys_version() < 18 )                  LEAVESEQ
  if ( parent )
  {
    if ( !ph.IsPositioned() )                          ERROR
    active = ph.IsTrue("active");
    ns_id = active ? ph.GetInt("itype") 
                   : parent->get_ns_id();
    Initialize(ph.GetArea("sys_ident"),parent->get_ns_id());
    name_spaces.Open(&ph,"name_spaces");
//    name_spaces.SetOrder("ik_Ident"); 29.3.06 hat nur noch den
    parent->get_children().AddTail(this);
  }
  else
  {
    DatabaseHandle   dbh(dict);  
    name_spaces.Open(dbh,"SDB_NameSpace",PI_Read);
    ns_id = 0;
    Initialize("__GLOBAL",0);
  }
  
  if ( namespace_id != AUTO )
  {
    if ( active )
      dict->get_namespace_list().Insert(this);
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Find - 


\return ns - 

\param  ns_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Find"

Namespace *Namespace :: Find (char *ns_name )
{
  char                    buffer[ID_SIZE];
  Namespace              *ns = NULL;
BEGINSEQ
  gvtxstb(buffer,ns_name,ID_SIZE);
  
  children.GoTop();
  while( ns = children.GetNext() )
    if ( *ns == buffer )
      break;
 
  if ( !ns ) 
  {
    if ( !name_spaces(ns_name) )                     ERROR
    ns = new Namespace(dict,this,AUTO);
    if ( ns->Fill(name_spaces) )                     ERROR
  }
RECOVER
  delete ns;
  ns = NULL;
ENDSEQ
  return(ns);
}

/******************************************************************************/
/**
\brief  GetNSID - 


\return nsid - 

\param  scope_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNSID"

int32 Namespace :: GetNSID (char *scope_name )
{
  int32                   nsid = AUTO;
  Namespace              *ns = NULL;
BEGINSEQ
  if ( !(ns = Locate(scope_name)) )                  ERROR
 
  nsid = ns->get_ns_id();
RECOVER
  nsid = AUTO;
ENDSEQ
  return(nsid);
}

/******************************************************************************/
/**
\brief  GetScope - 


\return nextpos - 

\param  string - 
\param  rlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetScope"

char *Namespace :: GetScope (char *string, int32 &rlen )
{
  char           workstr[ID_SIZE+1];
  char          *nextpos;
  int16          len;
BEGINSEQ
  if ( parent )
  {
    nextpos = parent->GetScope(string,rlen);
    if ( rlen < 2 )                                  ERROR
    {
      strcpy(nextpos,"::");
      rlen -= 2;
      nextpos += 2;
    }
  }
  else 
    nextpos = string;
    
  gvtxbts(workstr,sys_ident,ID_SIZE);
  len = MIN(strlen(workstr),rlen);
  memcpy(nextpos,workstr,len);
  rlen -= len;
  nextpos += len;
  *nextpos = 0;
  if ( len < strlen(workstr) )                       ERROR

RECOVER
  rlen = AUTO;
ENDSEQ
  return(nextpos);
}

/******************************************************************************/
/**
\brief  GetScopeName - 


\return term - Termination code

\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetScopeName"

logical Namespace :: GetScopeName (NString &nstring )
{
  Namespace              *ns = this;
  logical                 term = NO;
  nstring.Append(sys_ident,ID_SIZE);

  while ( ns = ns->get_parent() )
    if ( ns->get_active() && ns->get_parent() )
      break;

  if ( ns )
  {
    nstring += "::";
    ns->GetScopeName(nstring);
  }

  return(term);
}

/******************************************************************************/
/**
\brief  Locate - 


\return ns - 

\param  scope_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

Namespace *Namespace :: Locate (char *scope_name )
{
  char                   *end = scope_name;
  Namespace              *ns = NULL;
  logical                 repl = NO;
BEGINSEQ
  while ( *end && *end != ':' )
    end++;

  if ( *end )
  {
    *end = 0;
    repl = YES;
  }

  if ( !(ns = Find(scope_name)) )                    ERROR
 
  if ( repl )  // '::' found
  {
    *end = ':';
    repl = NO;
    if ( *(++end) != ':' )                           SDBERR(99)
    ns = Locate(end);
  }


RECOVER
  if ( repl )
    *end = ':';
  ns = NULL;
ENDSEQ
  return(ns);
}

/******************************************************************************/
/**
\brief  Namespace - 



\param  dictptr - Dictionary handle
\param  parent_ns - 
\param  nsid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Namespace"

     Namespace :: Namespace (Dictionary *dictptr, Namespace *parent_ns, int32 nsid )
                     :   parent(parent_ns),
  children(),
  ns_id(nsid),
  dict(dictptr)
{

// Fill() passiert für Dictionary in OpenPIs

}

/******************************************************************************/
/**
\brief  ~Namespace - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~Namespace"

     Namespace :: ~Namespace ( )
{
  Namespace        *ns;
  CloseNamespace();

}


