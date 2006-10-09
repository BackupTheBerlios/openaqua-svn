//******************************************************************/
//*  NodeTypes          
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2005/05/15*/ 
//******************************************************************/

#ifndef   NodeTypes_HPP 
#define   NodeTypes_HPP 

typedef enum 
{

  NT_undefined                     = 0,
  NT_ACAttribute                   = 1,
  NT_ACNode                        = 2,
  NT_ACMetaAttribute               = 3,
  NT_ACTopNode                     = 4,
  NT_ACProperty                    = 5,
  NT_CSNode                        = 6,
  NT_ACSubnode                     = 7,
  NT_ACReference                   = 8,
  NT_ACGenericAttr                 = 9,
  NT_ACRelationship                = 10,
  NT_ACShareBase                   = 11,
  NT_ACHierNode                    = 12,
  NT_ACBaseStruct                  = 13,
  NT_ACViewNode                    = 14,
  NT_ACTempExtent                  = 15,
  NT_ACTransient                   = 16,
  NT_Node                          = 17,
  NT_ACTransientReference          = 18,
  NT_ClientNode                    = 19,
  NT_ACDefine                      = 22,
  NT_ACOPView                      = 25,
  NT_ACOPSelect                    = 27,
  NT_ACOPGroupBy                   = 28,
  NT_ACOperation                   = 29,
  NT_ACOPOutput                    = 31,
  NT_ACOperand                     = 32,
  NT_ACSysProperty                 = 33,
  NT_ACOPProduct                   = 34,
  NT_ACOPJoin                      = 35,
  NT_ACPathNode                    = 36,

} NodeTypes;
#endif
