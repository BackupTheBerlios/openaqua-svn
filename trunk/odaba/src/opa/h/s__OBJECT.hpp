/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    __OBJECT

\brief    Database object
          Relevant  objects  can  be  defined  as database objects by inheriting
          from  this class. The  class provides two  essential features. The one
          is  the  support  for  update  timestamps, which is automatically set,
          whenever  a  modification  of  an  instance,  which type inherits from
          __OBJECT, is stored. 
          The  other feature  supported is  the global unique object identifier,
          which  is created for  each object instance,  which inherits from this
          type. 
          When   using   shared   inheritance   (multiple   derivation),  shared
          inheriting  instances should have an own  __OBJECT base class to get a
          separate  GUID  and  a  separate  update time stamp. Otherwise, shared
          instances  will  inherit  the  GUID  and the update timestamp from the
          shared base instance.

\date     $Date: 2006/03/13 21:30:14,46 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   __OBJECT_HPP
#define   __OBJECT_HPP

class     __OBJECT;

#include  <sdttm.hpp>
#include  <sguid.hpp>
#pragma pack(4)

class  __OBJECT
{
protected  :         guid                                         __GUID;                                                    // Global Unique Object Identifier (GUID)
protected  :         dttm                                         __LAST_UPDATE;                                             // Last update date
protected  :         PI(mem)                                      user;                                                      //

public     :
                     guid                                        &get___GUID() { return(__GUID); }
                     dttm                                        &get___LAST_UPDATE() { return(__LAST_UPDATE); }
                     PI(mem)                                     &get_user() { return(user); }
public     :                                     void SetTimeStamp ( );
public     :         OPS7ImpExp                                          __OBJECT ( );
};

#pragma pack()
#endif
