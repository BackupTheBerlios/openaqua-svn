/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EB_extSBHeader

\brief    


\date     $Date: 2006/03/12 19:13:19,75 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EB_extSBHeader_HPP
#define   EB_extSBHeader_HPP

class     EB_extSBHeader;

#include  <sEB_extDAHeader.hpp>
#pragma pack(1)

class  EB_extSBHeader :public EB_extDAHeader
{
protected  :         int16                                        sb_number ATTR_ALIGN(1);                                   
protected  :         int16                                        act_da;                                                    
protected  :         int16                                        da_count;                                                  
protected  :         int32                                        max_entry_size;                                            

public     :
public     :                                                             EB_extSBHeader (uint16 len );
public     :                                     void FromPIF (logical pif );
public     :                                     void ToPIF (logical pif );
public     :                                     int16 get_act_da ( );
public     :                                     int16 get_da_count ( );
public     :                                     int32 get_max_entry_size ( );
public     :                                     int16 get_sb_number ( );
public     :                                     void set_act_da (int16 actda );
public     :                                     void set_da_count (int32 dacount );
public     :                                     void set_max_entry_size (int32 entrysize );
public     :                                     void set_sb_number (uint16 sbnumber );
};

#pragma pack()
#endif
