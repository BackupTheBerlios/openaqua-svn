/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    exdBEntry

\brief    


\date     $Date: 2006/03/12 19:14:23,37 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   exdBEntry_HPP
#define   exdBEntry_HPP

class     exdBEntry;

class     CSLHandleList;
class     acb;
class     exd;
#include  <sBinArrayObjEntry.hpp>
#include  <sEB_Number.hpp>
#pragma pack(8)

class  exdBEntry :public BinArrayObjEntry
{
protected  :         exd                                         *inst_area ATTR_ALIGN(4);                                   //

public     :
                     exd                                         *get_inst_area() { return(inst_area); }
public     :                                     void Deinit ( );
public     :                                     void Init ( );
public     :                                     void set_inst_area (exd *exdarea ){

  inst_area = exdarea;

}

};

#pragma pack()
#endif
