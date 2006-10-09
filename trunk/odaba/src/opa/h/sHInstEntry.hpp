/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    HInstEntry

\brief    


\date     $Date: 2006/03/12 19:13:23,73 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   HInstEntry_HPP
#define   HInstEntry_HPP

class     HInstEntry;

#pragma pack(8)

class  HInstEntry
{
protected  :         char                                         dll_name[256];                                             
protected  :         HINSTANCE                                    hinstance;                                                 

public     :
                     char                                        *get_dll_name() { return(dll_name); }
                     HINSTANCE                                   &get_hinstance() { return(hinstance); }
public     :                                                             HInstEntry (char *dllname, logical check_opt=NO );
public     :                                                             ~HInstEntry ( );
};

#pragma pack()
#endif
