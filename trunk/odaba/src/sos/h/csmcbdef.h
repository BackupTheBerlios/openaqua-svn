 /*******************************************************************/
 /*                                                                 */
 /*                Structure MD Defines                     (SMCB)  */
 /*  Version 0.1                                          23.08.95  */
 /*******************************************************************/

 /* WARNING: This include file can not be generated  */


#ifndef   SMCBDEF_H
#define   SMCBDEF_H

// V6, only
#define   T_CSTRING  -15        /* coded string                   */
#define   T_UCHAR    -2         /* unsigned character             */
// end V6

#define   T_CHAR     -1         /* character                      */
#define   T_GUID     -2         /* global unique identifier       */
#define   T_INT      -3         /* integer                        */
#define   T_UINT     -4         /* unsigned integer               */
#define   T_MEMO     -5         /* text                           */
#define   T_VOID     -6         /* any type                       */
#define   T_DATE     -7         /* date                           */
#define   T_TIME     -8         /* time                           */
#define   T_LO       -9         /* logical                        */
#define   T_STRING   -10        /* character string               */
#define   T_BIT      -11        /* bit string                     */
#define   T_REAL     -12        /* real value (float)             */
#define   T_DATETIME -13        /* datetime                       */
#define   T_CCHAR    -14        /* coded character                */
#define   T_BLOB     -15        /* binary large object            */
//                   -16          reserverved for any coded datatype
//                   -17          should never be used
#define   T_NONE     -99        /* keien Typangabe                */

#define   T_MAX      15         /* number of base types           */

#define   R_DIRECT   0          /* pointer level 0                */
#define   R_GENERIC  -2         /* generisches Feld               */
#define   R_INTERN   -10        /* not saved in data base         */
#define   R_REFR     -99        /* reference to substructure      */

#define   REF_PRIV   1          /* private ( ==exclusive)         */
#define   REF_PUBL   2          /* public  ( ==share)             */

#endif
