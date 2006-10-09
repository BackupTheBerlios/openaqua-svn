/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    BNF_cpp

\brief    


\date     $Date: 2006/03/12 19:21:14,93 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "BNF_cpp"

#include  <pdefault.h>
#include  <sBNFParser.hpp>
#include  <sBNFSpecialSymbols.hpp>
#include  <sBNFStandardSymbols.hpp>
#include  <sBNF_cpp.hpp>


/******************************************************************************/
/**
\brief  BNF_cpp


\param  bs_parent - Parent parser
\param  trace_path - Trace file location
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BNF_cpp"

                        BNF_cpp :: BNF_cpp (BNFParser *bs_parent, char *trace_path )
                     : BNFParser ("cpp",bs_parent,YES,NO,trace_path)
{
  BNFExpression *expression;

/*
cpp             := block(*)
block           := comment | function_block | class_def | type_def | directive | comment_block

directive       := '#' name linechars [line_ext(*)] [nl]

type_def        := 'typedef' anychars ';'

class_def       := 'class' class_name [class_members] [name_list] ';'
class_members   := base_classes class_body | class_body
base_classes    := ':' base_class [bc_list(*)]
bc_list         := ',' base_class
base_class      := qbase_class | class_name
qbase_class     := qualifier(*) class_name
class_body      := '{' cd_text '}'
cd_text         := comment | comment_block | member_decl(*)
member_decl     := member_defin | member_qualifier | inline_funct 
inline_funct    := function_block | scope_qualifier ':' function_block 
member_qualifier:= scope_qualifier ':' member_defin
member_defin    := member_options(*) member_defin1 | member_defin1
member_defin1   := member_def [member_attr(*)] ';' [comment]
member_attr     := array_dim | bit_count | member_options | attr_ext 
bit_count       := ':' num_var
array_dim       := '[' num_var ']'
num_var         := number | name
attr_ext        := fct_call

function_block  := member_def [function_init] fblock
function_init   := ':' fct_call [call_ext(*)]
call_ext        := ',' fct_call
fct_call        := fct_name [call_parms]
parm_text       := call_parms | operstring
call_parms      := '(' [parm_text(*)] ')' 

member_def      := member_spec | type_name [refptr(*)] member_spec
type_name       := name [gen_parms]
gen_parms       := '(' parm_text ')' | '<' parm_text '>'
member_spec     := member_head | scope_member
scope_member    := class_name '::' member_head
member_head     := fct_name [tparm_list]
fct_name        := '~' name | name 

fct_line        := comment | comment_block | fblock | blockstring | begin_line | recover_line | end_line
begin_line      := 'BEGINSEQ' 
recover_line    := 'RECOVER' 
end_line        := 'ENDSEQ' 
fblock          := '{' [fct_line(*)] '}'

comment         := '//' linechars [line_ext(*)]
comment_block   := '/*' anychars end_comment
end_comment     := '* /'
line_ext        := '\\' linechars

tparm_list      := '(' [type_parms] ')'
type_parms      := type_parm [tparm_ext(*)]
tparm_ext       := ',' type_parm
type_parm       := type_name [refptr(*)] name

name_list       := name [name_ext(*)] name
refptr          := '&' | '*'
name_ext        := ',' name
qualifier       := scope_qualifier | member_options
member_options  := 'virtual' | 'static' | 'const'
scope_qualifier := 'public' | 'private' | 'protected'


std_symbols    ::= class(BNFStandardSymbols)
spec_symbols   ::= class(BNFSpecialSymbols)
blockstring    ::= ref(spec_block)
operstring     ::= ref(spec_plist)
linechars      ::= ref(spec_line)
nl             ::= ref(std_nl)
anychars       ::= ref(std_anychars)
class_name     ::= ref(std_name)
name           ::= ref(std_name)
number         ::= ref(std_integer)

*/


  BNFSymbol  *cpp = this;
  BNFSymbol  *std_symbols = new BNFStandardSymbols(this);
  BNFSymbol  *spec_symbols = new BNFSpecialSymbols(this);
  BNFSymbol  *blockstring = top_symbol->GetSymbol("spec_block");
  BNFSymbol  *operstring = top_symbol->GetSymbol("spec_plist");
  BNFSymbol  *linechars = top_symbol->GetSymbol("spec_line");
  BNFSymbol  *nl = top_symbol->GetSymbol("std_nl");
  BNFSymbol  *anychars = top_symbol->GetSymbol("std_anychars");
  BNFSymbol  *class_name = top_symbol->GetSymbol("std_name");
  BNFSymbol  *name = top_symbol->GetSymbol("std_name");
  BNFSymbol  *number = top_symbol->GetSymbol("std_integer");

  if ( !bs_parent )
    SetFirst();  
    
  BNFSymbol  *block = new BNFSymbol(top_symbol,"block");
  BNFSymbol  *directive = new BNFSymbol(top_symbol,"directive");
  BNFSymbol  *type_def = new BNFSymbol(top_symbol,"type_def");
  BNFSymbol  *class_def = new BNFSymbol(top_symbol,"class_def");
  BNFSymbol  *class_members = new BNFSymbol(top_symbol,"class_members");
  BNFSymbol  *base_classes = new BNFSymbol(top_symbol,"base_classes");
  BNFSymbol  *bc_list = new BNFSymbol(top_symbol,"bc_list");
  BNFSymbol  *base_class = new BNFSymbol(top_symbol,"base_class");
  BNFSymbol  *qbase_class = new BNFSymbol(top_symbol,"qbase_class");
  BNFSymbol  *class_body = new BNFSymbol(top_symbol,"class_body");
  BNFSymbol  *cd_text = new BNFSymbol(top_symbol,"cd_text");
  BNFSymbol  *member_decl = new BNFSymbol(top_symbol,"member_decl");
  BNFSymbol  *inline_funct = new BNFSymbol(top_symbol,"inline_funct");
  BNFSymbol  *member_qualifier = new BNFSymbol(top_symbol,"member_qualifier");
  BNFSymbol  *member_defin = new BNFSymbol(top_symbol,"member_defin");
  BNFSymbol  *member_defin1 = new BNFSymbol(top_symbol,"member_defin1");
  BNFSymbol  *member_attr = new BNFSymbol(top_symbol,"member_attr");
  BNFSymbol  *bit_count = new BNFSymbol(top_symbol,"bit_count");
  BNFSymbol  *array_dim = new BNFSymbol(top_symbol,"array_dim");
  BNFSymbol  *num_var = new BNFSymbol(top_symbol,"num_var",YES);
  BNFSymbol  *attr_ext = new BNFSymbol(top_symbol,"attr_ext");
  BNFSymbol  *function_block = new BNFSymbol(top_symbol,"function_block");
  BNFSymbol  *function_init = new BNFSymbol(top_symbol,"function_init");
  BNFSymbol  *call_ext = new BNFSymbol(top_symbol,"call_ext");
  BNFSymbol  *fct_call = new BNFSymbol(top_symbol,"fct_call");
  BNFSymbol  *parm_text = new BNFSymbol(top_symbol,"parm_text",YES);
  BNFSymbol  *call_parms = new BNFSymbol(top_symbol,"call_parms");
  BNFSymbol  *member_def = new BNFSymbol(top_symbol,"member_def");
  BNFSymbol  *type_name = new BNFSymbol(top_symbol,"type_name");
  BNFSymbol  *gen_parms = new BNFSymbol(top_symbol,"gen_parms");
  BNFSymbol  *member_spec = new BNFSymbol(top_symbol,"member_spec");
  BNFSymbol  *scope_member = new BNFSymbol(top_symbol,"scope_member");
  BNFSymbol  *member_head = new BNFSymbol(top_symbol,"member_head");
  BNFSymbol  *fct_name = new BNFSymbol(top_symbol,"fct_name",YES);
  BNFSymbol  *begin_line = new BNFSymbol(top_symbol,"begin_line",YES);
  BNFSymbol  *recover_line = new BNFSymbol(top_symbol,"recover_line",YES);
  BNFSymbol  *end_line = new BNFSymbol(top_symbol,"end_line",YES);
  BNFSymbol  *fct_line = new BNFSymbol(top_symbol,"fct_line");
  BNFSymbol  *fblock = new BNFSymbol(top_symbol,"fblock");
  BNFSymbol  *comment = new BNFSymbol(top_symbol,"comment",YES);
  BNFSymbol  *comment_block = new BNFSymbol(top_symbol,"comment_block",YES);
  BNFSymbol  *end_comment = new BNFSymbol(top_symbol,"end_comment");
  BNFSymbol  *line_ext = new BNFSymbol(top_symbol,"line_ext");
  BNFSymbol  *tparm_list = new BNFSymbol(top_symbol,"tparm_list");
  BNFSymbol  *type_parms = new BNFSymbol(top_symbol,"type_parms");
  BNFSymbol  *tparm_ext = new BNFSymbol(top_symbol,"tparm_ext");
  BNFSymbol  *type_parm = new BNFSymbol(top_symbol,"type_parm");
  BNFSymbol  *name_list = new BNFSymbol(top_symbol,"name_list");
  BNFSymbol  *refptr = new BNFSymbol(top_symbol,"refptr");
  BNFSymbol  *name_ext = new BNFSymbol(top_symbol,"name_ext");
  BNFSymbol  *qualifier = new BNFSymbol(top_symbol,"qualifier",YES);
  BNFSymbol  *member_options = new BNFSymbol(top_symbol,"member_options",YES);
  BNFSymbol  *scope_qualifier = new BNFSymbol(top_symbol,"scope_qualifier",YES);

// cpp
  expression = new BNFExpression(cpp);
    expression->AddElement(block,NO,UNDEF,YES,YES);

// block
  expression = new BNFExpression(block);
    expression->AddElement(comment,NO,1,YES,YES);
  expression = new BNFExpression(block);
    expression->AddElement(function_block,NO,1,YES,YES);
  expression = new BNFExpression(block);
    expression->AddElement(class_def,NO,1,YES,YES);
  expression = new BNFExpression(block);
    expression->AddElement(type_def,NO,1,YES,YES);
  expression = new BNFExpression(block);
    expression->AddElement(directive,NO,1,YES,YES);
  expression = new BNFExpression(block);
    expression->AddElement(comment_block,NO,1,YES,YES);

// directive
  expression = new BNFExpression(directive);
    expression->AddElement(ElementaryToken('#'),NO,1,NO,YES);
    expression->AddElement(name,NO,1,YES,YES);
    expression->AddElement(linechars,NO,1,YES,YES);
    expression->AddElement(line_ext,YES,UNDEF,YES,YES);
    expression->AddElement(nl,YES,1,YES,YES);

// type_def
  expression = new BNFExpression(type_def);
    expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('y'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('d'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('f'),NO,1,YES,YES);
    expression->AddElement(anychars,NO,1,YES,YES);
    expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// class_def
  expression = new BNFExpression(class_def);
    expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('s'),NO,1,YES,YES);
    expression->AddElement(class_name,NO,1,YES,YES);
    expression->AddElement(class_members,YES,1,YES,YES);
    expression->AddElement(name_list,YES,1,YES,YES);
    expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);

// class_members
  expression = new BNFExpression(class_members);
    expression->AddElement(base_classes,NO,1,YES,YES);
    expression->AddElement(class_body,NO,1,YES,YES);
  expression = new BNFExpression(class_members);
    expression->AddElement(class_body,NO,1,YES,YES);

// base_classes
  expression = new BNFExpression(base_classes);
    expression->AddElement(ElementaryToken(':'),NO,1,NO,YES);
    expression->AddElement(base_class,NO,1,YES,YES);
    expression->AddElement(bc_list,YES,UNDEF,YES,YES);

// bc_list
  expression = new BNFExpression(bc_list);
    expression->AddElement(ElementaryToken(','),NO,1,NO,YES);
    expression->AddElement(base_class,NO,1,YES,YES);

// base_class
  expression = new BNFExpression(base_class);
    expression->AddElement(qbase_class,NO,1,YES,YES);
  expression = new BNFExpression(base_class);
    expression->AddElement(class_name,NO,1,YES,YES);

// qbase_class
  expression = new BNFExpression(qbase_class);
    expression->AddElement(qualifier,NO,UNDEF,YES,YES);
    expression->AddElement(class_name,NO,1,YES,YES);

// class_body
  expression = new BNFExpression(class_body);
    expression->AddElement(ElementaryToken('{'),NO,1,NO,YES);
    expression->AddElement(cd_text,NO,1,YES,YES);
    expression->AddElement(ElementaryToken('}'),NO,1,NO,YES);

// cd_text
  expression = new BNFExpression(cd_text);
    expression->AddElement(comment,NO,1,YES,YES);
  expression = new BNFExpression(cd_text);
    expression->AddElement(comment_block,NO,1,YES,YES);
  expression = new BNFExpression(cd_text);
    expression->AddElement(member_decl,NO,UNDEF,YES,YES);

// member_decl
  expression = new BNFExpression(member_decl);
    expression->AddElement(member_defin,NO,1,YES,YES);
  expression = new BNFExpression(member_decl);
    expression->AddElement(member_qualifier,NO,1,YES,YES);
  expression = new BNFExpression(member_decl);
    expression->AddElement(inline_funct,NO,1,YES,YES);

// inline_funct
  expression = new BNFExpression(inline_funct);
    expression->AddElement(function_block,NO,1,YES,YES);
  expression = new BNFExpression(inline_funct);
    expression->AddElement(scope_qualifier,NO,1,YES,YES);
    expression->AddElement(ElementaryToken(':'),NO,1,NO,YES);
    expression->AddElement(function_block,NO,1,YES,YES);

// member_qualifier
  expression = new BNFExpression(member_qualifier);
    expression->AddElement(scope_qualifier,NO,1,YES,YES);
    expression->AddElement(ElementaryToken(':'),NO,1,NO,YES);
    expression->AddElement(member_defin,NO,1,YES,YES);

// member_defin
  expression = new BNFExpression(member_defin);
    expression->AddElement(member_options,NO,UNDEF,YES,YES);
    expression->AddElement(member_defin1,NO,1,YES,YES);
  expression = new BNFExpression(member_defin);
    expression->AddElement(member_defin1,NO,1,YES,YES);

// member_defin1
  expression = new BNFExpression(member_defin1);
    expression->AddElement(member_def,NO,1,YES,YES);
    expression->AddElement(member_attr,YES,UNDEF,YES,YES);
    expression->AddElement(ElementaryToken(';'),NO,1,NO,YES);
    expression->AddElement(comment,YES,1,YES,YES);

// member_attr
  expression = new BNFExpression(member_attr);
    expression->AddElement(array_dim,NO,1,YES,YES);
  expression = new BNFExpression(member_attr);
    expression->AddElement(bit_count,NO,1,YES,YES);
  expression = new BNFExpression(member_attr);
    expression->AddElement(member_options,NO,1,YES,YES);
  expression = new BNFExpression(member_attr);
    expression->AddElement(attr_ext,NO,1,YES,YES);

// bit_count
  expression = new BNFExpression(bit_count);
    expression->AddElement(ElementaryToken(':'),NO,1,NO,YES);
    expression->AddElement(num_var,NO,1,YES,YES);

// array_dim
  expression = new BNFExpression(array_dim);
    expression->AddElement(ElementaryToken('['),NO,1,NO,YES);
    expression->AddElement(num_var,NO,1,YES,YES);
    expression->AddElement(ElementaryToken(']'),NO,1,NO,YES);

// num_var
  expression = new BNFExpression(num_var);
    expression->AddElement(number,NO,1,YES,YES);
  expression = new BNFExpression(num_var);
    expression->AddElement(name,NO,1,YES,YES);

// attr_ext
  expression = new BNFExpression(attr_ext);
    expression->AddElement(fct_call,NO,1,YES,YES);

// function_block
  expression = new BNFExpression(function_block);
    expression->AddElement(member_def,NO,1,YES,YES);
    expression->AddElement(function_init,YES,1,YES,YES);
    expression->AddElement(fblock,NO,1,YES,YES);

// function_init
  expression = new BNFExpression(function_init);
    expression->AddElement(ElementaryToken(':'),NO,1,NO,YES);
    expression->AddElement(fct_call,NO,1,YES,YES);
    expression->AddElement(call_ext,YES,UNDEF,YES,YES);

// call_ext
  expression = new BNFExpression(call_ext);
    expression->AddElement(ElementaryToken(','),NO,1,NO,YES);
    expression->AddElement(fct_call,NO,1,YES,YES);

// fct_call
  expression = new BNFExpression(fct_call);
    expression->AddElement(fct_name,NO,1,YES,YES);
    expression->AddElement(call_parms,YES,1,YES,YES);

// parm_text
  expression = new BNFExpression(parm_text);
    expression->AddElement(call_parms,NO,1,YES,YES);
  expression = new BNFExpression(parm_text);
    expression->AddElement(operstring,NO,1,YES,YES);

// call_parms
  expression = new BNFExpression(call_parms);
    expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    expression->AddElement(parm_text,YES,UNDEF,YES,YES);
    expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);

// member_def
  expression = new BNFExpression(member_def);
    expression->AddElement(member_spec,NO,1,YES,YES);
  expression = new BNFExpression(member_def);
    expression->AddElement(type_name,NO,1,YES,YES);
    expression->AddElement(refptr,YES,UNDEF,YES,YES);
    expression->AddElement(member_spec,NO,1,YES,YES);

// type_name
  expression = new BNFExpression(type_name);
    expression->AddElement(name,NO,1,YES,YES);
    expression->AddElement(gen_parms,YES,1,YES,YES);

// gen_parms
  expression = new BNFExpression(gen_parms);
    expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    expression->AddElement(parm_text,NO,1,YES,YES);
    expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);
  expression = new BNFExpression(gen_parms);
    expression->AddElement(ElementaryToken('<'),NO,1,NO,YES);
    expression->AddElement(parm_text,NO,1,YES,YES);
    expression->AddElement(ElementaryToken('>'),NO,1,NO,YES);

// member_spec
  expression = new BNFExpression(member_spec);
    expression->AddElement(member_head,NO,1,YES,YES);
  expression = new BNFExpression(member_spec);
    expression->AddElement(scope_member,NO,1,YES,YES);

// scope_member
  expression = new BNFExpression(scope_member);
    expression->AddElement(class_name,NO,1,YES,YES);
    expression->AddElement(ElementaryToken(':'),NO,1,NO,NO);
    expression->AddElement(ElementaryToken(':'),NO,1,NO,YES);
    expression->AddElement(member_head,NO,1,YES,YES);

// member_head
  expression = new BNFExpression(member_head);
    expression->AddElement(fct_name,NO,1,YES,YES);
    expression->AddElement(tparm_list,YES,1,YES,YES);

// fct_name
  expression = new BNFExpression(fct_name);
    expression->AddElement(ElementaryToken('~'),NO,1,NO,YES);
    expression->AddElement(name,NO,1,YES,YES);
  expression = new BNFExpression(fct_name);
    expression->AddElement(name,NO,1,YES,YES);

// fct_line
  expression = new BNFExpression(fct_line);
    expression->AddElement(comment,NO,1,YES,YES);
  expression = new BNFExpression(fct_line);
    expression->AddElement(comment_block,NO,1,YES,YES);
  expression = new BNFExpression(fct_line);
    expression->AddElement(fblock,NO,1,YES,YES);
  expression = new BNFExpression(fct_line);
    expression->AddElement(blockstring,NO,1,YES,NO);
    expression->AddElement(nl,YES,1,YES,NO);
  expression = new BNFExpression(fct_line);
    expression->AddElement(begin_line,NO,1,YES,YES);
  expression = new BNFExpression(fct_line);
    expression->AddElement(recover_line,NO,1,YES,YES);
  expression = new BNFExpression(fct_line);
    expression->AddElement(end_line,NO,1,YES,YES);

// begin_line
  expression = new BNFExpression(begin_line);
    expression->AddElement(ElementaryToken('B'),NO,1,NO,NO);
    expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    expression->AddElement(ElementaryToken('G'),NO,1,NO,NO);
    expression->AddElement(ElementaryToken('I'),NO,1,NO,NO);
    expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    expression->AddElement(ElementaryToken('Q'),NO,1,NO,YES);

// recover_line
  expression = new BNFExpression(recover_line);
    expression->AddElement(ElementaryToken('R'),NO,1,NO,NO);
    expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    expression->AddElement(ElementaryToken('C'),NO,1,NO,NO);
    expression->AddElement(ElementaryToken('O'),NO,1,NO,NO);
    expression->AddElement(ElementaryToken('V'),NO,1,NO,NO);
    expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    expression->AddElement(ElementaryToken('R'),NO,1,NO,YES);

// end_line
  expression = new BNFExpression(end_line);
    expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    expression->AddElement(ElementaryToken('N'),NO,1,NO,NO);
    expression->AddElement(ElementaryToken('D'),NO,1,NO,NO);
    expression->AddElement(ElementaryToken('S'),NO,1,NO,NO);
    expression->AddElement(ElementaryToken('E'),NO,1,NO,NO);
    expression->AddElement(ElementaryToken('Q'),NO,1,NO,YES);

// fblock
  expression = new BNFExpression(fblock);
    expression->AddElement(ElementaryToken('{'),NO,1,NO,YES);
    expression->AddElement(fct_line,YES,UNDEF,YES,YES);
    expression->AddElement(ElementaryToken('}'),NO,1,NO,YES);

// comment
  expression = new BNFExpression(comment);
    expression->AddElement(ElementaryToken('/'),NO,1,NO,NO);
    expression->AddElement(ElementaryToken('/'),NO,1,NO,YES);
    expression->AddElement(linechars,NO,1,YES,YES);
    expression->AddElement(line_ext,YES,UNDEF,YES,YES);

// comment_block
  expression = new BNFExpression(comment_block);
    expression->AddElement(ElementaryToken('/'),NO,1,NO,NO);
    expression->AddElement(ElementaryToken('*'),NO,1,NO,YES);
    expression->AddElement(anychars,NO,1,YES,YES);
    expression->AddElement(end_comment,NO,1,YES,YES);

// end_comment
  expression = new BNFExpression(end_comment);
    expression->AddElement(ElementaryToken('*'),NO,1,NO,NO);
    expression->AddElement(ElementaryToken('/'),NO,1,NO,YES);

// line_ext
  expression = new BNFExpression(line_ext);
    expression->AddElement(ElementaryToken('\\'),NO,1,NO,NO);
    expression->AddElement(linechars,NO,1,YES,YES);

// tparm_list
  expression = new BNFExpression(tparm_list);
    expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    expression->AddElement(type_parms,YES,1,YES,YES);
    expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);

// type_parms
  expression = new BNFExpression(type_parms);
    expression->AddElement(type_parm,NO,1,YES,YES);
    expression->AddElement(tparm_ext,YES,UNDEF,YES,YES);

// tparm_ext
  expression = new BNFExpression(tparm_ext);
    expression->AddElement(ElementaryToken(','),NO,1,NO,YES);
    expression->AddElement(type_parm,NO,1,YES,YES);

// type_parm
  expression = new BNFExpression(type_parm);
    expression->AddElement(type_name,NO,1,YES,YES);
    expression->AddElement(refptr,YES,UNDEF,YES,YES);
    expression->AddElement(name,NO,1,YES,YES);

// name_list
  expression = new BNFExpression(name_list);
    expression->AddElement(name,NO,1,YES,YES);
    expression->AddElement(name_ext,YES,UNDEF,YES,YES);
    expression->AddElement(name,NO,1,YES,YES);

// refptr
  expression = new BNFExpression(refptr);
    expression->AddElement(ElementaryToken('&'),NO,1,NO,YES);
  expression = new BNFExpression(refptr);
    expression->AddElement(ElementaryToken('*'),NO,1,NO,YES);

// name_ext
  expression = new BNFExpression(name_ext);
    expression->AddElement(ElementaryToken(','),NO,1,NO,YES);
    expression->AddElement(name,NO,1,YES,YES);

// qualifier
  expression = new BNFExpression(qualifier);
    expression->AddElement(scope_qualifier,NO,1,YES,YES);
  expression = new BNFExpression(qualifier);
    expression->AddElement(member_options,NO,1,YES,YES);

// member_options
  expression = new BNFExpression(member_options);
    expression->AddElement(ElementaryToken('v'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('l'),NO,1,YES,YES);
  expression = new BNFExpression(member_options);
    expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('c'),NO,1,YES,YES);
  expression = new BNFExpression(member_options);
    expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('t'),NO,1,YES,YES);

// scope_qualifier
  expression = new BNFExpression(scope_qualifier);
    expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('b'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('c'),NO,1,YES,YES);
  expression = new BNFExpression(scope_qualifier);
    expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('i'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('v'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  expression = new BNFExpression(scope_qualifier);
    expression->AddElement(ElementaryToken('p'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('o'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('d'),NO,1,YES,YES);

  if ( !bs_parent )
  {
    ReorderSymbols();
    ListSymbols();
  }


}

/******************************************************************************/
/**
\brief  ~BNF_cpp


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~BNF_cpp"

                        BNF_cpp :: ~BNF_cpp ( )
{



}


