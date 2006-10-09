/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EB_extMBHeader

\brief    


\date     $Date: 2006/03/12 19:13:18,84 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EB_extMBHeader_HPP
#define   EB_extMBHeader_HPP

class     EB_extMBHeader;

#ifndef   INTERVAL_short_HPP
#define   INTERVAL_short_HPP
#include  <sINTERVAL.h>
#endif
class     MBHdr;
#include  <sEB_Number.hpp>
#include  <sEB_extSBHeader.hpp>
#pragma pack(1)

class  EB_extMBHeader :public EB_extSBHeader
{
protected  :         int16                                        mb_number ATTR_ALIGN(1);                                   
protected  :         int16                                        sb_count;                                                  
protected  :         EB_Number                                    last_EBS_num;                                              
protected  :         EB_Number                                    free_EBS_Numbers;                                          
protected  :         EB_Number                                    level0_index;                                              
protected  :         EB_Number                                    level1_index;                                              
protected  :         EB_Number                                    level2_index;                                              
protected  :         EB_Number                                    level3_index;                                              
protected  :         EB_Number                                    level4_index;                                              
protected  :         EB_Number                                    level5_index;                                              
protected  :         logical                                      platform_indep;                                            
protected  :         logical                                      dnm_opt;                                                   
protected  :         char                                         reserved1[7];                                              

public     :
                     logical                                      get_platform_indep() { return(platform_indep); }
                     logical                                      get_dnm_opt() { return(dnm_opt); }
public     :                                     void ConvertTo3 (MBHdr *old_header );
public     :                                                             EB_extMBHeader (uint16 len );
public     :                                     void FromPIF ( );
public     :                                     void SetLevelIndex (EB_Number entnr, int16 lev );
public     :                                     void ToPIF ( );
public     :                                     EB_Number get_free_EBS_Numbers ( );
public     :                                     EB_Number get_last_EBS_num ( );
public     :                                     EB_Number get_level0_index ( );
public     :                                     EB_Number get_level1_index ( );
public     :                                     EB_Number get_level2_index ( );
public     :                                     EB_Number get_level3_index ( );
public     :                                     EB_Number get_level4_index ( );
public     :                                     EB_Number get_level5_index ( );
public     :                                     int16 get_mb_number ( );
public     :                                     int16 get_sb_count ( );
public     :                                     void set_free_EBS_Numbers (EB_Number entnr );
public     :                                     void set_last_EBS_num (EB_Number entnr );
public     :                                     void set_level0_index (EB_Number entnr );
public     :                                     void set_level1_index (EB_Number entnr );
public     :                                     void set_level2_index (EB_Number entnr );
public     :                                     void set_level3_index (EB_Number entnr );
public     :                                     void set_level4_index (EB_Number entnr );
public     :                                     void set_level5_index (EB_Number entnr );
public     :                                     void set_mb_number (int16 mbnumber );
public     :                                     void set_platform_indep (logical pindep=NO );
public     :                                     void set_sb_count (int32 count );
};

#pragma pack()
#endif
