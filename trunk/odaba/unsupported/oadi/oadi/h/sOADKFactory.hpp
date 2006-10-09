/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OADKFactory



\date     $Date: 2006/04/28 17:02:29,39 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OADKFactory_HPP
#define   OADKFactory_HPP

class     OADKFactory;

class     OADKFactory;
class     PropertyHandle;
#pragma pack(4)

class  OADKFactory
{
protected  :         srt                                         *cftdsrt;                                                   

public     :
public     : static                                 OADKFactory *__cdecl Factory ( );
public     :                                        void *New (PropertyHandle *ph, char *typenames );
public     :                                        void *New (char *typenames );
protected  :                                             OADKFactory ( );
public     :                                             ~OADKFactory ( );
};

#pragma pack()
#endif
