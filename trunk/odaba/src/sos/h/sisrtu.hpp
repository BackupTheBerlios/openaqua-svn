/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    isrtu

\brief    


\date     $Date: 2006/03/12 19:20:49,56 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   isrtu_HPP
#define   isrtu_HPP

class     isrtu;

#ifndef   GSRT_isrt_entry_HPP
#define   GSRT_isrt_entry_HPP
#include  <sisrt_entry.hpp>
#include  <sGSRT.h>
#endif
#include  <sisrt_entry.hpp>
#include  <sisrtu.hpp>
#pragma pack(8)

class  isrtu :public GSRT(isrt_entry)
{
protected  :         uint32                                       start_index ATTR_ALIGN(4);                                 
protected  :         uint32                                       current_index;                                             
protected  :         uint32                                       count;                                                     

public     :
public     :         SOS7ImpExp                  void Clear ( );
public     :         SOS7ImpExp                  uint32 Count ( );
public     :         SOS7ImpExp                  void *FirstObject ( );
public     :                                     uint32 GetIndex (void *objptr );
public     :                                     uint32 GetIndex (uint32 ident );
public     :         SOS7ImpExp                  uint32 GetItemID (uint32 lindxu );
public     :         SOS7ImpExp                  uint32 GetItemID (void *objptr );
public     :         SOS7ImpExp                  void *GetObjectInst (uint32 lindxu );
public     :         SOS7ImpExp                  uint32 Insert (uint32 ident, void *objptr );
public     :         SOS7ImpExp                  uint32 Insert (void *objptr );
public     :         SOS7ImpExp                  logical IsIndexValid (uint32 lindxu );
public     :         SOS7ImpExp                  void *LastObject ( );
public     :         SOS7ImpExp                  void *NextObject ( );
public     :         SOS7ImpExp                  void *PrevObject ( );
public     :         SOS7ImpExp                  void *Remove (uint32 lindxu );
public     :         SOS7ImpExp                  void *Replace (uint32 lindxu, uint32 ident, void *objptr );
public     :         SOS7ImpExp                  void *Replace (uint32 lindxu, uint32 ident );
public     :         SOS7ImpExp                  void *Replace (uint32 lindxu, void *objptr );
public     :         SOS7ImpExp                                          isrtu (uint32 start, int32 maxe );
public     :         SOS7ImpExp                                          isrtu (const isrtu &isrtu_ref );
public     :         SOS7ImpExp                  isrt_entry *isrtuset (uint32 lindxu, uint32 ident, void *objptr );
public     :         SOS7ImpExp                  isrt_entry *isrtuset (uint32 lindxu );
public     :         SOS7ImpExp                                          ~isrtu ( );
};

#pragma pack()
#endif
