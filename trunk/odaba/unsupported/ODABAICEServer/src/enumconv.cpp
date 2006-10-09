#include <enumconv.h>
// handwritten - not able to generate from database yet
::OPI::PIACC enumcpp2ice(::PIACC c){
    switch(c){
    case PI_Read: return ::OPI::piaREAD;
    case PI_Write: return ::OPI::piaWRITE;
    case PI_Update: return ::OPI::piaUPDATE;
    case PI_undefined: return ::OPI::piaUNDEFINED;
    }
    return ::OPI::piaREAD;
}
::PIACC enumice2cpp(::OPI::PIACC c){
    switch(c){
    case ::OPI::piaREAD: return PI_Read;
    case ::OPI::piaWRITE: return PI_Write;
    case ::OPI::piaUPDATE: return PI_Update;
    case ::OPI::piaUNDEFINED: return PI_undefined;
    }
    return PI_undefined;
}

::OPI::PIREPL enumcpp2ice(::PIREPL c){
    switch(c){
    case  REPL_GUID: return ::OPI::piaREPLGUID;
    case  REPL_direct: return ::OPI::piaREPLDIRECT;
    case  REPL_none: return ::OPI::piaREPLNONE;
    case  REPL_local: return ::OPI::piaREPLLOCAL;
    case  REPL_all: return ::OPI::piaREPLALL;
    case  REPL_instance: return ::OPI::piaREPLINSTANCE;
    case  REPL_relationships: return ::OPI::piaREPLRELATIONSHIPS;
    case  REPL_no_create: return ::OPI::piaREPLNOCREATE;
    }
    return ::OPI::piaREPLNOCREATE;
}
::PIREPL enumice2cpp(::OPI::PIREPL  c){
    switch(c){
    case ::OPI::piaREPLGUID:return  REPL_GUID;
    case ::OPI::piaREPLDIRECT:return  REPL_direct;
    case ::OPI::piaREPLNONE:return  REPL_none;
    case ::OPI::piaREPLLOCAL:return  REPL_local;
    case ::OPI::piaREPLALL:return  REPL_all;
    case ::OPI::piaREPLINSTANCE:return  REPL_instance;
    case ::OPI::piaREPLRELATIONSHIPS:return  REPL_relationships;
    case ::OPI::piaREPLNOCREATE:return  REPL_no_create;
    }
    return REPL_no_create;
}


::OPI::PIADEF enumcpp2ice(::PIADEF c){
    switch(c){
    case  PI_unknown: return ::OPI::piaUNKNOWN;
    case  PI_Exclusive: return ::OPI::piaEXCLUSIVE;
    case  PI_Share: return ::OPI::piaSHARE;
    }
    return ::OPI::piaUNKNOWN;
}
::PIADEF enumice2cpp(::OPI::PIADEF  c){
    switch(c){
    case ::OPI::piaUNKNOWN:return  PI_unknown;
    case ::OPI::piaEXCLUSIVE:return  PI_Exclusive;
    case ::OPI::piaSHARE:return  PI_Share;
    }
    return PI_unknown;
}

::ResourceTypes enumice2cpp(::OPI::ResourceTypes c){
    switch (c){
    case OPI::resAUTOMATIC: return RES_automatic;
    case OPI::resSERVER: return RES_server;
    case OPI::resLOCAL: return RES_local;
    case OPI::resSERVERINTERN: return RES_server_intern;
    }
    return RES_automatic;
}
::OPI::ResourceTypes enumcpp2ice(::ResourceTypes c){
    switch(c){
    case RES_automatic: return ::OPI::resAUTOMATIC;
    case RES_server: return ::OPI::resSERVER;
    case RES_local: return ::OPI::resLOCAL;
    case RES_server_intern: return ::OPI::resSERVERINTERN;
    }
    return ::OPI::resAUTOMATIC;
}

::ApplicationTypes enumice2cpp(::OPI::ApplicationTypes c){
    switch(c){
    case ::OPI::aptWINDOWS : return APT_Windows;
    case ::OPI::aptCONSOLE : return APT_Console;
    }
    return APT_Console;
}

::OPI::ApplicationTypes enumcpp2ice(::ApplicationTypes c){
    switch(c){
    case APT_Windows: return ::OPI::aptWINDOWS;
    case APT_Console: return ::OPI::aptCONSOLE;
    }
    return ::OPI::aptCONSOLE;
}

