/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:32:37,32}|(REF)
\class    ResourceEntry

\brief    


\date     $Date: 2006/03/13 21:32:55,79 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ResourceEntry_HPP
#define   ResourceEntry_HPP

class     ResourceEntry;

class     OResource;
#include  <sBinArrayObjEntry.hpp>
class  ResourceEntry
{
protected  :         int32                                        obj_id;                                                    //
protected  :         OResource                                   *resource;                                                  //

public     :
                     int32                                        get_obj_id() { return(obj_id); }
                     OResource                                   *get_resource() { return(resource); }
public     :                                     void Free ( );
public     :                                     void Initialize (OResource *pOResource );
public     :                                                             ResourceEntry (int64 objid );
public     :                                                             ~ResourceEntry ( );
};

#endif
