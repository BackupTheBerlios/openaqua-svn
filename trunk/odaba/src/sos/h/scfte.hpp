/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    cfte

\brief    


\date     $Date: 2006/03/12 19:20:27,96 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cfte_HPP
#define   cfte_HPP

class     cfte;

#define  CFTE                                      sizeof(cfte)
#define  CFTE_KLN                                  40
#define  CFTE_KPS                                  sizeof(flnk)+1
#define  CFTE_KTP                                  'C'
#include  <sflnk.hpp>
#pragma pack(8)

class  cfte :public flnk
{
protected  :         char                                         cftefnam[40] ATTR_ALIGN(4);                                //

public     :
public     :         SOS7ImpExp                                          cfte (char *fnames, flnk flnkptr );
public     :         SOS7ImpExp                                          cfte ( );
};

#pragma pack()
#endif
