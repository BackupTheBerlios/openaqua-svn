 /*******************************************************************/
 /*                                                                 */
 /*                IDB system structure defines             (IDBD)  */
 /*  Version 0.1                                          11.04.94  */
 /*******************************************************************/

#ifndef   IDBD_H
#define   IDBD_H
#define   SID_SMCE  1          /* ISD structure identification   */
#define   SID_DDE   2          /* DDE structure identification   */
#define   SID_SKY   3          /* sort key                       */
#define   SID_K16   4          /* 16 byte key name               */
#define   SID_SKD   5          /* set key definition             */
#define   SID_MVL   -99        /* MVL structure identification   */
#define   IDB_MVLI  -1         /* MVL for unique instances       */
#define   IDB_MVLD  -2         /* MVL for not sorted instances   */
#define   IDB_MVLF  -15        /* MVL for not difference list    */
#define   IDB_MVLP  -3         /* MVL for not sorted instances   */
#define   IDB_MVLN  -5         /* MVL for not unique instances   */
#define   IDB_MVLL  -6         /* MVL high level index entry     */
#define   IDB_MVLY  -8         /* sorted MVLD                    */
#define   IDB_ICBE  -7         /* Large index header             */
#define   IDB_INS   -4         /* instance                       */
#define   IDB_INSL  -9         /* local instance                 */
#define   IDB_MAIN  'M'        /* main (data base) handle        */
#define   IDB_STR   'S'        /* structure handle               */
#define   IDB_REFR  'R'        /* reference handle               */
#define   IDB_MEMO  'T'        /* internal handle for Memo       */
#define   IDB_DRCT  'D'        /* internally opened handle       */
#define   IDB_IISD  'I'        /* internal handle for Inst.MVL   */
#define   CS_KLN    16         /* standard codeset key length    */
#endif
