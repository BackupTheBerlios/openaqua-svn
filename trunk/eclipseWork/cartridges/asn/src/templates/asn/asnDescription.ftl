<#include "asnMacros.ftl" parse=true>
<#-- This is a freemarker comment-->
<#list description.getAsnDescription() as file>
-- This is a generated file, dont modify it manually
-- ------------------------------------------------------
-- SYNTAX PRODUCED BY: AndroMDA ASN.1 Cartridge
-- SYNTAX LOCATION AT: ${file.getFullName()}.asn



-- --------------------------------------
${file.getDocumentation()}
-- --------------------------------------
${file.getShortName()} DEFINITIONS IMPLICIT TAGS ::=
BEGIN



<#if file.hasHeader()>
-- --------------------------------------
-- ---------Header Record----------------
<@MakeBlock block=file.getHeader() />
</#if>




<#if file.hasFooter()>
-- --------------------------------------
-- ---------Footer Record----------------
<@MakeBlock block=file.getFooter() />
</#if>


-- --------------------------------------
END

</#list>