<?php
   /**
    * Theme Sandy 2
    * @author neolao <neo@neolao.com>
    * @author Claudia Behrens < Claudia.Behrens@openaqua.de>
    * @link   http://resources.neolao.com/php/dokuwiki/templates
    */
   
   //secure the php file from direct access
   if (!defined('DOKU_INC')) die(); 
   
   
   //set up a couple of variables
   if (isset($DOKU_TPL)==FALSE) $DOKU_TPL = DOKU_TPL; 
   if (isset($DOKU_TPLINC)==FALSE) $DOKU_TPLINC = DOKU_TPLINC;
   if (!empty($INFO['userinfo'])) $user = true;

   //use displaywikipage for the menu (if exists)
   if (file_exists(DOKU_PLUGIN.'displaywikipage/code.php')) include_once(DOKU_PLUGIN.'displaywikipage/code.php');
   //use the referrers plugin (if exists)      
   if (file_exists(DOKU_PLUGIN.'referrers/code.php')) include_once(DOKU_PLUGIN.'referrers/code.php');
   
   $myLogo = '<p>IVC adf asdfalsdaaaaafd</p><p>IVC adf asdfalsdaaaaafd</p>';
   
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php echo $conf['lang']?>" lang="<?php echo $conf['lang']?>" dir="<?php echo $lang['direction']?>">

<!--##################################################HTML HEADER-->
<head>
   <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
   <?php 
      if (function_exists('re_log_referrers')) re_log_referrers();
      @include (dirname(__FILE__).'/string_fn.php');
      @include(dirname(__FILE__).'/pref.php');
      @include(dirname(__FILE__).'/context.php');

      
      //make page title
      echo '<title>' . strip_tags($conf['title']) . ': '; tpl_pagetitle(); echo "</title>\n";
      
      tpl_metaheaders();
      
      //add a page icon
      echo '<link rel="shortcut icon" href="<' . DOKU_TPL . '/favicon.ico" />' . "\n";
      
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
            echo '.secedit2 {display:none;}';
            echo '-->';
            echo '</style>';
         }
      }
   ?>
</head>

   
    
<!--##################################################HTML BODY-->
<body>
   <!--Header-->
   <div id="header">
      <div id="headerLogo">
         <a href="<?php echo DOKU_BASE?>" title="Start Page">
           <img src="<?php echo $DOKU_TPL?>/images/logoOpenaqua.gif" alt="Logo Openaqua"  border="0" />
         </a>
      </div>
   </div>
   
   <!--Menu   -->
   <?php writeMBPortlet($monobook['navigation'], 'menu', '', ''); ?>

   
   <!--Body-->
   <div id="body">
      <div id="body_top" class="smallGreyListText">
         <?php if($conf['breadcrumbs']){?>
            <div class="breadcrumbs">
               <?php tpl_breadcrumbs()?>
            </div>
         <?php }?>
         <?php if($conf['youarehere']){?>
            <div class="breadcrumbs">
               <?php tpl_youarehere() ?>
            </div>
         <?php }?>
      </div>
      <!--content itself-->
      <?php flush(); ?>
      <?php tpl_content(); ?>
      <?php flush(); ?>
      
      
      <div id="body_bottom" class="smallGreyListText clearer">
                  <?php 
                     if ($conf['useacl'] && $_SERVER['REMOTE_USER']) {    
                           echo '<ul >' .
                                  '<li >'; tpl_actionlink('edit'); echo '</li >'  .
                                  '<li >'; tpl_actionlink('history') ; echo '</li >' .
                                  '<li >'; tpl_actionlink('recent') ; echo '</li >' .
                                '</ul>';
                     } else {
                           //shows last edit time and user at a page
                           echo '<ul ><li>' ; 
                           tpl_pageinfo(); 
                           echo  '</li ><li>'; 
                           tpl_userinfo();
                           echo '</li ></ul>';
                     }
                  ?>
      </div>
   </div>
   
   <!--Footer-->
   
   <div id="footer" class="smallGreyListText">
      <?php tpl_searchform()?>
      <ul>
         <li><?php tpl_actionlink('login'); ?></li>
         <?php if ($user) { ?>
            <li><?php tpl_actionlink('profile')?></li>
            <li><?php tpl_actionlink('admin'); ?>&nbsp;</li>
         <?php } ?>
      </ul>
   </div>
   <?php writeMBPortlet($monobook['copyright'], 'copyright', '', 'smallGreyListText'); ?>
   <!--Copyright-->
   
   
</body>
</html>
