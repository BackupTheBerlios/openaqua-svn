<div id="media__manager" class="dokuwiki"><br/>
<table border=0 width=100% cellpadding=0 cellspacing=0><tr><td align="left" valign="top" id="media__left">
	<h1><?php echo hsc($lang['mediaselect'])?></h1>

	<?php /* keep the id! additional elements are inserted via JS here */?>
	<div id="media__opts"></div>

	<?php tpl_mediaTree() ?>
</td><td align="left" valign="top">
	<div id="media__right"><?php tpl_mediaContent() ?></div>
</td></tr></table>
</div>
