<?php 
require_once(dirname(__FILE__)."/../include/common.inc.php");
require_once(dirname(__FILE__)."/../include/membermodel.cls.php");

function getToken($url,$type="GET"){
$ch = curl_init();
$header = "Accept-Charset: utf-8";
curl_setopt($ch, CURLOPT_URL, $url);
curl_setopt($ch, CURLOPT_CUSTOMREQUEST, $type);
curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, FALSE);
curl_setopt($url, CURLOPT_HTTPHEADER, $header);
curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);
curl_setopt($ch, CURLOPT_AUTOREFERER, 1);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
$data = curl_exec($ch);
return $data;
}

$appid = 'wx7d457421604147a8';
$appsecret = '3784cc22f31a5751cd6478880dce1cdc';


$code = $_GET['code'];

$state = $_GET['state']; 

//echo '<h1>code：</h1>'.$code ;
if(empty($code))$this->error('授权失败');

$token_url = 'https://api.weixin.qq.com/sns/oauth2/access_token?appid='.$appid.'&secret='.$appsecret.'&code='.$code.'&grant_type=authorization_code';
//echo '<h1>token_url</h1>'.$token_url;
$token = json_decode(getToken($token_url));
 
if (isset($token->errcode)) {
	//echo '<h1>错误：</h1>'.$token->errcode;
    //echo '<br/><h2>错误信息：</h2>'.$token->errmsg;
    exit;
}
$access_token_url = 'https://api.weixin.qq.com/sns/oauth2/refresh_token?appid='.$appid.'&grant_type=refresh_token&refresh_token='.$token->refresh_token;
//echo '<h1>access_token_url</h1>'.$access_token_url ;
$access_token = json_decode(getToken($access_token_url));

if (isset($access_token->errcode)) {
   // echo '<h1>错误：</h1>'.$access_token->errcode;
	//echo '<br/><h2>错误信息：</h2>'.$access_token->errmsg;
    exit;
}
$user_info_url = 'https://api.weixin.qq.com/sns/userinfo?access_token='.$access_token->access_token.'&openid='.$access_token->openid.'&lang=zh_CN';
//转成对象
//echo '<h1>user_info_url</h1>'.$user_info_url ;
$user_info = json_decode(getToken($user_info_url));

if (isset($user_info->errcode)) {
   //echo '<h1>错误：</h1>'.$user_info->errcode;
   //echo '<br/><h2>错误信息：</h2>'.$user_info->errmsg;
    exit;
}

//记录用户session


$openid = $user_info->openid;
$nickname = $user_info->nickname;
$sex = $user_info->sex;
if($sex == 1)
{
	$sex = '男';
}else if($sex == 0)
{
	$sex = '女';
}else
{
	$sex = '未知';
}
$user_info->sex = $sex;
$province=$user_info->province;
$city = $user_info->city;
$user_info->address = $province.' '.$city;
$headimgurl = $user_info->headimgurl;

$jointime = time();
$logintime = time();
$joinip = GetIP();
$loginip = GetIP();

//查询数据库是否存在 openid 的信息，如果不存在，存储用户信息
//检测用户名是否存在

$row = $dsql->GetOne("SELECT userid FROM `#@__member` WHERE userid = '$openid'");
if(is_array($row))
{
	//echo '<h1>已存在：</h1>'.$nickname;
}else
{

	$inQuery = "INSERT INTO `#@__member` (`mtype` ,`userid` ,`uname` ,`sex` ,`face`,`jointime` ,`joinip` ,`logintime` ,`loginip` )
	       VALUES ('个人','$openid','$nickname','$sex','$headimgurl','$jointime','$joinip','$logintime','$loginip'); ";
	if($dsql->ExecuteNoneQuery($inQuery))
	{
		//echo '<h1>保存成功：</h1>'.$nickname;
	}else
	{

		//echo '<h1>保存失败：</h1>'.$inQuery;
	}
}

echo '
<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>个人中心</title>
<link href="/public/css/css.css" rel="stylesheet" type="text/css" />
<script type="text/javascript" src="/public/js/jquery-1.11.0.js"></script>
<script type="text/javascript" src="/public/js/zsy.js"></script>
<script type="text/javascript" src="/public/js/SuperSlide.js"></script>
</head>

<body>
<div class="touxiang">


<img src="'.$user_info->headimgurl.'">
<p>'.$user_info->nickname.'</p>
  
</div>
<div class="grzx">
	<div class="grzx_a">


 <p><span>手机</span>139****8910</p>
 <p><span>性别</span>'.$user_info->sex.'</p><p><span>地址</span>'.$user_info->address.'</p>

    	
    </div>
	<div class="grzx_b">
    	<h3>我的资产</h3>
        <ul>
        	<li><p><span>0</span>张</p><p>优惠券</p></li>
        	<li><p><span>0</span>分</p><p>积分</p></li>
			<div class="cl"></div>
        </ul>
    </div>
</div>
</body>
</html>
';

?>