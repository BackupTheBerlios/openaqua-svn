/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    ProcessVariable

\brief    Process variable


\date     $Date: 2006/03/12 19:20:11,25 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ProcessVariable_HPP
#define   ProcessVariable_HPP

class     ProcessVariable;

#include  <ssts.hpp>
#pragma pack(8)

class  ProcessVariable :public sts
{
protected  :         int16                                        reserved ATTR_ALIGN(1);                                    
public     :         void                                        *variable_ptr;                                              

public     :
public     :         SOS7ImpExp                  void *Remove ( );
};

#pragma pack()
#endif
