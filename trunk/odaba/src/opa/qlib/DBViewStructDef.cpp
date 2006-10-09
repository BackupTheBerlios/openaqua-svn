/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    DBViewStructDef

\brief    


\date     $Date: 2006/08/25 15:16:34,81 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBViewStructDef"

#include  <popa7.h>
#include  <sBNFData.hpp>
#include  <sDBViewGroup.hpp>
#include  <sDictionary.hpp>
#include  <sODC_View.hpp>
#include  <sSDB_Structure.hpp>
#include  <sSDB_ValueList.hpp>
#include  <sDBViewStructDef.hpp>


/******************************************************************************/
/**
\brief  DBViewStructDef - 


-------------------------------------------------------------------------------
\brief  i0 - 


\param  strdef - Structure definition
\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBViewStructDef"

     DBViewStructDef :: DBViewStructDef (DBStructDef *strdef, PropertyHandle &ph )
                     : struct_def(strdef),
  from(),
  where(NULL),
  having(NULL),
  group_by(NULL)
{

  Initialize(ph);

}

/******************************************************************************/
/**
\brief  i01 - 


\param  strdef - Structure definition
\param  bnf_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBViewStructDef"

     DBViewStructDef :: DBViewStructDef (DBStructDef *strdef, BNFData *bnf_data )
                     : struct_def(strdef),
  from(),
  where(NULL),
  having(NULL),
  group_by(NULL)
{

  Initialize(bnf_data);

}

/******************************************************************************/
/**
\brief  i02 - 


\param  strdef - Structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBViewStructDef"

     DBViewStructDef :: DBViewStructDef (DBStructDef *strdef )
                     : struct_def(strdef),
  from(),
  where(NULL),
  having(NULL),
  group_by(NULL)
{



}

/******************************************************************************/
/**
\brief  Initialize - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical DBViewStructDef :: Initialize (PropertyHandle &ph )
{
  int32            indx0 = 0;
  logical          term  = NO;
  PropertyHandle  from_ph(ph.GPH("from"));
  while ( from_ph.Get(indx0++) )
    from.AddTail(new DBViewPath(struct_def,from_ph));

  PropertyHandle  where_ph(ph.GPH("having"));
  if ( where_ph.Get(FIRST_INSTANCE) )
    where = strdup(where_ph.GetString());
    
  PropertyHandle  group_ph(ph.GPH("group_by"));
  if ( group_ph.Get(FIRST_INSTANCE) )
    group_by = new DBViewGroup(struct_def,&group_ph);
  
  PropertyHandle  having_ph(ph.GPH("having"));
  if ( having_ph.Get(FIRST_INSTANCE) )
    having = strdup(having_ph.GetString());


  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  bnf_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical DBViewStructDef :: Initialize (BNFData *bnf_data )
{
  BNFData                *bdata;
  BNFData                *oper;
  int32                   indx0 = 0;
  logical                 term = NO;
// view_header  := view identifier from_spec [where_spec] [group_spec] [having_spec] ...
// from_spec    := _from operand_list 
// operand_list := '(' [parm_list] ')' 
// parm_list    := parameter [parm_ext(*)]
// parm_ext     := ',' parameter

  if ( bdata = bnf_data->GetElement("from_spec") )
  {
    bdata = bdata->GetElement("operand_list");
    if ( bdata = bdata->GetElement("parm_list") )
    {
      oper = bdata->GetElement(indx0);
      while ( oper )
      {
        from.AddTail(new DBViewPath(struct_def,oper,indx0));
        if ( oper = bdata->GetElement(++indx0) )
          oper = oper->GetElement("parameter");
      }
    }
  }
    
  if ( bdata = bnf_data->GetElement("where_spec") )
    where = strdup(bdata->StringValue());
    
  if ( bdata = bnf_data->GetElement("group_by") )
    group_by = new DBViewGroup(struct_def,bdata);

  if ( bdata = bnf_data->GetElement("having_spec") )
    having = strdup(bdata->StringValue());


  return(term);
}

/******************************************************************************/
/**
\brief  ~DBViewStructDef - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DBViewStructDef"

     DBViewStructDef :: ~DBViewStructDef ( )
{
  DBViewPath   *dbvpath;
  if ( where )
    free(where);
  where = NULL;

  if ( having )
    delete having;
  having = NULL;

  while ( dbvpath = from.RemoveTail() )
    delete dbvpath;

  delete group_by;
  group_by = NULL;

}


