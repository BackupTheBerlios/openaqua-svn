<#-- This file contains a couple of useful macros set set ASN.1 Descriptions-->


<#macro printCopyright>
-- This is a useless copyright note
</#macro>


<#macro MakeBlock block>
${block.getDocumentation()}
${block.getShortName()} ::= SEQUENCE
{
	-- stuff
}
</#macro>

