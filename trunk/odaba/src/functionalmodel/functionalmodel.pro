isEmpty(PATH_PREFIX) {
   message "Configure OPA"
   PATH_PREFIX=.
   TARGET = odaba_functional_model
   CONFIG += odabalibs
   include (../projects.pri)
   #QMAKE_CXXFLAGS *= -fpermissive
   macx: LIBS += -L../../lib  -lodaba_greta -lodaba_zlib -lodaba_sos
}




# Input
HEADERS += $$PATH_PREFIX/h/cClassModLevel.h \
           $$PATH_PREFIX/h/cclrkey.h \
           $$PATH_PREFIX/h/cCompileStates.h \
           $$PATH_PREFIX/h/cContextTypes.h \
           $$PATH_PREFIX/h/cExternalResource.h \
           $$PATH_PREFIX/h/cIncRef_Level.h \
           $$PATH_PREFIX/h/cMethodTypes.h \
           $$PATH_PREFIX/h/cProcessingTypes.h \
           $$PATH_PREFIX/h/cProgramLanguage.h \
           $$PATH_PREFIX/h/cRTTI_Types.h \
           $$PATH_PREFIX/h/csysstr.h \
           $$PATH_PREFIX/h/cSystemPathes.h \
           $$PATH_PREFIX/h/iCtxClasses.h \
           $$PATH_PREFIX/h/iCTXFunctionalModel.h \
           $$PATH_PREFIX/h/iCtxIncl.h \
           $$PATH_PREFIX/h/ifmi.h \
           $$PATH_PREFIX/h/itest.h \
           $$PATH_PREFIX/h/pfmodel.h \
           $$PATH_PREFIX/h/s_if_ODABA2_extern.hpp \
           $$PATH_PREFIX/h/s_if_ODC_Executable.hpp \
           $$PATH_PREFIX/h/s_if_ODC_FunctImp.hpp \
           $$PATH_PREFIX/h/s_if_ODC_ImpClass.hpp \
           $$PATH_PREFIX/h/s_if_ODC_PFunction.hpp \
           $$PATH_PREFIX/h/s_if_ODC_Project.hpp \
           $$PATH_PREFIX/h/s_if_ODC_Variable.hpp \
           $$PATH_PREFIX/h/sCTXFunctionalModel.h \
           $$PATH_PREFIX/h/sFileMemo.hpp \
           $$PATH_PREFIX/h/sODABA2_extern.hpp \
           $$PATH_PREFIX/h/sODC_ApplLicence.hpp \
           $$PATH_PREFIX/h/sODC_BaseContext.hpp \
           $$PATH_PREFIX/h/sODC_Database.hpp \
           $$PATH_PREFIX/h/sODC_DBIdent.hpp \
           $$PATH_PREFIX/h/sODC_DBLicence.hpp \
           $$PATH_PREFIX/h/sODC_Environment.hpp \
           $$PATH_PREFIX/h/sODC_Executable.hpp \
           $$PATH_PREFIX/h/sODC_FunctGroup.hpp \
           $$PATH_PREFIX/h/sODC_FunctImp.hpp \
           $$PATH_PREFIX/h/sODC_Function.hpp \
           $$PATH_PREFIX/h/sODC_ImpClass.hpp \
           $$PATH_PREFIX/h/sODC_Include.hpp \
           $$PATH_PREFIX/h/sODC_Main.hpp \
           $$PATH_PREFIX/h/sODC_Module.hpp \
           $$PATH_PREFIX/h/sODC_NamedObject.hpp \
           $$PATH_PREFIX/h/sODC_PFunction.hpp \
           $$PATH_PREFIX/h/sODC_Project.hpp \
           $$PATH_PREFIX/h/sODC_ProjRef.hpp \
           $$PATH_PREFIX/h/sODC_Variable.hpp \
           $$PATH_PREFIX/h/sODC_View.hpp \
           $$PATH_PREFIX/h/sODC_ViewPath.hpp \
           $$PATH_PREFIX/h/spc_ODC_ClassRef.hpp \
           $$PATH_PREFIX/h/spc_ODC_compile_object_base.hpp \
           $$PATH_PREFIX/h/spc_ODC_Executable.hpp \
           $$PATH_PREFIX/h/spc_ODC_FunctImp.hpp \
           $$PATH_PREFIX/h/spc_ODC_ImpClass.hpp \
           $$PATH_PREFIX/h/spc_ODC_Main.hpp \
           $$PATH_PREFIX/h/spc_ODC_PFunction.hpp \
           $$PATH_PREFIX/h/spc_ODC_Project.hpp \
           $$PATH_PREFIX/h/spc_ODC_Variable.hpp \
           $$PATH_PREFIX/h/spc_SDB_TypeRef_fm.hpp \
           $$PATH_PREFIX/h/spc_TopicFromOldStyle.hpp \
           $$PATH_PREFIX/h/spRetvalInODC_Function.hpp \
           $$PATH_PREFIX/h/ssODC_Executable.hpp \
           $$PATH_PREFIX/h/ssODC_FunctImp.hpp \
           $$PATH_PREFIX/h/ssODC_ImpClass.hpp \
           $$PATH_PREFIX/h/ssODC_PFunction.hpp \
           $$PATH_PREFIX/h/ssODC_Project.hpp \
           $$PATH_PREFIX/h/ssODC_Variable.hpp \
           $$PATH_PREFIX/h/ssView.hpp \
           $$PATH_PREFIX/h/stest.hpp
SOURCES +=          $$PATH_PREFIX/qlib/CTXFunctionalModel.cpp \
         $$PATH_PREFIX/qlib/FileMemo.cpp \
         $$PATH_PREFIX/qlib/ODC_BaseContext.cpp \
         $$PATH_PREFIX/qlib/ODC_Database.cpp \
         $$PATH_PREFIX/qlib/ODC_Environment.cpp \
         $$PATH_PREFIX/qlib/ODC_Executable.cpp \
         $$PATH_PREFIX/qlib/ODC_FunctImp.cpp \
         $$PATH_PREFIX/qlib/ODC_Function.cpp \
         $$PATH_PREFIX/qlib/ODC_ImpClass.cpp \
         $$PATH_PREFIX/qlib/ODC_Include.cpp \
         $$PATH_PREFIX/qlib/ODC_Main.cpp \
         $$PATH_PREFIX/qlib/ODC_PFunction.cpp \
         $$PATH_PREFIX/qlib/ODC_Project.cpp \
         $$PATH_PREFIX/qlib/ODC_Variable.cpp \
         $$PATH_PREFIX/qlib/ODC_View.cpp \
         $$PATH_PREFIX/qlib/fmi.cpp \
         $$PATH_PREFIX/qlib/pRetvalInODC_Function.cpp \
         $$PATH_PREFIX/qlib/pc_ODC_Executable.cpp \
         $$PATH_PREFIX/qlib/pc_ODC_FunctImp.cpp \
         $$PATH_PREFIX/qlib/pc_ODC_ImpClass.cpp \
         $$PATH_PREFIX/qlib/pc_ODC_Main.cpp \
         $$PATH_PREFIX/qlib/pc_ODC_PFunction.cpp \
         $$PATH_PREFIX/qlib/pc_ODC_Project.cpp \
         $$PATH_PREFIX/qlib/pc_ODC_Variable.cpp \
         $$PATH_PREFIX/qlib/pc_ODC_compile_object_base.cpp \
         $$PATH_PREFIX/qlib/pc_SDB_TypeRef_fm.cpp \
         $$PATH_PREFIX/qlib/sODC_Executable.cpp \
         $$PATH_PREFIX/qlib/sODC_FunctImp.cpp \
         $$PATH_PREFIX/qlib/sODC_ImpClass.cpp \
         $$PATH_PREFIX/qlib/sODC_PFunction.cpp \
         $$PATH_PREFIX/qlib/sODC_Project.cpp \
         $$PATH_PREFIX/qlib/sODC_Variable.cpp \
         $$PATH_PREFIX/qlib/sView.cpp \
         