/********************************* Class Source Code ***************************/
/**
\package  OQL - 
\class    CLICollection

\brief    


\date     $Date: 2006/08/28 20:54:23,32 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CLICollection"

#include  <poql.h>
#ifndef   DLL_kcb_HPP
#define   DLL_kcb_HPP
#include  <skcb.hpp>
#include  <sDLL.h>
#endif
#include  <sBNFData.hpp>
#include  <sCLICollection.hpp>
#include  <sCLIDataSource.hpp>
#include  <sCLInterpreterBase.hpp>
#include  <sCLICollection.hpp>


/******************************************************************************/
/**
\brief  CLICollection - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  dsource - 
\param  ds_handle - 
\param  prop_path - Property path
\param  accmode - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CLICollection"

     CLICollection :: CLICollection (CLIDataSource *dsource, DBObjectHandle ds_handle, char *prop_path, PIACC accmode )
                     : PropertyHandle(),
  name(NULL),
  selection(NULL),
  attr_list(),
  attr_count(0),
  data_source(dsource)
{

BEGINSEQ
  if ( Open(ds_handle,prop_path,accmode) )              ERROR
  SetName(prop_path);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i01 - 



\param  dsource - 
\param  prophdl - 
\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CLICollection"

     CLICollection :: CLICollection (CLIDataSource *dsource, PropertyHandle &prophdl, char *prop_path )
                     : PropertyHandle(),
  name(NULL),
  selection(NULL),
  attr_list(),
  attr_count(0),
  data_source(dsource)
{

BEGINSEQ
  if ( !prop_path )
  {
    SetPropertyHandle(prophdl);
    LEAVESEQ
  }
  
  if ( !strcmp(prop_path,"&") )
  {
    if ( CopyHandle(prophdl.GetBaseProperty()) )        ERROR
  }
  else 
    if ( Open(prophdl,prop_path) )                      ERROR
  
  SetName(prop_path);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i02 - 



\param  dsource - 
\param  coll_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CLICollection"

     CLICollection :: CLICollection (CLIDataSource *dsource, CLICollection &coll_ref )
                     : PropertyHandle (),
  name(NULL),
  selection(NULL),
  attr_list(),
  attr_count(0),
  data_source(dsource)
{

BEGINSEQ
  if ( Open(coll_ref) )                         ERROR
  SetName(coll_ref.GetName());

  if ( coll_ref.get_selection() && *coll_ref.get_selection() )
    SetSelection(coll_ref.get_selection());
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i03 - 



\param  dsource - 
\param  names - 
\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CLICollection"

     CLICollection :: CLICollection (CLIDataSource *dsource, char *names, PropertyHandle &prophdl )
                     : PropertyHandle (&prophdl),
  name(NULL),
  selection(NULL),
  attr_list(),
  attr_count(0),
  data_source(dsource)
{

  SetName(names);

}

/******************************************************************************/
/**
\brief  i04 - 



\param  dsource - 
\param  ph_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CLICollection"

     CLICollection :: CLICollection (CLIDataSource *dsource, PropertyHandle *ph_ptr )
                     : PropertyHandle (ph_ptr),
  name(NULL),
  selection(NULL),
  attr_list(),
  attr_count(0),
  data_source(dsource)
{

  if ( ph_ptr )
    SetName(ph_ptr->GetPropertyPath());

}

/******************************************************************************/
/**
\brief  Copy - 



\return term - 

\param  source_coll - 
\param  mask - 
\param  key_value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

logical CLICollection :: Copy (CLICollection *source_coll, char *mask, char *key_value )
{
  char                    string[256];
  char                    key_area[513];
  char                    mask_area[513];
  Key                     keyptr;
  int32                   count;
  int32                   copied = 0;
  logical                 term = NO;
BEGINSEQ
  if ( GetParentProperty() && !GetParentProperty()->IsPositioned() )
  {
    Output("Error - cannot copy instance - no instance selected for parent in target\n");
                                                   ERROR
  }
  
  if ( mask && !(mask = ::GetStringValue(mask_area,mask)) ) 
                                                     ERROR
  if ( key_value && !(key_value = ::GetStringValue(key_area,key_value)) ) 
                                                     ERROR
  if ( !mask || !*mask || *mask == '.' )
  {
    if ( !source_coll->IsPositioned() )
    {
      Output("Error - cannot copy current instance - no instance selected\n");
                                                     ERROR
    }
    else
    {
      if ( key_value && *key_value )
      {
        keyptr = StringToKey(key_value);
        PropertyHandle::Copy(*source_coll,keyptr,REPL_local);
      }
      else
        PropertyHandle::Copy(*source_coll,REPL_local);
    }
  }
  else if ( *mask == '*' )
  {
    if ( source_coll->GetParentProperty() && !source_coll->GetParentProperty()->IsPositioned() )
    {
      Output("Error - cannot copy collection - no instance selected for parent in source\n");
                                                   ERROR
    }
    if ( GetParentProperty() && !GetParentProperty()->IsPositioned() )
    {
      Output("Error - cannot copy collection - no instance selected for parent in target\n");
                                                   ERROR
    }
    Output("All selected instances in the current collection will be copied - continue (y/n)?");
    SystemInput(string);
    if ( *string == 'y' || *string == 'Y' ) 
    {
      count = source_coll->GetCount();
      while ( count-- )
        if ( source_coll->Get(count) )
        {
          PropertyHandle::Copy(*source_coll,REPL_local,REPL_instance); 
          copied++;
        }
      count = source_coll->GetCount();
      while ( count-- )
        if ( source_coll->Get(count) )
          PropertyHandle::Copy(*source_coll,REPL_local,REPL_relationships); 
      Output("Success - %i instances copied\n",copied);
    }
  }
  else   // value is key or position
  {
    if ( source_coll->Locate(mask) )                           ERROR
    if ( key_value && *key_value )
    {
      keyptr = StringToKey(key_value);
      PropertyHandle::Copy(*source_coll,keyptr,REPL_local);
    }
    else
      PropertyHandle::Copy(*source_coll,REPL_local);
  }
//  else   // das müssen wir noch machen: cpy a*
  ;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Create - 



\return term - 

\param  key_value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

logical CLICollection :: Create (char *key_value )
{
  int32                    position = AUTO;
  char                    key_area[513];
  logical                 term = NO;
BEGINSEQ
  if ( !key_value )
    key_value = "";
  if ( *key_value >= '0' && *key_value <= '9' )
  {
    position = atoi(key_value);
    key_value = NULL;
  }

  if ( key_value && !(key_value = ::GetStringValue(key_area,key_value)) ) 
                                                     ERROR
  PositionTop();
    
  if ( key_value ) 
  {
    PropertyHandle    key(key_value);
    if ( !Provide(key) )
    {
      Output("Error - could not create instance: invalid key\n");
                                                     ERROR
    }
  }
  else 
  {
    if ( !Provide(position) )
    {
      Output("Error - could not create instance at requested position\n");
                                                     ERROR
    }
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Delete - 



\return term - 

\param  mask - 
\param  err_del - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical CLICollection :: Delete (char *mask, logical err_del )
{
  char                     string[256];
  char                     mask_area[513];
  int32                    count;
  int32                    deleted = 0;
  logical                 term = NO;
BEGINSEQ
  if ( err_del )
  {
    if ( !mask )                                     LEAVESEQ
    if ( *mask >= '0' && *mask <= '9' )
      PropertyHandle::Delete(atoi(mask));
    else
      ; // locate by key, delete cuurent index    
  }
  else 
  {
    if ( mask && !(mask = ::GetStringValue(mask_area,mask)) ) 
                                                     ERROR
    if ( !mask || !*mask || *mask == '.' )
    {
      if ( !IsPositioned() )
      {
        Output("Error - cannot delete current instance - no instance selected\n");
                                                     ERROR
      }
      PropertyHandle::Delete(AUTO);
    }
    else if ( *mask == '*' )
    {
      if ( GetParentProperty() && !GetParentProperty()->IsPositioned() )
      {
        Output("Error - cannot delete collection - no instance selected for parent\n");
                                                   ERROR
      }
      Output("All selected instances in the current collection will be deleted - continue (y/n)?");
      SystemInput(string);
      if ( *string == 'y' || *string == 'Y' ) 
        if ( count = GetCount() )
        {
          if ( !DeleteSet(count) )
            Output("Success - %i instances deleted\n",count);
          else
            Output("Error - %i instances not deleted\n",count-GetCount());
        }
    }
    else   // value is key 0r position
    {
      if ( Locate(mask) )                              ERROR
      PropertyHandle::Delete(AUTO);
    }
//  else  // das müssen wir noch machen: del a*
    ;
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetName - 



\return namestr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetName"

char *CLICollection :: GetName ( )
{

  if ( this && name ) return name;
  else return "";

}

/******************************************************************************/
/**
\brief  List - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "List"

logical CLICollection :: List ( )
{
  char                   *keyptr;
  fmcb                   *fmcbptr;
  char                    string[512];
  int32                    indx0 = 0;
  logical                 term = NO;
  ToTop();
  
  if ( GetSortKeyLength() || GetKeyLength() )
    while ( keyptr = NextKey() )
    {
      KeyToString(string,keyptr);
      Output("  %s\n",string);
    }
  else 
    while ( Get(indx0++) )
    {
      if ( GetSortKeyLength() || GetKeyLength() )
        Output("  %s\n",KeyToString(string,keyptr));
      else if ( (fmcbptr = GetDescription()) && fmcbptr->fmcbbase() )
        Output("  %s\n",GetString());
      else
        Output("  %s\n",gvtxitoa(indx0-1,string,10));
    }

  return(term);
}

/******************************************************************************/
/**
\brief  ListAttributes - 



\return term - 

\param  mask - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListAttributes"

logical CLICollection :: ListAttributes (char *mask )
{
  char                   *aname;
  int32                   indx0 = 0;
  logical                 term = NO;
  while ( (aname = GetAttribute(indx0++,NO,NO)) && *aname )
    Output("  %s\n",aname);

  return(term);
}

/******************************************************************************/
/**
\brief  ListCollections - 



\return term - 

\param  mask - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListCollections"

logical CLICollection :: ListCollections (char *mask )
{
  char                   *cname;
  int32                    indx0 = 0;
  logical                 term = NO;
  while ( (cname = GetReference(indx0++,NO,YES)) && *cname )
    Output("  %s\n",cname);

  return(term);
}

/******************************************************************************/
/**
\brief  ListKeys - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListKeys"

logical CLICollection :: ListKeys ( )
{
  DBStructDef            *strdef;
  kcb                    *kcbptr;
  char                    string[512];
  char                    snum[13];
  int32                    indx0 = 0;
  logical                 term = NO;
BEGINSEQ
  if ( !(strdef = GetStructDef()) )                 LEAVESEQ
  
  DLL(kcb)  cursor(*strdef->smcbskey);
  cursor.GoTop();
  while ( kcbptr = cursor.GetNext() )
  {
    Output("  %s(%s)\n",gvtxbts(string,kcbptr->scbsmcb->smcbname,ID_SIZE),
                        gvtxitoa(kcbptr->get_key_num(),snum,10));
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ListOrder - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListOrder"

logical CLICollection :: ListOrder ( )
{
  char                   *index_name;
  char                    string[512];
  int32                    indx0 = 0;
  logical                 term = NO;
  while ( index_name = GetIndexName(indx0++) )
    Output("  %s\n",gvtxbts(string,index_name,ID_SIZE));

  return(term);
}

/******************************************************************************/
/**
\brief  Locate - 



\return term - 

\param  key_value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

logical CLICollection :: Locate (char *key_value )
{
  int32                    position;
  char                    key_area[513];
  logical                 term = NO;
BEGINSEQ
  if ( !key_value )
    key_value = "";
  if ( *key_value >= '0' && *key_value <= '9' )
  {
    position = atoi(key_value);
    key_value = NULL;
  }
  else
    if ( !(key_value = ::GetStringValue(key_area,key_value)) ) 
                                                     ERROR
  PositionTop();
    
  if ( key_value ) 
  {
    PropertyHandle    key(key_value);
    if ( !Get(key) )
    {
      Output("Could not locate instance - key not found\n");
                                                     ERROR
    }
  }
  else 
  {
    if ( !Get(position) )
    {
      Output("Could not locate instance at requested position\n");
                                                     ERROR
    }
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Move - 



\return term - 

\param  source_coll - 
\param  mask - 
\param  key_value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Move"

logical CLICollection :: Move (CLICollection *source_coll, char *mask, char *key_value )
{
  char                    string[256];
  char                    key_area[513];
  char                    mask_area[513];
  Key                     keyptr;
  int32                    count;
  int32                    copied = 0;
  logical                 term = NO;
BEGINSEQ
  if ( GetParentProperty() && !GetParentProperty()->IsPositioned() )
  {
    Output("Error - cannot copy instance - no instance selected for parent in target\n");
                                                   ERROR
  }
  
  if ( mask && !(mask = ::GetStringValue(mask_area,mask)) ) 
                                                     ERROR
  if ( key_value && !(key_value = ::GetStringValue(key_area,key_value)) ) 
                                                     ERROR
  
  if ( !mask || !*mask || *mask == '.' )
  {
    if ( !source_coll->IsPositioned() )
    {
      Output("Error - cannot copy current instance - no instance selected\n");
                                                     ERROR
    }
    else
    {
      if ( key_value && *key_value )
      {
        keyptr = StringToKey(key_value);
        PropertyHandle::Move(*source_coll,keyptr,REPL_local);
      }
      else
        PropertyHandle::Move(*source_coll,REPL_local);
    }
  }
  else if ( *mask == '*' )
  {
    if ( source_coll->GetParentProperty() && !source_coll->GetParentProperty()->IsPositioned() )
    {
      Output("Error - cannot copy collection - no instance selected for parent in source\n");
                                                   ERROR
    }
    if ( GetParentProperty() && !GetParentProperty()->IsPositioned() )
    {
      Output("Error - cannot copy collection - no instance selected for parent in target\n");
                                                   ERROR
    }
    Output("All selected instances in the current collection will be moved - continue (y/n)?");
    SystemInput(string);
    if ( *string == 'y' || *string == 'Y' ) 
    {
      count = source_coll->GetCount();
      while ( count-- )
        if ( source_coll->Get(count) )
          PropertyHandle::Move(*source_coll,REPL_local), copied++;
      Output("Success - %i instances moved\n",copied);
    }
  }
  else   // value is key or position
  {
    if ( source_coll->Locate(mask) )               ERROR
    if ( key_value && *key_value )
    {
      keyptr = StringToKey(key_value);
      PropertyHandle::Move(*source_coll,keyptr,REPL_local);
    }
    else
      PropertyHandle::Move(*source_coll,REPL_local);
  }
//  else   // das müssen wir noch machen: cpy a*
  ;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Output - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  fstring - 
\param  parm1 - 
\param  parm2 - 
\param  parm3 - 
\param  parm4 - 
\param  parm5 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Output"

logical CLICollection :: Output (char *fstring, char *parm1, char *parm2, char *parm3, char *parm4, char *parm5 )
{

  return(data_source->Output(fstring,parm1,parm2,parm3,parm4,parm5));

}

/******************************************************************************/
/**
\brief  i01 - 



\param  fstring - 
\param  intval - 
\param  parm1 - 
\param  parm2 - 
\param  parm3 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Output"

logical CLICollection :: Output (char *fstring, int32 intval, char *parm1, char *parm2, char *parm3 )
{
  logical   term = NO;
  return(data_source->Output(fstring,intval,parm1,parm2));
  return(term);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  fstring - 
\param  parm0 - 
\param  intval - 
\param  parm2 - 
\param  parm3 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Output"

logical CLICollection :: Output (char *fstring, char *parm0, int32 intval, char *parm2, char *parm3 )
{
  logical   term = NO;
  return(data_source->Output(fstring,parm0,intval,parm2));
  return(term);
}

/******************************************************************************/
/**
\brief  ResetAttributes - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetAttributes"

logical CLICollection :: ResetAttributes ( )
{
  int                     i = 0;
  logical                 term = NO;
  while ( attr_count )
    if ( attr_list[--attr_count] )
    {
      free(attr_list[attr_count]);
      attr_list[attr_count] = NULL;
    }

  return(term);
}

/******************************************************************************/
/**
\brief  ResetSelection - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetSelection"

logical CLICollection :: ResetSelection ( )
{
  logical                 term = NO;
  if ( !selection )
    Output("Error - no selection defined for collection\n");
  else
  {
    free(selection);
    selection = NULL;
    PropertyHandle::ResetSelection();
  }

  return(term);
}

/******************************************************************************/
/**
\brief  SetAttributes - 



\return term - 

\param  attribute_list - 
\param  append - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAttributes"

logical CLICollection :: SetAttributes (char **attribute_list, logical append )
{
  char                   *prop_path;
  int                     i = 0;
  logical                 term = NO;
  if ( !append )
    ResetAttributes();

  while ( prop_path = attribute_list[i++] )
  {
    if ( !*prop_path )
      Output("Error - missing attribute name\n");
    if ( !GetPropertyHandle(prop_path) )
      Output("Error - wrong attribute name '%s'\n",prop_path);
    else
      attr_list.SetAtGrow (attr_count++,strdup(prop_path));
  }

  return(term);
}

/******************************************************************************/
/**
\brief  SetName - 




\param  string - String area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetName"

void CLICollection :: SetName (char *string )
{

  if ( name )
    free(name);
  name = NULL;

  if ( string )
    name = strdup(string);

}

/******************************************************************************/
/**
\brief  SetPropertyHandle - 



\return term - 

\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPropertyHandle"

logical CLICollection :: SetPropertyHandle (PropertyHandle &prophdl )
{
  logical                 term = NO;
  CopyHandle(&prophdl);
  SetName(GetPropertyPath());
  return(term);
}

/******************************************************************************/
/**
\brief  SetSelection - 



\return term - 

\param  expression - OQL expression
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSelection"

logical CLICollection :: SetSelection (char *expression )
{
  logical                 term = NO;
  if ( selection )
    ResetSelection();
    
  if ( PropertyHandle::SetSelection(expression) )
    Output("Error - expression passed is not valid\n");
  else
    selection = strdup(expression);
  return(term);
}

/******************************************************************************/
/**
\brief  SetValue - 



\return term - 

\param  assignment - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValue"

logical CLICollection :: SetValue (char *assignment )
{
  char                   *prop_path = assignment;
  PropertyHandle          prophdl;
  char                   *value = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( !assignment || !*assignment )                 ERROR

  if ( !IsSelected() )
  {
    Output("Error- no instance selected\n");         ERROR
  }
  
  if ( !(value = strchr(prop_path,'=')) )
  {
    Output("Error - Sytax error in statement\n");    ERROR
  }
  *value = 0;
  value++;
  
  if ( prophdl.Open(this,prop_path) )
  {
    Output("Error - invalid property path for assignment\n");         
                                                     ERROR
  }
  
  data_source->get_interpreter()->SetValue(prophdl,prop_path,value);
RECOVER
  term = YES;
ENDSEQ
  if ( value )
    *(--value) = '=';
  return(term);
}

/******************************************************************************/
/**
\brief  ~CLICollection - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CLICollection"

     CLICollection :: ~CLICollection ( )
{

  data_source = NULL;
      
  if ( name )
    free(name);
  name = NULL;

  if ( selection )
    ResetSelection();
    
  ResetAttributes();


}


