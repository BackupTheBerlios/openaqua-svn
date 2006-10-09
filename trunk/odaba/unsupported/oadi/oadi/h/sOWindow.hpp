/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OWindow



\date     $Date: 2006/04/28 16:57:57,35 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OWindow_HPP
#define   OWindow_HPP

class     OWindow;

class     ODataSource;
class     ODataSourceHaving;
class     PropertyHandle;
class     TControl;
#include  <sOFieldControl.hpp>
#include  <sOFrameStyle.hpp>
#pragma pack(4)

class  OWindow :public OFieldControl,
public OFrameStyle
{
protected  :         OFieldControl                               *fieldControl;                                              
protected  :         ODataSourceHaving                           *ds_having;                                                 

public     :
                     OFieldControl                               *get_fieldControl() { return(fieldControl); }
                     ODataSourceHaving                           *get_ds_having() { return(ds_having); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     :                                             OWindow ( );
public     :                                             OWindow (OFieldControl bcOFieldControl, OFrameStyle bcOFrameStyle, OFieldControl *pOFieldControl, ODataSourceHaving *pODataSourceHaving );
public     : virtual                                TControl *Open (char *typenames, TControl *tparent, logical active_f );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     :                                        void SetDataSourceHaving (ODataSourceHaving *pODataSourceHaving );
public     : virtual                                const char *fieldControlPHName ( ) const;
public     : virtual                                     ~OWindow ( );
};

#pragma pack()
#endif
