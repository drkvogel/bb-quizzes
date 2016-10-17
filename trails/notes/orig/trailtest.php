<?php
ini_set('include_path', "..");
include_once("loadSystemVars.php");
$pagetitle  = 'Healthy Mind study =>TrailTest section<= ';
$secid      = 'hm05';
if ((!isset($_POST["partid"]) || !isset($_POST["sid"]) || !isset($_POST["lsq"]) || !isset($_POST["seqord"])|| !isset($_POST["studytypeuid"]))) {
    logger("INFO", "$secid errorcode =>error params missing");
    $HexString = StringToHex('bad parameters');
    header("Location: $httpType://$URLRoot/error.php?error=$HexString");
    exit();
}
$pid = $_POST["partid"];
$sid = $_POST["sid"];
$lsq = $_POST["lsq"];
$seqord = $_POST["seqord"];
$studytypeuid = $_POST["studytypeuid"];
$svrtim = date("Y-m-d H:i:s T", time());
$custom = getCustom($sid);
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd"> 
<html>
<head>
<meta http-equiv="Expires" content="Mon, 26 Jul 1997 05:00:00 GMT">
<meta http-equiv="Pragma" content="no-cache">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<meta http-equiv="X-UA-Compatible" content="IE=edge"> 
<title>Healthy minds</title>
<link rel="icon" href="<?php echo $httpType ?>://<?php echo $URLRoot ?>/graphics/favicon.ico" type="image/x-icon">
<link rel="shortcut icon" href="<?php echo $httpType ?>://<?php echo $URLRoot ?>/graphics/favicon.ico" type="image/x-icon">
<link rel="stylesheet" type="text/css" href="<?php echo $httpType ?>://<?php echo $URLRoot ?>/common/biobank_cb.css">
<link rel="stylesheet" type="text/css" href="TrailMaking/trailtest.css">
    <!--[if lt IE 9]>
    <script type="text/javascript" src="common/ie7/ie7.js"></script>
    <![endif]-->
<script src="<?php echo $httpType;?>://<?php echo $URLRoot; ?>/common/script.js" type="text/javascript"></script>
<script src="common/hmTimer.js" type="text/javascript"></script>
<script type="text/javascript" src="common/json2.js"></script>
<script type="text/javascript">
    /* ************ © Copyright 2013 Cardiff University ******** */
<?php echo <<<EOT
    var sectionid = "$secid;"; //This must be unique and match the section id on the database
EOT
?>
</script>
<script type="text/javascript" src="<?php echo $httpType ?>://<?php echo $URLRoot ?>/common/jquery-1.9.1.min.js"></script>
    <?php echo $custom->css ?>
</head>
<body>
<div id="main">
<div id="jsversion" class="viz"></div>
<div id="headerdiv">
    <?php echo $custom->header; ?>
</div>
<form action="<?php echo $httpType ?>://<?php echo $URLRoot ?>/StoreData.php" method="POST" id="fm1">
    <div>
        <input type="hidden" name="sid" value="<?php echo $sid; ?>"/>
        <input type="hidden" name="pid" value="<?php echo $pid; ?>"/>
        <input type="hidden" name="lsq" value="<?php echo $lsq; ?>"/>
        <input type="hidden" name="seqord" value="<?php echo $seqord; ?>"/>
    	  <input type="hidden" name="studytypeuid" value="<?php echo $studytypeuid; ?>"/>
        <input type="hidden" id="timererror" name="timererror" value="-1" />
        <input type="hidden" id="performaceTimer" name="performaceTimer" value="-1" />
        <input type='hidden' id="levelerrors0" name="levelerrors0" value='-1'>
        <input type='hidden' id="levelerrors1" name="levelerrors1" value='-1'>
        <input type='hidden' id="levelerrors2" name="levelerrors2" value='-1'>
        <input type='hidden' id="levelerrors3" name="levelerrors3" value='-1'>
        <input type='hidden' id="levelelapsed0" name="levelelapsed0" value='-1'>
        <input type='hidden' id="levelelapsed1" name="levelelapsed1" value='-1'>
        <input type='hidden' id="levelelapsed2" name="levelelapsed2" value='-1'>
        <input type='hidden' id="levelelapsed3" name="levelelapsed3" value='-1'>
        <input type="hidden" name="datestarted" value="<?php echo $svrtim;?>">
        <input type='hidden' id="abandon" name="abandon" value='0'>
        <input type="hidden" id="totelapsed" name="totelapsed" value="-1">
        <input type="hidden" id="responses" name="responses" value="">
    </div>
</form>
<div id="introtable" style="width: 100%;margin: 0;">
  <table class="centred toppadding" style="height: 100%;">
    <tr>
        <td style="height: auto;">&nbsp;</td>
    </tr>
    <tr>
    <td style="width:450px;">
    <div id="wait" class="thanks">
      <table width="100%" border="0" cellspacing="0" cellpadding="0">
      <tr><td>&nbsp;</td></tr>
      <tr>
        <td style="text-align:center;">
           <h2 id="timesup">This section is now complete.<br><br>Thank you for doing it.</h2>
       </td>
       </tr>
     </table>
    </div>
       <div id="intro" class="textinvis">
           <p>We now want to measure your coordination.</p><br>
       </div>
        <div id="inst_nextbutton" class="textinvis">
           <table class="rows" border="0" cellspacing="0" cellpadding="0">
             <tr>
               <td class="sidebackground">&nbsp;</td>
               <td><p>Click &quot;Next&quot; to take the test. </p></td>
               <td class="sidebackground">&nbsp;</td>
             </tr>
           </table>
       </div>
       <div id="nextbutton" class="textinvis">
         <table class="rows" border="0" cellspacing="0" cellpadding="0">
           <tr>
             <td class="sidebackground">&nbsp;</td>
             <td class="buttontd">
                 <p><input type="button" class="btn_submit" onclick="nextDiv1()" value="Next" /></p>
             </td>
             <td class="sidebackground">&nbsp;</td>
           </tr>
         </table>
       </div>
     </td>
   </tr>
   <tr>
     <td style="height: auto;">&nbsp;</td>
   </tr>
 </table>
</div>
<div id="testtable" style="height: 100%;width: 100%;margin: 0;display: none;">
 <table class="centred toppadding" style="height: 100%;">
   <tr>
     <td style="height: auto;">&nbsp;</td>
   </tr>
   <tr>
     <td id="tmttd" style="width:450px;">

<!-- practicea -->

       <div id="practicea" style="width: 100%;height: 100%;display: none;">
         <div id="relpospa" class="relpos" style="display: block;height: 274px;width: 450px;">
           <img id="practice_a_back" src="TrailMaking/practice_a_gifs/practice_a_back.gif" alt="white background" style="position: relative;top: 0;left: 0;" />
           <img id="practice_a_red" src="TrailMaking/practice_a_gifs/practice_a_red.gif" alt="Red background" style="display:none;position: absolute;top: 0;left: 0;" />
           <img id="s01" src="TrailMaking/practice_a_gifs/s01.gif" alt="Halo 1" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="s12" src="TrailMaking/practice_a_gifs/s12.gif" alt="Line 1 to 2" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="s23" src="TrailMaking/practice_a_gifs/s23.gif" alt="Line 2 to 3" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="s34" src="TrailMaking/practice_a_gifs/s34.gif" alt="Line 3 to 4" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="s45" src="TrailMaking/practice_a_gifs/s45.gif" alt="Line 4 to 5" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="s56" src="TrailMaking/practice_a_gifs/s56.gif" alt="Line 5 to 6" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="s67" src="TrailMaking/practice_a_gifs/s67.gif" alt="Line 6 to 7" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="s78" src="TrailMaking/practice_a_gifs/s78.gif" alt="Line 7 to 8" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="tmt_practice_a" src="TrailMaking/practice_a_gifs/tmt_practice_a.gif" alt="Trail maker part 2" style="position: absolute;top: 0;left: 0;" usemap="#practiceamap" />
           <map id="practiceamap" name="practiceamap">
             <area id="apr0" nohref shape="circle" coords="245,167,20" alt="circle 1" onmousedown="clicked('0')">
             <area id="apr1" nohref shape="circle" coords="285,66,20" alt="circle 2" onmousedown="clicked('1')">
             <area id="apr2" nohref shape="circle" coords="384,127,20" alt="circle 3" onmousedown="clicked('2')">
             <area id="apr3" nohref shape="circle" coords="325,156,20" alt="circle 4" onmousedown="clicked('3')">
             <area id="apr4" nohref shape="circle" coords="353,236,20" alt="circle 5" onmousedown="clicked('4')">
             <area id="apr5" nohref shape="circle" coords="97,217,20" alt="circle 6" onmousedown="clicked('5')">
             <area id="apr6" nohref shape="circle" coords="48,117,20" alt="circle 7" onmousedown="clicked('6')">
             <area id="apr7" nohref shape="circle" coords="176,111,20" alt="circle 8" onmousedown="clicked('7')">
           </map>
         </div>
         <div style="height: 7em;border: 1px solid white;">
           <p id="praca_inst" class="text">We now want to measure your co-ordination<br><br>This is a practice. Beginning with number 1, join all the circles in numeric order by clicking the next numbered circle. Please work as quickly and accurately as you can.</p>
           <p id="parta_inst" class="text viz">Well done.<br /><br /><input type="button" class="btn_submit" value="Begin Test" onclick="gotoNextLevel()" /></p>
         </div>
       </div>

<!-- parta -->

       <div id="parta" style="width: 100%;height: 100%;display: none;">
         <div id="relposa" class="relpos" style="width: 450px;height: 546px;display: block;">
           <img id="part_a_back" src="TrailMaking/part_a_gifs/part_a_back.gif" alt="white background" style="position: relative;top: 0;left: 0;" />
           <img id="part_a_red" src="TrailMaking/part_a_gifs/part_a_red.gif" alt="Red background" style="display:none;position: absolute;top: 0;left: 0;" />
           <img id="t01" src="TrailMaking/part_a_gifs/t01.gif" alt="Halo 1" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="t12" src="TrailMaking/part_a_gifs/t12.gif" alt="Line 1 to 2" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="t23" src="TrailMaking/part_a_gifs/t23.gif" alt="Line 2 to 3" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="t34" src="TrailMaking/part_a_gifs/t34.gif" alt="Line 3 to 4" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="t45" src="TrailMaking/part_a_gifs/t45.gif" alt="Line 4 to 5" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="t56" src="TrailMaking/part_a_gifs/t56.gif" alt="Line 5 to 6" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="t67" src="TrailMaking/part_a_gifs/t67.gif" alt="Line 6 to 7" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="t78" src="TrailMaking/part_a_gifs/t78.gif" alt="Line 7 to 8" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="t89" src="TrailMaking/part_a_gifs/t89.gif" alt="Line 8 to 9" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="t910" src="TrailMaking/part_a_gifs/t910.gif" alt="Line 9 to 10" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="t1011" src="TrailMaking/part_a_gifs/t1011.gif" alt="Line 10 to 11" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="t1112" src="TrailMaking/part_a_gifs/t1112.gif" alt="Line 11 to 12" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="t1213" src="TrailMaking/part_a_gifs/t1213.gif" alt="Line 12 to 13" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="t1314" src="TrailMaking/part_a_gifs/t1314.gif" alt="Line 13 to 14" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="t1415" src="TrailMaking/part_a_gifs/t1415.gif" alt="Line 14 to 15" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="t1516" src="TrailMaking/part_a_gifs/t1516.gif" alt="Line 15 to 16" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="t1617" src="TrailMaking/part_a_gifs/t1617.gif" alt="Line 16 to 17" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="t1718" src="TrailMaking/part_a_gifs/t1718.gif" alt="Line 17 to 18" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="t1819" src="TrailMaking/part_a_gifs/t1819.gif" alt="Line 18 to 19" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="t1920" src="TrailMaking/part_a_gifs/t1920.gif" alt="Line 19 to 20" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="t2021" src="TrailMaking/part_a_gifs/t2021.gif" alt="Line 20 to 21" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="t2122" src="TrailMaking/part_a_gifs/t2122.gif" alt="Line 21 to 22" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="t2223" src="TrailMaking/part_a_gifs/t2223.gif" alt="Line 22 to 23" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="t2324" src="TrailMaking/part_a_gifs/t2324.gif" alt="Line 23 to 24" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="t2425" src="TrailMaking/part_a_gifs/t2425.gif" alt="Line 24 to 25" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="tmt_part_a" src="TrailMaking/part_a_gifs/tmt_part_a.gif" alt="Trail maker part 2" style="position: absolute;top: 0;left: 0;" usemap="#partamap" />
           <map id="partamap" name="partamap">
               <area id="aa0" nohref shape="circle" coords="277,390,20" alt="circle1" onmousedown="clicked('0')">
               <area id="aa1" nohref shape="circle" coords="213,452,20" alt="circle2" onmousedown="clicked('1')" >
               <area id="aa2" nohref shape="circle" coords="319,452,20" alt="circle3" onmousedown="clicked('2')" >
               <area id="aa3" nohref shape="circle" coords="327,208,20" alt="circle4" onmousedown="clicked('3')" >
               <area id="aa4" nohref shape="circle" coords="206,267,20" alt="circle5" onmousedown="clicked('4')" >
               <area id="aa5" nohref shape="circle" coords="263,321,20" alt="circle6" onmousedown="clicked('5')" >
               <area id="aa6" nohref shape="circle" coords="185,356,20" alt="circle7" onmousedown="clicked('6')" >
               <area id="aa7" nohref shape="circle" coords="86,440,20" alt="circle8" onmousedown="clicked('7')" >
               <area id="aa8" nohref shape="circle" coords="107,490,20" alt="circle9" onmousedown="clicked('8')" >
               <area id="aa9" nohref shape="circle" coords="156,445,20" alt="circle10" onmousedown="clicked('9')" >
               <area id="aa10" nohref shape="circle" coords="206,511,20" alt="circle11" onmousedown="clicked('10')" >
               <area id="aa11" nohref shape="circle" coords="35,516,20" alt="circle12" onmousedown="clicked('11')" >
               <area id="aa12" nohref shape="circle" coords="65,287,20" alt="circle13" onmousedown="clicked('12')" >
               <area id="aa13" nohref shape="circle" coords="29,336,20" alt="circle14" onmousedown="clicked('13')" >
               <area id="aa14" nohref shape="circle" coords="29,69,20" alt="circle15" onmousedown="clicked('14')" >
               <area id="aa15" nohref shape="circle" coords="72,159,20" alt="circle16" onmousedown="clicked('15')" >
               <area id="aa16" nohref shape="circle" coords="149,36,20" alt="circle17" onmousedown="clicked('16')" >
               <area id="aa17" nohref shape="circle" coords="178,158,20" alt="circle18" onmousedown="clicked('17')" >
               <area id="aa18" nohref shape="circle" coords="284,117,20" alt="circle19" onmousedown="clicked('18')" >
               <area id="aa19" nohref shape="circle" coords="206,110,20" alt="circle20" onmousedown="clicked('19')" >
               <area id="aa20" nohref shape="circle" coords="236,29,20" alt="circle21" onmousedown="clicked('20')" >
               <area id="aa21" nohref shape="circle" coords="406,84,20" alt="circle22" onmousedown="clicked('21')" >
               <area id="aa22" nohref shape="circle" coords="419,493,20" alt="circle23" onmousedown="clicked('22')" >
               <area id="aa23" nohref shape="circle" coords="370,282,20" alt="circle24" onmousedown="clicked('23')" >
               <area id="aa24" nohref shape="circle" coords="355,508,20" alt="circle25" onmousedown="clicked('24')" >
           </map>
         </div>
       </div>

<!-- practiceb -->

       <div id="practiceb" style="width: 100%;height: 100%;display: none;">
         <div id="relpospb" class="relpos" style="display: block;height: 274px;width: 450px;">
           <img id="practice_b_back" src="TrailMaking/practice_b_gifs/practice_b_back.gif" alt="white background" style="position: relative;top: 0;left: 0;" />
           <img id="practice_b_red" src="TrailMaking/practice_b_gifs/practice_b_red.gif" alt="Red background" style="display:none;position: absolute;top: 0;left: 0" />
           <img id="s_1" src="TrailMaking/practice_b_gifs/s_1.gif" alt="Halo 1" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="s1a" src="TrailMaking/practice_b_gifs/s1A.gif" alt="Line 1 to A" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="sa2" src="TrailMaking/practice_b_gifs/sA2.gif" alt="Line A to 2" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="s2b" src="TrailMaking/practice_b_gifs/s2B.gif" alt="Line 2 to B" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="sb3" src="TrailMaking/practice_b_gifs/sB3.gif" alt="Line B to 3" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="s3c" src="TrailMaking/practice_b_gifs/s3C.gif" alt="Line 3 to C" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="sc4" src="TrailMaking/practice_b_gifs/sC4.gif" alt="Line C to 4" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="s4d" src="TrailMaking/practice_b_gifs/s4D.gif" alt="Line 4 to D" style="position: absolute;top: 0;left: 0;display: none;" />
           <img id="tmt_practice_b" src="TrailMaking/practice_b_gifs/tmt_practice_b.gif" alt="Trail maker practice 2" style="position: absolute;top: 0;left: 0;" usemap="#practicebmap" />
           <map id="practicebmap" name="practicebmap">
               <area id="bpr0" nohref shape="circle" coords="245,167,20" alt="circle 1" onmousedown="clicked('0')">
               <area id="bpr1" nohref shape="circle" coords="285,66,20" alt="circle A" onmousedown="clicked('1')">
               <area id="bp2r" nohref shape="circle" coords="384,127,20" alt="circle 2" onmousedown="clicked('2')">
               <area id="bpr3" nohref shape="circle" coords="325,156,20" alt="circle B" onmousedown="clicked('3')">
               <area id="bpr4" nohref shape="circle" coords="353,236,20" alt="circle 3" onmousedown="clicked('4')">
               <area id="bpr5" nohref shape="circle" coords="97,217,20" alt="circle C" onmousedown="clicked('5')">
               <area id="bpr6" nohref shape="circle" coords="48,117,20" alt="circle 4" onmousedown="clicked('6')">
               <area id="bpr7" nohref shape="circle" coords="177,101,20" alt="circle D" onmousedown="clicked('7')">
           </map>
         </div>
         <div style="height: 9em;border: 1px solid white;">
           <p id="pracb_inst" class="text">This is a practice. <!-- Beginning with number 1 then letter A, join all the circles in alternating numeric and alphabetic order by clicking the next numbered then the next lettered circle.-->Beginning with number 1 join all the circles alternating between numbers and letters in ascending order, e.g. 1 A 2 B. Please work as quickly and accurately as you can.</p>
            <p id="partb_inst" class="text viz">Well done.<br /><br /><input type="button" class="btn_submit" value="Begin Test" onclick="gotoNextLevel()" /></p>
          </div>
        </div>

<!-- partb -->

        <div id="partb" style="width: 100%;height: 100%;display: none;">
          <div id="relposb" class="relpos" style="width: 450px;height: 546px;display: block;">    
            <img id="part_b_back" src="TrailMaking/part_b_gifs/part_b_back.gif" alt="white background" style="position: relative;top: 0;left: 0;" />
            <img id="part_b_red" src="TrailMaking/part_b_gifs/part_b_red.gif" alt="Red background" style="display:none;position: absolute;top: 0;left: 0;" />
            <img id="t_1" src="TrailMaking/part_b_gifs/t_1.gif" alt="Halo 1" style="position: absolute;top: 0;left: 0;display: none;" />
            <img id="t1a" src="TrailMaking/part_b_gifs/t1A.gif" alt="Line 1 to A" style="position: absolute;top: 0;left: 0;display: none;" />
            <img id="ta2" src="TrailMaking/part_b_gifs/tA2.gif" alt="Line A to 2" style="position: absolute;top: 0;left: 0;display: none;" />
            <img id="t2b" src="TrailMaking/part_b_gifs/t2B.gif" alt="Line 2 to B" style="position: absolute;top: 0;left: 0;display: none;" />
            <img id="tb3" src="TrailMaking/part_b_gifs/tB3.gif" alt="Line B to 3" style="position: absolute;top: 0;left: 0;display: none;" />
            <img id="t3c" src="TrailMaking/part_b_gifs/t3C.gif" alt="Line 3 to C" style="position: absolute;top: 0;left: 0;display: none;" />
            <img id="tc4" src="TrailMaking/part_b_gifs/tC4.gif" alt="Line C to 4" style="position: absolute;top: 0;left: 0;display: none;" />
            <img id="t4d" src="TrailMaking/part_b_gifs/t4D.gif" alt="Line 4 to D" style="position: absolute;top: 0;left: 0;display: none;" />
            <img id="td5" src="TrailMaking/part_b_gifs/tD5.gif" alt="Line D to 5" style="position: absolute;top: 0;left: 0;display: none;" />
            <img id="t5e" src="TrailMaking/part_b_gifs/t5E.gif" alt="Line 5 to E" style="position: absolute;top: 0;left: 0;display: none;" />
            <img id="te6" src="TrailMaking/part_b_gifs/tE6.gif" alt="Line E to 6" style="position: absolute;top: 0;left: 0;display: none;" />
            <img id="t6f" src="TrailMaking/part_b_gifs/t6F.gif" alt="Line 6 to F" style="position: absolute;top: 0;left: 0;display: none;" />
            <img id="tf7" src="TrailMaking/part_b_gifs/tF7.gif" alt="Line F to 7" style="position: absolute;top: 0;left: 0;display: none;" />
            <img id="t7g" src="TrailMaking/part_b_gifs/t7G.gif" alt="Line 7 to G" style="position: absolute;top: 0;left: 0;display: none;" />
            <img id="tg8" src="TrailMaking/part_b_gifs/tG8.gif" alt="Line G to 8" style="position: absolute;top: 0;left: 0;display: none;" />
            <img id="t8h" src="TrailMaking/part_b_gifs/t8H.gif" alt="Line 8 to H" style="position: absolute;top: 0;left: 0;display: none;" />
            <img id="th9" src="TrailMaking/part_b_gifs/tH9.gif" alt="Line H to 9" style="position: absolute;top: 0;left: 0;display: none;" />
            <img id="t9i" src="TrailMaking/part_b_gifs/t9I.gif" alt="Line 9 to I" style="position: absolute;top: 0;left: 0;display: none;" />
            <img id="ti10" src="TrailMaking/part_b_gifs/tI10.gif" alt="Line I to 10" style="position: absolute;top: 0;left: 0;display: none;" />
            <img id="t10j" src="TrailMaking/part_b_gifs/t10J.gif" alt="Line 10 to J" style="position: absolute;top: 0;left: 0;display: none;" />
            <img id="tj11" src="TrailMaking/part_b_gifs/tJ11.gif" alt="Line J to 11" style="position: absolute;top: 0;left: 0;display: none;" />
            <img id="t11k" src="TrailMaking/part_b_gifs/t11K.gif" alt="Line 11 to K" style="position: absolute;top: 0;left: 0;display: none;" />
            <img id="tk12" src="TrailMaking/part_b_gifs/tK12.gif" alt="Line K to 12" style="position: absolute;top: 0;left: 0;display: none;" />
            <img id="t12l" src="TrailMaking/part_b_gifs/t12L.gif" alt="Line 12 to L" style="position: absolute;top: 0;left: 0;display: none;" />
            <img id="tl13" src="TrailMaking/part_b_gifs/tL13.gif" alt="Line L to 13" style="position: absolute;top: 0;left: 0;display: none;" />
            <img id="tmt_part_b" src="TrailMaking/part_b_gifs/tmt_part_bb.gif" alt="Trail maker part 2" style="position: absolute;top: 0;left: 0;" usemap="#partbmap" />
            <map id="partbmap" name="partbmap">
              <area id="bb0" nohref shape="circle" coords="228,232,20" alt="circle 1" onmousedown="clicked('0')">
              <area id="bb1" nohref shape="circle" coords="323,387,20" alt="circle A" onmousedown="clicked('1')">
              <area id="bb2" nohref shape="circle" coords="175,420,20" alt="circle 2" onmousedown="clicked('2')">
              <area id="bb3" nohref shape="circle" coords="203,111,20" alt="circle B" onmousedown="clicked('3')">
              <area id="bb4" nohref shape="circle" coords="234,169,20" alt="circle 3" onmousedown="clicked('4')">
              <area id="bb5" nohref shape="circle" coords="327,286,20" alt="circle C" onmousedown="clicked('5')">
              <area id="bb6" nohref shape="circle" coords="277,80,20" alt="circle 4" onmousedown="clicked('6')">
              <area id="bb7" nohref shape="circle" coords="386,78,20" alt="circle D" onmousedown="clicked('7')">
              <area id="bb8" nohref shape="circle" coords="380,246,20" alt="circle 5" onmousedown="clicked('8')">
              <area id="bb9" nohref shape="circle" coords="381,472,20" alt="circle E" onmousedown="clicked('9')">
              <area id="bb10" nohref shape="circle" coords="233,457,20" alt="circle 6" onmousedown="clicked('10')">
              <area id="bb11" nohref shape="circle" coords="130,498,20" alt="circle F" onmousedown="clicked('11')">
              <area id="bb12" nohref shape="circle" coords="155,225,20" alt="circle 7" onmousedown="clicked('12')">
              <area id="bb13" nohref shape="circle" coords="90,381,20" alt="circle G" onmousedown="clicked('13')">
              <area id="bb14" nohref shape="circle" coords="65,90,20" alt="circle 8" onmousedown="clicked('14')">
              <area id="bb15" nohref shape="circle" coords="108,268,20" alt="circle H" onmousedown="clicked('15')">
              <area id="bb16" nohref shape="circle" coords="149,79,20" alt="circle 9" onmousedown="clicked('16')">
              <area id="bb17" nohref shape="circle" coords="342,29,20" alt="circle I" onmousedown="clicked('17')">
              <area id="bb18" nohref shape="circle" coords="416,29,20" alt="circle 10" onmousedown="clicked('18')">
              <area id="bb19" nohref shape="circle" coords="408,409,20" alt="circle J" onmousedown="clicked('19')">
              <area id="bb20" nohref shape="circle" coords="422,520,20" alt="circle 11" onmousedown="clicked('20')">
              <area id="bb21" nohref shape="circle" coords="38,521,20" alt="circle K" onmousedown="clicked('21')">
              <area id="bb22" nohref shape="circle" coords="23,337,20" alt="circle 12" onmousedown="clicked('22')">
              <area id="bb23" nohref shape="circle" coords="56,452,20" alt="circle L" onmousedown="clicked('23')">
              <area id="bb24" nohref shape="circle" coords="32,40,20" alt="circle 13" onmousedown="clicked('24')">
            </map>
          </div>
        </div>
      </td>
    </tr>
    <tr>
      <td style="height: auto;">&nbsp;</td>
    </tr>
  </table>
</div>

<div id="timeoutdiv" class="viz" style="height: 100%;width: 100%;margin: 0;display: none;position: absolute;left: 0;top: 0;">
  <table class="centred" style="height: 100%;">
    <tr>
      <td style="height: auto;">&nbsp;</td>
    </tr>
    <tr>
      <td id="timeouttd" style="height: auto;">
        <div class="thanks" style="display: block;">
          <table>
            <tr>
              <td>
                <span id="timeoutmessage" style="text-align: center">
                  This section is now complete. Thank you for doing it.
                </span>
              </td>
            </tr>
            <tr>
              <td style="text-align: center">
                <input id="timeoutnext" type="button" class="btn_submit" value="Next" onclick="timedOutNext()" />
              </td>
            </tr>
          </table>
        </div>
      </td>
    </tr>
    <tr>
      <td style="height: auto;">&nbsp;</td>
    </tr>
  </table>
</div>

<script type="text/javascript" src="<?php echo $httpType ?>://<?php echo $URLRoot ?>/common/biobank_cb_common.js?d=<?php echo date('Ymdhis'); ?>"></script>
<script type="text/javascript" src="TrailMaking/trailtest.js"></script>

<script type="text/javascript" >
    $(document).ready(function () { loaded()});
</script>


<div id="abandonbar" class="abandonbar">
    <input id="abandonbutton" type="button" class="abandonbutton" value="Abandon" onclick="abandonit(0)" />
    <span id="versions2" class="abondonhiddentext"></span>
</div>
<div id="abandondiv" class="viz" style="height: 100%;width: 100%;margin: 0;display: none;position: absolute;left: 0;top: 0;">
  <table class="centred" style="height: 100%;">
    <tr>
      <td style="height: auto;">&nbsp;</td>
    </tr>
    <tr>
      <td id="abandontd" style="height: auto;">
        <div class="abandontext">
          <table style="border: 1px solid black; border-image: none; box-shadow: 3px 3px 0 #000;">
            <tr>
              <td>
                <span id="abandonmessage" class="abandontext" style="text-align: center">
                  If you stop mid section, you will not be able to complete this section.<br>You can take a break if you need one from the 'progress' page. Are you sure?
                </span>
              </td>
            </tr>
            <tr>
              <td style="text-align: center">
                <input id="abandonyes" type="button" class="abandonbutton1" value="Yes - abandon" onclick="abandonit(1)" />
                <input id="abandonno" type="button" class="abandonbutton1" value="No - continue" 
                  onclick="abandonit(2)" />
              </td>
            </tr>
          </table>
        </div>
      </td>
    </tr>
    <tr>
      <td style="height: auto;">&nbsp;</td>
    </tr>
  </table>
</div>
</div>

<?php echo <<<EOT
<!-- Website release $WebSiteRelease -->
EOT
?>

</body>
</html>
