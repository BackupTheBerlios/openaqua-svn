//******************************************************************/
//* EBI - EB-Indexeintrag
//*
//*               ODABA II - Class Declaration
//*                          from  L:/OPA7/OPA7.dev
//*
//*  ODE Version 2.1                                   2004/11/22
//******************************************************************/
#ifndef   EBIo_HPP 
#define   EBIo_HPP 

#pragma pack(1)

class   EBIo   : 
                                  public  bsts

{
 public     :         int8                                         da_number ATTR_ALIGN(1);                                   // Nummer des Datenbereiches
 public     :         uint8                                        sb_number ;                                                // Nummer der SubBase
 public     :         uint32                                       da_position ;                                              // Position im Datenbereich
 public     :         int32                                        entry_length ;                                             // Länge des Entries
 public     :         uint8                                        mod_count ;                                                // Modifikationszähler
 public     :         uint8                                        schema_version ;                                           // 
 public     :         uint16                                       version ;                                                  // 
 public     :         int32                                        version_list ;                                             // 
};


#pragma pack()
#endif

