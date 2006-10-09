/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    isrt_entry

\brief    


\date     $Date: 2006/03/12 19:20:49,40 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   isrt_entry_HPP
#define   isrt_entry_HPP

class     isrt_entry;

#pragma pack(8)

class  isrt_entry
{
public     :         uint32                                       ident;                                                     
public     :         void                                        *datarea;                                                   

public     :
public     :         SOS7ImpExp                                          isrt_entry (uint32 ident, void *objptr );
public     :         SOS7ImpExp                                          isrt_entry ( );
public     :         SOS7ImpExp                  logical operator== (isrt_entry &isrtentry ) const;
};

#pragma pack()
#endif
