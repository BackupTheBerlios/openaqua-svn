//******************************************************************/
//*  OPNodeTypes        
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    06.11.2005*/ 
//******************************************************************/

#ifndef   OPNodeTypes_HPP 
#define   OPNodeTypes_HPP 

typedef enum 
{

  NT_OPBase                        = 1,
  NT_OPLocalVariable               = 2,
  NT_OPParameter                   = 3,
  NT_OPGlobalVariable              = 4,
  NT_OPProperty                    = 5,
  NT_OPExtent                      = 6,
  NT_OPFunction                    = 7,
  NT_OPExpression                  = 8,
  NT_OPPHFunction                  = 9,
  NT_OPSystemClass                 = 10,
  NT_OPConstant                    = 11,
  NT_OPInlineExpression            = 12,
  NT_OPSystemVariable              = 13,
  NT_OPAccessPath                  = 14,
  NT_OPSortKey                     = 15,
  NT_OPVariableSpec                = 16,
  NT_OPBaseCollection              = 19,
  NT_OPBinary                      = 20,
  NT_OPSynBlock                    = 21,
  NT_OPSynBreak                    = 22,
  NT_OPSynContinue                 = 23,
  NT_OPSynError                    = 24,
  NT_OPSynIf                       = 25,
  NT_OPSynLeave                    = 26,
  NT_OPSynReturn                   = 27,
  NT_OPSynSwitch                   = 28,
  NT_OPSynWhile                    = 29,
  NT_OPSynCase                     = 30,
  NT_OPExpressionDecl              = 31,
  NT_OPUnary                       = 32,
  NT_OPOperationDecl               = 34,
  NT_OPOperation                   = 35,
  NT_OPFunctionDecl                = 36,
  NT_OPDecl                        = 37,
  NT_OPAccessPathDecl              = 38,
  NT_OPOQLOperation                = 39,
  NT_OPSynException                = 40,

} OPNodeTypes;
#endif
