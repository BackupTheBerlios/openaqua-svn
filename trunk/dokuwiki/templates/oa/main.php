<?php
/**
 */

// must be run from within DokuWiki
if (!defined('DOKU_INC')) die();
if (file_exists(DOKU_PLUGIN.'displaywikipage/code.php')) include_once(DOKU_PLUGIN.'displaywikipage/code.php');

$myNamespacePrefix          = 'openaqua';
$myPAGENAVIGATION           = ':wiki:navigation';
$myPAGEHEADERNAVIGATION     = ':wiki:headernavigation';
$myDefaultPageContact       = $myNamespacePrefix . ':contact';
$myDefaultPageAbout         = $myNamespacePrefix . ':about';
$myDefaultPagePrivacyPolice = $myNamespacePrefix . ':privacypolicy';
$myDefaultPageCopyRight     = $myNamespacePrefix . ':copyright';
$myLogo                     = '<B><FONT COLOR="#ff0000">#</FONT><FONT COLOR="#666666">define</FONT>
<FONT COLOR="#333333">OpenAqua</FONT></B>';
?>


<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php echo $conf['lang']?>" lang="<?php echo $conf['lang']?>" dir="<?php echo $lang['direction']?>">
 
<!--##################################################HTML HEADER-->
<head>
   <?php 
      if (function_exists('re_log_referrers')) re_log_referrers();
      
      /*make page title*/
      echo '<title>';  tpl_pagetitle(); echo ' - ' . strip_tags($conf['title']) . "</title>\n";
      
      //Add meta headers
      echo '<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />';
      tpl_metaheaders();
      @include(dirname(__FILE__).'/meta.html');
    
   ?>
   
   <!-- to correct the unsightly Flash of Unstyled Content. http://www.bluerobot.com/web/css/fouc.asp -->
   <script type="text/javascript"></script>


   <!--
      @import "http://www.zeuscms.gr/zengarden/sample.css";
      @import "http://home.wi.ps.pl/~kzolnowski/default_revisited.css"; #doesnt work
      @import "http://vincentlenoir.d.free.fr/natural/natural.css";
      @import "http://www.csszengarden.com/004/004.css";
      @import "http://www.csszengarden.com/184/184.css";
      @import "http://csszengarden.com/zengarden-sample.css";
      @import "http://www.mhpverwoerd.nl/sites/apprentice/sample.css";
      @import "http://www.csszengarden.com/001/001.css";


Good Ideas: http://csszengarden.com/?cssfile=http://www.mhpverwoerd.nl/sites/apprentice/sample.css      

   
<style type="text/css" media="all">
      @import "http://www.csszengarden.com/184/184.css";
</style>
-->
</head>


<!--##################################################HTML BODY-->

   <!--

      This xhtml document is marked up to provide the designer with the maximum possible flexibility.
      There are more classes and extraneous tags than needed, and in a real world situation, it's more
      likely that it would be much leaner.

      However, I think we can all agree that even given that, we're still better off than if this had been
      built with tables.


   -->

   <body onload="window.defaultStatus='css Zen Garden: The Beauty in CSS Design';" id="css-zen-garden">

   <div id="container">
   
      <div id="intro">
         <!--Logo!!-->
         <div id="pageHeader">
            pageHeader
         </div>

         <!--subtitle for the website-->
         <div id="quickSummary">
            quickSummary
         </div>

         <!--????-->
         <div id="preamble">
         </div>
      </div>
      
      
      <div id="supportingText">
         <!--Hat drei Blöcke
            explanation
            participation
            benefits
            requirements
            footer
            -->

         <?php tpl_content();?>

         <div id="footer">
            <?php  tpl_pagelink($myDefaultPageCopyRight); ?>
            <?php  tpl_pagelink($myDefaultPageAbout);?>
            <?php  tpl_pagelink($myDefaultPageContact);?>
            <?php  tpl_pagelink($myDefaultPagePrivacyPolice);?>
            <?php  tpl_actionlink('index'); ?></li>
            <?php  $url = parse_url ( DOKU_URL ); $server = $url['host']; if(!empty( $url['port'])) { $server .= ':' . $url['port']; }; $server .= $url['path']; echo '<a href="' . DOKU_URL .  '" title="Visit ' . DOKU_URL . '" >'. $server . ' </a>';?></li>
         </div>
         
      </div>
      
      <div id="linkList">
         <!--extra div for flexibility - this list will probably be the trickiest spot you'll deal with -->

         <div id="linkList2">

         <!-- If you're wondering about the extra &nbsp; at the end of the link, it's a hack to meet WCAG 1 Accessibility. -->
         <!-- I don't like having to do it, but this is a visual exercise. It's a compromise. -->
            <div id="lselect">
               <h3 class="select"><span>Navigation</span></h3>
                <?php if (function_exists('dwp_display_wiki_page')) dwp_display_wiki_page($myPAGENAVIGATION);?>
            </div>

            <div id="larchives">
               <h3 class="archives"><span>Wiki</span></h3>
               <ul >
                  <li ><?php tpl_pagelink($myDefaultPageAbout); ?> </li>
                  <li ><?php tpl_actionlink('index'); ?></li>
                  <li ><?php tpl_actionlink('login'); ?></li>
                  <li ><?php tpl_actionlink('subscription');   ?> </li>
                  <li ><?php tpl_actionlink('admin');  ?> </li>
                  <li ><?php tpl_actionlink('profile');  ?> </li>
               </ul>

            </div>

            <div id="lresources">
               <h3 class="resources"><span>Edit</span></h3>
               <ul>
                  <li ><?php tpl_actionlink('edit');   ?> </li>
                  <li ><?php tpl_actionlink('history');   ?> </li>
                  <li ><?php tpl_actionlink('recent');   ?> </li>
               </ul>
            </div>
         </div>

      </div>
      
      
   </div>

   <!-- These extra divs/spans may be used as catch-alls to add extra imagery. -->
   <!-- Add a background image to each and use width and height to control sizing, place with absolute positioning -->
   <div id="extraDiv1"><span></span></div><div id="extraDiv2"><span></span></div><div id="extraDiv3"><span></span></div>
   <div id="extraDiv4"><span></span></div><div id="extraDiv5"><span></span></div><div id="extraDiv6"><span></span></div>

</body>
</html>


