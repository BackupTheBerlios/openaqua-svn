/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EB_extRBHeader

\brief    


\date     $Date: 2006/03/12 19:13:19,50 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EB_extRBHeader_HPP
#define   EB_extRBHeader_HPP

class     EB_extRBHeader;

class     RBHdr;
#include  <sEB_Number.hpp>
#include  <sEB_extMBHeader.hpp>
#pragma pack(1)

class  EB_extRBHeader :public EB_extMBHeader
{
protected  :         int16                                        mb_count ATTR_ALIGN(1);                                    //
protected  :         EB_Number                                    work_spaces;                                               // List of subordinated workspaces
protected  :         char                                         user_id[12];                                               //

public     :
                     EB_Number                                   &get_work_spaces() { return(work_spaces); }
                     char                                        *get_user_id() { return(user_id); }
public     :                                     logical CheckUserID (char *user_name );
public     :                                     logical ConvertTo3 ( );
public     :                                                             EB_extRBHeader (uint16 len );
public     :                                     void FromPIF ( );
public     :                                     void ToPIF ( );
public     :                                     int16 get_mb_count ( );
public     :                                     void set_mb_count (int32 count );
public     :                                     void set_user_id (char *user_name );
};

#pragma pack()
#endif
