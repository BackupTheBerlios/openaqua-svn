//******************************************************************/
//* EB_extSBHeader - 
//*
//*               ODABA II - Class Declaration
//*                          from  L:/OPA7/OPA7.dev
//*
//*  ODE Version 2.1                                   2003/11/14
//******************************************************************/
#ifndef   EB_extSBHeaderO_HPP 
#define   EB_extSBHeaderO_HPP 


#include  <sEB_extDAHeader.hpp>

#pragma pack(1)

class   SBHdr   : 
                                  public  EB_extDAHeader

{
 public    :         int16                                        sb_number ATTR_ALIGN(1);                                   // 
 public    :         int16                                        act_da ;                                                   // 
 public    :         int16                                        da_count ;                                                 // 
 public    :         int32                                        max_entry_size ;                                           // 
 public    :         char                                         reserved1[24] ;                                            // 
};


#pragma pack()
#endif

