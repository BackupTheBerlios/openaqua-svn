/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    TempMem

\brief    


\date     $Date: 2006/03/13 21:34:54,03 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TempMem_HPP
#define   TempMem_HPP

class     TempMem;

#include  <sTempMem.hpp>
#include  <sTools.hpp>
#pragma pack(4)

class  TempMem
{
protected  :         void                                        *buf;                                                       //

public     :
public     :         OGUI7ImpExp                 void Get (size_t size ){

  Release();
  if ( size != 0 )
  {
    buf         = Tools::gettemp( sizeof( int ) + size );
    *(int*) buf = 1; 
  }

}

public     :         OGUI7ImpExp                 void Release ( ){

  if ( buf )
  {
    if ( --(*(int*) buf) == 0 ) 
      Tools::freetemp(buf);
    buf = NULL;
  }

}

public     :         OGUI7ImpExp                                         TempMem (size_t size )                     : buf(NULL)
{

  Get(size);

}

public     :         OGUI7ImpExp                                         TempMem (TempMem &rTempMem )                     : buf(NULL)
{

  *this = rTempMem;


}

public     :         OGUI7ImpExp                                         TempMem ( )                     : buf(NULL)
{



}

public     :         OGUI7ImpExp                 NOTYPE operator char* ( ){

  return buf ? (char*) &((int*) buf)[1] : NULL;

}

public     :         OGUI7ImpExp                 NOTYPE operator long* ( ){

  return buf ? (long*) &((int*) buf)[1] : NULL;

}

public     :         OGUI7ImpExp                 NOTYPE operator void* ( ){

  return buf ? (void*) &((int*) buf)[1] : NULL;

}

public     :         OGUI7ImpExp                 void operator= (TempMem &rTempMem ){

  Release();
  buf = rTempMem.buf;
  if ( buf ) 
    (*(int *)buf)++;

}

public     :         OGUI7ImpExp                 void operator= (const char *cszText ){
  int      sl;
  Release();
  if ( cszText )
  {
    sl          = strlen(cszText);
    buf         = Tools::gettemp(sizeof(int) + sl + 1);
    *(int *) buf = 1;
    memcpy(&((int *)buf)[1],cszText,sl+1);
  }


}

public     :         OGUI7ImpExp                                         ~TempMem ( ){

  Release();

}

};

#pragma pack()
#endif
