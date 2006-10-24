<?php
/**
 * DokuWiki Default Template
 *
 * This is the template you need to change for the overall look
 * of DokuWiki.
 *
 * You should leave the doctype at the very top - It should
 * always be the very first line of a document.
 *
 * @link   http://wiki.splitbrain.org/wiki:tpl:templates
 * @author Andreas Gohr <andi@splitbrain.org>
 */

// must be run from within DokuWiki
if (!defined('DOKU_INC')) die();

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
 "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php echo $conf['lang']?>"
 lang="<?php echo $conf['lang']?>" dir="<?php echo $lang['direction']?>">
 
<!--##################################################HTML HEADER-->
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  <title>
    <?php tpl_pagetitle()?>
    [<?php echo strip_tags($conf['title'])?>]
  </title>
  <?php tpl_metaheaders()?>
  <link rel="shortcut icon" href="<?php echo DOKU_TPL?>images/favicon.ico" />
  <?php /*old includehook*/ @include(dirname(__FILE__).'/meta.html')?>
</head>


<!--##################################################HTML BODY-->
<body>


<!--
The very first part of each page

oapageheaderElements
<div id="oapageheader">

   <menu>
   <li>abc</li>
   <li>abc</li>
   <li>abc</li>
   <li>abc</li>
   </menu>
   
</div>
-->

<!--
Logo, Search Field
<div id="oapagecompany">
   <div id="oapagecompanylogo">
     <div>#define IVC</div>
     <div id="wiki_search">
        <form name="searchform" action="search"> <label for="searchGadget" class="hiddenStructure"> Search Site </label>
           <div class="LSBox"> <input autocomplete="off" id="searchGadget" tabindex="30001" name="SearchableText" size="15" title="Search Site" accesskey="4" class="visibility:visible" type="text"> <input class="searchButton" tabindex="30002" value="Search" type="submit">
           <div class="LSResult" id="LSResult" style="display: none;">
              <div class="LSShadow" id="LSShadow"> 
              </div>
           </div>
         </div>
        </form>
      <div id="portal-advanced-search" class="hiddenStructure">
   <a href="http://www.trolltech.com/search_form" accesskey="5"> Advanced Search </a>
   </div>
</div>
-->


<!--
The changable body
-->

   <div id="header">
      <div id="topHeader">
         <menu>
            <li>Site Map</li>
            <li>Impressum</li>
         </menu>
      </div>
   Logo, Search Field
   </div>

   <div id="leftPanel">
      <p>left panel</p>
      <p>There are many variations of passages of Lorem Ipsum available, but the majority have suffered alteration in some form, by injected humour, or randomised words which don't look even slightly believable. If you are going to use a passage of Lorem Ipsum, you need to be sure there isn't anything embarrassing hidden in the middle of text. All the Lorem Ipsum generators  words etc.</p>
   </div> 

   <div id="rightPanel">
      <p>right panel</p>
      <p>There are many variations of passages of Lorem Ipsum available, but the majority have suffered alteration in some form, by injected humour, or randomised words which don't look even slightly believable. If you are going to use a passage of Lorem Ipsum, you need to be sure there isn't anything embarrassing hidden in the middle of text. All the Lorem Ipsum generators  words etc.</p>
   </div> 
   
   
   <div id="contentArea">
      <p>contentArea</p>
       <p> Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.       Why do we use it? </p>
   </div> 

<!--
The very last part of each page
-->
   <div id="footer">
      <menu>
      <li>(c) 2006, TMO</li>
      <li>About OpenAqua</li>
      <li>Contact us</li>
      <li>Privacy Policy</li>
      <li>Site map</li>
      <li>www.openaqua.de</li>
      </menu>
   </div> 
   




<!--##################################################DokuWiki Indexer
<div class="no"><?php /* provide DokuWiki housekeeping, required in all templates */ tpl_indexerWebBug()?></div>
-->
</body>
</html>
