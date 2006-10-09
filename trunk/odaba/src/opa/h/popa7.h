/*******************************************************************/
/*			     S D B				  							   */
/*         Project Includes - General Defines and Error Class      */
/*   Version 0.1                                          12.02.00 */
/*******************************************************************/ 

#ifndef   PSDB_H
#define   PSDB_H

#ifndef    IF_Class
#define    _OPA7_
#endif

#include  <padcstd.h>
#include  <codaba2.h>
#include  <podaba2.h>

#include  <csos4mac.h>
#include  <igvts.h>
#include  <igvtx.h>
#include  <igvtu.h>
#include  <ifil.h>
#include  <imsm.h>
#include  <cactp.h>
#include  <cfctp.h>
#include  <cutimac.h>
#include  <OGUIDdef.h>

#include  <cstats.h>
 
extern    int32 dbf_count;
extern    int32 exd_count;
extern    int32 acb_count;

extern    int32 inti_count;
extern    int32 inti_max;

extern    int32 node_count;
extern    int32 node_max;
extern    int32 node_total;

extern    int32 ctx_count;
extern    int32 ctx_max;

#endif    // PSDB_H
