/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    TEditField



\date     $Date: 2006/04/28 15:21:11,01 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TEditField_HPP
#define   TEditField_HPP

class     TEditField;

class     OElementStyle;
class     OHighlighter;
class     OMultiLineEdit;
class     OSEdit;
class     OSingleLineEdit;
class     PropertyHandle;
#include  <sOFieldControl.hpp>
#include  <sTField.hpp>
#pragma pack(4)

class  TEditField :public TField
{

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateControl (TControl **tc_ptr );
public     : virtual                                logical DoCreate ( );
public     : virtual                                logical DoCreated ( );
public     :                                        logical SetupHighlightRules (OHighlighter *shl );
public     :                                        OSEdit *Style ( ) const;
public     :                                             TEditField ( );
};

#pragma pack()
#endif
