/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    CSegment

\brief    


\date     $Date: 2006/03/12 19:19:47,35 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CSegment_HPP
#define   CSegment_HPP

class     CSegment;

#include  <sCSegment.hpp>
#pragma pack(8)

class  CSegment
{
protected  :         CSegment                                    *previous;                                                  
protected  :         CSegment                                    *next;                                                      
protected  :         uint16                                       size;                                                      
protected  :         uint16                                       count;                                                     
protected  :         void                                       **seg_nodes;                                                 

public     :
                     CSegment                                    *get_previous() { return(previous); }
                     CSegment                                    *get_next() { return(next); }
                     uint16                                       get_size() { return(size); }
                     uint16                                       get_count() { return(count); }
                     void                                       **get_seg_nodes() { return(seg_nodes); }
public     :                                                             CSegment (uint16 init_size, CSegment *prev_seg );
public     :                                                             CSegment (const CSegment &seg_ref );
public     :                                                             CSegment (uint16 init_size, CSegment *prev_seg, CSegment *next_seg );
public     :                                     CSegment *GetNextSegment ( );
public     :                                     void *GetObjectInst (uint16 index );
public     :                                     void **GetObjectPtr (uint16 index );
public     :                                     CSegment *GetPrevSegment ( );
public     :                                     void Insert (void *element, uint16 index, uint16 new_size );
public     :                                     void *Remove (uint16 index, uint16 new_size );
public     :                                     void *Replace (void *element, uint16 index );
public     :                                     void Reset ( );
public     :                                     void SetNextSegment (CSegment *seg_ptr );
public     :                                     void SetPrevSegment (CSegment *seg_ptr );
public     :                                     void SetSize (uint16 new_size );
public     :                                     CSegment *Split (void *element, uint16 index, uint16 new_size );
public     :                                                             ~CSegment ( );
public     :                                     int16 Count ( ){

  return(count);

}

public     :                                     uint16 GetSize ( ){

  return(count);

}

};

#pragma pack()
#endif
