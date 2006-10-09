 /*******************************************************************/
 /*                                                                 */
 /*                OPA Utility macro definitions                    */
 /*  Version 0.1                                          25.3.96   */
 /*******************************************************************/

#ifndef   UTIHDLMAC_H
#define   UTIHDLMAC_H

// class     Window;
// class     StatusBar;

#include  <copadll.h>
#include  <sUtilityHandle.hpp>
extern    OPI7ImpExp UtilityHandle   *uti_handle;

 /*******************************************************************/

#define   SDBUERV1(str,len)  { uti_handle->SetErrorVariable(1, str, len); }
#define   SDBUERV2(str,len)  { uti_handle->SetErrorVariable(2, str, len); }
#define   SDBUERV3(str,len)  { uti_handle->SetErrorVariable(3, str, len); }
#define   SDBUERV4(str,len)  { uti_handle->SetErrorVariable(4, str, len); }
#define   SDBUERV5(str,len)  { uti_handle->SetErrorVariable(5, str, len); }

 /*******************************************************************/

#define   MAXPOS 6
#define   OT_MVLI 1
#define   OT_MVLD 2
#define   OT_MVLP 3
#define   OT_MEMO 4
#define   OT_INST 5
#define   OT_ICBE 6
#define   OT_MVLN 7
#define   OT_MVLL 8
#define   OT_INSL 9

#endif
