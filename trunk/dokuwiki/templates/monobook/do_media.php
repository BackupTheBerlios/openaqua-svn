  <h1><?php echo hsc($lang['mediaselect'])?> <code><?php echo hsc($NS)?></code></h1>

  <div class="mediaselect">

    <div class="mediaselect-left">
      <strong><a href="<?php echo DOKU_BASE?>lib/exe/media.php?ns="><?php echo hsc($lang['namespaces'])?></a></strong>

      <?php tpl_medianamespaces()?>
    </div>

    <div class="mediaselect-right">
      <?php tpl_mediafilelist()?>

      <div class="uploadform">
      <?php tpl_mediauploadform()?>
      </div>
    </div>

  </div>