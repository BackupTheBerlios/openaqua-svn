/********************************* Interface Class Source Code ***************************/
/**
\package  OPI - 
\class    DictionaryHandle

\brief    Dictionary Handle
          The  dictionary handle  is used  for providing schema definitions from
          the  dictionary.  The  dictionary  creates  internal  images  from the
          externally  stored schema definitions. These  internal images ({\b {.r
          DBStructDef}}) can be provided by means of dictionary functions.  
          Because  the dictionary  is a  database handle  {\b {.r DBHandle}} you
          can access schema information also directly via PI functions.

\date     $Date: 2006/06/29 18:08:27,54 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    IF_Class
#define    OBJ_ID  "_IF_DictionaryHandle"

#include  <pdefault.h>
#include  <s_if_DictionaryHandle.hpp>


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
                         *retval = ((DictionaryHandle *)instarea)->Close();
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
  ODABAClient      client;
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  void     *instarea;
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
    case ET_First      : if ( !(instarea = co->Get(0).GetArea()) )
                                                     ERROR
                         switch ( parmcnt )
                         {
                           case 3 : netopt = (*parmlist)[2]->IsTrue();
                           case 2 : accopt = (PIACC)GetSystemDictionary().StringToEnum("PIACC",*(*parmlist)[1]);
                           case 1 : cpath  = (*parmlist)[0]->GetString();
                                    break;
                           default: ERROR;
                         }
                         *retval = ((DictionaryHandle *)instarea)->Open(client,cpath,accopt,netopt);
                         break;
    case ET_Next       :
    default            : ERROR;
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

