/********************************* Interface Class Source Code ***************************/
/**
\package  OPI - 
\class    DatabaseHandle

\brief    Database Handle
          Database  handle  must  be  created  for  accessing  data  in an ODABA
          database.  An  ODABA  database  must  be  connected with a dictionary,
          which defines the object model for the database. 
          Each  ODABA database  consists of  at least  one Database Object (Root
          Object) that is the owner od extents and other data collections. 
          When  creating a database handle the object  handle this is based on a
          database  object handle (-> DBObjectHandle)  for the root object, i.e.
          the  database handle inherits all  the functionality from the database
          object handle. 
          A  database may consists of a  number of physical separated mainbases,
          sub-bases  and data areas. This  is, however, handles internally after
          creating  the database. For creating  a multiple resource database the
          database  handle provides several functions  for initializing main and
          sub bases and data areas. 
          Moreover,  the  database  handle  provides  log and recovery features,
          that  allow logging all changes made on the database or recovering the
          database in case of errors. 
          The  workspace feature supported  by the database  handle is a sort of
          persistent  transactions.  It  allows  storing  changes  for  a longer
          period  outside the  database and  consolidating or discarding changes
          when requested by the user.

\date     $Date: 2006/06/29 18:08:03,84 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    IF_Class
#define    OBJ_ID  "_IF_DatabaseHandle"

#include  <pdefault.h>
#include  <s_if_DatabaseHandle.hpp>


#undef     MOD_ID
#define    MOD_ID  "Close"

logical __cdecl Close( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  void     *instarea;
  logical   term    = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : if ( !(instarea = co->Get(0).GetArea()) )
                                                     ERROR
                         *retval = ((DatabaseHandle *)instarea)->Close();
                         break;
    case ET_Next       :
    default            : ERROR;
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}


#undef     MOD_ID
#define    MOD_ID  "Open"

logical __cdecl Open( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  void     *dct_inst;
  void     *db_inst;
  logical   netopt = NO;
  PIACC     accopt = PI_Read;
  char     *cpath;
  logical   term    = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : if ( !(db_inst = co->Get(0).GetArea()) )
                                                     ERROR
                         switch ( parmcnt )
                         {
                           case 4 : netopt   = (*parmlist)[3]->IsTrue();
                           case 3 : accopt   = (PIACC)GetSystemDictionary().StringToEnum("PIACC",*(*parmlist)[2]);
                           case 2 : cpath    = (*parmlist)[1]->GetString();
                                    dct_inst = (*parmlist)[0]->GetArea();
                                    break;
                           case 1 :
                           default: ERROR;
                         }
                         *retval = ((DatabaseHandle *)db_inst)->Open(*(DictionaryHandle *)dct_inst,
                                                                       cpath,accopt,netopt);
                         break;
    case ET_Next       :
    default            : ERROR;
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

