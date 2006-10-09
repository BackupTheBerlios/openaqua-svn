/***********************************************************************/
/*
/*  Gerarated Parser for: bnf
/*
/***********************************************************************/
#include <csos4mac.h>
#include <sBNFParser.hpp>
#include <sBNFStandardSymbols.hpp>
#include <sBNFSpecialSymbols.hpp>
#include <sBNF_cpp.hpp>
#include <sBNFData.hpp>
class BNF_OSI : public BNFParser {
    public:
	             BNF_OSI(BNFParser *bs_parent);
};

BNF_OSI :: BNF_OSI(BNFParser *bs_parent)
         : BNFParser ("OSI",bs_parent,YES)
{
  BNFExpression *__expression;

/*
// The OSI BNF provides two entry points for importing schema definitions (ODL) and for
// running script files (OSI).

// ODABA Script Interface (OSI)
// OSI is an ODL/OQL extension, which provides additional features for script interfaces. 
// OSI supports defining global expressions and variables. When calling an OSI script 
// whithout entry point, the global expression with the name 'main' is used as entry point. 
// Parameters passed to the entry point are passed as string parameters in the sequence as defined
// when calling the script.

OSI                   := [data_source] [debug_info] osi_element(*)
debug_info            := _debugprocs '=' location ';'

osi_element           := [block_intro(*)] osi_definition [';']
osi_definition        := type_dcl | view_dcl | osi_class | expr_def

osi_class             := class_header [ osi_class_def ] 
osi_class_def         := '{' osi_exports(*) '}'  
osi_exports           := [ comment_block(*) ] osi_export_dcl
osi_export_dcl        := attr_dcl | ref_dcl | rel_dcl | expr_def

_debugprocs           := 'debugProcedures'  | __debugprocs
__debugprocs          :: 'DEBUGPROCEDURES'

// ODL Schema 
// ODL differs between state and behaviour. Usually, an interface describes behaviour, 
// while a literal (structure or enumeration) describes a state. Classes may define states
// and behaviour. Inheritance relationship is restricted to behaviour. Thus, classes and
// interfaces may inherit behaviour from other interfaces but not from a class. Classes
// may inherit from other classes by EXTENDS relationships, only.

ODL                   := [data_source] sc_element(*)
data_source           := dictionary | datasource 
datasource            := [ comment_block(*) ] _datasource '=' location ';'
dictionary            := [ comment_block(*) ] _dictionary '=' location ';' [database]
database              := [ comment_block(*) ] _database '=' location ';'
location              := string | identifier                           // ODABA extension

sc_element            := [block_intro(*)] [update_option] sc_definition ';'
sc_definition         := mod_definition | schema_dcl 
schema_dcl            := schema [identifier] '{' sc_element(*) '}' 

// module_dcl    
mod_definition        := type_dcl | view_dcl | interface_dcl | class_dcl | const_dcl | module_dcl 
module_dcl            := _module identifier '{' mod_element(*) '}' 
mod_element           := [block_intro(*)] [update_option] mod_definition ';'

// type_dcl 

type_dcl              := namespace_dcl | type_def | struct_type | union_type | enum_type 
type_def              := _typedef type_spec [ declarators ]

// namespace_dcl    
namespace_dcl         := _namespace identifier '{' ns_element(*) '}' 
ns_element            := [block_intro(*)] [update_option] type_dcl ';'
update_option         := _new | update                                 // ODABA extension

// structure
struct_type           := _struct identifier [struct_def]               // ODABA allows forward declarations and references for structures
struct_def            := '{' member(*) '}'

// union
union_type            := _union identifier _switch '(' switch_type_spec ')' '{' case_def(*) '}'
switch_type_spec      := base_int | char_types | boolean_type | enum_type | scoped_name
case_def              := case_label(*) element_spec ';'
case_label            := case_inst | default_def
case_inst             := _case operand ':'
default_def           := _default ':'
element_spec          := type_spec declarator

// enumeration
enum_type             := _enum identifier [base_class] [enum_def]      // ODABA allows forward declarations for enumerations
base_class            := '(' scoped_name ')'                           // base class for discriminators, ODABA extension
enum_def              := '{' enumerator(*) '}'
enumerator            := identifier [ref_type] [ enum_value ] [enum_def] [',']
ref_type              := '(' scoped_name ')'                           // type for discriminators, ODABA extension
enum_value            := assign_op number                              // ODABA extension

// const_dcl 

const_dcl             := _const const_type identifier assigned_value
const_type            := base_int | char_types | boolean_type | string_type | scoped_name

// except_dcl

except_dcl            := _exception exceptions_def
exceptions_def        := exception_def | exception_specs
exception_specs       := '{' sexception_spec(*) '}'
sexception_spec       := exception_def ';'
exception_def         := identifier '{' [member(*)] '}'

// class_dcl : in contrast to ODL ODABA supports multiple class inheritance via EXTENDS relationship

class_dcl             := class_header [ class_def ] 
class_def             := '{' exports(*) '}' 
class_header          := _class identifier [guid] [extends_spec] [inheritance_spec] [type_property_list]
type_property_list    := '(' type_property(*) ')'
type_property         := key_spec | extent_spec | alignment_spec
alignment_spec        := _alignment '=' number ';'

// interface 

interface_dcl         := interface_header [ interface_spec ] 
interface_spec        := '{' [exports(*)] '}'
interface_header      := _interface identifier [ inheritance_spec ]

exports               := [ comment_block(*) ] export_dcl
export_dcl            := type_dcl | const_dcl | attr_dcl | ref_dcl | rel_dcl | except_dcl | method 

// view_dcl is an ODABA specific extension, which combines ODL and OQL elements

view_dcl              := view_header [ view_def ]
view_def              := '{' view_member(*) '}' 
view_member           := attr_dcl | ref_dcl | method
view_header           := _view identifier from_spec [where_spec] [group_spec] [having_spec] [type_property_list]
from_spec             := _from operand_list 
where_spec            := _where condition 
having_spec           := _having condition 
order_spec            := _order_by '(' scoped_names ')'
group_spec            := _group_by '(' categories ')'                   // automatically generates 'value' and 'partition' property in the structure

// inheritance_spec and extends_spec, which include some important ODABA extensions (multiple class inheritance,
// set based relationships)

inheritance_spec      := ':' base_types
extends_spec          := extends base_types                            // handled as based_on inheritance in ODABA
base_types            := base_type [base_type_suc(*)]
base_type_suc         := ',' base_type
base_type             := [base_option(*)] extended_type_spec [rel_option(*)] [base_declarator]
base_option           := _virtual | priv_option 
base_declarator       := identifier [col_ext_rel(*)] 

// extent_spec, which includes substantial extension for ODABA (multiple extents)

extent_spec           := extent extents_def ';'                        // ODABA requires a semicolon, here
extents_def           := extent_def | extent_specs
extent_specs          := '{' sextent_spec(*) '}' 
sextent_spec          := extent_def ';'
extent_def            := [_transient] identifier [rel_option(*)] [extent_option(*)]
extent_option         := order_keys | super_sets | sub_sets
sub_sets              := subset [subset_options(*)] extent_names 
subset_options        := distinct | complete
super_sets            := superset [intersect] extent_names
extent_names          := extent_name [extent_names_suc(*)]
extent_names_suc      := ',' extent_name

// key_spec

key_spec              := key keys_def ';'                                 // ODABA requires a semicolon, here, instead of comma
keys_def              := key_def | key_specs
key_specs             := '{' skey_spec(*) '}' 
skey_spec             := key_def ';'
key_def               := [ident_key] identifier [key_components_ext]
key_components_ext    := key_components | key_components_odmg 
key_components_odmg   := '(' key_components ')'
key_components        := key_component [key_component_suc(*)]
key_component_suc     := ',' key_component
key_component         := member_path [component_option(*)]
component_option      := ignore_case | descending

// attribute(s), which include specific ODABA extensions

attr_dcl              := attribute attr_def ';'
attr_def              := attr_spec | attr_specs
attr_specs            := '{' sattr_spec(*) '}'
sattr_spec            := attr_spec ';'
attr_spec             := type_ref declarators

// reference(s)

ref_dcl               := reference refs_def ';'
refs_def              := ref_def | ref_specs
ref_specs             := '{' sref_spec(*) '}'
sref_spec             := ref_def ';'
ref_def               := type_ref [ ref_option(*) ] references 
ref_option            := guid | weak_typed | update | multiple_key | delete_empty 
references            := ref_declarator [references_suc(*)] 
references_suc        := ',' ref_declarator
ref_declarator        := collection [col_ext_ref(*)]

// relationship(s)

rel_dcl               := relationship rels_def ';'
rels_def              := rel_def | rel_specs
rel_specs             := '{' srel_spec(*) '}'
srel_spec             := rel_def ';'
rel_def               := type_ref [ rel_option(*) ] relationships
rel_option            := ref_option | owner | no_create | dependent | secondary | shared
relationships         := rel_declarator [relationships_suc(*)] 
relationships_suc     := ',' rel_declarator
rel_declarator        := collection [col_ext_rel(*)]                   // in ODABA optional, but always sugested

// collections 

collection            := identifier [col_dimension] [assigned_value] 
col_dimension         := '[' [ number ] ']'                                // ODABA extension

col_ext_rel           := inverse_spec | base_collection | col_ext_ref
inverse_spec          := inverse inverse_traversal_path
inverse_traversal_path:= identifier [typed_identifier]
typed_identifier      := scope_op identifier
base_collection       := based_on base_path
base_path             := member_path | '*'
member_path           := extent_name | property_extension(*)
extent_name           := identifier | any_type
property_extension    := '.' identifier

col_ext_ref           := order_keys | attr_ext_decl
attr_ext_decl         := sources | constraint | version
constraint            := _constraint '(' operand ')'
sources               := _source operand_list
version               := _version number
order_keys            := ordered_by '(' index_specs ')'                        // ODABA extension
index_specs           := index_spec [index_spec_suc(*)]
index_spec_suc        := ',' index_spec
index_spec            := key_name [index_option(*)]
key_name              := identifier
index_option          := unique | not_empty | temporary

// operations

meth_dcl              := [oneway] mtype_ref [ref_symbol(*)] meth_ident parameter_dcls [raises_expr] [context_expr]
meth_ident            := ['~'] scoped_name [ impl_ident ] [cun_op]
impl_ident            := '.' identifier
mtype_ref             := [type_ref_options(*)] simple_type_spec

parameter_dcls        := '(' [params_dcl] ')'

raises_expr           := raises '(' scoped_names ')'                   // not supported
scoped_names          := scoped_name [scoped_name_suc(*)]
scoped_name_suc       := ',' scoped_name

context_expr          := context '(' string_literals ')'               // not supported
string_literals       := string_literal [string_literal_suc(*)]
string_literal_suc    := ',' string_literal
string_literal        := string

// members, parameter declarations, parameters, categories, declarators

members               := member(*)
member                := [_global] type_spec declarators ';'

params_dcl            := param_dcl [param_dcl_suc(*)]
param_dcl_suc         := ',' param_dcl
param_dcl             := [param_attribute] simple_type_spec declarator
param_attribute       := in | out | inout

parm_list             := parameter [parm_ext(*)]
parm_ext              := ',' parameter
parameter             := parm_spec | operand | '*'
parm_spec             := [simple_type_spec] [ref_symbol(*)] identifier [fixed_array_size(*)] assigned_value

categories            := category_list | operand
category_list         := category_spec [category_ext(*)]
category_ext          := ',' category_spec
category_spec         := cat_name [ cat_condition ]
cat_condition         := ':' operand
cat_name              := identifier | string | number

declarators           := declarator [declarator_suc(*)]
declarator_suc        := ',' declarator
declarator            := [ref_symbol(*)] identifier [fixed_array_size(*)] [assigned_value] [attr_ext_decl(*)]
ref_symbol            := '*' | '&'
fixed_array_size      := '[' size_spec ']'
size_spec             := size [ dimension ]
size                  := number
dimension             := ',' number
assigned_value        := assign_op operand

// type_ref, which includes ODMG 3.0 as subset (common definition) 

type_ref              := [type_ref_options(*)] domain_type             // ODABA extension
type_ref_options      := priv_option | prop_option
prop_option           := _static | _collection | _transient | _virtual | not_empty   // ODABA extension
priv_option           := _private | _public | _protected               // ODABA extension
domain_type           := simple_type_spec| struct_type | enum_type 

// type_spec 

type_spec             := simple_type_spec | constr_type_spec
constr_type_spec      := struct_type | union_type | enum_type

simple_type_spec      := base_type_spec | extended_type_spec
base_type_spec        := floating_pt_type | integer_type | char_len_types | boolean_type | octet_type | date_type | time_type | timestamp_type | bit_type | binary_type | any_type
extended_type_spec    := array_type | gstring_type | coll_type | interval_type | generic_type | scoped_name

array_type            := array_spec '<' simple_type_spec [array_dim] '>'
array_spec            := array | sequence
array_dim             := [','] number

gstring_type          := string_type string_size
string_size           := '<' number '>'

coll_type             := dict_coll | coll_coll
coll_coll             := coll_spec '<' simple_type_spec '>'
coll_spec             := set | list | bag
dict_coll             := _dictionary '<' simple_type_spec ',' simple_type_spec '>'

interval_type         := interval '<' simple_type_spec '>'

generic_type          := identifier gentype_parm                       // ODABA extension
gentype_parm          := gentype_parm_new | gentype_parm_old           // ODABA extension
gentype_parm_new      := '<' simple_type_spec '>'                      // ODABA extension
gentype_parm_old      := '(' simple_type_spec ')'                      // ODABA extension

// basic types 

char_len_types        := char_types [ len_spec ]
len_spec              := '(' size ')'                                  // ODABA extension
char_types            := char_type | string_type | coded_type | wstring_type

integer_type          := [_unsigned] int_types 
int_types             := base_int | int_spec
base_int              := short_int | long_int | long_long_int
long_long_int         := long_int long_int
int_spec              := int_type [int_size]                           // ODABA extension
int_size              := '(' size [','] [precision_val] ')'            // ODABA extension
precision_val         := number                                        // ODABA extension

// base types
date_type             := 'date'         | __date_type
__date_type           :: 'DATE'
time_type             := 'time'         | __time_type
__time_type           :: 'TIME'
timestamp_type        := 'Timestamp'    | 'datetime' | __timestamp_type
__timestamp_type      :: 'DATETIME'
coded_type            := 'coded'        | __coded_type                 // ODABA extension
__coded_type          :: 'CODED'        | 'CCHAR'            
string_type           := 'string'       | __string_type                // ODABA extension
__string_type         :: 'STRING'       | 'MEMO'
wstring_type          := 'wstring'      | __wstring_type               // ODABA extension
__wstring_type        :: 'WSTRING'           

char_type             :: 'char'         | 'CHAR'  | 'int8'
floating_pt_type      :: 'double'       | 'float' | 'real' | 'REAL'
boolean_type          :: 'boolean'      | 'bool'  | 'BOOL' | 'logical' | 'LOGICAL'
any_type              :: 'any' | 'void' | 'VOID'  | 'ANY'                             
bit_type              :: 'bit'          | 'BIT'                        // ODABA extension
short_int             :: 'int16'        | 'SHORT' | 'short'  
long_int              :: 'int32'        | 'LONG'  | 'long'
int_type              :: 'int'          | 'INT'   | 'DEC'              // ODABA extension
_unsigned             :: 'unsigned'     | 'UNSIGNED'
octet_type            :: 'octet'                                       //not supported in ODABA
binary_type           :: 'binary'       | 'BINARY' | 'BLOB'            // ODABA extension

//   standard key words
_exception            := 'exception'    | __exception
__exception           :: 'EXCEPTION'
_include              := 'include'      | __include
__include             :: 'INCLUDE'
_private              := 'private'      | __private
__private             :: 'PRIVATE'
_protected            := 'protected'    | __protected
__protected           :: 'PROTECTED'
_public               := 'public'       | __public
__public              :: 'PUBLIC'
_static               := 'static'       | __static
__static              :: 'STATIC'       | '__cdecl'
_virtual              := 'virtual'      | __virtual
__virtual             :: 'VIRTUAL'
_transient            := 'transient'    | __transient
__transient           :: 'TRANSIENT'
_new                  :: 'new'          | 'NEW'
_typedef              :: 'typedef'      | 'TYPEDEF'
_enum                 :: 'enum'         | 'ENUM'
_struct               :: 'struct'       | 'STRUCT'
_union                :: 'union'        | 'UNION'
_switch               :: 'switch'       | 'SWITCH'
_case                 :: 'case'         | 'CASE'
_default              :: 'default'      | 'DEFAULT' | 'other' | 'OTHER'
_interface            := 'interface'    | _interface_
_interface_           :: 'INTERFACE'
_view                 := 'view'         | __view
__view                :: 'VIEW'
_module               := 'module'       | __module
__module              :: 'MODULE'
_namespace            := 'namespace'    | __namespace
__namespace           :: 'NAMESPACE'
_const                :: 'const'        | 'CONST'
_class                := 'class'        | __class
__class               :: 'CLASS'
extends               := 'extends'      
__extends             :: 'EXTENDS'
in                    := 'in'           | __in
__in                  :: 'IN'
out                   := 'out'          | __out
__out                 :: 'OUT'
inout                 := 'inout'        | __inout
__inout               :: 'INOUT'
oneway                := 'oneway'       | __oneway                     // not supported in ODABA
__oneway              :: 'ONEWAY'                     
raises                := 'raises'       | __raises
__raises              :: 'RAISES'

array                 := 'array'        | __array
__array               :: 'ARRAY'
sequence              := 'sequence'     | __sequence
__sequence            :: 'SEQUENCE'
set                   := 'set'          | __set
__set                 :: 'SET'
list                  := 'list'         | __list
__list                :: 'LIST'
bag                   := 'bag'          | __bag
__bag                 :: 'BAG'
_dictionary           := 'dictionary'   | __dictionary
__dictionary          :: 'DICTIONARY'
attribute             := 'attribute'    | ___attribute
___attribute          :: 'ATTRIBUTE'
relationship          := 'relationship' | __relationship
__relationship        :: 'RELATIONSHIP'
reference             := 'reference'    | __reference
__reference           :: 'REFERENCE'
_collection           := 'collection'   | __collection
__collection          :: 'COLLECTION'
inverse               := 'inverse'      | __inverse
__inverse             :: 'INVERSE'
extent                := 'extent'       | __extent
__extent              :: 'EXTENT'
key                   := 'key' | 'keys' | __key
__key                 :: 'KEY' | 'KEYS'
context               := 'context'      | __context
__context             :: 'CONTEXT'

_select               :: 'Select'       | 'SELECT'
_from                 :: 'From'         | 'FROM'
_where                :: 'Where'        | 'WHERE' 
_having               :: 'Having'       | 'HAVING'
_join                 :: 'Join'         | 'JOIN'
_minus                :: 'Minus'        | 'MINUS'
_intersect            :: 'Intersect'    | 'INTERSECT'
_group_by             :: 'GroupBy'      | 'GROUP_BY'
_order_by             :: 'OrderBy'      | 'ORDER_BY'
_tofile               :: 'ToFile'       | 'TO_FILE'
_todb                 :: 'ToDatabase'   | 'TO_DATABASE'
_use                  :: 'Use'          | 'USE'

//    ODABA keyword extensions 
_database             := 'database'         | __database
__database            :: 'DATABASE'
_datasource           := 'datasource'       | __datasource
__datasource          :: 'DATASOURCE'
schema                := 'schema'       | __schema
__schema              :: 'SCHEMA'
update                := 'update'       | __update
__update              :: 'UPDATE'
multiple_key          := 'multiple_key' | __multiple_key
__multiple_key        :: 'MULTIPLE_KEY'
no_create             := 'no_create'    | __no_create
__no_create           :: 'NO_CREATE'
ordered_by            := 'ordered_by'   | __ordered_by
__ordered_by          :: 'ORDERED_BY'
unique                := 'unique'       | __unique
__unique              :: 'UNIQUE'
not_empty             := 'not_empty'    | __not_empty
__not_empty           :: 'NOT_EMPTY'
temporary             := 'temporary'    | __temporary
__temporary           :: 'TEMPORARY'
guid                  := 'guid'         | __guid
__guid                :: 'GUID'
weak_typed            := 'weak_typed'   | __weak_typed
__weak_typed          :: 'WEAK_TYPED'
owner                 := 'owner'        | __owner
__owner               :: 'OWNER'
shared                := 'shared'        | __shared
__shared              :: 'SHARED'
dependent             := 'dependent'    | __dependent
__dependent           :: 'DEPENDENT'
secondary             := 'secondary'    | __secondary
__secondary           :: 'SECONDARY'
based_on              := 'based_on'     | __based_on
__based_on            :: 'BASED_ON'
subset                := 'subset'       | __subset
__subset              :: 'SUBSET'
superset              := 'superset'     | __superset
__superset            :: 'SUPERSET'
ident_key             := 'ident_key'    | __ident_key
__ident_key           :: 'IDENT_KEY'
complete              := 'complete'     | __complete
__complete            :: 'COMPLETE'
distinct              := 'distinct'     | __distinct
__distinct            :: 'DISTINCT'
intersect             := 'intersect'    | __intersect
__intersect           :: 'INTERSECT'
ignore_case           := 'ignore_case'  | __ignore_case
__ignore_case         :: 'IGNORE_CASE'
descending            := 'descending'   | __descending
__descending          :: 'DESCENDING'
interval              := 'interval'     | __interval
__interval            :: 'INTERVAL'
_constraint           := 'constraint'   | __constraint
__constraint          :: 'CONSTRAINT'
_alignment            := 'alignment'   | __alignment
__alignment           :: 'ALIGNMENT'
delete_empty          := 'delete_empty' | __delete_empty
__delete_empty        :: 'DELETE_EMPTY'
_source              := 'source' | __source
__source             :: 'SOURCE'
_version              := 'version' | __version
__version             :: 'VERSION'

// OQL specifications ...
OQLExpression         := [meth_dcl] expr_code [';']

// method definitions
method                := [block_intro(*)] method_spec
method_spec           := doc_template | expression | cpp_function | window | control

block_intro           := comment_block | pragma | member | file_reference
file_reference        := _include string  ';' 
pragma                := '#' multiple_line 

// document templates  (das geht so einfach nicht !!!)

doc_template          := '<template>' dct_header [dct_variables] [ dct_spec ] '</template>'
dct_header            := '<header>' meth_dcl '</header>'
dct_variables         := '<variables>' member(*) '</variables>'
dct_spec              := fixed_text | extended_text(*)
fixed_text            := anychar(*)
extended_text         := [fixed_text] imbedded_expr
imbedded_expr         := comp_expr | output_expr
output_expr           := '<:' expr_element(*) ':>'
comp_expr             := '<%' expr_element(*) '%>'
expr_element          := member | statement

// expressions: entry points: OQLExpression, expression

expression            := _expression expr_spec
expr_spec             := expr_dcl | expr_def
expr_dcl              := meth_dcl ';'
expr_def              := meth_dcl expr_code [';']
// expr_code kommt weiter hinten
var_defs              := _variables [ member(*) ]
init_code             := _init [ statement(*) ]
proc_code             := [ _process ] statement(*)
error_code            := _on_error [ statement(*) ]
final_code            := _final [ statement(*) ]


// OQL SELECT statement
OQLSelect             := sel_spec from_spec [sel_extensions(*)] [output_spec]
sel_spec              := _select operand_list
sel_extensions        := where_spec | having_spec | group_spec | order_spec

output_spec           := to_file | to_database
to_file               := _tofile operand_list   // ToFile( Path=Console, FieldSeparator=',', StringSeparator='"', LineSeparator=10,, HeadLine=YES )
to_database           := _todb operand_list     // ToDatabase ( Datasource='Output',  Extent=SelectedPersons )

// simplified C++ function specification (for import/export, only)

cpp_function          := funct_dcl | funct_def
funct_dcl             := meth_dcl ';'
funct_def             := meth_dcl function_text [';']
function_text         := [ ini_code ] function_block
ini_code              := ':' ini_line(*)
ini_line              := blockstring | string | comment_block 
function_block        := '{' [fct_line(*)] '}'
fct_line              := comment_block | function_block | string | blockstring | _process | _on_error | _final 

// window definition (not yet implemented
window                := _window identifier [';']

// control definition (not yet implemented
control               := _control identifier [';']

// general OQL symbols

if_block              := _if condition bstatement [ else_stmt ]  
else_stmt             := [debug_opt] _else bstatement
while_block           := _while condition bstatement  
for_block             := _for '(' basic_stmt basic_stmt stmt_operlist ')' bstatement  
case_block            := _switch condition  '{' [ case_stmt(*) ] [ other_stmt ] '}'
case_stmt             := [debug_opt] _case simple_op ':' statement(*)
other_stmt            := [debug_opt] _default ':' statement(*)
condition             := '(' doperand ')'                   // condition sollte operand_list sein, mehrere Werte zulassen
bstatement            := block | statement
statement             := [debug_opt] istatement

istatement            := basic_stmt | if_block | case_block | while_block | for_block | syntax_op | ';'
basic_stmt            := stmt_operlist ';' 
stmt_operlist         := doperand [stoplist_ext(*)] 
stoplist_ext          := ',' doperand
doperand              := [debug_opt] operand

debug_opt             := '#' [ auto_run ]
auto_run              := ':' identifier

syntax_op             := return_op | error_op | leave_op | continue_op | break_op | exception_op | nv_op | eh_op
return_op             := _return [operand] ';'
error_op              := _error  [operand] ';'
eh_op                 := _exceptions [operand] ';'
nv_op                 := _null_value [operand] ';'
nv_handling           := _accept | _ignore | _exception
exception_op          := _exception [operand] ';'
leave_op              := _leave_ ';'
break_op              := _break ';'
continue_op           := _continue ';'

// acess_path (refers to expr_code, statement)

access_path           := path_element [ path_extension(*) ]
path_extension        := ext_op path_element 
ext_op                := '.' | '@' | '->'
path_element          := path_operand [ operand_list ]
path_operand          := path_name | coll_operand | expr_code 
path_name             := pname [ name_index ]

oql_oper              := _select | _from | _where | _having | _group_by | _order_by | _join | _union | _minus | _intersect | _tofile | _todb | _use
name_index            := '[' operand ']'
coll_operand          := '[' access_path ']'
operand_list          := '(' [parm_list] ')' 

operand               := un_operation [ bin_operand ] 
bin_operand           := bin_op operand 
un_operation          := [un_oper] simple_op	
un_oper               := un_op | cast_op
cast_op               := '(' simple_type_spec ')'
simple_op             := OQLSelect | access_path | block | sngl_operand | constant | sys_variable	
sngl_operand          := '(' operand ')'
sys_variable          := '%' identifier '%'

// names
pname                 := oql_oper | scoped_name | db_name | any_type
scoped_name           := identifier [ scoped_name_ext(*) ]
scoped_name_ext       := scope_op identifier
db_name               := '#' identifier
identifier            := name

// block und expr_code müssen hier liegen, damit statement nicht zu früh kommt
expr_code             := '{' [var_defs] [init_code] proc_code [error_code] [final_code] '}' 
block                 := '{' [ statement(*) ] '}'			

// OQL keywords

_global               := 'global'     | __global
__global              :: 'GLOBAL'
_expression           := 'expression' | _expression_
_expression_          :: 'EXPRESSION'
_window               := 'window'     | __window
__window              :: 'WINDOW'
_control              := 'control'    | __control
__control             :: 'CONTROL'
_variables            := 'variables'  | __variables
__variables           :: 'VARIABLES'
_init                 := 'init'       | __init
__init                :: 'INIT'
_process              := 'process'    | __process
__process             :: 'PROCESS'    | 'BEGINSEQ'
_on_error             := 'on_error'   | __on_error
__on_error            :: 'ON_ERROR'   | 'RECOVER'
_final                := 'final'      | __final
__final               :: 'FINAL'      | 'ENDSEQ'

_if                   :: 'if'         | 'IF'
_else                 :: 'else'       | 'ELSE'
_while                :: 'while'      | 'WHILE'
_for                  :: 'for'        | 'FOR'
_continue             :: 'continue'   | 'CONTINUE'
_leave_               :: 'leave'      | 'LEAVE'
_break                :: 'break'      | 'BREAK'
_error                :: 'error'      | 'ERROR'
_return               :: 'return'     | 'RETURN'
_null_value           :: '#NullValue' | '#NULLVALUE'
_exceptions           :: '#Exceptions'| '#EXCEPTIONS'
_ignore               := 'ignore'     | __ignore
__ignore              :: 'IGNORE'
_accept               := 'accept'     | __accept
__accept              :: 'ACCEPT'

scope_op              := '::' 
cun_op                := '++' | '--' | _not | bin_op 		
un_op                 := '--' | '++' | '-' | _not 	
bin_op                := bin_assign_op | '^' | '%' | '+' | '-' | '*' | '/' | _and | _or | _xor | '>' | '<' | '==' | '<=' | '>=' | '<>' | '!=' | '=' | assign_op
assign_op             := '=' | '&='  
bin_assign_op         := '+=' | '-=' | '*=' | '/='

_not                  := _not_kw | '!'  
_and                  := _and_kw | '&&' 
_or                   := _or_kw  | '||'
_not_kw               :: 'not' | 'NOT' 
_and_kw               :: 'and' | 'AND' 
_or_kw                :: 'or'  | 'OR'  
_xor                  :: 'xor' | 'XOR'

// OQL specifications END

// comment line characters
CC                    := '//'
comment_block         := '/' '*' comment_next
comment_next          := comment_end | comment_cont
comment_cont          := anychar comment_next
comment_end           := '*' '/'

// bnf references

std_symbols          ::= class(BNFStandardSymbols)
spec_symbols         ::= class(BNFSpecialSymbols)
name                 ::= ref(std_name)
number               ::= ref(std_integer)
std_float            ::= ref(std_float)
std_bool             ::= ref(std_bool)
string               ::= ref(std_string)
constant             ::= ref(std_constant)
blockstring          ::= ref(spec_block)
anychar              ::= ref(std_anychar)
multiple_line        ::= ref(spec_line)
nl                   ::= ref(std_nl)

*/


  BNFSymbol  *OSI = this;
  if ( !bs_parent ) bs_parent = this;

  BNFSymbol  *std_symbols = new BNFStandardSymbols(bs_parent);
  BNFSymbol  *spec_symbols = new BNFSpecialSymbols(bs_parent);
  BNFSymbol  *name = top_symbol->GetSymbol("std_name");
  BNFSymbol  *number = top_symbol->GetSymbol("std_integer");
  BNFSymbol  *std_float = top_symbol->GetSymbol("std_float");
  BNFSymbol  *std_bool = top_symbol->GetSymbol("std_bool");
  BNFSymbol  *string = top_symbol->GetSymbol("std_string");
  BNFSymbol  *constant = top_symbol->GetSymbol("std_constant");
  BNFSymbol  *blockstring = top_symbol->GetSymbol("spec_block");
  BNFSymbol  *anychar = top_symbol->GetSymbol("std_anychar");
  BNFSymbol  *multiple_line = top_symbol->GetSymbol("spec_line");
  BNFSymbol  *nl = top_symbol->GetSymbol("std_nl");
  if ( !bs_parent || bs_parent == this )
    SetFirst();
  BNFSymbol  *debug_info = new BNFSymbol(top_symbol,"debug_info");
  BNFSymbol  *osi_element = new BNFSymbol(top_symbol,"osi_element");
  BNFSymbol  *osi_definition = new BNFSymbol(top_symbol,"osi_definition");
  BNFSymbol  *osi_class = new BNFSymbol(top_symbol,"osi_class");
  BNFSymbol  *osi_class_def = new BNFSymbol(top_symbol,"osi_class_def");
  BNFSymbol  *osi_exports = new BNFSymbol(top_symbol,"osi_exports");
  BNFSymbol  *osi_export_dcl = new BNFSymbol(top_symbol,"osi_export_dcl");
  BNFSymbol  *_debugprocs = new BNFSymbol(top_symbol,"_debugprocs");
  BNFSymbol  *__debugprocs = new BNFSymbol(top_symbol,"__debugprocs");
  BNFSymbol  *ODL = new BNFSymbol(top_symbol,"ODL");
  BNFSymbol  *data_source = new BNFSymbol(top_symbol,"data_source");
  BNFSymbol  *datasource = new BNFSymbol(top_symbol,"datasource");
  BNFSymbol  *dictionary = new BNFSymbol(top_symbol,"dictionary");
  BNFSymbol  *database = new BNFSymbol(top_symbol,"database");
  BNFSymbol  *location = new BNFSymbol(top_symbol,"location");
  BNFSymbol  *sc_element = new BNFSymbol(top_symbol,"sc_element");
  BNFSymbol  *sc_definition = new BNFSymbol(top_symbol,"sc_definition");
  BNFSymbol  *schema_dcl = new BNFSymbol(top_symbol,"schema_dcl");
  BNFSymbol  *mod_definition = new BNFSymbol(top_symbol,"mod_definition");
  BNFSymbol  *module_dcl = new BNFSymbol(top_symbol,"module_dcl");
  BNFSymbol  *mod_element = new BNFSymbol(top_symbol,"mod_element");
  BNFSymbol  *type_dcl = new BNFSymbol(top_symbol,"type_dcl");
  BNFSymbol  *type_def = new BNFSymbol(top_symbol,"type_def");
  BNFSymbol  *namespace_dcl = new BNFSymbol(top_symbol,"namespace_dcl");
  BNFSymbol  *ns_element = new BNFSymbol(top_symbol,"ns_element");
  BNFSymbol  *update_option = new BNFSymbol(top_symbol,"update_option");
  BNFSymbol  *struct_type = new BNFSymbol(top_symbol,"struct_type");
  BNFSymbol  *struct_def = new BNFSymbol(top_symbol,"struct_def");
  BNFSymbol  *union_type = new BNFSymbol(top_symbol,"union_type");
  BNFSymbol  *switch_type_spec = new BNFSymbol(top_symbol,"switch_type_spec");
  BNFSymbol  *case_def = new BNFSymbol(top_symbol,"case_def");
  BNFSymbol  *case_label = new BNFSymbol(top_symbol,"case_label");
  BNFSymbol  *case_inst = new BNFSymbol(top_symbol,"case_inst");
  BNFSymbol  *default_def = new BNFSymbol(top_symbol,"default_def");
  BNFSymbol  *element_spec = new BNFSymbol(top_symbol,"element_spec");
  BNFSymbol  *enum_type = new BNFSymbol(top_symbol,"enum_type");
  BNFSymbol  *base_class = new BNFSymbol(top_symbol,"base_class");
  BNFSymbol  *enum_def = new BNFSymbol(top_symbol,"enum_def");
  BNFSymbol  *enumerator = new BNFSymbol(top_symbol,"enumerator");
  BNFSymbol  *ref_type = new BNFSymbol(top_symbol,"ref_type");
  BNFSymbol  *enum_value = new BNFSymbol(top_symbol,"enum_value");
  BNFSymbol  *const_dcl = new BNFSymbol(top_symbol,"const_dcl");
  BNFSymbol  *const_type = new BNFSymbol(top_symbol,"const_type");
  BNFSymbol  *except_dcl = new BNFSymbol(top_symbol,"except_dcl");
  BNFSymbol  *exceptions_def = new BNFSymbol(top_symbol,"exceptions_def");
  BNFSymbol  *exception_specs = new BNFSymbol(top_symbol,"exception_specs");
  BNFSymbol  *sexception_spec = new BNFSymbol(top_symbol,"sexception_spec");
  BNFSymbol  *exception_def = new BNFSymbol(top_symbol,"exception_def");
  BNFSymbol  *class_dcl = new BNFSymbol(top_symbol,"class_dcl");
  BNFSymbol  *class_def = new BNFSymbol(top_symbol,"class_def");
  BNFSymbol  *class_header = new BNFSymbol(top_symbol,"class_header");
  BNFSymbol  *type_property_list = new BNFSymbol(top_symbol,"type_property_list");
  BNFSymbol  *type_property = new BNFSymbol(top_symbol,"type_property");
  BNFSymbol  *alignment_spec = new BNFSymbol(top_symbol,"alignment_spec");
  BNFSymbol  *interface_dcl = new BNFSymbol(top_symbol,"interface_dcl");
  BNFSymbol  *interface_spec = new BNFSymbol(top_symbol,"interface_spec");
  BNFSymbol  *interface_header = new BNFSymbol(top_symbol,"interface_header");
  BNFSymbol  *exports = new BNFSymbol(top_symbol,"exports");
  BNFSymbol  *export_dcl = new BNFSymbol(top_symbol,"export_dcl");
  BNFSymbol  *view_dcl = new BNFSymbol(top_symbol,"view_dcl");
  BNFSymbol  *view_def = new BNFSymbol(top_symbol,"view_def");
  BNFSymbol  *view_member = new BNFSymbol(top_symbol,"view_member");
  BNFSymbol  *view_header = new BNFSymbol(top_symbol,"view_header");
  BNFSymbol  *from_spec = new BNFSymbol(top_symbol,"from_spec");
  BNFSymbol  *where_spec = new BNFSymbol(top_symbol,"where_spec");
  BNFSymbol  *having_spec = new BNFSymbol(top_symbol,"having_spec");
  BNFSymbol  *order_spec = new BNFSymbol(top_symbol,"order_spec");
  BNFSymbol  *group_spec = new BNFSymbol(top_symbol,"group_spec");
  BNFSymbol  *inheritance_spec = new BNFSymbol(top_symbol,"inheritance_spec");
  BNFSymbol  *extends_spec = new BNFSymbol(top_symbol,"extends_spec");
  BNFSymbol  *base_types = new BNFSymbol(top_symbol,"base_types");
  BNFSymbol  *base_type_suc = new BNFSymbol(top_symbol,"base_type_suc");
  BNFSymbol  *base_type = new BNFSymbol(top_symbol,"base_type");
  BNFSymbol  *base_option = new BNFSymbol(top_symbol,"base_option");
  BNFSymbol  *base_declarator = new BNFSymbol(top_symbol,"base_declarator");
  BNFSymbol  *extent_spec = new BNFSymbol(top_symbol,"extent_spec");
  BNFSymbol  *extents_def = new BNFSymbol(top_symbol,"extents_def");
  BNFSymbol  *extent_specs = new BNFSymbol(top_symbol,"extent_specs");
  BNFSymbol  *sextent_spec = new BNFSymbol(top_symbol,"sextent_spec");
  BNFSymbol  *extent_def = new BNFSymbol(top_symbol,"extent_def");
  BNFSymbol  *extent_option = new BNFSymbol(top_symbol,"extent_option");
  BNFSymbol  *sub_sets = new BNFSymbol(top_symbol,"sub_sets");
  BNFSymbol  *subset_options = new BNFSymbol(top_symbol,"subset_options");
  BNFSymbol  *super_sets = new BNFSymbol(top_symbol,"super_sets");
  BNFSymbol  *extent_names = new BNFSymbol(top_symbol,"extent_names");
  BNFSymbol  *extent_names_suc = new BNFSymbol(top_symbol,"extent_names_suc");
  BNFSymbol  *key_spec = new BNFSymbol(top_symbol,"key_spec");
  BNFSymbol  *keys_def = new BNFSymbol(top_symbol,"keys_def");
  BNFSymbol  *key_specs = new BNFSymbol(top_symbol,"key_specs");
  BNFSymbol  *skey_spec = new BNFSymbol(top_symbol,"skey_spec");
  BNFSymbol  *key_def = new BNFSymbol(top_symbol,"key_def");
  BNFSymbol  *key_components_ext = new BNFSymbol(top_symbol,"key_components_ext");
  BNFSymbol  *key_components_odmg = new BNFSymbol(top_symbol,"key_components_odmg");
  BNFSymbol  *key_components = new BNFSymbol(top_symbol,"key_components");
  BNFSymbol  *key_component_suc = new BNFSymbol(top_symbol,"key_component_suc");
  BNFSymbol  *key_component = new BNFSymbol(top_symbol,"key_component");
  BNFSymbol  *component_option = new BNFSymbol(top_symbol,"component_option");
  BNFSymbol  *attr_dcl = new BNFSymbol(top_symbol,"attr_dcl");
  BNFSymbol  *attr_def = new BNFSymbol(top_symbol,"attr_def");
  BNFSymbol  *attr_specs = new BNFSymbol(top_symbol,"attr_specs");
  BNFSymbol  *sattr_spec = new BNFSymbol(top_symbol,"sattr_spec");
  BNFSymbol  *attr_spec = new BNFSymbol(top_symbol,"attr_spec");
  BNFSymbol  *ref_dcl = new BNFSymbol(top_symbol,"ref_dcl");
  BNFSymbol  *refs_def = new BNFSymbol(top_symbol,"refs_def");
  BNFSymbol  *ref_specs = new BNFSymbol(top_symbol,"ref_specs");
  BNFSymbol  *sref_spec = new BNFSymbol(top_symbol,"sref_spec");
  BNFSymbol  *ref_def = new BNFSymbol(top_symbol,"ref_def");
  BNFSymbol  *ref_option = new BNFSymbol(top_symbol,"ref_option");
  BNFSymbol  *references = new BNFSymbol(top_symbol,"references");
  BNFSymbol  *references_suc = new BNFSymbol(top_symbol,"references_suc");
  BNFSymbol  *ref_declarator = new BNFSymbol(top_symbol,"ref_declarator");
  BNFSymbol  *rel_dcl = new BNFSymbol(top_symbol,"rel_dcl");
  BNFSymbol  *rels_def = new BNFSymbol(top_symbol,"rels_def");
  BNFSymbol  *rel_specs = new BNFSymbol(top_symbol,"rel_specs");
  BNFSymbol  *srel_spec = new BNFSymbol(top_symbol,"srel_spec");
  BNFSymbol  *rel_def = new BNFSymbol(top_symbol,"rel_def");
  BNFSymbol  *rel_option = new BNFSymbol(top_symbol,"rel_option");
  BNFSymbol  *relationships = new BNFSymbol(top_symbol,"relationships");
  BNFSymbol  *relationships_suc = new BNFSymbol(top_symbol,"relationships_suc");
  BNFSymbol  *rel_declarator = new BNFSymbol(top_symbol,"rel_declarator");
  BNFSymbol  *collection = new BNFSymbol(top_symbol,"collection");
  BNFSymbol  *col_dimension = new BNFSymbol(top_symbol,"col_dimension");
  BNFSymbol  *col_ext_rel = new BNFSymbol(top_symbol,"col_ext_rel");
  BNFSymbol  *inverse_spec = new BNFSymbol(top_symbol,"inverse_spec");
  BNFSymbol  *inverse_traversal_path = new BNFSymbol(top_symbol,"inverse_traversal_path");
  BNFSymbol  *typed_identifier = new BNFSymbol(top_symbol,"typed_identifier");
  BNFSymbol  *base_collection = new BNFSymbol(top_symbol,"base_collection");
  BNFSymbol  *base_path = new BNFSymbol(top_symbol,"base_path");
  BNFSymbol  *member_path = new BNFSymbol(top_symbol,"member_path");
  BNFSymbol  *extent_name = new BNFSymbol(top_symbol,"extent_name");
  BNFSymbol  *property_extension = new BNFSymbol(top_symbol,"property_extension");
  BNFSymbol  *col_ext_ref = new BNFSymbol(top_symbol,"col_ext_ref");
  BNFSymbol  *attr_ext_decl = new BNFSymbol(top_symbol,"attr_ext_decl");
  BNFSymbol  *constraint = new BNFSymbol(top_symbol,"constraint");
  BNFSymbol  *sources = new BNFSymbol(top_symbol,"sources");
  BNFSymbol  *version = new BNFSymbol(top_symbol,"version");
  BNFSymbol  *order_keys = new BNFSymbol(top_symbol,"order_keys");
  BNFSymbol  *index_specs = new BNFSymbol(top_symbol,"index_specs");
  BNFSymbol  *index_spec_suc = new BNFSymbol(top_symbol,"index_spec_suc");
  BNFSymbol  *index_spec = new BNFSymbol(top_symbol,"index_spec");
  BNFSymbol  *key_name = new BNFSymbol(top_symbol,"key_name");
  BNFSymbol  *index_option = new BNFSymbol(top_symbol,"index_option");
  BNFSymbol  *meth_dcl = new BNFSymbol(top_symbol,"meth_dcl");
  BNFSymbol  *meth_ident = new BNFSymbol(top_symbol,"meth_ident");
  BNFSymbol  *impl_ident = new BNFSymbol(top_symbol,"impl_ident");
  BNFSymbol  *mtype_ref = new BNFSymbol(top_symbol,"mtype_ref");
  BNFSymbol  *parameter_dcls = new BNFSymbol(top_symbol,"parameter_dcls");
  BNFSymbol  *raises_expr = new BNFSymbol(top_symbol,"raises_expr");
  BNFSymbol  *scoped_names = new BNFSymbol(top_symbol,"scoped_names");
  BNFSymbol  *scoped_name_suc = new BNFSymbol(top_symbol,"scoped_name_suc");
  BNFSymbol  *context_expr = new BNFSymbol(top_symbol,"context_expr");
  BNFSymbol  *string_literals = new BNFSymbol(top_symbol,"string_literals");
  BNFSymbol  *string_literal_suc = new BNFSymbol(top_symbol,"string_literal_suc");
  BNFSymbol  *string_literal = new BNFSymbol(top_symbol,"string_literal");
  BNFSymbol  *members = new BNFSymbol(top_symbol,"members");
  BNFSymbol  *member = new BNFSymbol(top_symbol,"member");
  BNFSymbol  *params_dcl = new BNFSymbol(top_symbol,"params_dcl");
  BNFSymbol  *param_dcl_suc = new BNFSymbol(top_symbol,"param_dcl_suc");
  BNFSymbol  *param_dcl = new BNFSymbol(top_symbol,"param_dcl");
  BNFSymbol  *param_attribute = new BNFSymbol(top_symbol,"param_attribute");
  BNFSymbol  *parm_list = new BNFSymbol(top_symbol,"parm_list");
  BNFSymbol  *parm_ext = new BNFSymbol(top_symbol,"parm_ext");
  BNFSymbol  *parameter = new BNFSymbol(top_symbol,"parameter");
  BNFSymbol  *parm_spec = new BNFSymbol(top_symbol,"parm_spec");
  BNFSymbol  *categories = new BNFSymbol(top_symbol,"categories");
  BNFSymbol  *category_list = new BNFSymbol(top_symbol,"category_list");
  BNFSymbol  *category_ext = new BNFSymbol(top_symbol,"category_ext");
  BNFSymbol  *category_spec = new BNFSymbol(top_symbol,"category_spec");
  BNFSymbol  *cat_condition = new BNFSymbol(top_symbol,"cat_condition");
  BNFSymbol  *cat_name = new BNFSymbol(top_symbol,"cat_name");
  BNFSymbol  *declarators = new BNFSymbol(top_symbol,"declarators");
  BNFSymbol  *declarator_suc = new BNFSymbol(top_symbol,"declarator_suc");
  BNFSymbol  *declarator = new BNFSymbol(top_symbol,"declarator");
  BNFSymbol  *ref_symbol = new BNFSymbol(top_symbol,"ref_symbol");
  BNFSymbol  *fixed_array_size = new BNFSymbol(top_symbol,"fixed_array_size");
  BNFSymbol  *size_spec = new BNFSymbol(top_symbol,"size_spec");
  BNFSymbol  *size = new BNFSymbol(top_symbol,"size");
  BNFSymbol  *dimension = new BNFSymbol(top_symbol,"dimension");
  BNFSymbol  *assigned_value = new BNFSymbol(top_symbol,"assigned_value");
  BNFSymbol  *type_ref = new BNFSymbol(top_symbol,"type_ref");
  BNFSymbol  *type_ref_options = new BNFSymbol(top_symbol,"type_ref_options");
  BNFSymbol  *prop_option = new BNFSymbol(top_symbol,"prop_option");
  BNFSymbol  *priv_option = new BNFSymbol(top_symbol,"priv_option");
  BNFSymbol  *domain_type = new BNFSymbol(top_symbol,"domain_type");
  BNFSymbol  *type_spec = new BNFSymbol(top_symbol,"type_spec");
  BNFSymbol  *constr_type_spec = new BNFSymbol(top_symbol,"constr_type_spec");
  BNFSymbol  *simple_type_spec = new BNFSymbol(top_symbol,"simple_type_spec");
  BNFSymbol  *base_type_spec = new BNFSymbol(top_symbol,"base_type_spec");
  BNFSymbol  *extended_type_spec = new BNFSymbol(top_symbol,"extended_type_spec");
  BNFSymbol  *array_type = new BNFSymbol(top_symbol,"array_type");
  BNFSymbol  *array_spec = new BNFSymbol(top_symbol,"array_spec");
  BNFSymbol  *array_dim = new BNFSymbol(top_symbol,"array_dim");
  BNFSymbol  *gstring_type = new BNFSymbol(top_symbol,"gstring_type");
  BNFSymbol  *string_size = new BNFSymbol(top_symbol,"string_size");
  BNFSymbol  *coll_type = new BNFSymbol(top_symbol,"coll_type");
  BNFSymbol  *coll_coll = new BNFSymbol(top_symbol,"coll_coll");
  BNFSymbol  *coll_spec = new BNFSymbol(top_symbol,"coll_spec");
  BNFSymbol  *dict_coll = new BNFSymbol(top_symbol,"dict_coll");
  BNFSymbol  *interval_type = new BNFSymbol(top_symbol,"interval_type");
  BNFSymbol  *generic_type = new BNFSymbol(top_symbol,"generic_type");
  BNFSymbol  *gentype_parm = new BNFSymbol(top_symbol,"gentype_parm");
  BNFSymbol  *gentype_parm_new = new BNFSymbol(top_symbol,"gentype_parm_new");
  BNFSymbol  *gentype_parm_old = new BNFSymbol(top_symbol,"gentype_parm_old");
  BNFSymbol  *char_len_types = new BNFSymbol(top_symbol,"char_len_types");
  BNFSymbol  *len_spec = new BNFSymbol(top_symbol,"len_spec");
  BNFSymbol  *char_types = new BNFSymbol(top_symbol,"char_types");
  BNFSymbol  *integer_type = new BNFSymbol(top_symbol,"integer_type");
  BNFSymbol  *int_types = new BNFSymbol(top_symbol,"int_types");
  BNFSymbol  *base_int = new BNFSymbol(top_symbol,"base_int");
  BNFSymbol  *long_long_int = new BNFSymbol(top_symbol,"long_long_int");
  BNFSymbol  *int_spec = new BNFSymbol(top_symbol,"int_spec");
  BNFSymbol  *int_size = new BNFSymbol(top_symbol,"int_size");
  BNFSymbol  *precision_val = new BNFSymbol(top_symbol,"precision_val");
  BNFSymbol  *date_type = new BNFSymbol(top_symbol,"date_type");
  BNFSymbol  *__date_type = new BNFSymbol(top_symbol,"__date_type");
  BNFSymbol  *time_type = new BNFSymbol(top_symbol,"time_type");
  BNFSymbol  *__time_type = new BNFSymbol(top_symbol,"__time_type");
  BNFSymbol  *timestamp_type = new BNFSymbol(top_symbol,"timestamp_type");
  BNFSymbol  *__timestamp_type = new BNFSymbol(top_symbol,"__timestamp_type");
  BNFSymbol  *coded_type = new BNFSymbol(top_symbol,"coded_type");
  BNFSymbol  *__coded_type = new BNFSymbol(top_symbol,"__coded_type");
  BNFSymbol  *string_type = new BNFSymbol(top_symbol,"string_type");
  BNFSymbol  *__string_type = new BNFSymbol(top_symbol,"__string_type");
  BNFSymbol  *wstring_type = new BNFSymbol(top_symbol,"wstring_type");
  BNFSymbol  *__wstring_type = new BNFSymbol(top_symbol,"__wstring_type");
  BNFSymbol  *char_type = new BNFSymbol(top_symbol,"char_type");
  BNFSymbol  *floating_pt_type = new BNFSymbol(top_symbol,"floating_pt_type");
  BNFSymbol  *boolean_type = new BNFSymbol(top_symbol,"boolean_type");
  BNFSymbol  *any_type = new BNFSymbol(top_symbol,"any_type");
  BNFSymbol  *bit_type = new BNFSymbol(top_symbol,"bit_type");
  BNFSymbol  *short_int = new BNFSymbol(top_symbol,"short_int");
  BNFSymbol  *long_int = new BNFSymbol(top_symbol,"long_int");
  BNFSymbol  *int_type = new BNFSymbol(top_symbol,"int_type");
  BNFSymbol  *_unsigned = new BNFSymbol(top_symbol,"_unsigned");
  BNFSymbol  *octet_type = new BNFSymbol(top_symbol,"octet_type");
  BNFSymbol  *binary_type = new BNFSymbol(top_symbol,"binary_type");
  BNFSymbol  *_exception = new BNFSymbol(top_symbol,"_exception");
  BNFSymbol  *__exception = new BNFSymbol(top_symbol,"__exception");
  BNFSymbol  *_include = new BNFSymbol(top_symbol,"_include");
  BNFSymbol  *__include = new BNFSymbol(top_symbol,"__include");
  BNFSymbol  *_private = new BNFSymbol(top_symbol,"_private");
  BNFSymbol  *__private = new BNFSymbol(top_symbol,"__private");
  BNFSymbol  *_protected = new BNFSymbol(top_symbol,"_protected");
  BNFSymbol  *__protected = new BNFSymbol(top_symbol,"__protected");
  BNFSymbol  *_public = new BNFSymbol(top_symbol,"_public");
  BNFSymbol  *__public = new BNFSymbol(top_symbol,"__public");
  BNFSymbol  *_static = new BNFSymbol(top_symbol,"_static");
  BNFSymbol  *__static = new BNFSymbol(top_symbol,"__static");
  BNFSymbol  *_virtual = new BNFSymbol(top_symbol,"_virtual");
  BNFSymbol  *__virtual = new BNFSymbol(top_symbol,"__virtual");
  BNFSymbol  *_transient = new BNFSymbol(top_symbol,"_transient");
  BNFSymbol  *__transient = new BNFSymbol(top_symbol,"__transient");
  BNFSymbol  *_new = new BNFSymbol(top_symbol,"_new");
  BNFSymbol  *_typedef = new BNFSymbol(top_symbol,"_typedef");
  BNFSymbol  *_enum = new BNFSymbol(top_symbol,"_enum");
  BNFSymbol  *_struct = new BNFSymbol(top_symbol,"_struct");
  BNFSymbol  *_union = new BNFSymbol(top_symbol,"_union");
  BNFSymbol  *_switch = new BNFSymbol(top_symbol,"_switch");
  BNFSymbol  *_case = new BNFSymbol(top_symbol,"_case");
  BNFSymbol  *_default = new BNFSymbol(top_symbol,"_default");
  BNFSymbol  *_interface = new BNFSymbol(top_symbol,"_interface");
  BNFSymbol  *_interface_ = new BNFSymbol(top_symbol,"_interface_");
  BNFSymbol  *_view = new BNFSymbol(top_symbol,"_view");
  BNFSymbol  *__view = new BNFSymbol(top_symbol,"__view");
  BNFSymbol  *_module = new BNFSymbol(top_symbol,"_module");
  BNFSymbol  *__module = new BNFSymbol(top_symbol,"__module");
  BNFSymbol  *_namespace = new BNFSymbol(top_symbol,"_namespace");
  BNFSymbol  *__namespace = new BNFSymbol(top_symbol,"__namespace");
  BNFSymbol  *_const = new BNFSymbol(top_symbol,"_const");
  BNFSymbol  *_class = new BNFSymbol(top_symbol,"_class");
  BNFSymbol  *__class = new BNFSymbol(top_symbol,"__class");
  BNFSymbol  *extends = new BNFSymbol(top_symbol,"extends");
  BNFSymbol  *__extends = new BNFSymbol(top_symbol,"__extends");
  BNFSymbol  *in = new BNFSymbol(top_symbol,"in");
  BNFSymbol  *__in = new BNFSymbol(top_symbol,"__in");
  BNFSymbol  *out = new BNFSymbol(top_symbol,"out");
  BNFSymbol  *__out = new BNFSymbol(top_symbol,"__out");
  BNFSymbol  *inout = new BNFSymbol(top_symbol,"inout");
  BNFSymbol  *__inout = new BNFSymbol(top_symbol,"__inout");
  BNFSymbol  *oneway = new BNFSymbol(top_symbol,"oneway");
  BNFSymbol  *__oneway = new BNFSymbol(top_symbol,"__oneway");
  BNFSymbol  *raises = new BNFSymbol(top_symbol,"raises");
  BNFSymbol  *__raises = new BNFSymbol(top_symbol,"__raises");
  BNFSymbol  *array = new BNFSymbol(top_symbol,"array");
  BNFSymbol  *__array = new BNFSymbol(top_symbol,"__array");
  BNFSymbol  *sequence = new BNFSymbol(top_symbol,"sequence");
  BNFSymbol  *__sequence = new BNFSymbol(top_symbol,"__sequence");
  BNFSymbol  *set = new BNFSymbol(top_symbol,"set");
  BNFSymbol  *__set = new BNFSymbol(top_symbol,"__set");
  BNFSymbol  *list = new BNFSymbol(top_symbol,"list");
  BNFSymbol  *__list = new BNFSymbol(top_symbol,"__list");
  BNFSymbol  *bag = new BNFSymbol(top_symbol,"bag");
  BNFSymbol  *__bag = new BNFSymbol(top_symbol,"__bag");
  BNFSymbol  *_dictionary = new BNFSymbol(top_symbol,"_dictionary");
  BNFSymbol  *__dictionary = new BNFSymbol(top_symbol,"__dictionary");
  BNFSymbol  *attribute = new BNFSymbol(top_symbol,"attribute");
  BNFSymbol  *___attribute = new BNFSymbol(top_symbol,"___attribute");
  BNFSymbol  *relationship = new BNFSymbol(top_symbol,"relationship");
  BNFSymbol  *__relationship = new BNFSymbol(top_symbol,"__relationship");
  BNFSymbol  *reference = new BNFSymbol(top_symbol,"reference");
  BNFSymbol  *__reference = new BNFSymbol(top_symbol,"__reference");
  BNFSymbol  *_collection = new BNFSymbol(top_symbol,"_collection");
  BNFSymbol  *__collection = new BNFSymbol(top_symbol,"__collection");
  BNFSymbol  *inverse = new BNFSymbol(top_symbol,"inverse");
  BNFSymbol  *__inverse = new BNFSymbol(top_symbol,"__inverse");
  BNFSymbol  *extent = new BNFSymbol(top_symbol,"extent");
  BNFSymbol  *__extent = new BNFSymbol(top_symbol,"__extent");
  BNFSymbol  *key = new BNFSymbol(top_symbol,"key");
  BNFSymbol  *__key = new BNFSymbol(top_symbol,"__key");
  BNFSymbol  *context = new BNFSymbol(top_symbol,"context");
  BNFSymbol  *__context = new BNFSymbol(top_symbol,"__context");
  BNFSymbol  *_select = new BNFSymbol(top_symbol,"_select");
  BNFSymbol  *_from = new BNFSymbol(top_symbol,"_from");
  BNFSymbol  *_where = new BNFSymbol(top_symbol,"_where");
  BNFSymbol  *_having = new BNFSymbol(top_symbol,"_having");
  BNFSymbol  *_join = new BNFSymbol(top_symbol,"_join");
  BNFSymbol  *_minus = new BNFSymbol(top_symbol,"_minus");
  BNFSymbol  *_intersect = new BNFSymbol(top_symbol,"_intersect");
  BNFSymbol  *_group_by = new BNFSymbol(top_symbol,"_group_by");
  BNFSymbol  *_order_by = new BNFSymbol(top_symbol,"_order_by");
  BNFSymbol  *_tofile = new BNFSymbol(top_symbol,"_tofile");
  BNFSymbol  *_todb = new BNFSymbol(top_symbol,"_todb");
  BNFSymbol  *_use = new BNFSymbol(top_symbol,"_use");
  BNFSymbol  *_database = new BNFSymbol(top_symbol,"_database");
  BNFSymbol  *__database = new BNFSymbol(top_symbol,"__database");
  BNFSymbol  *_datasource = new BNFSymbol(top_symbol,"_datasource");
  BNFSymbol  *__datasource = new BNFSymbol(top_symbol,"__datasource");
  BNFSymbol  *schema = new BNFSymbol(top_symbol,"schema");
  BNFSymbol  *__schema = new BNFSymbol(top_symbol,"__schema");
  BNFSymbol  *update = new BNFSymbol(top_symbol,"update");
  BNFSymbol  *__update = new BNFSymbol(top_symbol,"__update");
  BNFSymbol  *multiple_key = new BNFSymbol(top_symbol,"multiple_key");
  BNFSymbol  *__multiple_key = new BNFSymbol(top_symbol,"__multiple_key");
  BNFSymbol  *no_create = new BNFSymbol(top_symbol,"no_create");
  BNFSymbol  *__no_create = new BNFSymbol(top_symbol,"__no_create");
  BNFSymbol  *ordered_by = new BNFSymbol(top_symbol,"ordered_by");
  BNFSymbol  *__ordered_by = new BNFSymbol(top_symbol,"__ordered_by");
  BNFSymbol  *unique = new BNFSymbol(top_symbol,"unique");
  BNFSymbol  *__unique = new BNFSymbol(top_symbol,"__unique");
  BNFSymbol  *not_empty = new BNFSymbol(top_symbol,"not_empty");
  BNFSymbol  *__not_empty = new BNFSymbol(top_symbol,"__not_empty");
  BNFSymbol  *temporary = new BNFSymbol(top_symbol,"temporary");
  BNFSymbol  *__temporary = new BNFSymbol(top_symbol,"__temporary");
  BNFSymbol  *guid = new BNFSymbol(top_symbol,"guid");
  BNFSymbol  *__guid = new BNFSymbol(top_symbol,"__guid");
  BNFSymbol  *weak_typed = new BNFSymbol(top_symbol,"weak_typed");
  BNFSymbol  *__weak_typed = new BNFSymbol(top_symbol,"__weak_typed");
  BNFSymbol  *owner = new BNFSymbol(top_symbol,"owner");
  BNFSymbol  *__owner = new BNFSymbol(top_symbol,"__owner");
  BNFSymbol  *shared = new BNFSymbol(top_symbol,"shared");
  BNFSymbol  *__shared = new BNFSymbol(top_symbol,"__shared");
  BNFSymbol  *dependent = new BNFSymbol(top_symbol,"dependent");
  BNFSymbol  *__dependent = new BNFSymbol(top_symbol,"__dependent");
  BNFSymbol  *secondary = new BNFSymbol(top_symbol,"secondary");
  BNFSymbol  *__secondary = new BNFSymbol(top_symbol,"__secondary");
  BNFSymbol  *based_on = new BNFSymbol(top_symbol,"based_on");
  BNFSymbol  *__based_on = new BNFSymbol(top_symbol,"__based_on");
  BNFSymbol  *subset = new BNFSymbol(top_symbol,"subset");
  BNFSymbol  *__subset = new BNFSymbol(top_symbol,"__subset");
  BNFSymbol  *superset = new BNFSymbol(top_symbol,"superset");
  BNFSymbol  *__superset = new BNFSymbol(top_symbol,"__superset");
  BNFSymbol  *ident_key = new BNFSymbol(top_symbol,"ident_key");
  BNFSymbol  *__ident_key = new BNFSymbol(top_symbol,"__ident_key");
  BNFSymbol  *complete = new BNFSymbol(top_symbol,"complete");
  BNFSymbol  *__complete = new BNFSymbol(top_symbol,"__complete");
  BNFSymbol  *distinct = new BNFSymbol(top_symbol,"distinct");
  BNFSymbol  *__distinct = new BNFSymbol(top_symbol,"__distinct");
  BNFSymbol  *intersect = new BNFSymbol(top_symbol,"intersect");
  BNFSymbol  *__intersect = new BNFSymbol(top_symbol,"__intersect");
  BNFSymbol  *ignore_case = new BNFSymbol(top_symbol,"ignore_case");
  BNFSymbol  *__ignore_case = new BNFSymbol(top_symbol,"__ignore_case");
  BNFSymbol  *descending = new BNFSymbol(top_symbol,"descending");
  BNFSymbol  *__descending = new BNFSymbol(top_symbol,"__descending");
  BNFSymbol  *interval = new BNFSymbol(top_symbol,"interval");
  BNFSymbol  *__interval = new BNFSymbol(top_symbol,"__interval");
  BNFSymbol  *_constraint = new BNFSymbol(top_symbol,"_constraint");
  BNFSymbol  *__constraint = new BNFSymbol(top_symbol,"__constraint");
  BNFSymbol  *_alignment = new BNFSymbol(top_symbol,"_alignment");
  BNFSymbol  *__alignment = new BNFSymbol(top_symbol,"__alignment");
  BNFSymbol  *delete_empty = new BNFSymbol(top_symbol,"delete_empty");
  BNFSymbol  *__delete_empty = new BNFSymbol(top_symbol,"__delete_empty");
  BNFSymbol  *_source = new BNFSymbol(top_symbol,"_source");
  BNFSymbol  *__source = new BNFSymbol(top_symbol,"__source");
  BNFSymbol  *_version = new BNFSymbol(top_symbol,"_version");
  BNFSymbol  *__version = new BNFSymbol(top_symbol,"__version");
  BNFSymbol  *OQLExpression = new BNFSymbol(top_symbol,"OQLExpression");
  BNFSymbol  *method = new BNFSymbol(top_symbol,"method");
  BNFSymbol  *method_spec = new BNFSymbol(top_symbol,"method_spec");
  BNFSymbol  *block_intro = new BNFSymbol(top_symbol,"block_intro");
  BNFSymbol  *file_reference = new BNFSymbol(top_symbol,"file_reference");
  BNFSymbol  *pragma = new BNFSymbol(top_symbol,"pragma");
  BNFSymbol  *doc_template = new BNFSymbol(top_symbol,"doc_template");
  BNFSymbol  *dct_header = new BNFSymbol(top_symbol,"dct_header");
  BNFSymbol  *dct_variables = new BNFSymbol(top_symbol,"dct_variables");
  BNFSymbol  *dct_spec = new BNFSymbol(top_symbol,"dct_spec");
  BNFSymbol  *fixed_text = new BNFSymbol(top_symbol,"fixed_text");
  BNFSymbol  *extended_text = new BNFSymbol(top_symbol,"extended_text");
  BNFSymbol  *imbedded_expr = new BNFSymbol(top_symbol,"imbedded_expr");
  BNFSymbol  *output_expr = new BNFSymbol(top_symbol,"output_expr");
  BNFSymbol  *comp_expr = new BNFSymbol(top_symbol,"comp_expr");
  BNFSymbol  *expr_element = new BNFSymbol(top_symbol,"expr_element");
  BNFSymbol  *expression = new BNFSymbol(top_symbol,"expression");
  BNFSymbol  *expr_spec = new BNFSymbol(top_symbol,"expr_spec");
  BNFSymbol  *expr_dcl = new BNFSymbol(top_symbol,"expr_dcl");
  BNFSymbol  *expr_def = new BNFSymbol(top_symbol,"expr_def");
  BNFSymbol  *var_defs = new BNFSymbol(top_symbol,"var_defs");
  BNFSymbol  *init_code = new BNFSymbol(top_symbol,"init_code");
  BNFSymbol  *proc_code = new BNFSymbol(top_symbol,"proc_code");
  BNFSymbol  *error_code = new BNFSymbol(top_symbol,"error_code");
  BNFSymbol  *final_code = new BNFSymbol(top_symbol,"final_code");
  BNFSymbol  *OQLSelect = new BNFSymbol(top_symbol,"OQLSelect");
  BNFSymbol  *sel_spec = new BNFSymbol(top_symbol,"sel_spec");
  BNFSymbol  *sel_extensions = new BNFSymbol(top_symbol,"sel_extensions");
  BNFSymbol  *output_spec = new BNFSymbol(top_symbol,"output_spec");
  BNFSymbol  *to_file = new BNFSymbol(top_symbol,"to_file");
  BNFSymbol  *to_database = new BNFSymbol(top_symbol,"to_database");
  BNFSymbol  *cpp_function = new BNFSymbol(top_symbol,"cpp_function");
  BNFSymbol  *funct_dcl = new BNFSymbol(top_symbol,"funct_dcl");
  BNFSymbol  *funct_def = new BNFSymbol(top_symbol,"funct_def");
  BNFSymbol  *function_text = new BNFSymbol(top_symbol,"function_text");
  BNFSymbol  *ini_code = new BNFSymbol(top_symbol,"ini_code");
  BNFSymbol  *ini_line = new BNFSymbol(top_symbol,"ini_line");
  BNFSymbol  *function_block = new BNFSymbol(top_symbol,"function_block");
  BNFSymbol  *fct_line = new BNFSymbol(top_symbol,"fct_line");
  BNFSymbol  *window = new BNFSymbol(top_symbol,"window");
  BNFSymbol  *control = new BNFSymbol(top_symbol,"control");
  BNFSymbol  *if_block = new BNFSymbol(top_symbol,"if_block");
  BNFSymbol  *else_stmt = new BNFSymbol(top_symbol,"else_stmt");
  BNFSymbol  *while_block = new BNFSymbol(top_symbol,"while_block");
  BNFSymbol  *for_block = new BNFSymbol(top_symbol,"for_block");
  BNFSymbol  *case_block = new BNFSymbol(top_symbol,"case_block");
  BNFSymbol  *case_stmt = new BNFSymbol(top_symbol,"case_stmt");
  BNFSymbol  *other_stmt = new BNFSymbol(top_symbol,"other_stmt");
  BNFSymbol  *condition = new BNFSymbol(top_symbol,"condition");
  BNFSymbol  *bstatement = new BNFSymbol(top_symbol,"bstatement");
  BNFSymbol  *statement = new BNFSymbol(top_symbol,"statement");
  BNFSymbol  *istatement = new BNFSymbol(top_symbol,"istatement");
  BNFSymbol  *basic_stmt = new BNFSymbol(top_symbol,"basic_stmt");
  BNFSymbol  *stmt_operlist = new BNFSymbol(top_symbol,"stmt_operlist");
  BNFSymbol  *stoplist_ext = new BNFSymbol(top_symbol,"stoplist_ext");
  BNFSymbol  *doperand = new BNFSymbol(top_symbol,"doperand");
  BNFSymbol  *debug_opt = new BNFSymbol(top_symbol,"debug_opt");
  BNFSymbol  *auto_run = new BNFSymbol(top_symbol,"auto_run");
  BNFSymbol  *syntax_op = new BNFSymbol(top_symbol,"syntax_op");
  BNFSymbol  *return_op = new BNFSymbol(top_symbol,"return_op");
  BNFSymbol  *error_op = new BNFSymbol(top_symbol,"error_op");
  BNFSymbol  *eh_op = new BNFSymbol(top_symbol,"eh_op");
  BNFSymbol  *nv_op = new BNFSymbol(top_symbol,"nv_op");
  BNFSymbol  *nv_handling = new BNFSymbol(top_symbol,"nv_handling");
  BNFSymbol  *exception_op = new BNFSymbol(top_symbol,"exception_op");
  BNFSymbol  *leave_op = new BNFSymbol(top_symbol,"leave_op");
  BNFSymbol  *break_op = new BNFSymbol(top_symbol,"break_op");
  BNFSymbol  *continue_op = new BNFSymbol(top_symbol,"continue_op");
  BNFSymbol  *access_path = new BNFSymbol(top_symbol,"access_path");
  BNFSymbol  *path_extension = new BNFSymbol(top_symbol,"path_extension");
  BNFSymbol  *ext_op = new BNFSymbol(top_symbol,"ext_op");
  BNFSymbol  *path_element = new BNFSymbol(top_symbol,"path_element");
  BNFSymbol  *path_operand = new BNFSymbol(top_symbol,"path_operand");
  BNFSymbol  *path_name = new BNFSymbol(top_symbol,"path_name");
  BNFSymbol  *oql_oper = new BNFSymbol(top_symbol,"oql_oper");
  BNFSymbol  *name_index = new BNFSymbol(top_symbol,"name_index");
  BNFSymbol  *coll_operand = new BNFSymbol(top_symbol,"coll_operand");
  BNFSymbol  *operand_list = new BNFSymbol(top_symbol,"operand_list");
  BNFSymbol  *operand = new BNFSymbol(top_symbol,"operand");
  BNFSymbol  *bin_operand = new BNFSymbol(top_symbol,"bin_operand");
  BNFSymbol  *un_operation = new BNFSymbol(top_symbol,"un_operation");
  BNFSymbol  *un_oper = new BNFSymbol(top_symbol,"un_oper");
  BNFSymbol  *cast_op = new BNFSymbol(top_symbol,"cast_op");
  BNFSymbol  *simple_op = new BNFSymbol(top_symbol,"simple_op");
  BNFSymbol  *sngl_operand = new BNFSymbol(top_symbol,"sngl_operand");
  BNFSymbol  *sys_variable = new BNFSymbol(top_symbol,"sys_variable");
  BNFSymbol  *pname = new BNFSymbol(top_symbol,"pname");
  BNFSymbol  *scoped_name = new BNFSymbol(top_symbol,"scoped_name");
  BNFSymbol  *scoped_name_ext = new BNFSymbol(top_symbol,"scoped_name_ext");
  BNFSymbol  *db_name = new BNFSymbol(top_symbol,"db_name");
  BNFSymbol  *identifier = new BNFSymbol(top_symbol,"identifier");
  BNFSymbol  *expr_code = new BNFSymbol(top_symbol,"expr_code");
  BNFSymbol  *block = new BNFSymbol(top_symbol,"block");
  BNFSymbol  *_global = new BNFSymbol(top_symbol,"_global");
  BNFSymbol  *__global = new BNFSymbol(top_symbol,"__global");
  BNFSymbol  *_expression = new BNFSymbol(top_symbol,"_expression");
  BNFSymbol  *_expression_ = new BNFSymbol(top_symbol,"_expression_");
  BNFSymbol  *_window = new BNFSymbol(top_symbol,"_window");
  BNFSymbol  *__window = new BNFSymbol(top_symbol,"__window");
  BNFSymbol  *_control = new BNFSymbol(top_symbol,"_control");
  BNFSymbol  *__control = new BNFSymbol(top_symbol,"__control");
  BNFSymbol  *_variables = new BNFSymbol(top_symbol,"_variables");
  BNFSymbol  *__variables = new BNFSymbol(top_symbol,"__variables");
  BNFSymbol  *_init = new BNFSymbol(top_symbol,"_init");
  BNFSymbol  *__init = new BNFSymbol(top_symbol,"__init");
  BNFSymbol  *_process = new BNFSymbol(top_symbol,"_process");
  BNFSymbol  *__process = new BNFSymbol(top_symbol,"__process");
  BNFSymbol  *_on_error = new BNFSymbol(top_symbol,"_on_error");
  BNFSymbol  *__on_error = new BNFSymbol(top_symbol,"__on_error");
  BNFSymbol  *_final = new BNFSymbol(top_symbol,"_final");
  BNFSymbol  *__final = new BNFSymbol(top_symbol,"__final");
  BNFSymbol  *_if = new BNFSymbol(top_symbol,"_if");
  BNFSymbol  *_else = new BNFSymbol(top_symbol,"_else");
  BNFSymbol  *_while = new BNFSymbol(top_symbol,"_while");
  BNFSymbol  *_for = new BNFSymbol(top_symbol,"_for");
  BNFSymbol  *_continue = new BNFSymbol(top_symbol,"_continue");
  BNFSymbol  *_leave_ = new BNFSymbol(top_symbol,"_leave_");
  BNFSymbol  *_break = new BNFSymbol(top_symbol,"_break");
  BNFSymbol  *_error = new BNFSymbol(top_symbol,"_error");
  BNFSymbol  *_return = new BNFSymbol(top_symbol,"_return");
  BNFSymbol  *_null_value = new BNFSymbol(top_symbol,"_null_value");
  BNFSymbol  *_exceptions = new BNFSymbol(top_symbol,"_exceptions");
  BNFSymbol  *_ignore = new BNFSymbol(top_symbol,"_ignore");
  BNFSymbol  *__ignore = new BNFSymbol(top_symbol,"__ignore");
  BNFSymbol  *_accept = new BNFSymbol(top_symbol,"_accept");
  BNFSymbol  *__accept = new BNFSymbol(top_symbol,"__accept");
  BNFSymbol  *scope_op = new BNFSymbol(top_symbol,"scope_op");
  BNFSymbol  *cun_op = new BNFSymbol(top_symbol,"cun_op");
  BNFSymbol  *un_op = new BNFSymbol(top_symbol,"un_op");
  BNFSymbol  *bin_op = new BNFSymbol(top_symbol,"bin_op");
  BNFSymbol  *assign_op = new BNFSymbol(top_symbol,"assign_op");
  BNFSymbol  *bin_assign_op = new BNFSymbol(top_symbol,"bin_assign_op");
  BNFSymbol  *_not = new BNFSymbol(top_symbol,"_not");
  BNFSymbol  *_and = new BNFSymbol(top_symbol,"_and");
  BNFSymbol  *_or = new BNFSymbol(top_symbol,"_or");
  BNFSymbol  *_not_kw = new BNFSymbol(top_symbol,"_not_kw");
  BNFSymbol  *_and_kw = new BNFSymbol(top_symbol,"_and_kw");
  BNFSymbol  *_or_kw = new BNFSymbol(top_symbol,"_or_kw");
  BNFSymbol  *_xor = new BNFSymbol(top_symbol,"_xor");
  BNFSymbol  *comment_block = new BNFSymbol(top_symbol,"comment_block");
  BNFSymbol  *comment_next = new BNFSymbol(top_symbol,"comment_next");
  BNFSymbol  *comment_cont = new BNFSymbol(top_symbol,"comment_cont");
  BNFSymbol  *comment_end = new BNFSymbol(top_symbol,"comment_end");

// OSI
  __expression = new BNFExpression(OSI);
    __expression->AddElement(data_source,YES,1,YES,YES);
    __expression->AddElement(debug_info,YES,1,YES,YES);
    __expression->AddElement(osi_element,NO,UNDEF,YES,YES);

// debug_info
  __expression = new BNFExpression(debug_info);
    __expression->AddElement(_debugprocs,NO,1,NO,YES);
    __expression->AddElement(ElementaryToken('='),NO,1,NO,YES);
    __expression->AddElement(location,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// osi_element
  __expression = new BNFExpression(osi_element);
    __expression->AddElement(block_intro,YES,UNDEF,YES,YES);
    __expression->AddElement(osi_definition,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),YES,1,NO,YES);

// osi_definition
  __expression = new BNFExpression(osi_definition);
    __expression->AddElement(type_dcl,NO,1,YES,YES);
  __expression = new BNFExpression(osi_definition);
    __expression->AddElement(view_dcl,NO,1,YES,YES);
  __expression = new BNFExpression(osi_definition);
    __expression->AddElement(osi_class,NO,1,YES,YES);
  __expression = new BNFExpression(osi_definition);
    __expression->AddElement(expr_def,NO,1,YES,YES);

// osi_class
  __expression = new BNFExpression(osi_class);
    __expression->AddElement(class_header,NO,1,YES,YES);
    __expression->AddElement(osi_class_def,YES,1,YES,YES);

// osi_class_def
  __expression = new BNFExpression(osi_class_def);
    __expression->AddElement(ElementaryToken('{'),NO,1,NO,YES);
    __expression->AddElement(osi_exports,NO,UNDEF,YES,YES);
    __expression->AddElement(ElementaryToken('}'),NO,1,NO,YES);

// osi_exports
  __expression = new BNFExpression(osi_exports);
    __expression->AddElement(comment_block,YES,UNDEF,YES,YES);
    __expression->AddElement(osi_export_dcl,NO,1,YES,YES);

// osi_export_dcl
  __expression = new BNFExpression(osi_export_dcl);
    __expression->AddElement(attr_dcl,NO,1,YES,YES);
  __expression = new BNFExpression(osi_export_dcl);
    __expression->AddElement(ref_dcl,NO,1,YES,YES);
  __expression = new BNFExpression(osi_export_dcl);
    __expression->AddElement(rel_dcl,NO,1,YES,YES);
  __expression = new BNFExpression(osi_export_dcl);
    __expression->AddElement(expr_def,NO,1,YES,YES);

// _debugprocs
  __expression = new BNFExpression(_debugprocs);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('b'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('g'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('P'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,YES);
  __expression = new BNFExpression(_debugprocs);
    __expression->AddElement(__debugprocs,NO,1,NO,YES);

// __debugprocs
  __expression = new BNFExpression(__debugprocs);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('B'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('G'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('P'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,YES);
  __debugprocs->SetKeyword();

// ODL
  __expression = new BNFExpression(ODL);
    __expression->AddElement(data_source,YES,1,YES,YES);
    __expression->AddElement(sc_element,NO,UNDEF,YES,YES);

// data_source
  __expression = new BNFExpression(data_source);
    __expression->AddElement(dictionary,NO,1,YES,YES);
  __expression = new BNFExpression(data_source);
    __expression->AddElement(datasource,NO,1,YES,YES);

// datasource
  __expression = new BNFExpression(datasource);
    __expression->AddElement(comment_block,YES,UNDEF,YES,YES);
    __expression->AddElement(_datasource,NO,1,NO,YES);
    __expression->AddElement(ElementaryToken('='),NO,1,NO,YES);
    __expression->AddElement(location,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// dictionary
  __expression = new BNFExpression(dictionary);
    __expression->AddElement(comment_block,YES,UNDEF,YES,YES);
    __expression->AddElement(_dictionary,NO,1,NO,YES);
    __expression->AddElement(ElementaryToken('='),NO,1,NO,YES);
    __expression->AddElement(location,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);
    __expression->AddElement(database,YES,1,YES,YES);

// database
  __expression = new BNFExpression(database);
    __expression->AddElement(comment_block,YES,UNDEF,YES,YES);
    __expression->AddElement(_database,NO,1,NO,YES);
    __expression->AddElement(ElementaryToken('='),NO,1,NO,YES);
    __expression->AddElement(location,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// location
  __expression = new BNFExpression(location);
    __expression->AddElement(string,NO,1,YES,YES);
  __expression = new BNFExpression(location);
    __expression->AddElement(identifier,NO,1,YES,YES);

// sc_element
  __expression = new BNFExpression(sc_element);
    __expression->AddElement(block_intro,YES,UNDEF,YES,YES);
    __expression->AddElement(update_option,YES,1,YES,YES);
    __expression->AddElement(sc_definition,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// sc_definition
  __expression = new BNFExpression(sc_definition);
    __expression->AddElement(mod_definition,NO,1,YES,YES);
  __expression = new BNFExpression(sc_definition);
    __expression->AddElement(schema_dcl,NO,1,YES,YES);

// schema_dcl
  __expression = new BNFExpression(schema_dcl);
    __expression->AddElement(schema,NO,1,YES,YES);
    __expression->AddElement(identifier,YES,1,YES,YES);
    __expression->AddElement(ElementaryToken('{'),NO,1,NO,YES);
    __expression->AddElement(sc_element,NO,UNDEF,YES,YES);
    __expression->AddElement(ElementaryToken('}'),NO,1,NO,YES);

// mod_definition
  __expression = new BNFExpression(mod_definition);
    __expression->AddElement(type_dcl,NO,1,YES,YES);
  __expression = new BNFExpression(mod_definition);
    __expression->AddElement(view_dcl,NO,1,YES,YES);
  __expression = new BNFExpression(mod_definition);
    __expression->AddElement(interface_dcl,NO,1,YES,YES);
  __expression = new BNFExpression(mod_definition);
    __expression->AddElement(class_dcl,NO,1,YES,YES);
  __expression = new BNFExpression(mod_definition);
    __expression->AddElement(const_dcl,NO,1,YES,YES);
  __expression = new BNFExpression(mod_definition);
    __expression->AddElement(module_dcl,NO,1,YES,YES);

// module_dcl
  __expression = new BNFExpression(module_dcl);
    __expression->AddElement(_module,NO,1,NO,YES);
    __expression->AddElement(identifier,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken('{'),NO,1,NO,YES);
    __expression->AddElement(mod_element,NO,UNDEF,YES,YES);
    __expression->AddElement(ElementaryToken('}'),NO,1,NO,YES);

// mod_element
  __expression = new BNFExpression(mod_element);
    __expression->AddElement(block_intro,YES,UNDEF,YES,YES);
    __expression->AddElement(update_option,YES,1,YES,YES);
    __expression->AddElement(mod_definition,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// type_dcl
  __expression = new BNFExpression(type_dcl);
    __expression->AddElement(namespace_dcl,NO,1,YES,YES);
  __expression = new BNFExpression(type_dcl);
    __expression->AddElement(type_def,NO,1,YES,YES);
  __expression = new BNFExpression(type_dcl);
    __expression->AddElement(struct_type,NO,1,YES,YES);
  __expression = new BNFExpression(type_dcl);
    __expression->AddElement(union_type,NO,1,YES,YES);
  __expression = new BNFExpression(type_dcl);
    __expression->AddElement(enum_type,NO,1,YES,YES);

// type_def
  __expression = new BNFExpression(type_def);
    __expression->AddElement(_typedef,NO,1,NO,YES);
    __expression->AddElement(type_spec,NO,1,YES,YES);
    __expression->AddElement(declarators,YES,1,YES,YES);

// namespace_dcl
  __expression = new BNFExpression(namespace_dcl);
    __expression->AddElement(_namespace,NO,1,NO,YES);
    __expression->AddElement(identifier,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken('{'),NO,1,NO,YES);
    __expression->AddElement(ns_element,NO,UNDEF,YES,YES);
    __expression->AddElement(ElementaryToken('}'),NO,1,NO,YES);

// ns_element
  __expression = new BNFExpression(ns_element);
    __expression->AddElement(block_intro,YES,UNDEF,YES,YES);
    __expression->AddElement(update_option,YES,1,YES,YES);
    __expression->AddElement(type_dcl,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// update_option
  __expression = new BNFExpression(update_option);
    __expression->AddElement(_new,NO,1,NO,YES);
  __expression = new BNFExpression(update_option);
    __expression->AddElement(update,NO,1,YES,YES);

// struct_type
  __expression = new BNFExpression(struct_type);
    __expression->AddElement(_struct,NO,1,NO,YES);
    __expression->AddElement(identifier,NO,1,YES,YES);
    __expression->AddElement(struct_def,YES,1,YES,YES);

// struct_def
  __expression = new BNFExpression(struct_def);
    __expression->AddElement(ElementaryToken('{'),NO,1,NO,YES);
    __expression->AddElement(member,NO,UNDEF,YES,YES);
    __expression->AddElement(ElementaryToken('}'),NO,1,NO,YES);

// union_type
  __expression = new BNFExpression(union_type);
    __expression->AddElement(_union,NO,1,NO,YES);
    __expression->AddElement(identifier,NO,1,YES,YES);
    __expression->AddElement(_switch,NO,1,NO,YES);
    __expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    __expression->AddElement(switch_type_spec,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);
    __expression->AddElement(ElementaryToken('{'),NO,1,NO,YES);
    __expression->AddElement(case_def,NO,UNDEF,YES,YES);
    __expression->AddElement(ElementaryToken('}'),NO,1,NO,YES);

// switch_type_spec
  __expression = new BNFExpression(switch_type_spec);
    __expression->AddElement(base_int,NO,1,YES,YES);
  __expression = new BNFExpression(switch_type_spec);
    __expression->AddElement(char_types,NO,1,YES,YES);
  __expression = new BNFExpression(switch_type_spec);
    __expression->AddElement(boolean_type,NO,1,YES,YES);
  __expression = new BNFExpression(switch_type_spec);
    __expression->AddElement(enum_type,NO,1,YES,YES);
  __expression = new BNFExpression(switch_type_spec);
    __expression->AddElement(scoped_name,NO,1,YES,YES);

// case_def
  __expression = new BNFExpression(case_def);
    __expression->AddElement(case_label,NO,UNDEF,YES,YES);
    __expression->AddElement(element_spec,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// case_label
  __expression = new BNFExpression(case_label);
    __expression->AddElement(case_inst,NO,1,YES,YES);
  __expression = new BNFExpression(case_label);
    __expression->AddElement(default_def,NO,1,YES,YES);

// case_inst
  __expression = new BNFExpression(case_inst);
    __expression->AddElement(_case,NO,1,NO,YES);
    __expression->AddElement(operand,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(':'),NO,1,NO,YES);

// default_def
  __expression = new BNFExpression(default_def);
    __expression->AddElement(_default,NO,1,NO,YES);
    __expression->AddElement(ElementaryToken(':'),NO,1,NO,YES);

// element_spec
  __expression = new BNFExpression(element_spec);
    __expression->AddElement(type_spec,NO,1,YES,YES);
    __expression->AddElement(declarator,NO,1,YES,YES);

// enum_type
  __expression = new BNFExpression(enum_type);
    __expression->AddElement(_enum,NO,1,NO,YES);
    __expression->AddElement(identifier,NO,1,YES,YES);
    __expression->AddElement(base_class,YES,1,YES,YES);
    __expression->AddElement(enum_def,YES,1,YES,YES);

// base_class
  __expression = new BNFExpression(base_class);
    __expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    __expression->AddElement(scoped_name,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);

// enum_def
  __expression = new BNFExpression(enum_def);
    __expression->AddElement(ElementaryToken('{'),NO,1,NO,YES);
    __expression->AddElement(enumerator,NO,UNDEF,YES,YES);
    __expression->AddElement(ElementaryToken('}'),NO,1,NO,YES);

// enumerator
  __expression = new BNFExpression(enumerator);
    __expression->AddElement(identifier,NO,1,YES,YES);
    __expression->AddElement(ref_type,YES,1,YES,YES);
    __expression->AddElement(enum_value,YES,1,YES,YES);
    __expression->AddElement(enum_def,YES,1,YES,YES);
    __expression->AddElement(ElementaryToken(','),YES,1,NO,YES);

// ref_type
  __expression = new BNFExpression(ref_type);
    __expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    __expression->AddElement(scoped_name,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);

// enum_value
  __expression = new BNFExpression(enum_value);
    __expression->AddElement(assign_op,NO,1,YES,YES);
    __expression->AddElement(number,NO,1,YES,YES);

// const_dcl
  __expression = new BNFExpression(const_dcl);
    __expression->AddElement(_const,NO,1,NO,YES);
    __expression->AddElement(const_type,NO,1,YES,YES);
    __expression->AddElement(identifier,NO,1,YES,YES);
    __expression->AddElement(assigned_value,NO,1,YES,YES);

// const_type
  __expression = new BNFExpression(const_type);
    __expression->AddElement(base_int,NO,1,YES,YES);
  __expression = new BNFExpression(const_type);
    __expression->AddElement(char_types,NO,1,YES,YES);
  __expression = new BNFExpression(const_type);
    __expression->AddElement(boolean_type,NO,1,YES,YES);
  __expression = new BNFExpression(const_type);
    __expression->AddElement(string_type,NO,1,YES,YES);
  __expression = new BNFExpression(const_type);
    __expression->AddElement(scoped_name,NO,1,YES,YES);

// except_dcl
  __expression = new BNFExpression(except_dcl);
    __expression->AddElement(_exception,NO,1,NO,YES);
    __expression->AddElement(exceptions_def,NO,1,YES,YES);

// exceptions_def
  __expression = new BNFExpression(exceptions_def);
    __expression->AddElement(exception_def,NO,1,YES,YES);
  __expression = new BNFExpression(exceptions_def);
    __expression->AddElement(exception_specs,NO,1,YES,YES);

// exception_specs
  __expression = new BNFExpression(exception_specs);
    __expression->AddElement(ElementaryToken('{'),NO,1,NO,YES);
    __expression->AddElement(sexception_spec,NO,UNDEF,YES,YES);
    __expression->AddElement(ElementaryToken('}'),NO,1,NO,YES);

// sexception_spec
  __expression = new BNFExpression(sexception_spec);
    __expression->AddElement(exception_def,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// exception_def
  __expression = new BNFExpression(exception_def);
    __expression->AddElement(identifier,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken('{'),NO,1,NO,YES);
    __expression->AddElement(member,YES,UNDEF,YES,YES);
    __expression->AddElement(ElementaryToken('}'),NO,1,NO,YES);

// class_dcl
  __expression = new BNFExpression(class_dcl);
    __expression->AddElement(class_header,NO,1,YES,YES);
    __expression->AddElement(class_def,YES,1,YES,YES);

// class_def
  __expression = new BNFExpression(class_def);
    __expression->AddElement(ElementaryToken('{'),NO,1,NO,YES);
    __expression->AddElement(exports,NO,UNDEF,YES,YES);
    __expression->AddElement(ElementaryToken('}'),NO,1,NO,YES);

// class_header
  __expression = new BNFExpression(class_header);
    __expression->AddElement(_class,NO,1,NO,YES);
    __expression->AddElement(identifier,NO,1,YES,YES);
    __expression->AddElement(guid,YES,1,YES,YES);
    __expression->AddElement(extends_spec,YES,1,YES,YES);
    __expression->AddElement(inheritance_spec,YES,1,YES,YES);
    __expression->AddElement(type_property_list,YES,1,YES,YES);

// type_property_list
  __expression = new BNFExpression(type_property_list);
    __expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    __expression->AddElement(type_property,NO,UNDEF,YES,YES);
    __expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);

// type_property
  __expression = new BNFExpression(type_property);
    __expression->AddElement(key_spec,NO,1,YES,YES);
  __expression = new BNFExpression(type_property);
    __expression->AddElement(extent_spec,NO,1,YES,YES);
  __expression = new BNFExpression(type_property);
    __expression->AddElement(alignment_spec,NO,1,YES,YES);

// alignment_spec
  __expression = new BNFExpression(alignment_spec);
    __expression->AddElement(_alignment,NO,1,NO,YES);
    __expression->AddElement(ElementaryToken('='),NO,1,NO,YES);
    __expression->AddElement(number,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// interface_dcl
  __expression = new BNFExpression(interface_dcl);
    __expression->AddElement(interface_header,NO,1,YES,YES);
    __expression->AddElement(interface_spec,YES,1,YES,YES);

// interface_spec
  __expression = new BNFExpression(interface_spec);
    __expression->AddElement(ElementaryToken('{'),NO,1,NO,YES);
    __expression->AddElement(exports,YES,UNDEF,YES,YES);
    __expression->AddElement(ElementaryToken('}'),NO,1,NO,YES);

// interface_header
  __expression = new BNFExpression(interface_header);
    __expression->AddElement(_interface,NO,1,NO,YES);
    __expression->AddElement(identifier,NO,1,YES,YES);
    __expression->AddElement(inheritance_spec,YES,1,YES,YES);

// exports
  __expression = new BNFExpression(exports);
    __expression->AddElement(comment_block,YES,UNDEF,YES,YES);
    __expression->AddElement(export_dcl,NO,1,YES,YES);

// export_dcl
  __expression = new BNFExpression(export_dcl);
    __expression->AddElement(type_dcl,NO,1,YES,YES);
  __expression = new BNFExpression(export_dcl);
    __expression->AddElement(const_dcl,NO,1,YES,YES);
  __expression = new BNFExpression(export_dcl);
    __expression->AddElement(attr_dcl,NO,1,YES,YES);
  __expression = new BNFExpression(export_dcl);
    __expression->AddElement(ref_dcl,NO,1,YES,YES);
  __expression = new BNFExpression(export_dcl);
    __expression->AddElement(rel_dcl,NO,1,YES,YES);
  __expression = new BNFExpression(export_dcl);
    __expression->AddElement(except_dcl,NO,1,YES,YES);
  __expression = new BNFExpression(export_dcl);
    __expression->AddElement(method,NO,1,YES,YES);

// view_dcl
  __expression = new BNFExpression(view_dcl);
    __expression->AddElement(view_header,NO,1,YES,YES);
    __expression->AddElement(view_def,YES,1,YES,YES);

// view_def
  __expression = new BNFExpression(view_def);
    __expression->AddElement(ElementaryToken('{'),NO,1,NO,YES);
    __expression->AddElement(view_member,NO,UNDEF,YES,YES);
    __expression->AddElement(ElementaryToken('}'),NO,1,NO,YES);

// view_member
  __expression = new BNFExpression(view_member);
    __expression->AddElement(attr_dcl,NO,1,YES,YES);
  __expression = new BNFExpression(view_member);
    __expression->AddElement(ref_dcl,NO,1,YES,YES);
  __expression = new BNFExpression(view_member);
    __expression->AddElement(method,NO,1,YES,YES);

// view_header
  __expression = new BNFExpression(view_header);
    __expression->AddElement(_view,NO,1,NO,YES);
    __expression->AddElement(identifier,NO,1,YES,YES);
    __expression->AddElement(from_spec,NO,1,YES,YES);
    __expression->AddElement(where_spec,YES,1,YES,YES);
    __expression->AddElement(group_spec,YES,1,YES,YES);
    __expression->AddElement(having_spec,YES,1,YES,YES);
    __expression->AddElement(type_property_list,YES,1,YES,YES);

// from_spec
  __expression = new BNFExpression(from_spec);
    __expression->AddElement(_from,NO,1,NO,YES);
    __expression->AddElement(operand_list,NO,1,YES,YES);

// where_spec
  __expression = new BNFExpression(where_spec);
    __expression->AddElement(_where,NO,1,NO,YES);
    __expression->AddElement(condition,NO,1,YES,YES);

// having_spec
  __expression = new BNFExpression(having_spec);
    __expression->AddElement(_having,NO,1,NO,YES);
    __expression->AddElement(condition,NO,1,YES,YES);

// order_spec
  __expression = new BNFExpression(order_spec);
    __expression->AddElement(_order_by,NO,1,NO,YES);
    __expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    __expression->AddElement(scoped_names,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);

// group_spec
  __expression = new BNFExpression(group_spec);
    __expression->AddElement(_group_by,NO,1,NO,YES);
    __expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    __expression->AddElement(categories,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);

// inheritance_spec
  __expression = new BNFExpression(inheritance_spec);
    __expression->AddElement(ElementaryToken(':'),NO,1,NO,YES);
    __expression->AddElement(base_types,NO,1,YES,YES);

// extends_spec
  __expression = new BNFExpression(extends_spec);
    __expression->AddElement(extends,NO,1,YES,YES);
    __expression->AddElement(base_types,NO,1,YES,YES);

// base_types
  __expression = new BNFExpression(base_types);
    __expression->AddElement(base_type,NO,1,YES,YES);
    __expression->AddElement(base_type_suc,YES,UNDEF,YES,YES);

// base_type_suc
  __expression = new BNFExpression(base_type_suc);
    __expression->AddElement(ElementaryToken(','),NO,1,NO,YES);
    __expression->AddElement(base_type,NO,1,YES,YES);

// base_type
  __expression = new BNFExpression(base_type);
    __expression->AddElement(base_option,YES,UNDEF,YES,YES);
    __expression->AddElement(extended_type_spec,NO,1,YES,YES);
    __expression->AddElement(rel_option,YES,UNDEF,YES,YES);
    __expression->AddElement(base_declarator,YES,1,YES,YES);

// base_option
  __expression = new BNFExpression(base_option);
    __expression->AddElement(_virtual,NO,1,NO,YES);
  __expression = new BNFExpression(base_option);
    __expression->AddElement(priv_option,NO,1,YES,YES);

// base_declarator
  __expression = new BNFExpression(base_declarator);
    __expression->AddElement(identifier,NO,1,YES,YES);
    __expression->AddElement(col_ext_rel,YES,UNDEF,YES,YES);

// extent_spec
  __expression = new BNFExpression(extent_spec);
    __expression->AddElement(extent,NO,1,YES,YES);
    __expression->AddElement(extents_def,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// extents_def
  __expression = new BNFExpression(extents_def);
    __expression->AddElement(extent_def,NO,1,YES,YES);
  __expression = new BNFExpression(extents_def);
    __expression->AddElement(extent_specs,NO,1,YES,YES);

// extent_specs
  __expression = new BNFExpression(extent_specs);
    __expression->AddElement(ElementaryToken('{'),NO,1,NO,YES);
    __expression->AddElement(sextent_spec,NO,UNDEF,YES,YES);
    __expression->AddElement(ElementaryToken('}'),NO,1,NO,YES);

// sextent_spec
  __expression = new BNFExpression(sextent_spec);
    __expression->AddElement(extent_def,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// extent_def
  __expression = new BNFExpression(extent_def);
    __expression->AddElement(_transient,YES,1,NO,YES);
    __expression->AddElement(identifier,NO,1,YES,YES);
    __expression->AddElement(rel_option,YES,UNDEF,YES,YES);
    __expression->AddElement(extent_option,YES,UNDEF,YES,YES);

// extent_option
  __expression = new BNFExpression(extent_option);
    __expression->AddElement(order_keys,NO,1,YES,YES);
  __expression = new BNFExpression(extent_option);
    __expression->AddElement(super_sets,NO,1,YES,YES);
  __expression = new BNFExpression(extent_option);
    __expression->AddElement(sub_sets,NO,1,YES,YES);

// sub_sets
  __expression = new BNFExpression(sub_sets);
    __expression->AddElement(subset,NO,1,YES,YES);
    __expression->AddElement(subset_options,YES,UNDEF,YES,YES);
    __expression->AddElement(extent_names,NO,1,YES,YES);

// subset_options
  __expression = new BNFExpression(subset_options);
    __expression->AddElement(distinct,NO,1,YES,YES);
  __expression = new BNFExpression(subset_options);
    __expression->AddElement(complete,NO,1,YES,YES);

// super_sets
  __expression = new BNFExpression(super_sets);
    __expression->AddElement(superset,NO,1,YES,YES);
    __expression->AddElement(intersect,YES,1,YES,YES);
    __expression->AddElement(extent_names,NO,1,YES,YES);

// extent_names
  __expression = new BNFExpression(extent_names);
    __expression->AddElement(extent_name,NO,1,YES,YES);
    __expression->AddElement(extent_names_suc,YES,UNDEF,YES,YES);

// extent_names_suc
  __expression = new BNFExpression(extent_names_suc);
    __expression->AddElement(ElementaryToken(','),NO,1,NO,YES);
    __expression->AddElement(extent_name,NO,1,YES,YES);

// key_spec
  __expression = new BNFExpression(key_spec);
    __expression->AddElement(key,NO,1,YES,YES);
    __expression->AddElement(keys_def,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// keys_def
  __expression = new BNFExpression(keys_def);
    __expression->AddElement(key_def,NO,1,YES,YES);
  __expression = new BNFExpression(keys_def);
    __expression->AddElement(key_specs,NO,1,YES,YES);

// key_specs
  __expression = new BNFExpression(key_specs);
    __expression->AddElement(ElementaryToken('{'),NO,1,NO,YES);
    __expression->AddElement(skey_spec,NO,UNDEF,YES,YES);
    __expression->AddElement(ElementaryToken('}'),NO,1,NO,YES);

// skey_spec
  __expression = new BNFExpression(skey_spec);
    __expression->AddElement(key_def,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// key_def
  __expression = new BNFExpression(key_def);
    __expression->AddElement(ident_key,YES,1,YES,YES);
    __expression->AddElement(identifier,NO,1,YES,YES);
    __expression->AddElement(key_components_ext,YES,1,YES,YES);

// key_components_ext
  __expression = new BNFExpression(key_components_ext);
    __expression->AddElement(key_components,NO,1,YES,YES);
  __expression = new BNFExpression(key_components_ext);
    __expression->AddElement(key_components_odmg,NO,1,YES,YES);

// key_components_odmg
  __expression = new BNFExpression(key_components_odmg);
    __expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    __expression->AddElement(key_components,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);

// key_components
  __expression = new BNFExpression(key_components);
    __expression->AddElement(key_component,NO,1,YES,YES);
    __expression->AddElement(key_component_suc,YES,UNDEF,YES,YES);

// key_component_suc
  __expression = new BNFExpression(key_component_suc);
    __expression->AddElement(ElementaryToken(','),NO,1,NO,YES);
    __expression->AddElement(key_component,NO,1,YES,YES);

// key_component
  __expression = new BNFExpression(key_component);
    __expression->AddElement(member_path,NO,1,YES,YES);
    __expression->AddElement(component_option,YES,UNDEF,YES,YES);

// component_option
  __expression = new BNFExpression(component_option);
    __expression->AddElement(ignore_case,NO,1,YES,YES);
  __expression = new BNFExpression(component_option);
    __expression->AddElement(descending,NO,1,YES,YES);

// attr_dcl
  __expression = new BNFExpression(attr_dcl);
    __expression->AddElement(attribute,NO,1,YES,YES);
    __expression->AddElement(attr_def,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// attr_def
  __expression = new BNFExpression(attr_def);
    __expression->AddElement(attr_spec,NO,1,YES,YES);
  __expression = new BNFExpression(attr_def);
    __expression->AddElement(attr_specs,NO,1,YES,YES);

// attr_specs
  __expression = new BNFExpression(attr_specs);
    __expression->AddElement(ElementaryToken('{'),NO,1,NO,YES);
    __expression->AddElement(sattr_spec,NO,UNDEF,YES,YES);
    __expression->AddElement(ElementaryToken('}'),NO,1,NO,YES);

// sattr_spec
  __expression = new BNFExpression(sattr_spec);
    __expression->AddElement(attr_spec,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// attr_spec
  __expression = new BNFExpression(attr_spec);
    __expression->AddElement(type_ref,NO,1,YES,YES);
    __expression->AddElement(declarators,NO,1,YES,YES);

// ref_dcl
  __expression = new BNFExpression(ref_dcl);
    __expression->AddElement(reference,NO,1,YES,YES);
    __expression->AddElement(refs_def,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// refs_def
  __expression = new BNFExpression(refs_def);
    __expression->AddElement(ref_def,NO,1,YES,YES);
  __expression = new BNFExpression(refs_def);
    __expression->AddElement(ref_specs,NO,1,YES,YES);

// ref_specs
  __expression = new BNFExpression(ref_specs);
    __expression->AddElement(ElementaryToken('{'),NO,1,NO,YES);
    __expression->AddElement(sref_spec,NO,UNDEF,YES,YES);
    __expression->AddElement(ElementaryToken('}'),NO,1,NO,YES);

// sref_spec
  __expression = new BNFExpression(sref_spec);
    __expression->AddElement(ref_def,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// ref_def
  __expression = new BNFExpression(ref_def);
    __expression->AddElement(type_ref,NO,1,YES,YES);
    __expression->AddElement(ref_option,YES,UNDEF,YES,YES);
    __expression->AddElement(references,NO,1,YES,YES);

// ref_option
  __expression = new BNFExpression(ref_option);
    __expression->AddElement(guid,NO,1,YES,YES);
  __expression = new BNFExpression(ref_option);
    __expression->AddElement(weak_typed,NO,1,YES,YES);
  __expression = new BNFExpression(ref_option);
    __expression->AddElement(update,NO,1,YES,YES);
  __expression = new BNFExpression(ref_option);
    __expression->AddElement(multiple_key,NO,1,YES,YES);
  __expression = new BNFExpression(ref_option);
    __expression->AddElement(delete_empty,NO,1,YES,YES);

// references
  __expression = new BNFExpression(references);
    __expression->AddElement(ref_declarator,NO,1,YES,YES);
    __expression->AddElement(references_suc,YES,UNDEF,YES,YES);

// references_suc
  __expression = new BNFExpression(references_suc);
    __expression->AddElement(ElementaryToken(','),NO,1,NO,YES);
    __expression->AddElement(ref_declarator,NO,1,YES,YES);

// ref_declarator
  __expression = new BNFExpression(ref_declarator);
    __expression->AddElement(collection,NO,1,YES,YES);
    __expression->AddElement(col_ext_ref,YES,UNDEF,YES,YES);

// rel_dcl
  __expression = new BNFExpression(rel_dcl);
    __expression->AddElement(relationship,NO,1,YES,YES);
    __expression->AddElement(rels_def,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// rels_def
  __expression = new BNFExpression(rels_def);
    __expression->AddElement(rel_def,NO,1,YES,YES);
  __expression = new BNFExpression(rels_def);
    __expression->AddElement(rel_specs,NO,1,YES,YES);

// rel_specs
  __expression = new BNFExpression(rel_specs);
    __expression->AddElement(ElementaryToken('{'),NO,1,NO,YES);
    __expression->AddElement(srel_spec,NO,UNDEF,YES,YES);
    __expression->AddElement(ElementaryToken('}'),NO,1,NO,YES);

// srel_spec
  __expression = new BNFExpression(srel_spec);
    __expression->AddElement(rel_def,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// rel_def
  __expression = new BNFExpression(rel_def);
    __expression->AddElement(type_ref,NO,1,YES,YES);
    __expression->AddElement(rel_option,YES,UNDEF,YES,YES);
    __expression->AddElement(relationships,NO,1,YES,YES);

// rel_option
  __expression = new BNFExpression(rel_option);
    __expression->AddElement(ref_option,NO,1,YES,YES);
  __expression = new BNFExpression(rel_option);
    __expression->AddElement(owner,NO,1,YES,YES);
  __expression = new BNFExpression(rel_option);
    __expression->AddElement(no_create,NO,1,YES,YES);
  __expression = new BNFExpression(rel_option);
    __expression->AddElement(dependent,NO,1,YES,YES);
  __expression = new BNFExpression(rel_option);
    __expression->AddElement(secondary,NO,1,YES,YES);
  __expression = new BNFExpression(rel_option);
    __expression->AddElement(shared,NO,1,YES,YES);

// relationships
  __expression = new BNFExpression(relationships);
    __expression->AddElement(rel_declarator,NO,1,YES,YES);
    __expression->AddElement(relationships_suc,YES,UNDEF,YES,YES);

// relationships_suc
  __expression = new BNFExpression(relationships_suc);
    __expression->AddElement(ElementaryToken(','),NO,1,NO,YES);
    __expression->AddElement(rel_declarator,NO,1,YES,YES);

// rel_declarator
  __expression = new BNFExpression(rel_declarator);
    __expression->AddElement(collection,NO,1,YES,YES);
    __expression->AddElement(col_ext_rel,YES,UNDEF,YES,YES);

// collection
  __expression = new BNFExpression(collection);
    __expression->AddElement(identifier,NO,1,YES,YES);
    __expression->AddElement(col_dimension,YES,1,YES,YES);
    __expression->AddElement(assigned_value,YES,1,YES,YES);

// col_dimension
  __expression = new BNFExpression(col_dimension);
    __expression->AddElement(ElementaryToken('['),NO,1,NO,YES);
    __expression->AddElement(number,YES,1,YES,YES);
    __expression->AddElement(ElementaryToken(']'),NO,1,NO,YES);

// col_ext_rel
  __expression = new BNFExpression(col_ext_rel);
    __expression->AddElement(inverse_spec,NO,1,YES,YES);
  __expression = new BNFExpression(col_ext_rel);
    __expression->AddElement(base_collection,NO,1,YES,YES);
  __expression = new BNFExpression(col_ext_rel);
    __expression->AddElement(col_ext_ref,NO,1,YES,YES);

// inverse_spec
  __expression = new BNFExpression(inverse_spec);
    __expression->AddElement(inverse,NO,1,YES,YES);
    __expression->AddElement(inverse_traversal_path,NO,1,YES,YES);

// inverse_traversal_path
  __expression = new BNFExpression(inverse_traversal_path);
    __expression->AddElement(identifier,NO,1,YES,YES);
    __expression->AddElement(typed_identifier,YES,1,YES,YES);

// typed_identifier
  __expression = new BNFExpression(typed_identifier);
    __expression->AddElement(scope_op,NO,1,YES,YES);
    __expression->AddElement(identifier,NO,1,YES,YES);

// base_collection
  __expression = new BNFExpression(base_collection);
    __expression->AddElement(based_on,NO,1,YES,YES);
    __expression->AddElement(base_path,NO,1,YES,YES);

// base_path
  __expression = new BNFExpression(base_path);
    __expression->AddElement(member_path,NO,1,YES,YES);
  __expression = new BNFExpression(base_path);
    __expression->AddElement(ElementaryToken('*'),NO,1,NO,YES);

// member_path
  __expression = new BNFExpression(member_path);
    __expression->AddElement(extent_name,NO,1,YES,YES);
  __expression = new BNFExpression(member_path);
    __expression->AddElement(property_extension,NO,UNDEF,YES,YES);

// extent_name
  __expression = new BNFExpression(extent_name);
    __expression->AddElement(identifier,NO,1,YES,YES);
  __expression = new BNFExpression(extent_name);
    __expression->AddElement(any_type,NO,1,YES,YES);

// property_extension
  __expression = new BNFExpression(property_extension);
    __expression->AddElement(ElementaryToken('.'),NO,1,NO,YES);
    __expression->AddElement(identifier,NO,1,YES,YES);

// col_ext_ref
  __expression = new BNFExpression(col_ext_ref);
    __expression->AddElement(order_keys,NO,1,YES,YES);
  __expression = new BNFExpression(col_ext_ref);
    __expression->AddElement(attr_ext_decl,NO,1,YES,YES);

// attr_ext_decl
  __expression = new BNFExpression(attr_ext_decl);
    __expression->AddElement(sources,NO,1,YES,YES);
  __expression = new BNFExpression(attr_ext_decl);
    __expression->AddElement(constraint,NO,1,YES,YES);
  __expression = new BNFExpression(attr_ext_decl);
    __expression->AddElement(version,NO,1,YES,YES);

// constraint
  __expression = new BNFExpression(constraint);
    __expression->AddElement(_constraint,NO,1,NO,YES);
    __expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    __expression->AddElement(operand,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);

// sources
  __expression = new BNFExpression(sources);
    __expression->AddElement(_source,NO,1,NO,YES);
    __expression->AddElement(operand_list,NO,1,YES,YES);

// version
  __expression = new BNFExpression(version);
    __expression->AddElement(_version,NO,1,NO,YES);
    __expression->AddElement(number,NO,1,YES,YES);

// order_keys
  __expression = new BNFExpression(order_keys);
    __expression->AddElement(ordered_by,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    __expression->AddElement(index_specs,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);

// index_specs
  __expression = new BNFExpression(index_specs);
    __expression->AddElement(index_spec,NO,1,YES,YES);
    __expression->AddElement(index_spec_suc,YES,UNDEF,YES,YES);

// index_spec_suc
  __expression = new BNFExpression(index_spec_suc);
    __expression->AddElement(ElementaryToken(','),NO,1,NO,YES);
    __expression->AddElement(index_spec,NO,1,YES,YES);

// index_spec
  __expression = new BNFExpression(index_spec);
    __expression->AddElement(key_name,NO,1,YES,YES);
    __expression->AddElement(index_option,YES,UNDEF,YES,YES);

// key_name
  __expression = new BNFExpression(key_name);
    __expression->AddElement(identifier,NO,1,YES,YES);

// index_option
  __expression = new BNFExpression(index_option);
    __expression->AddElement(unique,NO,1,YES,YES);
  __expression = new BNFExpression(index_option);
    __expression->AddElement(not_empty,NO,1,YES,YES);
  __expression = new BNFExpression(index_option);
    __expression->AddElement(temporary,NO,1,YES,YES);

// meth_dcl
  __expression = new BNFExpression(meth_dcl);
    __expression->AddElement(oneway,YES,1,YES,YES);
    __expression->AddElement(mtype_ref,NO,1,YES,YES);
    __expression->AddElement(ref_symbol,YES,UNDEF,YES,YES);
    __expression->AddElement(meth_ident,NO,1,YES,YES);
    __expression->AddElement(parameter_dcls,NO,1,YES,YES);
    __expression->AddElement(raises_expr,YES,1,YES,YES);
    __expression->AddElement(context_expr,YES,1,YES,YES);

// meth_ident
  __expression = new BNFExpression(meth_ident);
    __expression->AddElement(ElementaryToken('~'),YES,1,NO,YES);
    __expression->AddElement(scoped_name,NO,1,YES,YES);
    __expression->AddElement(impl_ident,YES,1,YES,YES);
    __expression->AddElement(cun_op,YES,1,YES,YES);

// impl_ident
  __expression = new BNFExpression(impl_ident);
    __expression->AddElement(ElementaryToken('.'),NO,1,NO,YES);
    __expression->AddElement(identifier,NO,1,YES,YES);

// mtype_ref
  __expression = new BNFExpression(mtype_ref);
    __expression->AddElement(type_ref_options,YES,UNDEF,YES,YES);
    __expression->AddElement(simple_type_spec,NO,1,YES,YES);

// parameter_dcls
  __expression = new BNFExpression(parameter_dcls);
    __expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    __expression->AddElement(params_dcl,YES,1,YES,YES);
    __expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);

// raises_expr
  __expression = new BNFExpression(raises_expr);
    __expression->AddElement(raises,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    __expression->AddElement(scoped_names,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);

// scoped_names
  __expression = new BNFExpression(scoped_names);
    __expression->AddElement(scoped_name,NO,1,YES,YES);
    __expression->AddElement(scoped_name_suc,YES,UNDEF,YES,YES);

// scoped_name_suc
  __expression = new BNFExpression(scoped_name_suc);
    __expression->AddElement(ElementaryToken(','),NO,1,NO,YES);
    __expression->AddElement(scoped_name,NO,1,YES,YES);

// context_expr
  __expression = new BNFExpression(context_expr);
    __expression->AddElement(context,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    __expression->AddElement(string_literals,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);

// string_literals
  __expression = new BNFExpression(string_literals);
    __expression->AddElement(string_literal,NO,1,YES,YES);
    __expression->AddElement(string_literal_suc,YES,UNDEF,YES,YES);

// string_literal_suc
  __expression = new BNFExpression(string_literal_suc);
    __expression->AddElement(ElementaryToken(','),NO,1,NO,YES);
    __expression->AddElement(string_literal,NO,1,YES,YES);

// string_literal
  __expression = new BNFExpression(string_literal);
    __expression->AddElement(string,NO,1,YES,YES);

// members
  __expression = new BNFExpression(members);
    __expression->AddElement(member,NO,UNDEF,YES,YES);

// member
  __expression = new BNFExpression(member);
    __expression->AddElement(_global,YES,1,NO,YES);
    __expression->AddElement(type_spec,NO,1,YES,YES);
    __expression->AddElement(declarators,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// params_dcl
  __expression = new BNFExpression(params_dcl);
    __expression->AddElement(param_dcl,NO,1,YES,YES);
    __expression->AddElement(param_dcl_suc,YES,UNDEF,YES,YES);

// param_dcl_suc
  __expression = new BNFExpression(param_dcl_suc);
    __expression->AddElement(ElementaryToken(','),NO,1,NO,YES);
    __expression->AddElement(param_dcl,NO,1,YES,YES);

// param_dcl
  __expression = new BNFExpression(param_dcl);
    __expression->AddElement(param_attribute,YES,1,YES,YES);
    __expression->AddElement(simple_type_spec,NO,1,YES,YES);
    __expression->AddElement(declarator,NO,1,YES,YES);

// param_attribute
  __expression = new BNFExpression(param_attribute);
    __expression->AddElement(in,NO,1,YES,YES);
  __expression = new BNFExpression(param_attribute);
    __expression->AddElement(out,NO,1,YES,YES);
  __expression = new BNFExpression(param_attribute);
    __expression->AddElement(inout,NO,1,YES,YES);

// parm_list
  __expression = new BNFExpression(parm_list);
    __expression->AddElement(parameter,NO,1,YES,YES);
    __expression->AddElement(parm_ext,YES,UNDEF,YES,YES);

// parm_ext
  __expression = new BNFExpression(parm_ext);
    __expression->AddElement(ElementaryToken(','),NO,1,NO,YES);
    __expression->AddElement(parameter,NO,1,YES,YES);

// parameter
  __expression = new BNFExpression(parameter);
    __expression->AddElement(parm_spec,NO,1,YES,YES);
  __expression = new BNFExpression(parameter);
    __expression->AddElement(operand,NO,1,YES,YES);
  __expression = new BNFExpression(parameter);
    __expression->AddElement(ElementaryToken('*'),NO,1,NO,YES);

// parm_spec
  __expression = new BNFExpression(parm_spec);
    __expression->AddElement(simple_type_spec,YES,1,YES,YES);
    __expression->AddElement(ref_symbol,YES,UNDEF,YES,YES);
    __expression->AddElement(identifier,NO,1,YES,YES);
    __expression->AddElement(fixed_array_size,YES,UNDEF,YES,YES);
    __expression->AddElement(assigned_value,NO,1,YES,YES);

// categories
  __expression = new BNFExpression(categories);
    __expression->AddElement(category_list,NO,1,YES,YES);
  __expression = new BNFExpression(categories);
    __expression->AddElement(operand,NO,1,YES,YES);

// category_list
  __expression = new BNFExpression(category_list);
    __expression->AddElement(category_spec,NO,1,YES,YES);
    __expression->AddElement(category_ext,YES,UNDEF,YES,YES);

// category_ext
  __expression = new BNFExpression(category_ext);
    __expression->AddElement(ElementaryToken(','),NO,1,NO,YES);
    __expression->AddElement(category_spec,NO,1,YES,YES);

// category_spec
  __expression = new BNFExpression(category_spec);
    __expression->AddElement(cat_name,NO,1,YES,YES);
    __expression->AddElement(cat_condition,YES,1,YES,YES);

// cat_condition
  __expression = new BNFExpression(cat_condition);
    __expression->AddElement(ElementaryToken(':'),NO,1,NO,YES);
    __expression->AddElement(operand,NO,1,YES,YES);

// cat_name
  __expression = new BNFExpression(cat_name);
    __expression->AddElement(identifier,NO,1,YES,YES);
  __expression = new BNFExpression(cat_name);
    __expression->AddElement(string,NO,1,YES,YES);
  __expression = new BNFExpression(cat_name);
    __expression->AddElement(number,NO,1,YES,YES);

// declarators
  __expression = new BNFExpression(declarators);
    __expression->AddElement(declarator,NO,1,YES,YES);
    __expression->AddElement(declarator_suc,YES,UNDEF,YES,YES);

// declarator_suc
  __expression = new BNFExpression(declarator_suc);
    __expression->AddElement(ElementaryToken(','),NO,1,NO,YES);
    __expression->AddElement(declarator,NO,1,YES,YES);

// declarator
  __expression = new BNFExpression(declarator);
    __expression->AddElement(ref_symbol,YES,UNDEF,YES,YES);
    __expression->AddElement(identifier,NO,1,YES,YES);
    __expression->AddElement(fixed_array_size,YES,UNDEF,YES,YES);
    __expression->AddElement(assigned_value,YES,1,YES,YES);
    __expression->AddElement(attr_ext_decl,YES,UNDEF,YES,YES);

// ref_symbol
  __expression = new BNFExpression(ref_symbol);
    __expression->AddElement(ElementaryToken('*'),NO,1,NO,YES);
  __expression = new BNFExpression(ref_symbol);
    __expression->AddElement(ElementaryToken('&'),NO,1,NO,YES);
  ref_symbol->SetTerminal();

// fixed_array_size
  __expression = new BNFExpression(fixed_array_size);
    __expression->AddElement(ElementaryToken('['),NO,1,NO,YES);
    __expression->AddElement(size_spec,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(']'),NO,1,NO,YES);

// size_spec
  __expression = new BNFExpression(size_spec);
    __expression->AddElement(size,NO,1,YES,YES);
    __expression->AddElement(dimension,YES,1,YES,YES);

// size
  __expression = new BNFExpression(size);
    __expression->AddElement(number,NO,1,YES,YES);

// dimension
  __expression = new BNFExpression(dimension);
    __expression->AddElement(ElementaryToken(','),NO,1,NO,YES);
    __expression->AddElement(number,NO,1,YES,YES);

// assigned_value
  __expression = new BNFExpression(assigned_value);
    __expression->AddElement(assign_op,NO,1,YES,YES);
    __expression->AddElement(operand,NO,1,YES,YES);

// type_ref
  __expression = new BNFExpression(type_ref);
    __expression->AddElement(type_ref_options,YES,UNDEF,YES,YES);
    __expression->AddElement(domain_type,NO,1,YES,YES);

// type_ref_options
  __expression = new BNFExpression(type_ref_options);
    __expression->AddElement(priv_option,NO,1,YES,YES);
  __expression = new BNFExpression(type_ref_options);
    __expression->AddElement(prop_option,NO,1,YES,YES);

// prop_option
  __expression = new BNFExpression(prop_option);
    __expression->AddElement(_static,NO,1,NO,YES);
  __expression = new BNFExpression(prop_option);
    __expression->AddElement(_collection,NO,1,NO,YES);
  __expression = new BNFExpression(prop_option);
    __expression->AddElement(_transient,NO,1,NO,YES);
  __expression = new BNFExpression(prop_option);
    __expression->AddElement(_virtual,NO,1,NO,YES);
  __expression = new BNFExpression(prop_option);
    __expression->AddElement(not_empty,NO,1,YES,YES);

// priv_option
  __expression = new BNFExpression(priv_option);
    __expression->AddElement(_private,NO,1,NO,YES);
  __expression = new BNFExpression(priv_option);
    __expression->AddElement(_public,NO,1,NO,YES);
  __expression = new BNFExpression(priv_option);
    __expression->AddElement(_protected,NO,1,NO,YES);

// domain_type
  __expression = new BNFExpression(domain_type);
    __expression->AddElement(simple_type_spec,NO,1,YES,YES);
  __expression = new BNFExpression(domain_type);
    __expression->AddElement(struct_type,NO,1,YES,YES);
  __expression = new BNFExpression(domain_type);
    __expression->AddElement(enum_type,NO,1,YES,YES);

// type_spec
  __expression = new BNFExpression(type_spec);
    __expression->AddElement(simple_type_spec,NO,1,YES,YES);
  __expression = new BNFExpression(type_spec);
    __expression->AddElement(constr_type_spec,NO,1,YES,YES);

// constr_type_spec
  __expression = new BNFExpression(constr_type_spec);
    __expression->AddElement(struct_type,NO,1,YES,YES);
  __expression = new BNFExpression(constr_type_spec);
    __expression->AddElement(union_type,NO,1,YES,YES);
  __expression = new BNFExpression(constr_type_spec);
    __expression->AddElement(enum_type,NO,1,YES,YES);

// simple_type_spec
  __expression = new BNFExpression(simple_type_spec);
    __expression->AddElement(base_type_spec,NO,1,YES,YES);
  __expression = new BNFExpression(simple_type_spec);
    __expression->AddElement(extended_type_spec,NO,1,YES,YES);

// base_type_spec
  __expression = new BNFExpression(base_type_spec);
    __expression->AddElement(floating_pt_type,NO,1,YES,YES);
  __expression = new BNFExpression(base_type_spec);
    __expression->AddElement(integer_type,NO,1,YES,YES);
  __expression = new BNFExpression(base_type_spec);
    __expression->AddElement(char_len_types,NO,1,YES,YES);
  __expression = new BNFExpression(base_type_spec);
    __expression->AddElement(boolean_type,NO,1,YES,YES);
  __expression = new BNFExpression(base_type_spec);
    __expression->AddElement(octet_type,NO,1,YES,YES);
  __expression = new BNFExpression(base_type_spec);
    __expression->AddElement(date_type,NO,1,YES,YES);
  __expression = new BNFExpression(base_type_spec);
    __expression->AddElement(time_type,NO,1,YES,YES);
  __expression = new BNFExpression(base_type_spec);
    __expression->AddElement(timestamp_type,NO,1,YES,YES);
  __expression = new BNFExpression(base_type_spec);
    __expression->AddElement(bit_type,NO,1,YES,YES);
  __expression = new BNFExpression(base_type_spec);
    __expression->AddElement(binary_type,NO,1,YES,YES);
  __expression = new BNFExpression(base_type_spec);
    __expression->AddElement(any_type,NO,1,YES,YES);

// extended_type_spec
  __expression = new BNFExpression(extended_type_spec);
    __expression->AddElement(array_type,NO,1,YES,YES);
  __expression = new BNFExpression(extended_type_spec);
    __expression->AddElement(gstring_type,NO,1,YES,YES);
  __expression = new BNFExpression(extended_type_spec);
    __expression->AddElement(coll_type,NO,1,YES,YES);
  __expression = new BNFExpression(extended_type_spec);
    __expression->AddElement(interval_type,NO,1,YES,YES);
  __expression = new BNFExpression(extended_type_spec);
    __expression->AddElement(generic_type,NO,1,YES,YES);
  __expression = new BNFExpression(extended_type_spec);
    __expression->AddElement(scoped_name,NO,1,YES,YES);

// array_type
  __expression = new BNFExpression(array_type);
    __expression->AddElement(array_spec,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken('<'),NO,1,NO,YES);
    __expression->AddElement(simple_type_spec,NO,1,YES,YES);
    __expression->AddElement(array_dim,YES,1,YES,YES);
    __expression->AddElement(ElementaryToken('>'),NO,1,NO,YES);

// array_spec
  __expression = new BNFExpression(array_spec);
    __expression->AddElement(array,NO,1,YES,YES);
  __expression = new BNFExpression(array_spec);
    __expression->AddElement(sequence,NO,1,YES,YES);

// array_dim
  __expression = new BNFExpression(array_dim);
    __expression->AddElement(ElementaryToken(','),YES,1,NO,YES);
    __expression->AddElement(number,NO,1,YES,YES);

// gstring_type
  __expression = new BNFExpression(gstring_type);
    __expression->AddElement(string_type,NO,1,YES,YES);
    __expression->AddElement(string_size,NO,1,YES,YES);

// string_size
  __expression = new BNFExpression(string_size);
    __expression->AddElement(ElementaryToken('<'),NO,1,NO,YES);
    __expression->AddElement(number,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken('>'),NO,1,NO,YES);

// coll_type
  __expression = new BNFExpression(coll_type);
    __expression->AddElement(dict_coll,NO,1,YES,YES);
  __expression = new BNFExpression(coll_type);
    __expression->AddElement(coll_coll,NO,1,YES,YES);

// coll_coll
  __expression = new BNFExpression(coll_coll);
    __expression->AddElement(coll_spec,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken('<'),NO,1,NO,YES);
    __expression->AddElement(simple_type_spec,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken('>'),NO,1,NO,YES);

// coll_spec
  __expression = new BNFExpression(coll_spec);
    __expression->AddElement(set,NO,1,YES,YES);
  __expression = new BNFExpression(coll_spec);
    __expression->AddElement(list,NO,1,YES,YES);
  __expression = new BNFExpression(coll_spec);
    __expression->AddElement(bag,NO,1,YES,YES);

// dict_coll
  __expression = new BNFExpression(dict_coll);
    __expression->AddElement(_dictionary,NO,1,NO,YES);
    __expression->AddElement(ElementaryToken('<'),NO,1,NO,YES);
    __expression->AddElement(simple_type_spec,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(','),NO,1,NO,YES);
    __expression->AddElement(simple_type_spec,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken('>'),NO,1,NO,YES);

// interval_type
  __expression = new BNFExpression(interval_type);
    __expression->AddElement(interval,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken('<'),NO,1,NO,YES);
    __expression->AddElement(simple_type_spec,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken('>'),NO,1,NO,YES);

// generic_type
  __expression = new BNFExpression(generic_type);
    __expression->AddElement(identifier,NO,1,YES,YES);
    __expression->AddElement(gentype_parm,NO,1,YES,YES);

// gentype_parm
  __expression = new BNFExpression(gentype_parm);
    __expression->AddElement(gentype_parm_new,NO,1,YES,YES);
  __expression = new BNFExpression(gentype_parm);
    __expression->AddElement(gentype_parm_old,NO,1,YES,YES);

// gentype_parm_new
  __expression = new BNFExpression(gentype_parm_new);
    __expression->AddElement(ElementaryToken('<'),NO,1,NO,YES);
    __expression->AddElement(simple_type_spec,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken('>'),NO,1,NO,YES);

// gentype_parm_old
  __expression = new BNFExpression(gentype_parm_old);
    __expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    __expression->AddElement(simple_type_spec,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);

// char_len_types
  __expression = new BNFExpression(char_len_types);
    __expression->AddElement(char_types,NO,1,YES,YES);
    __expression->AddElement(len_spec,YES,1,YES,YES);

// len_spec
  __expression = new BNFExpression(len_spec);
    __expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    __expression->AddElement(size,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);

// char_types
  __expression = new BNFExpression(char_types);
    __expression->AddElement(char_type,NO,1,YES,YES);
  __expression = new BNFExpression(char_types);
    __expression->AddElement(string_type,NO,1,YES,YES);
  __expression = new BNFExpression(char_types);
    __expression->AddElement(coded_type,NO,1,YES,YES);
  __expression = new BNFExpression(char_types);
    __expression->AddElement(wstring_type,NO,1,YES,YES);

// integer_type
  __expression = new BNFExpression(integer_type);
    __expression->AddElement(_unsigned,YES,1,NO,YES);
    __expression->AddElement(int_types,NO,1,YES,YES);

// int_types
  __expression = new BNFExpression(int_types);
    __expression->AddElement(base_int,NO,1,YES,YES);
  __expression = new BNFExpression(int_types);
    __expression->AddElement(int_spec,NO,1,YES,YES);

// base_int
  __expression = new BNFExpression(base_int);
    __expression->AddElement(short_int,NO,1,YES,YES);
  __expression = new BNFExpression(base_int);
    __expression->AddElement(long_int,NO,1,YES,YES);
  __expression = new BNFExpression(base_int);
    __expression->AddElement(long_long_int,NO,1,YES,YES);

// long_long_int
  __expression = new BNFExpression(long_long_int);
    __expression->AddElement(long_int,NO,1,YES,YES);
    __expression->AddElement(long_int,NO,1,YES,YES);

// int_spec
  __expression = new BNFExpression(int_spec);
    __expression->AddElement(int_type,NO,1,YES,YES);
    __expression->AddElement(int_size,YES,1,YES,YES);

// int_size
  __expression = new BNFExpression(int_size);
    __expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    __expression->AddElement(size,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(','),YES,1,NO,YES);
    __expression->AddElement(precision_val,YES,1,YES,YES);
    __expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);

// precision_val
  __expression = new BNFExpression(precision_val);
    __expression->AddElement(number,NO,1,YES,YES);

// date_type
  __expression = new BNFExpression(date_type);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(date_type);
    __expression->AddElement(__date_type,NO,1,NO,YES);

// __date_type
  __expression = new BNFExpression(__date_type);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  __date_type->SetKeyword();

// time_type
  __expression = new BNFExpression(time_type);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('m'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(time_type);
    __expression->AddElement(__time_type,NO,1,NO,YES);

// __time_type
  __expression = new BNFExpression(__time_type);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('M'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  __time_type->SetKeyword();

// timestamp_type
  __expression = new BNFExpression(timestamp_type);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('m'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('m'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('p'),NO,1,YES,YES);
  __expression = new BNFExpression(timestamp_type);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('m'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(timestamp_type);
    __expression->AddElement(__timestamp_type,NO,1,NO,YES);

// __timestamp_type
  __expression = new BNFExpression(__timestamp_type);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('M'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  __timestamp_type->SetKeyword();

// coded_type
  __expression = new BNFExpression(coded_type);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,YES);
  __expression = new BNFExpression(coded_type);
    __expression->AddElement(__coded_type,NO,1,NO,YES);

// __coded_type
  __expression = new BNFExpression(__coded_type);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,YES);
  __expression = new BNFExpression(__coded_type);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('H'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,YES);
  __coded_type->SetKeyword();

// string_type
  __expression = new BNFExpression(string_type);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('g'),NO,1,YES,YES);
  __expression = new BNFExpression(string_type);
    __expression->AddElement(__string_type,NO,1,NO,YES);

// __string_type
  __expression = new BNFExpression(__string_type);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('G'),NO,1,NO,YES);
  __expression = new BNFExpression(__string_type);
    __expression->AddElement(ElementaryToken('M'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('M'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,YES);
  __string_type->SetKeyword();

// wstring_type
  __expression = new BNFExpression(wstring_type);
    __expression->AddElement(ElementaryToken('w'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('g'),NO,1,YES,YES);
  __expression = new BNFExpression(wstring_type);
    __expression->AddElement(__wstring_type,NO,1,NO,YES);

// __wstring_type
  __expression = new BNFExpression(__wstring_type);
    __expression->AddElement(ElementaryToken('W'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('G'),NO,1,NO,YES);
  __wstring_type->SetKeyword();

// char_type
  __expression = new BNFExpression(char_type);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('h'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,YES);
  __expression = new BNFExpression(char_type);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('H'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,YES);
  __expression = new BNFExpression(char_type);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('8'),NO,1,NO,YES);
  char_type->SetKeyword();

// floating_pt_type
  __expression = new BNFExpression(floating_pt_type);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('b'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(floating_pt_type);
    __expression->AddElement(ElementaryToken('f'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  __expression = new BNFExpression(floating_pt_type);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,YES);
  __expression = new BNFExpression(floating_pt_type);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,YES);
  floating_pt_type->SetKeyword();

// boolean_type
  __expression = new BNFExpression(boolean_type);
    __expression->AddElement(ElementaryToken('b'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,YES);
  __expression = new BNFExpression(boolean_type);
    __expression->AddElement(ElementaryToken('b'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,YES);
  __expression = new BNFExpression(boolean_type);
    __expression->AddElement(ElementaryToken('B'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,YES);
  __expression = new BNFExpression(boolean_type);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('g'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,YES);
  __expression = new BNFExpression(boolean_type);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('G'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,YES);
  boolean_type->SetKeyword();

// any_type
  __expression = new BNFExpression(any_type);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('y'),NO,1,YES,YES);
  __expression = new BNFExpression(any_type);
    __expression->AddElement(ElementaryToken('v'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,YES);
  __expression = new BNFExpression(any_type);
    __expression->AddElement(ElementaryToken('V'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,YES);
  __expression = new BNFExpression(any_type);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('Y'),NO,1,NO,YES);
  any_type->SetKeyword();

// bit_type
  __expression = new BNFExpression(bit_type);
    __expression->AddElement(ElementaryToken('b'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  __expression = new BNFExpression(bit_type);
    __expression->AddElement(ElementaryToken('B'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,YES);
  bit_type->SetKeyword();

// short_int
  __expression = new BNFExpression(short_int);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('1'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('6'),NO,1,NO,YES);
  __expression = new BNFExpression(short_int);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('H'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,YES);
  __expression = new BNFExpression(short_int);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('h'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  short_int->SetKeyword();

// long_int
  __expression = new BNFExpression(long_int);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('3'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('2'),NO,1,NO,YES);
  __expression = new BNFExpression(long_int);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('G'),NO,1,NO,YES);
  __expression = new BNFExpression(long_int);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('g'),NO,1,YES,YES);
  long_int->SetKeyword();

// int_type
  __expression = new BNFExpression(int_type);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  __expression = new BNFExpression(int_type);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,YES);
  __expression = new BNFExpression(int_type);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,YES);
  int_type->SetKeyword();

// _unsigned
  __expression = new BNFExpression(_unsigned);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('g'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,YES);
  __expression = new BNFExpression(_unsigned);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('G'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,YES);
  _unsigned->SetKeyword();

// octet_type
  __expression = new BNFExpression(octet_type);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  octet_type->SetKeyword();

// binary_type
  __expression = new BNFExpression(binary_type);
    __expression->AddElement(ElementaryToken('b'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('y'),NO,1,YES,YES);
  __expression = new BNFExpression(binary_type);
    __expression->AddElement(ElementaryToken('B'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('Y'),NO,1,NO,YES);
  __expression = new BNFExpression(binary_type);
    __expression->AddElement(ElementaryToken('B'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('B'),NO,1,NO,YES);
  binary_type->SetKeyword();

// _exception
  __expression = new BNFExpression(_exception);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('x'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,YES);
  __expression = new BNFExpression(_exception);
    __expression->AddElement(__exception,NO,1,NO,YES);

// __exception
  __expression = new BNFExpression(__exception);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('X'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('P'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,YES);
  __exception->SetKeyword();

// _include
  __expression = new BNFExpression(_include);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(_include);
    __expression->AddElement(__include,NO,1,NO,YES);

// __include
  __expression = new BNFExpression(__include);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  __include->SetKeyword();

// _private
  __expression = new BNFExpression(_private);
    __expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('v'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(_private);
    __expression->AddElement(__private,NO,1,NO,YES);

// __private
  __expression = new BNFExpression(__private);
    __expression->AddElement(ElementaryToken('P'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('V'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  __private->SetKeyword();

// _protected
  __expression = new BNFExpression(_protected);
    __expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,YES);
  __expression = new BNFExpression(_protected);
    __expression->AddElement(__protected,NO,1,NO,YES);

// __protected
  __expression = new BNFExpression(__protected);
    __expression->AddElement(ElementaryToken('P'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,YES);
  __protected->SetKeyword();

// _public
  __expression = new BNFExpression(_public);
    __expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('b'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,YES);
  __expression = new BNFExpression(_public);
    __expression->AddElement(__public,NO,1,NO,YES);

// __public
  __expression = new BNFExpression(__public);
    __expression->AddElement(ElementaryToken('P'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('B'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,YES);
  __public->SetKeyword();

// _static
  __expression = new BNFExpression(_static);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,YES);
  __expression = new BNFExpression(_static);
    __expression->AddElement(__static,NO,1,NO,YES);

// __static
  __expression = new BNFExpression(__static);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,YES);
  __expression = new BNFExpression(__static);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,YES);
  __static->SetKeyword();

// _virtual
  __expression = new BNFExpression(_virtual);
    __expression->AddElement(ElementaryToken('v'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,YES);
  __expression = new BNFExpression(_virtual);
    __expression->AddElement(__virtual,NO,1,NO,YES);

// __virtual
  __expression = new BNFExpression(__virtual);
    __expression->AddElement(ElementaryToken('V'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,YES);
  __virtual->SetKeyword();

// _transient
  __expression = new BNFExpression(_transient);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  __expression = new BNFExpression(_transient);
    __expression->AddElement(__transient,NO,1,NO,YES);

// __transient
  __expression = new BNFExpression(__transient);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,YES);
  __transient->SetKeyword();

// _new
  __expression = new BNFExpression(_new);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('w'),NO,1,YES,YES);
  __expression = new BNFExpression(_new);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('W'),NO,1,NO,YES);
  _new->SetKeyword();

// _typedef
  __expression = new BNFExpression(_typedef);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('y'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('f'),NO,1,YES,YES);
  __expression = new BNFExpression(_typedef);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('Y'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('P'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('F'),NO,1,NO,YES);
  _typedef->SetKeyword();

// _enum
  __expression = new BNFExpression(_enum);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('m'),NO,1,YES,YES);
  __expression = new BNFExpression(_enum);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('M'),NO,1,NO,YES);
  _enum->SetKeyword();

// _struct
  __expression = new BNFExpression(_struct);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  __expression = new BNFExpression(_struct);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,YES);
  _struct->SetKeyword();

// _union
  __expression = new BNFExpression(_union);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,YES);
  __expression = new BNFExpression(_union);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,YES);
  _union->SetKeyword();

// _switch
  __expression = new BNFExpression(_switch);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('w'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('h'),NO,1,YES,YES);
  __expression = new BNFExpression(_switch);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('W'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('H'),NO,1,NO,YES);
  _switch->SetKeyword();

// _case
  __expression = new BNFExpression(_case);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(_case);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  _case->SetKeyword();

// _default
  __expression = new BNFExpression(_default);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('f'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  __expression = new BNFExpression(_default);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('F'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,YES);
  __expression = new BNFExpression(_default);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('h'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,YES);
  __expression = new BNFExpression(_default);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('H'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,YES);
  _default->SetKeyword();

// _interface
  __expression = new BNFExpression(_interface);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('f'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(_interface);
    __expression->AddElement(_interface_,NO,1,NO,YES);

// _interface_
  __expression = new BNFExpression(_interface_);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('F'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  _interface_->SetKeyword();

// _view
  __expression = new BNFExpression(_view);
    __expression->AddElement(ElementaryToken('v'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('w'),NO,1,YES,YES);
  __expression = new BNFExpression(_view);
    __expression->AddElement(__view,NO,1,NO,YES);

// __view
  __expression = new BNFExpression(__view);
    __expression->AddElement(ElementaryToken('V'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('W'),NO,1,NO,YES);
  __view->SetKeyword();

// _module
  __expression = new BNFExpression(_module);
    __expression->AddElement(ElementaryToken('m'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(_module);
    __expression->AddElement(__module,NO,1,NO,YES);

// __module
  __expression = new BNFExpression(__module);
    __expression->AddElement(ElementaryToken('M'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  __module->SetKeyword();

// _namespace
  __expression = new BNFExpression(_namespace);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('m'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(_namespace);
    __expression->AddElement(__namespace,NO,1,NO,YES);

// __namespace
  __expression = new BNFExpression(__namespace);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('M'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('P'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  __namespace->SetKeyword();

// _const
  __expression = new BNFExpression(_const);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  __expression = new BNFExpression(_const);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,YES);
  _const->SetKeyword();

// _class
  __expression = new BNFExpression(_class);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,YES);
  __expression = new BNFExpression(_class);
    __expression->AddElement(__class,NO,1,NO,YES);

// __class
  __expression = new BNFExpression(__class);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,YES);
  __class->SetKeyword();

// extends
  __expression = new BNFExpression(extends);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('x'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,YES);
  extends->SetTerminal();

// __extends
  __expression = new BNFExpression(__extends);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('X'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,YES);
  __extends->SetKeyword();

// in
  __expression = new BNFExpression(in);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,YES);
  __expression = new BNFExpression(in);
    __expression->AddElement(__in,NO,1,NO,YES);

// __in
  __expression = new BNFExpression(__in);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,YES);
  __in->SetKeyword();

// out
  __expression = new BNFExpression(out);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  __expression = new BNFExpression(out);
    __expression->AddElement(__out,NO,1,NO,YES);

// __out
  __expression = new BNFExpression(__out);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,YES);
  __out->SetKeyword();

// inout
  __expression = new BNFExpression(inout);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  __expression = new BNFExpression(inout);
    __expression->AddElement(__inout,NO,1,NO,YES);

// __inout
  __expression = new BNFExpression(__inout);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,YES);
  __inout->SetKeyword();

// oneway
  __expression = new BNFExpression(oneway);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('w'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('y'),NO,1,YES,YES);
  __expression = new BNFExpression(oneway);
    __expression->AddElement(__oneway,NO,1,NO,YES);

// __oneway
  __expression = new BNFExpression(__oneway);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('W'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('Y'),NO,1,NO,YES);
  __oneway->SetKeyword();

// raises
  __expression = new BNFExpression(raises);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,YES);
  __expression = new BNFExpression(raises);
    __expression->AddElement(__raises,NO,1,NO,YES);

// __raises
  __expression = new BNFExpression(__raises);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,YES);
  __raises->SetKeyword();

// array
  __expression = new BNFExpression(array);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('y'),NO,1,YES,YES);
  __expression = new BNFExpression(array);
    __expression->AddElement(__array,NO,1,NO,YES);

// __array
  __expression = new BNFExpression(__array);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('Y'),NO,1,NO,YES);
  __array->SetKeyword();

// sequence
  __expression = new BNFExpression(sequence);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('q'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(sequence);
    __expression->AddElement(__sequence,NO,1,NO,YES);

// __sequence
  __expression = new BNFExpression(__sequence);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('Q'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  __sequence->SetKeyword();

// set
  __expression = new BNFExpression(set);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  __expression = new BNFExpression(set);
    __expression->AddElement(__set,NO,1,NO,YES);

// __set
  __expression = new BNFExpression(__set);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,YES);
  __set->SetKeyword();

// list
  __expression = new BNFExpression(list);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  __expression = new BNFExpression(list);
    __expression->AddElement(__list,NO,1,NO,YES);

// __list
  __expression = new BNFExpression(__list);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,YES);
  __list->SetKeyword();

// bag
  __expression = new BNFExpression(bag);
    __expression->AddElement(ElementaryToken('b'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('g'),NO,1,YES,YES);
  __expression = new BNFExpression(bag);
    __expression->AddElement(__bag,NO,1,NO,YES);

// __bag
  __expression = new BNFExpression(__bag);
    __expression->AddElement(ElementaryToken('B'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('G'),NO,1,NO,YES);
  __bag->SetKeyword();

// _dictionary
  __expression = new BNFExpression(_dictionary);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('y'),NO,1,YES,YES);
  __expression = new BNFExpression(_dictionary);
    __expression->AddElement(__dictionary,NO,1,NO,YES);

// __dictionary
  __expression = new BNFExpression(__dictionary);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('Y'),NO,1,NO,YES);
  __dictionary->SetKeyword();

// attribute
  __expression = new BNFExpression(attribute);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('b'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(attribute);
    __expression->AddElement(___attribute,NO,1,NO,YES);

// ___attribute
  __expression = new BNFExpression(___attribute);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('B'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  ___attribute->SetKeyword();

// relationship
  __expression = new BNFExpression(relationship);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('h'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('p'),NO,1,YES,YES);
  __expression = new BNFExpression(relationship);
    __expression->AddElement(__relationship,NO,1,NO,YES);

// __relationship
  __expression = new BNFExpression(__relationship);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('H'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('P'),NO,1,NO,YES);
  __relationship->SetKeyword();

// reference
  __expression = new BNFExpression(reference);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('f'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(reference);
    __expression->AddElement(__reference,NO,1,NO,YES);

// __reference
  __expression = new BNFExpression(__reference);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('F'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  __reference->SetKeyword();

// _collection
  __expression = new BNFExpression(_collection);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,YES);
  __expression = new BNFExpression(_collection);
    __expression->AddElement(__collection,NO,1,NO,YES);

// __collection
  __expression = new BNFExpression(__collection);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,YES);
  __collection->SetKeyword();

// inverse
  __expression = new BNFExpression(inverse);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('v'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(inverse);
    __expression->AddElement(__inverse,NO,1,NO,YES);

// __inverse
  __expression = new BNFExpression(__inverse);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('V'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  __inverse->SetKeyword();

// extent
  __expression = new BNFExpression(extent);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('x'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  __expression = new BNFExpression(extent);
    __expression->AddElement(__extent,NO,1,NO,YES);

// __extent
  __expression = new BNFExpression(__extent);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('X'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,YES);
  __extent->SetKeyword();

// key
  __expression = new BNFExpression(key);
    __expression->AddElement(ElementaryToken('k'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('y'),NO,1,YES,YES);
  __expression = new BNFExpression(key);
    __expression->AddElement(ElementaryToken('k'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('y'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,YES);
  __expression = new BNFExpression(key);
    __expression->AddElement(__key,NO,1,NO,YES);

// __key
  __expression = new BNFExpression(__key);
    __expression->AddElement(ElementaryToken('K'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('Y'),NO,1,NO,YES);
  __expression = new BNFExpression(__key);
    __expression->AddElement(ElementaryToken('K'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('Y'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,YES);
  __key->SetKeyword();

// context
  __expression = new BNFExpression(context);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('x'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  __expression = new BNFExpression(context);
    __expression->AddElement(__context,NO,1,NO,YES);

// __context
  __expression = new BNFExpression(__context);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('X'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,YES);
  __context->SetKeyword();

// _select
  __expression = new BNFExpression(_select);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  __expression = new BNFExpression(_select);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,YES);
  _select->SetKeyword();

// _from
  __expression = new BNFExpression(_from);
    __expression->AddElement(ElementaryToken('F'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('m'),NO,1,YES,YES);
  __expression = new BNFExpression(_from);
    __expression->AddElement(ElementaryToken('F'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('M'),NO,1,NO,YES);
  _from->SetKeyword();

// _where
  __expression = new BNFExpression(_where);
    __expression->AddElement(ElementaryToken('W'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('h'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(_where);
    __expression->AddElement(ElementaryToken('W'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('H'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  _where->SetKeyword();

// _having
  __expression = new BNFExpression(_having);
    __expression->AddElement(ElementaryToken('H'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('v'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('g'),NO,1,YES,YES);
  __expression = new BNFExpression(_having);
    __expression->AddElement(ElementaryToken('H'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('V'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('G'),NO,1,NO,YES);
  _having->SetKeyword();

// _join
  __expression = new BNFExpression(_join);
    __expression->AddElement(ElementaryToken('J'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,YES);
  __expression = new BNFExpression(_join);
    __expression->AddElement(ElementaryToken('J'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,YES);
  _join->SetKeyword();

// _minus
  __expression = new BNFExpression(_minus);
    __expression->AddElement(ElementaryToken('M'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,YES);
  __expression = new BNFExpression(_minus);
    __expression->AddElement(ElementaryToken('M'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,YES);
  _minus->SetKeyword();

// _intersect
  __expression = new BNFExpression(_intersect);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  __expression = new BNFExpression(_intersect);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,YES);
  _intersect->SetKeyword();

// _group_by
  __expression = new BNFExpression(_group_by);
    __expression->AddElement(ElementaryToken('G'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('B'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('y'),NO,1,YES,YES);
  __expression = new BNFExpression(_group_by);
    __expression->AddElement(ElementaryToken('G'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('P'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('B'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('Y'),NO,1,NO,YES);
  _group_by->SetKeyword();

// _order_by
  __expression = new BNFExpression(_order_by);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('B'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('y'),NO,1,YES,YES);
  __expression = new BNFExpression(_order_by);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('B'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('Y'),NO,1,NO,YES);
  _order_by->SetKeyword();

// _tofile
  __expression = new BNFExpression(_tofile);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('F'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(_tofile);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('F'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  _tofile->SetKeyword();

// _todb
  __expression = new BNFExpression(_todb);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('b'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(_todb);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('B'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  _todb->SetKeyword();

// _use
  __expression = new BNFExpression(_use);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(_use);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  _use->SetKeyword();

// _database
  __expression = new BNFExpression(_database);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('b'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(_database);
    __expression->AddElement(__database,NO,1,NO,YES);

// __database
  __expression = new BNFExpression(__database);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('B'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  __database->SetKeyword();

// _datasource
  __expression = new BNFExpression(_datasource);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(_datasource);
    __expression->AddElement(__datasource,NO,1,NO,YES);

// __datasource
  __expression = new BNFExpression(__datasource);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  __datasource->SetKeyword();

// schema
  __expression = new BNFExpression(schema);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('h'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('m'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,YES);
  __expression = new BNFExpression(schema);
    __expression->AddElement(__schema,NO,1,NO,YES);

// __schema
  __expression = new BNFExpression(__schema);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('H'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('M'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,YES);
  __schema->SetKeyword();

// update
  __expression = new BNFExpression(update);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(update);
    __expression->AddElement(__update,NO,1,NO,YES);

// __update
  __expression = new BNFExpression(__update);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('P'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  __update->SetKeyword();

// multiple_key
  __expression = new BNFExpression(multiple_key);
    __expression->AddElement(ElementaryToken('m'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('k'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('y'),NO,1,YES,YES);
  __expression = new BNFExpression(multiple_key);
    __expression->AddElement(__multiple_key,NO,1,NO,YES);

// __multiple_key
  __expression = new BNFExpression(__multiple_key);
    __expression->AddElement(ElementaryToken('M'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('P'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('K'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('Y'),NO,1,NO,YES);
  __multiple_key->SetKeyword();

// no_create
  __expression = new BNFExpression(no_create);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(no_create);
    __expression->AddElement(__no_create,NO,1,NO,YES);

// __no_create
  __expression = new BNFExpression(__no_create);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  __no_create->SetKeyword();

// ordered_by
  __expression = new BNFExpression(ordered_by);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('b'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('y'),NO,1,YES,YES);
  __expression = new BNFExpression(ordered_by);
    __expression->AddElement(__ordered_by,NO,1,NO,YES);

// __ordered_by
  __expression = new BNFExpression(__ordered_by);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('B'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('Y'),NO,1,NO,YES);
  __ordered_by->SetKeyword();

// unique
  __expression = new BNFExpression(unique);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('q'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(unique);
    __expression->AddElement(__unique,NO,1,NO,YES);

// __unique
  __expression = new BNFExpression(__unique);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('Q'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  __unique->SetKeyword();

// not_empty
  __expression = new BNFExpression(not_empty);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('m'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('y'),NO,1,YES,YES);
  __expression = new BNFExpression(not_empty);
    __expression->AddElement(__not_empty,NO,1,NO,YES);

// __not_empty
  __expression = new BNFExpression(__not_empty);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('M'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('P'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('Y'),NO,1,NO,YES);
  __not_empty->SetKeyword();

// temporary
  __expression = new BNFExpression(temporary);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('m'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('y'),NO,1,YES,YES);
  __expression = new BNFExpression(temporary);
    __expression->AddElement(__temporary,NO,1,NO,YES);

// __temporary
  __expression = new BNFExpression(__temporary);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('M'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('P'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('Y'),NO,1,NO,YES);
  __temporary->SetKeyword();

// guid
  __expression = new BNFExpression(guid);
    __expression->AddElement(ElementaryToken('g'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,YES);
  __expression = new BNFExpression(guid);
    __expression->AddElement(__guid,NO,1,NO,YES);

// __guid
  __expression = new BNFExpression(__guid);
    __expression->AddElement(ElementaryToken('G'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,YES);
  __guid->SetKeyword();

// weak_typed
  __expression = new BNFExpression(weak_typed);
    __expression->AddElement(ElementaryToken('w'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('k'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('y'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,YES);
  __expression = new BNFExpression(weak_typed);
    __expression->AddElement(__weak_typed,NO,1,NO,YES);

// __weak_typed
  __expression = new BNFExpression(__weak_typed);
    __expression->AddElement(ElementaryToken('W'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('K'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('Y'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('P'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,YES);
  __weak_typed->SetKeyword();

// owner
  __expression = new BNFExpression(owner);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('w'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,YES);
  __expression = new BNFExpression(owner);
    __expression->AddElement(__owner,NO,1,NO,YES);

// __owner
  __expression = new BNFExpression(__owner);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('W'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,YES);
  __owner->SetKeyword();

// shared
  __expression = new BNFExpression(shared);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('h'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,YES);
  __expression = new BNFExpression(shared);
    __expression->AddElement(__shared,NO,1,NO,YES);

// __shared
  __expression = new BNFExpression(__shared);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('H'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,YES);
  __shared->SetKeyword();

// dependent
  __expression = new BNFExpression(dependent);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  __expression = new BNFExpression(dependent);
    __expression->AddElement(__dependent,NO,1,NO,YES);

// __dependent
  __expression = new BNFExpression(__dependent);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('P'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,YES);
  __dependent->SetKeyword();

// secondary
  __expression = new BNFExpression(secondary);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('y'),NO,1,YES,YES);
  __expression = new BNFExpression(secondary);
    __expression->AddElement(__secondary,NO,1,NO,YES);

// __secondary
  __expression = new BNFExpression(__secondary);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('Y'),NO,1,NO,YES);
  __secondary->SetKeyword();

// based_on
  __expression = new BNFExpression(based_on);
    __expression->AddElement(ElementaryToken('b'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,YES);
  __expression = new BNFExpression(based_on);
    __expression->AddElement(__based_on,NO,1,NO,YES);

// __based_on
  __expression = new BNFExpression(__based_on);
    __expression->AddElement(ElementaryToken('B'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,YES);
  __based_on->SetKeyword();

// subset
  __expression = new BNFExpression(subset);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('b'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  __expression = new BNFExpression(subset);
    __expression->AddElement(__subset,NO,1,NO,YES);

// __subset
  __expression = new BNFExpression(__subset);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('B'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,YES);
  __subset->SetKeyword();

// superset
  __expression = new BNFExpression(superset);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  __expression = new BNFExpression(superset);
    __expression->AddElement(__superset,NO,1,NO,YES);

// __superset
  __expression = new BNFExpression(__superset);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('P'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,YES);
  __superset->SetKeyword();

// ident_key
  __expression = new BNFExpression(ident_key);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('k'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('y'),NO,1,YES,YES);
  __expression = new BNFExpression(ident_key);
    __expression->AddElement(__ident_key,NO,1,NO,YES);

// __ident_key
  __expression = new BNFExpression(__ident_key);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('K'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('Y'),NO,1,NO,YES);
  __ident_key->SetKeyword();

// complete
  __expression = new BNFExpression(complete);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('m'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(complete);
    __expression->AddElement(__complete,NO,1,NO,YES);

// __complete
  __expression = new BNFExpression(__complete);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('M'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('P'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  __complete->SetKeyword();

// distinct
  __expression = new BNFExpression(distinct);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  __expression = new BNFExpression(distinct);
    __expression->AddElement(__distinct,NO,1,NO,YES);

// __distinct
  __expression = new BNFExpression(__distinct);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,YES);
  __distinct->SetKeyword();

// intersect
  __expression = new BNFExpression(intersect);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  __expression = new BNFExpression(intersect);
    __expression->AddElement(__intersect,NO,1,NO,YES);

// __intersect
  __expression = new BNFExpression(__intersect);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,YES);
  __intersect->SetKeyword();

// ignore_case
  __expression = new BNFExpression(ignore_case);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('g'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(ignore_case);
    __expression->AddElement(__ignore_case,NO,1,NO,YES);

// __ignore_case
  __expression = new BNFExpression(__ignore_case);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('G'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  __ignore_case->SetKeyword();

// descending
  __expression = new BNFExpression(descending);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('g'),NO,1,YES,YES);
  __expression = new BNFExpression(descending);
    __expression->AddElement(__descending,NO,1,NO,YES);

// __descending
  __expression = new BNFExpression(__descending);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('G'),NO,1,NO,YES);
  __descending->SetKeyword();

// interval
  __expression = new BNFExpression(interval);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('v'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,YES);
  __expression = new BNFExpression(interval);
    __expression->AddElement(__interval,NO,1,NO,YES);

// __interval
  __expression = new BNFExpression(__interval);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('V'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,YES);
  __interval->SetKeyword();

// _constraint
  __expression = new BNFExpression(_constraint);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  __expression = new BNFExpression(_constraint);
    __expression->AddElement(__constraint,NO,1,NO,YES);

// __constraint
  __expression = new BNFExpression(__constraint);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,YES);
  __constraint->SetKeyword();

// _alignment
  __expression = new BNFExpression(_alignment);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('g'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('m'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  __expression = new BNFExpression(_alignment);
    __expression->AddElement(__alignment,NO,1,NO,YES);

// __alignment
  __expression = new BNFExpression(__alignment);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('G'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('M'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,YES);
  __alignment->SetKeyword();

// delete_empty
  __expression = new BNFExpression(delete_empty);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('m'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('y'),NO,1,YES,YES);
  __expression = new BNFExpression(delete_empty);
    __expression->AddElement(__delete_empty,NO,1,NO,YES);

// __delete_empty
  __expression = new BNFExpression(__delete_empty);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('M'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('P'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('Y'),NO,1,NO,YES);
  __delete_empty->SetKeyword();

// _source
  __expression = new BNFExpression(_source);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(_source);
    __expression->AddElement(__source,NO,1,NO,YES);

// __source
  __expression = new BNFExpression(__source);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  __source->SetKeyword();

// _version
  __expression = new BNFExpression(_version);
    __expression->AddElement(ElementaryToken('v'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,YES);
  __expression = new BNFExpression(_version);
    __expression->AddElement(__version,NO,1,NO,YES);

// __version
  __expression = new BNFExpression(__version);
    __expression->AddElement(ElementaryToken('V'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,YES);
  __version->SetKeyword();

// OQLExpression
  __expression = new BNFExpression(OQLExpression);
    __expression->AddElement(meth_dcl,YES,1,YES,YES);
    __expression->AddElement(expr_code,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),YES,1,NO,YES);

// method
  __expression = new BNFExpression(method);
    __expression->AddElement(block_intro,YES,UNDEF,YES,YES);
    __expression->AddElement(method_spec,NO,1,YES,YES);

// method_spec
  __expression = new BNFExpression(method_spec);
    __expression->AddElement(doc_template,NO,1,YES,YES);
  __expression = new BNFExpression(method_spec);
    __expression->AddElement(expression,NO,1,YES,YES);
  __expression = new BNFExpression(method_spec);
    __expression->AddElement(cpp_function,NO,1,YES,YES);
  __expression = new BNFExpression(method_spec);
    __expression->AddElement(window,NO,1,YES,YES);
  __expression = new BNFExpression(method_spec);
    __expression->AddElement(control,NO,1,YES,YES);

// block_intro
  __expression = new BNFExpression(block_intro);
    __expression->AddElement(comment_block,NO,1,YES,YES);
  __expression = new BNFExpression(block_intro);
    __expression->AddElement(pragma,NO,1,YES,YES);
  __expression = new BNFExpression(block_intro);
    __expression->AddElement(member,NO,1,YES,YES);
  __expression = new BNFExpression(block_intro);
    __expression->AddElement(file_reference,NO,1,YES,YES);

// file_reference
  __expression = new BNFExpression(file_reference);
    __expression->AddElement(_include,NO,1,NO,YES);
    __expression->AddElement(string,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// pragma
  __expression = new BNFExpression(pragma);
    __expression->AddElement(ElementaryToken('#'),NO,1,NO,YES);
    __expression->AddElement(multiple_line,NO,1,YES,YES);

// doc_template
  __expression = new BNFExpression(doc_template);
    __expression->AddElement(ElementaryToken('<'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('m'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('>'),NO,1,NO,YES);
    __expression->AddElement(dct_header,NO,1,YES,YES);
    __expression->AddElement(dct_variables,YES,1,YES,YES);
    __expression->AddElement(dct_spec,YES,1,YES,YES);
    __expression->AddElement(ElementaryToken('<'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('/'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('m'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('>'),NO,1,NO,YES);

// dct_header
  __expression = new BNFExpression(dct_header);
    __expression->AddElement(ElementaryToken('<'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('h'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('>'),NO,1,NO,YES);
    __expression->AddElement(meth_dcl,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken('<'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('/'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('h'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('>'),NO,1,NO,YES);

// dct_variables
  __expression = new BNFExpression(dct_variables);
    __expression->AddElement(ElementaryToken('<'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('v'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('b'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('>'),NO,1,NO,YES);
    __expression->AddElement(member,NO,UNDEF,YES,YES);
    __expression->AddElement(ElementaryToken('<'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('/'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('v'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('b'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('>'),NO,1,NO,YES);

// dct_spec
  __expression = new BNFExpression(dct_spec);
    __expression->AddElement(fixed_text,NO,1,YES,YES);
  __expression = new BNFExpression(dct_spec);
    __expression->AddElement(extended_text,NO,UNDEF,YES,YES);

// fixed_text
  __expression = new BNFExpression(fixed_text);
    __expression->AddElement(anychar,NO,UNDEF,YES,YES);

// extended_text
  __expression = new BNFExpression(extended_text);
    __expression->AddElement(fixed_text,YES,1,YES,YES);
    __expression->AddElement(imbedded_expr,NO,1,YES,YES);

// imbedded_expr
  __expression = new BNFExpression(imbedded_expr);
    __expression->AddElement(comp_expr,NO,1,YES,YES);
  __expression = new BNFExpression(imbedded_expr);
    __expression->AddElement(output_expr,NO,1,YES,YES);

// output_expr
  __expression = new BNFExpression(output_expr);
    __expression->AddElement(ElementaryToken('<'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken(':'),NO,1,NO,YES);
    __expression->AddElement(expr_element,NO,UNDEF,YES,YES);
    __expression->AddElement(ElementaryToken(':'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('>'),NO,1,NO,YES);

// comp_expr
  __expression = new BNFExpression(comp_expr);
    __expression->AddElement(ElementaryToken('<'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('%'),NO,1,NO,YES);
    __expression->AddElement(expr_element,NO,UNDEF,YES,YES);
    __expression->AddElement(ElementaryToken('%'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('>'),NO,1,NO,YES);

// expr_element
  __expression = new BNFExpression(expr_element);
    __expression->AddElement(member,NO,1,YES,YES);
  __expression = new BNFExpression(expr_element);
    __expression->AddElement(statement,NO,1,YES,YES);

// expression
  __expression = new BNFExpression(expression);
    __expression->AddElement(_expression,NO,1,NO,YES);
    __expression->AddElement(expr_spec,NO,1,YES,YES);

// expr_spec
  __expression = new BNFExpression(expr_spec);
    __expression->AddElement(expr_dcl,NO,1,YES,YES);
  __expression = new BNFExpression(expr_spec);
    __expression->AddElement(expr_def,NO,1,YES,YES);

// expr_dcl
  __expression = new BNFExpression(expr_dcl);
    __expression->AddElement(meth_dcl,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// expr_def
  __expression = new BNFExpression(expr_def);
    __expression->AddElement(meth_dcl,NO,1,YES,YES);
    __expression->AddElement(expr_code,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),YES,1,NO,YES);

// var_defs
  __expression = new BNFExpression(var_defs);
    __expression->AddElement(_variables,NO,1,NO,YES);
    __expression->AddElement(member,YES,UNDEF,YES,YES);

// init_code
  __expression = new BNFExpression(init_code);
    __expression->AddElement(_init,NO,1,NO,YES);
    __expression->AddElement(statement,YES,UNDEF,YES,YES);

// proc_code
  __expression = new BNFExpression(proc_code);
    __expression->AddElement(_process,YES,1,NO,YES);
    __expression->AddElement(statement,NO,UNDEF,YES,YES);

// error_code
  __expression = new BNFExpression(error_code);
    __expression->AddElement(_on_error,NO,1,NO,YES);
    __expression->AddElement(statement,YES,UNDEF,YES,YES);

// final_code
  __expression = new BNFExpression(final_code);
    __expression->AddElement(_final,NO,1,NO,YES);
    __expression->AddElement(statement,YES,UNDEF,YES,YES);

// OQLSelect
  __expression = new BNFExpression(OQLSelect);
    __expression->AddElement(sel_spec,NO,1,YES,YES);
    __expression->AddElement(from_spec,NO,1,YES,YES);
    __expression->AddElement(sel_extensions,YES,UNDEF,YES,YES);
    __expression->AddElement(output_spec,YES,1,YES,YES);

// sel_spec
  __expression = new BNFExpression(sel_spec);
    __expression->AddElement(_select,NO,1,NO,YES);
    __expression->AddElement(operand_list,NO,1,YES,YES);

// sel_extensions
  __expression = new BNFExpression(sel_extensions);
    __expression->AddElement(where_spec,NO,1,YES,YES);
  __expression = new BNFExpression(sel_extensions);
    __expression->AddElement(having_spec,NO,1,YES,YES);
  __expression = new BNFExpression(sel_extensions);
    __expression->AddElement(group_spec,NO,1,YES,YES);
  __expression = new BNFExpression(sel_extensions);
    __expression->AddElement(order_spec,NO,1,YES,YES);

// output_spec
  __expression = new BNFExpression(output_spec);
    __expression->AddElement(to_file,NO,1,YES,YES);
  __expression = new BNFExpression(output_spec);
    __expression->AddElement(to_database,NO,1,YES,YES);

// to_file
  __expression = new BNFExpression(to_file);
    __expression->AddElement(_tofile,NO,1,NO,YES);
    __expression->AddElement(operand_list,NO,1,YES,YES);

// to_database
  __expression = new BNFExpression(to_database);
    __expression->AddElement(_todb,NO,1,NO,YES);
    __expression->AddElement(operand_list,NO,1,YES,YES);

// cpp_function
  __expression = new BNFExpression(cpp_function);
    __expression->AddElement(funct_dcl,NO,1,YES,YES);
  __expression = new BNFExpression(cpp_function);
    __expression->AddElement(funct_def,NO,1,YES,YES);

// funct_dcl
  __expression = new BNFExpression(funct_dcl);
    __expression->AddElement(meth_dcl,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// funct_def
  __expression = new BNFExpression(funct_def);
    __expression->AddElement(meth_dcl,NO,1,YES,YES);
    __expression->AddElement(function_text,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),YES,1,NO,YES);

// function_text
  __expression = new BNFExpression(function_text);
    __expression->AddElement(ini_code,YES,1,YES,YES);
    __expression->AddElement(function_block,NO,1,YES,YES);

// ini_code
  __expression = new BNFExpression(ini_code);
    __expression->AddElement(ElementaryToken(':'),NO,1,NO,YES);
    __expression->AddElement(ini_line,NO,UNDEF,YES,YES);

// ini_line
  __expression = new BNFExpression(ini_line);
    __expression->AddElement(blockstring,NO,1,YES,YES);
  __expression = new BNFExpression(ini_line);
    __expression->AddElement(string,NO,1,YES,YES);
  __expression = new BNFExpression(ini_line);
    __expression->AddElement(comment_block,NO,1,YES,YES);

// function_block
  __expression = new BNFExpression(function_block);
    __expression->AddElement(ElementaryToken('{'),NO,1,NO,YES);
    __expression->AddElement(fct_line,YES,UNDEF,YES,YES);
    __expression->AddElement(ElementaryToken('}'),NO,1,NO,YES);

// fct_line
  __expression = new BNFExpression(fct_line);
    __expression->AddElement(comment_block,NO,1,YES,YES);
  __expression = new BNFExpression(fct_line);
    __expression->AddElement(function_block,NO,1,YES,YES);
  __expression = new BNFExpression(fct_line);
    __expression->AddElement(string,NO,1,YES,YES);
  __expression = new BNFExpression(fct_line);
    __expression->AddElement(blockstring,NO,1,YES,YES);
  __expression = new BNFExpression(fct_line);
    __expression->AddElement(_process,NO,1,NO,YES);
  __expression = new BNFExpression(fct_line);
    __expression->AddElement(_on_error,NO,1,NO,YES);
  __expression = new BNFExpression(fct_line);
    __expression->AddElement(_final,NO,1,NO,YES);

// window
  __expression = new BNFExpression(window);
    __expression->AddElement(_window,NO,1,NO,YES);
    __expression->AddElement(identifier,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),YES,1,NO,YES);

// control
  __expression = new BNFExpression(control);
    __expression->AddElement(_control,NO,1,NO,YES);
    __expression->AddElement(identifier,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),YES,1,NO,YES);

// if_block
  __expression = new BNFExpression(if_block);
    __expression->AddElement(_if,NO,1,NO,YES);
    __expression->AddElement(condition,NO,1,YES,YES);
    __expression->AddElement(bstatement,NO,1,YES,YES);
    __expression->AddElement(else_stmt,YES,1,YES,YES);

// else_stmt
  __expression = new BNFExpression(else_stmt);
    __expression->AddElement(debug_opt,YES,1,YES,YES);
    __expression->AddElement(_else,NO,1,NO,YES);
    __expression->AddElement(bstatement,NO,1,YES,YES);

// while_block
  __expression = new BNFExpression(while_block);
    __expression->AddElement(_while,NO,1,NO,YES);
    __expression->AddElement(condition,NO,1,YES,YES);
    __expression->AddElement(bstatement,NO,1,YES,YES);

// for_block
  __expression = new BNFExpression(for_block);
    __expression->AddElement(_for,NO,1,NO,YES);
    __expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    __expression->AddElement(basic_stmt,NO,1,YES,YES);
    __expression->AddElement(basic_stmt,NO,1,YES,YES);
    __expression->AddElement(stmt_operlist,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);
    __expression->AddElement(bstatement,NO,1,YES,YES);

// case_block
  __expression = new BNFExpression(case_block);
    __expression->AddElement(_switch,NO,1,NO,YES);
    __expression->AddElement(condition,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken('{'),NO,1,NO,YES);
    __expression->AddElement(case_stmt,YES,UNDEF,YES,YES);
    __expression->AddElement(other_stmt,YES,1,YES,YES);
    __expression->AddElement(ElementaryToken('}'),NO,1,NO,YES);

// case_stmt
  __expression = new BNFExpression(case_stmt);
    __expression->AddElement(debug_opt,YES,1,YES,YES);
    __expression->AddElement(_case,NO,1,NO,YES);
    __expression->AddElement(simple_op,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(':'),NO,1,NO,YES);
    __expression->AddElement(statement,NO,UNDEF,YES,YES);

// other_stmt
  __expression = new BNFExpression(other_stmt);
    __expression->AddElement(debug_opt,YES,1,YES,YES);
    __expression->AddElement(_default,NO,1,NO,YES);
    __expression->AddElement(ElementaryToken(':'),NO,1,NO,YES);
    __expression->AddElement(statement,NO,UNDEF,YES,YES);

// condition
  __expression = new BNFExpression(condition);
    __expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    __expression->AddElement(doperand,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);

// bstatement
  __expression = new BNFExpression(bstatement);
    __expression->AddElement(block,NO,1,YES,YES);
  __expression = new BNFExpression(bstatement);
    __expression->AddElement(statement,NO,1,YES,YES);

// statement
  __expression = new BNFExpression(statement);
    __expression->AddElement(debug_opt,YES,1,YES,YES);
    __expression->AddElement(istatement,NO,1,YES,YES);

// istatement
  __expression = new BNFExpression(istatement);
    __expression->AddElement(basic_stmt,NO,1,YES,YES);
  __expression = new BNFExpression(istatement);
    __expression->AddElement(if_block,NO,1,YES,YES);
  __expression = new BNFExpression(istatement);
    __expression->AddElement(case_block,NO,1,YES,YES);
  __expression = new BNFExpression(istatement);
    __expression->AddElement(while_block,NO,1,YES,YES);
  __expression = new BNFExpression(istatement);
    __expression->AddElement(for_block,NO,1,YES,YES);
  __expression = new BNFExpression(istatement);
    __expression->AddElement(syntax_op,NO,1,YES,YES);
  __expression = new BNFExpression(istatement);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// basic_stmt
  __expression = new BNFExpression(basic_stmt);
    __expression->AddElement(stmt_operlist,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// stmt_operlist
  __expression = new BNFExpression(stmt_operlist);
    __expression->AddElement(doperand,NO,1,YES,YES);
    __expression->AddElement(stoplist_ext,YES,UNDEF,YES,YES);

// stoplist_ext
  __expression = new BNFExpression(stoplist_ext);
    __expression->AddElement(ElementaryToken(','),NO,1,NO,YES);
    __expression->AddElement(doperand,NO,1,YES,YES);

// doperand
  __expression = new BNFExpression(doperand);
    __expression->AddElement(debug_opt,YES,1,YES,YES);
    __expression->AddElement(operand,NO,1,YES,YES);

// debug_opt
  __expression = new BNFExpression(debug_opt);
    __expression->AddElement(ElementaryToken('#'),NO,1,NO,YES);
    __expression->AddElement(auto_run,YES,1,YES,YES);

// auto_run
  __expression = new BNFExpression(auto_run);
    __expression->AddElement(ElementaryToken(':'),NO,1,NO,YES);
    __expression->AddElement(identifier,NO,1,YES,YES);

// syntax_op
  __expression = new BNFExpression(syntax_op);
    __expression->AddElement(return_op,NO,1,YES,YES);
  __expression = new BNFExpression(syntax_op);
    __expression->AddElement(error_op,NO,1,YES,YES);
  __expression = new BNFExpression(syntax_op);
    __expression->AddElement(leave_op,NO,1,YES,YES);
  __expression = new BNFExpression(syntax_op);
    __expression->AddElement(continue_op,NO,1,YES,YES);
  __expression = new BNFExpression(syntax_op);
    __expression->AddElement(break_op,NO,1,YES,YES);
  __expression = new BNFExpression(syntax_op);
    __expression->AddElement(exception_op,NO,1,YES,YES);
  __expression = new BNFExpression(syntax_op);
    __expression->AddElement(nv_op,NO,1,YES,YES);
  __expression = new BNFExpression(syntax_op);
    __expression->AddElement(eh_op,NO,1,YES,YES);

// return_op
  __expression = new BNFExpression(return_op);
    __expression->AddElement(_return,NO,1,NO,YES);
    __expression->AddElement(operand,YES,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// error_op
  __expression = new BNFExpression(error_op);
    __expression->AddElement(_error,NO,1,NO,YES);
    __expression->AddElement(operand,YES,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// eh_op
  __expression = new BNFExpression(eh_op);
    __expression->AddElement(_exceptions,NO,1,NO,YES);
    __expression->AddElement(operand,YES,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// nv_op
  __expression = new BNFExpression(nv_op);
    __expression->AddElement(_null_value,NO,1,NO,YES);
    __expression->AddElement(operand,YES,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// nv_handling
  __expression = new BNFExpression(nv_handling);
    __expression->AddElement(_accept,NO,1,NO,YES);
  __expression = new BNFExpression(nv_handling);
    __expression->AddElement(_ignore,NO,1,NO,YES);
  __expression = new BNFExpression(nv_handling);
    __expression->AddElement(_exception,NO,1,NO,YES);

// exception_op
  __expression = new BNFExpression(exception_op);
    __expression->AddElement(_exception,NO,1,NO,YES);
    __expression->AddElement(operand,YES,1,YES,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// leave_op
  __expression = new BNFExpression(leave_op);
    __expression->AddElement(_leave_,NO,1,NO,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// break_op
  __expression = new BNFExpression(break_op);
    __expression->AddElement(_break,NO,1,NO,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// continue_op
  __expression = new BNFExpression(continue_op);
    __expression->AddElement(_continue,NO,1,NO,YES);
    __expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// access_path
  __expression = new BNFExpression(access_path);
    __expression->AddElement(path_element,NO,1,YES,YES);
    __expression->AddElement(path_extension,YES,UNDEF,YES,YES);

// path_extension
  __expression = new BNFExpression(path_extension);
    __expression->AddElement(ext_op,NO,1,YES,YES);
    __expression->AddElement(path_element,NO,1,YES,YES);

// ext_op
  __expression = new BNFExpression(ext_op);
    __expression->AddElement(ElementaryToken('.'),NO,1,NO,YES);
  __expression = new BNFExpression(ext_op);
    __expression->AddElement(ElementaryToken('@'),NO,1,NO,YES);
  __expression = new BNFExpression(ext_op);
    __expression->AddElement(ElementaryToken('-'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('>'),NO,1,NO,YES);
  ext_op->SetTerminal();

// path_element
  __expression = new BNFExpression(path_element);
    __expression->AddElement(path_operand,NO,1,YES,YES);
    __expression->AddElement(operand_list,YES,1,YES,YES);

// path_operand
  __expression = new BNFExpression(path_operand);
    __expression->AddElement(path_name,NO,1,YES,YES);
  __expression = new BNFExpression(path_operand);
    __expression->AddElement(coll_operand,NO,1,YES,YES);
  __expression = new BNFExpression(path_operand);
    __expression->AddElement(expr_code,NO,1,YES,YES);

// path_name
  __expression = new BNFExpression(path_name);
    __expression->AddElement(pname,NO,1,YES,YES);
    __expression->AddElement(name_index,YES,1,YES,YES);

// oql_oper
  __expression = new BNFExpression(oql_oper);
    __expression->AddElement(_select,NO,1,NO,YES);
  __expression = new BNFExpression(oql_oper);
    __expression->AddElement(_from,NO,1,NO,YES);
  __expression = new BNFExpression(oql_oper);
    __expression->AddElement(_where,NO,1,NO,YES);
  __expression = new BNFExpression(oql_oper);
    __expression->AddElement(_having,NO,1,NO,YES);
  __expression = new BNFExpression(oql_oper);
    __expression->AddElement(_group_by,NO,1,NO,YES);
  __expression = new BNFExpression(oql_oper);
    __expression->AddElement(_order_by,NO,1,NO,YES);
  __expression = new BNFExpression(oql_oper);
    __expression->AddElement(_join,NO,1,NO,YES);
  __expression = new BNFExpression(oql_oper);
    __expression->AddElement(_union,NO,1,NO,YES);
  __expression = new BNFExpression(oql_oper);
    __expression->AddElement(_minus,NO,1,NO,YES);
  __expression = new BNFExpression(oql_oper);
    __expression->AddElement(_intersect,NO,1,NO,YES);
  __expression = new BNFExpression(oql_oper);
    __expression->AddElement(_tofile,NO,1,NO,YES);
  __expression = new BNFExpression(oql_oper);
    __expression->AddElement(_todb,NO,1,NO,YES);
  __expression = new BNFExpression(oql_oper);
    __expression->AddElement(_use,NO,1,NO,YES);

// name_index
  __expression = new BNFExpression(name_index);
    __expression->AddElement(ElementaryToken('['),NO,1,NO,YES);
    __expression->AddElement(operand,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(']'),NO,1,NO,YES);

// coll_operand
  __expression = new BNFExpression(coll_operand);
    __expression->AddElement(ElementaryToken('['),NO,1,NO,YES);
    __expression->AddElement(access_path,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(']'),NO,1,NO,YES);

// operand_list
  __expression = new BNFExpression(operand_list);
    __expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    __expression->AddElement(parm_list,YES,1,YES,YES);
    __expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);

// operand
  __expression = new BNFExpression(operand);
    __expression->AddElement(un_operation,NO,1,YES,YES);
    __expression->AddElement(bin_operand,YES,1,YES,YES);

// bin_operand
  __expression = new BNFExpression(bin_operand);
    __expression->AddElement(bin_op,NO,1,YES,YES);
    __expression->AddElement(operand,NO,1,YES,YES);

// un_operation
  __expression = new BNFExpression(un_operation);
    __expression->AddElement(un_oper,YES,1,YES,YES);
    __expression->AddElement(simple_op,NO,1,YES,YES);

// un_oper
  __expression = new BNFExpression(un_oper);
    __expression->AddElement(un_op,NO,1,YES,YES);
  __expression = new BNFExpression(un_oper);
    __expression->AddElement(cast_op,NO,1,YES,YES);

// cast_op
  __expression = new BNFExpression(cast_op);
    __expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    __expression->AddElement(simple_type_spec,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);

// simple_op
  __expression = new BNFExpression(simple_op);
    __expression->AddElement(OQLSelect,NO,1,NO,YES);
  __expression = new BNFExpression(simple_op);
    __expression->AddElement(access_path,NO,1,YES,YES);
  __expression = new BNFExpression(simple_op);
    __expression->AddElement(block,NO,1,YES,YES);
  __expression = new BNFExpression(simple_op);
    __expression->AddElement(sngl_operand,NO,1,YES,YES);
  __expression = new BNFExpression(simple_op);
    __expression->AddElement(constant,NO,1,YES,YES);
  __expression = new BNFExpression(simple_op);
    __expression->AddElement(sys_variable,NO,1,YES,YES);

// sngl_operand
  __expression = new BNFExpression(sngl_operand);
    __expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    __expression->AddElement(operand,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);

// sys_variable
  __expression = new BNFExpression(sys_variable);
    __expression->AddElement(ElementaryToken('%'),NO,1,NO,YES);
    __expression->AddElement(identifier,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken('%'),NO,1,NO,YES);

// pname
  __expression = new BNFExpression(pname);
    __expression->AddElement(oql_oper,NO,1,YES,YES);
  __expression = new BNFExpression(pname);
    __expression->AddElement(scoped_name,NO,1,YES,YES);
  __expression = new BNFExpression(pname);
    __expression->AddElement(db_name,NO,1,YES,YES);
  __expression = new BNFExpression(pname);
    __expression->AddElement(any_type,NO,1,YES,YES);

// scoped_name
  __expression = new BNFExpression(scoped_name);
    __expression->AddElement(identifier,NO,1,YES,YES);
    __expression->AddElement(scoped_name_ext,YES,UNDEF,YES,YES);

// scoped_name_ext
  __expression = new BNFExpression(scoped_name_ext);
    __expression->AddElement(scope_op,NO,1,YES,YES);
    __expression->AddElement(identifier,NO,1,YES,YES);

// db_name
  __expression = new BNFExpression(db_name);
    __expression->AddElement(ElementaryToken('#'),NO,1,NO,YES);
    __expression->AddElement(identifier,NO,1,YES,YES);

// identifier
  __expression = new BNFExpression(identifier);
    __expression->AddElement(name,NO,1,YES,YES);

// expr_code
  __expression = new BNFExpression(expr_code);
    __expression->AddElement(ElementaryToken('{'),NO,1,NO,YES);
    __expression->AddElement(var_defs,YES,1,YES,YES);
    __expression->AddElement(init_code,YES,1,YES,YES);
    __expression->AddElement(proc_code,NO,1,YES,YES);
    __expression->AddElement(error_code,YES,1,YES,YES);
    __expression->AddElement(final_code,YES,1,YES,YES);
    __expression->AddElement(ElementaryToken('}'),NO,1,NO,YES);

// block
  __expression = new BNFExpression(block);
    __expression->AddElement(ElementaryToken('{'),NO,1,NO,YES);
    __expression->AddElement(statement,YES,UNDEF,YES,YES);
    __expression->AddElement(ElementaryToken('}'),NO,1,NO,YES);

// _global
  __expression = new BNFExpression(_global);
    __expression->AddElement(ElementaryToken('g'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('b'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,YES);
  __expression = new BNFExpression(_global);
    __expression->AddElement(__global,NO,1,NO,YES);

// __global
  __expression = new BNFExpression(__global);
    __expression->AddElement(ElementaryToken('G'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('B'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,YES);
  __global->SetKeyword();

// _expression
  __expression = new BNFExpression(_expression);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('x'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,YES);
  __expression = new BNFExpression(_expression);
    __expression->AddElement(_expression_,NO,1,NO,YES);

// _expression_
  __expression = new BNFExpression(_expression_);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('X'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('P'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,YES);
  _expression_->SetKeyword();

// _window
  __expression = new BNFExpression(_window);
    __expression->AddElement(ElementaryToken('w'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('w'),NO,1,YES,YES);
  __expression = new BNFExpression(_window);
    __expression->AddElement(__window,NO,1,NO,YES);

// __window
  __expression = new BNFExpression(__window);
    __expression->AddElement(ElementaryToken('W'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('W'),NO,1,NO,YES);
  __window->SetKeyword();

// _control
  __expression = new BNFExpression(_control);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,YES);
  __expression = new BNFExpression(_control);
    __expression->AddElement(__control,NO,1,NO,YES);

// __control
  __expression = new BNFExpression(__control);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,YES);
  __control->SetKeyword();

// _variables
  __expression = new BNFExpression(_variables);
    __expression->AddElement(ElementaryToken('v'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('b'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,YES);
  __expression = new BNFExpression(_variables);
    __expression->AddElement(__variables,NO,1,NO,YES);

// __variables
  __expression = new BNFExpression(__variables);
    __expression->AddElement(ElementaryToken('V'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('B'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,YES);
  __variables->SetKeyword();

// _init
  __expression = new BNFExpression(_init);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  __expression = new BNFExpression(_init);
    __expression->AddElement(__init,NO,1,NO,YES);

// __init
  __expression = new BNFExpression(__init);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,YES);
  __init->SetKeyword();

// _process
  __expression = new BNFExpression(_process);
    __expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,YES);
  __expression = new BNFExpression(_process);
    __expression->AddElement(__process,NO,1,NO,YES);

// __process
  __expression = new BNFExpression(__process);
    __expression->AddElement(ElementaryToken('P'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,YES);
  __expression = new BNFExpression(__process);
    __expression->AddElement(ElementaryToken('B'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('G'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('Q'),NO,1,NO,YES);
  __process->SetKeyword();

// _on_error
  __expression = new BNFExpression(_on_error);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,YES);
  __expression = new BNFExpression(_on_error);
    __expression->AddElement(__on_error,NO,1,NO,YES);

// __on_error
  __expression = new BNFExpression(__on_error);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,YES);
  __expression = new BNFExpression(__on_error);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('V'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,YES);
  __on_error->SetKeyword();

// _final
  __expression = new BNFExpression(_final);
    __expression->AddElement(ElementaryToken('f'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,YES);
  __expression = new BNFExpression(_final);
    __expression->AddElement(__final,NO,1,NO,YES);

// __final
  __expression = new BNFExpression(__final);
    __expression->AddElement(ElementaryToken('F'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,YES);
  __expression = new BNFExpression(__final);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('Q'),NO,1,NO,YES);
  __final->SetKeyword();

// _if
  __expression = new BNFExpression(_if);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('f'),NO,1,YES,YES);
  __expression = new BNFExpression(_if);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('F'),NO,1,NO,YES);
  _if->SetKeyword();

// _else
  __expression = new BNFExpression(_else);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(_else);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  _else->SetKeyword();

// _while
  __expression = new BNFExpression(_while);
    __expression->AddElement(ElementaryToken('w'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('h'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(_while);
    __expression->AddElement(ElementaryToken('W'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('H'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  _while->SetKeyword();

// _for
  __expression = new BNFExpression(_for);
    __expression->AddElement(ElementaryToken('f'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,YES);
  __expression = new BNFExpression(_for);
    __expression->AddElement(ElementaryToken('F'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,YES);
  _for->SetKeyword();

// _continue
  __expression = new BNFExpression(_continue);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(_continue);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  _continue->SetKeyword();

// _leave_
  __expression = new BNFExpression(_leave_);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('v'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(_leave_);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('V'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  _leave_->SetKeyword();

// _break
  __expression = new BNFExpression(_break);
    __expression->AddElement(ElementaryToken('b'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('k'),NO,1,YES,YES);
  __expression = new BNFExpression(_break);
    __expression->AddElement(ElementaryToken('B'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('K'),NO,1,NO,YES);
  _break->SetKeyword();

// _error
  __expression = new BNFExpression(_error);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,YES);
  __expression = new BNFExpression(_error);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,YES);
  _error->SetKeyword();

// _return
  __expression = new BNFExpression(_return);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,YES);
  __expression = new BNFExpression(_return);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,YES);
  _return->SetKeyword();

// _null_value
  __expression = new BNFExpression(_null_value);
    __expression->AddElement(ElementaryToken('#'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('V'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(_null_value);
    __expression->AddElement(ElementaryToken('#'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('V'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('L'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('U'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  _null_value->SetKeyword();

// _exceptions
  __expression = new BNFExpression(_exceptions);
    __expression->AddElement(ElementaryToken('#'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('x'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,YES);
  __expression = new BNFExpression(_exceptions);
    __expression->AddElement(ElementaryToken('#'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('X'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('P'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('S'),NO,1,NO,YES);
  _exceptions->SetKeyword();

// _ignore
  __expression = new BNFExpression(_ignore);
    __expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('g'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  __expression = new BNFExpression(_ignore);
    __expression->AddElement(__ignore,NO,1,NO,YES);

// __ignore
  __expression = new BNFExpression(__ignore);
    __expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('G'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,YES);
  __ignore->SetKeyword();

// _accept
  __expression = new BNFExpression(_accept);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  __expression = new BNFExpression(_accept);
    __expression->AddElement(__accept,NO,1,NO,YES);

// __accept
  __expression = new BNFExpression(__accept);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('P'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,YES);
  __accept->SetKeyword();

// scope_op
  __expression = new BNFExpression(scope_op);
    __expression->AddElement(ElementaryToken(':'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken(':'),NO,1,NO,YES);
  scope_op->SetTerminal();

// cun_op
  __expression = new BNFExpression(cun_op);
    __expression->AddElement(ElementaryToken('+'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('+'),NO,1,NO,YES);
  __expression = new BNFExpression(cun_op);
    __expression->AddElement(ElementaryToken('-'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('-'),NO,1,NO,YES);
  __expression = new BNFExpression(cun_op);
    __expression->AddElement(_not,NO,1,NO,YES);
  __expression = new BNFExpression(cun_op);
    __expression->AddElement(bin_op,NO,1,YES,YES);

// un_op
  __expression = new BNFExpression(un_op);
    __expression->AddElement(ElementaryToken('-'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('-'),NO,1,NO,YES);
  __expression = new BNFExpression(un_op);
    __expression->AddElement(ElementaryToken('+'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('+'),NO,1,NO,YES);
  __expression = new BNFExpression(un_op);
    __expression->AddElement(ElementaryToken('-'),NO,1,NO,YES);
  __expression = new BNFExpression(un_op);
    __expression->AddElement(_not,NO,1,NO,YES);

// bin_op
  __expression = new BNFExpression(bin_op);
    __expression->AddElement(bin_assign_op,NO,1,YES,YES);
  __expression = new BNFExpression(bin_op);
    __expression->AddElement(ElementaryToken('^'),NO,1,NO,YES);
  __expression = new BNFExpression(bin_op);
    __expression->AddElement(ElementaryToken('%'),NO,1,NO,YES);
  __expression = new BNFExpression(bin_op);
    __expression->AddElement(ElementaryToken('+'),NO,1,NO,YES);
  __expression = new BNFExpression(bin_op);
    __expression->AddElement(ElementaryToken('-'),NO,1,NO,YES);
  __expression = new BNFExpression(bin_op);
    __expression->AddElement(ElementaryToken('*'),NO,1,NO,YES);
  __expression = new BNFExpression(bin_op);
    __expression->AddElement(ElementaryToken('/'),NO,1,NO,YES);
  __expression = new BNFExpression(bin_op);
    __expression->AddElement(_and,NO,1,NO,YES);
  __expression = new BNFExpression(bin_op);
    __expression->AddElement(_or,NO,1,NO,YES);
  __expression = new BNFExpression(bin_op);
    __expression->AddElement(_xor,NO,1,NO,YES);
  __expression = new BNFExpression(bin_op);
    __expression->AddElement(ElementaryToken('>'),NO,1,NO,YES);
  __expression = new BNFExpression(bin_op);
    __expression->AddElement(ElementaryToken('<'),NO,1,NO,YES);
  __expression = new BNFExpression(bin_op);
    __expression->AddElement(ElementaryToken('='),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('='),NO,1,NO,YES);
  __expression = new BNFExpression(bin_op);
    __expression->AddElement(ElementaryToken('<'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('='),NO,1,NO,YES);
  __expression = new BNFExpression(bin_op);
    __expression->AddElement(ElementaryToken('>'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('='),NO,1,NO,YES);
  __expression = new BNFExpression(bin_op);
    __expression->AddElement(ElementaryToken('<'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('>'),NO,1,NO,YES);
  __expression = new BNFExpression(bin_op);
    __expression->AddElement(ElementaryToken('!'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('='),NO,1,NO,YES);
  __expression = new BNFExpression(bin_op);
    __expression->AddElement(ElementaryToken('='),NO,1,NO,YES);
  __expression = new BNFExpression(bin_op);
    __expression->AddElement(assign_op,NO,1,YES,YES);

// assign_op
  __expression = new BNFExpression(assign_op);
    __expression->AddElement(ElementaryToken('='),NO,1,NO,YES);
  __expression = new BNFExpression(assign_op);
    __expression->AddElement(ElementaryToken('&'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('='),NO,1,NO,YES);
  assign_op->SetTerminal();

// bin_assign_op
  __expression = new BNFExpression(bin_assign_op);
    __expression->AddElement(ElementaryToken('+'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('='),NO,1,NO,YES);
  __expression = new BNFExpression(bin_assign_op);
    __expression->AddElement(ElementaryToken('-'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('='),NO,1,NO,YES);
  __expression = new BNFExpression(bin_assign_op);
    __expression->AddElement(ElementaryToken('*'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('='),NO,1,NO,YES);
  __expression = new BNFExpression(bin_assign_op);
    __expression->AddElement(ElementaryToken('/'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('='),NO,1,NO,YES);
  bin_assign_op->SetTerminal();

// _not
  __expression = new BNFExpression(_not);
    __expression->AddElement(_not_kw,NO,1,NO,YES);
  __expression = new BNFExpression(_not);
    __expression->AddElement(ElementaryToken('!'),NO,1,NO,YES);

// _and
  __expression = new BNFExpression(_and);
    __expression->AddElement(_and_kw,NO,1,NO,YES);
  __expression = new BNFExpression(_and);
    __expression->AddElement(ElementaryToken('&'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('&'),NO,1,NO,YES);

// _or
  __expression = new BNFExpression(_or);
    __expression->AddElement(_or_kw,NO,1,NO,YES);
  __expression = new BNFExpression(_or);
    __expression->AddElement(ElementaryToken('|'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('|'),NO,1,NO,YES);

// _not_kw
  __expression = new BNFExpression(_not_kw);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);
  __expression = new BNFExpression(_not_kw);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('T'),NO,1,NO,YES);
  _not_kw->SetKeyword();

// _and_kw
  __expression = new BNFExpression(_and_kw);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('d'),NO,1,YES,YES);
  __expression = new BNFExpression(_and_kw);
    __expression->AddElement(ElementaryToken('A'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('D'),NO,1,NO,YES);
  _and_kw->SetKeyword();

// _or_kw
  __expression = new BNFExpression(_or_kw);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,YES);
  __expression = new BNFExpression(_or_kw);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,YES);
  _or_kw->SetKeyword();

// _xor
  __expression = new BNFExpression(_xor);
    __expression->AddElement(ElementaryToken('x'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,YES);
  __expression = new BNFExpression(_xor);
    __expression->AddElement(ElementaryToken('X'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('R'),NO,1,NO,YES);
  _xor->SetKeyword();

// CC
  SetCC("//");

// comment_block
  __expression = new BNFExpression(comment_block);
    __expression->AddElement(ElementaryToken('/'),NO,1,NO,YES);
    __expression->AddElement(ElementaryToken('*'),NO,1,NO,YES);
    __expression->AddElement(comment_next,NO,1,YES,YES);

// comment_next
  __expression = new BNFExpression(comment_next);
    __expression->AddElement(comment_end,NO,1,YES,YES);
  __expression = new BNFExpression(comment_next);
    __expression->AddElement(comment_cont,NO,1,YES,YES);

// comment_cont
  __expression = new BNFExpression(comment_cont);
    __expression->AddElement(anychar,NO,1,YES,YES);
    __expression->AddElement(comment_next,NO,1,YES,YES);

// comment_end
  __expression = new BNFExpression(comment_end);
    __expression->AddElement(ElementaryToken('*'),NO,1,NO,YES);
    __expression->AddElement(ElementaryToken('/'),NO,1,NO,YES);

  if ( !bs_parent || bs_parent == this )
    ReorderSymbols();


};
