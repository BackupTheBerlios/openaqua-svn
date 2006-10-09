/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    ctxe



\date     $Date: 2006/03/12 19:20:28,29 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ctxe_HPP
#define   ctxe_HPP

class     ctxe;

#define  CTXE                                      sizeof(ctxe)
#define  CTXE_KLN                                  4
#define  CTXE_KPS                                  sizeof(flnk)+1
#define  CTXE_KTP                                  'I'
#include  <sflnk.hpp>
class  ctxe :public flnk
{
protected  :         int32                                        res_number ATTR_ALIGN(4);                                  

public     :
                     int32                                        get_res_number() { return(res_number); }
public     :         SOS7ImpExp                                          ctxe (int32 class_number, flnk flnkptr );
public     :         SOS7ImpExp                                          ctxe ( );
};

#endif
