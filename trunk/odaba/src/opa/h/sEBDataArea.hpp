/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EBDataArea

\brief    


\date     $Date: 2006/03/12 19:13:14,37 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EBDataArea_HPP
#define   EBDataArea_HPP

class     EBDataArea;

#pragma pack(1)

class  EBDataArea
{
protected  :         uint8                                        version_flag;                                              //
protected  :         char                                         file_name[513];                                            //
protected  :         int64                                        next_da;                                                   //

public     :
                     char                                        *get_file_name() { return(file_name); }
public     :                                                             EBDataArea (char *filename );
public     :                                     void FromPIF (logical pif );
public     :                                     int64 SetNext (uint64 position64 );
public     :                                     void ToPIF (logical pif );
public     :                                     int64 get_next_da ( );
};

#pragma pack()
#endif
