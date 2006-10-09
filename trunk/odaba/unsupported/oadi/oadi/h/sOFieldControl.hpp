/********************************* Class Declaration ***************************/
/**
\package  OADI - 
\class    OFieldControl

\brief    


\date     $Date: 2006/07/17 14:10:57,56 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OFieldControl_HPP
#define   OFieldControl_HPP

class     OFieldControl;

class     OElementStyle;
class     OFrameStyle;
class     PropertyHandle;
class     TControl;
#include  <sDMargin.hpp>
#include  <sDSize.hpp>
#include  <sOStyleAction.hpp>
#pragma pack(4)

class  OFieldControl :public OStyleAction
{
protected  :         int16                                        length;                                                    // 
protected  :         logical                                      cache;                                                     // 
protected  :         logical                                      reserved;                                                  // 
protected  :         logical                                      output;                                                    // 
protected  :         logical                                      dynamic;                                                   // 
protected  :         char                                         class_name[40];                                            // 
protected  :         DSize                                        grid_size;                                                 // 
protected  :         DMargin                                      field_margin;                                              // 
protected  :         int16                                        inner_distance;                                            // 

public     :
                     int16                                        get_length() { return(length); }
                     logical                                      get_cache() { return(cache); }
                     logical                                      get_reserved() { return(reserved); }
                     logical                                      get_output() { return(output); }
                     logical                                      get_dynamic() { return(dynamic); }
                     char                                        *get_class_name() { return(class_name); }
                     DSize                                       &get_grid_size() { return(grid_size); }
                     DMargin                                     &get_field_margin() { return(field_margin); }
                     int16                                        get_inner_distance() { return(inner_distance); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     :                                        OField *FieldByName (const DString &rcdsName );
public     :                                             OFieldControl ( );
public     :                                             OFieldControl (OStyleAction bcOStyleAction, int32 length, logical output, logical dynamic, char *class_name, DSize grid_size, DMargin dm_field_margin, int16 inner_distance );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     :                                        void SetClassName (char *string );
public     :                                        void SetInnerDistance ( );
public     : virtual                                     ~OFieldControl ( );
};

#pragma pack()
#endif
