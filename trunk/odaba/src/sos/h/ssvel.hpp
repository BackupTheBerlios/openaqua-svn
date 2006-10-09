/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/05|16:41:32,95}|(REF)
\class    svel

\brief    System Variable List
          System  variables are  variables, which  can be  passed via an ini- or
          configuration  file (XML). In addition, system variables can be set in
          the application program or in the system environment. 
          System  variables are  searched in  the following sequence (svelget(),
          GetSysVariable()):
          - in the internal table (svel)
          - in the ini- or configuration file
          - in the system environment
          System  variables,  which  could  not  be  located, are added as empty
          variables  to the table  and will not  be reloaded when being searched
          later on. 
          System   variables   usually   are   thread   variables,   i.e.   the 
          GetSysVariable()  function returns a  thread specific system variable.
          Each  thread  inherits  system  variables  from  its  parent thread by
          looking  for system variables  in a hierarchy  of variable lists. When
          looking  for a variable in a hierarchy, searching starts at the bottom
          list.  When the variable could not be found in the list and not in the
          ini-  or  configuration  file,  the  variable is searched in the upper
          list  etc. When not being found in  any list in the hierarchy, finally
          the variable is searched in the system variable.
          The  hierarchy  can  be  maintained using ConnectAt() or ConnectLast()
          and  DisconnectAt() or  DisconnectLast(). Both  functions will connect
          or  disconnect  two  hierarchies.  When  connecting  two  hierarchies,
          PopStop  is  set  for  the  hierarchy  connected  with  the  calling 
          hierarchy.  This is done automatically  by connect functions and reset
          by disconnect functions.

\date     $Date: 2006/04/18 18:50:57,12 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   svel_HPP
#define   svel_HPP

#include "csosdll.h"
class     svel;

#ifndef   GSRT_sve_HPP
#define   GSRT_sve_HPP
#include  <ssve.hpp>
#include  <sGSRT.h>
#endif
#ifndef   DLL_svel_HPP
#define   DLL_svel_HPP
#include  <ssvel.hpp>
#include  <sDLL.h>
#endif
class     sve;
class     svel;
#include  <sIniFile.hpp>
#pragma pack(8)

class  svel :public GSRT(sve)
{
protected  :         IniFile                                     *svelpini ATTR_ALIGN(4);                                    // 
protected  :         char                                         svelmini[128];                                             // 
protected  :         svel                                        *upper_list;                                                // 
protected  :         DLL(svel)                                    children;                                                  // 

public     :
                     IniFile                                     *get_svelpini() { return(svelpini); }
                     char                                        *get_svelmini() { return(svelmini); }
                     svel                                        *get_upper_list() { return(upper_list); }
                     DLL(svel)                                   &get_children() { return(children); }
public     :         SOSImpExp                   logical CheckSection (char *sectionname );
public     :         SOSImpExp                   logical ConnectAt (svel *svelptr );
public     :         SOSImpExp                   logical ConnectTail (svel *svelptr );
public     :         SOSImpExp                   logical ConnectUpper (svel *svelptr );
public     :         SOSImpExp                   logical Copy (svel *srcesvel );
public     :                                     void DisconnectAll (svel *svelptr );
public     :         SOSImpExp                   svel *DisconnectAt (svel *svelptr );
public     :         SOSImpExp                   svel *DisconnectTail (svel *svelptr );
public     :         SOSImpExp                   svel *DisconnectUpper ( );
public     :         SOSImpExp                   char *GetINIFile ( );
public     :         SOSImpExp                   svel *NextSubHierarchy ( );
public     :         SOSImpExp                   svel *Parent ( );
public     :                                     svel *Pop ( );
public     :                                     logical PopStop ( );
public     :                                     svel *Push ( );
public     :         SOSImpExp                   logical RemoveEmpty ( );
public     :                                     void SetPopStop (logical pop_stop );
public     :         SOSImpExp                                           svel (int32 maxe );
public     :         SOSImpExp                   sve *sveladd (char *vnames, char *vtext );
public     :         SOSImpExp                   logical svelcpr (svel *srcesvel );
public     :         SOSImpExp                   logical svelcpy (svel *srcesvel );
public     :         SOSImpExp                   sve *sveleget (char *vnames );
public     :         SOSImpExp                   char *svelexc (char *textptr, uint16 mlen=UNDEF );
public     :         SOSImpExp                   logical svelfini (char *inipath, char *mainsect );
public     :         SOSImpExp                   char *svelget (char *vnames );
public     :         SOSImpExp                   char *svelget (int16 indx, char *vnames );
public     :         SOSImpExp                   char *svelread (char *vnames );
public     :         SOSImpExp                   char *svelread (char *vnames, char *sectname );
public     :         SOSImpExp                   logical svelrmv (char *vnames );
public     :         SOSImpExp                   logical svelset (char *vnames, char *vtext );
public     :         SOSImpExp                   char *svelupd (char *vnames, char *vtext );
public     :         SOSImpExp                                           ~svel ( );
};

#pragma pack()
#endif
