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
$myDomain                   =  trim($_SERVER['HTTP_HOST']);
$myNamespacePrefix          = 'openaqua';
$myDefaultPageContact       = $myNamespacePrefix . ':contact';
$myDefaultPageAbout         = $myNamespacePrefix . ':about';
$myDefaultPagePrivacyPolice = $myNamespacePrefix . ':privacypolicy';
$myDefaultPageCopyRight     = $myNamespacePrefix . ':copyright';
$myLogo                     = 'It is IVC';

 
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
 "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php echo $conf['lang']?>"
 lang="<?php echo $conf['lang']?>" dir="<?php echo $lang['direction']?>">
 
<!--##################################################HTML HEADER-->
<head>
   <?php if (function_exists('re_log_referrers')) re_log_referrers(); ?>
   <!--
   <?php @include(dirname(__FILE__).'/user/pref.php'); ?>
   <?php @include(dirname(__FILE__).'/lang/en/lang.php');
      if ( $conf['lang'] && $conf['lang'] != 'en' )  @include(dirname(__FILE__).'/lang/'.$conf['lang'].'/lang.php');
      //@include(dirname(__FILE__).'/context.php');
      //@include(dirname(__FILE__).'/meta.html')
      //@include(dirname(__FILE__).'/other.php');
    ?>
    -->
   <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
   <title><?php tpl_pagetitle()?> [<?php echo strip_tags($conf['title'])?>]</title>
   <?php tpl_metaheaders()?>
   <link rel="shortcut icon" href="<?php echo DOKU_TPL?>images/favicon.ico" />
   <?php    if (file_exists(DOKU_PLUGIN.'googleanalytics/code.php')) include_once(DOKU_PLUGIN.'googleanalytics/code.php');
             if (function_exists('ga_google_analytics_code')) ga_google_analytics_code();
   ?>
</head>


<!--##################################################HTML BODY-->
<body>

<!--HEADER-->
<div id="oaTmplHeader">
      <div id="oaTmplHeaderTop">
            <?php  tpl_actionlink('login');
                    tpl_actionlink('index');
                    tpl_pagelink($myDefaultPageAbout);
            ?>
      </div>
      <hr />
      
      
      <div id="oaTmplHeaderBottom">
         <div id="oaTmplHeaderBottomLogo"> <?php echo $myLogo ?> </div>
         <div id="oaTmplHeaderBottomSearch">  <?php tpl_searchform()?></div>
      </div>
      
    
      <div id="oaTmplHeaderEdit">
         <div id="oaTmplHeaderEditLeft">
           <?php tpl_button('edit')?>
           <?php tpl_button('history')?>
           <?php tpl_button('recent')?>
         </div>
         <div id="oaTmplHeaderEditRight">
           <?php tpl_button('subscription'); 
                  tpl_button('admin');
                  tpl_button('profile');
                  tpl_button('index');
                  tpl_button('top');
           ?>
         </div>
      </div>
      <hr />
      
</div>
   
   
<!--Content-->   
<div id="oaTmplMainPage">
   <div id="oaTmplMainPageLeft">
   </div> 

   <div id="oaTmplMainPageRight">
   </div> 
   
   <div id="oaTmplMainPageContent">
       <!-- wikipage start -->
      <?php tpl_content()?>
       <!-- wikipage stop -->
   </div>
</div>

   
   
   <!--Page Footer-->
   <hr />
   <div id="oaTmplFooter">
      <p id="oaTmplFooterCopyright">   <?php  tpl_pagelink($myDefaultPageCopyRight); ?> </p>
      <p id="oaTmplFooterNavigation">  <?php  tpl_pagelink($myDefaultPageAbout);
                                               tpl_pagelink($myDefaultPageContact);
                                               tpl_pagelink($myDefaultPagePrivacyPolice);             
                                               tpl_actionlink('index');
                                               echo '<a href="http://' . $myDomain . '" title="Visit' . $myDomain . '" >'. $myDomain . ' </a>';
                                        ?>
                                       <a target="_blank" href="<?php echo DOKU_BASE?>feed.php" title="Recent changes RSS feed" class="lastNavItem">Recent changes RSS feed</a>
      </p>   
   </div> 
   
   <p><?php tpl_pageinfo()?> <?php tpl_userinfo()?></p>
   <div class="hiddenParts"><?php /* provide DokuWiki housekeeping, required in all templates */ tpl_indexerWebBug()?></div>

</body>
</html>
