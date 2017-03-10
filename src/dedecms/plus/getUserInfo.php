<?php 

//发布信息
//爆料
//个人中心
$appid = 'wx7d457421604147a8';
if(emptyempty($_SESSION['user'])){  
	header('location:https://open.weixin.qq.com/connect/oauth2/authorize?appid='.$appid.'&redirect_uri=http%3a%2f%2fweixin.xyszhcg.org.cn%2fplus%2foauth.php&response_type=code&scope=snsapi_userinfo&state=STATE#wechat_redirect');
}else
{
	
}
 ?>}
