/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EBMainBase

\brief    


\date     $Date: 2006/03/12 19:13:15,62 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EBMainBase_HPP
#define   EBMainBase_HPP

class     EBMainBase;

#include  <sEBSubBase.hpp>
#pragma pack(1)

class  EBMainBase :public EBSubBase
{
protected  :         int64                                        next_mb ATTR_ALIGN(1);                                     //
protected  :         char                                         server_name[16];                                           

public     :
                     char                                        *get_server_name() { return(server_name); }
public     :                                                             EBMainBase (char *filename, char *server=NULL );
public     :                                     void FromPIF (logical pif );
public     :                                     int64 SetNext (int64 nextpos );
public     :                                     void ToPIF (logical pif );
public     :                                     int64 get_next_mb ( );
};

#pragma pack()
#endif
