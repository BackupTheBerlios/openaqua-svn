/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_GenType

\brief    Definition of template types
          Template  types are  user-defined and  system-provided template types,
          which  are stored in a list of available types. This is just a list of
          available  types. Template types,  however, require the implementation
          of  a specific template class, which must  be provided by the user for
          user-defined  template  types.  ODABA  supports  user-defined template
          types with one parameter, which is the data type.

\date     $Date: 2006/03/13 21:30:08,65 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_GenType_HPP
#define   SDB_GenType_HPP

class     SDB_GenType;

#pragma pack(8)

class  SDB_GenType :public SDB_Structure
{
protected  :         PI(SDB_Member)                               parameters;                                                

public     :
                     PI(SDB_Member)                              &get_parameters() { return(parameters); }
};

#pragma pack()
#endif
