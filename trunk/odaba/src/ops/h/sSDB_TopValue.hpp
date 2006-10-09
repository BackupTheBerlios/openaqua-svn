/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_TopValue

\brief    


\date     $Date: 2006/03/13 21:30:13,43 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_TopValue_HPP
#define   SDB_TopValue_HPP

class     SDB_TopValue;

class  SDB_TopValue :public SDB_Value
{
protected  :         PI(SDB_ValueList)                            value_list;                                                

public     :
                     PI(SDB_ValueList)                           &get_value_list() { return(value_list); }
};

#endif
