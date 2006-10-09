TARGET = odaba_odcp
CONFIG += odabaqtlibs
include (../../projects.pri)

# Input
HEADERS += h/codcp8mac.h \
           h/codcpdll.h \
           h/cperrmac.h \
           h/cuctx.h \
           h/fctypes.h \
           h/iOGUI_Interface.h \
           h/iUCTXInterface.h \
           h/ope80.h \
           h/podcp8.h \
           h/sCTX_Administration.hpp \
           h/sCTX_Application.hpp \
           h/sCTX_Control.hpp \
           h/sCTX_Design.hpp \
           h/sCTX_Document.hpp \
           h/sCTX_GUIBase.hpp \
           h/sCTX_Project.hpp \
           h/sDesignerMode.hpp \
           h/sDesignerModeControl.hpp \
           h/sDesignerModeControlFactory.hpp \
           h/sDesignerModeFactory.hpp \
           h/sDMCLayoutItem.hpp \
           h/sGUIVariables.hpp \
           h/sInputArea.hpp \
           h/soe_helper.hpp \
           h/sOGUI_Interface.h \
           h/sOutputArea.hpp \
           h/sUCTX_dll.hpp \
           h/sUCTXInterface.h \
           h/unxdl.h \
           h/woe80.h
SOURCES +=        qlib/CTX_Administration.cpp \
       qlib/CTX_Application.cpp \
       qlib/CTX_Control.cpp \
       qlib/CTX_Design.cpp \
       qlib/CTX_Document.cpp \
       qlib/CTX_GUIBase.cpp \
       qlib/CTX_Project.cpp \
       qlib/DMCLayoutItem.cpp \
       qlib/DesignerMode.cpp \
       qlib/DesignerModeControl.cpp \
       qlib/DesignerModeControlFactory.cpp \
       qlib/DesignerModeFactory.cpp \
       qlib/GUIVariables.cpp \
       qlib/InputArea.cpp \
       qlib/OGUI_Interface.cpp \
       qlib/OutputArea.cpp \
       qlib/UCTXInterface.cpp \
       qlib/UCTX_dll.cpp \
       