<#include "asnMacros.ftl" parse=true>
<#-- This is a freemarker comment
<#assign description=facade.getAsnDescription()>
-- This is a generated file, dont modify it manually
-- ------------------------------------------------------
-- SYNTAX PRODUCED BY: AndroMDA ASN.1 Cartridge
-- SYNTAX LOCATION AT: ${description.getFullName()}.asn



-- --------------------------------------
${description.getDocumentation()}
-- --------------------------------------
${description.getShortName()} DEFINITIONS IMPLICIT TAGS ::=
BEGIN

-->

<#-- Lets collect blocks now 
<#list description.getBlocks() as aBlock>
<@MakeBlock block=aBlock />
</#list>
-->



-- --------------------------------------
END
