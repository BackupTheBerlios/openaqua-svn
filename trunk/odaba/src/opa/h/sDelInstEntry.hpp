/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/07|16:46:42,89}|(REF)
\class    DelInstEntry

\brief    


\date     $Date: 2006/04/10 17:24:41,59 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DelInstEntry_HPP
#define   DelInstEntry_HPP

class     DelInstEntry;

#include  <sEB_Number.hpp>
class  DelInstEntry
{
protected  :         char                                         extent_name[40];                                           
protected  :         EB_Number                                    entnr;                                                     
protected  :         DelInstEntry                                *next;                                                      

public     :
                     char                                        *get_extent_name() { return(extent_name); }
                     EB_Number                                   &get_entnr() { return(entnr); }
                     DelInstEntry                                *get_next() { return(next); }
public     :                                                             DelInstEntry ( );
public     :                                                             DelInstEntry (char *extnames, EB_Number pifent, DelInstEntry *di_entry );
public     :                                     DelInstEntry *GetLast ( );
public     :                                     void set_next (DelInstEntry *di_entry );
public     :                                                             ~DelInstEntry ( );
};

#endif
