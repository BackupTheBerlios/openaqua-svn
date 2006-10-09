/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_CSEntry

\brief    Enumerator instance
          An  enumerator  value  consists  of  a  numerical  value,  an optional
          category  type,  which  defines  the  object  type  for  the sub-class
          created by the category, and the category definition.
          When  using  the  category  as  discriminator or delineating variable,
          enumerators are associated with a type.

\date     $Date: 2006/03/13 21:30:07,76 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_CSEntry_HPP
#define   SDB_CSEntry_HPP

class     SDB_CSEntry;

#pragma pack(8)

class  SDB_CSEntry
{
public     :         int16                                        value;                                                     // Numerical value
public     :         char                                         type[40];                                                  // Generated type
public     :         char                                         string[256];                                               // Category definition

public     :
public     :                                                             SDB_CSEntry (int32 cs_value, char *cs_string, char *cs_type );
public     :                                                             SDB_CSEntry ( );
};

#pragma pack()
#endif
