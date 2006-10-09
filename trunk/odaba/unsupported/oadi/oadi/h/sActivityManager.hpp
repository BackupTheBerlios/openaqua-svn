/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:32:37,32}|(REF)
\class    ActivityManager

\brief    


\date     $Date: 2006/03/13 21:32:40,67 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ActivityManager_HPP
#define   ActivityManager_HPP


#include  <sActivityManagerI.hpp>
#pragma pack(4)

template < class I, class A >
class  ActivityManager :public ActivityManagerI
{

public     :
public     :                                                             ActivityManager ( )                     : ActivityManagerI ()
{



}

public     :                                     ActivityHandler<I,A> &Add (const char *cszName_0=0 ){

// this works since the handler itself does not store Is or As
  
  return (ActivityHandler<I,A>&) ActivityManagerI::Add( cszName_0 );

}

};

#pragma pack()
#endif
