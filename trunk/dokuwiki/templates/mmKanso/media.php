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
 *
 * Modification for mmClean Theme
 * @author Marcin Mierzejewski <marcin@mierzejewski.net>
 */

 require_once(dirname(__FILE__).'/tpl_functions.php');
 @include(dirname(__FILE__).'/header.php');
?>
<body>
<div class="dokuwiki">
  <?php html_msgarea()?>

  <h1 style="background:none;"><?php echo hsc($lang['mediaselect'])?> <code style="background:none;"><?php echo hsc($NS)?></code></h1>

  <div class="mediaselect">

    <div class="mediaselect-left">
      <b><a href="<?php echo DOKU_BASE?>lib/exe/media.php?ns="><?php echo hsc($lang['namespaces'])?></a></b>

			<?php tpl_medianamespaces()?>
		</div>

    <div class="mediaselect-right">
      <?php tpl_mediafilelist()?>

			<div class="uploadform">
			<?php tpl_mediauploadform()?>
			</div>
		</div>

  </div>

</div>
</body>
</html>

