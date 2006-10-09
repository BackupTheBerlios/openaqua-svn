/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    tim

\brief    


\date     $Date: 2006/03/12 19:21:00,53 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   tim_HPP
#define   tim_HPP

class     tim;

#define  TWAIT                                     tim::timestp
#pragma pack(8)

class  tim
{

public     :
public     : static  SOS7ImpExp                  void __cdecl WaitMilliseconds (uint32 short_time );
public     : static  SOS7ImpExp                  void __cdecl timestp (uint16 sleeping_time );
};

#pragma pack()
#endif
