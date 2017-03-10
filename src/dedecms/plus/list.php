<?php
/**
 *
 * 栏目列表/频道动态页
 *
 * @version        $Id: list.php 1 15:38 2010年7月8日Z tianya $
 * @package        DedeCMS.Site
 * @copyright      Copyright (c) 2007 - 2010, DesDev, Inc.
 * @license        http://help.dedecms.com/usersguide/license.html
 * @link           http://www.dedecms.com
 */
require_once(dirname(__FILE__)."/../include/common.inc.php");

$tid = (isset($tid) && is_numeric($tid) ? $tid : 0);

$appid = 'wx7d457421604147a8';
$url = 'https://open.weixin.qq.com/connect/oauth2/authorize?appid='.$appid.'&redirect_uri=http%3a%2f%2fweixin.xyszhcg.org.cn%2fplus%2foauth.php&response_type=code&scope=snsapi_userinfo&state='.$tid.'#wechat_redirect';
header('location:'.$url);
?>