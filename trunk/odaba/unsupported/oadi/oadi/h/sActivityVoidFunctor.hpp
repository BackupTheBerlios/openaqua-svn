/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:32:37,32}|(REF)
\class    ActivityVoidFunctor

\brief    


\date     $Date: 2006/03/13 21:32:41,01 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ActivityVoidFunctor_HPP
#define   ActivityVoidFunctor_HPP


#pragma pack(4)

template < class I, class A >
class  ActivityVoidFunctor
{
protected  :         typedef void                                 (*Func)( void*, I*, A* );                                  //
protected  :         void                                        *data;                                                      //
protected  :         Func                                         func;                                                      //

public     :
public     :                                                             ActivityVoidFunctor ( )                     : data(0),
func(0)
{



}

public     :                                                             ActivityVoidFunctor (void *pData, Func vFunc )                     : data(pData),
func(vFunc)
{



}

public     :                                     void operator() (I *pI, A *pA ) const{

  if ( func ) 
    (*func)(data,pI,pA);

}

};

#pragma pack()
#endif
