 /*******************************************************************/
 /*                                                                 */
 /*                Structure MD Includes                    (SMCB)  */
 /*  Version 0.1                                          16.03.97  */
 /*******************************************************************/

#ifndef   SMCBMAC_H
#define   SMCBMAC_H

#include  <csmcbdef.h>
#include  <cSDB_AT.h>
#include  <cSDB_ST.h>
#include  <cSDB_SET.h>

#include  <sDLL.h>
#define   lkcb   DLL(kcb)

#include  <ssrt.hpp>
#include  <sksrt.hpp>

#ifndef   SFMC_HPP       // old style
#define   SFMC_HPP       // old style
#ifndef   GSRT_fmcb_HPP 
#define   GSRT_fmcb_HPP 
#include  <sfmcb.hpp>
#include  <sGSRT.h>
GSRT_dcl   (fmcb)
#endif
#endif                   // old style

#include  <sfmcl.hpp>
#include  <sacc.hpp>   
#include  <ssmcb.hpp>

#ifndef   SFCB_HPP       // old style
#define   SFCB_HPP       // old style
#ifndef   GSRT_fcb_HPP 
#define   GSRT_fcb_HPP 
#include  <sfcb.hpp>
#include  <sGSRT.h>
GSRT_dcl   (fcb)
#endif
#endif                   // old style

//#include  <sscb.hpp>
//#include  <sGSCB.h>

#ifndef   SKFC_HPP      // old style
#define   SKFC_HPP      // old style
#ifndef   GSRT_kfc_HPP 
#define   GSRT_kfc_HPP 
#include  <skfc.hpp>
#include  <sGSRT.h>
GSRT_dcl   (kfc)
#endif
#endif                  // old style

#ifndef   CKCB_HPP      // old style
#define   CKCB_HPP      // old style
#ifndef   GSCB_kfc_HPP 
#define   GSCB_kfc_HPP 
#include  <skfc.hpp>
#include  <skfcl.hpp>   // achtung!! dieses include würde derzeit nicht generiert!!!
#include  <sGSCB.h>
GSCB_dcl   (kfc)
#endif
#endif                  // old style

#include  <skcb.hpp>

#include  <sdfs.hpp>

#endif
