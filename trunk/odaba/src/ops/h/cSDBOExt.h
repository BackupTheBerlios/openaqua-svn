//******************************************************************/
//* SDB_ObjectExt - Externe Struktur f�r den Index der Objekt-Identit�ten (SDB_ObjectID)
//*
//*               ODABA II - Class Declaration
//*                          from  L:/OPS7/OPS7.dev
//*
//*  ODE Version 2.1                                   14.11.2003
//******************************************************************/
#ifndef   SDB_ObjectExtO_HPP 
#define   SDB_ObjectExtO_HPP 


#include  <sEB_Number.hpp>

#pragma pack(8)

 class   SDBOExt   
{
 public  :         int32                                        object_id ;                                                // Identit�t des Objektes
 public  :         int32                                        derivates ;                                                // Adresse der Referenztabelle (mvly) f�r die abgeleiteten Ojekte in der EntryBase
 public  :         int32                                        extends ;                                                  // Adresse der Referenztabelle (mvly) f�r die Extends in der EntryBase
 public  :         int32                                        version_list ;                                             // 
 public  :         uint16                                       version ;                                                  // 
 public  :         char                                         reserved[14] ;                                             // 
};

#pragma pack()
#endif

