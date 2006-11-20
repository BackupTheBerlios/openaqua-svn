<?php
if (!empty($INFO['userinfo'])) {
    $user = true;
}
/**
 * Thème pour Sandy
 * @author neolao <neo@neolao.com>
 * @link   http://resources.neolao.com/php/dokuwiki/templates
 */
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php echo $conf['lang']; ?>" lang="<?php echo $conf['lang']; ?>">
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
        <meta http-equiv="Content-Style-Type" content="text/css" />
        <?php tpl_metaheaders(); ?>
        <link rel="shortcut icon" type="image/x-icon" href="/favicon.ico"/>
        <title><?php echo hsc($conf['title']).wl($ID); ?></title>
    </head>
    <body>
        <div id="header"><?php tpl_link(wl(),'<img src="'.DOKU_TPL.'images/banner.png" alt="'.hsc($conf['title']).'"/>','name="dokuwiki__top" id="dokuwiki__top" accesskey="h" title="[ALT+H]"')?></div>
        <div id="menu">
            <ul>
                <?php include('menu.php'); ?>
            </ul>
        </div>
		<div id="body">
            <div id="body_top"></div>
            <p><?php tpl_youarehere(); ?></p>
			<?php flush(); ?>
            <?php tpl_content(); ?>
            <?php flush(); ?>
            <div id="body_bottom"></div>
		</div>
        <div id="footer">
            <?php tpl_searchform()?>
            <ul>
                <li><?php tpl_actionlink('edit'); ?></li>
                <li><?php tpl_actionlink('login'); ?></li>
            </ul>
            <ul>
                <li><a href="http://dokuwiki.org/wiki:dokuwiki">DokuWiki</a></li>
            <?php if ($user) { ?>
                <li><?php tpl_actionlink('profile')?></li>
                <li><?php tpl_actionlink('admin'); ?>&nbsp;</li>
            <?php } ?>
            </ul>
        </div>
    </body>
</html>
