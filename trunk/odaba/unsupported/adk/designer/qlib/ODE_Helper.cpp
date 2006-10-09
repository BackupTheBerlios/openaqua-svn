/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    ODE_Helper



\date     $Date: 2006/05/23 13:52:49,48 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODE_Helper"

#include  <pdesign.h>
#include  <sBNFData.hpp>
#include  <sODE_Project.hpp>
#include  <sPropertyHandle.hpp>
#include  <igvts.h>
#include  <spc1_ODC_ImpClass.hpp>
#include  <sODE_Helper.hpp>


/******************************************************************************/
/**
\brief  Deinitialize


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deinitialize"

void ODE_Helper :: Deinitialize ( )
{

  dictionary = DictionaryHandle();

}

/******************************************************************************/
/**
\brief  GetAccPathType

\return lph

\param  type_key
\param  bdata
\param  lookup_type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAccPathType"

PropertyHandle *ODE_Helper :: GetAccPathType (TypeKey &type_key, BNFData *bdata, char &lookup_type )
{
  PropertyHandle         *mem_ph    = NULL;
  BNFData                *element   = NULL;
  BNFData                *pext      = NULL;
  BNFData                *pname;
  char                    scope_name[1025];
  char                   *classname = NULL;
  logical                 first     = YES;
  int32                   indx0     = 0;
  int32                   ecnt      = 0;
  int32                   i         = 0;
  PropertyHandle         *lph       = NULL;

BEGINSEQ
// path_element          := path_operand [ operand_list ]
// path_operand          := path_name | coll_operand | expr_code
// path_name             := pname [ name_index ]
// pname                 := oql_oper | scoped_name | db_name | any_type
// scoped_name           := identifier [ scoped_name_ext(*) ]
// scoped_name_ext       := scope_op identifier

  if ( !(lph = projects->GetImplementedClass(type_key)) )
                                                     ERROR
  // bdata is an access_path
  element = bdata->GetElement(indx0++);
  while ( element )
  {
    if ( !(pname = element->GetElement(0)->GetSymbol("path_name")) )
                                                     ERROR
    pname = pname->GetElement(0);
    if ( !(pname = pname->GetSymbol("scoped_name")) )       ERROR
    if ( !pname->IsSymbol("identifier") )
    {
      ecnt = pname->GetElementCount();
      while ( i < ecnt-2 )
      { 
        if ( !first )
          strcat(scope_name,"::");
        first = NO;
        strcat(scope_name,pname->GetElement(i++)->GetElement("identifier")->StringValue());
      }
      classname = pname->GetElement(i)->GetStringValue(NULL,NULL);
      
      type_key.Initialize(dictionary,scope_name,classname);
      if ( !(lph = projects->GetImplementedClass(type_key)) )
                                                      ERROR
      pname = pname->GetElement(ecnt-1)->GetElement("identifier");
    }

    element = NULL;
    if ( pext = bdata->GetElement(indx0++) )
      element = pext->GetElement(1);
    
    switch ( lookup_type )
    {
      case 'C' : type_key.Initialize(dictionary,scope_name,pname->StringValue());
                 lph = projects->GetImplementedClass(type_key);
                 break;
      case 'I' : if ( !element )  // last element
                 {
                   if ( !(lph  = GetMember(lph,pname->StringValue(),'F')) ) 
                                                     ERROR
                   break;
                 }  
      case 'M' : if ( !(lph  = GetMember(lph,pname->StringValue(),'M')) ) 
                                                     ERROR
                 type_key.Initialize(lph->GetString("ddetype"),lph->GetInt("namespace_id"));
                 if ( !(lph = projects->GetImplementedClass(type_key)) )
                                                     ERROR
                 break;
    }
  }

RECOVER
  lph = NULL;
ENDSEQ
  return(lph);
}

/******************************************************************************/
/**
\brief  GetListHandle

\return lph
-------------------------------------------------------------------------------
\brief  i0


\param  type_key
\param  bdata
\param  lookup_type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetListHandle"

PropertyHandle *ODE_Helper :: GetListHandle (TypeKey &type_key, BNFData *bdata, char &lookup_type )
{
  PropertyHandle    *lph = NULL;

BEGINSEQ
  switch ( bdata->GetSymbolCode("access_path","sngl_operand","OQLSelect",
                                "block","constant","sys_variable") )
  {
    case  1 : if ( !(lph = GetAccPathType(type_key,bdata->GetSymbol("access_path"),lookup_type)) )  
                                                     ERROR
              break;
    case  2 : bdata = bdata->GetElement(1); // '(' operand ')'
              if ( !(bdata = bdata->GetSymbol("simple_op")) )
                                                     ERROR
              if ( !(lph = GetListHandle(type_key,bdata,lookup_type)) )
                                                     ERROR
              break;
    default :                                        ERROR
  }

RECOVER
  lph = NULL;
ENDSEQ
  return(lph);
}

/******************************************************************************/
/**
\brief  i01


\param  type_key
\param  accpath
\param  lookup_type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetListHandle"

PropertyHandle *ODE_Helper :: GetListHandle (TypeKey &type_key, char *accpath, char &lookup_type )
{
  BNFData                *bdata = NULL;
  PropertyHandle         *lph   = NULL;
BEGINSEQ
  if ( !(bdata = dictionary.ParseExpression(accpath,"simple_op")) )
                                                     ERROR
  if ( !(lph = GetListHandle(type_key,bdata,lookup_type)) )
                                                     ERROR
RECOVER
  lph = NULL;
ENDSEQ
  return(lph);
}

/******************************************************************************/
/**
\brief  GetMember

\return mph

\param  class_ph
\param  memnames
\param  search_type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMember"

PropertyHandle *ODE_Helper :: GetMember (PropertyHandle *class_ph, char *memnames, char search_type )
{
  PropertyHandle       *base_ph = NULL;
  int32                 indx0   = 0;
  PropertyHandle       *mph     = NULL;
  TypeKey               type_key;

BEGINSEQ
  pc1_ODC_ImpClass    pc_imp(class_ph);

  if ( mph = pc_imp.GetMember(memnames,search_type)) LEAVESEQ

  if ( class_ph->GPH("smcebase")->GetCount() > 0 )
  {
    PropertyHandle copy_pc(*class_ph);
    base_ph = copy_pc.GPH("smcebase");  
    while ( base_ph->Get(indx0++) )
    {
      type_key.Initialize(base_ph->GetString("ddetype"),base_ph->GetInt("namespace_id"));
      if ( class_ph = projects->GetImplementedClass(type_key) )
        if ( mph = GetMember(class_ph,memnames,search_type) ) 
                                                     LEAVESEQ
    }
  }
ENDSEQ
  return(mph);
}

/******************************************************************************/
/**
\brief  GetPath

\return accpath

\param  codestring
\param  textpos
\param  lookup_type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPath"

char *__cdecl ODE_Helper :: GetPath (char *codestring, int32 textpos, char &lookup_type )
{
  char            *accpath = NULL;
  int32            pos     = UNDEF;
  int32            end     = textpos;
  logical         stop_before_name = NO;
  char            *spos    = UNDEF;
BEGINSEQ
  lookup_type = 'M';
  if ( codestring[textpos-1] == '(' )
    lookup_type = 'I';
    
  if ( codestring[textpos-1] == '.' || codestring[textpos-1] == '(')
    end--;
  else if ( codestring[textpos-1] == '>' )   // ->
    end -= 2;
  else if ( codestring[textpos-1] == ':' )
  {
    end -= 2;
    lookup_type = 'C';
    stop_before_name = YES;
  }
  if ( end <= 0 )                                ERROR
    
  pos = end;
  while ( --pos )
  {
    if ( !memcmp(codestring+pos-1,"->",2) || codestring[pos] == '.')
    {
      if ( stop_before_name )
      {
        pos++;
        break;
      }
      if ( codestring[pos] == '>' ) 
        --pos;
    }
    else if ( !memcmp(codestring+pos-1,"::",2) ) // scope operator
    {
      --pos;
      stop_before_name = YES;
    }
    else if ( strchr(" -+*/%!^&|=<>(:?;,",codestring[pos]) ) // terminator found
    {
      pos++;
      break;
    }
    else if ( codestring[pos] == ')' || codestring[pos] == ']' || codestring[pos] == '}')
    {
      if ( !(spos = gvtsfbpb(codestring+pos+1,pos)) ) ERROR
      pos = spos-codestring;
    }
  }
  if ( pos <= 0 )                                    ERROR
  
  accpath = (char *)malloc((end-pos)+1);
  memcpy(accpath,codestring+pos,end-pos);
  accpath[end-pos] = 0;
RECOVER
  if ( accpath )
    free(accpath);
  accpath = NULL;
ENDSEQ
  return(accpath);

}

/******************************************************************************/
/**
\brief  GetTargetClass

\return impcls_ph

\param  type_key
\param  accpath
\param  lookup_type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTargetClass"

PropertyHandle *ODE_Helper :: GetTargetClass (TypeKey &type_key, char *accpath, char &lookup_type )
{
  PropertyHandle         *impcls_ph = NULL;
BEGINSEQ
  if ( lookup_type == 'I' )                          ERROR
  
  if ( !(impcls_ph = GetListHandle(type_key,accpath,lookup_type)) )
                                                     ERROR
RECOVER
  impcls_ph = NULL;
ENDSEQ
  return(impcls_ph);
}

/******************************************************************************/
/**
\brief  GetTargetFunction

\return funct_ph

\param  type_key
\param  accpath
\param  lookup_type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTargetFunction"

PropertyHandle *ODE_Helper :: GetTargetFunction (TypeKey &type_key, char *accpath, char &lookup_type )
{
  PropertyHandle         *funct_ph  = NULL;
BEGINSEQ
  if ( !accpath || !*accpath || lookup_type != 'I' ) ERROR
  
  if ( !(funct_ph = GetListHandle(type_key,accpath,lookup_type)) )
                                                     ERROR
RECOVER
  funct_ph = NULL;
ENDSEQ
  return(funct_ph);
}

/******************************************************************************/
/**
\brief  Initialize

\return term - 
-------------------------------------------------------------------------------
\brief  i0


\param  dict_handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical ODE_Helper :: Initialize (DictionaryHandle &dict_handle )
{

  dictionary = dict_handle;
  return(NO);
}

/******************************************************************************/
/**
\brief  i01


\param  ode_project
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical ODE_Helper :: Initialize (ODE_Project *ode_project )
{
  projects   = ode_project;
  dictionary = ode_project->get_db_handle().GetDictionary();
  return(NO);
}

/******************************************************************************/
/**
\brief  ODE_Helper


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODE_Helper"

     ODE_Helper :: ODE_Helper ( )
                     :   dictionary(),
  projects(NULL)
{
}

/******************************************************************************/
/**
\brief  ~ODE_Helper


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODE_Helper"

     ODE_Helper :: ~ODE_Helper ( )
{
}


