/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_ODABA_Str

\brief    Persistent ODABA structures
          Persistent  ODABA structures  allow storing  structure instances in an
          ODABA   database.   Persistent   structures   a   specific   structure
          definition,  which extent  the intensional  features of a complex data
          type by extensional features. 
          The  persistent structure definition is the base for storing instances
          in  extents,  which  can  be  defined  as  property  of the persistent
          structure.

\date     $Date: 2006/03/13 21:30:10,65 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_ODABA_Str_HPP
#define   SDB_ODABA_Str_HPP

class     SDB_ODABA_Str;

#ifndef   P_SDB_Extend_HPP
#define   P_SDB_Extend_HPP
#include  <sPI.hpp>
class       SDB_Extend;
PI_dcl     (SDB_Extend)
#endif
#ifndef   P_SDB_NameSpace_HPP
#define   P_SDB_NameSpace_HPP
#include  <sPI.hpp>
class       SDB_NameSpace;
PI_dcl     (SDB_NameSpace)
#endif
class     SDB_CodeSet;
class     SDB_NameSpace;
#include  <sSDB_Structure.hpp>
#pragma pack(8)

class  SDB_ODABA_Str :public SDB_Structure
{
protected  :         logical                                      clustered ATTR_ALIGN(4);                                   // Create clustered instance
protected  :         logical                                      smcemod;                                                   // Reserved for future
protected  :         logical                                      smceindp;                                                  // Create name space
protected  :         logical                                      smcefctd;                                                  // Functional context
protected  :         int16                                        sb_number;                                                 // Sub-base number
protected  :         PI(SDB_Extend)                               smceextd;                                                  // Extent definitions
protected  :         PI(SDB_NameSpace)                            name_space;                                                

public     :
                     logical                                      get_clustered() { return(clustered); }
                     logical                                      get_smcemod() { return(smcemod); }
                     logical                                      get_smceindp() { return(smceindp); }
                     logical                                      get_smcefctd() { return(smcefctd); }
                     int16                                        get_sb_number() { return(sb_number); }
                     PI(SDB_Extend)                              &get_smceextd() { return(smceextd); }
                     PI(SDB_NameSpace)                           &get_name_space() { return(name_space); }
public     :         OPS7ImpExp                  logical Initialize ( );
public     :                                                             SDB_ODABA_Str ( );
};

#pragma pack()
#endif
