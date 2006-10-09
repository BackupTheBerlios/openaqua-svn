/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OField



\date     $Date: 2006/04/28 16:40:48,00 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OField_HPP
#define   OField_HPP

class     OField;

class     PropertyHandle;
class     TControl;
#include  <cOFieldType.h>
#include  <sDPoint.hpp>
#include  <sDSize.hpp>
#include  <sODataSource.hpp>
#include  <sODataSourceHaving.hpp>
#include  <sOFieldControl.hpp>
#include  <sOFrameStyle.hpp>
#include  <sOResource.hpp>
#include  <sOStyleElement.hpp>
#pragma pack(4)

class  OField :public OFieldControl,
public ODataSourceHaving
{
protected  :         OFieldControl                               *fieldControl;                                              
protected  :         OFrameStyle                                 *frameStyle;                                                
protected  :         OFieldType                                   used_as;                                                   
protected  :         logical                                      used_recursive;                                            

public     :
                     OFieldControl                               *get_fieldControl() { return(fieldControl); }
                     OFieldType                                   get_used_as() { return(used_as); }
                     logical                                      get_used_recursive() { return(used_recursive); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     :                                        OFrameStyle *FrameStyle ( ) const;
public     :                                        char *GetAccessClassName ( );
public     :                                             OField ( );
public     :                                             OField (OFieldControl bcOFieldControl, ODataSourceHaving bcODataSourceHaving, OFieldControl *pOFieldControl, OFrameStyle *pOFrameStyle, OFieldType used_as, logical used_recursive );
public     :                                        TControl *Open (TControl *tparent, logical active_f );
protected  : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                logical Read_intern (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     :                                        logical SetClassName (PropertyHandle *ph );
public     :                                        void set_position (DPoint position );
public     :                                        void set_res_id (int resource_id=AUTO );
public     :                                        void set_size (DSize dsize );
public     :                                        void set_type (OFieldType ofield_type );
public     : virtual                                     ~OField ( );
};

#pragma pack()
#endif
