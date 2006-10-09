 /*******************************************************************/ 
 /*                                                                 */
 /*                                                         (OCTP)  */
 /*  Version 0.1                                          10.05.2004*/
 /*******************************************************************/

#ifndef   CCTP_H
#define   CCTP_H

class     PropertyHandle;
class     ParmList;
typedef logical  (__far __cdecl *CCTP)( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *, ExecutionTypes);

#define CLINK( funcptr ) FunctLink ( (CCTP)(logical (*)(PropertyHandle *, PropertyHandle *,ParmList *,char *,ExecutionTypes)) &funcptr)

#endif
