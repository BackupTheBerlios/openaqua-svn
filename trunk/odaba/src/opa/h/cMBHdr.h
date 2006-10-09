//******************************************************************/
//* EB_extMBHeader - 
//*
//*               ODABA II - Class Declaration
//*                          from  L:/OPA7/OPA7.dev
//*
//*  ODE Version 2.1                                   2003/11/14
//******************************************************************/
#ifndef   EB_extMBHeaderO_HPP 
#define   EB_extMBHeaderO_HPP 

#include  <cSBHdr.h>


#pragma pack(1)

 class   MBHdr   : 
                                  public  SBHdr

{
 public     :
                      int16                                        mb_number ATTR_ALIGN(1);                                   // 
                      int16                                        num_low ;                                                  // 
                      int16                                        num_high ;                                                 // 
                      int16                                        sb_count ;                                                 // 
                      int32                                        last_EBS_num ;                                             // 
                      int32                                        free_EBS_Numbers ;                                         // 
                      int32                                        level0_index ;                                             // 
                      int32                                        level1_index ;                                             // 
                      int32                                        level2_index ;                                             // 
                      int32                                        level3_index ;                                             // 
                      logical                                      dnm_opt ;                                                  // 
                      char                                         reserved1[17] ;                                            // 
                      logical                                      platform_indep ;                                           // 
                      logical                                      large_db ;                                                 // 
                      logical                                      mb_reserved ;                                              // 
};


#pragma pack()
#endif

