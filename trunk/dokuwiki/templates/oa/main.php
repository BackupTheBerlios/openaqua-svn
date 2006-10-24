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

<!--HEADER-->
<div id="oaTmplHeader">
      <div id="oaTmplHeaderTop">
            <a href="" title="Site Map" >Site Map</a>
            <a href="" title="Accessibility" >Accessibility</a>
            <a href="" title="Impressum" > Impressum </a>
      </div>
      
      
      <div id="oaTmplHeaderBottom">
         <div id="logo"> #define IVC </div>
         <div id="search-box">
             <form name="searchform"  action="http://www.trolltech.com/search"  style="white-space:nowrap" onsubmit="return liveSearchSubmit()">
                <label for="searchGadget" class="hiddenStructure">Search Site</label>
                <div class="LSBox">
                   <input id="searchGadget" tabindex="30001" name="SearchableText" type="text" size="15"  title="Search Site" accesskey="4" class="visibility:visible" />
                   <input class="searchButton" type="submit" tabindex="30002" value="Search" />
                   <div class="LSResult" id="LSResult" style="">
                      <div class="LSShadow" id="LSShadow" />
                   </div>
                </div>         
             </form>
         </div>
      </div>
    </div>
</div>
   
   
<!--Content-->   
<div id="mainpage">
   <div id="leftPanel">
      <p>left panel</p>
      <p>There are many variations of passages of Lorem Ipsum available, but the majority have suffered alteration in some form, by injected humour, or randomised words which don't look even slightly believable. If you are going to use a passage of Lorem Ipsum, you need to be sure there isn't anything embarrassing hidden in the middle of text. All the Lorem Ipsum generators  words etc.</p>
   </div> 

   <!--Information-->
   <div id="rightPanel">
      <p>right panel</p>
      <p>There are many variations of passages of Lorem Ipsum available, but the majority have suffered alteration in some form, by injected humour, or randomised words which don't look even slightly believable. If you are going to use a passage of Lorem Ipsum, you need to be sure there isn't anything embarrassing hidden in the middle of text. All the Lorem Ipsum generators  words etc.</p>
   </div> 
   
   
   <!--Wiki Content-->
   <div id="contentArea">
      <p>contentArea</p>
       <p> Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.       Why do we use it? </p>
   </div> 

</div>

   
   

   <div id="oaTmplFooter">
      <p id="oaTmplFooterCopyright"> <a href="copyright" title="Copyright"><span>2006</span> &copy; Copyright</a></p>
      <p id="oaTmplFooterNavigation">
          <a href="about" title="About OpenAqua"> About OpenAqua  </a>
          <a href="http://www.trolltech.com/company/contact-info" title="Contact us"> Contact us </a>
          <a href="/trolltech/privacypolicy" title="Privacy policy"> Privacy Policy </a>
          <a href="http://www.trolltech.com/sitemap" title="Site map">  Site map  </a>
          <a href="http://www.trolltech.com" title="Visit www.trolltech.com" class="lastNavItem"> www.trolltech.com </a>
      </p>   
   </div> 
   


   <div class="hiddenParts"><?php /* provide DokuWiki housekeeping, required in all templates */ tpl_indexerWebBug()?></div>

</body>
</html>
