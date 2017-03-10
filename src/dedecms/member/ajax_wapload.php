<?php
require_once(dirname(__FILE__)."/../include/common.inc.php"); 
$dsql->safeCheck = false;
$id = isset($id) && is_numeric($id) ? $id : 1;
$p = isset($p) ? intval($p) : 0; 
$digg='';
if($p>0){
$p=($p-1)*8;
}else{
$p=0;
}

if($id != 0 ){
$wstr.=" and a.typeid=" . $id . " ";
}
$sql = "Select a.*,b.typename From #@__archives a left join #@__arctype b on a.typeid=b.id where a.channel=1 " . $wstr . " order by a.id desc limit " . $p . ",8"; 
$dsql->SetQuery($sql);
$dsql->Execute();
$km=1;
while ($row = $dsql->GetArray())
   {
   	$url=GetOneArchive($row['id']);
	$digg.='<ul>';
   	$digg.='<li><a href="'. $url['arcurl'] . '">'. $row['title'] .'<span>></span></a></li>';
    $digg.= '</ul>';
   }
AjaxHead(); 
echo $digg; 
exit(); 
?>