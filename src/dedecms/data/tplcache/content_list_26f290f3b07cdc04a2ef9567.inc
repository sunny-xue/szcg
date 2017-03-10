<?php
if(!isset($GLOBALS['_vars'])) $GLOBALS['_vars'] = array(); 
$fields = array();
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312 echo $cfg_soft_lang; ?>">
<title>文档管理</title>
<link rel="stylesheet" type="text/css" href="css/base.css">
<script language="javascript" src="../include/js/dedeajax2.js"></script>
<script language="javascript" src="js/ieemu.js"></script>
<script language="javascript" src="js/context_menu.js"></script>
<script language="javascript" src="js/main.js"></script>
<script language="javascript" src="js/list.js"></script>
<style type="text/css">
.atext:hover{
	text-decoration:underline;}
	


</style>
</head>
<body leftmargin="8" topmargin="8" background='images/allbg.gif' onLoad="ContextMenu.intializeContextMenu()">

<!--  快速转换位置按钮  -->
<table width="98%" border="0" cellpadding="0" cellspacing="0" bgcolor="#ccd9b9" align="center">
<tr>
 <td height="26" style="background:#fff;">
  <table width="98%" border="0" cellspacing="0" cellpadding="0">
  <tr>
  <td align="left">
  <input type='button' class="coolbg np" style="background:url(images/inputbg2.gif) no-repeat; width:72px; height:27px; color:#fff; text-align:center; border:none;" onClick="location='catalog_do.php?channelid=<?php echo $GLOBALS['channelid']; ?>&cid=<?php echo $GLOBALS['cid']; ?>&dopost=addArchives';" value='添加文档' />&nbsp;&nbsp;
  <?php if($adminid==$mid){ ?>
	<input type='button' class="coolbg np" style="background:url(images/inputbg1.gif) no-repeat; width:68px; height:25px; color:#fff; text-align:center; border:none;" onClick="location='content_list.php?cid=<?php echo $GLOBALS['cid']; ?>&mid=0';" value='全部文档' />
	<?php
}
else{
?>
	<input type='button' class="coolbg np" style="background:url(images/inputbg1.gif) no-repeat; width:68px; height:25px; color:#fff; text-align:center; border:none;" onClick="location='content_list.php?cid=<?php echo $GLOBALS['cid']; ?>&mid=<?php echo $cuserLogin->getUserID(); ?>';" value='我的文档' />
	<?php }  echo $GLOBALS['CheckUserSend']; ?>
 <input type='button' class="coolbg np" style="background:url(images/inputbg1.gif) no-repeat; width:68px; height:25px;color:#fff; text-align:center; border:none;" onClick="location='catalog_main.php';" value='栏目管理' />
 <input type='button' class="coolbg np" style="background:url(images/inputbg1.gif) no-repeat; width:68px; height:25px; color:#fff; text-align:center; border:none;" name='bb1' onClick="location='makehtml_list.php?cid=<?php echo $GLOBALS['cid']; ?>';" value='更新列表' />
 <input type='button' class="coolbg np" style="background:url(images/inputbg1.gif) no-repeat; width:68px; height:25px; color:#fff; text-align:center; border:none;" name='bb2' onClick="location='makehtml_archives.php?cid=<?php echo $GLOBALS['cid']; ?>';" value='更新文档' />
 <input type='button' class="coolbg np" style="background:url(images/inputbg1.gif) no-repeat; width:68px; height:25px;  color:#fff; text-align:center; border:none;" name='bb1' onClick="location='recycling.php?cid=<?php echo $GLOBALS['cid']; ?>';" value='回收站' />
 </td>
 </tr>
</table>
</td>
</tr>
</table>
  
<!--  内容列表   -->
<form name="form2">
<table width="98%" border="0" cellpadding="0" cellspacing="0" bgcolor="#CFCFCF" align="center" style="margin-top:8px">
<tr bgcolor="#E7E7E7" >
	<td height="25" colspan="9"  style="background:#fff; font-family:'微软雅黑'; font-size:14px; color:#467A00; height:25px; line-height:25px; font-weight:bold;">
	<?php echo $GLOBALS['positionname']; ?>列表&nbsp;&nbsp;&nbsp;&nbsp;<a href="#" title="" onClick="ShowHide('aa')" style="color:#CC6600;">点击按条件查看</a>
	</td>
</tr>

<tr>
	<td colspan="9">
		<form name='form3' action='content_list.php' method='get'>
		<input type='hidden' name='dopost' value='listArchives' />
		<div style="background:#eee; padding:8px 0 8px 20px; border:1px solid #FFBE7A; background:#FFFCED; display:none;" id="aa">
				
				  
				  <table>
				  	<tr>
						<td><select name='cid' style='width:150px'>
				  <option value='0'>选择栏目...</option>
					<?php echo $GLOBALS['optionarr']; ?>
				  </select></td>
				  
				  <td>关键字：<input type='text' name='keyword' value='<?php echo $GLOBALS['keyword']; ?>' style='width:120px' /></td>
				  <td><select name='orderby' style='width:80px'>
					<option value='id'>排序...</option>
					<option value='pubdate'>更新时间</option>
					<option value='sortrank'>置顶权值</option>
					<option value='click'>点击量</option>
					<option value='scores'>评论积分</option>
					<option value='lastpost'>最后评论</option>
				</select></td>
					<td><select name='flag' style='width:80px'>
					<option value=''>属性...</option>
					<?php echo $GLOBALS['flagsArr']; ?>
				</select></td>
				<td>  <input name="imageField" type="image" src="images/button_search.gif"  border="0" class="np" /></td>
					</tr>
				</table>
		</div>
		</form>
	</td>
</tr>

<tr align="center"  height="30" style="background:#EEF3F7 url(images/abg1.gif) left bottom repeat-x;">
	
	<td width="4%" style="border-right:1px solid #E5EDF2;">选择</td>
	<td width="5%" style="border-right:1px solid #E5EDF2;">ID</td>
	<td width="48%" style="border-right:1px solid #E5EDF2;">标题</td>
	<td width="10%" style="border-right:1px solid #E5EDF2;">更新时间</td>
	<td width="4%" style="border-right:1px solid #E5EDF2;">点击</td>
	<td width="5%" style="border-right:1px solid #E5EDF2;">HTML</td>
	<td width="5%" style="border-right:1px solid #E5EDF2;">权限</td>
	<td width="7%" style="border-right:1px solid #E5EDF2;">作者</td>
	<td width="10%" style="border-right:1px solid #E5EDF2;">操作</td>
</tr>
<?php
$atts = array();
$atts['tagname'] = 'datalist';
$blockValue = $this->refObj->GetArcList($atts,$this->refObj,$fields); 
if(is_array($blockValue)){
foreach( $blockValue as $key=>$fields )
{
?>
<tr align='center' bgcolor="#FFFFFF" height="35" align="center" onMouseMove="javascript:this.bgColor='#FFFCED';" onMouseOut="javascript:this.bgColor='#FFFFFF';">
	<td nowrap>
		<input name="arcID" type="checkbox" id="arcID" value="<?php echo $fields['id']; ?>" class="np" style="background:none;"/>
	</td>
	<td>
		<?php echo $fields['id']; ?>
	</td>
	<td align='left'>
		<span id="arc<?php echo $fields['id']; ?>">
			<a href='content_list.php?cid=<?php echo $fields['typeid']; ?>' style="color:#275D96;">[<?php echo GetTypename($fields['typeid']); ?>]</a>
			&nbsp;&nbsp;<a style="font-size:12px; color:#444444;" class="atext" href='archives_do.php?aid=<?php echo $fields['id']; ?>&dopost=editArchives'
				 oncontextmenu="ShowMenu(event,this,<?php echo $fields['id']; ?>,'<?php echo str_replace('\'', '', $fields['title']); ?>')">
				<?php echo $fields['title']; ?>
			</a>
		</span>
		&nbsp;&nbsp;<?php echo IsCommendArchives($fields['flag']); ?>
	</td>
	<td><?php echo GetDateMk($fields['senddate']); ?></td>
	<td><?php echo $fields['click']; ?></td>
	<td><?php echo IsHtmlArchives($fields['ismake']); ?></td>
	<td><?php echo GetRankName($fields['arcrank']); ?></td>
	<td><?php echo GetMemberName($fields['mid']); ?></td>
	<td>
		<!--<img src='images/trun.gif' title="属性" alt="属性" onClick="QuickEdit(<?php echo $fields['id']; ?>, event, this);" style='cursor:pointer' border='0' />
		<img src='images/gtk-edit.png' title="编辑" alt="编辑" onClick="editArc(<?php echo $fields['id']; ?>);" style='cursor:pointer' border='0' />
		<img src='images/part-list.gif' title="预览" alt="预览" onClick="viewArc(<?php echo $fields['id']; ?>);" style='cursor:pointer' border='0' />-->
		<a href="#" title="" onClick="QuickEdit(<?php echo $fields['id']; ?>, event, this);" class="font444">属性</a>|
		<a href="#" title="" onClick="viewArc(<?php echo $fields['id']; ?>);" class="font444">预览</a>
	</td>
</tr>
<tr><td colspan="9" style="margin:0; padding:0;background:#f2f2f2; height:1px; overflow:hidden;"></td></tr>
<?php
}
}?>
<tr bgcolor="#F6F6F6">
<td height="36" colspan="9">
	&nbsp;
	<a href="javascript:selAll()" class="coolbg">全选</a>
	<a href="javascript:noSelAll()" class="coolbg">取消</a>
	&nbsp;&nbsp;
	
	
	<a href="javascript:delArc(0)" class="coolbg">&nbsp;删除&nbsp;</a>
	<a href="javascript:;" onClick="moveArc(event,this,<?php echo (empty($channelid) ? 0 : $channelid); ?>)" class="coolbg">&nbsp;移动&nbsp;</a>
	<a href="javascript:updateArc(0)" class="coolbg">&nbsp;更新&nbsp;</a>
	<a href="javascript:checkArc(0)" class="coolbg">&nbsp;审核&nbsp;</a>
	<a href="javascript:adArc(0)" class="coolbg">&nbsp;推荐&nbsp;</a>
	<?php if($channelid==1) echo "	<a href=\"javascript:kwArc(0)\" class=\"coolbg\">&nbsp;自动关键字&nbsp;</a>\r\n"; ?>
	<a href="javascript:;" onClick="cAtts('attsAdd',event,this)" class="coolbg">&nbsp;增加属性&nbsp;</a>
	<a href="javascript:;" onClick="cAtts('attsDel',event,this)" class="coolbg">&nbsp;删除属性&nbsp;</a>
</td>
</tr>
</form>
<tr align="right" bgcolor="#F9FCEF">
	<td height="25" colspan="9" align="center">
		<?php
$atts = array();
$atts['tagname'] = 'pagelist';
$atts['listsize'] = '3';
 echo $this->refObj->GetPageList($atts,$this->refObj,$fields); 
?>

	</td>
</tr>
</table>



</body>
</html>