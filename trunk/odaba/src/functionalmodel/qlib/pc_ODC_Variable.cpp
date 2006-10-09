/********************************* Class Source Code ***************************/
/**
\package  FunctionalModel
\class    pc_ODC_Variable



\date     $Date: 2006/04/28 11:15:53,90 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ODC_Variable"

#include  <pfmodel.h>
#include  <sPropertyHandle.hpp>
#include  <spc_ODC_Variable.hpp>


/******************************************************************************/
/**
\brief  DataTypeCString

\return string

\param  nstring
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DataTypeCString"

char *pc_ODC_Variable :: DataTypeCString (NString &nstring )
{
  PropertyHandle   *ddetype   = GPH("ddetype");
  char             *save_type = NULL;
  logical           term      = NO;
BEGINSEQ
  if ( GPH("const_val")->IsTrue() )
  {
    nstring += "const";
    nstring.Append(' ');
  }

  if ( TestSysVariable("C_INTERFACE","Y") )
  {
    PropertyHandle   inst_coll(GetDBHandle(),"InstCollection",PI_Read);
                                                    SDBCERR
	PropertyHandle phCInterface("CInterface");
    if ( !inst_coll(phCInterface) ) SDBERR(99)

    if ( inst_coll.GPH("collection")->Get(*ddetype) )
    {
      save_type = strdup(ddetype->GetString());
      ddetype->SetValue("void",NO);
    }
  } 
  
  pc_SDB_Member::DataTypeCString(nstring,NO);
RECOVER

ENDSEQ
  if ( save_type )
  {
    ddetype->SetValue(save_type,NO);
    free(save_type);
  }
  return(nstring);
}

/******************************************************************************/
/**
\brief  Fill

\return term

\param  propnames
\param  proptypes
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

logical pc_ODC_Variable :: Fill (char *propnames, char *proptypes )
{
  PropertyHandle   *sys_ident       = GPH("sys_ident");
  PropertyHandle   *ddetype         = GPH("ddetype");
  PropertyHandle   *reference_level = GPH("reference_level");
  logical           term            = NO;
BEGINSEQ
  if ( pc_SDB_Member::Fill(propnames,proptypes) )   ERROR

  if ( (*ddetype == "CHAR" || *ddetype == "STRING") &&
       *reference_level == "RL_direct"                 )
    *reference_level = "RL_1";
    
  if ( strstr(sys_ident->GetString(),"_ref") )
    *reference_level = "RL_reference";

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetCastType

\return string

\param  nstring
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCastType"

char *pc_ODC_Variable :: GetCastType (NString &nstring )
{

  nstring += "(";
  DataTypeCString(nstring);
  nstring += ")";
  return(nstring);
}

/******************************************************************************/
/**
\brief  GetParmCallList

\return string

\param  nstring
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParmCallList"

char *pc_ODC_Variable :: GetParmCallList (NString &nstring )
{
  PropertyHandle  *sys_ident = GPH("sys_ident");
  int32            curidx    = GetCurrentIndex();
  int32            indx0     = 0;
  logical          started   = StartRTA() ? YES : NO;
  logical          first     = YES;

  while ( Get(indx0++) )
  {
    if ( first )
      first = NO;
    else
      nstring += ",";
    nstring += sys_ident->GetString();
  }

  if ( curidx != AUTO )
    Get(curidx);
  StopRTA(started);
  return(nstring);
}

/******************************************************************************/
/**
\brief  GetParmList

\return string

\param  nstring
\param  com_opt
\param  prototyp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParmList"

char *pc_ODC_Variable :: GetParmList (NString &nstring, logical com_opt, logical prototyp )
{
  int32     curidx  = GetCurrentIndex();
  int32     indx0   = 0;
  logical   started = StartRTA() ? YES : NO;
  logical   first   = YES;

  if ( !com_opt && TestSysVariable("C_INTERFACE","Y") )
  {
    nstring += "void * object_handle";
    first    = NO;
  }

  while ( Get(indx0++) )
  {
    if ( first )
      first = NO;
    else
      nstring.Append(", ");
    if ( com_opt )
      ParmTypeCOMString(nstring,prototyp,NO);
    else
      ParmTypeCString(nstring,prototyp);
  }

  if ( curidx != AUTO )
    Get(curidx);
  StopRTA(started);
  return(nstring);
}

/******************************************************************************/
/**
\brief  ParmTypeCOMString

\return string

\param  nstring
\param  prototyp
\param  retvar_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ParmTypeCOMString"

char *pc_ODC_Variable :: ParmTypeCOMString (NString &nstring, logical prototyp, logical retvar_opt )
{
  PropertyHandle   *initialize = GPH("initialize");
  PropertyHandle   *ddeinit    = GPH("ddeinit");
  PropertyHandle   *external   = GPH("external");
  char             *str        = "";
  if ( !prototyp )
    nstring += "/*"; //*/ syntax highlight patch
  nstring += "[";

  nstring += (char*)(retvar_opt         ? "out, retval" :
                     external->IsTrue() ? "in,out" 
                                        : "in");
  
  if ( !retvar_opt && initialize->IsTrue() )
  {
    nstring += ",optional";
    if ( !ddeinit->IsEmpty() )
    {
      if ( *ddeinit == "AUTO" )
        str ="odaba_AUTO";
      else if ( *ddeinit == "YES" )
        str = "ogcYES";
      else if ( *ddeinit == "NO" )
        str = "ogcNO";
      else 
        str = ddeinit->GetString();
        
      nstring += ",defaultvalue(";
      nstring += str;
      nstring += ")";
    }
  }  
  
  nstring += "]";
  if ( !prototyp )
    nstring += "*/";
  
  pc_SDB_Member::DataTypeCOMString(nstring,retvar_opt);

  return(nstring);
}

/******************************************************************************/
/**
\brief  ParmTypeCString

\return string

\param  nstring
\param  prototyp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ParmTypeCString"

char *pc_ODC_Variable :: ParmTypeCString (NString &nstring, logical prototyp )
{

  DataTypeCString(nstring);

  nstring += GPH("sys_ident")->GetString();

  if ( prototyp && GPH("initialize")->IsTrue() )
  {
    nstring += "=";
    nstring += GPH("ddeinit")->GetString();
  }
  return(nstring);
}

/******************************************************************************/
/**
\brief  pc_ODC_Variable


\param  prophdl
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ODC_Variable"

     pc_ODC_Variable :: pc_ODC_Variable (PropertyHandle *prophdl )
                     : pc_SDB_Member(prophdl)
{
}


