isEmpty(PATH_PREFIX) {
   message ("Configure ClientLib")
   PATH_PREFIX=.
   TARGET = odaba_client
   CONFIG += odabalibs
   include (../projects.pri)
   QMAKE_CXXFLAGS *= -fpermissive
   macx: LIBS += -L../../lib  -lodaba_greta -lodaba_zlib -lodaba_sos
}

HEADERS += ../opa/h/sCClient.hpp \
                    ../opa/h/sCSInstanceList.hpp \
                    ../opa/h/sServices.hpp \
                    ../ops/h/sENUM_Value.hpp \
                     ../ops/h/sENUM_ValueList.hpp \
                     ../opa/h/seb_RootBase.hpp \
                     ../opa/h/sDBStructDef.hpp \
                     ../opa/h/sDBFieldDef.hpp \
                     ../opi/h/sPropertyHandle.hpp \
                     ../oql/h/sOPFunctionDecl.hpp \
                     ../ops/h/spc_SDB_Property.hpp \
                     ../ops/h/sSDB_Property.hpp   \
                     ../opa/h/sObjectEntryList.hpp \
                     ../opa/h/sWSList.hpp \
                     ../opa/h/sTypeKey.hpp \
                     ../opi/h/sUtilityHandle.hpp \
                     ../opi/h/sCSUtilityHandle.hpp \
                     ../opa/h/sWorkspaceEntry.hpp \
                     ../opa/h/sWorkspace.hpp \
                     ../ops/h/spTypeInSDB_Member.hpp  \
                     ../ops/h/ssSDB_Member.hpp  \
                     ../ops/h/ssSDB_Member_base.hpp  \
                     ../ops/h/spc_SDB_Member.hpp  \
                     ../ops/h/s_if_SDB_Member.hpp  \
                     ../ops/h/sSDB_Member.hpp \
                     ../ops/h/sSDB_ResourceRef.hpp \
                     ../ops/h/sSDB_Resource.hpp \
                     ../ops/h/spSDB_ResourceRef.hpp \
                     ../opa/h/sTABuffer.hpp \
                     ../opa/h/sDBStructDef.hpp \
                     ../opa/h/xxBViewStructDef.hpp \
                     ../opa/h/sStructDef.hpp \
                     ../opa/h/sDBViewStructDef.hpp \
                     ../oql/h/sOPBase.hpp \
                     ../oql/h/sOperEnvironment.hpp \
                     ../opa/h/sOperation.hpp \


          
        
SOURCES += ../opa/qlib/CClient.cpp \
                    ../opa/qlib/CSInstanceList.cpp \
                    ../opa/qlib/Services.cpp \
                    ../ops/qlib/ENUM_Value.cpp \
                    ../ops/qlib/ENUM_ValueList.cpp \
                    ../opa/qlib/eb_RootBase.cpp \
                    ../opa/qlib/DBStructDef.cpp \
                    ../opa/qlib/DBFieldDef.cpp \
                    ../opi/qlib/PropertyHandle.cpp \
                    ../oql/qlib/OPFunctionDecl.cpp \
                    ../ops/qlib/SDB_Property.cpp \
                    ../ops/qlib/pc_SDB_Property.cpp \
                    ../opa/qlib/ObjectEntryList.cpp \
                    ../opa/qlib/WSList.cpp \
                    ../opa/qlib/TypeKey.cpp \
                    ../opi/qlib/CSUtilityHandle.cpp \
                    ../opi/qlib/UtilityHandle.cpp \
                    ../opa/qlib/WorkspaceEntry.cpp \
                    ../opa/qlib/Workspace.cpp \
                   ../ops/qlib/SDB_Member.cpp \
                   ../ops/qlib/pc_SDB_Member.cpp \
                   ../ops/qlib/sSDB_Member.cpp \
                   ../ops/qlib/pTypeInSDB_Member.cpp \
                   ../ops/qlib/_if_SDB_Member.cpp \
                   ../ops/qlib/sSDB_Member_base.cpp \
                   ../ops/qlib/pSDB_ResourceRef.cpp \
                   ../ops/qlib/SDB_ResourceRef.cpp  \
                   ../ops/qlib/SDB_Resource.cpp  \
                   ../opa/qlib/TABuffer.cpp \
                   ../opa/qlib/StructDef.cpp \
                   ../opa/qlib/DBViewStructDef.cpp \
                   ../oql/qlib/OPBase.cpp \
                   ../oql/qlib/OperEnvironment.cpp \
                   ../opa/qlib/Operation.cpp \
                   ../opi/qlib/OperationHandle.cpp \
                   ../ops/qlib/SDB_Workspace.cpp \
                   ../ops/qlib/SDB_Type.cpp \
                   ../ops/qlib/SDB_Relationship.cpp \
                   ../oql/qlib/SchemaResources.cpp \
                   ../opi/qlib/PIStack.cpp \
                   ../oql/qlib/OPUnary.cpp \
                   ../oql/qlib/OPParmList.cpp \
                   ../oql/qlib/OPDecl.cpp \
                   ../opi/qlib/ODABAClient.cpp \
                   ../opa/qlib/ObjectEntry.cpp \
                   ../opa/qlib/LACObject.cpp \
                   ../opa/qlib/ExpressionReference.cpp \
                   ../ops/qlib/SDB_Reference.cpp \
                   ../ops/qlib/SDB_ObjectExt.cpp \
                   ../ops/qlib/SDB_ObjectVE.cpp \
                   ../ops/qlib/SDB_Index.cpp \
                   ../ops/qlib/SDB_Extend.cpp \
                   ../oql/qlib/OPVariable.cpp \
../opa/qlib/ACTransientReference.cpp
../opa/qlib/ACTransient.cpp
../opa/qlib/ACTopNode.cpp
../opa/qlib/ACTempExtent.cpp
../opa/qlib/ACStructure.cpp