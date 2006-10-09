/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EBSubBase

\brief    


\date     $Date: 2006/03/12 19:13:16,07 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EBSubBase_HPP
#define   EBSubBase_HPP

class     EBSubBase;

#include  <sEBDataArea.hpp>
#pragma pack(1)

class  EBSubBase :public EBDataArea
{
protected  :         int64                                        next_sb ATTR_ALIGN(1);                                     //

public     :
public     :                                                             EBSubBase (char *filename );
public     :                                     void FromPIF (logical pif );
public     :                                     uint64 SetNext (int64 nextpos );
public     :                                     void ToPIF (logical pif );
public     :                                     int64 get_next_sb ( );
};

#pragma pack()
#endif
