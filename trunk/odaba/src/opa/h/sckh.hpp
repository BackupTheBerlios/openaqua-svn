/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ckh

\brief    


\date     $Date: 2006/03/12 19:14:07,96 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ckh_HPP
#define   ckh_HPP

class     ckh;

class     cke;
class     ckh;
class     kcb;
#pragma pack(8)

class  ckh
{
protected  :         char                                        *ckhinst;                                                   
protected  :         kcb                                         *ckhkcb;                                                    
protected  :         cke                                         *ckhcke;                                                    
protected  :         int16                                        ckhcur;                                                    
protected  :         char                                        *ckhkey;                                                    
protected  :         int8                                         ckhdim;                                                    
protected  :         int8                                         ckhopc;                                                    

public     :
                     char                                        *get_ckhinst() { return(ckhinst); }
                     kcb                                         *get_ckhkcb() { return(ckhkcb); }
                     cke                                         *get_ckhcke() { return(ckhcke); }
                     int16                                        get_ckhcur() { return(ckhcur); }
                     char                                        *get_ckhkey() { return(ckhkey); }
                     int8                                         get_ckhdim() { return(ckhdim); }
                     int8                                         get_ckhopc() { return(ckhopc); }
public     :                                                             ckh (kcb *kcbptr );
public     :                                     logical ckhchg (ckh *ckhptr );
public     : virtual                             logical ckhclos ( );
public     : virtual                             char *ckhkget (int16 indx );
public     : virtual                             int8 ckhopen (void *instptr, void *srceinst );
public     :                                                             ~ckh ( );
public     :                                     logical ckhsin ( ){

 return (ckhcke ? NO : YES);

}

};

#pragma pack()
#endif
