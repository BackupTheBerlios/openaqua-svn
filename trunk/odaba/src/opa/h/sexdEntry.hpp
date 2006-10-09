/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    exdEntry

\brief    


\date     $Date: 2006/03/12 19:14:24,03 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   exdEntry_HPP
#define   exdEntry_HPP

class     exdEntry;

class     exd;
#include  <sEB_Number.hpp>
#pragma pack(8)

class  exdEntry
{
protected  :         EB_Number                                    entry_number;                                              //
protected  :         exd                                         *inst_area;                                                 //

public     :
                     EB_Number                                   &get_entry_number() { return(entry_number); }
                     exd                                         *get_inst_area() { return(inst_area); }
public     :                                                             exdEntry (EB_Number entnr, exd *exdarea );
public     :                                     void set_entry_number (EB_Number entnr ){

  entry_number = entnr;

}

public     :                                     void set_inst_area (exd *exdarea ){

  inst_area = exdarea;

}

};

#pragma pack()
#endif
