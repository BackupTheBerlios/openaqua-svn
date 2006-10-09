//******************************************************************/
//* EB_extRBHeader - Externer Rootbase Header
//*
//*               ODABA II - Class Declaration
//*                          from  L:/OPA7/OPA7.dev
//*
//*  ODE Version 2.1                                   2003/11/14
//******************************************************************/
#ifndef   EB_extRBHeaderO_HPP 
#define   EB_extRBHeaderO_HPP 





#include  <cMBHdr.h>


#pragma pack(1)

 class   RBHdr   : 
                                  public  MBHdr

{
 public     :         int16                                        mb_count ATTR_ALIGN(1);                                    // Anzahl der Mainbases
 public     :         int32                                        work_spaces ;                                              // Liste der Workspaces für die Rootbase
 public     :         char                                         user_id[16] ;                                              // Eigentümer der Rootbase
};


#pragma pack()
#endif

