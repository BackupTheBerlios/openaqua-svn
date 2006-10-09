/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    isrt

\brief    


\date     $Date: 2006/03/12 19:20:48,85 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   isrt_HPP
#define   isrt_HPP

class     isrt;

#ifndef   GSRT_isrt_entry_HPP
#define   GSRT_isrt_entry_HPP
#include  <sisrt_entry.hpp>
#include  <sGSRT.h>
#endif
#include  <sisrt.hpp>
#include  <ssrt.hpp>
#pragma pack(8)

class  isrt :public GSRT(isrt_entry)
{

public     :
public     :         SOS7ImpExp                  logical Copy (const isrt &isrtref );
public     :         SOS7ImpExp                  void *Get (uint32 ident ) const;
public     :         SOS7ImpExp                  uint32 GetItemID (int16 indx ) const;
public     :         SOS7ImpExp                  uint32 GetItemID (void *objptr ) const;
public     :         SOS7ImpExp                  void *GetObjectInst (int16 indx ) const;
public     :         SOS7ImpExp                  uint32 Insert (uint32 ident, void *objptr );
public     :         SOS7ImpExp                  uint32 Insert (void *objptr );
public     :         SOS7ImpExp                  void *Remove (uint32 ident );
public     :         SOS7ImpExp                                          isrt (int32 maxe );
public     :         SOS7ImpExp                                          isrt (const isrt &isrtref );
public     :         SOS7ImpExp                  logical operator!= (const isrt &isrtref ) const;
public     :         SOS7ImpExp                  isrt &operator= (const isrt &isrtref );
public     :         SOS7ImpExp                  logical operator== (const isrt &isrtref ) const;
public     :         SOS7ImpExp                                          ~isrt ( );
};

#pragma pack()
#endif
