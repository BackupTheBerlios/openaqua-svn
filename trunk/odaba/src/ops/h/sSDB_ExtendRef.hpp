/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_ExtendRef

\brief    Extent reference
          Extent  references are instantiation objects, which define the root of
          an  extent in an  instance of a  database object. The extent reference
          refers  to  one  or  more  indexes,  which  provide  different ways of
          accessing instances of the extent.

\date     $Date: 2006/03/13 21:30:08,60 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_ExtendRef_HPP
#define   SDB_ExtendRef_HPP

class     SDB_ExtendRef;

#ifndef   P_SDB_SetIndex_HPP
#define   P_SDB_SetIndex_HPP
#include  <sPI.hpp>
class       SDB_SetIndex;
PI_dcl     (SDB_SetIndex)
#endif
#pragma pack(8)

class  SDB_ExtendRef
{
protected  :         char                                         sys_ident[40];                                             //
protected  :         int32                                        namespace_id;                                              //
protected  :         PI(SDB_IndexRef)                             indizes;                                                   // Extent indexes

public     :
                     char                                        *get_sys_ident() { return(sys_ident); }
                     int32                                        get_namespace_id() { return(namespace_id); }
                     PI(SDB_IndexRef)                            &get_indizes() { return(indizes); }
};

#pragma pack()
#endif
