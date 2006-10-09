/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    guid

\brief    


\date     $Date: 2006/03/12 19:20:44,50 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   guid_HPP
#define   guid_HPP

class     guid;

#include  <sdttm.hpp>
#pragma pack(4)

class  guid
{
protected  :         DATETIME                                     time_stamp;                                                
protected  :         uint16                                       sid;                                                       
protected  :         uint16                                       num1;                                                      
protected  :         uint32                                       num2;                                                      

public     :
public     :         SOS7ImpExp                  void AutoCorrection ( );
public     :         SOS7ImpExp                  void FromPIF (logical convert );
public     :         SOS7ImpExp                  uint16 GetSID ( );
public     :         SOS7ImpExp                  char *GetString (char *guid_string );
public     :         SOS7ImpExp                  void Initialize (uint16 type_id, uint32 number1, uint32 number2 );
public     :         SOS7ImpExp                  void Initialize (char *string );
public     :         SOS7ImpExp                  logical IsEmpty ( );
public     :         SOS7ImpExp                  void Reset ( );
public     :         SOS7ImpExp                  void ToPIF (logical convert );
public     :         SOS7ImpExp                                          guid (int16 sid, uint32 number1, uint32 number2 );
public     :         SOS7ImpExp                                          guid ( );
};

#pragma pack()
#endif
