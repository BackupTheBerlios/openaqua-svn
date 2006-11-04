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

	<style type="text/css" media="all">
		@import "http://forum.rgsw.org.uk/music/garden/sample.css";
	</style>
	
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
      <?php tpl_content();?>
   </div>


</body>
</html>


