 /*******************************************************************/
 /*                                                                 */ 
 /*                                                      (CS_FCTP)  */
 /*  Version 0.1                                          30.01.95  */
 /*******************************************************************/

#ifndef   CS_FCTP_H
#define   CS_FCTP_H

class  CS_Connection;
class  CSInstanceList;

typedef logical (*CS_FCTP)( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result );

#endif