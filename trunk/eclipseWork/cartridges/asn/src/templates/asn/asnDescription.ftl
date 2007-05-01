<#-- This is a freemarker comment-->

-- This is a generated file, dont modify it manually
-- ------------------------------------------------------
-- SYNTAX PRODUCED BY: AndroMDA ASN.1 Cartridge
-- SYNTAX LOCATION AT: ${file.fullyQualifiedNamePath}.asn


-- --------------------------------------
${file.getDocumentation("-- ")}
-- --------------------------------------


${file.name} DEFINITIONS IMPLICIT TAGS ::=

BEGIN

<#if file.hasHeaderDescription()>
-- --------------------------------------
-- ---------Header Record----------------
<#list file.getHeaderDescription() as class>
${class.getDocumentation("-- ")}
${class.name} ::= SEQUENCE
{
}


</#list>
</#if>

<#if file.hasFooterDescription()>
-- --------------------------------------
-- ---------Footer Record----------------
<#list file.getFooterDescription() as class>
${class.getDocumentation("-- ")}
${class.name} ::= SEQUENCE
{
}


</#list>
</#if>

<#if file.hasDetailDescription()>
-- --------------------------------------
-- ---------Detail Record----------------
AsnDetailRecord ::= CHOICE 
{
<#list file.getDetailDescription() as class>
	//hier müssen die Attribute gelesen werden, nicht die zugeordneten Klassen!
	foo ${class.name}
</#list>
}


</#if>


<#-- 
Construct the ASN.1 Blocks for all Value Objects
-->
<#if file.hasDetailDescription()>
-- --------------------------------------
-- ---------Other Declarations Record----------------
<#list file.getDetailDescription() as class>

-- --------------------------------------
${class.getDocumentation("-- ")}
${class.name} ::= SEQUENCE
{
}

</#list>
</#if>

-- --------------------------------------
END
