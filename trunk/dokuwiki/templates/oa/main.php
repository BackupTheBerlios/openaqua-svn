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
$myNamespacePrefix          = 'openaqua';
$myDefaultPageContact       = $myNamespacePrefix . ':contact';
$myDefaultPageAbout         = $myNamespacePrefix . ':about';
$myDefaultPagePrivacyPolice = $myNamespacePrefix . ':privacypolicy';
$myDefaultPageCopyRight     = $myNamespacePrefix . ':copyright';
$myLogo                     = 'It is IVC';


 
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php echo $conf['lang']?>" lang="<?php echo $conf['lang']?>" dir="<?php echo $lang['direction']?>">
 
<!--##################################################HTML HEADER-->
<head>
   <?php 
      if (function_exists('re_log_referrers')) re_log_referrers();
      @include(dirname(__FILE__).'/user/pref.php');
      @include(dirname(__FILE__).'/lang/en/lang.php');
      if ( $conf['lang'] && $conf['lang'] != 'en' )  @include(dirname(__FILE__).'/lang/'.$conf['lang'].'/lang.php');
      //@include(dirname(__FILE__).'/context.php');
      //@include(dirname(__FILE__).'/meta.html')
      //@include(dirname(__FILE__).'/other.php');
      
      /*make page title*/
      echo '<title>';  tpl_pagetitle(); echo ' - ' . strip_tags($conf['title']) . "</title>\n";
      
      //Add meta headers
      echo '<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />';
      tpl_metaheaders();
      @include(dirname(__FILE__).'/meta.html');
      
      //add a page icon
      echo '<link rel="shortcut icon" href="<' . DOKU_TPL . 'images/favicon.ico" />' . "\n";
      
      //add googleanalytics support
      if (file_exists(DOKU_PLUGIN.'googleanalytics/code.php')) include_once(DOKU_PLUGIN.'googleanalytics/code.php');
      if (function_exists('ga_google_analytics_code')) ga_google_analytics_code();
   ?>
</head>


<!--##################################################HTML BODY-->
<body>

<!--Content-->   
<div id="oaTmplMainPage">
   <div id="oaTmplMainPageLeft">
   </div> 

   <div id="oaTmplMainPageRight">
   </div> 
   
   <div  class="dokuwiki">
   <!-- wikipage start -->
   <?php tpl_content()?>
   <!-- wikipage stop -->
   </div >
   <div class="horizontalNavigation" style="text-align: left;" >
       <ul >
          <li ><?php tpl_actionlink('edit');   ?> </li>
          <li ><?php tpl_actionlink('history');   ?> </li>
          <li ><?php tpl_actionlink('recent');   ?> </li>
       </ul>
   </div>
</div>

<!--HEADER-->
<div id="oaTmplHeader">
      <div class="horizontalNavigation"  style="text-align: right;">
         <ul >
            <li ><?php  tpl_pagelink($myDefaultPageAbout); ?> </li>
            <li ><?php  tpl_actionlink('index'); ?></li>
            <li ><?php  tpl_actionlink('login'); ?></li>
            <li ><?php tpl_actionlink('subscription');   ?> </li>
            <li ><?php tpl_actionlink('admin');  ?> </li>
            <li ><?php tpl_actionlink('profile');  ?> </li>
         </ul>
      </div>
      
      
      <div id="oaTmplHeaderLogo">
         <div id="oaTmplHeaderLogoLogo"> <?php tpl_link(wl(), $myLogo ,'name="dokuwiki__top" id="dokuwiki__top" accesskey="h" title="[ALT+H]"')?> </div>
         <div id="oaTmplHeaderLogoSearch">  <?php tpl_searchform()?></div>
      </div>
      
      <div class="clearer"></div>
      
      <div>
         <ul class="horizontalNavigation">
            <li >q </li>
            <li >w </li>
            <li >e </li>
            <li >r</li>
            <li >t</li>
            <li >z</li>
            <li >u</li>
         </ul>
      </div>
      
    
      <div class="clearer"></div>
      
</div>
   
   

  
   <!--Page Footer-->
   <div class="horizontalNavigation"  >
      <ul>
         <li> <?php  tpl_pagelink($myDefaultPageCopyRight); ?> </li>
         <li> <?php  tpl_pagelink($myDefaultPageAbout);?></li>
         <li> <?php  tpl_pagelink($myDefaultPageContact);?></li>
         <li> <?php  tpl_pagelink($myDefaultPagePrivacyPolice);?></li>
         <li> <?php  tpl_actionlink('index'); ?></li>
         <li> <?php  $url = parse_url ( DOKU_URL ); $server = $url['host']; if(!empty( $url['port'])) { $server .= ':' . $url['port']; }; $server .= $url['path']; echo '<a href="' . DOKU_URL .  '" title="Visit ' . DOKU_URL . '" >'. $server . ' </a>';?></li>
         <li>  <a target="_blank" href="<?php echo DOKU_BASE?>feed.php" title="Recent changes RSS feed" class="lastNavItem">Recent changes RSS feed</a></li>
      </ul>
   </div> 
   
   <p><?php tpl_pageinfo()?> <?php tpl_userinfo()?></p>
   <div class="hiddenParts"><?php /* provide DokuWiki housekeeping, required in all templates */ tpl_indexerWebBug()?></div>

</body>
</html>
