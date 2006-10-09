/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    cke

\brief    


\date     $Date: 2006/03/12 19:14:07,78 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cke_HPP
#define   cke_HPP

class     cke;

class     kfc;
#pragma pack(8)

class  cke
{
protected  :         kfc                                         *ckekfc;                                                    
protected  :         char                                        *ckefld;                                                    

public     :
                     kfc                                         *get_ckekfc() { return(ckekfc); }
                     char                                        *get_ckefld() { return(ckefld); }
public     :                                                             cke (kfc *kfcptr );
public     :                                                             ~cke ( );
public     : virtual                             logical CloseCKE ( ) = 0;
public     : virtual                             char *GetKey (char *keyptr, void *instptr, int16 indx ) = 0;
public     : virtual                             int16 OpenCKE (void *instptr, logical refopt=NO ) = 0;
public     : virtual                             logical CheckMod ( ){

 return(YES);

}

};

#pragma pack()
#endif
