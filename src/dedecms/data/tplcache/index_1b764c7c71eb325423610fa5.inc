<?php
if(!isset($GLOBALS['_vars'])) $GLOBALS['_vars'] = array(); 
$fields = array();
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title>会员中心 -<?php echo $cfg_webname; ?></title>
<meta http-equiv="Content-Type" content="text/html; charset=<?php echo $cfg_soft_lang; ?>" />

<link href="/public/css/css.css" rel="stylesheet" type="text/css" />
<script type='text/javascript' src="/public/js/jquery-1.11.0.js"></script>
<script type='text/javascript' src="/public/js/zsy.js"></script>

<script type='text/javascript' src="/public/js/SuperSlide.js"></script>
</head>
<body>
<div class="touxiang">
	<img src="<?php echo $GLOBALS['_vars']['face']; ?>">
    <p><?php echo $GLOBALS['_vars']['uname']; ?></p>
</div>
<div class="grzx">
	<div class="grzx_a">
    	<p><span>手机</span>139****8910</p>
    	<p><span>性别</span><?php echo $GLOBALS['_vars']['sex']; ?></p>
    	<p><span>地址</span>阳城路第六大街105弄131号112室</p>
    </div>
	<div class="grzx_b">
    	<h3>我的资产</h3>
        <ul>
        	<li><p><span>21</span>张</p><p>优惠券</p></li>
        	<li><p><span>221</span>分</p><p>积分</p></li>
        </ul>
    </div>
</div>
</body>
</html>