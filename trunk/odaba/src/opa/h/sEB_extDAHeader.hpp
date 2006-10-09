/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EB_extDAHeader

\brief    


\date     $Date: 2006/03/12 19:13:18,32 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EB_extDAHeader_HPP
#define   EB_extDAHeader_HPP

class     EB_extDAHeader;

#define  CURRENT_VERSION                           4
#include  <sEB_extHeader.hpp>
#pragma pack(1)

class  EB_extDAHeader :public EB_extHeader
{
protected  :         int16                                        da_number ATTR_ALIGN(1);                                   
protected  :         int64                                        da_size;                                                   
protected  :         char                                         reserved1[4];                                              
protected  :         int16                                        version;                                                   
protected  :         int64                                        next_position;                                             
protected  :         char                                         eb_reserved[6];                                            

public     :
public     :                                                             EB_extDAHeader (uint16 len );
public     :                                     void FromPIF (logical pif );
public     :                                     void ToPIF (logical pif );
public     :                                     int16 get_da_number ( );
public     :                                     int64 get_da_size ( );
public     :                                     int64 get_next_position ( );
public     :                                     int16 get_version ( );
public     :                                     void set_da_number (uint16 danumber );
public     :                                     void set_da_size (int64 dasize64 );
public     :                                     void set_next_position (uint64 position64 );
public     :                                     void set_version (int16 new_version );
};

#pragma pack()
#endif
