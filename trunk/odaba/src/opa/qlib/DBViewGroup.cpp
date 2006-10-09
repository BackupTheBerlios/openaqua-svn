/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    DBViewGroup

\brief    GroupBy Clause
          A  group  clause  consists  either  of an expression defining the view
          value  domain  or  an  explicite  domain  definition  by  using  case 
          expressions,  i.e.  assigning  the  first  value  from  a  list, which
          returns true for the case condition.

\date     $Date: 2006/08/25 15:14:24,17 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBViewGroup"

#include  <popa7.h>
#include  <sBNFData.hpp>
#include  <sDBFieldList.hpp>
#include  <sDBStructDef.hpp>
#include  <sPropertyHandle.hpp>
#include  <sDBViewGroup.hpp>


/******************************************************************************/
/**
\brief  DBViewGroup - 


-------------------------------------------------------------------------------
\brief  i0 - 


\param  strdef - Structure definition
\param  vl_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBViewGroup"

     DBViewGroup :: DBViewGroup (DBStructDef *strdef, PropertyHandle *vl_ph )
                     :   struct_def(strdef),
  source(NULL),
  case_list()
{

  Initialize(vl_ph);

}

/******************************************************************************/
/**
\brief  i01 - 


\param  strdef - Structure definition
\param  bnf_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBViewGroup"

     DBViewGroup :: DBViewGroup (DBStructDef *strdef, BNFData *bnf_data )
                     :   struct_def(strdef),
  source(NULL),
  case_list()
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
#define    MOD_ID  "DBViewGroup"

     DBViewGroup :: DBViewGroup (DBStructDef *strdef )
                     : struct_def(strdef),
  source(),
  case_list()
{



}

/******************************************************************************/
/**
\brief  Initialize - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  bnf_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical DBViewGroup :: Initialize (BNFData *bnf_data )
{
  BNFData      *bdata;
  BNFData      *cat_spec;
  int32         indx0 = 0;
  DBFieldDef   *fd;
  logical       term = NO;

BEGINSEQ
// categories            := category_list | operand
// category_list         := category_spec [category_ext(*)]
// category_ext          := ',' category_spec

  if ( bdata = bnf_data->GetSymbol("operand") )
    source = strdup(bdata->GetStringValue(NULL,NULL));
  else
  {
    if ( !(bdata = bnf_data->GetSymbol("category_list")) )     
                                                     SDBERR(99)
    cat_spec = bdata->GetElement(indx0);
    case_list.SetAtGrow(indx0++,new DBViewGroupCase(cat_spec));
    while ( cat_spec = bdata->GetElement(indx0) )
      if ( cat_spec = cat_spec->GetElement(indx0) )
        case_list.SetAtGrow(indx0++,new DBViewGroupCase(cat_spec));
  }

  fd = ((DBFieldList *)struct_def->smcbfmcl)->CreateField();
  DBFieldDef tdbfdv("value","CHAR",0,RL_direct,ID_SIZE,0,1,NULL,NULL,NO,NULL,NULL,NULL);
  *fd = tdbfdv;
  struct_def->IncreaseAttrCount(1);
  
  fd  = ((DBFieldList *)struct_def->smcbfmcl)->CreateField();
  DBFieldDef tdbfdp("partition","VOID",0,RL_reference,0,0,0,NULL,NULL,NO,NULL,NULL,NULL);
  *fd = tdbfdp;
  struct_def->IncreaseRefrCount(1);
  
  struct_def->Setup(NULL,NULL,"ident_key","value");
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  vl_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical DBViewGroup :: Initialize (PropertyHandle *vl_ph )
{
  PropertyHandle         *ph;
  char                   *string;
  int32                   indx0 = 0;
  logical                 term = NO;
BEGINSEQ
  if ( (string = vl_ph->GetString("expression")) && *string )
    source = strdup(string);
  else
  {
    if ( !(ph = vl_ph->GPH("values")) )              SDBERR(99)
    if ( ph->GetCount() <= 0 )                       SDBERR(382)
    
    while ( ph->Get(indx0) )
      case_list.SetAtGrow(indx0++,
        new DBViewGroupCase(ph->GetString("name"), 
                            ph->GetInt("value"),
                            ph->GetString("condition")) );
     
  }


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~DBViewGroup - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DBViewGroup"

     DBViewGroup :: ~DBViewGroup ( )
{
  int32         count = case_list.GetSize();
  if ( source )
    free(source);
  source = NULL;

  while ( count-- )
  {
    delete case_list[count];
    case_list[count] = NULL;
  }

}


