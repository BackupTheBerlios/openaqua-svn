/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    CDictionary

\brief    Dictionary
          The  dictionary handle  is used  for providing schema definitions from
          the  dictionary.  The  dictionary  creates  internal  images  from the
          externally  stored schema definitions. These  internal images ({\b {.r
          DBStructDef}}) can be provided by means of dictionary functions.  
          Because  the dictionary  is a  database handle  {\b {.r DBHandle}} you
          can access schema information also directly via PI functions.

\date     $Date: 2006/08/26 12:56:18,96 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CDictionary"

#include  <popa7.h>
#include  <sofifct.h>
#ifndef   P_SDB_Member_HPP
#define   P_SDB_Member_HPP
#include  <sPI.hpp>
class       SDB_Member;
PI_dcl     (SDB_Member)
#endif
#include  <cPIREPL.h>
#include  <sCClient.hpp>
#include  <sCDictionary.hpp>
#include  <sDBExtend.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBFieldList.hpp>
#include  <sDBHandle.hpp>
#include  <sDBResource.hpp>
#include  <sDBStructDef.hpp>
#include  <sDataSourceHandle.hpp>
#include  <sDictionary.hpp>
#include  <sODABAClient.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTypeKey.hpp>
#include  <skcb.hpp>
#include  <stim.hpp>
#include  <sCDictionary.hpp>


/******************************************************************************/
/**
\brief  CDictionary - 



-------------------------------------------------------------------------------
\brief  ci0 - 



\param  odaba_client - 
\param  cpath - Complete path
\param  accopt - Access mode
\param  w_netopt - Multi-user option
\param  version_nr - Internal version number
\param  local_ressources - Resource type
\param  sysenv - System application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CDictionary"

     CDictionary :: CDictionary (CClient *odaba_client, char *cpath, PIACC accopt, logical w_netopt, uint16 version_nr, ResourceTypes local_ressources, char sysenv )
                     : Dictionary(cpath,accopt,w_netopt,version_nr,sysenv),
CDBHandle(odaba_client),
DBHandle(NULL,cpath,accopt,w_netopt,version_nr,sysenv),
ACObject()


{
  logical       term = NO;
BEGINSEQ
#ifndef IF_Class  // client version

  if ( !csconnection )                               SDBERR(517)
     
  ACObject::Initialize(this,accopt,version_nr);
  LockSendParms().Fill(cpath,version_nr,(int32)accopt);
  SetClientPointer(this); 
    
  if ( !CConnection()->SendCSMessage(this,S_CDictionary,SF_CDictionary_CDictionary_ci0) )
  {
    SetServerObject(Get_rec_result().GetHandle()->GetServerObject()); 
    term = Get_rec_result()[0].GetUChar();      
  }
  UnlockSendParms();
  if ( term )                                        ERROR
    
  SetServerObject(Get_rec_result().GetHandle()->GetServerObject()); 
  if ( Get_rec_result()[0].GetUChar())               ERROR
  
  InitHandle(NO);
  
  if ( OpenDictionary() )                            ERROR
  if ( OpenPIs() )                                   ERROR
  
#else             // server version

  SC_Dictionary *sc_dict;
  CS_Handle   *handle = parms->GetHandle();
//SDBError().TraceMessage("OpenDictionary");  
  sc_dict = ((ServerConnection *)connection)->ProvideDict(
                  handle->GetClientObject(),
                  (*parms)[0].GetString(),                                    // cpath
                  (*parms)[1].GetUShort(connection->get_conversion()),        // version_nr
                  (PIACC)(*parms)[2].GetLong(connection->get_conversion()) ); // accopt
   
  handle->SetServerPointer(sc_dict);
  *result->GetHandle() = *handle;
  result->Fill((logical)!sc_dict);

  return(NO);

#endif
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i02 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CDictionary"

     CDictionary :: CDictionary ( )
                     : Dictionary (),
CDBHandle (),
DBHandle (),
ACObject ()

{



}

/******************************************************************************/
/**
\brief  i03 - 



\param  dbhandle - Database handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CDictionary"

     CDictionary :: CDictionary (DBHandle *dbhandle )
                     : Dictionary (),
CDBHandle (),
DBHandle (),
ACObject ()

{

BEGINSEQ
// muss noch gemacht werden

  SDBERR(999)
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  CloseDictionary - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseDictionary"

void CDictionary :: CloseDictionary ( )
{
  logical     term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    Dictionary::CloseDictionary();
    if ( !csconnection || CConnection()->Check() )                                 
      SDBSET(517)
    else
    {
      if ( GetServerObject() )
      {
        LockSendParms().Fill();
        if ( CConnection()->SendCSMessage(this,S_CDictionary,SF_CDictionary_CloseDictionary_ci) ||
             Get_rec_result()[0].GetUChar() )
          term = YES;
        UnlockSendParms();
      }    
      SetServerPointer((void *)NULL); 
    }
    UninitHandle();
  }

#else             // server version

  ((SC_Dictionary *)cso_ptr)->SetClientObject(0);
  term = ((ServerConnection *)connection)->ReleaseDict(parms->GetHandle());
  
  result->Fill(term);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  CreateEnum - 



\return term - Termination code

\param  enum_name - Enumeration name
\param  basetype - Base type name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateEnum"

logical CDictionary :: CreateEnum (char *enum_name, char *basetype )
{
  logical   term = YES;
BEGINSEQ
  SDBERR(999)

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateExtentDef - 



\return extdef - Internal extent definition

\param  tkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateExtentDef"

DBExtend *CDictionary :: CreateExtentDef (TypeKey &tkey )
{
  DBExtend        *extdef = NULL;
  int32            indx0  = 0;
#ifndef IF_Class  // client version

char      string[ID_SIZE+1];

  if ( IsValid() )
  {
    if ( !csconnection )
      SDBSET(517)
    else
    {
      CConnection()->PushResult();
      LockSendParms().Fill(gvtxbts(string,tkey.Name(),ID_SIZE),tkey.GetID());
      if ( !CConnection()->SendCSMessage(this,S_CDictionary,SF_CDictionary_CreateExtentDef_ci) )
        extdef = SetupDBExtent();
      UnlockSendParms();
      CConnection()->PopResult();
    }
  }
  
  return(extdef);

#else             // server version

  extdef = ((SC_Dictionary *)cso_ptr)->DictionaryHandle::ProvideExtentDef(
                  (*parms)[0].GetString(),                          // extnames
                  (*parms)[1].GetLong(connection->get_conversion()) // nsid
           );
  result->FillDBExtentExt(((SC_Dictionary *)cso_ptr)->get_dictionary(),extdef);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  CreateStructDef - 



\return dbstructdef - 

\param  tkey - 
\param  strdef - Structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateStructDef"

DBStructDef *CDictionary :: CreateStructDef (TypeKey &tkey, DBStructDef *strdef )
{


#ifndef IF_Class  // client version

char      string[ID_SIZE+1];
  
  if ( IsValid() )
  {
    if ( !strdef || !strdef->smcbsts.stscerr() )
    {
      if ( !csconnection )
        SDBSET(517)
      else
      {
        CConnection()->PushResult();
        LockSendParms().Fill(gvtxbts(string,tkey.Name(),ID_SIZE),tkey.GetID());
        if ( !CConnection()->SendCSMessage(this,S_CDictionary,SF_CDictionary_CreateStructDef_ci) )
          strdef = SetupDBStructDef(tkey,strdef);
        UnlockSendParms();
        CConnection()->PopResult();
      }
    }
    if ( strdef && strdef->smcbsts.stscerr() )
      strdef = NULL;
  }
  
  return(strdef);

#else             // server version
  DBStructDef    *strdef;

  strdef = ((SC_Dictionary *)cso_ptr)->DictionaryHandle::ProvideStructureDef(
                  (*parms)[0].GetString(),                          // strnames
                  (*parms)[1].GetLong(connection->get_conversion()) // nsid
           );
  result->FillDBStructDefExt(((SC_Dictionary *)cso_ptr)->get_dictionary(),strdef);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  CreateTempExtent - 



\return extnames - Extent name
-------------------------------------------------------------------------------
\brief  ci - 



\param  strnames - Type name
\param  extnames_w - Extent name
\param  key_name_w - 
\param  baseexts_w - 
\param  weak_opt_w - 
\param  own_opt_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTempExtent"

char *CDictionary :: CreateTempExtent (char *strnames, char *extnames_w, char *key_name_w, char *baseexts_w, logical weak_opt_w, logical own_opt_w )
{
  char  *extnames = NULL;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                               
      SDBSET(517)
    else
    {
      LockSendParms().Fill(strnames,extnames_w,key_name_w,baseexts_w,weak_opt_w,own_opt_w);
      if ( !CConnection()->SendCSMessage(this,S_CDictionary,SF_CDictionary_CreateTempExtent_ci) )
        if ( extnames = Get_rec_result()[0].GetString() )
          if ( !Dictionary::CreateTempExtent(strnames,extnames,key_name_w,baseexts_w,weak_opt_w,own_opt_w) )
            extnames = NULL;
      UnlockSendParms();
    }
  }
  
  return(extnames);

#else             // server version

  extnames = ((SC_Dictionary *)cso_ptr)->CreateTempExtent(
                  (*parms)[0].GetString(),     // strnames
                  (*parms)[1].GetString(),     // extnames_w
                  (*parms)[2].GetString(),     // key_name_w
                  (*parms)[3].GetString(),     // baseexts_w
                  (*parms)[4].GetUChar(),      // weak_opt_w
                  (*parms)[5].GetUChar() );    // own_opt_w
  result->Fill(extnames);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  i01 - 



\param  field_def - 
\param  extnames_w - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTempExtent"

char *CDictionary :: CreateTempExtent (DBFieldDef *field_def, char *extnames_w )
{
  char        *extnames = NULL;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )
      SDBSET(517)
    else
    {  
      SDBSET(999) 
// wie muß die DBFieldDefinition rüber und was muß zurück ?
//      Get_send_parms().Fill(?);
//      if ( !CConnection()->SendCSMessage(this,S_CDictionary,SF_CDictionary_CreateTempExtent_ci) )
//        extnames = Get_rec_result()[0].GetString();
    }
  }
  
  return(extnames);

#else             // server version


  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  DeleteEnum - 



\return term - Termination code

\param  enum_name - Enumeration name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteEnum"

logical CDictionary :: DeleteEnum (char *enum_name )
{
  logical   term = YES;
BEGINSEQ
  SDBERR(999)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetClientDictionary - 



\return cdictionary - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClientDictionary"

CDictionary *CDictionary :: GetClientDictionary ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  GetTempName - 



\return extname - Extent name

\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTempName"

char *CDictionary :: GetTempName (char *extnames )
{
  char       *ext_names = NULL;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )
      SDBSET(517)
    else
    {
      if ( !extnames )
        SDBSET(99)
      else
      {
        if ( *extnames )
          ext_names = extnames;
        else
        {
          LockSendParms().Fill(extnames);
          if ( !CConnection()->SendCSMessage(this,S_CDictionary,SF_CDictionary_GetTempName_ci) )
            if ( ext_names = Get_rec_result()[0].GetString() )
              ext_names = strncpy(extnames,ext_names,ID_SIZE);
          UnlockSendParms();
        }
      }
    }
  }
  
  return(ext_names);

#else             // server version

  char   extnames[ID_SIZE+1];
  char  *extname_ptr;
  
  strncpy(extnames,(*parms)[0].GetString(),sizeof(extnames));
  extname_ptr = ((SC_Dictionary *)cso_ptr)->GetTempName(extnames);
  result->Fill(extname_ptr);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  SetupDBExtent - 



\return extdef - Internal extent definition
-------------------------------------------------------------------------------
\brief  i0 - 



\param  rindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupDBExtent"

DBExtend *CDictionary :: SetupDBExtent (int32 &rindx0 )
{
  DBExtend      *extdef       = new DBExtend();
  DBExtend      *exist_extdef = NULL;
  int32          lrindx0      = 0;
  void          *buffer;
  int32          len;

  buffer = Get_rec_result()[rindx0].GetBuffer();
  len    = Get_rec_result()[rindx0].GetCurSize();
  CConnection()->PushResult();
    
  CConnection()->SetResult(buffer,len);
  if ( !Get_rec_result().GetDBExtentData(this,extdef,lrindx0) )
  {
    delete extdef;
    extdef = NULL;
  }
  else if ( exist_extdef = GetExtendDef(extdef->GetTypeKey()) )
  {
    delete extdef;
    extdef = exist_extdef;  // ev. GetDBExtentData dahinein wiederholen ??
  }
    
  if ( !exist_extdef && extdef )
    extdef_list.Insert(extdef);
  
  CConnection()->PopResult();
  rindx0++;

  return(extdef);
}

/******************************************************************************/
/**
\brief  i01 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupDBExtent"

DBExtend *CDictionary :: SetupDBExtent ( )
{
  int32         rindx0 = 0;
  return ( SetupDBExtent(rindx0) );

}

/******************************************************************************/
/**
\brief  SetupDBFieldDef - 



\return term - Termination code

\param  fielddef - Internal field defintion
\param  rindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupDBFieldDef"

logical CDictionary :: SetupDBFieldDef (DBFieldDef *fielddef, int32 &rindx0 )
{
  int32          lrindx0 = 0;
  void          *buffer;
  int32          len;
  logical        term = NO;
  buffer = Get_rec_result()[rindx0].GetBuffer();
  len    = Get_rec_result()[rindx0].GetCurSize();
  CConnection()->PushResult();
  
  CConnection()->SetResult(buffer,len);
  
  if ( !Get_rec_result().GetDBFieldDefData(this,fielddef,lrindx0) )
    term = YES;
  
  CConnection()->PopResult();
  rindx0++;

  return(term);
}

/******************************************************************************/
/**
\brief  SetupDBIndex - 



\return term - Termination code

\param  fielddef - Internal field defintion
\param  rindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupDBIndex"

logical CDictionary :: SetupDBIndex (DBFieldDef *fielddef, int32 &rindx0 )
{
  void          *buffer;
  int32          len;
  int32          lrindx0 = 0;
  logical        term = NO;
  buffer = Get_rec_result()[rindx0].GetBuffer();
  len = Get_rec_result()[rindx0].GetCurSize();
  CConnection()->PushResult();
    
  CConnection()->SetResult(buffer,len);
  term = Get_rec_result().GetDBIndexData(fielddef,lrindx0);
    
  CConnection()->PopResult();
  rindx0++;

  return(term);
}

/******************************************************************************/
/**
\brief  SetupDBKeyComponent - 



\return term - Termination code

\param  kcbptr - 
\param  rindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupDBKeyComponent"

logical CDictionary :: SetupDBKeyComponent (kcb *kcbptr, int32 &rindx0 )
{
  void          *buffer;
  int32          len;
  logical        term = NO;
  buffer = Get_rec_result()[rindx0].GetBuffer();
  len    = Get_rec_result()[rindx0].GetCurSize();
  CConnection()->PushResult();
    
  CConnection()->SetResult(buffer,len);
  term = Get_rec_result().GetDBKeyComponentData(kcbptr);
    
  CConnection()->PopResult();
  rindx0++;

  return(term);
}

/******************************************************************************/
/**
\brief  SetupDBKeyDef - 



\return term - Termination code

\param  strdef - Structure definition
\param  rindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupDBKeyDef"

logical CDictionary :: SetupDBKeyDef (DBStructDef *strdef, int32 &rindx0 )
{
  void          *buffer;
  int32          len;
  int32          lrindx0 = 0;
  logical        term = NO;
  buffer = Get_rec_result()[rindx0].GetBuffer();
  len = Get_rec_result()[rindx0].GetCurSize();
  CConnection()->PushResult();
    
  CConnection()->SetResult(buffer,len);
  if ( !Get_rec_result().GetDBKeyDefData(this,strdef,lrindx0) )
    term = YES;
  
  CConnection()->PopResult();
  rindx0++;

  return(term);
}

/******************************************************************************/
/**
\brief  SetupDBResource - 



\return term - Termination code

\param  dbresource - 
\param  rindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupDBResource"

logical CDictionary :: SetupDBResource (DBResource *dbresource, int32 &rindx0 )
{
  void          *buffer;
  int32          len;
  logical        term = NO;
  buffer = Get_rec_result()[rindx0].GetBuffer();
  len = Get_rec_result()[rindx0].GetCurSize();
  CConnection()->PushResult();
  
  CConnection()->SetResult(buffer,len);
  if ( !Get_rec_result().GetDBResourceData(this,dbresource) )
    term = YES;
  
  CConnection()->PopResult();
  rindx0++;

  return(term);
}

/******************************************************************************/
/**
\brief  SetupDBStructDef - 



\return strdef - Structure definition
-------------------------------------------------------------------------------
\brief  i00 - 



\param  tkey - 
\param  strdef - Structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupDBStructDef"

DBStructDef *CDictionary :: SetupDBStructDef (TypeKey &tkey, DBStructDef *strdef )
{
  int32              rindx0 = 0;
  return( SetupDBStructDef(tkey,strdef,rindx0) );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  tkey - 
\param  strdef - Structure definition
\param  rindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupDBStructDef"

DBStructDef *CDictionary :: SetupDBStructDef (TypeKey &tkey, DBStructDef *strdef, int32 &rindx0 )
{
  void          *buffer;
  int32          len;
  int32          lrindx0 = 0;
  logical        term = YES;
BEGINSEQ
  if ( !strdef )
    if ( !(strdef = ProvideStructDcl(tkey)) )        ERROR
  
  buffer = Get_rec_result()[rindx0].GetBuffer();
  len = Get_rec_result()[rindx0].GetCurSize();
  if ( len > 0 )
  {
    term = NO;
    CConnection()->PushResult();
  
    CConnection()->SetResult(buffer,len);
    if ( !Get_rec_result().GetDBStructDefData(this,strdef,lrindx0) )
      term = YES;
   
    CConnection()->PopResult();
    rindx0++;
  }
  if ( term )                                        
  {
    strdef->smcbsts.stsserr();
    SDBEV1(strdef->smcbname,ID_SIZE)
    SDBERR(20)
  }

RECOVER
  strdef = NULL;
ENDSEQ
  return(strdef);
}

/******************************************************************************/
/**
\brief  SetupDBValue - 



\return term - Termination code

\param  csentry - 
\param  rindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupDBValue"

logical CDictionary :: SetupDBValue (ENUM_Value *csentry, int32 &rindx0 )
{
  void          *buffer;
  int32          len;
  logical        term = NO;

  buffer = Get_rec_result()[rindx0].GetBuffer();
  len = Get_rec_result()[rindx0].GetCurSize();
  CConnection()->PushResult();
      
  CConnection()->SetResult(buffer,len);
  term = Get_rec_result().GetDBValueData(csentry);
  
  CConnection()->PopResult();
  rindx0++;

  return(term);
}

/******************************************************************************/
/**
\brief  ~CDictionary - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CDictionary"

     CDictionary :: ~CDictionary ( )
{

  CloseDictionary();


}


