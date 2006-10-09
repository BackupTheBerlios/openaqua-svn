/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    kfc

\brief    


\date     $Date: 2006/03/12 19:20:51,60 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   kfc_HPP
#define   kfc_HPP

class     kfc;

class     fmcb;
#include  <sfcb.hpp>
#pragma pack(8)

class  kfc :public fcb
{
public     :         fmcb                                        *kfcfmcb ATTR_ALIGN(4);                                     //
public     :         int32                                        kfcpos;                                                    //
protected  :         char                                        *key_name;                                                  //

public     :
                     char                                        *get_key_name() { return(key_name); }
public     :                                     void Deinitialize ( );
public     :         SOS7ImpExp                  char *get_kc_name ( );
public     :                                                             kfc ( );
public     :                                     void kfcesu (fmcb *fmcbptr );
public     :                                     void kfcesu (fmcb *fmcbptr, int32 struct_offset );
public     :         SOS7ImpExp                  logical kfckgt (char *instptr, char *keyptr, int16 w_indx=1 );
public     :         SOS7ImpExp                  logical kfckpt (char *instptr, char *keyptr, int16 w_indx=1 );
public     :         SOS7ImpExp                  void set_kc_name (char *keynames );
public     :                                                             ~kfc ( );
public     :                                     fmcb *kfcfmcbg ( ){

  return(kfcfmcb);

}

};

#pragma pack()
#endif
