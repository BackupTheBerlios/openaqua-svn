<#-- This file contains a couple of useful macros set set ASN.1 Descriptions-->


<#macro MakeElements e>
	${e.getName()}
</#macro>



<#macro MakeBlock block>
${block.getDocumentation()}
${block.getName()} ::= SEQUENCE
{

<#list block.getSubElements() as Element>
<@MakeElements e=Element />
</#list>

}
</#macro>

