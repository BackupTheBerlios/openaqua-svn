
TARGET = odaba_adk
CONFIG += odabalibs
include (../projects.pri)

# Input
HEADERS += h/cadkctxidll.h \
           h/iCtxClasses.h \
           h/iCtxIncl.h \
           h/iCTXInterface.h \
           h/iGlobalC.h \
           h/isysctxi.h \
           h/padkctxi.h \
           h/sCTXInterface.h \
           h/sdb_ODE.hpp \
           h/sGlobalC.h \
           h/spActionList.hpp \
           h/spButtons_StyleAction.hpp \
           h/spc0_ODC_FunctImp.hpp \
           h/spc0_ODC_ImpClass.hpp \
           h/spc0_ODC_PFunction.hpp \
           h/spc0_SDB_Member.hpp \
           h/spc0_SDB_Structure.hpp \
           h/spc0_SDB_ValueList.hpp \
           h/spc_ADK_Allign.hpp \
           h/spc_ADK_Button.hpp \
           h/spc_ADK_Button_.hpp \
           h/spc_ADK_Class.hpp \
           h/spc_ADK_EventAction.hpp \
           h/spc_ADK_Field.hpp \
           h/spc_ADK_Field_.hpp \
           h/spc_ADK_FieldControl.hpp \
           h/spc_ADK_FieldControl_.hpp \
           h/spc_ADK_KeyEvent.hpp \
           h/spc_ADK_StyleElement.hpp \
           h/spc_ADK_StyleElement_.hpp \
           h/spColumns_StyleAction.hpp \
           h/spFields_StyleAction.hpp \
           h/spRegions_StyleAction.hpp \
           h/ss_err.hpp \
           h/ssADK_EventAction.hpp \
           h/ssADK_FieldControl.hpp \
           h/ssADKLanguageDependend.hpp \
           h/ssHTMLDescriptor.hpp \
           h/ssLanguageDependendBase.hpp \
           h/ssODS_Description.hpp
SOURCES +=         qlib/CTXInterface.cpp \
        qlib/pActionList.cpp \
        qlib/pButtons_StyleAction.cpp \
        qlib/pColumns_StyleAction.cpp \
        qlib/pFields_StyleAction.cpp \
        qlib/pRegions_StyleAction.cpp \
        qlib/pc0_SDB_Member.cpp \
        qlib/pc0_SDB_Structure.cpp \
        qlib/pc0_SDB_ValueList.cpp \
        qlib/pc_ADK_Allign.cpp \
        qlib/pc_ADK_Button.cpp \
        qlib/pc_ADK_Class.cpp \
        qlib/pc_ADK_EventAction.cpp \
        qlib/pc_ADK_Field.cpp \
        qlib/pc_ADK_FieldControl.cpp \
        qlib/pc_ADK_KeyEvent.cpp \
        qlib/pc_ADK_StyleElement.cpp \
        qlib/sADKLanguageDependend.cpp \
        qlib/sADK_EventAction.cpp \
        qlib/sADK_FieldControl.cpp \
        qlib/sLanguageDependendBase.cpp \
        