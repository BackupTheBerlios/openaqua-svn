 dictptr->ProvideStructDcl("PropertyPath",615,UNDEF,UNDEF,TYP_Structure,ST_SYS,0,5,0,0,"ik_PropertyPath",N,0,N,N);
 dictptr->ProvideStructDcl("EXC_Structure",614,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,7,0,0,"ik_EXC_Structure",N,18,N,N);
 dictptr->ProvideStructDcl("EXC_StructAlloc",612,UNDEF,UNDEF,TYP_Structure,ST_SYS,0,4,1,2,"ik_EXC_StructAll",N,5,N,N);
 dictptr->ProvideStructDcl("EXC_ExtRel",613,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,1,0,3,"ik_EXC_ExtRel",N,5,N,N);
 dictptr->ProvideStructDcl("EXC_Allocation",610,UNDEF,UNDEF,TYP_Structure,ST_SYS,0,6,1,0,"ik_EXC_Allocatio",N,5,N,N);
 dictptr->ProvideStructDcl("EXC_Exchange",611,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,3,0,3,"ik_EXC_Exchange",N,18,N,N);
 dictptr->ProvideStructDcl("EXT_Extension",305,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,6,0,0,"ik_EXT_Extension",N,18,N,N);
 dictptr->ProvideStructDcl("EXT_BLOB",309,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,0,1,0,"ik_EXT_BLOB",N,18,N,N);
 dictptr->ProvideStructDcl("EXT_FilePath",310,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,1,0,0,"ik_EXT_FilePath",N,18,N,N);
 dictptr->ProvideStructDcl("SDB_ExternFile",359,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,2,0,0,"ik_Ident",N,18,N,N);
 dictptr->ProvideStructDcl("SDB_BinaryFile",358,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,0,0,0,"ik_SDB_BinaryFil",N,18,N,N);
 dictptr->ProvideStructDcl("SDB_SDF_File",364,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,7,0,0,"ik_Ident",N,18,N,N);
 dictptr->ProvideStructDcl("SDB_OEL_File",363,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,0,0,0,"ik_Ident",N,18,N,N);
 dictptr->ProvideStructDcl("SDB_XML_Document",367,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,0,0,0,"ik_Ident",N,18,N,N);
 dictptr->ProvideStructDcl("SDB_ODBCRelation",366,UNDEF,UNDEF,TYP_Structure,ST_SYS,1,3,1,0,"ik_Ident",N,18,N,N);
 dictptr->ProvideStructDcl("SDB_KeyLockInstance",170,UNDEF,UNDEF,TYP_Structure,ST_SYS,0,3,0,0,"ik_SDB_KeyLockInstance",N,0,N,N);
 dictptr->ProvideStructDcl("SDB_KeyLockIndex",168,UNDEF,UNDEF,TYP_Structure,ST_SYS,0,1,1,0,"ik_SDB_KeyLockIndex",N,0,N,N);
 dictptr->ProvideStructDcl("SDB_KeyLock",167,UNDEF,UNDEF,TYP_Structure,ST_SYS,0,2,1,0,"ik_SDB_KeyLock",N,0,N,N);


 SDB_Index     ri_EXC_Structure_EXC_Structure[] = {
               SDB_Index("ik_EXC_Structure",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("EXC_Structure","EXC_Structure",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_EXC_Structure_EXC_Structure,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_EXC_StructAlloc_EXC_StructAlloc[] = {
               SDB_Index("ik_EXC_StructAll",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("EXC_StructAlloc","EXC_StructAlloc",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_EXC_StructAlloc_EXC_StructAlloc,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_EXC_ExtRel_EXC_ExtRel[] = {
               SDB_Index("ik_EXC_ExtRel",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("EXC_ExtRel","EXC_ExtRel",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_EXC_ExtRel_EXC_ExtRel,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_EXC_Allocation_EXC_Allocation[] = {
               SDB_Index("ik_EXC_Allocatio",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("EXC_Allocation","EXC_Allocation",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_EXC_Allocation_EXC_Allocation,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_EXC_Exchange_EXC_Exchange[] = {
               SDB_Index("ik_EXC_Exchange",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("EXC_Exchange","EXC_Exchange",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_EXC_Exchange_EXC_Exchange,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_EXT_Extension_EXT_Extension[] = {
               SDB_Index("ik_EXT_Extension",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("EXT_Extension","EXT_Extension",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_EXT_Extension_EXT_Extension,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_EXT_BLOB_EXT_BLOB[] = {
               SDB_Index("ik_EXT_BLOB",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("EXT_BLOB","EXT_BLOB",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_EXT_BLOB_EXT_BLOB,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_EXT_FilePath_EXT_FilePath[] = {
               SDB_Index("ik_EXT_FilePath",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("EXT_FilePath","EXT_FilePath",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_EXT_FilePath_EXT_FilePath,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_SDB_ExternFile_SDB_ExternFile[] = {
               SDB_Index("ik_Ident",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("SDB_ExternFile","SDB_ExternFile",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_SDB_ExternFile_SDB_ExternFile,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_SDB_BinaryFile_SDB_BinaryFile[] = {
               SDB_Index("ik_SDB_BinaryFil",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("SDB_BinaryFile","SDB_BinaryFile",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_SDB_BinaryFile_SDB_BinaryFile,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_SDB_SDF_File_SDB_SDF_File[] = {
               SDB_Index("ik_Ident",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("SDB_SDF_File","SDB_SDF_File",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_SDB_SDF_File_SDB_SDF_File,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_SDB_OEL_File_SDB_OEL_File[] = {
               SDB_Index("ik_Ident",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("SDB_OEL_File","SDB_OEL_File",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_SDB_OEL_File_SDB_OEL_File,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_SDB_XML_Document_SDB_XML_Document[] = {
               SDB_Index("ik_Ident",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("SDB_XML_Document","SDB_XML_Document",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_SDB_XML_Document_SDB_XML_Document,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_SDB_ODBCRelation_SDB_ODBCRelation[] = {
               SDB_Index("ik_Ident",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("SDB_ODBCRelation","SDB_ODBCRelation",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_SDB_ODBCRelation_SDB_ODBCRelation,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_SDB_KeyLockInstance_SDB_KeyLockInstance[] = {
               SDB_Index("ik_SDB_KeyLockInstance",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("SDB_KeyLockInstance","SDB_KeyLockInstance",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_SDB_KeyLockInstance_SDB_KeyLockInstance,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_SDB_KeyLockIndex_SDB_KeyLockIndex[] = {
               SDB_Index("ik_SDB_KeyLockIndex",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("SDB_KeyLockIndex","SDB_KeyLockIndex",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_SDB_KeyLockIndex_SDB_KeyLockIndex,1,Y,Y,N),N,N,N,YES);
 SDB_Index     ri_SDB_KeyLock_SDB_KeyLock[] = {
               SDB_Index("ik_SDB_KeyLock",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("SDB_KeyLock","SDB_KeyLock",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_SDB_KeyLock_SDB_KeyLock,1,Y,Y,N),N,N,N,YES);



 SDB_BaseStruct **bf_PropertyPath = NULL;
 SDB_Attribute *af_PropertyPath[] = {
              new SDB_Attribute(SDB_Member("struct_ref","DBStructDef",RL_1,0,0,1,"",N,N,0),Y,0),
              new SDB_Attribute(SDB_Member("name","STRING",RL_direct,81,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("index","INT",RL_direct,10,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("attr_type","STRING",RL_direct,32,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("reserve","INT",RL_direct,10,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_PropertyPath = NULL;
 SDB_Relationship **pf_PropertyPath = NULL;

 SDB_BaseStruct *bf_EXC_Structure[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("SDB_Structure","SDB_Structure",RL_direct,16,0,1,"",N,N,0),N,0,N,Y,N,0,N,NULL,0,Y,N,N),N,N,"",N,"SDB_Structure"),N),
              };
 SDB_Attribute *af_EXC_Structure[] = {
              new SDB_Attribute(SDB_Member("imp_condition","CAU_simpleAction",RL_direct,16,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("exp_condition","CAU_simpleAction",RL_direct,16,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("imp_handler","CAU_simpleAction",RL_direct,16,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("key","CHAR",RL_direct,40,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("create","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("recreate","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("_reserve","STRING",RL_direct,31,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_EXC_Structure = NULL;
 SDB_Relationship **pf_EXC_Structure = NULL;

 SDB_BaseStruct **bf_EXC_StructAlloc = NULL;
 SDB_Attribute *af_EXC_StructAlloc[] = {
              new SDB_Attribute(SDB_Member("__AUTOIDENT","INT",RL_direct,10,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("import","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("export","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("_reserve","STRING",RL_direct,31,0,1,"",N,N,0),N,0),
              };
 SDB_Index     ri_EXC_StructAlloc_allocations[] = {
               SDB_Index("ik_EXC_Allocatio",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Reference *rf_EXC_StructAlloc[] = {
              new SDB_Reference(SDB_Member("allocations","EXC_Allocation",RL_direct,16,0,0,"PI",N,N,0),N,0,Y,Y,Y,0,N,ri_EXC_StructAlloc_allocations,1,N,Y,N),
              };
 SDB_Index     ri_EXC_StructAlloc_relation[] = {
               SDB_Index("ik_EXC_Structure",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_EXC_StructAlloc_extent[] = {
               SDB_Index("ik_EXC_Structure",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Relationship *pf_EXC_StructAlloc[] = {
              new SDB_Relationship(SDB_Reference(SDB_Member("relation","EXC_Structure",RL_direct,16,0,1,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_EXC_StructAlloc_relation,1,Y,N,N),N,N,"",N,""),
              new SDB_Relationship(SDB_Reference(SDB_Member("extent","EXC_Structure",RL_direct,16,0,1,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_EXC_StructAlloc_extent,1,Y,N,N),N,N,"",N,""),
              };

 SDB_BaseStruct *bf_EXC_ExtRel[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("EXC_StructAlloc","EXC_StructAlloc",RL_direct,16,0,1,"",N,N,0),N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),
              };
 SDB_Attribute *af_EXC_ExtRel[] = {
              new SDB_Attribute(SDB_Member("view_path","STRING",RL_direct,127,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_EXC_ExtRel = NULL;
 SDB_Index     ri_EXC_ExtRel_exchange[] = {
               SDB_Index("ik_EXC_Exchange",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_EXC_ExtRel_ext_extent[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_EXC_ExtRel_int_extent[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Relationship *pf_EXC_ExtRel[] = {
              new SDB_Relationship(SDB_Reference(SDB_Member("exchange","EXC_Exchange",RL_direct,16,0,1,"PI",N,N,0),N,0,N,Y,N,0,N,ri_EXC_ExtRel_exchange,1,Y,N,N),Y,N,"allocations",N,"EXC_Exchange"),
              new SDB_Relationship(SDB_Reference(SDB_Member("ext_extent","SDB_Reference",RL_direct,16,0,1,"PI",N,N,0),N,0,N,Y,N,0,N,ri_EXC_ExtRel_ext_extent,1,N,N,N),N,N,"",N,"SDB_Reference"),
              new SDB_Relationship(SDB_Reference(SDB_Member("int_extent","SDB_Extend",RL_direct,16,0,1,"PI",N,N,0),N,0,N,Y,N,0,N,ri_EXC_ExtRel_int_extent,1,N,N,N),N,N,"",N,"SDB_Extend"),
              };

 SDB_BaseStruct **bf_EXC_Allocation = NULL;
 SDB_Attribute *af_EXC_Allocation[] = {
              new SDB_Attribute(SDB_Member("attribute","PropertyPath",RL_direct,16,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("property","PropertyPath",RL_direct,16,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("key","CHAR",RL_direct,40,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("ignore","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("no_imp_exp","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("_reverve","STRING",RL_direct,31,0,1,"",N,N,0),N,0),
              };
 SDB_Index    *ri_EXC_Allocation_sub_allocation = NULL;
 SDB_Reference *rf_EXC_Allocation[] = {
              new SDB_Reference(SDB_Member("sub_allocation","EXC_StructAlloc",RL_direct,16,0,1,"PI",N,N,0),N,0,Y,Y,Y,0,N,ri_EXC_Allocation_sub_allocation,0,N,N,N),
              };
 SDB_Relationship **pf_EXC_Allocation = NULL;

 SDB_BaseStruct *bf_EXC_Exchange[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("SDB_Resource","SDB_Resource",RL_direct,16,0,1,"",N,N,0),N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),
              };
 SDB_Attribute *af_EXC_Exchange[] = {
              new SDB_Attribute(SDB_Member("export","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("all","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("_reserve","STRING",RL_direct,31,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_EXC_Exchange = NULL;
 SDB_Index     ri_EXC_Exchange_relations[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_EXC_Exchange_extents[] = {
               SDB_Index("ik_Ident",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Index     ri_EXC_Exchange_allocations[] = {
               SDB_Index("ik_EXC_ExtRel",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Relationship *pf_EXC_Exchange[] = {
              new SDB_Relationship(SDB_Reference(SDB_Member("relations","SDB_Reference",RL_direct,16,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_EXC_Exchange_relations,1,Y,N,N),N,N,"",N,"SDB_Reference"),
              new SDB_Relationship(SDB_Reference(SDB_Member("extents","SDB_Extend",RL_direct,16,0,0,"PI",N,N,0),N,0,N,Y,N,0,N,ri_EXC_Exchange_extents,1,Y,N,N),N,N,"",N,"SDB_Extend"),
              new SDB_Relationship(SDB_Reference(SDB_Member("allocations","EXC_ExtRel",RL_direct,16,0,0,"PI",N,N,0),N,0,Y,Y,N,0,N,ri_EXC_Exchange_allocations,1,Y,N,N),N,N,"exchange",N,""),
              };

 SDB_BaseStruct *bf_EXT_Extension[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("SDB_Resource","SDB_Resource",RL_direct,0,0,1,"",N,N,0),N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),
              };
 SDB_Attribute *af_EXT_Extension[] = {
              new SDB_Attribute(SDB_Member("system_extension","CHAR",RL_direct,40,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("default_association","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("software_location","STRING",RL_direct,80,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("component","STRING",RL_direct,80,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("library","STRING",RL_direct,80,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("parameters","STRING",RL_direct,80,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_EXT_Extension = NULL;
 SDB_Relationship **pf_EXT_Extension = NULL;

 SDB_BaseStruct *bf_EXT_BLOB[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("EXT_Extension","EXT_Extension",RL_direct,0,0,1,"",N,N,0),N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),
              };
 SDB_Attribute **af_EXT_BLOB = NULL;
 SDB_Index    *ri_EXT_BLOB_data = NULL;
 SDB_Reference *rf_EXT_BLOB[] = {
              new SDB_Reference(SDB_Member("data","BLOB",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,Y,0,N,ri_EXT_BLOB_data,0,N,N,N),
              };
 SDB_Relationship **pf_EXT_BLOB = NULL;

 SDB_BaseStruct *bf_EXT_FilePath[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("EXT_Extension","EXT_Extension",RL_direct,0,0,1,"",N,N,0),N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),
              };
 SDB_Attribute *af_EXT_FilePath[] = {
              new SDB_Attribute(SDB_Member("data_path","STRING",RL_direct,80,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_EXT_FilePath = NULL;
 SDB_Relationship **pf_EXT_FilePath = NULL;

 SDB_BaseStruct *bf_SDB_ExternFile[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("SDB_Reference","SDB_Reference",RL_direct,0,0,1,"",N,N,0),N,0,N,Y,N,0,N,NULL,0,Y,N,N),N,N,"",N,"SDB_Reference"),N),
              };
 SDB_Attribute *af_SDB_ExternFile[] = {
              new SDB_Attribute(SDB_Member("file_path","STRING",RL_direct,80,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("text","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_SDB_ExternFile = NULL;
 SDB_Relationship **pf_SDB_ExternFile = NULL;

 SDB_BaseStruct *bf_SDB_BinaryFile[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("SDB_ExternFile","SDB_ExternFile",RL_direct,0,0,1,"",N,N,0),N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),
              };
 SDB_Attribute **af_SDB_BinaryFile = NULL;
 SDB_Reference **rf_SDB_BinaryFile = NULL;
 SDB_Relationship **pf_SDB_BinaryFile = NULL;

 SDB_BaseStruct *bf_SDB_SDF_File[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("SDB_ExternFile","SDB_ExternFile",RL_direct,0,0,1,"",N,N,0),N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),
              };
 SDB_Attribute *af_SDB_SDF_File[] = {
              new SDB_Attribute(SDB_Member("prop_delimiter","CHAR",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("str_begin","CHAR",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("str_end","CHAR",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("set_begin","CHAR",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("set_end","CHAR",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("string_delimiter","CHAR",RL_direct,1,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("headline","LOGICAL",RL_direct,1,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_SDB_SDF_File = NULL;
 SDB_Relationship **pf_SDB_SDF_File = NULL;

 SDB_BaseStruct *bf_SDB_OEL_File[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("SDB_SDF_File","SDB_SDF_File",RL_direct,0,0,1,"",N,N,0),N,0,N,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),
              };
 SDB_Attribute **af_SDB_OEL_File = NULL;
 SDB_Reference **rf_SDB_OEL_File = NULL;
 SDB_Relationship **pf_SDB_OEL_File = NULL;

 SDB_BaseStruct *bf_SDB_XML_Document[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("SDB_ExternFile","SDB_ExternFile",RL_direct,40,0,1,"",N,N,0),N,0,Y,Y,N,0,N,NULL,0,N,N,N),N,N,"",N,""),N),
              };
 SDB_Attribute **af_SDB_XML_Document = NULL;
 SDB_Reference **rf_SDB_XML_Document = NULL;
 SDB_Relationship **pf_SDB_XML_Document = NULL;

 SDB_BaseStruct *bf_SDB_ODBCRelation[] = {
              new SDB_BaseStruct(SDB_Relationship(SDB_Reference(SDB_Member("SDB_Reference","SDB_Reference",RL_direct,0,0,1,"",N,N,0),N,0,N,Y,N,0,N,NULL,0,Y,N,N),N,N,"",N,"SDB_Reference"),N),
              };
 SDB_Attribute *af_SDB_ODBCRelation[] = {
              new SDB_Attribute(SDB_Member("data_source","STRING",RL_direct,80,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("user_id","CHAR",RL_direct,16,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("password","CHAR",RL_direct,16,0,1,"",N,N,0),N,0),
              };
 SDB_Index    *ri_SDB_ODBCRelation_SQL_Statement = NULL;
 SDB_Reference *rf_SDB_ODBCRelation[] = {
              new SDB_Reference(SDB_Member("SQL_Statement","MEMO",RL_direct,8000,0,1,"PI",N,N,0),N,0,Y,Y,Y,0,N,ri_SDB_ODBCRelation_SQL_Statement,0,N,N,N),
              };
 SDB_Relationship **pf_SDB_ODBCRelation = NULL;

 SDB_BaseStruct **bf_SDB_KeyLockInstance = NULL;
 SDB_Attribute *af_SDB_KeyLockInstance[] = {
              new SDB_Attribute(SDB_Member("value","CHAR",RL_direct,512,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("owner","INT",RL_direct,19,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("lock_count","INT",RL_direct,10,0,1,"",N,N,0),N,0),
              };
 SDB_Reference **rf_SDB_KeyLockInstance = NULL;
 SDB_Relationship **pf_SDB_KeyLockInstance = NULL;

 SDB_BaseStruct **bf_SDB_KeyLockIndex = NULL;
 SDB_Attribute *af_SDB_KeyLockIndex[] = {
              new SDB_Attribute(SDB_Member("index_id","EB_Number",RL_direct,0,0,1,"",N,N,0),N,0),
              };
 SDB_Index     ri_SDB_KeyLockIndex_key_locks[] = {
               SDB_Index("ik_SDB_KeyLockInstance",SET_SMAL,Y,N,Y,N,0),
              };
 SDB_Reference *rf_SDB_KeyLockIndex[] = {
              new SDB_Reference(SDB_Member("key_locks","SDB_KeyLockInstance",RL_direct,0,0,1,"PI",N,N,0),N,0,Y,Y,Y,0,N,ri_SDB_KeyLockIndex_key_locks,1,N,N,N),
              };
 SDB_Relationship **pf_SDB_KeyLockIndex = NULL;

 SDB_BaseStruct **bf_SDB_KeyLock = NULL;
 SDB_Attribute *af_SDB_KeyLock[] = {
              new SDB_Attribute(SDB_Member("sys_ident","CHAR",RL_direct,40,0,1,"",N,N,0),N,0),
              new SDB_Attribute(SDB_Member("last_use_id","INT",RL_direct,19,0,1,"",N,N,0),N,0),
              };
 SDB_Index    *ri_SDB_KeyLock_collections = NULL;
 SDB_Reference *rf_SDB_KeyLock[] = {
              new SDB_Reference(SDB_Member("collections","SDB_KeyLockIndex",RL_direct,0,0,0,"PI",N,N,0),N,0,Y,Y,Y,0,N,ri_SDB_KeyLock_collections,0,N,N,N),
              };
 SDB_Relationship **pf_SDB_KeyLock = NULL;


 char         *kc_PropertyPath_ik_PropertyPath[] = {
              "name",
              "" };
 SDB_Key       sk_PropertyPath[] = {
              SDB_Key("ik_PropertyPath",kc_PropertyPath_ik_PropertyPath,1),
              };
 dictptr->SetupStructDef("PropertyPath",bf_PropertyPath,af_PropertyPath,rf_PropertyPath,pf_PropertyPath,sk_PropertyPath,1,4,0);

 char         *kc_EXC_Structure_ik_EXC_Structure[] = {
              "SDB_Structure",
              "" };
 SDB_Key       sk_EXC_Structure[] = {
              SDB_Key("ik_EXC_Structure",kc_EXC_Structure_ik_EXC_Structure,1),
              };
 dictptr->SetupStructDef("EXC_Structure",bf_EXC_Structure,af_EXC_Structure,rf_EXC_Structure,pf_EXC_Structure,sk_EXC_Structure,1,8,0);

 char         *kc_EXC_StructAlloc_ik_EXC_StructAll[] = {
              "__AUTOIDENT",
              "" };
 SDB_Key       sk_EXC_StructAlloc[] = {
              SDB_Key("ik_EXC_StructAll",kc_EXC_StructAlloc_ik_EXC_StructAll,1),
              };
 dictptr->SetupStructDef("EXC_StructAlloc",bf_EXC_StructAlloc,af_EXC_StructAlloc,rf_EXC_StructAlloc,pf_EXC_StructAlloc,sk_EXC_StructAlloc,1,8,0);

 char         *kc_EXC_ExtRel_ik_EXC_ExtRel[] = {
              "__AUTOIDENT",
              "" };
 SDB_Key       sk_EXC_ExtRel[] = {
              SDB_Key("ik_EXC_ExtRel",kc_EXC_ExtRel_ik_EXC_ExtRel,1),
              };
 dictptr->SetupStructDef("EXC_ExtRel",bf_EXC_ExtRel,af_EXC_ExtRel,rf_EXC_ExtRel,pf_EXC_ExtRel,sk_EXC_ExtRel,1,8,0);

 char         *kc_EXC_Allocation_ik_EXC_Allocatio[] = {
              "property.name",
              "attribute.name",
              "" };
 char         *kc_EXC_Allocation_s1_EXC_Allocatio[] = {
              "property.name",
              "property.index",
              "property.attr_type",
              "" };
 char         *kc_EXC_Allocation_s2_EXC_Allocatio[] = {
              "attribute.name",
              "" };
 SDB_Key       sk_EXC_Allocation[] = {
              SDB_Key("ik_EXC_Allocatio",kc_EXC_Allocation_ik_EXC_Allocatio,1),
              SDB_Key("s1_EXC_Allocatio",kc_EXC_Allocation_s1_EXC_Allocatio,2),
              SDB_Key("s2_EXC_Allocatio",kc_EXC_Allocation_s2_EXC_Allocatio,3),
              };
 dictptr->SetupStructDef("EXC_Allocation",bf_EXC_Allocation,af_EXC_Allocation,rf_EXC_Allocation,pf_EXC_Allocation,sk_EXC_Allocation,3,8,0);

 char         *kc_EXC_Exchange_ik_EXC_Exchange[] = {
              "sys_ident",
              "" };
 SDB_Key       sk_EXC_Exchange[] = {
              SDB_Key("ik_EXC_Exchange",kc_EXC_Exchange_ik_EXC_Exchange,1),
              };
 dictptr->SetupStructDef("EXC_Exchange",bf_EXC_Exchange,af_EXC_Exchange,rf_EXC_Exchange,pf_EXC_Exchange,sk_EXC_Exchange,1,8,0);

 char         *kc_EXT_Extension_ik_EXT_Extension[] = {
              "sys_ident",
              "" };
 SDB_Key       sk_EXT_Extension[] = {
              SDB_Key("ik_EXT_Extension",kc_EXT_Extension_ik_EXT_Extension,1),
              };
 dictptr->SetupStructDef("EXT_Extension",bf_EXT_Extension,af_EXT_Extension,rf_EXT_Extension,pf_EXT_Extension,sk_EXT_Extension,1,8,0);

 char         *kc_EXT_BLOB_ik_EXT_BLOB[] = {
              "sys_ident",
              "" };
 SDB_Key       sk_EXT_BLOB[] = {
              SDB_Key("ik_EXT_BLOB",kc_EXT_BLOB_ik_EXT_BLOB,1),
              };
 dictptr->SetupStructDef("EXT_BLOB",bf_EXT_BLOB,af_EXT_BLOB,rf_EXT_BLOB,pf_EXT_BLOB,sk_EXT_BLOB,1,8,0);

 char         *kc_EXT_FilePath_ik_EXT_FilePath[] = {
              "sys_ident",
              "" };
 SDB_Key       sk_EXT_FilePath[] = {
              SDB_Key("ik_EXT_FilePath",kc_EXT_FilePath_ik_EXT_FilePath,1),
              };
 dictptr->SetupStructDef("EXT_FilePath",bf_EXT_FilePath,af_EXT_FilePath,rf_EXT_FilePath,pf_EXT_FilePath,sk_EXT_FilePath,1,8,0);

 char         *kc_SDB_ExternFile_ik_Ident[] = {
              "sys_ident",
              "" };
 SDB_Key       sk_SDB_ExternFile[] = {
              SDB_Key("ik_Ident",kc_SDB_ExternFile_ik_Ident,1),
              };
 dictptr->SetupStructDef("SDB_ExternFile",bf_SDB_ExternFile,af_SDB_ExternFile,rf_SDB_ExternFile,pf_SDB_ExternFile,sk_SDB_ExternFile,1,8,0);

 char         *kc_SDB_BinaryFile_ik_SDB_BinaryFil[] = {
              "SDB_ExternFile",
              "" };
 SDB_Key       sk_SDB_BinaryFile[] = {
              SDB_Key("ik_SDB_BinaryFil",kc_SDB_BinaryFile_ik_SDB_BinaryFil,1),
              };
 dictptr->SetupStructDef("SDB_BinaryFile",bf_SDB_BinaryFile,af_SDB_BinaryFile,rf_SDB_BinaryFile,pf_SDB_BinaryFile,sk_SDB_BinaryFile,1,8,0);

 char         *kc_SDB_SDF_File_ik_Ident[] = {
              "sys_ident",
              "" };
 SDB_Key       sk_SDB_SDF_File[] = {
              SDB_Key("ik_Ident",kc_SDB_SDF_File_ik_Ident,1),
              };
 dictptr->SetupStructDef("SDB_SDF_File",bf_SDB_SDF_File,af_SDB_SDF_File,rf_SDB_SDF_File,pf_SDB_SDF_File,sk_SDB_SDF_File,1,8,0);

 char         *kc_SDB_OEL_File_ik_Ident[] = {
              "sys_ident",
              "" };
 SDB_Key       sk_SDB_OEL_File[] = {
              SDB_Key("ik_Ident",kc_SDB_OEL_File_ik_Ident,1),
              };
 dictptr->SetupStructDef("SDB_OEL_File",bf_SDB_OEL_File,af_SDB_OEL_File,rf_SDB_OEL_File,pf_SDB_OEL_File,sk_SDB_OEL_File,1,8,0);

 char         *kc_SDB_XML_Document_ik_Ident[] = {
              "sys_ident",
              "" };
 SDB_Key       sk_SDB_XML_Document[] = {
              SDB_Key("ik_Ident",kc_SDB_XML_Document_ik_Ident,1),
              };
 dictptr->SetupStructDef("SDB_XML_Document",bf_SDB_XML_Document,af_SDB_XML_Document,rf_SDB_XML_Document,pf_SDB_XML_Document,sk_SDB_XML_Document,1,8,0);

 char         *kc_SDB_ODBCRelation_ik_Ident[] = {
              "sys_ident",
              "" };
 SDB_Key       sk_SDB_ODBCRelation[] = {
              SDB_Key("ik_Ident",kc_SDB_ODBCRelation_ik_Ident,1),
              };
 dictptr->SetupStructDef("SDB_ODBCRelation",bf_SDB_ODBCRelation,af_SDB_ODBCRelation,rf_SDB_ODBCRelation,pf_SDB_ODBCRelation,sk_SDB_ODBCRelation,1,8,0);

 char         *kc_SDB_KeyLockInstance_ik_SDB_KeyLockInstance[] = {
              "value",
              "" };
 SDB_Key       sk_SDB_KeyLockInstance[] = {
              SDB_Key("ik_SDB_KeyLockInstance",kc_SDB_KeyLockInstance_ik_SDB_KeyLockInstance,1),
              };
 dictptr->SetupStructDef("SDB_KeyLockInstance",bf_SDB_KeyLockInstance,af_SDB_KeyLockInstance,rf_SDB_KeyLockInstance,pf_SDB_KeyLockInstance,sk_SDB_KeyLockInstance,1,8,0);

 char         *kc_SDB_KeyLockIndex_ik_SDB_KeyLockIndex[] = {
              "index_id",
              "" };
 SDB_Key       sk_SDB_KeyLockIndex[] = {
              SDB_Key("ik_SDB_KeyLockIndex",kc_SDB_KeyLockIndex_ik_SDB_KeyLockIndex,1),
              };
 dictptr->SetupStructDef("SDB_KeyLockIndex",bf_SDB_KeyLockIndex,af_SDB_KeyLockIndex,rf_SDB_KeyLockIndex,pf_SDB_KeyLockIndex,sk_SDB_KeyLockIndex,1,8,0);

 char         *kc_SDB_KeyLock_ik_SDB_KeyLock[] = {
              "sys_ident",
              "" };
 SDB_Key       sk_SDB_KeyLock[] = {
              SDB_Key("ik_SDB_KeyLock",kc_SDB_KeyLock_ik_SDB_KeyLock,1),
              };
 dictptr->SetupStructDef("SDB_KeyLock",bf_SDB_KeyLock,af_SDB_KeyLock,rf_SDB_KeyLock,pf_SDB_KeyLock,sk_SDB_KeyLock,1,8,0);

