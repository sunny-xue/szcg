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
$tid = $state;
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
$user_info->$sex = $sex;
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

//--------------------------------------------------------------------
//$t1 = ExecTime();

$tid = (isset($tid) && is_numeric($tid) ? $tid : 0);

$channelid = (isset($channelid) && is_numeric($channelid) ? $channelid : 0);

if($tid==0 && $channelid==0) die(" Request Error! ");
if(isset($TotalResult)) $TotalResult = intval(preg_replace("/[^\d]/", '', $TotalResult));


//如果指定了内容模型ID但没有指定栏目ID，那么自动获得为这个内容模型的第一个顶级栏目作为频道默认栏目
if(!empty($channelid) && empty($tid))
{
    $tinfos = $dsql->GetOne("SELECT tp.id,ch.issystem FROM `#@__arctype` tp LEFT JOIN `#@__channeltype` ch ON ch.id=tp.channeltype WHERE tp.channeltype='$channelid' And tp.reid=0 order by sortrank asc");
    if(!is_array($tinfos)) die(" No catalogs in the channel! ");
    $tid = $tinfos['id'];
}
else
{
    $tinfos = $dsql->GetOne("SELECT ch.issystem FROM `#@__arctype` tp LEFT JOIN `#@__channeltype` ch ON ch.id=tp.channeltype WHERE tp.id='$tid' ");
}

if($tinfos['issystem']==-1)
{
    $nativeplace = ( (empty($nativeplace) || !is_numeric($nativeplace)) ? 0 : $nativeplace );
    $infotype = ( (empty($infotype) || !is_numeric($infotype)) ? 0 : $infotype );
    if(!empty($keyword)) $keyword = FilterSearch($keyword);
    $cArr = array();
    if(!empty($nativeplace)) $cArr['nativeplace'] = $nativeplace;
    if(!empty($infotype)) $cArr['infotype'] = $infotype;
    if(!empty($keyword)) $cArr['keyword'] = $keyword;
    include(DEDEINC."/arc.sglistview.class.php");
    $lv = new SgListView($tid,$cArr);
} else {
    include(DEDEINC."/arc.listview.class.php");
    $lv = new ListView($tid);
    //对设置了会员级别的栏目进行处理
    if(isset($lv->Fields['corank']) && $lv->Fields['corank'] > 0)
    {
        require_once(DEDEINC.'/memberlogin.class.php');
        $cfg_ml = new MemberLogin();
        if( $cfg_ml->M_Rank < $lv->Fields['corank'] )
        {
            $dsql->Execute('me' , "SELECT * FROM `#@__arcrank` ");
            while($row = $dsql->GetObject('me'))
            {
                $memberTypes[$row->rank] = $row->membername;
            }
            $memberTypes[0] = "游客或没权限会员";
            $msgtitle = "你没有权限浏览栏目：{$lv->Fields['typename']} ！";
            $moremsg = "这个栏目需要 <font color='red'>".$memberTypes[$lv->Fields['corank']]."</font> 才能访问，你目前是：<font color='red'>".$memberTypes[$cfg_ml->M_Rank]."</font> ！";
            include_once(DEDETEMPLATE.'/plus/view_msg_catalog.htm');
            exit();
        }
    }
}

if($lv->IsError) ParamError();

$lv->Display();
?>