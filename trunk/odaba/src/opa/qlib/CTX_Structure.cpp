/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    CTX_Structure

\brief    Structure Context
          A  structure context  is created  for each  structure type. It defines
          the  connection  between  the  instance  and the instance description.
          Moreover,  it allows determining the active con-text hierarchy for the
          structure  instance,  i.e.  the  parent property/extent, the structure
          the  parent property  is defined  in, the  parent parent property etc.
          Thus,  the structure context  defines the context  in which the object
          instance has been provided.
          The  parent  context  for  a  structure  context  is always a property
          context.  This  can  be  the  property  context  for  an extent or for
          another property within a structure instance.
          The  structure  context  allows  handling  read and updating events as
          well as creating or deleting events.

\date     $Date: 2006/06/13 22:40:33,35 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CTX_Structure"

#include  <popa7.h>
#include  <cfctp.h>
#include  <coctp.h>
#include  <cHTML_BlockTypes.h>
#include  <cHTML_ReferenceTypes.h>
#include  <sACObject.hpp>
#include  <sCTX_Base.hpp>
#include  <sCTX_Property.hpp>
#include  <sCTX_Structure.hpp>
#include  <sDBStructDef.hpp>
#include  <sPropertyHandle.hpp>
#include  <sSystemStates.hpp>
#include  <sbinti.hpp>
#include  <scfte.hpp>
#include  <sCTX_Structure.hpp>


/******************************************************************************/
/**
\brief  BuildDefaultDescription - 


\return term - Termination code

\param  string_buffer - 
\param  html - HTML option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BuildDefaultDescription"

logical CTX_Structure :: BuildDefaultDescription (bds &string_buffer, logical html )
{
  logical           term = NO;
  BuildDescription(string_buffer,GetPropertyHandle("name.name")->GetString(),'H',1,html);
  BuildDescription(string_buffer,GetPropertyHandle("description.lang_descr.characteristic")->GetString(),'P',0,html);

  return(term);
}

/******************************************************************************/
/**
\brief  BuildDescription - 


\return term - Termination code

\param  string_buffer - 
\param  string - 
\param  ptype - 
\param  plevel - 
\param  html - HTML option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BuildDescription"

logical CTX_Structure :: BuildDescription (bds &string_buffer, char *string, char ptype, int16 plevel, logical html )
{
  int32                    len;
  char                    prefix[65];
  char                    suffix[65];
  char                    presuf[131];
  char                    uline[512];
  char                   *str;
  logical                 term = NO;
BEGINSEQ
  if ( !(len = strlen(string)) )                     ERROR
  
  BuildPrefixSuffix(prefix,suffix,ptype,plevel,html);
  if ( html )
  {
    strcat(strcpy(presuf,suffix),prefix);
    
    string_buffer.Append(prefix);
      
    str = new char[len+1000];
    strcpy(str,string);
    STRExchange(str,"\r\n",presuf,len+1000-1);
    string_buffer.Append(str); 
    delete str;
    
    string_buffer.Append(suffix);
  }
  else
  {
    if ( ptype == 'L' )
    {
      memset(prefix,' ',plevel*3);
      string_buffer.Append(prefix);
      string_buffer.Append("- ");
    }    
    string_buffer.Append(string); 
    if ( ptype == 'H' )
    {
      memset(uline,0,sizeof(uline));
      memset(uline,'-',MIN(len,sizeof(uline)-1));
      string_buffer.Append("\r\n");
      string_buffer.Append(uline);
    }    
    if ( ptype != 'S' )
      string_buffer.Append("\r\n");
  }
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  BuildDescriptionByTemplate - 


\return term - Termination code

\param  templ_pi - Template property handle
\param  string_buffer - 
\param  html - HTML option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BuildDescriptionByTemplate"

logical CTX_Structure :: BuildDescriptionByTemplate (PropertyHandle &templ_pi, bds &string_buffer, logical html )
{
  PropertyHandle   *descriptors;
  int32              indx0 = 0;
  logical           term = NO;
  descriptors = templ_pi.GetPropertyHandle("descriptors");
  while ( descriptors->Get(indx0++) )
    BuildDescriptorText(templ_pi,GetPropertyHandle(),*descriptors,string_buffer,html,NO);

  return(term);
}

/******************************************************************************/
/**
\brief  BuildDescriptorText - 


\return term - Termination code

\param  templ_pi - Template property handle
\param  data_pi - 
\param  descr_pi - 
\param  string_buffer - 
\param  html - HTML option
\param  in_table - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BuildDescriptorText"

logical CTX_Structure :: BuildDescriptorText (PropertyHandle &templ_pi, PropertyHandle *data_pi, PropertyHandle &descr_pi, bds &string_buffer, logical html, logical in_table )
{
  HTML_ReferenceTypes     ref_type = (HTML_ReferenceTypes)descr_pi.GetInt("ref_type");
  HTML_BlockTypes         type = (HTML_BlockTypes)descr_pi.GetInt("type");
  PropertyHandle         *ph = NULL;
  PropertyHandle         *hl_pi = NULL;
  char                    prefix[65];
  char                    suffix[65];
  char                   *source;
  int32                    indx0 = 0;
  logical                 first;
  logical                 cur_inst = NO;
  logical                 close_td = NO;
  logical                 reference = NO;
  logical                 term = NO;

  if ( in_table )
  {
    if ( html && (type == HBT_Table || !descr_pi.GetPropertyHandle("sub_descriptors")->GetCount()) )
    {
      string_buffer.Append("<TD>");
      close_td = YES;
    }
    else
      string_buffer.Append("\t");
  }
  
  if ( html && type == HBT_Table )
  {
    string_buffer.Append("<TABLE WIDTH=75% BORDER=");
    string_buffer.Append(descr_pi.GetString("level"));
    string_buffer.Append(" CELLSPACING=2 CELLPADDING=2>");
    string_buffer.Append("<TR>");
    in_table = YES;
  }
  
  if ( html && type == HBT_List )
  {
    string_buffer.Append("<L");
    string_buffer.Append(descr_pi.GetString("level"));
    string_buffer.Append(">");
    string_buffer.Append("<LI>");
    in_table = YES;
  }
  
  hl_pi = descr_pi.GetPropertyHandle("head_line");
  if ( hl_pi->Get(FIRST_INSTANCE) )
  {
    BuildDescriptorText(templ_pi,data_pi,*hl_pi,string_buffer,html,in_table);
    string_buffer.Append("</TR><TR>");
  } 
    
  if ( html && (reference = !descr_pi.GetPropertyHandle("reference")->IsEmpty()) )
    BuildReference(data_pi,descr_pi,string_buffer,html);
    
  switch ( ref_type )
  {
    case HRT_Constant   : BuildDescription(string_buffer,
                                           descr_pi.GetString("source"),
                                           (char)type,
                                           descr_pi.GetInt("level"),
                                           html);
                          break;
    case HRT_Template   : BuildTemplate(data_pi,
                                        descr_pi,
                                        string_buffer,
                                        html);
                          break;
    case HRT_Expression : CTXSET(99) // ph = expression
                          break;
    case HRT_Reference  : source = descr_pi.GetString("source");
                          if ( *source == '*' )
                          {
                            ph = data_pi;
                            cur_inst = YES;
                            if ( *(source+1) > ' ' )
                              ph = data_pi->GetPropertyHandle(source+1);
                          }
                          else if ( !*source )
                            ph = data_pi;
                          else
                            ph = data_pi->GetPropertyHandle(source);
                          break;
    default             : ;
  }
   
  if ( ph )
  {
    BuildPrefixSuffix(prefix,suffix,(char)type,descr_pi.GetInt("level"),html);
    string_buffer.Append(prefix);
    if ( cur_inst || !ph->IsCollection() )
      BuildInstanceText(templ_pi,ph,descr_pi,string_buffer,html,in_table);
    else
    {
      ph->ToTop();
      first = YES;
      while ( ph->Get(indx0++) )
      {
        if ( !first && html )
        {
          if ( type == HBT_Table )
            string_buffer.Append("</TR><TR>");
          if ( type == HBT_List )
            string_buffer.Append("</LI><LI>");
        }
        BuildInstanceText(templ_pi,ph,descr_pi,string_buffer,html,in_table);
        first = NO;
      }
    }
    string_buffer.Append(suffix);
  }
  
  if ( html && ( reference || type == HBT_Reference ) )
    string_buffer.Append("</A>");

  if ( html )
  {
    if ( type == HBT_Table )
    string_buffer.Append("</TR></TABLE>");
    if ( type == HBT_List )
      string_buffer.Append("</LI>");
  }
  else if ( html && close_td )
    string_buffer.Append("</TD>");

  return(term);
}

/******************************************************************************/
/**
\brief  BuildInstanceText - 


\return term - Termination code

\param  templ_pi - Template property handle
\param  data_pi - 
\param  descr_pi - 
\param  string_buffer - 
\param  html - HTML option
\param  in_table - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BuildInstanceText"

logical CTX_Structure :: BuildInstanceText (PropertyHandle &templ_pi, PropertyHandle *data_pi, PropertyHandle &descr_pi, bds &string_buffer, logical html, logical in_table )
{
  PropertyHandle         *sub_descriptors = descr_pi.GetPropertyHandle("sub_descriptors");
  int32                    indx0 = 0;
  logical                 term = NO;
  if ( sub_descriptors->GetCount() > 0 )
  {
    sub_descriptors = descr_pi.GetPropertyHandle("sub_descriptors");
    while ( sub_descriptors->Get(indx0++) )
      BuildDescriptorText(templ_pi,data_pi,*sub_descriptors,string_buffer,html,in_table);
  }
  else
    BuildDescription(string_buffer,data_pi->GetString(),(char)descr_pi.GetInt("type"),
                     descr_pi.GetInt("level"),html);

  return(term);
}

/******************************************************************************/
/**
\brief  BuildObjDescription - Create an object description
        The  function provides a html or  simple text description for the object
        that  is constructed according to a  defined template that describes the
        elements to be included into the object.

\return term - Termination code

\param  templ_pi - Template property handle
\param  html - HTML option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BuildObjDescription"

logical CTX_Structure :: BuildObjDescription (PropertyHandle &templ_pi, logical html )
{
  PropertyHandle   *prop_hdl = GetPropertyHandle();
  bds               string;
  DatabaseHandle    db_handle;
  logical           term = NO;
  InitDescription(templ_pi,string,html);
  if ( !templ_pi.Exist() )
    BuildDefaultDescription(string,html);
  else
    BuildDescriptionByTemplate(templ_pi,string,html);
  TermDescription(string,html);

  prop_hdl->SetActionResult(string.GetArea());
  return(term);
}

/******************************************************************************/
/**
\brief  BuildPrefixSuffix - 


\return term - Termination code

\param  prefix - 
\param  suffix - 
\param  ptype - 
\param  plevel - 
\param  html - HTML option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BuildPrefixSuffix"

logical CTX_Structure :: BuildPrefixSuffix (char *prefix, char *suffix, char ptype, int16 plevel, logical html )
{
  logical                 term = NO;
  memset(prefix,0,65);
  memset(suffix,0,65);
  if ( html )
  {
    if ( ptype == 'R' )
    {
      strcpy(prefix,"<A HREF=");
      strcpy(suffix,">");
    }    
    else if ( ptype != 'T' && ptype != 'S' && ptype != 'L' )
    {
      prefix[0] = '<';
      prefix[1] = ptype;
      if ( plevel > 0 )
        gvtxitoa(plevel,prefix+2,10);
    
      strcat(prefix,">");
      if ( ptype != 'H' )
      {
        strcat(suffix,"</P>");
        strcat(prefix,"<P>");
      }
      strcat(suffix,"</");
      strcat(suffix,prefix+1);
    }    
  }
  return(term);
}

/******************************************************************************/
/**
\brief  BuildReference - 


\return term - Termination code

\param  data_pi - 
\param  descr_pi - 
\param  string_buffer - 
\param  html - HTML option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BuildReference"

logical CTX_Structure :: BuildReference (PropertyHandle *data_pi, PropertyHandle &descr_pi, bds &string_buffer, logical html )
{
  HTML_BlockTypes         type = (HTML_BlockTypes)descr_pi.GetInt("type");
  PropertyHandle         *ph = NULL;
  char                    temp_string[1001];
  char                    source[256];
  char                   *pos1;
  char                   *pos2;
  char                   *data_str;
  logical                 term = NO;

  strcpy(temp_string,descr_pi.GetString("reference"));
  while ( (pos1 = strchr(temp_string,'%')) && (pos2 = strchr(pos1+1,'%')) )
  {
    memcpy(source,pos1,(pos2-pos1)+1);
    *(source+(pos2-pos1)) = 0;
    data_str = data_pi->GetString(source+1);
    strcat(source,"%");
    STRExchange(temp_string,source,data_str,sizeof(temp_string)-1);
  }

  BuildDescription(string_buffer,temp_string,'R',0,html);

  return(term);
}

/******************************************************************************/
/**
\brief  BuildTemplate - 


\return term - Termination code

\param  data_pi - 
\param  descr_pi - 
\param  string_buffer - 
\param  html - HTML option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BuildTemplate"

logical CTX_Structure :: BuildTemplate (PropertyHandle *data_pi, PropertyHandle &descr_pi, bds &string_buffer, logical html )
{
  HTML_BlockTypes         type = (HTML_BlockTypes)descr_pi.GetInt("type");
  PropertyHandle         *ph = NULL;
  char                    temp_string[1001];
  char                    source[256];
  char                   *pos1;
  char                   *pos2;
  char                   *data_str;
  logical                 term = NO;

  strcpy(temp_string,descr_pi.GetString("source"));
  while ( (pos1 = strchr(temp_string,'%')) && (pos2 = strchr(pos1+1,'%')) )
  {
    memcpy(source,pos1,(pos2-pos1)+1);
    *(source+(pos2-pos1)) = 0;
    data_str = data_pi->GetString(source+1);
    strcat(source,"%");
    STRExchange(temp_string,source,data_str,sizeof(temp_string)-1);
  }

  BuildDescription(string_buffer,temp_string,(char)type,descr_pi.GetInt("level"),html);

  return(term);
}

/******************************************************************************/
/**
\brief  CTX_Structure - Structure context constructor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CTX_Structure"

     CTX_Structure :: CTX_Structure ( )
                     : CTX_DBBase (),
  int_instance(NULL),
  old_instance(NULL),
  ref_context(NULL)
{

  intern_states.display_state = DSP_Visible;

}

/******************************************************************************/
/**
\brief  CopyTo - Duplicate instance
        The  function duplicates an existing instance. Since specific copy rules
        must  be implemented in several cases  an overloaded specific action can
        be  defined in  derived context  classes. The  function is not a virtual
        function  and must  be implemented  as an  action that can be called via
        the executeFunction function

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyTo"

logical CTX_Structure :: CopyTo ( )
{
  PropertyHandle  *source = GetPropertyHandle();
  DBObjectHandle   dbohdl(source->GetObjectHandle());
  int16            ta_level = 0;
  logical          term = NO;
BEGINSEQ
  CTXSETEV1(Parm(1),UNDEF)
  source = GetPropertyHandle();
  if ( !source->IsServer() )                         LEAVESEQ
  
  if ( !Parm(1) )                                    SDBERR(359)

  if ( !source->Exist() )                            SDBERR(360)
  ta_level = dbohdl.BeginTransaction();
  
  PropertyHandle  target(*source);
  Key             sortkey(source->StringToKey(Parm(1)));
  if ( target.GetGlobalID(sortkey) > 0  ||
       target.Get(sortkey)                 )         CTXERR(361)
  if ( !target.Copy(*source,sortkey,REPL_local) )    ERROR

RECOVER
  if ( ta_level )
    dbohdl.RollBack(ta_level);
  ta_level = 0;
  term = YES;
ENDSEQ
  if ( ta_level )
    dbohdl.CommitTransaction(ta_level);
  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteFunction - 


\return term - Termination code

\param  fname - 
\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical CTX_Structure :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("CopyTo",ALINK(this,CTX_Structure,CopyTo)),
                         };
  static srt  cftesrt(sizeof(acttbl)/CFTE,CFTE,UNDEF,UNDEF,UNDEF,(char *)acttbl,NO);

  if ( !cftesrt.srtkln() )
    cftesrt.srtsor(CFTE_KPS,CFTE_KLN,CFTE_KTP);

  if ( cfteptr = (cfte *)cftesrt.srtigt(cftesrt.srtssr(gvtxstb(actname,fname,ID_SIZE))) )
  {
    if ( chk_opt )                                   LEAVESEQ
    term = cfteptr->ActionCall(this);
  }
  else
    term = CTX_DBBase::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetCollection - 


\return property_handle - 
/******************************************************************************/
/**
\brief  i0 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCollection"

PropertyHandle *CTX_Structure :: GetCollection ( )
{
  PropertyHandle *pmemptr = NULL;

  return(pmemptr);
}

/******************************************************************************/
/**
\brief  GetConnectionClient - 


\return client - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetConnectionClient"

ODABAClient CTX_Structure :: GetConnectionClient ( )
{

  return (   this 
           ? ((CTX_Property *)HighDBContext(CTXT_Property))->GetConnectionClient()
           : GetMainClient() );

}

/******************************************************************************/
/**
\brief  GetContextType - Get Context type
        The function returns the specific context type as CTX_Structure.

\return ctxtype - Context type

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetContextType"

CTX_Types CTX_Structure :: GetContextType ( )
{


  return(CTXT_Structure);
}

/******************************************************************************/
/**
\brief  GetDBField - 


\return property_hdl - 

\param  fldname_w - Property name or path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBField"

PropertyHandle CTX_Structure :: GetDBField (char *fldname_w )
{
  PropertyHandle    *property_handle = NULL;

  property_handle = GetPropertyHandle(fldname_w);
    

  return(property_handle ? property_handle->get_nodeptr() 
                         : (node *)NULL);
}

/******************************************************************************/
/**
\brief  GetInstContext - Get Instance context
        The  function returns the  structure context for  the instance that owns
        the  current property (high  structure). This is  not identical with the
        structure  that owns the  property. The instance  owning the property is
        the  instance that is  stored in the  database. Hence, the function goes
        up  in the context  hirarchy until it  finds the context that referst to
        the instance stored in the database.

\return strctx - Structure Context

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstContext"

CTX_Structure *CTX_Structure :: GetInstContext ( )
{
  CTX_Structure *high_str_ctx;
  CTX_Structure *strctx        = this;

BEGINSEQ
  if ( !high_ctx )                                   LEAVESEQ
  
  if ( !(high_str_ctx = (CTX_Structure *)high_ctx->HighContext()) )
                                                     LEAVESEQ
  if ( high_str_ctx->GetPropertyHandle()->IsCollection() )
                                                     LEAVESEQ
  strctx = high_str_ctx->GetInstContext();

ENDSEQ
  return(strctx);
}

/******************************************************************************/
/**
\brief  GetInstance - Get instance
        The function returns the instance for the  context.

\return instance - Instance handle
/******************************************************************************/
/**
\brief  i0 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstance"

Instance CTX_Structure :: GetInstance ( )
{

  return ( GetPropertyHandle()->Get() );

}

/******************************************************************************/
/**
\brief  GetKey - Get Key value
        This  function  can  be  called  when  an  instance  is  selected in the
        property   handle   (PropertyHandle::IsSelected()   )   or   in   the  
        DBBeforeRead()  event  handler.  The  function  returns  the key for the
        selcted  instance in the internal key  structure, when the collection is
        ordered  or an empty key instance, when the collection is not ordered or
        no instance is selected in the collection.

\return keyptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKey"

char *CTX_Structure :: GetKey ( )
{

  return ( GetPropertyHandle()->GetSelectedKey() );

}

/******************************************************************************/
/**
\brief  GetOldField - Provide property handle for old instance
        The  function  returns  a  froperty  handle  for  the  old  instance (as
        currently stored in the database, -> GetOldInstance()).

\return property_hdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOldField"

PropertyHandle CTX_Structure :: GetOldField ( )
{
  PropertyHandle      dbfld;
  fmcb               *fmcbptr;
  int8                max_aligned = 1;
  if ( old_instance && int_instance )
  {
    dbfld.Open();
    dbfld.CopyDescription(int_instance->get_field_def());
    fmcbptr = dbfld.GetDescription();
    if ( fmcbptr->fmcbrlev == R_REFR )
    {
      fmcbptr->fmcbrlev = R_DIRECT;
      fmcbptr->fmcbdim  = 1;
      if ( fmcbptr->fmcbityp != T_MEMO && fmcbptr->fmcbityp != T_BLOB )
        fmcbptr->fmcbesu(int_instance->get_struct_def(),fmcbptr->fmcbposn,DEFAULT_ALLIGNMENT,max_aligned);
    }  
    dbfld.SetArea(old_instance);
  }
  return(&dbfld);
}

/******************************************************************************/
/**
\brief  GetOldInstance - Get old instance
        The  function returns the "old instance" state  as it is stored still in
        the  database.  This  allows  comparing  old  and  new values within the
        DBModify() or DBStore() handler.

\return oldinst - 
/******************************************************************************/
/**
\brief  i0 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOldInstance"

char *CTX_Structure :: GetOldInstance ( )
{

  old_instance = NULL;
  
  if ( int_instance )
    old_instance = int_instance->GetOldInst(NULL);
  return(old_instance);
}

/******************************************************************************/
/**
\brief  GetPropContext - Get Property context
        The  function returns  the property  context for  the property passed as
        name  or  property  path.  The  property  is  searched  in the structure
        associated with the context.

\return propctx - 

\param  w_fldnames - Property name or path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropContext"

CTX_Property *CTX_Structure :: GetPropContext (char *w_fldnames )
{

  return ( int_instance ? 
           int_instance->GetPropNode(w_fldnames,(CTX_Property *)high_ctx)->GetContext() : 
           NULL );


}

/******************************************************************************/
/**
\brief  GetPropertyHandle - Get Property handle
        The  function returns the property  handle associated for the structure.
        When  a  property  name  or  path is passed to the function the property
        handle  is searched in  the structure. When  no property name or path is
        passed the property handle the structure belongs to is returned.

\return property_handle - 

\param  fldname_w - Property name or path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropertyHandle"

PropertyHandle *CTX_Structure :: GetPropertyHandle (char *fldname_w )
{
  CTX_Property   *propctx = (CTX_Property *)HighDBContext(CTXT_Property);

  return ( propctx ? propctx->GetPropertyHandle(fldname_w) : NULL );

}

/******************************************************************************/
/**
\brief  GetReadOnly - Is context set to read-only?
        The  function returns whether the context  has been set to read-only (->
        SetReadOnly()).

\return dspstate - Data state

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetReadOnly"

CTX_DisplayState CTX_Structure :: GetReadOnly ( )
{


  return( this ? intern_states.display_state : DSP_undefined );
}

/******************************************************************************/
/**
\brief  GetRefContext - Get referenced context
        Some  functions as Copy  are setting a  reference context. The reference
        context  can be set also  explicitly using the SetRefContext() function.
        The  function  returns  the  reference  context  when  it is set or NULL
        otherwise.

\return strctx - Structure Context

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRefContext"

CTX_Structure *CTX_Structure :: GetRefContext ( )
{

  return(ref_context);

}

/******************************************************************************/
/**
\brief  GetResourceName - Get resource name
        The  function  returns  the  structure name as context specific resource
        name.

\return resname - Resource name

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetResourceName"

char *CTX_Structure :: GetResourceName ( )
{
  char      *resname;
  return (   int_instance && int_instance->get_field_def()->fmcbsmcb
           ? int_instance->get_field_def()->fmcbsmcb->smcbname
           : NULL );
  return(resname);
}

/******************************************************************************/
/**
\brief  GetSourceField - Get source field
        Some  functions as Copy  are setting the  property handle for the source
        during  the action that refers to a source property handle. The function
        returns  the source property handle when it  is set or an empty property
        handle otherwise.

\return property_hdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSourceField"

PropertyHandle CTX_Structure :: GetSourceField ( )
{
  PropertyHandle      dbfld;
  fmcb               *fmcbptr;
  int8                max_aligned = 1;
  inti        *source_instance = ref_context ? ref_context->get_int_instance() : NULL;
  if ( source_instance )
  {
    dbfld.Open();
    dbfld.CopyDescription(source_instance->get_field_def());
    fmcbptr = dbfld.GetDescription();
    if ( fmcbptr->fmcbrlev == R_REFR )
    {
      fmcbptr->fmcbrlev = R_DIRECT;
      fmcbptr->fmcbdim  = 1;
      if ( fmcbptr->fmcbityp != T_MEMO && fmcbptr->fmcbityp != T_BLOB )
        fmcbptr->fmcbesu(source_instance->get_struct_def(),fmcbptr->fmcbposn,DEFAULT_ALLIGNMENT,max_aligned);
    }  
    dbfld.SetArea(source_instance->get_iselarea());
  }
  return(dbfld);
}

/******************************************************************************/
/**
\brief  GetStructContext - Get Structure context


\return strctx - Structure Context

\param  w_strnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStructContext"

CTX_Structure *CTX_Structure :: GetStructContext (char *w_strnames )
{
  CTX_Structure          *strctx = NULL;

  return(strctx);
}

/******************************************************************************/
/**
\brief  HideInstance - Hide instance
        The  function  can  be  used  in  the  structure  context  to exclude an
        instance  from being  selected in  any property handle. Hidden instances
        will  return NO  when trying  to lacate  such an instance using Get() or
        another  function to  locate the  instance. Position()  (or the ++ or --
        operator) will skip hidden instances.
        The  state is typically  set in the  DBRead() handler. When resetting or
        changing   the   selection   in   the   property   handle   the state is
        automatically  reset.  You  may,  however,  reset  the state explicitely
        using the ShowInstance() context function.
        The  function returns  the 'hidden'  state as  it was set before calling
        the function.

\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HideInstance"

logical CTX_Structure :: HideInstance ( )
{
  logical                 cond = IsHidden();
  intern_states.display_state = DSP_Hidden;
  return(cond);
}

/******************************************************************************/
/**
\brief  InitDescription - 


\return term - Termination code

\param  templ_pi - Template property handle
\param  string_buffer - 
\param  html - HTML option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitDescription"

logical CTX_Structure :: InitDescription (PropertyHandle &templ_pi, bds &string_buffer, logical html )
{
  logical                 term = NO;
  string_buffer.bdsaloc(8000);
  if ( html )
  {
    string_buffer.Append("<html><head><title>Generated ComeIn Page</title>");
      
    PropertyHandle  *style_sheet = templ_pi.GetPropertyHandle("style_sheet");
    if ( !style_sheet->IsEmpty() )
    {
      string_buffer.Append("<link rel=\"stylesheet\" href=");
      string_buffer.Append(style_sheet->GetString());
      string_buffer.Append(">");
    }
    string_buffer.Append("</head><body>");
  }
  
  

  return(term);
}

/******************************************************************************/
/**
\brief  Initialize - 



\param  bintiptr - 
\param  highctx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void CTX_Structure :: Initialize (binti *bintiptr, CTX_Base *highctx )
{

  CTX_DBBase::Initialize(bintiptr->get_struct_def()->get_resource(),highctx);
  int_instance = bintiptr;

  if ( highctx && ((CTX_Property *)highctx)->IsReadOnly() )
    intern_states.display_state = DSP_undefined;

}

/******************************************************************************/
/**
\brief  IsEdit - Can data be updated
        The  function  checks  whether  data  can  be  updated  in  the instance
        selected for the property handle.

\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEdit"

logical CTX_Structure :: IsEdit ( )
{

  return ( HighDBContext()->IsEdit() );

}

/******************************************************************************/
/**
\brief  IsHidden - Is instance hidden
        Hidden  instances  are  not  selected  when attempting to read them. The
        state  can be set using the structure context function HideInstance() in
        a  derived  structure  context.  The  function  returns  YES,  when  the
        instance is hidden and NO otherwise.

\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsHidden"

logical CTX_Structure :: IsHidden ( )
{

  return(intern_states.display_state == DSP_Hidden ? YES : NO);

}

/******************************************************************************/
/**
\brief  IsReadOnly - Has instance been set to read-only
        The  function  returns  whether  the  read-only  state  is  set  for the
        instance in the property handle (-> SetReadOnly()).

\return readonly - Read-only state

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsReadOnly"

logical CTX_Structure :: IsReadOnly ( )
{


  return( this ? intern_states.display_state != DSP_Visible : NO);
}

/******************************************************************************/
/**
\brief  SetKey - Set key in instance area
        This  function  can  be  called  when  an  instance  is  selected in the
        property  handle (PropertyHandle::IsSelected()) or in the DBBeforeRead()
        event  handler. The function moves the key to the property instance area
        for  the key components.  The function returns  an error (YES), when the
        collection  is  not  ordered  or  when  no  instance  is selected in the
        collection.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetKey"

logical CTX_Structure :: SetKey ( )
{

  return ( GetPropertyHandle()->GetSelectedKey() ? YES : NO );

}

/******************************************************************************/
/**
\brief  SetReadOnly - Set instance to read-only
        The  function allows protecting an instance from being updated or remove
        the  write  protection.  The  function  can  be  called  from within any
        structure  context function or in relation with a structure context. The
        function  will  protect  the  current property handle and all subsequent
        handles,  i.e. it works recursively.  When resetting the read-only state
        the  function will not reset subsequent  property handles that have been
        set  explicitly to read-only. Setting the read-only state for a property
        handle  has the consequence that not  only all subordinated instaces are
        locked  for writing but all subordinated  collections as well, i.e. that
        the  application  cannot  add  or  delete  instances  from  subordinated
        property handles.
        The  read-only state is set for  the property handle, i.e. after setting
        the  read only state all instances  selected for the property handle are
        read-only until the state is reset by another context function call.
        The function returns the current state for the property handle. 
        When  changing the instance state for a property handle this will affect
        the  write permission only, when being  set before selecting an instance
        in  the  Property  handle.  To  activate  the  state  for  the  instance
        currently  selected  the  instance  can  be  re-selected (e.g. using {.r
        PropertyHandle.Reset}()).  Resetting the read-only state will not affect
        instances  that  are  write  protected  for  other reasons and instances
        selected  in other property handles, which  have been set explicitely to
        'read only' by the application.

\return readonly - Read-only state

\param  readonly - Read-only state
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReadOnly"

logical CTX_Structure :: SetReadOnly (logical readonly )
{
  logical        oldstate = IsReadOnly();
BEGINSEQ
  if ( !this )                                       LEAVESEQ
  switch ( readonly )
  {
    case NO  : if ( intern_states.display_state == DSP_Disabled )
               {
                 intern_states.display_state = DSP_Visible;
                 int_instance->SetReadOnly('R');
               }
    case 'R' : if ( intern_states.display_state == DSP_undefined )
               {
                 intern_states.display_state = DSP_Visible;
                 int_instance->SetReadOnly('R');
               }
               break; 
    case YES : if ( intern_states.display_state != DSP_Disabled )
               {
                 intern_states.display_state = DSP_Disabled;
                 int_instance->SetReadOnly('S');
               }
               break;
    case 'S' : if ( intern_states.display_state == DSP_Visible )
               {
                 intern_states.display_state = DSP_undefined;
                 int_instance->SetReadOnly('S');
               }
  }
ENDSEQ
  return(oldstate);
}

/******************************************************************************/
/**
\brief  SetRefContext - Set reference context
        The  function  allows  setting  a  reference context  as link in another
        context  e.g.  to  link  structure  contexts in a copy process. Only one
        context  can be set  as reference context.  Calling the function several
        times  will overwrite  the reference  context each  time the function is
        called.  When  passing  NULL  as reference context the reference context
        will be reset.

\return term - Termination code

\param  strctx - Structure Context
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetRefContext"

logical CTX_Structure :: SetRefContext (CTX_Structure *strctx )
{

  ref_context = strctx;
  return(NO);
}

/******************************************************************************/
/**
\brief  SetResult - Set Result
        The  function  stores  the  result  of  a context function in the result
        area,   which   can   be   retrieved   in   the   application  using the
        PropertyHandle::GetResult() function.


\param  result_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetResult"

void CTX_Structure :: SetResult (char *result_string )
{

  GetPropertyHandle()->SetActionResult(result_string);

}

/******************************************************************************/
/**
\brief  SetTransactionError - Set Transaction Error
        The  function marks a transaction as  errounus. This leads to a rollback
        of  the transaction when  the transaction is  finished. The function can
        be  called  in  post  handlers  (as  inserted  or  deleted)  to undo the
        performed operation.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTransactionError"

void CTX_Structure :: SetTransactionError ( )
{
  node         *prop_node;
  CTX_Property   *propctx = (CTX_Property *)HighDBContext(CTXT_Property);

BEGINSEQ
  if ( !propctx )                                    ERROR
  prop_node = propctx->get_prop_node();
  if ( !prop_node )                                  ERROR
  
  prop_node->GetObjectHandle()->SetTransactionError();

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ShowInstance - Show instannce
        The  show  instance  function  resets  the hidden state for an instance.
        Usually,  the hidden state is reset automatically, when the selection in
        a property handle is changed.
        The  function returns  the 'hidden'  state as  it was set before calling
        the function.

\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShowInstance"

logical CTX_Structure :: ShowInstance ( )
{
  logical                 cond = IsHidden();
  intern_states.display_state = DSP_Visible;
  return(cond);
}

/******************************************************************************/
/**
\brief  TermDescription - 


\return term - Termination code

\param  string_buffer - 
\param  html - HTML option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TermDescription"

logical CTX_Structure :: TermDescription (bds &string_buffer, logical html )
{
  logical                 term = NO;
  if ( html )
  {
    string_buffer.Append("\r\n</body>\r\n</html> ");
  }
  else
    string_buffer.Append(" ");
  
  *(string_buffer.bdsend()-1) = 0;

  return(term);
}

/******************************************************************************/
/**
\brief  ~CTX_Structure - Destructor
        The  function  destroys  the  structure  context.  The  function must be
        overloaded  in an  application specific  implementation of the structure
        context.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CTX_Structure"

     CTX_Structure :: ~CTX_Structure ( )
{



}


