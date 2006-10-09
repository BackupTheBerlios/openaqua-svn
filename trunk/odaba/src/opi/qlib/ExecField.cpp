/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:09:46,17}|(REF)
\class    ExecField

\brief    


\date     $Date: 2006/03/12 19:10:28,87 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ExecField"

#include  <pdefault.h>
#include  <sPropertyHandle.hpp>
#include  <sExecField.hpp>


/******************************************************************************/
/**
\brief  ExecField - 


-------------------------------------------------------------------------------
\brief i0


\param  dat_field -
\param  prop_dbf -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecField"

                        ExecField :: ExecField (PropertyHandle *dat_field, PropertyHandle &prop_dbf )
                     : db_field(NULL),
  index(0)
{
  char     *prop_path = prop_dbf.GetPropertyHandle("name")->GetArea();
  fmcb     *dbflddef;
BEGINSEQ
  if ( *prop_path <= ' ' || *prop_path == '.' )
  {
    db_field = dat_field->Dereference();
  }  
  else  
    db_field = new PropertyHandle(dat_field->GetPropertyHandle(prop_path));
  
  if ( !db_field )                                   SDBERR(95)
                                                     SDBCERR
  index = prop_dbf.GetPropertyHandle("index")->GetInt();
  strcpy(attr_type,prop_dbf.GetPropertyHandle("attr_type")->GetArea());

  SDBRESET
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief i1


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecField"

                        ExecField :: ExecField ( )
                     : db_field(NULL),
  index(0)
{



}

/******************************************************************************/
/**
\brief  LocateInstance - 


\return term - Termination code

\param  inst_ptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateInstance"

logical ExecField :: LocateInstance (void *inst_ptr )
{
  logical                 term = NO;
BEGINSEQ
//  if ( !db_field->SetInstance(inst_ptr) )            ERROR
  
  if ( *attr_type && db_field->GetDescription()->fmcbrlev == R_GENERIC )
    if ( db_field->SetGenAttribute(attr_type) )      ERROR
      
  if ( !db_field->IsCollection() )
    if ( !db_field->GetValue(index) )                ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~ExecField - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ExecField"

                        ExecField :: ~ExecField ( )
{

  delete db_field;

}


