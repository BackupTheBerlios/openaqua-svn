 /*******************************************************************/
 /*                                                                 */
 /*                OPA Utility macro definitions                    */
 /*  Version 0.1                                          25.3.96   */
 /*******************************************************************/

#ifndef   UTIMAC_H
#define   UTIMAC_H

#include  <copadll.h>

#include  <codaba2.h>

#include  <sExecExchange.hpp>
#include  <sDataSourceHandle.hpp>
#include  <sUtilityHandle.hpp>
#include  <sCSUtilityHandle.hpp>
#include  <sODABAClient.hpp>

#define sdbuptr  UtilityControlBlock()

 /*******************************************************************/

#define   SDBUERV1(str,len)  { SDBError().SetErrorVariable(1, str, len); }
#define   SDBUERV2(str,len)  { SDBError().SetErrorVariable(2, str, len); }
#define   SDBUERV3(str,len)  { SDBError().SetErrorVariable(3, str, len); }
#define   SDBUERV4(str,len)  { SDBError().SetErrorVariable(4, str, len); }
#define   SDBUERV5(str,len)  { SDBError().SetErrorVariable(5, str, len); }

 /*******************************************************************/

#endif
