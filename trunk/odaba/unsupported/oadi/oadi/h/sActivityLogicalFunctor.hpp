/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:32:37,32}|(REF)
\class    ActivityLogicalFunctor



\date     $Date: 2006/03/13 21:32:40,54 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ActivityLogicalFunctor_HPP
#define   ActivityLogicalFunctor_HPP


#pragma pack(4)

template < class I, class A >
class  ActivityLogicalFunctor
{
protected  :         typedef logical                              (*Func)( void*, I*, A* );                                  
protected  :         void                                        *data;                                                      
protected  :         Func                                         func;                                                      

public     :
public     :                                                             ActivityLogicalFunctor ( )                     : data(0),
func(0)
{



}

public     :                                                             ActivityLogicalFunctor (void *pData, Func vFunc )                     : data(pData),
func(vFunc)
{



}

public     :                                     logical operator () (I *pI, A *pA ) const{

  if ( func ) 
    return (*func)( data, pI, pA );
  else 
    return NO;

}

};

#pragma pack()
#endif
