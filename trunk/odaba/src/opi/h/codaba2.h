/*******************************************************************/
/*                           O P A 7                                                       */
/*                      User Macro Definitions                     */
/*   Version 2.0                                          15.08.00 */
/*******************************************************************/ 

#ifndef   ODABA2_H
#define   ODABA2_H

#define   CUR_VERSION     USHORTMAX
#define   CUR_INSTANCE    AUTO
#define   FIRST_INSTANCE  (int32)0
#define   LAST_INSTANCE   LONGMAX
#define   BACKWARD        -1
#define   FOREWARD        1

#include  <padcstd.h>
#include  <csosdll.h>
#include  <copadll.h>
#include  <compatibility.h>

 /*******************************************************************/ 

#include  <cfctp.h>
#include  <cactp.h>
#include  <coctp.h>
#include  <cevtp.h>
#include  <scfte.hpp>

#include  <csdberr.h>
#include  <coqlerr.h>

#include  <cResourceTypes.h>
#include  <cST_OpCodes.h>
#include  <cFunctionTypes.h>
#include  <cNodeTypes.h> //daGnuwwel : es sollte nicht so sein...nicht so sein...nich so sein... ... ...
#include  <cPIACC.h>
#include  <cPIADEF.h>
#include  <cPIREPL.h>
#include  <cADT_Types.h>
#include  <sdbdt.hpp>
#include  <sdbtm.hpp>
#include  <sdttm.hpp>
#include  <csmcbmac.h>
#include  <cSDB_RLEV.h>
#include  <isosi.h>

#include  <cActionType.h>

#include  <sKeyClass.hpp>
#include  <sInstance.hpp>

#include  <sDictionaryHandle.hpp>
#include  <sODABAClient.hpp>
#include  <sPropertyHandle.hpp>
#include  <sOperationHandle.hpp>
#include  <sServices.hpp>
#include  <sUtilityHandle.hpp>
#include  <sPI.hpp>
#define  MEMO  mem
#ifndef  P_mem_HPP
#define  P_mem_HPP
class  mem 
{
  public : char   memo[1];
};
#pragma pack(4)
PI_dcl(mem)
#pragma pack()
#endif

#include  <sPIStack.hpp>
#include  <sParmList.hpp>
//neu
#include  <sDBIndex.hpp>
#include  <sFieldDef.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBExtend.hpp>
#include  <sDBStructDef.hpp>

#include  <sCTX_DataBase.hpp>
#include  <sCTX_Object.hpp>
#include  <sCTX_Structure.hpp>
#include  <sCTX_Property.hpp>

#include  <sEventHandler.hpp>

 /*******************************************************************/ 

#endif



