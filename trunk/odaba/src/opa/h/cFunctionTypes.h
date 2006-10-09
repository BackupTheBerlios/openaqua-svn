//******************************************************************/
//*  FunctionTypes      
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    15.07.2005*/ 
//******************************************************************/

#ifndef   FunctionTypes_HPP 
#define   FunctionTypes_HPP 

typedef enum 
{

  FT_error                         = -1,
  FT_undefined                     = 0,
  FT_Number                        = 2,
  FT_String                        = 3,
  FT_Variable                      = 4,
  FT_Parameter                     = 5,
  FT_Property                      = 6,
  FT_Function                      = 7,
  FT_Expression                    = 8,
  FT_SysFunction                   = 9,
  FT_DynamicFunction               = 10,
  FT_SyntaxFunction                = 11,
  FT_Logical                       = 12,
  FT_Operation                     = 13,
  FT_Extent                        = 14,
  FT_SysVariable                   = 15,
  FT_Enumeration                   = 16,
  FT_Enumerator                    = 17,
  FT_Action                        = 18,
  FT_OperationPath                 = 19,
  FT_InlineExpression              = 21,
  FT_View                          = 22,
  FT_OQLOperation                  = 24,
  FT_PHFunction                    = 25,
  FT_Collection                    = 26,
  FT_AccessPath                    = 27,
  FT_Global                        = 28,
  FT_OQLSelect                     = 29,
  FT_OQLView                       = 30,
  FT_OQLFrom                       = 31,
  FT_OQLWhere                      = 32,
  FT_OQLGroupBy                    = 33,
  FT_OQLOrderBy                    = 34,
  FT_OQLToFile                     = 35,
  FT_OQLToDB                       = 36,
  FT_OQLJoin                       = 37,
  FT_OQLUnion                      = 38,
  FT_OQLMinus                      = 39,
  FT_OQLIntersect                  = 40,
  FT_OQLUse                        = 41,
  FT_EnumHandle                    = 42,
  FT_MetaAttribute                 = 43,

} FunctionTypes;
#endif
