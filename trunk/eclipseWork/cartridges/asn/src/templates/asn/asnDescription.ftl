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

<#if file.isHasHeaderRecord()>
-- --------------------------------------
-- ---------Header Record----------------
<#list file.allAssociatedClasses as class>
<#if asnHelp.hasStereotype("AsnSimpleHeader", class)>
${class.getDocumentation("-- ")}
${class.name} ::= SEQUENCE
{
}


</#if>
</#list>
</#if>

<#if file.isHasFooterRecord()>
-- --------------------------------------
-- ---------Footer Record----------------
<#list file.allAssociatedClasses as class>
<#if asnHelp.hasStereotype("AsnSimpleFooter", class)>
${class.getDocumentation("-- ")}
${class.name} ::= SEQUENCE
{
}


</#if>
</#list>
</#if>

<#if file.isHasDetailRecords()>
-- --------------------------------------
-- ---------Detail Record----------------
AsnDetailRecord ::= CHOICE 
{
<#list file.allAssociatedClasses as class>
<#if asnHelp.hasStereotype("AsnStorable", class)>
	${class.name}
</#if>
</#list>
}


</#if>

<#if file.isHasDetailRecords()>
-- --------------------------------------
-- ---------Other Declarations Record----------------
<#list file.allAssociatedClasses as class>
<#if asnHelp.hasStereotype("AsnStorable", class)>
${class.getDocumentation("-- ")}
${class.name} ::= SEQUENCE
{
}


</#if>
</#list>
</#if>


RETransferBatch ::= [APPLICATION 80] SEQUENCE
{
     headerRecord                      HeaderRecord,
     detailRecordList                  DetailRecordList
}



-- --------------------------------------
END
