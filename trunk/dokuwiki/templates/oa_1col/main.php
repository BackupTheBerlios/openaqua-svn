<?php
// must be run from within DokuWiki
$monobook;
if (!defined('DOKU_INC')) die();
if (file_exists(DOKU_PLUGIN.'displaywikipage/code.php')) include_once(DOKU_PLUGIN.'displaywikipage/code.php');
if (isset($DOKU_TPL)==FALSE) $DOKU_TPL = DOKU_TPL; if (isset($DOKU_TPLINC)==FALSE) $DOKU_TPLINC = DOKU_TPLINC;
if (file_exists(DOKU_PLUGIN.'displaywikipage/code.php')) include_once(DOKU_PLUGIN.'displaywikipage/code.php');
if (file_exists(DOKU_PLUGIN.'referrers/code.php')) include_once(DOKU_PLUGIN.'referrers/code.php');
?>


<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php echo $conf['lang']?>" lang="<?php echo $conf['lang']?>" dir="<?php echo $lang['direction']?>">
 
<!--##################################################HTML HEADER-->
<head>
   <?php 
      if (function_exists('re_log_referrers')) re_log_referrers();
      @include (dirname(__FILE__).'/string_fn.php');
      @include(dirname(__FILE__).'/user/pref.php');
      @include(dirname(__FILE__).'/context.php');

      
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
      <!--++++++++++++++++++Header++++++++++++++-->
      <div id="header" >
         <div id="headerLinks" class="horizontalNavigation">
            <?php //writeMBPortlet($monobook['navigation'], 'p-x-navigation', '', 'n'); ?>      
         </div>

         <div id="headerPagename">
           [[<?php //tpl_link(wl($ID,'do=backlink'),tpl_pagetitle($ID,true))?>]]
         </div>
          
         <div id="headerLogo">
           <?php //tpl_link(wl(),$conf['title'],'name="dokuwiki__top" id="dokuwiki__top" accesskey="h" title="[ALT+H]"')?>
         </div>
         
         <?php writeMBPortlet($monobook['navigation'], '', '', '', 'nav'); ?>      

      </div><!--header-->      
      
      
      <!--++++++++++++++++++Content++++++++++++++-->
      <div id="page">
         <!--main column (is the left column)-->
         <div id="maincol" > 
            <div id="maincolContent" > 
               <!-- start content -->
               <?php if ($conf['breadcrumbs']) { ?><div id="catlinks"><p class="catlinks"><?php tpl_breadcrumbs(); ?></p></div><?php } ?>
               <?php if ($conf['youarehere']) { ?><div id="catlinks"><p class="catlinks"><?php tpl_youarehere(); ?></p></div><?php } ?>
               <?php html_msgarea()?>
               <div id="qsearch__out" class="ajax_qsearch JSpopup"></div>
               <?php if ($_REQUEST['mbdo'] == 'cite')
                        @include(dirname(__FILE__).'/do_cite.php');
                     else if ($_REQUEST['mbdo'] == 'detail')
                        @include(dirname(__FILE__).'/do_detail.php');
                     else if ($_REQUEST['mbdo'] == 'media')
                        @include(dirname(__FILE__).'/do_media.php');
                     else
                        tpl_content();
               ?>
               <!-- end content -->
            </div> <!-- id="maincolContent" -->
            
            <div id="contentfooterNavigation" class="horizontalNavigation"> 
                  <?php 
                     if ($conf['useacl'] && $_SERVER['REMOTE_USER']) {    
                           echo '<ul >' .
                                  '<li >'; tpl_actionlink('edit'); echo '</li >'  .
                                  '<li >'; tpl_actionlink('history') ; echo '</li >' .
                                  '<li >'; tpl_actionlink('recent') ; echo '</li >' .
                                '</ul>';
                     } else {
                           echo '<ul>' .
                                  '<li>' ; echo tpl_pageinfo() . '</li >'  .
                                  '<li>' . tpl_userinfo() . '</li >' .
                                '</ul>';
                     }
                  ?>
            </div>
         </div>
         <!--right column-->
         <?php writeMBPortlet($monobook['personal'], 'rightcol', '', 'rightcol'); ?>         
      </div>

      
      
      <!--++++++++++++++++++Footer++++++++++++++-->
      <div class="clearer"> </div>
      <hr />
      <?php writeMBPortlet($monobook['footer'], 'footer', '', '', 'horizontalNavigation'); ?>      
      <!--++++++++++++++++++Cleanup++++++++++++++-->
      <a href="<?php echo DOKU_BASE.DOKU_SCRIPT;?>?do=recent" accesskey="r" style="visibility:hidden;" rel="nofollow">&nbsp;</a> 
      <?php tpl_indexerWebBug(); ?>
      <?php flush()?>
   </div><!-- id="pagewidth"-->
</body>
</html>


