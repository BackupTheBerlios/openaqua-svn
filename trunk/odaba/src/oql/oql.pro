

isEmpty(PATH_PREFIX) {
   message ("Configure OQL")
   PATH_PREFIX=.
   TARGET = odaba_oql
   CONFIG += odabalibs
   include (../projects.pri)
   #macx: LIBS +=  -L../../lib -lodaba_greta -lodaba_zlib -lodaba_sos
}


# Input
HEADERS += $$PATH_PREFIX/h/_cs_def_OQL.hpp \
           $$PATH_PREFIX/h/_cs_tbl_OQL.hpp \
           $$PATH_PREFIX/h/cDebugModi.h \
           $$PATH_PREFIX/h/cExecReturnCodes.h \
           $$PATH_PREFIX/h/cOPNodeTypes.h \
           $$PATH_PREFIX/h/cOQL_CodeBlock.h \
           $$PATH_PREFIX/h/cVHN_Types.h \
           $$PATH_PREFIX/h/dlincl.h \
           $$PATH_PREFIX/h/iopbase.h \
           $$PATH_PREFIX/h/ioshell.h \
           $$PATH_PREFIX/h/oqlglob.h \
           $$PATH_PREFIX/h/poql.h \
           $$PATH_PREFIX/h/sCLICollection.hpp \
           $$PATH_PREFIX/h/sCLIDataSource.hpp \
           $$PATH_PREFIX/h/sCLInterpreter.hpp \
           $$PATH_PREFIX/h/sCLInterpreterBase.hpp \
           $$PATH_PREFIX/h/sDBreakPoint.hpp \
           $$PATH_PREFIX/h/sDLInterpreter.hpp \
           $$PATH_PREFIX/h/sOqlExtentList.hpp \
           $$PATH_PREFIX/h/sOPAccessPath.hpp \
           $$PATH_PREFIX/h/sOPAccessPathDecl.hpp \
           $$PATH_PREFIX/h/sOPBase.hpp \
           $$PATH_PREFIX/h/sOPBaseCollection.hpp \
           $$PATH_PREFIX/h/sOPBinary.hpp \
           $$PATH_PREFIX/h/sOPConstant.hpp \
           $$PATH_PREFIX/h/sOPDecl.hpp \
           $$PATH_PREFIX/h/sOPEnumeration.hpp \
           $$PATH_PREFIX/h/sOperEnvironment.hpp \
           $$PATH_PREFIX/h/sOperResources.hpp \
           $$PATH_PREFIX/h/sOPExpressionDecl.hpp \
           $$PATH_PREFIX/h/sOPExtent.hpp \
           $$PATH_PREFIX/h/sOPFunctionDecl.hpp \
           $$PATH_PREFIX/h/sOPGlobalVariable.hpp \
           $$PATH_PREFIX/h/sOPLocalVariable.hpp \
           $$PATH_PREFIX/h/sOPOperation.hpp \
           $$PATH_PREFIX/h/sOPOperationDecl.hpp \
           $$PATH_PREFIX/h/sOPOQLOperation.hpp \
           $$PATH_PREFIX/h/sOPParameter.hpp \
           $$PATH_PREFIX/h/sOPParmList.hpp \
           $$PATH_PREFIX/h/sOPProperty.hpp \
           $$PATH_PREFIX/h/sOPSynBlock.hpp \
           $$PATH_PREFIX/h/sOPSynBreak.hpp \
           $$PATH_PREFIX/h/sOPSynCase.hpp \
           $$PATH_PREFIX/h/sOPSynContinue.hpp \
           $$PATH_PREFIX/h/sOPSynError.hpp \
           $$PATH_PREFIX/h/sOPSynExceptHandling.hpp \
           $$PATH_PREFIX/h/sOPSynException.hpp \
           $$PATH_PREFIX/h/sOPSynFor.hpp \
           $$PATH_PREFIX/h/sOPSynIf.hpp \
           $$PATH_PREFIX/h/sOPSynLeave.hpp \
           $$PATH_PREFIX/h/sOPSynNVHandling.hpp \
           $$PATH_PREFIX/h/sOPSynReturn.hpp \
           $$PATH_PREFIX/h/sOPSynSwitch.hpp \
           $$PATH_PREFIX/h/sOPSynWhile.hpp \
           $$PATH_PREFIX/h/sOPSystemVariable.hpp \
           $$PATH_PREFIX/h/sOPUnary.hpp \
           $$PATH_PREFIX/h/sOPVariable.hpp \
           $$PATH_PREFIX/h/sOPVariableSpec.hpp \
           $$PATH_PREFIX/h/sOSchema.hpp \
           $$PATH_PREFIX/h/sOScript.hpp \
           $$PATH_PREFIX/h/sOScriptFile.hpp \
           $$PATH_PREFIX/h/sSchemaResources.hpp
SOURCES +=         $$PATH_PREFIX/qlib/CLICollection.cpp \
        $$PATH_PREFIX/qlib/CLIDataSource.cpp \
        $$PATH_PREFIX/qlib/CLInterpreter.cpp \
        $$PATH_PREFIX/qlib/CLInterpreterBase.cpp \
        $$PATH_PREFIX/qlib/DBreakPoint.cpp \
        $$PATH_PREFIX/qlib/DLInterpreter.cpp \
        $$PATH_PREFIX/qlib/OqlExtentList.cpp \
        $$PATH_PREFIX/qlib/OPAccessPath.cpp \
        $$PATH_PREFIX/qlib/OPAccessPathDecl.cpp \
        $$PATH_PREFIX/qlib/OPBase.cpp \
        $$PATH_PREFIX/qlib/OPBaseCollection.cpp \
        $$PATH_PREFIX/qlib/OPBinary.cpp \
        $$PATH_PREFIX/qlib/OPConstant.cpp \
        $$PATH_PREFIX/qlib/OPDecl.cpp \
        $$PATH_PREFIX/qlib/OPEnumeration.cpp \
        $$PATH_PREFIX/qlib/OPExpressionDecl.cpp \
        $$PATH_PREFIX/qlib/OPExtent.cpp \
        $$PATH_PREFIX/qlib/OPFunctionDecl.cpp \
        $$PATH_PREFIX/qlib/OPGlobalVariable.cpp \
        $$PATH_PREFIX/qlib/OPLocalVariable.cpp \
        $$PATH_PREFIX/qlib/OPOperation.cpp \
        $$PATH_PREFIX/qlib/OPOperationDecl.cpp \
        $$PATH_PREFIX/qlib/OPParameter.cpp \
        $$PATH_PREFIX/qlib/OPParmList.cpp \
        $$PATH_PREFIX/qlib/OPProperty.cpp \
        $$PATH_PREFIX/qlib/OPSynBlock.cpp \
        $$PATH_PREFIX/qlib/OPSynBreak.cpp \
        $$PATH_PREFIX/qlib/OPSynCase.cpp \
        $$PATH_PREFIX/qlib/OPSynContinue.cpp \
        $$PATH_PREFIX/qlib/OPSynError.cpp \
        $$PATH_PREFIX/qlib/OPSynExceptHandling.cpp \
        $$PATH_PREFIX/qlib/OPSynException.cpp \
        $$PATH_PREFIX/qlib/OPSynFor.cpp \
        $$PATH_PREFIX/qlib/OPSynIf.cpp \
        $$PATH_PREFIX/qlib/OPSynLeave.cpp \
        $$PATH_PREFIX/qlib/OPSynNVHandling.cpp \
        $$PATH_PREFIX/qlib/OPSynReturn.cpp \
        $$PATH_PREFIX/qlib/OPSynSwitch.cpp \
        $$PATH_PREFIX/qlib/OPSynWhile.cpp \
        $$PATH_PREFIX/qlib/OPSystemVariable.cpp \
        $$PATH_PREFIX/qlib/OPUnary.cpp \
        $$PATH_PREFIX/qlib/OPVariable.cpp \
        $$PATH_PREFIX/qlib/OPVariableSpec.cpp \
        $$PATH_PREFIX/qlib/OSchema.cpp \
        $$PATH_PREFIX/qlib/OScript.cpp \
        $$PATH_PREFIX/qlib/OScriptFile.cpp \
        $$PATH_PREFIX/qlib/OperEnvironment.cpp \
        $$PATH_PREFIX/qlib/OperResources.cpp \
        $$PATH_PREFIX/qlib/SchemaResources.cpp \
        