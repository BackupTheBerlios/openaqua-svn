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
      
      //add a page icon
      echo '<link rel="shortcut icon" href="<' . DOKU_TPL . 'images/favicon.ico" />' . "\n";
      
      //add googleanalytics support
      if (function_exists('ga_google_analytics_code')) ga_google_analytics_code();
      if (file_exists(DOKU_PLUGIN.'googleanalytics/code.php')) include_once(DOKU_PLUGIN.'googleanalytics/code.php');
      if (function_exists('ga_google_analytics_code')) ga_google_analytics_code();
    
    
      //don't show edit buttons if user is not logged in
      if ($conf['useacl'] ) {
         if(! $_SERVER['REMOTE_USER']) {
            echo '<style type="text/css">';
            echo '<!--';
            echo '.secedit {display:none;}';
            echo '-->';
            echo '</style>';
         }
      }
   ?>
</head>
<body>
   <div id="pagewidth" >
      <div id="header" > 
         Head 
      </div>

   	<div id="wrapper" class="clearfix" >
   		<div id="twocols" class="clearfix"> 
   			<div id="maincol" > 
   			   <?php html_msgarea()?>
   			</div>
   			<div id="rightcol" > 
   			   right Column 
   			</div>
   		</div> 
   		<div id="leftcol" > 
   		   Left Column 
   		</div>
      </div>
   	<div id="footer" > 
   	   <ul id="footer-list">
             <li id="lastmod"><?php tpl_pageinfo()?></li>
             <li id="usermod"><?php tpl_userinfo()?><br />
             </li>
         </ul>
   	</div>
   </div>
   <!--some cleanup for dokuwiki indexer-->
   <a href="<?php echo DOKU_BASE.DOKU_SCRIPT;?>?do=recent" accesskey="r" style="visibility:hidden;" rel="nofollow">&nbsp;</a>	<?php tpl_indexerWebBug(); ?>
   
</body>
</html>


