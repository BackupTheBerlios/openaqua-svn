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
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
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

<!--
   
   -->

<!--##################################################HTML BODY-->
<body>



<div id="oaTmplPageHeader≤≤≤≤≤">
      <div id="oaTmplPageHeaderLinks" class="horizontalNavigation"  style="">
         <ul >
            <li ><?php tpl_pagelink($myDefaultPageAbout); ?> </li>
            <li ><?php tpl_actionlink('index'); ?></li>
            <li ><?php tpl_actionlink('login'); ?></li>
            <li ><?php tpl_actionlink('subscription');   ?> </li>
            <li ><?php tpl_actionlink('admin');  ?> </li>
            <li ><?php tpl_actionlink('profile');  ?> </li>
         </ul>
      </div>
      
      <div id="oaTmplHeaderLogo">
         <div id="oaTmplHeaderLogoLogo"> <?php tpl_link(wl(), $myLogo ,'name="dokuwiki__top" id="dokuwiki__top" accesskey="h" title="[ALT+H]"')?> </div>
      </div>

      <div class="clearer"> </div>
</div>


<div id="oaTmplPageHeaderColorBox">
      <div class="oaTmplPageLeft">
          <div class="colorBox" > </div>
      </div>
      
      <div class="oaTmplPageContent">
         <div class="colorBox" style="background-color: #344966;"></div>
      </div>

      <div class="clearer"> </div>
</div>

   

<div id="wrapper_extra">
   <div id="wrapper">
      
      <!--Page Left-->
      <div class="oaTmplPageLeft">
      
         <!--
            <?php if ($conf['breadcrumbs']) { ?>
               <div id="catlinks">
                  <p class="catlinks"></p>
               </div>
            <?php } ?>
         -->
      
         <div class="oaTmplPageLeftNavigation" >  
            <?php if (function_exists('dwp_display_wiki_page')) dwp_display_wiki_page($myPAGENAVIGATION);?>
         </div>

         <h1 class="toc">Welcome!</h1>
         <p>Welcome on the OpenAqua documentation wiki.</p>
         
         <div class="searchBox">
            <?php tpl_searchform()?>
         </div>

      </div>
      
      
      <div class="oaTmplPageContent">
         <div  class="dokuwiki">
            <!-- start content -->

            <!-- html_msgarea -->
            <?php //html_msgarea()?>

            <!-- breadcrumbs -->
            <!--
            <?php if ($conf['breadcrumbs']) { ?>
               <div id="catlinks">
                  <p class="catlinks"> <?php tpl_breadcrumbs(); ?> </p>
               </div>
            <?php } ?>
            -->

            <!-- search_out -->
            <!--
            <div id="qsearch__out" class="ajax_qsearch JSpopup"></div>
            -->

            <!-- content output -->
            <?php //most lines are for monobook template
                   if ($_REQUEST['mbdo'] == 'cite')
                           @include(dirname(__FILE__).'/do_cite.php');
                   else if ($_REQUEST['mbdo'] == 'detail')
                           @include(dirname(__FILE__).'/do_detail.php');
                   else if ($_REQUEST['mbdo'] == 'media')
                           @include(dirname(__FILE__).'/do_media.php');
                   else
                           tpl_content();//this is the default
            ?>
            <br/>
            <?php if ($conf['youarehere']) { ?><div id="catlinks"><p class="catlinks">
            <?php tpl_youarehere(); ?></p></div><?php } ?>
            <!-- end content -->
         </div >
         <div class="horizontalNavigation" style="text-align: left;" >
            <?php if ($conf['useacl'] ) {if(! $_SERVER['REMOTE_USER']) {    echo '<!--';   }} ?>
             <ul >
                <li ><?php tpl_actionlink('edit');   ?> </li>
                <li ><?php tpl_actionlink('history');   ?> </li>
                <li ><?php tpl_actionlink('recent');   ?> </li>
             </ul>
             <?php if ($conf['useacl'] ) {if(! $_SERVER['REMOTE_USER']) {    echo '-->';   }} ?>
         </div>
      </div>
      
      
   </div><!-- close div#wrapper -->
</div><!-- close div#wrapper_extra -->



<!--PAGE FOOTER-->
<div id="oaTmplPageFooter" class="horizontalNavigation"  >
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

<!--Clean Up staff for dokuwiki-->
<div class="clearer"> </div>
   
<p><?php tpl_pageinfo()?> <?php tpl_userinfo()?></p>
<div class="hiddenParts"><?php /* provide DokuWiki housekeeping, required in all templates */ tpl_indexerWebBug()?></div>
</div>

   

</body>
</html>
