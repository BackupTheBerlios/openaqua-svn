 dictptr->ProvideStructDcl("ENUM_Value",619,UNDEF,UNDEF,TYP_Structure,ST_SYS,0,8,0,0,"ik_name",N,0,N,N);





 SDB_BaseStruct **bf_ENUM_Value = NULL;
 SDB_Attribute *af_ENUM_Value[] = {
              new SDB_Attribute(SDB_Member("id","INT",RL_direct,17,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("code","INT",RL_direct,10,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("name","CHAR",RL_direct,40,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("type","STRING",RL_1,40,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("display_name","STRING",RL_1,255,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("title","STRING",RL_1,255,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("description","STRING",RL_1,255,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("values","PropertyHandle",RL_direct,0,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_ENUM_Value = NULL;
 SDB_Relationship **pf_ENUM_Value = NULL;


 char         *kc_ENUM_Value_ik_code[] = {
              "code",
              "" };
 char         *kc_ENUM_Value_ik_display_name[] = {
              "display_name",
              "" };
 char         *kc_ENUM_Value_ik_name[] = {
              "name",
              "" };
 char         *kc_ENUM_Value_ik_type[] = {
              "type",
              "" };
 SDB_Key       sk_ENUM_Value[] = {
              SDB_Key("ik_code",kc_ENUM_Value_ik_code,1),
              SDB_Key("ik_display_name",kc_ENUM_Value_ik_display_name,4),
              SDB_Key("ik_name",kc_ENUM_Value_ik_name,2),
              SDB_Key("ik_type",kc_ENUM_Value_ik_type,3),
              };
 dictptr->SetupStructDef("ENUM_Value",bf_ENUM_Value,af_ENUM_Value,rf_ENUM_Value,pf_ENUM_Value,sk_ENUM_Value,4,8,0);

