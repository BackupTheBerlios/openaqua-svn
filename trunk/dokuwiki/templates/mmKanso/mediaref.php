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

  <h1><?php echo hsc($lang['reference'])?> <code><?php echo hsc(noNS($DEL))?></code></h1>

  <div class="mediaref">
    <div class="mediaref_head">
      <p><?php echo hsc($lang['ref_inuse'])?></p>
    </div>
  
    <?php tpl_showreferences($mediareferences)?>
	
	<div class="mediaref_footer">
	  <hr>
      <?php tpl_button('backtomedia')?>
    </div>
  </div>

</div>
</body>
</html>

