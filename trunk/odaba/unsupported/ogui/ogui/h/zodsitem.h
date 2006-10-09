#include <sODSItem.hpp>  
#include <sDLL.h>  
#include <sODS.hpp>  

#define FIRE_SIGNAL( list, listtype, listdlli, code ) \
 { DLL(listtype) it(list); \
   while( listtype* obj= it.GetNext() ) \
     { code; } } \

#define FIRE_ODS_SIGNAL( code ) \
  FIRE_SIGNAL( odslist, ODS, ODSItemodslistDLLItem, code )

#define FIRE_CHILD_SIGNAL( code ) \
  FIRE_SIGNAL( subs, ODSItem, ODSItem, code )
