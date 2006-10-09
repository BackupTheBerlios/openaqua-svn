/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    CSInstHeader

\brief    


\date     $Date: 2006/03/12 19:12:34,28 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CSInstHeader_HPP
#define   CSInstHeader_HPP

class     CSInstHeader;

#include  <cCS_ParmTypes.h>
#include  <sCSInstHeader.hpp>
#include  <sCSInstance.hpp>
#pragma pack(1)

class  CSInstHeader
{
protected  :         int32                                        size;                                                      
protected  :         CS_ParmTypes                                 type;                                                      

public     :
                     int32                                        get_size() { return(size); }
                     CS_ParmTypes                                 get_type() { return(type); }
public     :                                                             CSInstHeader ( );
public     :                                                             CSInstHeader (int32 inst_len, CS_ParmTypes inst_type );
public     :                                                             CSInstHeader (CSInstHeader &inst_header_ref );
public     :                                     void ConvertFromNet (CS_ParmTypes parm_type, int32 arealen );
public     :                                     void ConvertFromNet (CSInstHeader &inst_header_ref );
public     :                                     void ConvertToNet (CS_ParmTypes parm_type, int32 arealen );
public     :                                     void ConvertToNet (CSInstHeader &inst_header_ref );
public     :                                     void Initialize (CSInstance *cs_inst );
public     :                                     void Initialize (CS_ParmTypes parm_type, int32 arealen );
public     :                                                             ~CSInstHeader ( );
};

#pragma pack()
#endif
