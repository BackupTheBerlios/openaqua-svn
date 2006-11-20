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
 * @author Michael Klier <chi@chimeric.de>
 * additional editing by
 * @author Marcin Mierzejewski <marcin@mierzejewski.net>
 */

 require_once(dirname(__FILE__).'/tpl_functions.php');
 @include(dirname(__FILE__).'/header.php');
?>
<body>
<?php /*old includehook*/ @include(dirname(__FILE__).'/topheader.html')?>
<div class="Page">
<div class="Content">

  <?php html_msgarea()?>

  <?php flush()?>

  <?php /*old includehook*/ #@include(dirname(__FILE__).'/pageheader.html')?>
      <div class="content" style="width: <?php echo tpl_img_getTag('File.Width')+10; ?>px; padding-top: 15px;">
      <center>
  <?php #tpl_img(); ?>
  <img src="<?php echo ml($IMG);?>" width="<?php echo tpl_img_getTag('File.Width')?>" height="<? echo tpl_img_getTag('File.Height')?>">
  <br><br>Back to <?php echo tpl_pagelink($ID);?><br><br>
      </center>
      </div>
    </div>

  <?php flush()?>
</div>

<?php tpl_indexerWebBug();?>

</body>
</html>

