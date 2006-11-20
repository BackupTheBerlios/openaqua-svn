<?php
/**
 * DokuWiki mmKaizen Template
 *
 * @link   http://www.mierzejewski.net/software/mmkaizen
 * @author Marcin Mierzejewski <marcin@mierzejewski.net>
 *
 */

 require_once(dirname(__FILE__).'/tpl_functions.php');
 @include(dirname(__FILE__).'/header.php');
?>

<body>
  <div class="Page">
		<div class="Header">

			<div class="Banner">
        <?php #tpl_link(wl(),$conf['title'],'name="top" accesskey="h" title="[ALT+H]"') ?>
        <!-- <div class="searchform"> <?php #tpl_searchform() ?> </div> -->
      </div>

			<div class="MenuContainer">
				<?php tpl_renderMenu(); ?>
			</div>

			<? if ( true == tpl_isEditMenu() ) { ?>
			<div style="clear: both;"></div>	
			<div class="MenuContainer">
				<?php tpl_editMenu(); ?>
			</div>
			<? } ?>

		</div> 
    <?php flush(); ?>
	
		<div class="Content">
		<?php html_msgarea() ?>
		<?php tpl_content()?>
		</div>
  
    <?php flush(); ?>

    <?php 
      if ($INFO['perm'] > AUTH_READ ) 
      { 
    ?>
    <div class="stylefoot">
      <div class="meta">
        <div class="doc">
          <?php tpl_pageinfo()?>
        </div>
        <div class="user">
          <?php tpl_userinfo()?>
        </div>
      </div>
      <?php tpl_bottombar(); ?>
    </div>
    <?php } ?>

		<div class="Footer">
  		<?echo $conf['tpl_mmKanso']['footer']; ?>
		</div>
	  <?php tpl_indexerWebBug();?>
  </div>
</body>
</html>
