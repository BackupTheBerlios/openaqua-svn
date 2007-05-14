<#-- This file contains a couple of useful macros set set ASN.1 Descriptions-->


<#-- ================================================================
The following Macro builds the elements in a ASN.1 block
================================================================  -->

<#macro MakeElements e>
	<#assign asnElement=e.getElement()>
	${e.getName()}			${asnElement.getName()}
</#macro>



<#-- ================================================================
The following macro builds a ASN.1 structure Block
================================================================  -->
<#macro MakeBlock block>
   
   
   
${block.getDocumentation()}
${block.getName()} ::= SEQUENCE
{
<#list block.getSubElements() as Element>
<@MakeElements e=Element />
</#list>
}
</#macro>

