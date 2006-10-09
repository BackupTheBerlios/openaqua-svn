 dictptr->ProvideStructDcl("vcls",0,UNDEF,UNDEF,TYP_Structure,ST_SYS,0,0,0,0,"",N,0,Y,N);
 dictptr->ProvideStructDcl("bsts",0,UNDEF,UNDEF,TYP_Structure,ST_SYS,0,2,0,0,"",N,0,N,N);
 dictptr->ProvideStructDcl("sts",0,UNDEF,UNDEF,TYP_Structure,ST_SYS,2,0,0,0,"",N,0,N,N);
 dictptr->ProvideStructDcl("acc",0,UNDEF,UNDEF,TYP_Structure,ST_SYS,0,3,0,0,"",N,0,N,N);
 dictptr->ProvideStructDcl("UserStates",0,UNDEF,UNDEF,TYP_Structure,ST_SYS,0,4,0,0,"",N,0,Y,N);
 dictptr->ProvideStructDcl("SystemStates",0,UNDEF,UNDEF,TYP_Structure,ST_SYS,0,4,0,0,"",N,0,Y,N);
 dictptr->ProvideStructDcl("CTX_Base",0,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,5,0,0,"",Y,0,Y,N);
 dictptr->ProvideStructDcl("ReferenceObject",1555,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,1,0,0,"",N,0,N,N);
 dictptr->ProvideStructDcl("srt",0,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,10,0,0,"",N,0,N,N);
 dictptr->ProvideStructDcl("fmcb",0,UNDEF,UNDEF,TYP_Structure,ST_SYS,0,30,0,0,"",N,0,N,N);
 dictptr->ProvideStructDcl("fmcl",0,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,0,0,0,"",N,0,N,N);
 dictptr->ProvideStructDcl("fcb",0,UNDEF,UNDEF,TYP_Structure,ST_SYS,0,1,0,0,"",N,0,N,N);
 dictptr->ProvideStructDcl("kfc",0,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,3,0,0,"",N,0,N,N);
 dictptr->ProvideStructDcl("kcb",0,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,5,0,0,"",N,0,N,N);
 dictptr->ProvideStructDcl("smcb",0,UNDEF,UNDEF,TYP_Structure,ST_SYS,0,15,0,0,"",N,0,N,N);

 dictptr->ProvideStructDcl("ActionType",82,UNDEF,UNDEF,TYP_Codeset,ST_CODE,0,2,0,0);
 dictptr->ProvideStructDcl("CTX_ProcessState",1047,UNDEF,UNDEF,TYP_Codeset,ST_CODE,0,2,0,0);
 dictptr->ProvideStructDcl("CTX_DisplayState",1046,UNDEF,UNDEF,TYP_Codeset,ST_CODE,0,2,0,0);
 dictptr->ProvideStructDcl("CTX_DataStates",1045,UNDEF,UNDEF,TYP_Codeset,ST_CODE,0,2,0,0);


 SDB_Index    *ri_ActionType_ActionType = NULL;
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("ActionType","ActionType",RL_direct,0,0,0,"",N,N,0),N,0,Y,Y,N,0,N,ri_ActionType_ActionType,0,N,N,Y),N,N,N,YES);
 SDB_Index    *ri_CTX_ProcessState_CTX_ProcessState = NULL;
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("CTX_ProcessState","CTX_ProcessState",RL_direct,0,0,0,"",N,N,0),N,0,Y,Y,N,0,N,ri_CTX_ProcessState_CTX_ProcessState,0,N,N,Y),N,N,N,YES);
 SDB_Index    *ri_CTX_DisplayState_CTX_DisplayState = NULL;
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("CTX_DisplayState","CTX_DisplayState",RL_direct,0,0,0,"",N,N,0),N,0,Y,Y,N,0,N,ri_CTX_DisplayState_CTX_DisplayState,0,N,N,Y),N,N,N,YES);
 SDB_Index    *ri_CTX_DataStates_CTX_DataStates = NULL;
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("CTX_DataStates","CTX_DataStates",RL_direct,0,0,0,"",N,N,0),N,0,Y,Y,N,0,N,ri_CTX_DataStates_CTX_DataStates,0,N,N,Y),N,N,N,YES);

 ENUM_Value *cs_ActionType[] = {
              new ENUM_Value(0,"ACT_undefined","", NULL, NULL, NULL),
              new ENUM_Value(65,"ACT_ParmAction","", NULL, NULL, NULL),
              new ENUM_Value(67,"ACT_Constant","", NULL, NULL, NULL),
              new ENUM_Value(68,"ACT_Document","", NULL, NULL, NULL),
              new ENUM_Value(69,"ACT_Expression","", NULL, NULL, NULL),
              new ENUM_Value(70,"ACT_Function","", NULL, NULL, NULL),
              new ENUM_Value(74,"ACT_Jump","", NULL, NULL, NULL),
              new ENUM_Value(77,"ACT_Menu","", NULL, NULL, NULL),
              new ENUM_Value(80,"ACT_Program","", NULL, NULL, NULL),
              new ENUM_Value(83,"ACT_Sequence","", NULL, NULL, NULL),
              new ENUM_Value(87,"ACT_Window","", NULL, NULL, NULL),
              new ENUM_Value(88,"ACT_Extended","", NULL, NULL, NULL),
              };
 dictptr->SetupEnumeration("ActionType",cs_ActionType,"",sizeof(cs_ActionType)/sizeof(void *));
 ENUM_Value *cs_CTX_ProcessState[] = {
              new ENUM_Value(0,"PRC_undefined","", NULL, NULL, NULL),
              new ENUM_Value(4,"PRC_Active","", NULL, NULL, NULL),
              new ENUM_Value(5,"PRC_Closed","", NULL, NULL, NULL),
              new ENUM_Value(6,"PRC_Opened","", NULL, NULL, NULL),
              new ENUM_Value(7,"PRC_Busy","", NULL, NULL, NULL),
              };
 dictptr->SetupEnumeration("CTX_ProcessState",cs_CTX_ProcessState,"",sizeof(cs_CTX_ProcessState)/sizeof(void *));
 ENUM_Value *cs_CTX_DisplayState[] = {
              new ENUM_Value(0,"DSP_undefined","", NULL, NULL, NULL),
              new ENUM_Value(1,"DSP_Hidden","", NULL, NULL, NULL),
              new ENUM_Value(2,"DSP_Disabled","", NULL, NULL, NULL),
              new ENUM_Value(3,"DSP_Visible","", NULL, NULL, NULL),
              };
 dictptr->SetupEnumeration("CTX_DisplayState",cs_CTX_DisplayState,"",sizeof(cs_CTX_DisplayState)/sizeof(void *));
 ENUM_Value *cs_CTX_DataStates[] = {
              new ENUM_Value(0,"DAT_undefined","", NULL, NULL, NULL),
              new ENUM_Value(1,"DAT_Clear","", NULL, NULL, NULL),
              new ENUM_Value(2,"DAT_Filled","", NULL, NULL, NULL),
              new ENUM_Value(3,"DAT_Modified","", NULL, NULL, NULL),
              new ENUM_Value(4,"DAT_Invalid","", NULL, NULL, NULL),
              };
 dictptr->SetupEnumeration("CTX_DataStates",cs_CTX_DataStates,"",sizeof(cs_CTX_DataStates)/sizeof(void *));

 SDB_BaseStruct **bf_vcls = NULL;
 SDB_Attribute **af_vcls = NULL;
 SDB_Reference **rf_vcls = NULL;
 SDB_Relationship **pf_vcls = NULL;

 SDB_BaseStruct **bf_bsts = NULL;
 SDB_Attribute *af_bsts[] = {
              new SDB_Attribute(SDB_Member("sts1","UINT",RL_direct,2,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("sts2","UINT",RL_direct,2,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_bsts = NULL;
 SDB_Relationship **pf_bsts = NULL;

 SDB_BaseStruct *bf_sts[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("vcls","vcls",RL_direct,0,0,1,"",N,N,0),N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("bsts","bsts",RL_direct,0,0,1,"",N,N,0),N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),
              };
 SDB_Attribute **af_sts = NULL;
 SDB_Reference **rf_sts = NULL;
 SDB_Relationship **pf_sts = NULL;

 SDB_BaseStruct **bf_acc = NULL;
 SDB_Attribute *af_acc[] = {
              new SDB_Attribute(SDB_Member("accinst","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("acccntrd","INT",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("acccntwt","INT",RL_direct,4,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_acc = NULL;
 SDB_Relationship **pf_acc = NULL;

 SDB_BaseStruct **bf_UserStates = NULL;
 SDB_Attribute *af_UserStates[] = {
              new SDB_Attribute(SDB_Member("state1","INT",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("state2","INT",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("state3","INT",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("object_states","CHAR",RL_direct,16,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_UserStates = NULL;
 SDB_Relationship **pf_UserStates = NULL;

 SDB_BaseStruct **bf_SystemStates = NULL;
 SDB_Attribute *af_SystemStates[] = {
              new SDB_Attribute(SDB_Member("display_state","CTX_DisplayState",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("data_state","CTX_DataStates",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("process_state","CTX_ProcessState",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("element_stati","CHAR",RL_direct,16,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_SystemStates = NULL;
 SDB_Relationship **pf_SystemStates = NULL;

 SDB_BaseStruct *bf_CTX_Base[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("vcls","vcls",RL_direct,0,0,1,"",N,N,0),N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),Y),
              };
 SDB_Attribute *af_CTX_Base[] = {
              new SDB_Attribute(SDB_Member("high_ctx","CTX_Base",RL_1,0,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("user_states","UserStates",RL_direct,0,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("intern_states","SystemStates",RL_direct,0,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("action_rc","INT",RL_direct,10,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("action_parms","NParm",RL_1,0,0,0,"",N,N,0),N,0),
              };
 SDB_Reference **rf_CTX_Base = NULL;
 SDB_Relationship **pf_CTX_Base = NULL;

 SDB_BaseStruct *bf_ReferenceObject[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("vcls","vcls",RL_direct,0,0,1,"",N,N,0),N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),
              };
 SDB_Attribute *af_ReferenceObject[] = {
              new SDB_Attribute(SDB_Member("use_count","INT",RL_direct,10,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_ReferenceObject = NULL;
 SDB_Relationship **pf_ReferenceObject = NULL;

 SDB_BaseStruct *bf_srt[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("sts","sts",RL_direct,0,0,1,"",N,N,0),N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),Y),
              };
 SDB_Attribute *af_srt[] = {
              new SDB_Attribute(SDB_Member("srtmaxe","INT",RL_direct,10,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("srtecnt","INT",RL_direct,10,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("srtelen","INT",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("srtklen","INT",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("srtkpos","INT",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("srtktyp","CHAR",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("srtexp","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("srtind","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("srtenty","CHAR",RL_1,0,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("srt_lock","RessourceLock",RL_1,0,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_srt = NULL;
 SDB_Relationship **pf_srt = NULL;

 SDB_BaseStruct **bf_fmcb = NULL;
 SDB_Attribute *af_fmcb[] = {
              new SDB_Attribute(SDB_Member("fmcbname","CHAR",RL_direct,40,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbtype","CHAR",RL_direct,40,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbnsid","INT",RL_direct,10,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbsize","UINT",RL_direct,10,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbdim","INT",RL_direct,10,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbprec","INT",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbrlev","INT",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbposn","INT",RL_direct,10,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbbyte","UINT",RL_direct,10,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbityp","INT",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbgentype","BIT",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbsmcb","smcb",RL_1,0,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbsyns","DLL(char)",RL_1,0,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcberr","INT",RL_direct,2,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbbstr","BIT",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbunicode","BIT",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbvar","BIT",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbtrans","BIT",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbopt","BIT",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbempty","BIT",RL_direct,1,0,0,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbinwk","BIT",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbold","BIT",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbic","BIT",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbdesc","BIT",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbcnst","BIT",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbstat","BIT",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbvirt","BIT",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbinit","BIT",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcballoc_opt","BIT",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("fmcbsensi","BIT",RL_direct,1,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_fmcb = NULL;
 SDB_Relationship **pf_fmcb = NULL;

 SDB_BaseStruct *bf_fmcl[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("GSRT(fmcb)","fmcb",RL_direct,0,0,1,"GSRT",N,N,0),N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),Y),
              };
 SDB_Attribute **af_fmcl = NULL;
 SDB_Reference **rf_fmcl = NULL;
 SDB_Relationship **pf_fmcl = NULL;

 SDB_BaseStruct **bf_fcb = NULL;
 SDB_Attribute *af_fcb[] = {
              new SDB_Attribute(SDB_Member("fcbfmcb","fmcb",RL_1,0,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_fcb = NULL;
 SDB_Relationship **pf_fcb = NULL;

 SDB_BaseStruct *bf_kfc[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("fcb","fcb",RL_direct,0,0,1,"",N,N,0),N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),Y),
              };
 SDB_Attribute *af_kfc[] = {
              new SDB_Attribute(SDB_Member("kfcfmcb","fmcb",RL_1,0,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("kfcpos","INT",RL_direct,10,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("key_name","STRING",RL_1,0,0,0,"",N,N,0),N,0),
              };
 SDB_Reference **rf_kfc = NULL;
 SDB_Relationship **pf_kfc = NULL;

 SDB_BaseStruct *bf_kcb[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("GSCB(kfc)","kfc",RL_direct,0,0,1,"GSCB",N,N,0),N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),Y),
              };
 SDB_Attribute *af_kcb[] = {
              new SDB_Attribute(SDB_Member("kcbarea","CHAR",RL_1,0,0,0,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("kcbgfmcb","fmcb",RL_1,0,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("kcbgoff","INT",RL_direct,10,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("key_num","INT",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("is_pd","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_kcb = NULL;
 SDB_Relationship **pf_kcb = NULL;

 SDB_BaseStruct **bf_smcb = NULL;
 SDB_Attribute *af_smcb[] = {
              new SDB_Attribute(SDB_Member("smcbname","CHAR",RL_direct,40,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("smcbnsid","INT",RL_direct,10,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("smcbityp","INT",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("smcbstyp","INT",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("smcbatyp","INT",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("smcberr","INT",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("smcbsts","sts",RL_direct,0,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("is_pd","INT",RL_direct,2,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("defined_align","INT",RL_direct,2,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("plattform_align","INT",RL_direct,2,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("smcbtlen","INT",RL_direct,10,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("smcbfmcl","fmcl",RL_1,0,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("smcbidky","kcb",RL_1,0,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("smcbskey","kcb",RL_1,0,0,1,"DLL",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("smcbacc","acc",RL_1,0,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_smcb = NULL;
 SDB_Relationship **pf_smcb = NULL;


 SDB_Key       *sk_vcls = NULL;
 dictptr->SetupStructDef("vcls",bf_vcls,af_vcls,rf_vcls,pf_vcls,sk_vcls,0,4,0);

 SDB_Key       *sk_bsts = NULL;
 dictptr->SetupStructDef("bsts",bf_bsts,af_bsts,rf_bsts,pf_bsts,sk_bsts,0,2,0);

 SDB_Key       *sk_sts = NULL;
 dictptr->SetupStructDef("sts",bf_sts,af_sts,rf_sts,pf_sts,sk_sts,0,1,0);

 SDB_Key       *sk_acc = NULL;
 dictptr->SetupStructDef("acc",bf_acc,af_acc,rf_acc,pf_acc,sk_acc,0,8,0);

 SDB_Key       *sk_UserStates = NULL;
 dictptr->SetupStructDef("UserStates",bf_UserStates,af_UserStates,rf_UserStates,pf_UserStates,sk_UserStates,0,8,0);

 SDB_Key       *sk_SystemStates = NULL;
 dictptr->SetupStructDef("SystemStates",bf_SystemStates,af_SystemStates,rf_SystemStates,pf_SystemStates,sk_SystemStates,0,8,0);

 SDB_Key       *sk_CTX_Base = NULL;
 dictptr->SetupStructDef("CTX_Base",bf_CTX_Base,af_CTX_Base,rf_CTX_Base,pf_CTX_Base,sk_CTX_Base,0,8,0);

 SDB_Key       *sk_ReferenceObject = NULL;
 dictptr->SetupStructDef("ReferenceObject",bf_ReferenceObject,af_ReferenceObject,rf_ReferenceObject,pf_ReferenceObject,sk_ReferenceObject,0,8,0);

 SDB_Key       *sk_srt = NULL;
 dictptr->SetupStructDef("srt",bf_srt,af_srt,rf_srt,pf_srt,sk_srt,0,8,0);

 SDB_Key       *sk_fmcb = NULL;
 dictptr->SetupStructDef("fmcb",bf_fmcb,af_fmcb,rf_fmcb,pf_fmcb,sk_fmcb,0,8,0);

 SDB_Key       *sk_fmcl = NULL;
 dictptr->SetupStructDef("fmcl",bf_fmcl,af_fmcl,rf_fmcl,pf_fmcl,sk_fmcl,0,8,0);

 SDB_Key       *sk_fcb = NULL;
 dictptr->SetupStructDef("fcb",bf_fcb,af_fcb,rf_fcb,pf_fcb,sk_fcb,0,8,0);

 SDB_Key       *sk_kfc = NULL;
 dictptr->SetupStructDef("kfc",bf_kfc,af_kfc,rf_kfc,pf_kfc,sk_kfc,0,8,0);

 SDB_Key       *sk_kcb = NULL;
 dictptr->SetupStructDef("kcb",bf_kcb,af_kcb,rf_kcb,pf_kcb,sk_kcb,0,8,0);

 SDB_Key       *sk_smcb = NULL;
 dictptr->SetupStructDef("smcb",bf_smcb,af_smcb,rf_smcb,pf_smcb,sk_smcb,0,8,0);

