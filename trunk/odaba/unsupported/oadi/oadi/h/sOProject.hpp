/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OProject



\date     $Date: 2006/04/28 16:51:47,79 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OProject_HPP
#define   OProject_HPP

class     OProject;

class     PropertyHandle;
class     TControl;
#include  <sOApplication.hpp>
#pragma pack(4)

class  OProject :public OApplication
{
protected  :         char                                        *tpPath;                                                    
protected  :         int/*OQueryLevel*/                           queryLevel;                                                
protected  :         char                                         errorClass[41];                                            

public     :
                     char                                        *get_tpPath() { return(tpPath); }
                     char                                        *get_errorClass() { return(errorClass); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     :                                             OProject ( );
public     :                                             OProject (OApplication bcOApplication, char *tpPath, int16 queryLevel, char *errorClass );
public     : virtual                                TControl *Open (TControl *tparent, logical active_f );
public     : virtual                                logical Read (PropertyHandle *ph );
public     :                                        void Reset ( );
public     : virtual                                     ~OProject ( );
};

#pragma pack()
#endif
