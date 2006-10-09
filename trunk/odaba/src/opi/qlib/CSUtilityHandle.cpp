/********************************* Class Source Code ***************************/
/**
\package  OPI - 
\class    CSUtilityHandle

\brief    


\date     $Date: 2006/08/28 20:15:59,92 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CSUtilityHandle"

#include  <pdefault.h>
#include  <sDBHandle.hpp>
#include  <sDBInfo.hpp>
#include  <sDBObjectHandle.hpp>
#include  <sDictionary.hpp>
#include  <sError.hpp>
#include  <sODABAClient.hpp>
#include  <sUtilityHandle.hpp>
#include  <sCSUtilityHandle.hpp>


/******************************************************************************/
/**
\brief  CSUtilityHandle - 


-------------------------------------------------------------------------------
\brief  i0 - 


\param  odaba_client - ODABA Client Handle
\param  utiname - 
\param  inipath - 
\param  utititle - 
\param  progpath - Programme path
\param  application_type - Run as console application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSUtilityHandle"

     CSUtilityHandle :: CSUtilityHandle (ODABAClient &odaba_client, char *utiname, char *inipath, char *utititle, char *progpath, ApplicationTypes application_type )
                     : UtilityHandle (odaba_client,utiname,utititle,inipath,
               progpath,application_type)

{



}

/******************************************************************************/
/**
\brief  i1 - 


\param  odaba_client - ODABA Client Handle
\param  utiname - 
\param  inipath - 
\param  progpath - Programme path
\param  application_type - Run as console application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSUtilityHandle"

     CSUtilityHandle :: CSUtilityHandle (ODABAClient &odaba_client, char *utiname, char *inipath, char *progpath, ApplicationTypes application_type )
                     : UtilityHandle (odaba_client,utiname,inipath,
               progpath,application_type)

{



}

/******************************************************************************/
/**
\brief  Copy - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

logical CSUtilityHandle :: Copy ( )
{
  DBExtend  *extdef;
  char       strnames[ID_SIZE+1];
  char       strname[ID_SIZE+1];
  char       target[ID_SIZE+1];
  char       source[ID_SIZE+1];
  char      *curpos;
  int32       indx0  = 0;
  int16      tlen   = 0;
  int16      cmplen = 0;
  logical    term    = NO;
BEGINSEQ
  SDBRESET

  memset(strname,0,sizeof(strname));
  memset(target,0,sizeof(target));
  memset(source,0,sizeof(source));
  
  if ( TestSysVariable("RETAIN_SID","YES") )
    retain_sid = YES;
  if ( TestSysVariable("RETAIN_SCHEMAVERSION","YES") )
    retain_schemaversion = YES;
  if ( TestSysVariable("REPLACE","all") )
    sdburepl = REPL_all;
  else if ( TestSysVariable("REPLACE","local") )
    sdburepl = REPL_local;
  else if ( TestSysVariable("REPLACE","none") )
    sdburepl = REPL_none;
    
  if ( *sdbures->extent_name )
  {
    if ( !(extdef = sdbures->dictionary.ProvideExtentDef(sdbures->extent_name)) )
                                                     ERROR
    if ( !*sdbures->struct_name )
      memcpy(strname,extdef->fmcbtype,ID_SIZE);
  }
  else
  {
    if ( !*sdbures->struct_name )                     SDBERR(122)
    gvtxstb(strname,sdbures->struct_name,ID_SIZE); 
  }  
  
  if ( *strname <= ' ' )                             LEAVESEQ
       
  if ( *strname && !sdbuinstonly && sdburepl != REPL_relationships )
  {
    PropertyHandle sdbspi(sdbures->dictionary,"SDB_Structure",PI_Read);
                                                     SDBCERR
    if ( *strname == '*' )
    {
      while ( sdbspi(indx0++).GetData() )
      {
        sdbspi.ExtractKey(strname);
        memcpy(target,strname,ID_SIZE);
        SDBError().DisplayMessage(-401,strname,sdbures->dict_path,sdbudat->dict_path);
        if ( sdbudat->dictionary.CopyType(sdbures->dictionary,strname,target,strname,sdburepl,retain_sid,YES,retain_schemaversion) )
                                                     ERROR
      }
    } 
    else
    {
      if ( curpos = strchr(gvtxbts(strnames,strname,ID_SIZE),'*') )
      {
        *curpos = 0;
        cmplen  = strlen(strnames);
        if ( sdbspi.LocateKey(strnames) )
          sdbspi.NextKey(strnames);
        if ( curpos = strchr(sdbudat->struct_name,'*') )
        {
           memset(target,' ',sizeof(target));
           memcpy(target,sdbudat->struct_name,tlen = curpos-sdbudat->struct_name);
        }
        while ( sdbspi.Exist() && (!cmplen || !memcmp(sdbspi.ExtractKey(strname).GetData(),strnames,cmplen)) )
        {
          if ( tlen )
            memcpy(target+tlen,((char *)sdbspi.ExtractKey().GetData())+cmplen,sizeof(target)-tlen);
          else  
            memcpy(target,strname,ID_SIZE);
          SDBError().DisplayMessage(-401,strname,sdbures->dict_path,sdbudat->dict_path);
          if ( sdbudat->dictionary.CopyType(sdbures->dictionary,strname,target,strname,sdburepl,retain_sid,YES,retain_schemaversion) )
                                                     ERROR
          sdbspi.NextKey();
        }
      }
      else
      { 
        if ( *sdbudat->struct_name && *sdbudat->struct_name != '*' )
          gvtxstb(target,sdbures->struct_name,ID_SIZE);
        else
          memcpy(target,strname,sizeof(target));
        SDBError().DisplayMessage(-401,strname,sdbures->dict_path,sdbudat->dict_path);
        if ( sdbudat->dictionary.CopyType(sdbures->dictionary,strname,target,strname,sdburepl,retain_sid,YES,retain_schemaversion) )
                                                     ERROR
      }
    }                                                 
  }

  if ( *sdbures->extent_name )
  {
    gvtxstb(source,sdbures->extent_name,ID_SIZE);
    if ( *sdbudat->extent_name && *sdbudat->extent_name != '*' )
      gvtxstb(target,sdbudat->extent_name,ID_SIZE);
    else
      gvtxstb(target,sdbures->extent_name,ID_SIZE);
    
    if ( !sdbuinstonly )
      if ( sdbudat->dictionary.CopyExtentDef(sdbures->dictionary,source,target,NULL,YES) )
                                                     ERROR 
    
    if ( !*sdbudat->db_path || !*sdbures->db_path || 
         (!*sdbures->inst_key && !sdbuinstonly )   )  LEAVESEQ
                                   
    if ( CopyInstances(target,source) )            ERROR
  }
RECOVER
  SDBError().DisplayMessage();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CopyAllObjects - 


\return term - Termination code

\param  srce_object - 
\param  targ_object - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyAllObjects"

logical CSUtilityHandle :: CopyAllObjects (DBObjectHandle &srce_object, DBObjectHandle &targ_object )
{
  char              opath[sizeof(sdbures->object_name)];
  char             *pos;
  int32              lindx0 = 0;
  logical           term = NO;
BEGINSEQ
  sdbures->CloseDBObject();
  sdbudat->CloseDBObject();
  sdbures->object_handle = srce_object;
  sdbudat->object_handle = targ_object;
  srce_object.SetOverload(NO);  
  if ( CopyObject() )                                ERROR

  sdbures->object_handle.Close();
  sdbudat->object_handle.Close();
  
  PropertyHandle   objname_pi(srce_object,"SDB_NamedObject",PI_Read);
                                                     SDBCERR
  switch ( *sdbures->object_name )
  {
    case  0    :
    case  ' '  : LEAVESEQ
    case  '*'  : while ( objname_pi.Get(lindx0++).GetData() )
                 {
                   DBObjectHandle s_object(srce_object,objname_pi.ExtractKey().GetData(),PI_Read);
                                                     SDBCERR
                   DBObjectHandle t_object(targ_object,objname_pi.ExtractKey().GetData(),PI_Write);
                                                     SDBCERR
                   CopyAllObjects(s_object,t_object);
                 }
                 break;
    default    : strcpy(opath,sdbures->object_name);
                 if ( pos = strchr(opath,'.') )
                 {
                   strcpy(sdbures->object_name,pos+1);
                   *pos = 0;
                 }
                 else
                   *sdbures->object_name = 0;
                 DBObjectHandle s_object(srce_object,opath,PI_Read);
                                                     SDBCERR
                 DBObjectHandle t_object(targ_object,opath,PI_Write);
                                                     SDBCERR
                 CopyAllObjects(s_object,t_object);
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CopyCollection - 


\return term - Termination code

\param  coll_pi - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyCollection"

logical CSUtilityHandle :: CopyCollection (PropertyHandle &coll_pi )
{
  PropertyHandle    *subcoll = coll_pi.GetPropertyHandle("collection");
  PropertyHandle    *instcoll;
  char       *extname;
  int32        subi0;
  int32        indx0 = 0;
  logical     term = NO;
BEGINSEQ
  if ( !subcoll )                                    ERROR
  *sdbudat->inst_key = 0;
  
  while ( subcoll->Get(indx0++).GetData() )
  {
    instcoll =  subcoll->GetPropertyHandle("collection");
    extname = subcoll->GetPropertyHandle("type")->GetString();
    if ( *extname < ' ' )
      extname = subcoll->GetPropertyHandle("sys_ident")->GetString();
    if ( !instcoll->GetCount() )
    {
      strcpy(sdbures->inst_key,"*");
      CopyInstances(extname,extname);
    }
    else
    {
      subi0 = 0;
      while ( instcoll->Get(subi0++).GetData() )
      {
        strcpy(sdbures->inst_key,instcoll->GetPropertyHandle("sys_ident")->GetString());
        CopyInstances(extname,extname);
      }
    }
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CopyDB - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyDB"

logical CSUtilityHandle :: CopyDB ( )
{
  logical     term = NO;
  SetSysVariable("MAINTENANCE_PROCESS","YES");
  
  term = CopyAllObjects(sdbures->dbhandle,sdbudat->dbhandle);

  if ( retain_schemaversion )  
    sdbudat->dictionary.UpdateVersion();

  return(term);
}

/******************************************************************************/
/**
\brief  CopyInstances - 


\return term - Termination code

\param  targ_ext - 
\param  srce_ext - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyInstances"

logical CSUtilityHandle :: CopyInstances (char *targ_ext, char *srce_ext )
{
  char       entarea[513];
  char       idkey[513];
  char       targid[513];
  char      *new_key;
  PIREPL     db_replace = sdburepl;
  PIREPL     copy_type = REPL_all;
  int32      setcnt;
  int32      count = 0;
  int32      indx  = 0;
  int16      tlen  = 0;
  int16      ta_level = 0;
  int16      cmplen;
  char       string1[17];
  char       string2[17];
  char      *curpos;
  logical    oldmode;
  logical    term = NO;
BEGINSEQ
  oldmode = sdbudat->object_handle.UpdateTimestamp(NO);
  if ( !sdbures->object_handle.ExtentExist(srce_ext) ) LEAVESEQ
    
  SDBError().InsertStatField();
  
  PropertyHandle    svoidpi(sdbures->object_handle,srce_ext,PI_Read);
                                                     SDBCERR
  PropertyHandle    tvoidpi(sdbudat->object_handle,targ_ext,PI_Write);
                                                     SDBCERR
  if ( !tvoidpi.GetDescription() || !tvoidpi.GetType() )
                                                     SDBERR(99)
  if ( !memcmp(tvoidpi.GetType(),"SDB_Structure ",14) &&
       !tvoidpi.GetDescription()->get_log_reference()   )
                                                     LEAVESEQ

  if ( sdburepl == REPL_relationships || sdburepl == REPL_instance )
  {
    copy_type  = sdburepl;
    db_replace = REPL_none;
  }
  
  SDBError().DisplayMessage(-408,gvtxbts(idkey,srce_ext,ID_SIZE),sdbures->db_path,sdbudat->db_path);
  ta_level = sdbudat->dbhandle.BeginTransaction(NO,100);
  switch ( *sdbures->inst_key )
  {
    case '*' : if ( (setcnt = svoidpi.GetCount()) > 0 )
                 while ( indx < setcnt )
                   if ( svoidpi(indx++).GetData() )                              
// has been used for upgrade to v6        
//                   if ( tvoidpi.Copy(svoidpi,svoidpi.ExtractSortKey(),db_replace,copy_type).GetData() )                 
                     if ( tvoidpi.Copy(svoidpi,db_replace,copy_type).GetData() )         
                     {
                       count++;
                       SDBError().SetStatField(gvtxltoa(count,entarea,10));
                     }
               SDBError().DisplayMessage(-406,gvtxltoa(count,entarea,10),gvtxltoa(setcnt,string1,10));
               break;
    default  : if ( curpos = strchr(gvtxbts(idkey,sdbures->inst_key,sizeof(idkey)),'*') )
               {
                 *curpos = 0;
                 cmplen  = strlen(idkey);
                 if ( svoidpi.LocateKey(idkey) )
                   svoidpi.NextKey(idkey);
                 if ( curpos = strchr(sdbudat->inst_key,'*') )
                 {
                   memset(targid,' ',sizeof(targid));
                   memcpy(targid,sdbudat->inst_key,tlen = curpos-sdbudat->inst_key);
                 }
                 if ( tlen && tvoidpi.GetSortKeySMCB()->smcbfmcl->GetCount() > 1 && tlen != cmplen )
                                                     SDBERR(123)
                 while ( svoidpi.Exist() && (!cmplen || !memcmp(svoidpi.ExtractKey().GetData(),idkey,cmplen)) )
                 {
                   if ( tlen )
                     memcpy(targid+tlen,((char *)svoidpi.ExtractKey().GetData())+cmplen,sizeof(targid)-tlen);
                   if ( tvoidpi.Copy(svoidpi,tlen ? targid : (char*)NULL,db_replace,copy_type).GetData() )   
                   {
                     count++;
                     SDBError().SetStatField(gvtxltoa(count,entarea,10));
                   }
                   svoidpi.NextKey();
                 }
                 SDBError().DisplayMessage(-406,gvtxltoa(count,string1,10),gvtxltoa(svoidpi.GetCount(),string2,10));
               }
               else
               {
                 svoidpi.GetSortKeySMCB()->ConvertToStruct(sdbures->inst_key,idkey,0);
                 new_key = targid;
                 if ( *sdbudat->inst_key )
                   tvoidpi.GetSortKeySMCB()->ConvertToStruct(sdbures->inst_key,targid,0);
                 else
                   new_key = NULL;
                 if ( svoidpi(idkey).GetData() )
                 {
                   if ( !tvoidpi.Copy(svoidpi,new_key,db_replace,copy_type).GetData() )     ERROR
                   SDBError().DisplayMessage(-405,gvtxbts(entarea,idkey,MIN(sizeof(idkey)-1,svoidpi.GetKeyLength())));
                 }
                 else  
                   SDBError().DisplayMessage(-407,gvtxbts(entarea,idkey,MIN(sizeof(idkey)-1,svoidpi.GetKeyLength())));
               }
  }
RECOVER
  SDBError().DisplayMessage();
  term = YES;
ENDSEQ
  if ( ta_level )
    sdbudat->dbhandle.CommitTransaction(ta_level);
  sdbudat->object_handle.UpdateTimestamp(oldmode);
  SDBError().RemoveStatField();
  return(term);

}

/******************************************************************************/
/**
\brief  CopyObject - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyObject"

logical CSUtilityHandle :: CopyObject ( )
{
  DBExtend         *extdef;
  char              types[ID_SIZE+1];
  char              collection[ID_SIZE];
  char             *extnames;
  int16             indx0 = 0;
  logical           term  = NO;
BEGINSEQ
  PropertyHandle    ext_pi(sdbures->dictionary,"SDB_Extend",PI_Read);  
                                                     SDBCERR
  PropertyHandle    dbs_pi(sdbures->dictionary,"SDB_Structure",PI_Read);  
                                                     SDBCERR
  PropertyHandle    cs_pi(sdbures->dictionary,"SDB_CodeSet",PI_Read);  
                                                     SDBCERR
  PropertyHandle    targ_cs_pi(sdbudat->dictionary,"SDB_CodeSet",PI_Read);  
                                                     SDBCERR
  PropertyHandle    targ_dbs_pi(sdbudat->dictionary,"SDB_Structure",PI_Read);  
                                                     SDBCERR
  
  PropertyHandle    dbs_sys_ident(dbs_pi,"sys_ident");  
  
  PropertyHandle    cs_sys_ident(cs_pi,"sys_ident");  
  
  PropertyHandle    ext_sys_ident(ext_pi,"sys_ident");  
  PropertyHandle    ext_ddetype(ext_pi,"ddetype");  
  
  SDBEV1(sdbures->struct_name,ID_SIZE)
  SDBEV2(sdbures->extent_name,ID_SIZE)
  SDBEV3(*sdbudat->struct_name ? sdbudat->struct_name : sdbures->struct_name,ID_SIZE)
  SDBEV4(sdbudat->extent_name,ID_SIZE)
  TypeKey   tstr(sdbudat->dictionary,*sdbudat->struct_name ? sdbudat->struct_name : sdbures->struct_name);
  TypeKey   sstr(sdbures->dictionary,sdbures->struct_name);
  
  if ( sdbures->collopt || sdbudat->collopt )
  {
    DataSourceHandle *ds = sdbures->collopt ? sdbures : sdbudat;
    PropertyHandle    coll_pi(ds->dictionary,"SDB_Collection",PI_Read);
                                                     SDBCERR
    SDBEV1(ds->extent_name,UNDEF)
    if ( !coll_pi(gvtxstb(collection,ds->extent_name,ID_SIZE)) )
                                                     SDBERR(218)
    if ( CopyCollection(coll_pi) )                   ERROR
    LEAVESEQ
  }
  
  switch ( *sdbures->extent_name )
  {
    case '*' : switch ( *sdbures->struct_name )
               {
                 case 0   :
                 case ' ' :
                 case '*' : while ( extnames = sdbures->object_handle.GetExtent(indx0++) )
                            {
                              TypeKey     tkey(sdbures->dictionary,extnames);
                              extdef = NULL;
                              if ( ext_pi(tkey.GetKey()).GetData() || (extdef = sdbures->dictionary->GetExtendDef(extnames)) ) 
                              {
                                gvtxbts(types,extdef ? extdef->fmcbtype : ext_ddetype.GetString(),sizeof(types)-1);
                                if ( !cs_pi(extdef ? extdef->fmcbname : ext_sys_ident.GetArea()).GetData()  && 
                                     strcmp(types,"SDB_Structure") &&
                                     strcmp(types,"__OBJECT")      &&
                                     strcmp(types,"SDB_CodeSet")     )
                                {
                                  strcpy(sdbures->extent_name,extdef ? extnames : ext_sys_ident.GetString());
                                  if ( !ext_pi.Exist() || ext_pi.GetPropertyHandle("ddeindx")->GetCount() )     // Index ?, neu aus CopyRESDB 10.5.00
                                    Copy();
                                }
                              }
                            }
                            break;
                 default  : if ( cs_pi(sstr.GetKey()).GetData() )   SDBERR(-931)
                            if ( targ_cs_pi(tstr.GetKey()).GetData() ) 
                                                     SDBERR(-933)
                            if ( targ_dbs_pi(tstr.GetKey()).GetData() && SDBError().GetDecision(-935) )
                                                     ERROR
                            while ( extnames = sdbures->object_handle.GetExtent(indx0++) )
                            {
                              TypeKey   tkey(sdbures->dictionary,extnames);
                              extdef = NULL;
                              if ( (ext_pi(tkey.GetKey()).GetData() || (extdef = sdbures->dictionary->GetExtendDef(extnames))) &&
                                   !memcmp(sstr.Name(),extdef ? extdef->fmcbtype : ext_ddetype.GetArea(),ID_SIZE) )
                              {
                                strcpy(sdbures->extent_name,extdef ? extdef->fmcbname : ext_sys_ident.GetString());
                                Copy();
                              }
                            }
               }  
               *sdbures->extent_name = '*';
               break;
    case 0   :           
    case ' ' : switch ( *sdbures->struct_name )
               {
                 case 0   :                          ERROR
                 case ' ' :                          ERROR
                 case '*' : while ( (++dbs_pi).Exist() )
                            {
                              memcpy(sdbures->struct_name,dbs_sys_ident.GetArea(),ID_SIZE);
                              Copy();
                            }
                            while ( (++cs_pi).Exist() )
                            {
                              memcpy(sdbures->struct_name,cs_sys_ident.GetArea(),ID_SIZE);
                              Copy();
                            }
                            *sdbures->struct_name = '*';
                            break;
                 default  : if ( targ_dbs_pi(tstr.GetKey()).GetData() && sdburepl == REPL_none)
                                                     SDBERR(-932)
                            if ( targ_cs_pi(tstr.GetKey()).GetData() && sdburepl == REPL_none)
                                                     SDBERR(-933)
                            if ( term = Copy() )     ERROR
               }
               break;
    default  : if ( term = Copy() )                  ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CopyResDB - 


\return term - Termination code

\param  sdbuold - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyResDB"

logical CSUtilityHandle :: CopyResDB (UtilityHandle *sdbuold )
{
  Statistic   stat;
  char       *idkey;
  char        old_dict_path[129];
  char        new_dict_path[129];
  char        buffer[ID_SIZE];
  TypeKey     tkey;
  int32       maxcount;
  logical     copystr = YES;
  int32       lindx0;
  ODABAClient dummy_client;
  logical     term = NO;
BEGINSEQ
//  stat.Start();
  
  sdbures->accmode = PI_Read;
  sdbures->netopt  = YES;
  sdbudat->accmode = PI_Write;
  sdbudat->netopt  = NO;
  
  retain_sid   = YES;
  sdburepl     = REPL_none;
  sdbuinstonly = NO;
  
  *sdbures->extent_name = 0;
  *sdbures->object_name = 0;
  *sdbures->inst_key    = 0;
  
  *sdbudat->extent_name = 0;
  *sdbudat->object_name = 0;
  *sdbudat->struct_name = 0;
  *sdbudat->inst_key    = 0;

  sdbuinstonly = YES;
  if ( sdbudat->Open(dummy_client,PI_Write) )          ERROR  // zum Setzen der schema_version in neuer RESDB
  sdbudat->Close();
  sdbuinstonly = NO;
  
  strcpy(old_dict_path,sdbures->dict_path);
  strcpy(new_dict_path,sdbudat->dict_path);
  strcpy(sdbures->dict_path,sdbures->db_path);
  strcpy(sdbudat->dict_path,sdbudat->db_path);
  *sdbures->db_path = 0;
  *sdbudat->db_path = 0;

if ( copystr )
{
  if ( sdbures->Open(dummy_client) )                 ERROR 
  if ( sdbudat->Open(dummy_client) )                 ERROR
  
{
  PropertyHandle   dbs_pi(sdbures->dictionary,"SDB_Structure",PI_Read);  
                                                     SDBCERR
  PropertyHandle   cs_pi(sdbures->dictionary,"SDB_ValueList",PI_Read);  
                                                     SDBCERR

  tkey.Initialize("SDB_Structure",0);
  if ( dbs_pi(tkey.GetKey()).GetData() )
  {
    strcpy(sdbures->struct_name,"SDB_Structure");
    if ( Copy() )                                    ERROR
  }
 
  maxcount = cs_pi.GetCount();
  lindx0 = 0;
  while ( lindx0 < maxcount )
  {
    if ( cs_pi(lindx0++).GetData() )
    {
      memcpy(sdbures->struct_name,cs_pi.GetPropertyHandle("sys_ident")->GetArea(),ID_SIZE);
      Copy();
    }
  }
  
  dbs_pi.Cancel();
  maxcount = dbs_pi.GetCount();
  lindx0 = 0;
  while ( lindx0 < maxcount )
  {
    if ( dbs_pi(lindx0++).GetData() )
    {
      memcpy(sdbures->struct_name,dbs_pi.GetPropertyHandle("sys_ident")->GetArea(),ID_SIZE);
      Copy();
    }
  }
 
}
  
  if ( retain_schemaversion )  
    sdbudat->dictionary.UpdateVersion();
  
  if ( sdbures->Close() )                             ERROR
  if ( sdbudat->Close() )                             ERROR
}
  strcpy(sdbures->db_path,sdbures->dict_path);
  strcpy(sdbudat->db_path,sdbudat->dict_path);
  strcpy(sdbures->dict_path,old_dict_path);
  strcpy(sdbudat->dict_path,new_dict_path);
  
  *sdbures->struct_name = 0;
  strcpy(sdbures->inst_key,"*");
  sdbuinstonly = YES;
  
  if ( sdbures->Open(dummy_client) )                 ERROR
  if ( sdbudat->Open(dummy_client) )                 ERROR
    
  gvtxstb(sdbures->extent_name,"SDB_Extend",ID_SIZE);
  Copy();                                            SDBCERR
  gvtxstb(sdbures->extent_name,"SDB_CodeSet",ID_SIZE);
  Copy();                                            SDBCERR
  
  strcpy(sdbures->extent_name,"*");
   
  sdburepl     = REPL_instance;
  CopyDB();      // CopyObject() reicht auch!
  sdburepl     = REPL_relationships;
  CopyDB();      // CopyObject() reicht auch!
  
  if ( sdbures->Close() )                             ERROR
  if ( sdbudat->Close() )                             ERROR

RECOVER
  term = YES;
ENDSEQ
//  stat.Stop();
//  stat.Print("CopyRESDB",YES);
  return(term);
}

/******************************************************************************/
/**
\brief  Licence - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Licence"

logical CSUtilityHandle :: Licence ( )
{
  char                   *cpath;
  ODABAClient             dummy_client;
  logical                 term = NO;
BEGINSEQ
  SDBRESET
  
  cpath = GetSysVariable("DICTIONARY");
  
  DictionaryHandle   dict(dummy_client,cpath,PI_Write,YES);
  if ( SDBERROR )
  {
    SDBError().DisplayMessage();
    ERROR
  }
  
  DatabaseHandle     dbhandle(dict,PI_Write);
  if ( SDBERROR )
  {
    SDBError().DisplayMessage();
    ERROR
  }
  
  DBInfo             dbi(dbhandle.get_dbhandle()); 
  if ( SDBERROR )
  {
    SDBError().DisplayMessage();
    ERROR
  }
  
  dbi.SetLicence (dict.get_dictionary(),GetSysVariable("OWNER"));
  if ( SDBERROR )
  {
    SDBError().DisplayMessage();
    ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RecreateExtent - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RecreateExtent"

logical CSUtilityHandle :: RecreateExtent ( )
{
  DBExtend   *dbext_def;
  logical     term = NO;
BEGINSEQ
  if ( sdbudat->object_handle.GetHighObject() )      SDBERR(99)
  
  if ( !(dbext_def = sdbudat->dictionary.ProvideExtentDef(sdbudat->extent_name)) )
                                                     ERROR
  if ( dbext_def->GetBaseExtent((int16)0) )          SDBERR(99)
    
  if ( sdbudat->dbhandle.RecreateExtent(sdbudat->extent_name) )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  VersionSetup - 


\return term - Termination code

\param  version - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "VersionSetup"

logical CSUtilityHandle :: VersionSetup (uint16 version )
{
  logical                 renamed = NO;
  logical                 term = NO;
BEGINSEQ
  if ( !OpenSYS() )                                  ERROR
  if ( !sdbures || !sdbudat )                        ERROR
    
  if ( version == CUR_VERSION )
  {
    if ( !OpenRES() )                                ERROR
    PropertyHandle    ini_pi(sdbures->dbhandle,"ODABA2_ini",PI_Read);
                                                     SDBCERR
    if ( ini_pi(0L).GetData() && !ini_pi.GetPropertyHandle("odaba2_productio")->IsTrue() )
      version = ini_pi.GetPropertyHandle("odaba2_version")->GetInt();
    CloseRES();        
  }
  *sdbures = *sdbudat;
  strcpy(sdbures->extent_name,"*");
  strcpy(sdbures->inst_key,"*");
  sdbures->accmode = PI_Read;
  
  sdbudat->accmode = PI_Write;
  sdbudat->schema_version = version;
  
  sdburepl     = REPL_none;
  sdbuinstonly = YES;

  SDBEV2(sdbures->db_path,UNDEF)
  filextr(sdbures->db_path,"#_O");
  remove(sdbures->db_path);
  if ( rename(sdbudat->db_path,sdbures->db_path) )     SDBERR(217)
  renamed = YES;
  
  sdbures->online_version = NO;
  if ( sdbures->Open(connection) )                     ERROR
  sdbudat->online_version = NO;
  if ( sdbudat->Open(connection) )                     ERROR

  if ( CopyDB() )                                      ERROR

RECOVER
  term = YES;
ENDSEQ
  sdbures->Close();
  sdbudat->Close();
  if ( term && renamed ) // erst hier möglich, da Datenbank geschlossen sein muß
  {
    remove(sdbudat->db_path);
    rename(sdbures->db_path,sdbudat->db_path);
  }
  return(term);
}

/******************************************************************************/
/**
\brief  ~CSUtilityHandle - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CSUtilityHandle"

     CSUtilityHandle :: ~CSUtilityHandle ( )
{



}


