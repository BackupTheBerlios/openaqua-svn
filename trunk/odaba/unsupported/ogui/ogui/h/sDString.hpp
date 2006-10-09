/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    DString

\brief    


\date     $Date: 2006/03/13 21:33:38,48 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DString_HPP
#define   DString_HPP

class     DString;

class     DStringPrivate;
#include  <sDString.hpp>
#pragma pack(4)

class  DString
{
protected  :         DStringPrivate                              *p;                                                         //

public     :
public     :         OGUI7ImpExp                                         DString (const char *cszString );
public     :         OGUI7ImpExp                                         DString (const DString &rcDString );
public     :         OGUI7ImpExp                                         DString ( );
public     :         OGUI7ImpExp                 logical IsEmpty ( ) const;
public     :         OGUI7ImpExp                 logical IsNull ( ) const;
public     :         OGUI7ImpExp                 int Length ( ) const;
public     :         OGUI7ImpExp                 NOTYPE operator const char* ( ) const;
public     :         OGUI7ImpExp                 logical operator!= (const DString &rcdsText ) const;
public     :         OGUI7ImpExp                 logical operator!= (const char *cszText ) const;
public     :         OGUI7ImpExp                 DString &operator+ (const DString &rcdsText );
public     :         OGUI7ImpExp                 DString &operator+ (const char *cszText );
public     :         OGUI7ImpExp                 DString &operator+= (const DString &rcdsText );
public     :         OGUI7ImpExp                 DString &operator+= (const char *cszText );
public     :         OGUI7ImpExp                 DString &operator= (const char *cszString );
public     :         OGUI7ImpExp                 DString &operator= (const DString &rcDString );
public     :         OGUI7ImpExp                 logical operator== (const DString &rcdsText ) const;
public     :         OGUI7ImpExp                 logical operator== (const char *cszText ) const;
public     :         OGUI7ImpExp                 const char operator[] (int iIndex ) const;
protected  :                                     void resize (int newLength, logical fCopy );
public     :         OGUI7ImpExp                                         ~DString ( );
};

#pragma pack()
#endif
