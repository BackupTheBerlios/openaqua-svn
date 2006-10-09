/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ICEntry

\brief    


\date     $Date: 2006/03/12 19:13:24,25 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ICEntry_HPP
#define   ICEntry_HPP

class     ICEntry;

class     ICEntry;
class     bnode;
class     inti;
class     node;
#include  <sEB_Number.hpp>
#pragma pack(1)

class  ICEntry
{
protected  :         EB_Number                                    entry_number;                                              
protected  :         uint32                                       last_use;                                                  
protected  :         inti                                        *inti_ref;                                                  
protected  :         char                                         key[2];                                                    

public     :
                     EB_Number                                   &get_entry_number() { return(entry_number); }
                     uint32                                       get_last_use() { return(last_use); }
                     inti                                        *get_inti_ref() { return(inti_ref); }
                     char                                        *get_key() { return(key); }
public     :                                     logical Initialize (bnode *bnodeptr, inti *intiptr );
public     :                                     void SetLastUse (int32 count );
};

#pragma pack()
#endif
