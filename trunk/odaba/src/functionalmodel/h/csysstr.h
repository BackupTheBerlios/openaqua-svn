 dictptr->ProvideStructDcl("FileMemo",111,UNDEF,UNDEF,TYP_Structure,ST_SYS,0,4,1,0,"ik_FileMemo",N,0,N,N);
 dictptr->ProvideStructDcl("ODC_Error",314,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,2,0,2,"ik_errnum",N,18,N,N);
 dictptr->ProvideStructDcl("ODC_ErrorClass",312,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,0,0,2,"ik_Ident",N,18,N,N);
 dictptr->ProvideStructDcl("ODC_BaseContext",116,UNDEF,UNDEF,TYP_Structure,ST_SYS,0,2,0,0,"ik_ODC_BaseCtx",Y,2,Y,N);
 dictptr->ProvideStructDcl("ODC_Environment",119,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,3,3,1,"ik_Ident",N,18,N,N);
 dictptr->ProvideStructDcl("ODC_Include",110,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,0,0,12,"ik_ODC_Include",N,18,N,N);
 dictptr->ProvideStructDcl("ODC_Variable",106,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,5,0,5,"ik_Ident",N,18,N,N);
 dictptr->ProvideStructDcl("ODC_FunctImp",105,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,11,6,4,"ik_Ident",N,18,N,N);
 dictptr->ProvideStructDcl("ODC_Function",104,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,8,0,1,"ik_Ident",N,18,N,N);
 dictptr->ProvideStructDcl("ODC_PFunction",103,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,4,0,7,"ik_Ident",N,8,N,N);
 dictptr->ProvideStructDcl("ODC_FunctGroup",183,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,0,0,2,"ik_Ident",N,18,N,N);
 dictptr->ProvideStructDcl("ODC_ImpClass",98,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,12,1,13,"ik_Ident8",N,18,N,N);
 dictptr->ProvideStructDcl("ODC_Main",128,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,4,0,2,"ik_Ident",N,18,N,N);
 dictptr->ProvideStructDcl("ODC_Executable",126,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,2,1,2,"ik_Ident",N,18,N,N);
 dictptr->ProvideStructDcl("ODC_ViewPath",396,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,3,0,0,"ik_Ident",N,18,N,N);
 dictptr->ProvideStructDcl("ODC_View",360,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,0,4,1,"ik_Ident8",Y,18,Y,N);
 dictptr->ProvideStructDcl("ODC_ProjRef",115,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,4,0,0,"ik_Ident",N,18,N,N);
 dictptr->ProvideStructDcl("ODC_NamedObject",269,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,1,0,1,"ik_Ident",N,0,N,N);
 dictptr->ProvideStructDcl("ODC_Module",311,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,8,0,12,"ik_Ident",N,18,N,N);
 dictptr->ProvideStructDcl("ODC_Project",113,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,3,2,6,"ik_Ident",N,18,N,N);
 dictptr->ProvideStructDcl("ODC_DBIdent",371,UNDEF,UNDEF,TYP_Structure,ST_SYS,0,3,0,0,"",N,5,N,N);
 dictptr->ProvideStructDcl("ODC_DBLicence",370,UNDEF,UNDEF,TYP_Structure,ST_SYS,0,9,0,0,"",N,5,N,N);
 dictptr->ProvideStructDcl("ODC_ApplLicence",383,UNDEF,UNDEF,TYP_Structure,ST_SYS,0,2,0,0,"ik_name",N,5,N,N);
 dictptr->ProvideStructDcl("ODC_Database",369,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,4,1,0,"ik_Ident",N,18,N,N);

 dictptr->ProvideStructDcl("MethodTypes",124,UNDEF,UNDEF,TYP_Codeset,ST_CODE,0,0,0,0);
 dictptr->ProvideStructDcl("ProcessingTypes",125,UNDEF,UNDEF,TYP_Codeset,ST_CODE,0,0,0,0);
 dictptr->ProvideStructDcl("CompileStates",100,UNDEF,UNDEF,TYP_Codeset,ST_CODE,0,0,0,0);
 dictptr->ProvideStructDcl("ClassModLevel",101,UNDEF,UNDEF,TYP_Codeset,ST_CODE,0,0,0,0);
 dictptr->ProvideStructDcl("ProgramLanguage",102,UNDEF,UNDEF,TYP_Codeset,ST_CODE,0,0,0,0);
 dictptr->ProvideStructDcl("RTTI_Types",123,UNDEF,UNDEF,TYP_Codeset,ST_CODE,0,0,0,0);
 dictptr->ProvideStructDcl("ContextTypes",117,UNDEF,UNDEF,TYP_Codeset,ST_CODE,0,0,0,0);

 SDB_Index     ri_FileMemo_FileMemo[] = {
               SDB_Index("ik_FileMemo",SET_LARG,Y,N,Y,N,0),
               SDB_Index("sk_FileMemo",SET_LARG,N,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("FileMemo","FileMemo",RL_direct,0,0,0,"",N,N,0),N,0,Y,Y,N,0,N,ri_FileMemo_FileMemo,2,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_ODC_Error_ODC_Error[] = {
               SDB_Index("ik_errnum",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("ODC_Error","ODC_Error",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_Error_ODC_Error,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_ODC_ErrorClass_ODC_ErrorClass[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("ODC_ErrorClass","ODC_ErrorClass",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_ErrorClass_ODC_ErrorClass,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_ODC_BaseContext_ODC_BaseContext[] = {
               SDB_Index("ik_ODC_BaseCtx",SET_SMAL,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("ODC_BaseContext","ODC_BaseContext",RL_direct,0,0,0,"",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_BaseContext_ODC_BaseContext,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_ODC_Environment_ODC_Environment[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("ODC_Environment","ODC_Environment",RL_direct,0,0,0,"",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_Environment_ODC_Environment,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_ODC_Include_ODC_Include[] = {
               SDB_Index("ik_ODC_Include",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("ODC_Include","ODC_Include",RL_direct,0,0,0,"",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_Include_ODC_Include,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_ODC_Variable_ODC_Variable[] = {
               SDB_Index("ik_Ident",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("ODC_Variable","ODC_Variable",RL_direct,0,0,0,"",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_Variable_ODC_Variable,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_ODC_FunctImp_ODC_FunctImp[] = {
               SDB_Index("ik_Ident",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("ODC_FunctImp","ODC_FunctImp",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_FunctImp_ODC_FunctImp,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_ODC_Function_ODC_Function[] = {
               SDB_Index("ik_Ident",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("ODC_Function","ODC_Function",RL_direct,0,0,0,"",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_Function_ODC_Function,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_ODC_PFunction_ODC_PFunction[] = {
               SDB_Index("ik_Ident",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("ODC_PFunction","ODC_PFunction",RL_direct,0,0,0,"",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_PFunction_ODC_PFunction,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_ODC_FunctGroup_ODC_FunctGroup[] = {
               SDB_Index("ik_Ident",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("ODC_FunctGroup","ODC_FunctGroup",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_FunctGroup_ODC_FunctGroup,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_ODC_ImpClass_ODC_ImpClass[] = {
               SDB_Index("ik_Ident8",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("ODC_ImpClass","ODC_ImpClass",RL_direct,0,0,0,"",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_ImpClass_ODC_ImpClass,1,N,N,N),N,N,N,YES);
 SDB_Index     ri_ODC_Main_ODC_Main[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("ODC_Main","ODC_Main",RL_direct,0,0,0,"",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_Main_ODC_Main,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_ODC_Executable_ODC_Executable[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("ODC_Executable","ODC_Executable",RL_direct,0,0,0,"",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_Executable_ODC_Executable,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_ODC_ViewPath_ODC_ViewPath[] = {
               SDB_Index("ik_Ident",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("ODC_ViewPath","ODC_ViewPath",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_ViewPath_ODC_ViewPath,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_ODC_View_ODC_View[] = {
               SDB_Index("ik_Ident8",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("ODC_View","ODC_View",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_View_ODC_View,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_ODC_ProjRef_ODC_ProjRef[] = {
               SDB_Index("ik_Ident",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("ODC_ProjRef","ODC_ProjRef",RL_direct,0,0,0,"",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_ProjRef_ODC_ProjRef,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_ODC_NamedObject_ODC_NamedObject[] = {
               SDB_Index("ik_Ident",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("ODC_NamedObject","ODC_NamedObject",RL_direct,0,0,0,"",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_NamedObject_ODC_NamedObject,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_ODC_Module_ODC_Module[] = {
               SDB_Index("ik_Ident",SET_LARG,Y,N,Y,N,0),
               SDB_Index("ik_Ident8",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("ODC_Module","ODC_Module",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_Module_ODC_Module,2,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_ODC_Project_ODC_Project[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
               SDB_Index("ik_Ident8",SET_SMAL,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("ODC_Project","ODC_Project",RL_direct,0,0,0,"",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_Project_ODC_Project,2,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_ODC_Database_ODC_Database[] = {
               SDB_Index("ik_Ident",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("ODC_Database","ODC_Database",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_Database_ODC_Database,1,Y,Y,N),N,N,N,YES);

 SDB_Index    *ri_MethodTypes_MethodTypes = NULL;
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("MethodTypes","MethodTypes",RL_direct,0,0,0,"",N,N,0),N,0,Y,Y,N,0,N,ri_MethodTypes_MethodTypes,0,N,N,N),N,N,N,YES);
 SDB_Index    *ri_ProcessingTypes_ProcessingTypes = NULL;
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("ProcessingTypes","ProcessingTypes",RL_direct,0,0,0,"",N,N,0),N,0,Y,Y,N,0,N,ri_ProcessingTypes_ProcessingTypes,0,N,N,N),N,N,N,YES);
 SDB_Index    *ri_CompileStates_CompileStates = NULL;
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("CompileStates","CompileStates",RL_direct,0,0,0,"",N,N,0),N,0,Y,Y,N,0,N,ri_CompileStates_CompileStates,0,N,N,N),N,N,N,YES);
 SDB_Index    *ri_ClassModLevel_ClassModLevel = NULL;
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("ClassModLevel","ClassModLevel",RL_direct,0,0,0,"",N,N,0),N,0,Y,Y,N,0,N,ri_ClassModLevel_ClassModLevel,0,N,N,N),N,N,N,YES);
 SDB_Index    *ri_ProgramLanguage_ProgramLanguage = NULL;
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("ProgramLanguage","ProgramLanguage",RL_direct,0,0,0,"",N,N,0),N,0,Y,Y,N,0,N,ri_ProgramLanguage_ProgramLanguage,0,N,N,N),N,N,N,YES);
 SDB_Index    *ri_RTTI_Types_RTTI_Types = NULL;
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("RTTI_Types","RTTI_Types",RL_direct,0,0,0,"",N,N,0),N,0,Y,Y,N,0,N,ri_RTTI_Types_RTTI_Types,0,N,N,N),N,N,N,YES);
 SDB_Index    *ri_ContextTypes_ContextTypes = NULL;
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("ContextTypes","ContextTypes",RL_direct,0,0,0,"",N,N,0),N,0,Y,Y,N,0,N,ri_ContextTypes_ContextTypes,0,N,N,N),N,N,N,YES);


 ENUM_Value *cs_MethodTypes[] = {
              new ENUM_Value(70,"MT_CPPFunction","", NULL, NULL, NULL),
              new ENUM_Value(84,"MT_DOCTemplate","", NULL, NULL, NULL),
              new ENUM_Value(69,"MT_OQLExpression","", NULL, NULL, NULL),
              new ENUM_Value(0,"MT_Undefined","", NULL, NULL, NULL),
              };
 dictptr->SetupEnumeration("MethodTypes",cs_MethodTypes,"",sizeof(cs_MethodTypes)/sizeof(void *));

 ENUM_Value *cs_ProcessingTypes[] = {
              new ENUM_Value(1,"PRCT_collection","", NULL, NULL, NULL),
              new ENUM_Value(0,"PRCT_instance","", NULL, NULL, NULL),
              new ENUM_Value(-1,"PRCT_undefined","", NULL, NULL, NULL),
              };
 dictptr->SetupEnumeration("ProcessingTypes",cs_ProcessingTypes,"",sizeof(cs_ProcessingTypes)/sizeof(void *));

 ENUM_Value *cs_CompileStates[] = {
              new ENUM_Value(2,"CPS_failed","", NULL, NULL, NULL),
              new ENUM_Value(3,"CPS_ready","", NULL, NULL, NULL),
              new ENUM_Value(1,"CPS_requested","", NULL, NULL, NULL),
              new ENUM_Value(0,"CPS_undefined","", NULL, NULL, NULL),
              };
 dictptr->SetupEnumeration("CompileStates",cs_CompileStates,"",sizeof(cs_CompileStates)/sizeof(void *));

 ENUM_Value *cs_ClassModLevel[] = {
              new ENUM_Value(2,"CML_Intern","", NULL, NULL, NULL),
              new ENUM_Value(1,"CML_Member","", NULL, NULL, NULL),
              new ENUM_Value(0,"CML_undefined","", NULL, NULL, NULL),
              };
 dictptr->SetupEnumeration("ClassModLevel",cs_ClassModLevel,"",sizeof(cs_ClassModLevel)/sizeof(void *));

 ENUM_Value *cs_ProgramLanguage[] = {
              new ENUM_Value(2,"PL_ASM","", NULL, NULL, NULL),
              new ENUM_Value(3,"PL_C","", NULL, NULL, NULL),
              new ENUM_Value(4,"PL_COM_IDL","", NULL, NULL, NULL),
              new ENUM_Value(5,"PL_CORBA_IDL","", NULL, NULL, NULL),
              new ENUM_Value(1,"PL_CPP","", NULL, NULL, NULL),
              new ENUM_Value(0,"PL_undefined","", NULL, NULL, NULL),
              };
 dictptr->SetupEnumeration("ProgramLanguage",cs_ProgramLanguage,"",sizeof(cs_ProgramLanguage)/sizeof(void *));

 ENUM_Value *cs_RTTI_Types[] = {
              new ENUM_Value(2,"RTTI_can_create","", NULL, NULL, NULL),
              new ENUM_Value(1,"RTTI_cannot_create","", NULL, NULL, NULL),
              new ENUM_Value(0,"RTTI_none","", NULL, NULL, NULL),
              };
 dictptr->SetupEnumeration("RTTI_Types",cs_RTTI_Types,"",sizeof(cs_RTTI_Types)/sizeof(void *));

 ENUM_Value *cs_ContextTypes[] = {
              new ENUM_Value(1,"FNCC_APP","", NULL, NULL, NULL),
              new ENUM_Value(3,"FNCC_CTL","", NULL, NULL, NULL),
              new ENUM_Value(4,"FNCC_DOC","", NULL, NULL, NULL),
              new ENUM_Value(5,"FNCC_PRJ","", NULL, NULL, NULL),
              new ENUM_Value(2,"FNCC_WIN","", NULL, NULL, NULL),
              };
 dictptr->SetupEnumeration("ContextTypes",cs_ContextTypes,"",sizeof(cs_ContextTypes)/sizeof(void *));

 SDB_BaseStruct **bf_FileMemo = NULL;
 SDB_Attribute *af_FileMemo[] = {
              new SDB_Attribute(SDB_Member("file_name","CHAR",RL_direct,8,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("file_ext","CHAR",RL_direct,3,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("file_path","STRING",RL_direct,64,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("internal","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              };
 SDB_Index    *ri_FileMemo_file_memo = NULL;
 SDB_Reference *rf_FileMemo[] = {
              new SDB_Reference(SDB_Member("file_memo","MEMO",RL_direct,8192,0,1,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_FileMemo_file_memo,0,N,N,N),
              };
 SDB_Relationship **pf_FileMemo = NULL;

 SDB_BaseStruct *bf_ODC_Error[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("SDB_Resource","SDB_Resource",RL_direct,0,0,1,"",N,N,0),N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),
              };
 SDB_Attribute *af_ODC_Error[] = {
              new SDB_Attribute(SDB_Member("_errnum","INT",RL_direct,10,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("_errtyp","CHAR",RL_direct,40,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_ODC_Error = NULL;
 SDB_Index     ri_ODC_Error_modules[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Error_error_class[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Relationship *pf_ODC_Error[] = {
              new SDB_Relationship(SDB_Reference(SDB_Member("modules","ODC_Module",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Error_modules,1,Y,Y,N),Y,N,"errors",N,""),
              new SDB_Relationship(SDB_Reference(SDB_Member("error_class","ODC_ErrorClass",RL_direct,0,0,1,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Error_error_class,1,Y,N,N),Y,N,"errors",N,""),
              };

 SDB_BaseStruct *bf_ODC_ErrorClass[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("SDB_Resource","SDB_Resource",RL_direct,0,0,1,"",N,N,0),N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),
              };
 SDB_Attribute **af_ODC_ErrorClass = NULL;
 SDB_Reference **rf_ODC_ErrorClass = NULL;
 SDB_Index     ri_ODC_ErrorClass_errors[] = {
               SDB_Index("ik_errnum",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_ErrorClass_modules[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Relationship *pf_ODC_ErrorClass[] = {
              new SDB_Relationship(SDB_Reference(SDB_Member("errors","ODC_Error",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_ErrorClass_errors,1,Y,N,N),N,N,"error_class",N,""),
              new SDB_Relationship(SDB_Reference(SDB_Member("modules","ODC_Module",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_ErrorClass_modules,1,Y,N,N),Y,N,"error_class",N,"ODC_Module"),
              };

 SDB_BaseStruct **bf_ODC_BaseContext = NULL;
 SDB_Attribute *af_ODC_BaseContext[] = {
              new SDB_Attribute(SDB_Member("classname","CHAR",RL_direct,40,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("contexttype","ContextTypes",RL_direct,2,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_ODC_BaseContext = NULL;
 SDB_Relationship **pf_ODC_BaseContext = NULL;

 SDB_BaseStruct *bf_ODC_Environment[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("SDB_Resource","SDB_Resource",RL_direct,40,0,1,"",N,N,0),N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),
              };
 SDB_Attribute *af_ODC_Environment[] = {
              new SDB_Attribute(SDB_Member("env_title","STRING",RL_direct,50,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("link_spec","STRING",RL_direct,396,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("lib_manager","STRING",RL_direct,160,0,1,"",N,N,0),N,0),
              };
 SDB_Index    *ri_ODC_Environment_help_spec = NULL;
 SDB_Index    *ri_ODC_Environment_resc_spec = NULL;
 SDB_Index    *ri_ODC_Environment_comp_spec = NULL;
 SDB_Reference *rf_ODC_Environment[] = {
              new SDB_Reference(SDB_Member("help_spec","MEMO",RL_direct,1024,0,1,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_Environment_help_spec,0,N,N,N),
              new SDB_Reference(SDB_Member("resc_spec","MEMO",RL_direct,1024,0,1,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_Environment_resc_spec,0,N,N,N),
              new SDB_Reference(SDB_Member("comp_spec","MEMO",RL_direct,1024,0,1,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_Environment_comp_spec,0,N,N,N),
              };
 SDB_Index     ri_ODC_Environment_env_ref[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Relationship *pf_ODC_Environment[] = {
              new SDB_Relationship(SDB_Reference(SDB_Member("env_ref","ODC_Project",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Environment_env_ref,1,Y,N,N),Y,N,"environment",N,"ODC_Project"),
              };

 SDB_BaseStruct *bf_ODC_Include[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("FileMemo","FileMemo",RL_direct,0,0,1,"",N,N,0),N,0,N,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),
              };
 SDB_Attribute **af_ODC_Include = NULL;
 SDB_Reference **rf_ODC_Include = NULL;
 SDB_Index     ri_ODC_Include_projects[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Include_systemincl_ref[] = {
               SDB_Index("ik_Ident8",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Include_beg_class_incls[] = {
               SDB_Index("ik_Ident8",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Include_after_class_incls[] = {
               SDB_Index("ik_Ident8",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Include_userincl_ref[] = {
               SDB_Index("ik_Ident8",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Include_end_class_incls[] = {
               SDB_Index("ik_Ident8",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Include_before_impls_incls[] = {
               SDB_Index("__IDENTITY",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Include_after_impls_incls[] = {
               SDB_Index("__IDENTITY",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Include_before_impl_incls[] = {
               SDB_Index("__IDENTITY",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Include_after_impl_incls[] = {
               SDB_Index("__IDENTITY",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Include_user_main_incls[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Include_system_main_incls[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Relationship *pf_ODC_Include[] = {
              new SDB_Relationship(SDB_Reference(SDB_Member("projects","ODC_Project",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Include_projects,1,Y,N,N),Y,N,"proj_include",N,""),
              new SDB_Relationship(SDB_Reference(SDB_Member("systemincl_ref","ODC_ImpClass",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Include_systemincl_ref,1,Y,N,N),Y,N,"incl_system",N,""),
              new SDB_Relationship(SDB_Reference(SDB_Member("beg_class_incls","ODC_ImpClass",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Include_beg_class_incls,1,Y,N,N),Y,N,"incl_beg_class",N,""),
              new SDB_Relationship(SDB_Reference(SDB_Member("after_class_incls","ODC_ImpClass",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Include_after_class_incls,1,Y,N,N),Y,N,"incl_after_class",N,""),
              new SDB_Relationship(SDB_Reference(SDB_Member("userincl_ref","ODC_ImpClass",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Include_userincl_ref,1,Y,N,N),Y,N,"incl_user",N,""),
              new SDB_Relationship(SDB_Reference(SDB_Member("end_class_incls","ODC_ImpClass",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Include_end_class_incls,1,Y,N,N),Y,N,"incl_end_class",N,""),
              new SDB_Relationship(SDB_Reference(SDB_Member("before_impls_incls","ODC_PFunction",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,Y,ri_ODC_Include_before_impls_incls,1,Y,N,N),Y,N,"incl_before_impls",N,""),
              new SDB_Relationship(SDB_Reference(SDB_Member("after_impls_incls","ODC_PFunction",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,Y,ri_ODC_Include_after_impls_incls,1,Y,N,N),Y,N,"incl_after_impls",N,""),
              new SDB_Relationship(SDB_Reference(SDB_Member("before_impl_incls","ODC_FunctImp",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Include_before_impl_incls,1,Y,N,N),Y,N,"incl_before_impl",N,""),
              new SDB_Relationship(SDB_Reference(SDB_Member("after_impl_incls","ODC_FunctImp",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Include_after_impl_incls,1,Y,N,N),Y,N,"incl_after_impl",N,""),
              new SDB_Relationship(SDB_Reference(SDB_Member("user_main_incls","ODC_Main",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Include_user_main_incls,1,Y,N,N),Y,N,"mincl_user",N,""),
              new SDB_Relationship(SDB_Reference(SDB_Member("system_main_incls","ODC_Main",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Include_system_main_incls,1,Y,N,N),Y,N,"mincl_system",N,""),
              };

 SDB_BaseStruct *bf_ODC_Variable[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("SDB_Member","SDB_Member",RL_direct,0,0,1,"",N,N,0),N,0,N,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),
              };
 SDB_Attribute *af_ODC_Variable[] = {
              new SDB_Attribute(SDB_Member("initialize","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("const_val","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("external","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("in","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("out","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_ODC_Variable = NULL;
 SDB_Index     ri_ODC_Variable_externals_ref[] = {
               SDB_Index("ik_Ident8",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Variable_constants_ref[] = {
               SDB_Index("ik_Ident8",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Variable_retvals[] = {
               SDB_Index("__IDENTITY",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Variable_parameters[] = {
               SDB_Index("__IDENTITY",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Variable_main_functions[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Relationship *pf_ODC_Variable[] = {
              new SDB_Relationship(SDB_Reference(SDB_Member("externals_ref","ODC_ImpClass",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Variable_externals_ref,1,Y,Y,N),Y,N,"externals",N,""),
              new SDB_Relationship(SDB_Reference(SDB_Member("constants_ref","ODC_ImpClass",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Variable_constants_ref,1,Y,Y,N),Y,N,"constants",N,""),
              new SDB_Relationship(SDB_Reference(SDB_Member("retvals","ODC_Function",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,Y,ri_ODC_Variable_retvals,1,Y,N,N),Y,N,"retval",N,""),
              new SDB_Relationship(SDB_Reference(SDB_Member("parameters","ODC_FunctImp",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Variable_parameters,1,Y,N,N),Y,N,"parameters",N,""),
              new SDB_Relationship(SDB_Reference(SDB_Member("main_functions","ODC_Executable",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Variable_main_functions,1,Y,N,N),Y,N,"mexternals",N,""),
              };

 SDB_BaseStruct *bf_ODC_FunctImp[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("SDB_Resource","SDB_Resource",RL_direct,16,0,1,"",N,N,0),N,0,N,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),
              };
 SDB_Attribute *af_ODC_FunctImp[] = {
              new SDB_Attribute(SDB_Member("inline_funct","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("inter_face","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("sequence","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("recover","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("head_line","STRING",RL_direct,512,0,1,"",N,N,0),Y,0),
              new SDB_Attribute(SDB_Member("linecount","INT",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("init_count","INT",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("start_count","INT",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("code_count","INT",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("error_count","INT",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("term_count","INT",RL_direct,4,0,1,"",N,N,0),N,0),
              };
 SDB_Index     ri_ODC_FunctImp_globals[] = {
               SDB_Index("",SET_undefined,N,N,Y,N,0),
              };
 SDB_Index    *ri_ODC_FunctImp_init_code = NULL;
 SDB_Index    *ri_ODC_FunctImp_start_code = NULL;
 SDB_Index    *ri_ODC_FunctImp_code = NULL;
 SDB_Index    *ri_ODC_FunctImp_error_code = NULL;
 SDB_Index    *ri_ODC_FunctImp_term_code = NULL;
 SDB_Reference *rf_ODC_FunctImp[] = {
              new SDB_Reference(SDB_Member("globals","ODC_Variable",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,Y,0,N,ri_ODC_FunctImp_globals,1,N,N,N),
              new SDB_Reference(SDB_Member("init_code","MEMO",RL_direct,2048,0,1,"PI",N,N,0),N,0,Y,Y,Y,0,N,ri_ODC_FunctImp_init_code,0,N,N,N),
              new SDB_Reference(SDB_Member("start_code","MEMO",RL_direct,2048,0,1,"PI",N,N,0),N,0,Y,Y,Y,0,N,ri_ODC_FunctImp_start_code,0,N,N,N),
              new SDB_Reference(SDB_Member("code","MEMO",RL_direct,32600,0,1,"PI",N,N,0),N,0,Y,Y,Y,0,N,ri_ODC_FunctImp_code,0,N,N,N),
              new SDB_Reference(SDB_Member("error_code","MEMO",RL_direct,2048,0,1,"PI",N,N,0),N,0,Y,Y,Y,0,N,ri_ODC_FunctImp_error_code,0,N,N,N),
              new SDB_Reference(SDB_Member("term_code","MEMO",RL_direct,2048,0,1,"PI",N,N,0),N,0,Y,Y,Y,0,N,ri_ODC_FunctImp_term_code,0,N,N,N),
              };
 SDB_Index     ri_ODC_FunctImp_parameters[] = {
               SDB_Index("",SET_SMAL,N,N,Y,N,0),
              };
 SDB_Index     ri_ODC_FunctImp_function[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index    *ri_ODC_FunctImp_incl_before_impl = NULL;
 SDB_Index    *ri_ODC_FunctImp_incl_after_impl = NULL;
 SDB_Relationship *pf_ODC_FunctImp[] = {
              new SDB_Relationship(SDB_Reference(SDB_Member("parameters","ODC_Variable",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_FunctImp_parameters,1,Y,N,N),N,N,"parameters",N,"ODC_Variable"),
              new SDB_Relationship(SDB_Reference(SDB_Member("function","ODC_PFunction",RL_direct,16,0,1,"PI",N,N,0),N,0,N,Y,N,0,Y,ri_ODC_FunctImp_function,1,Y,N,N),Y,N,"implementation_descr",N,""),
              new SDB_Relationship(SDB_Reference(SDB_Member("incl_before_impl","ODC_Include",RL_direct,40,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_FunctImp_incl_before_impl,0,Y,N,N),N,N,"before_impl_incls",N,"ODC_Include"),
              new SDB_Relationship(SDB_Reference(SDB_Member("incl_after_impl","ODC_Include",RL_direct,40,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_FunctImp_incl_after_impl,0,Y,N,N),N,N,"after_impl_incls",N,"ODC_Include"),
              };

 SDB_BaseStruct *bf_ODC_Function[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("SDB_Member","SDB_Member",RL_direct,0,0,1,"",N,N,0),N,0,N,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),
              };
 SDB_Attribute *af_ODC_Function[] = {
              new SDB_Attribute(SDB_Member("errorcase","CHAR",RL_direct,32,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("signal","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("slot","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("imp_type","MethodTypes",RL_direct,40,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("proc_type","ProcessingTypes",RL_direct,2,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("action","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("inter_face","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("retval_name","CHAR",RL_direct,40,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_ODC_Function = NULL;
 SDB_Index     ri_ODC_Function_retval[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Relationship *pf_ODC_Function[] = {
              new SDB_Relationship(SDB_Reference(SDB_Member("retval","ODC_Variable",RL_direct,0,0,1,"PI",N,N,304564),N,0,N,Y,N,0,N,ri_ODC_Function_retval,1,Y,N,N),N,N,"retvals",N,"ODC_Variable"),
              };

 SDB_BaseStruct *bf_ODC_PFunction[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("ODC_Function","ODC_Function",RL_direct,0,0,1,"",N,N,0),N,0,N,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),
              };
 SDB_Attribute *af_ODC_PFunction[] = {
              new SDB_Attribute(SDB_Member("linecount","INT",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("const_val","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("pure_funct","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("exportfunction","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_ODC_PFunction = NULL;
 SDB_Index     ri_ODC_PFunction_implementation_descr[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_PFunction_implementations[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index    *ri_ODC_PFunction_classx = NULL;
 SDB_Index    *ri_ODC_PFunction_incl_before_impls = NULL;
 SDB_Index    *ri_ODC_PFunction_incl_after_impls = NULL;
 SDB_Index     ri_ODC_PFunction_function_group[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_PFunction_module[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Relationship *pf_ODC_PFunction[] = {
              new SDB_Relationship(SDB_Reference(SDB_Member("implementation_descr","ODC_FunctImp",RL_direct,40,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_PFunction_implementation_descr,1,Y,N,N),N,N,"function",N,""),
              new SDB_Relationship(SDB_Reference(SDB_Member("implementations","ODC_FunctImp",RL_direct,16,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_PFunction_implementations,1,Y,N,N),N,N,"",N,"..implementation_descr"),
              new SDB_Relationship(SDB_Reference(SDB_Member("classx","ODC_ImpClass",RL_direct,16,0,1,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_PFunction_classx,0,Y,N,N),Y,N,"function_descr",N,""),
              new SDB_Relationship(SDB_Reference(SDB_Member("incl_before_impls","ODC_Include",RL_direct,40,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_PFunction_incl_before_impls,0,Y,N,N),N,N,"before_impls_incls",N,"ODC_Include"),
              new SDB_Relationship(SDB_Reference(SDB_Member("incl_after_impls","ODC_Include",RL_direct,40,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_PFunction_incl_after_impls,0,Y,N,N),N,N,"after_impls_incls",N,"ODC_Include"),
              new SDB_Relationship(SDB_Reference(SDB_Member("function_group","ODC_FunctGroup",RL_direct,0,0,1,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_PFunction_function_group,1,Y,N,N),N,N,"functions",N,"..classx.function_groups"),
              new SDB_Relationship(SDB_Reference(SDB_Member("module","ODC_Module",RL_direct,0,0,1,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_PFunction_module,1,Y,N,N),Y,N,"pfunctions",N,"ODC_Module"),
              };

 SDB_BaseStruct *bf_ODC_FunctGroup[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("SDB_Resource","SDB_Resource",RL_direct,40,0,1,"",N,N,0),N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),
              };
 SDB_Attribute **af_ODC_FunctGroup = NULL;
 SDB_Reference **rf_ODC_FunctGroup = NULL;
 SDB_Index     ri_ODC_FunctGroup_imp_class[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_FunctGroup_functions[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Relationship *pf_ODC_FunctGroup[] = {
              new SDB_Relationship(SDB_Reference(SDB_Member("imp_class","ODC_ImpClass",RL_direct,40,0,1,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_FunctGroup_imp_class,1,Y,N,N),Y,N,"function_groups",N,"ODC_ImpClass"),
              new SDB_Relationship(SDB_Reference(SDB_Member("functions","ODC_PFunction",RL_direct,40,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_FunctGroup_functions,1,Y,N,N),Y,N,"function_group",N,"..imp_class.function_descr"),
              };

 SDB_BaseStruct *bf_ODC_ImpClass[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("SDB_Structure","SDB_Structure",RL_direct,0,0,1,"",N,N,0),N,0,N,Y,N,0,N,NULL,0,Y,N,N),N,N,"smceclas",N,"SDB_Structure"),N),
              };
 SDB_Attribute *af_ODC_ImpClass[] = {
              new SDB_Attribute(SDB_Member("date_time","DATETIME",RL_direct,8,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("req_compile","CompileStates",RL_direct,2,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("req_genincl","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("mod_level","ClassModLevel",RL_direct,2,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("opt_language","ProgramLanguage",RL_direct,2,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("opt_debug","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("no_compile","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("opt_export","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("expandable","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("rtti_type","RTTI_Types",RL_direct,40,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("reserve","CHAR",RL_direct,12,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("expansion","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              };
 SDB_Index    *ri_ODC_ImpClass_template_parms = NULL;
 SDB_Reference *rf_ODC_ImpClass[] = {
              new SDB_Reference(SDB_Member("template_parms","MEMO",RL_direct,2000,0,1,"PI",N,N,0),N,0,Y,Y,Y,0,N,ri_ODC_ImpClass_template_parms,0,N,N,N),
              };
 SDB_Index     ri_ODC_ImpClass_function_descr[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_ImpClass_pfunctions[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_ImpClass_class_ref[] = {
               SDB_Index("ik_SDB_TypeRef",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_ImpClass_constants[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_ImpClass_externals[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_ImpClass_incl_system[] = {
               SDB_Index("ik_ODC_Include",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_ImpClass_incl_user[] = {
               SDB_Index("ik_ODC_Include",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index    *ri_ODC_ImpClass_incl_beg_class = NULL;
 SDB_Index    *ri_ODC_ImpClass_incl_end_class = NULL;
 SDB_Index    *ri_ODC_ImpClass_incl_after_class = NULL;
 SDB_Index    *ri_ODC_ImpClass_proj_class_ref = NULL;
 SDB_Index     ri_ODC_ImpClass_function_groups[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_ImpClass_module[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Relationship *pf_ODC_ImpClass[] = {
              new SDB_Relationship(SDB_Reference(SDB_Member("function_descr","ODC_PFunction",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_ImpClass_function_descr,1,Y,N,N),N,N,"classx",N,""),
              new SDB_Relationship(SDB_Reference(SDB_Member("pfunctions","ODC_PFunction",RL_direct,16,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_ImpClass_pfunctions,1,Y,N,N),N,N,"",N,"..function_descr"),
              new SDB_Relationship(SDB_Reference(SDB_Member("class_ref","SDB_TypeRef",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_ImpClass_class_ref,1,Y,N,N),N,N,"",N,"..type_references"),
              new SDB_Relationship(SDB_Reference(SDB_Member("constants","ODC_Variable",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_ImpClass_constants,1,Y,N,N),N,N,"constants_ref",N,"ODC_Variable"),
              new SDB_Relationship(SDB_Reference(SDB_Member("externals","ODC_Variable",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_ImpClass_externals,1,Y,N,N),N,N,"externals_ref",N,"ODC_Variable"),
              new SDB_Relationship(SDB_Reference(SDB_Member("incl_system","ODC_Include",RL_direct,0,0,1,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_ImpClass_incl_system,1,Y,N,N),N,N,"systemincl_ref",N,"ODC_Include"),
              new SDB_Relationship(SDB_Reference(SDB_Member("incl_user","ODC_Include",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_ImpClass_incl_user,1,Y,N,N),N,N,"userincl_ref",N,"ODC_Include"),
              new SDB_Relationship(SDB_Reference(SDB_Member("incl_beg_class","ODC_Include",RL_direct,40,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_ImpClass_incl_beg_class,0,Y,N,N),N,N,"beg_class_incls",N,"ODC_Include"),
              new SDB_Relationship(SDB_Reference(SDB_Member("incl_end_class","ODC_Include",RL_direct,40,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_ImpClass_incl_end_class,0,Y,N,N),N,N,"end_class_incls",N,"ODC_Include"),
              new SDB_Relationship(SDB_Reference(SDB_Member("incl_after_class","ODC_Include",RL_direct,40,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_ImpClass_incl_after_class,0,Y,N,N),N,N,"after_class_incls",N,"ODC_Include"),
              new SDB_Relationship(SDB_Reference(SDB_Member("proj_class_ref","ODC_Project",RL_direct,0,0,1,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_ImpClass_proj_class_ref,0,Y,N,N),Y,N,"proj_classes",N,"ODC_Project"),
              new SDB_Relationship(SDB_Reference(SDB_Member("function_groups","ODC_FunctGroup",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_ImpClass_function_groups,1,Y,N,N),N,N,"imp_class",N,""),
              new SDB_Relationship(SDB_Reference(SDB_Member("module","ODC_Module",RL_direct,40,0,1,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_ImpClass_module,1,Y,N,N),Y,N,"classes",N,"ODC_Module"),
              };

 SDB_BaseStruct *bf_ODC_Main[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("ODC_PFunction","ODC_PFunction",RL_direct,0,0,1,"",N,N,0),N,0,N,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),
              };
 SDB_Attribute *af_ODC_Main[] = {
              new SDB_Attribute(SDB_Member("opt_debug","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("opt_language","ProgramLanguage",RL_direct,2,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("req_compile","CompileStates",RL_direct,2,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("no_compile","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_ODC_Main = NULL;
 SDB_Index    *ri_ODC_Main_mincl_system = NULL;
 SDB_Index     ri_ODC_Main_mincl_user[] = {
               SDB_Index("",SET_SMAL,N,N,Y,N,0),
              };
 SDB_Relationship *pf_ODC_Main[] = {
              new SDB_Relationship(SDB_Reference(SDB_Member("mincl_system","ODC_Include",RL_direct,0,0,1,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Main_mincl_system,0,Y,N,N),N,N,"system_main_incls",N,"ODC_Include"),
              new SDB_Relationship(SDB_Reference(SDB_Member("mincl_user","ODC_Include",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Main_mincl_user,1,Y,N,N),N,N,"user_main_incls",N,"ODC_Include"),
              };

 SDB_BaseStruct *bf_ODC_Executable[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("main_function","ODC_Main",RL_direct,0,0,1,"",N,N,0),N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),
              };
 SDB_Attribute *af_ODC_Executable[] = {
              new SDB_Attribute(SDB_Member("autolink","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("dll_option","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              };
 SDB_Index    *ri_ODC_Executable_def_file = NULL;
 SDB_Reference *rf_ODC_Executable[] = {
              new SDB_Reference(SDB_Member("def_file","FileMemo",RL_direct,0,0,1,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_Executable_def_file,0,N,N,N),
              };
 SDB_Index     ri_ODC_Executable_module[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Executable_mexternals[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Relationship *pf_ODC_Executable[] = {
              new SDB_Relationship(SDB_Reference(SDB_Member("module","ODC_Module",RL_direct,0,0,1,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Executable_module,1,Y,N,N),Y,N,"main_functions",N,"ODC_Module"),
              new SDB_Relationship(SDB_Reference(SDB_Member("mexternals","ODC_Variable",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Executable_mexternals,1,Y,N,N),N,N,"main_functions",N,"ODC_Variable"),
              };

 SDB_BaseStruct *bf_ODC_ViewPath[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("SDB_Resource","SDB_Resource",RL_direct,40,0,1,"",N,N,0),N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),
              };
 SDB_Attribute *af_ODC_ViewPath[] = {
              new SDB_Attribute(SDB_Member("path","STRING",RL_direct,255,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("structure","CHAR",RL_direct,40,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("order","CHAR",RL_direct,40,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_ODC_ViewPath = NULL;
 SDB_Relationship **pf_ODC_ViewPath = NULL;

 SDB_BaseStruct *bf_ODC_View[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("SDB_Structure","SDB_Structure",RL_direct,0,0,1,"",N,N,0),N,0,N,Y,N,0,N,NULL,1,Y,Y,N),N,N,"view",N,"SDB_Structure"),N),
              };
 SDB_Attribute **af_ODC_View = NULL;
 SDB_Index    *ri_ODC_View_from = NULL;
 SDB_Index    *ri_ODC_View_where = NULL;
 SDB_Index    *ri_ODC_View_group_by = NULL;
 SDB_Index    *ri_ODC_View_having = NULL;
 SDB_Reference *rf_ODC_View[] = {
              new SDB_Reference(SDB_Member("from","ODC_ViewPath",RL_direct,40,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_View_from,0,N,N,N),
              new SDB_Reference(SDB_Member("where","MEMO",RL_direct,4000,0,1,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_View_where,0,N,N,N),
              new SDB_Reference(SDB_Member("group_by","SDB_ValueList",RL_direct,40,0,1,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_View_group_by,0,N,N,N),
              new SDB_Reference(SDB_Member("having","MEMO",RL_direct,4000,0,1,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_View_having,0,N,N,N),
              };
 SDB_Index    *ri_ODC_View_module = NULL;
 SDB_Relationship *pf_ODC_View[] = {
              new SDB_Relationship(SDB_Reference(SDB_Member("module","ODC_Module",RL_direct,40,0,1,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_View_module,0,Y,N,N),N,N,"views",N,""),
              };

 SDB_BaseStruct *bf_ODC_ProjRef[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("SDB_Resource","SDB_Resource",RL_direct,0,0,1,"",N,N,0),N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),
              };
 SDB_Attribute *af_ODC_ProjRef[] = {
              new SDB_Attribute(SDB_Member("project_name","CHAR",RL_direct,40,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("dll_path","STRING",RL_direct,127,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("ini_file","STRING",RL_direct,127,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("reserved","STRING",RL_direct,499,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_ODC_ProjRef = NULL;
 SDB_Relationship **pf_ODC_ProjRef = NULL;

 SDB_BaseStruct *bf_ODC_NamedObject[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("SDB_Resource","SDB_Resource",RL_direct,16,0,1,"",N,N,0),N,0,N,Y,N,0,N,NULL,1,N,N,N),N,N,"",N,""),N),
              };
 SDB_Attribute *af_ODC_NamedObject[] = {
              new SDB_Attribute(SDB_Member("object_ref","EB_Number",RL_direct,0,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_ODC_NamedObject = NULL;
 SDB_Index     ri_ODC_NamedObject_module[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Relationship *pf_ODC_NamedObject[] = {
              new SDB_Relationship(SDB_Reference(SDB_Member("module","ODC_Module",RL_direct,0,0,1,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_NamedObject_module,1,Y,Y,N),Y,N,"named_objects",N,"ODC_Module"),
              };

 SDB_BaseStruct *bf_ODC_Module[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("SDB_NameSpace","SDB_NameSpace",RL_direct,0,0,1,"",N,N,0),N,0,N,Y,N,0,N,NULL,1,Y,N,N),N,N,"namespace_ref",N,"SDB_NameSpace"),N),
              };
 SDB_Attribute *af_ODC_Module[] = {
              new SDB_Attribute(SDB_Member("odaba2_version","INT",RL_direct,10,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("odaba2_productio","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("req_genincl","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("is_modified","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("req_compile","CompileStates",RL_direct,40,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("no_compile","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("proj_busy","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("ctx_interface","CHAR",RL_direct,40,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_ODC_Module = NULL;
 SDB_Index     ri_ODC_Module_error_class[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Module_errors[] = {
               SDB_Index("ik_errnum",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Module_named_objects[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Module_sub_modules[] = {
               SDB_Index("ik_Ident8",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Module_parent_module[] = {
               SDB_Index("ik_Ident8",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Module_module_ref[] = {
               SDB_Index("ik_Ident8",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Module_classes[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Module_views[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
               SDB_Index("ik_Ident8",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Module_database[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Module_function_descr[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Module_pfunctions[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Module_main_functions[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Relationship *pf_ODC_Module[] = {
              new SDB_Relationship(SDB_Reference(SDB_Member("error_class","ODC_ErrorClass",RL_direct,0,0,1,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Module_error_class,1,Y,N,N),N,N,"modules",N,"ODC_ErrorClass"),
              new SDB_Relationship(SDB_Reference(SDB_Member("errors","ODC_Error",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Module_errors,1,Y,N,N),N,N,"modules",N,"..error_class.errors"),
              new SDB_Relationship(SDB_Reference(SDB_Member("named_objects","ODC_NamedObject",RL_direct,40,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_Module_named_objects,1,Y,N,N),N,N,"module",N,""),
              new SDB_Relationship(SDB_Reference(SDB_Member("sub_modules","ODC_Module",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Module_sub_modules,1,Y,Y,N),N,N,"parent_module",N,"ODC_Module"),
              new SDB_Relationship(SDB_Reference(SDB_Member("parent_module","ODC_Module",RL_direct,0,0,1,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Module_parent_module,1,Y,N,N),Y,N,"sub_modules",N,"ODC_Module"),
              new SDB_Relationship(SDB_Reference(SDB_Member("module_ref","ODC_Module",RL_direct,40,0,1,"PI",N,N,0),N,0,N,Y,N,0,Y,ri_ODC_Module_module_ref,1,Y,N,N),Y,N,"ODC_Module",N,"*"),
              new SDB_Relationship(SDB_Reference(SDB_Member("classes","ODC_ImpClass",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Module_classes,1,Y,N,N),N,N,"module",N,"ODC_ImpClass"),
              new SDB_Relationship(SDB_Reference(SDB_Member("views","ODC_View",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Module_views,2,Y,Y,N),Y,N,"module",N,"ODC_View"),
              new SDB_Relationship(SDB_Reference(SDB_Member("database","ODC_Database",RL_direct,40,0,1,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Module_database,1,Y,N,N),Y,N,"ODC_Module",N,"ODC_Module"),
              new SDB_Relationship(SDB_Reference(SDB_Member("function_descr","ODC_PFunction",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_Module_function_descr,1,Y,N,N),N,N,"module",N,""),
              new SDB_Relationship(SDB_Reference(SDB_Member("pfunctions","ODC_PFunction",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Module_pfunctions,1,Y,N,N),N,N,"",N,"..function_descr"),
              new SDB_Relationship(SDB_Reference(SDB_Member("main_functions","ODC_Executable",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Module_main_functions,1,Y,N,N),N,N,"module",N,"ODC_Executable"),
              };

 SDB_BaseStruct *bf_ODC_Project[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("ODC_Module","ODC_Module",RL_direct,40,0,1,"",N,N,0),N,0,N,Y,N,0,N,NULL,1,Y,N,N),N,N,"module_ref",N,"ODC_Module"),N),
              };
 SDB_Attribute *af_ODC_Project[] = {
              new SDB_Attribute(SDB_Member("proj_path","STRING",RL_direct,255,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("resource_base","STRING",RL_direct,63,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("path_names","STRING",RL_direct,31,0,20,"",N,N,0),N,0),
              };
 SDB_Index     ri_ODC_Project_proj_references[] = {
               SDB_Index("",SET_SMAL,N,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Project_basecontexts[] = {
               SDB_Index("ik_ODC_BaseCtx",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Reference *rf_ODC_Project[] = {
              new SDB_Reference(SDB_Member("proj_references","ODC_ProjRef",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_Project_proj_references,1,N,N,N),
              new SDB_Reference(SDB_Member("basecontexts","ODC_BaseContext",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_ODC_Project_basecontexts,1,N,N,N),
              };
 SDB_Index    *ri_ODC_Project_proj_include = NULL;
 SDB_Index     ri_ODC_Project_ref_projects[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Project_environment[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Project_sub_projects[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Project_parent_project[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_ODC_Project_proj_classes[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
               SDB_Index("ik_Ident8",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Relationship *pf_ODC_Project[] = {
              new SDB_Relationship(SDB_Reference(SDB_Member("proj_include","ODC_Include",RL_direct,0,0,1,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Project_proj_include,0,Y,N,N),N,N,"projects",N,"ODC_Include"),
              new SDB_Relationship(SDB_Reference(SDB_Member("ref_projects","ODC_Project",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Project_ref_projects,1,N,N,N),N,N,"",N,"ODC_Project"),
              new SDB_Relationship(SDB_Reference(SDB_Member("environment","ODC_Environment",RL_direct,0,0,1,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Project_environment,1,Y,N,N),N,N,"env_ref",N,"ODC_Environment"),
              new SDB_Relationship(SDB_Reference(SDB_Member("sub_projects","ODC_Project",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Project_sub_projects,1,Y,N,N),N,N,"parent_project",N,"ODC_Project"),
              new SDB_Relationship(SDB_Reference(SDB_Member("parent_project","ODC_Project",RL_direct,0,0,1,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Project_parent_project,1,Y,N,N),Y,N,"sub_projects",N,"ODC_Project"),
              new SDB_Relationship(SDB_Reference(SDB_Member("proj_classes","ODC_ImpClass",RL_direct,0,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_ODC_Project_proj_classes,2,Y,Y,N),N,N,"proj_class_ref",N,"ODC_ImpClass"),
              };

 SDB_BaseStruct **bf_ODC_DBIdent = NULL;
 SDB_Attribute *af_ODC_DBIdent[] = {
              new SDB_Attribute(SDB_Member("date","DATE",RL_direct,8,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("time","TIME",RL_direct,8,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("id","INT",RL_direct,10,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_ODC_DBIdent = NULL;
 SDB_Relationship **pf_ODC_DBIdent = NULL;

 SDB_BaseStruct **bf_ODC_DBLicence = NULL;
 SDB_Attribute *af_ODC_DBLicence[] = {
              new SDB_Attribute(SDB_Member("req_licence_id","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("month_limit","UINT",RL_direct,2,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("owner","CHAR",RL_direct,48,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("licence_number","CHAR",RL_direct,12,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("time_limit","DATE",RL_direct,8,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("max_users","UINT",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("reserved","CHAR",RL_direct,12,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("licence_number_t","CHAR",RL_direct,12,0,1,"",N,N,0),Y,0),
              new SDB_Attribute(SDB_Member("owner_t","CHAR",RL_direct,48,0,1,"",N,N,0),Y,0),
              };
 SDB_Reference **rf_ODC_DBLicence = NULL;
 SDB_Relationship **pf_ODC_DBLicence = NULL;

 SDB_BaseStruct **bf_ODC_ApplLicence = NULL;
 SDB_Attribute *af_ODC_ApplLicence[] = {
              new SDB_Attribute(SDB_Member("name","CHAR",RL_direct,40,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("licence","ODC_DBLicence",RL_direct,1,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_ODC_ApplLicence = NULL;
 SDB_Relationship **pf_ODC_ApplLicence = NULL;

 SDB_BaseStruct *bf_ODC_Database[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("ODC_Module","ODC_Module",RL_direct,40,0,1,"",N,N,0),N,0,N,Y,N,0,N,NULL,1,Y,N,N),N,N,"database",N,"ODC_Module"),N),
              };
 SDB_Attribute *af_ODC_Database[] = {
              new SDB_Attribute(SDB_Member("reserved","CHAR",RL_direct,30,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("ident","ODC_DBIdent",RL_direct,10,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("sub_version","INT",RL_direct,4,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("licence","ODC_DBLicence",RL_direct,1,0,1,"",N,N,0),N,0),
              };
 SDB_Index     ri_ODC_Database_applications[] = {
               SDB_Index("ik_name",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Reference *rf_ODC_Database[] = {
              new SDB_Reference(SDB_Member("applications","ODC_ApplLicence",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,Y,0,N,ri_ODC_Database_applications,1,N,N,N),
              };
 SDB_Relationship **pf_ODC_Database = NULL;


 char         *kc_FileMemo_ik_FileMemo[] = {
              "file_name",
              "" };
 char         *kc_FileMemo_sk_FileMemo[] = {
              "file_ext",
              "" };
 SDB_Key       sk_FileMemo[] = {
              SDB_Key("ik_FileMemo",kc_FileMemo_ik_FileMemo,1),
              SDB_Key("sk_FileMemo",kc_FileMemo_sk_FileMemo,2),
              };
 dictptr->SetupStructDef("FileMemo",bf_FileMemo,af_FileMemo,rf_FileMemo,pf_FileMemo,sk_FileMemo,2,8,0);

 char         *kc_ODC_Error_ik_errnum[] = {
              "_errnum",
              "" };
 SDB_Key       sk_ODC_Error[] = {
              SDB_Key("ik_errnum",kc_ODC_Error_ik_errnum,1),
              };
 dictptr->SetupStructDef("ODC_Error",bf_ODC_Error,af_ODC_Error,rf_ODC_Error,pf_ODC_Error,sk_ODC_Error,1,8,0);

 char         *kc_ODC_ErrorClass_ik_Ident[] = {
              "sys_ident",
              "" };
 SDB_Key       sk_ODC_ErrorClass[] = {
              SDB_Key("ik_Ident",kc_ODC_ErrorClass_ik_Ident,1),
              };
 dictptr->SetupStructDef("ODC_ErrorClass",bf_ODC_ErrorClass,af_ODC_ErrorClass,rf_ODC_ErrorClass,pf_ODC_ErrorClass,sk_ODC_ErrorClass,1,8,0);

 char         *kc_ODC_BaseContext_id_ODC_BaseCtx[] = {
              "classname",
              "" };
 char         *kc_ODC_BaseContext_ik_ODC_BaseCtx[] = {
              "contexttype",
              "" };
 SDB_Key       sk_ODC_BaseContext[] = {
              SDB_Key("id_ODC_BaseCtx",kc_ODC_BaseContext_id_ODC_BaseCtx,1),
              SDB_Key("ik_ODC_BaseCtx",kc_ODC_BaseContext_ik_ODC_BaseCtx,2),
              };
 dictptr->SetupStructDef("ODC_BaseContext",bf_ODC_BaseContext,af_ODC_BaseContext,rf_ODC_BaseContext,pf_ODC_BaseContext,sk_ODC_BaseContext,2,8,0);

 char         *kc_ODC_Environment_ik_Ident[] = {
              "sys_ident",
              "" };
 SDB_Key       sk_ODC_Environment[] = {
              SDB_Key("ik_Ident",kc_ODC_Environment_ik_Ident,1),
              };
 dictptr->SetupStructDef("ODC_Environment",bf_ODC_Environment,af_ODC_Environment,rf_ODC_Environment,pf_ODC_Environment,sk_ODC_Environment,1,8,0);

 char         *kc_ODC_Include_ik_ODC_Include[] = {
              "FileMemo",
              "" };
 SDB_Key       sk_ODC_Include[] = {
              SDB_Key("ik_ODC_Include",kc_ODC_Include_ik_ODC_Include,1),
              };
 dictptr->SetupStructDef("ODC_Include",bf_ODC_Include,af_ODC_Include,rf_ODC_Include,pf_ODC_Include,sk_ODC_Include,1,8,0);

 char         *kc_ODC_Variable_ik_Ident[] = {
              "sys_ident",
              "" };
 SDB_Key       sk_ODC_Variable[] = {
              SDB_Key("ik_Ident",kc_ODC_Variable_ik_Ident,1),
              };
 dictptr->SetupStructDef("ODC_Variable",bf_ODC_Variable,af_ODC_Variable,rf_ODC_Variable,pf_ODC_Variable,sk_ODC_Variable,1,8,303505);

 char         *kc_ODC_FunctImp___IDENTITY[] = {
              "" };
 char         *kc_ODC_FunctImp_ik_Ident[] = {
              "sys_ident",
              "" };
 SDB_Key       sk_ODC_FunctImp[] = {
              SDB_Key("__IDENTITY",kc_ODC_FunctImp___IDENTITY,2),
              SDB_Key("ik_Ident",kc_ODC_FunctImp_ik_Ident,3),
              };
 dictptr->SetupStructDef("ODC_FunctImp",bf_ODC_FunctImp,af_ODC_FunctImp,rf_ODC_FunctImp,pf_ODC_FunctImp,sk_ODC_FunctImp,2,8,303100);

 char         *kc_ODC_Function___IDENTITY[] = {
              "" };
 char         *kc_ODC_Function_ik_Ident[] = {
              "sys_ident",
              "" };
 SDB_Key       sk_ODC_Function[] = {
              SDB_Key("__IDENTITY",kc_ODC_Function___IDENTITY,2),
              SDB_Key("ik_Ident",kc_ODC_Function_ik_Ident,1),
              };
 dictptr->SetupStructDef("ODC_Function",bf_ODC_Function,af_ODC_Function,rf_ODC_Function,pf_ODC_Function,sk_ODC_Function,2,8,0);

 char         *kc_ODC_PFunction___IDENTITY[] = {
              "" };
 char         *kc_ODC_PFunction_ik_Ident[] = {
              "sys_ident",
              "" };
 SDB_Key       sk_ODC_PFunction[] = {
              SDB_Key("__IDENTITY",kc_ODC_PFunction___IDENTITY,2),
              SDB_Key("ik_Ident",kc_ODC_PFunction_ik_Ident,1),
              };
 dictptr->SetupStructDef("ODC_PFunction",bf_ODC_PFunction,af_ODC_PFunction,rf_ODC_PFunction,pf_ODC_PFunction,sk_ODC_PFunction,2,8,303411);

 char         *kc_ODC_FunctGroup_ik_Ident[] = {
              "sys_ident",
              "" };
 SDB_Key       sk_ODC_FunctGroup[] = {
              SDB_Key("ik_Ident",kc_ODC_FunctGroup_ik_Ident,1),
              };
 dictptr->SetupStructDef("ODC_FunctGroup",bf_ODC_FunctGroup,af_ODC_FunctGroup,rf_ODC_FunctGroup,pf_ODC_FunctGroup,sk_ODC_FunctGroup,1,0,0);

 char         *kc_ODC_ImpClass_ik_Ident[] = {
              "sys_ident",
              "" };
 char         *kc_ODC_ImpClass_ik_Ident8[] = {
              "sys_ident",
              "namespace_id",
              "" };
 char         *kc_ODC_ImpClass_sk_date_time[] = {
              "date_time",
              "" };
 SDB_Key       sk_ODC_ImpClass[] = {
              SDB_Key("ik_Ident",kc_ODC_ImpClass_ik_Ident,1),
              SDB_Key("ik_Ident8",kc_ODC_ImpClass_ik_Ident8,3),
              SDB_Key("sk_date_time",kc_ODC_ImpClass_sk_date_time,2),
              };
 dictptr->SetupStructDef("ODC_ImpClass",bf_ODC_ImpClass,af_ODC_ImpClass,rf_ODC_ImpClass,pf_ODC_ImpClass,sk_ODC_ImpClass,3,8,303099);

 char         *kc_ODC_Main_ik_Ident[] = {
              "sys_ident",
              "" };
 SDB_Key       sk_ODC_Main[] = {
              SDB_Key("ik_Ident",kc_ODC_Main_ik_Ident,1),
              };
 dictptr->SetupStructDef("ODC_Main",bf_ODC_Main,af_ODC_Main,rf_ODC_Main,pf_ODC_Main,sk_ODC_Main,1,8,0);

 char         *kc_ODC_Executable_ik_Ident[] = {
              "sys_ident",
              "" };
 SDB_Key       sk_ODC_Executable[] = {
              SDB_Key("ik_Ident",kc_ODC_Executable_ik_Ident,1),
              };
 dictptr->SetupStructDef("ODC_Executable",bf_ODC_Executable,af_ODC_Executable,rf_ODC_Executable,pf_ODC_Executable,sk_ODC_Executable,1,8,0);

 char         *kc_ODC_ViewPath_ik_Ident[] = {
              "sys_ident",
              "" };
 SDB_Key       sk_ODC_ViewPath[] = {
              SDB_Key("ik_Ident",kc_ODC_ViewPath_ik_Ident,1),
              };
 dictptr->SetupStructDef("ODC_ViewPath",bf_ODC_ViewPath,af_ODC_ViewPath,rf_ODC_ViewPath,pf_ODC_ViewPath,sk_ODC_ViewPath,1,8,0);

 char         *kc_ODC_View_ik_Ident[] = {
              "sys_ident",
              "" };
 char         *kc_ODC_View_ik_Ident8[] = {
              "sys_ident",
              "namespace_id",
              "" };
 SDB_Key       sk_ODC_View[] = {
              SDB_Key("ik_Ident",kc_ODC_View_ik_Ident,2),
              SDB_Key("ik_Ident8",kc_ODC_View_ik_Ident8,1),
              };
 dictptr->SetupStructDef("ODC_View",bf_ODC_View,af_ODC_View,rf_ODC_View,pf_ODC_View,sk_ODC_View,2,8,300772);

 char         *kc_ODC_ProjRef_ik_Ident[] = {
              "sys_ident",
              "" };
 SDB_Key       sk_ODC_ProjRef[] = {
              SDB_Key("ik_Ident",kc_ODC_ProjRef_ik_Ident,1),
              };
 dictptr->SetupStructDef("ODC_ProjRef",bf_ODC_ProjRef,af_ODC_ProjRef,rf_ODC_ProjRef,pf_ODC_ProjRef,sk_ODC_ProjRef,1,8,0);

 char         *kc_ODC_NamedObject_ik_Ident[] = {
              "sys_ident",
              "" };
 SDB_Key       sk_ODC_NamedObject[] = {
              SDB_Key("ik_Ident",kc_ODC_NamedObject_ik_Ident,1),
              };
 dictptr->SetupStructDef("ODC_NamedObject",bf_ODC_NamedObject,af_ODC_NamedObject,rf_ODC_NamedObject,pf_ODC_NamedObject,sk_ODC_NamedObject,1,8,0);

 char         *kc_ODC_Module_ik_Ident[] = {
              "sys_ident",
              "" };
 char         *kc_ODC_Module_ik_Ident8[] = {
              "sys_ident",
              "namespace_id",
              "" };
 SDB_Key       sk_ODC_Module[] = {
              SDB_Key("ik_Ident",kc_ODC_Module_ik_Ident,1),
              SDB_Key("ik_Ident8",kc_ODC_Module_ik_Ident8,2),
              };
 dictptr->SetupStructDef("ODC_Module",bf_ODC_Module,af_ODC_Module,rf_ODC_Module,pf_ODC_Module,sk_ODC_Module,2,8,0);

 char         *kc_ODC_Project_ik_Ident[] = {
              "sys_ident",
              "" };
 char         *kc_ODC_Project_ik_Ident8[] = {
              "sys_ident",
              "namespace_id",
              "" };
 SDB_Key       sk_ODC_Project[] = {
              SDB_Key("ik_Ident",kc_ODC_Project_ik_Ident,1),
              SDB_Key("ik_Ident8",kc_ODC_Project_ik_Ident8,2),
              };
 dictptr->SetupStructDef("ODC_Project",bf_ODC_Project,af_ODC_Project,rf_ODC_Project,pf_ODC_Project,sk_ODC_Project,2,8,303101);

 SDB_Key       *sk_ODC_DBIdent = NULL;
 dictptr->SetupStructDef("ODC_DBIdent",bf_ODC_DBIdent,af_ODC_DBIdent,rf_ODC_DBIdent,pf_ODC_DBIdent,sk_ODC_DBIdent,0,8,0);

 SDB_Key       *sk_ODC_DBLicence = NULL;
 dictptr->SetupStructDef("ODC_DBLicence",bf_ODC_DBLicence,af_ODC_DBLicence,rf_ODC_DBLicence,pf_ODC_DBLicence,sk_ODC_DBLicence,0,8,0);

 char         *kc_ODC_ApplLicence_ik_name[] = {
              "name",
              "" };
 SDB_Key       sk_ODC_ApplLicence[] = {
              SDB_Key("ik_name",kc_ODC_ApplLicence_ik_name,1),
              };
 dictptr->SetupStructDef("ODC_ApplLicence",bf_ODC_ApplLicence,af_ODC_ApplLicence,rf_ODC_ApplLicence,pf_ODC_ApplLicence,sk_ODC_ApplLicence,1,8,0);

 char         *kc_ODC_Database_ik_Ident[] = {
              "sys_ident",
              "" };
 SDB_Key       sk_ODC_Database[] = {
              SDB_Key("ik_Ident",kc_ODC_Database_ik_Ident,1),
              };
 dictptr->SetupStructDef("ODC_Database",bf_ODC_Database,af_ODC_Database,rf_ODC_Database,pf_ODC_Database,sk_ODC_Database,1,8,0);

