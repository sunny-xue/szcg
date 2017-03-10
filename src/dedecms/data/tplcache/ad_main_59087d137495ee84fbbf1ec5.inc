<?php
if(!isset($GLOBALS['_vars'])) $GLOBALS['_vars'] = array(); 
$fields = array();
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312 echo $cfg_soft_lang; ?>">
<title>广告管理</title>
<link href="css/base.css" rel="stylesheet" type="text/css">
</head>
<body background="images/allbg.gif" leftmargin="8" topmargin='8'>
<table width="98%" border="0" align="center" cellpadding="3" cellspacing="0" bgcolor="#D6D6D6">
  <tr>
    <td height="28" colspan="7" style="padding-left:10px; background:#fff; border-bottom:1px solid #fff;">
      <b><a href="ad_main.php" style="color:#4B8200; font-size:16px;">广告管理</a></b>
	  <a href="ad_add.php" style="width:90px; height:27px; background:url(images/inputbg3.gif) no-repeat; border:none; color:#fff; display:block; text-align:center; float:right; margin-right:10px;">增加一个新广告</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    <a href="adtype_main.php" style=" float:right;width:90px; height:27px; background:url(images/inputbg3.gif) no-repeat; border:none; color:#fff; display:block;  float:right; margin-left:5px; text-align:center;">广告分类管理</a><div style="clear:both;"></div></td>
</tr>
  <tr>
    <td height="28" colspan="7" style="padding-left:10px;border:1px solid #FFBE7A;" bgcolor="#FFFCED"><table style="">
      <tr>
        <form action='ad_main.php' method='get' name='form3' id="form3">
          <input type='hidden' name='dopost' value='listArchives' />
          <td><table width='600' border='0' cellpadding='0' cellspacing='0'>
            <tr>
              <td width='120' align='center'>请选择分类：</td>
              <td width='124'><select name='clsid' style='width:150' id="clsid">
                <option value='0'>默认分类...</option>
                
          	<?php echo $option;?>
          
              </select></td>
              <td width='71'> 关键字： </td>
              <td width='185'><input type='text' name='keyword' style='width:150' /></td>
              <td width="130" align="left"><input name="imageField" type="image" src="images/button_search.gif"  border="0" class="np" /></td>
            </tr>
          </table></td>
        </form>
      </tr>
    </table></td>
  </tr>
  <tr align="center"  bgcolor="#EEF3F7"" height="24"> 
      <td width="8%">编号</td>
      <td width="20%">分类</td>
      <td width="20%">广告名称</td>
      <td width="12%">投放范围</td>
      <td width="11%">是否限时</td>
      <td width="11%">结束时间</td>
      <td width="18%">管理</td>
   </tr>
   
   <?php
$atts = array();
$atts['tagname'] = 'datalist';
$blockValue = $this->refObj->GetArcList($atts,$this->refObj,$fields); 
if(is_array($blockValue)){
foreach( $blockValue as $key=>$fields )
{
?>
    <tr align="center" bgcolor="#FFFFFF" height="30"  onMouseMove="javascript:this.bgColor='#FCFDEE';" onMouseOut="javascript:this.bgColor='#FFFFFF';"> 
        <td class="bline"><?php echo $fields['aid']; ?></td>
        <td class="bline"><?php echo TestType($fields['clsname'],1); ?></td>
        <td class="bline"><?php echo $fields['adname']; ?></td>
        <td class="bline"><?php echo TestType($fields['typename']); ?></td>
        <td class="bline"><?php echo TimeSetValue($fields['timeset']); ?></td>
        <td class="bline"><?php echo GetDateMk($fields['endtime']); ?></td>
        <td class="bline">
         <a href='ad_edit.php?aid=<?php echo $fields['aid']; ?>&dopost=gettag'>[代码]</a>
         <a href='ad_edit.php?aid=<?php echo $fields['aid']; ?>&dopost=edit'>[更改]</a>
		     <a href='ad_edit.php?aid=<?php echo $fields['aid']; ?>&dopost=delete'>[删除]</a>
		    </td>
     </tr>
		<?php
}
}?>
     <tr align="center" bgcolor="#EEF3F7" height="34"> 
      <td colspan="7">
      	<?php
$atts = array();
$atts['tagname'] = 'pagelist';
$atts['listsize'] = '5';
 echo $this->refObj->GetPageList($atts,$this->refObj,$fields); 
?>

      </td>
     </tr>
   </table>
   </td>
</tr>
</table>
</body>
</html>