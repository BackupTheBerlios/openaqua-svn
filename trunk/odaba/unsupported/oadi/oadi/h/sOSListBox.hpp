/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OSListBox



\date     $Date: 2006/04/28 16:55:13,09 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSListBox_HPP
#define   OSListBox_HPP

class     OSListBox;

class     PropertyHandle;
#include  <sOStyle.hpp>
#pragma pack(4)

class  OSListBox :public OStyle
{
protected  :         logical                                      drop;                                                      
protected  :         logical                                      edit;                                                      
protected  :         logical                                      hscrol;                                                    
protected  :         logical                                      vscrol;                                                    
protected  :         logical                                      sorted;                                                    
protected  :         logical                                      multisel;                                                  
protected  :         logical                                      multi_column;                                              
protected  :         logical                                      check_box;                                                 
protected  :         logical                                      tree;                                                      
protected  :         logical                                      transposed;                                                
protected  :         logical                                      table_grid;                                                
protected  :         logical                                      fast_list;                                                 

public     :
                     logical                                      get_drop() { return(drop); }
                     logical                                      get_edit() { return(edit); }
                     logical                                      get_hscrol() { return(hscrol); }
                     logical                                      get_vscrol() { return(vscrol); }
                     logical                                      get_sorted() { return(sorted); }
                     logical                                      get_multisel() { return(multisel); }
                     logical                                      get_multi_column() { return(multi_column); }
                     logical                                      get_check_box() { return(check_box); }
                     logical                                      get_tree() { return(tree); }
                     logical                                      get_transposed() { return(transposed); }
                     logical                                      get_table_grid() { return(table_grid); }
                     logical                                      get_fast_list() { return(fast_list); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     : virtual                                char *GetObjectType ( );
public     :                                             OSListBox ( );
public     :                                             OSListBox (OStyle bcOStyle, logical drop, logical edit, logical hscroll, logical vscroll, logical sorted, logical multisel, logical multi_column, logical check_box, logical tree, logical transposed, logical table_grid, logical fast_list );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     : virtual                                     ~OSListBox ( );
};

#pragma pack()
#endif
