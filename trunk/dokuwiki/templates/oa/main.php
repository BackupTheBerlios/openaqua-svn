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
                    tpl_pagelink('openaqua:accessibility');
                    tpl_pagelink('openaqua:impressum');
            ?>
      </div>
      
      
      <div id="oaTmplHeaderBottom">
         <div id="logo"> #define IVC </div>
         <div id="search-box"> <?php tpl_searchform()?>&nbsp; </div>
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
</div>
   
   
<!--Content-->   
<div id="oaTmplMainPage">
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
    <!-- wikipage start -->
    <?php tpl_content()?>
    <!-- wikipage stop -->
   </div>
</div>

   
   

   <div id="oaTmplFooter">
      <p id="oaTmplFooterCopyright"> <a href="copyright" title="Copyright"><span>2006</span> &copy; Copyright</a></p>
      <p id="oaTmplFooterNavigation">
          <a href="about" title="About OpenAqua"> About OpenAqua  </a>
          <a href="http://www.trolltech.com/company/contact-info" title="Contact us"> Contact us </a>
          <a href="/trolltech/privacypolicy" title="Privacy policy"> Privacy Policy </a>
          <a href="http://www.trolltech.com/sitemap" title="Site map">  Site map  </a>
          <a href="http://www.trolltech.com" title="Visit www.trolltech.com" > www.trolltech.com </a>
          <a target="_blank" href="<?php echo DOKU_BASE?>feed.php" title="Recent changes RSS feed" class="lastNavItem">Recent changes RSS feed</a>
      </p>   
   </div> 
   <p><?php tpl_pageinfo()?> <?php tpl_userinfo()?></p>
   <!-- 
   
   <p><?php if ($monobook['copyright']) { ?><?php if (function_exists('dwp_display_wiki_page')) dwp_display_wiki_page($monobook['copyright']); ?><?php } ?></p>
   -->
   <p></p>
   
   


   <div class="hiddenParts"><?php /* provide DokuWiki housekeeping, required in all templates */ tpl_indexerWebBug()?></div>

</body>
</html>
