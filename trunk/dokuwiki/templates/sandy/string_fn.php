<?php
/** Determine the context of the buttons
 * for Monobook for DokuWiki
 * By Terence J. Grant
 * tjgrant [at] tatewake [dot] com
 * License: GPL v2
 */

function beginsWith( $str, $sub ) {
	return ( substr( $str, 0, strlen( $sub ) ) === $sub );
}
function endsWith( $str, $sub ) {
	return ( substr( $str, strlen( $str ) - strlen( $sub ) ) === $sub );
}
function contains($str, $sub) {
	return strstr( $str, $sub);
}

?>