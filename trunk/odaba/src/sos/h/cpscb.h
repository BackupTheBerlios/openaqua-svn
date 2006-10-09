 /*******************************************************************/
 /*                                                                 */
 /*                Pool Storage Control Block               (PSCB)  */
 /*  Version 0.1                                          31.10.92  */
 /*******************************************************************/

#ifndef   PSCB_H
#define   PSCB_H

typedef struct  {
  uint32      pecbsize;        /* entry length in bytes          */
  char        pecbstat[4];     /* status of pool entry ( F.A )   */
               } pecb;

#endif