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

  <h1><?php echo hsc($lang['metaedit'])?> <code><?php echo hsc(noNS($IMG))?></code></h1>

  <div class="mediaedit">
		<?php/* everything in meta array is tried to save and read */?>

 		<div class="data">
			<form action="<?php echo DOKU_BASE?>lib/exe/media.php" accept-charset="utf-8" method="post">
				<input type="hidden" name="edit" value="<?php echo hsc($IMG)?>" />
				<input type="hidden" name="save" value="1" />

				<label for="title"><?php echo $lang['img_title']?></label>
				<input type="text" name="meta[Iptc.Headline]" id="title" class="edit"
         value="<?php echo hsc(tpl_img_getTag('IPTC.Headline'))?>" /><br />

				<label for="caption"><?php echo $lang['img_caption']?></label>
				<textarea name="meta[Iptc.Caption]" id="caption" class="edit" rows="5"><?php
          echo hsc(tpl_img_getTag(array('IPTC.Caption',
                                        'EXIF.UserComment',
                                        'EXIF.TIFFImageDescription',
                                        'EXIF.TIFFUserComment')));
        ?></textarea><br />

				<label for="artist"><?php echo $lang['img_artist']?></label>
				<input type="text" name="meta[Iptc.Byline]" id="artist" class="edit"
         value="<?php echo hsc(tpl_img_getTag(array('Iptc.Byline',
                                                    'Exif.TIFFArtist',
                                                    'Exif.Artist',
                                                    'Iptc.Credit')))?>" /><br />

				<label for="copy"><?php echo $lang['img_copyr']?></label>
				<input type="text" name="meta[Iptc.CopyrightNotice]" id="copy" class="edit"
         value="<?php echo hsc(tpl_img_getTag(array('Iptc.CopyrightNotice','Exif.TIFFCopyright','Exif.Copyright')))?>" /><br />


				<label for="keywords"><?php echo $lang['img_keywords']?></label>
        <textarea name="meta[Iptc.Keywords]" id="keywords" class="edit"><?php
          echo hsc(tpl_img_getTag(array('IPTC.Keywords',
                                        'EXIF.Category')));
        ?></textarea><br />


				<input type="submit" value="<?php echo $lang['btn_save']?>" title="ALT+S"
         accesskey="s" class="button" />

			</form>
 		</div>


    <div class="footer">
      <hr>
        <?php tpl_button('backtomedia')?>
    </div>
  </div>

</div>
</body>
</html>

