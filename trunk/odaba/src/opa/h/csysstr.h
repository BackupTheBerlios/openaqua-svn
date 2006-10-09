
 dictptr->ProvideStructDcl("CTX_DBBase",0,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,2,0,0,"",N,0,Y,N);
 dictptr->ProvideStructDcl("CTX_DataBase",0,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,1,0,0,"",N,0,Y,N);
 dictptr->ProvideStructDcl("CTX_Object",0,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,1,0,0,"",N,0,Y,N);
 dictptr->ProvideStructDcl("CTX_Structure",0,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,4,0,0,"",N,0,Y,N);
 dictptr->ProvideStructDcl("CTX_Property",0,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,1,0,0,"",N,0,Y,N);




 SDB_BaseStruct *bf_CTX_DBBase[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("CTX_Base","CTX_Base",RL_direct,0,0,1,"",N,N,0), N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),

              };

 SDB_Attribute *af_CTX_DBBase[] = {
              new SDB_Attribute(SDB_Member("resource","DBResource",RL_1,0,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("evt_context","CTX_DBBase",RL_1,0,0,1,"",N,N,0),N,0),

              };


 SDB_Reference **rf_CTX_DBBase = NULL;


 SDB_Relationship **pf_CTX_DBBase = NULL;
 SDB_BaseStruct *bf_CTX_DataBase[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("CTX_DBBase","CTX_DBBase",RL_direct,0,0,1,"",N,N,0), N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),

              };

 SDB_Attribute *af_CTX_DataBase[] = {
              new SDB_Attribute(SDB_Member("object_handle","ACObject",RL_1,0,0,0,"",N,N,0),N,0),

              };


 SDB_Reference **rf_CTX_DataBase = NULL;


 SDB_Relationship **pf_CTX_DataBase = NULL;
 SDB_BaseStruct *bf_CTX_Object[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("CTX_DBBase","CTX_DBBase",RL_direct,0,0,1,"",N,N,0), N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),

              };

 SDB_Attribute *af_CTX_Object[] = {
              new SDB_Attribute(SDB_Member("object_handle","ACObject",RL_1,0,0,1,"",N,N,0),N,0),

              };


 SDB_Reference **rf_CTX_Object = NULL;


 SDB_Relationship **pf_CTX_Object = NULL;
 SDB_BaseStruct *bf_CTX_Structure[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("CTX_DBBase","CTX_DBBase",RL_direct,0,0,1,"",N,N,0), N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),

              };

 SDB_Attribute *af_CTX_Structure[] = {
              new SDB_Attribute(SDB_Member("int_instance","binti",RL_1,0,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("old_instance","CHAR",RL_1,0,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("ref_context","CTX_Structure",RL_1,0,0,0,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("key_check","LOGICAL",RL_direct,0,0,0,"",N,N,0),N,0),

              };


 SDB_Reference **rf_CTX_Structure = NULL;


 SDB_Relationship **pf_CTX_Structure = NULL;
 SDB_BaseStruct *bf_CTX_Property[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("CTX_DBBase","CTX_DBBase",RL_direct,0,0,1,"",N,N,0), N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),

              };

 SDB_Attribute *af_CTX_Property[] = {
              new SDB_Attribute(SDB_Member("prop_node","node",RL_1,0,0,1,"",N,N,0),N,0),

              };


 SDB_Reference **rf_CTX_Property = NULL;


 SDB_Relationship **pf_CTX_Property = NULL;

 SDB_Key       *sk_CTX_DBBase = NULL;

 dictptr->SetupStructDef("CTX_DBBase",bf_CTX_DBBase,af_CTX_DBBase,rf_CTX_DBBase,pf_CTX_DBBase,sk_CTX_DBBase,0,8,0);
 SDB_Key       *sk_CTX_DataBase = NULL;

 dictptr->SetupStructDef("CTX_DataBase",bf_CTX_DataBase,af_CTX_DataBase,rf_CTX_DataBase,pf_CTX_DataBase,sk_CTX_DataBase,0,8,0);
 SDB_Key       *sk_CTX_Object = NULL;

 dictptr->SetupStructDef("CTX_Object",bf_CTX_Object,af_CTX_Object,rf_CTX_Object,pf_CTX_Object,sk_CTX_Object,0,8,0);
 SDB_Key       *sk_CTX_Structure = NULL;

 dictptr->SetupStructDef("CTX_Structure",bf_CTX_Structure,af_CTX_Structure,rf_CTX_Structure,pf_CTX_Structure,sk_CTX_Structure,0,8,0);
 SDB_Key       *sk_CTX_Property = NULL;

 dictptr->SetupStructDef("CTX_Property",bf_CTX_Property,af_CTX_Property,rf_CTX_Property,pf_CTX_Property,sk_CTX_Property,0,8,0);
