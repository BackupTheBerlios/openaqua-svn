/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EB_extHeader

\brief    


\date     $Date: 2006/03/12 19:13:18,64 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EB_extHeader_HPP
#define   EB_extHeader_HPP

class     EB_extHeader;

#pragma pack(1)

class  EB_extHeader
{
protected  :         int16                                        reserved0;                                                 
protected  :         char                                         eb_ident[4];                                               
protected  :         uint16                                       mod_count;                                                 
protected  :         int16                                        header_length;                                             
protected  :         char                                         reserved1[3];                                              

public     :
                     char                                        *get_eb_ident() { return(eb_ident); }
public     :                                                             EB_extHeader (uint16 len );
public     :                                     void FromPIF (logical pif );
public     :                                     void ToPIF (logical pif );
public     :                                     uint16 get_header_length ( );
public     :                                     int16 get_mod_count ( );
public     :                                     void set_header_length (uint16 len );
public     :                                     void set_mod_count (int16 modcount );
};

#pragma pack()
#endif
