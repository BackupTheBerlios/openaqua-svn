 dictptr->ProvideStructDcl("FileHandle",0,UNDEF,UNDEF,TYP_Structure,ST_SYS,0,1,0,0,"",N,0,N,N);
 dictptr->ProvideStructDcl("DBObjectHandle",1547,UNDEF,UNDEF,TYP_Structure,ST_SYS,0,1,0,0,"",N,0,N,N);
 dictptr->ProvideStructDcl("DatabaseHandle",1546,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,0,0,0,"",N,0,N,N);
 dictptr->ProvideStructDcl("DictionaryHandle",1545,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,0,0,0,"",N,0,N,N);
 dictptr->ProvideStructDcl("PropertyHandle",1544,UNDEF,UNDEF,TYP_Structure,ST_SYS,0,1,0,0,"",N,0,N,N);





 SDB_BaseStruct **bf_FileHandle = NULL;

 SDB_Attribute *af_FileHandle[] = {
              new SDB_Attribute(SDB_Member("file","File",RL_1,0,0,1,"",N,N,0),N,0),

              };


 SDB_Reference **rf_FileHandle = NULL;


 SDB_Relationship **pf_FileHandle = NULL;
 SDB_BaseStruct **bf_DBObjectHandle = NULL;

 SDB_Attribute *af_DBObjectHandle[] = {
              new SDB_Attribute(SDB_Member("object_handle","ACObject",RL_1,0,0,1,"",N,N,0),N,0),

              };


 SDB_Reference **rf_DBObjectHandle = NULL;


 SDB_Relationship **pf_DBObjectHandle = NULL;
 SDB_BaseStruct *bf_DatabaseHandle[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("DBObjectHandle","DBObjectHandle",RL_direct,0,0,1,"",N,N,0), N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),

              };

 SDB_Attribute **af_DatabaseHandle = NULL;


 SDB_Reference **rf_DatabaseHandle = NULL;


 SDB_Relationship **pf_DatabaseHandle = NULL;
 SDB_BaseStruct *bf_DictionaryHandle[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("DatabaseHandle","DatabaseHandle",RL_direct,0,0,1,"",N,N,0), N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),

              };

 SDB_Attribute **af_DictionaryHandle = NULL;


 SDB_Reference **rf_DictionaryHandle = NULL;


 SDB_Relationship **pf_DictionaryHandle = NULL;
 SDB_BaseStruct **bf_PropertyHandle = NULL;

 SDB_Attribute *af_PropertyHandle[] = {
              new SDB_Attribute(SDB_Member("nodeptr","node",RL_1,0,0,1,"",N,N,0),N,0),

              };


 SDB_Reference **rf_PropertyHandle = NULL;


 SDB_Relationship **pf_PropertyHandle = NULL;

 SDB_Key       *sk_FileHandle = NULL;

 dictptr->SetupStructDef("FileHandle",bf_FileHandle,af_FileHandle,rf_FileHandle,pf_FileHandle,sk_FileHandle,0,8,0);
 SDB_Key       *sk_DBObjectHandle = NULL;

 dictptr->SetupStructDef("DBObjectHandle",bf_DBObjectHandle,af_DBObjectHandle,rf_DBObjectHandle,pf_DBObjectHandle,sk_DBObjectHandle,0,8,0);
 SDB_Key       *sk_DatabaseHandle = NULL;

 dictptr->SetupStructDef("DatabaseHandle",bf_DatabaseHandle,af_DatabaseHandle,rf_DatabaseHandle,pf_DatabaseHandle,sk_DatabaseHandle,0,8,0);
 SDB_Key       *sk_DictionaryHandle = NULL;

 dictptr->SetupStructDef("DictionaryHandle",bf_DictionaryHandle,af_DictionaryHandle,rf_DictionaryHandle,pf_DictionaryHandle,sk_DictionaryHandle,0,8,0);
 SDB_Key       *sk_PropertyHandle = NULL;

 dictptr->SetupStructDef("PropertyHandle",bf_PropertyHandle,af_PropertyHandle,rf_PropertyHandle,pf_PropertyHandle,sk_PropertyHandle,0,8,0);
