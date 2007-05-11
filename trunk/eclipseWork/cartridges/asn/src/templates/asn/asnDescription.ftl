<#include "asnMacros.ftl" parse=true>
<#assign description=facade.getAsnDescription()>
-- This is a generated file, dont modify it manually
-- ------------------------------------------------------
-- SYNTAX PRODUCED BY: AndroMDA ASN.1 Cartridge
-- SYNTAX LOCATION AT: ${description.getPackageName()}.asn



-- --------------------------------------
${description.getDocumenation()}
-- --------------------------------------
${description.getName()} DEFINITIONS IMPLICIT TAGS ::=
BEGIN


<#list description.getAllAsnElements() as aBlock>
<@MakeBlock block=aBlock />
</#list>

<#-- Lets collect blocks now 
-->


-- --------------------------------------
END
