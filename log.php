<?php
 date_default_timezone_set("Belgrade/Serbia");
 
  $servername = "fdb13.biz.nf";
  $username = "*************";
  $password = "**********";
  $controller;
  $result;
  $sql;

  $conn = new mysqli($servername, $username, $password);
  mysqli_select_db($conn, $username);


  if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
  }
 
    if (isset($_GET['log'])) {
      $scan_id = $_GET['id'];
      $temperature = $_GET['tmp'];
      $humidity = $_GET['hmd'];
      $heat_index = $_GET['hix'];
      $flame_detection = $_GET['flm'];
      $smoke_detection = $_GET['smk'];
      $time = $_GET['tim'];   
      $lat = $_GET['lat'];
      $lon = $_GET['lon'];
      
     $sql = "INSERT INTO `inferino` (`scan_id`, `Date`, `Temp`, `Humidity`, `HIndex`, `FlameSensor`, `SmokeSensor`, `Latitude`, `Logitude`) VALUES (" . $scan_id . ",'" . $time . "','" . $temperature ."','" . $humidity . "','" . $heat_index . "','" . $flame_detection . "','" . $smoke_detection . "','" . $lat .  "','" . $lon . "')";
     $result = $conn->query($sql);
     echo "done";

    }

    if (isset($_GET['new_data'])) {
    	$dat = $_GET['date'];
    	$sql = "CREATE TABLE " . $dat . " ( id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,Temperature VARCHAR(30) NOT NULL,
Humidity VARCHAR(30) NOT NULL,
HeatIndex VARCHAR(50) NOT NULL,
FlameDetection VARCHAR(30) NOT NULL, 
SmokeDetection VARCHAR(30) NOT NULL,
Date VARCHAR(30) NOT NULL,
Longitute VARCHAR(30),
Latitute VARCHAR(30)
reg_date TIMESTAMP
) ";
$result = $conn->query($sql);
echo "wa";
echo $dat;
   }
    
    
    if (isset($_GET['update_id'])) {
      $myFileReader = fopen("scan_id.txt", "r");
      $tot = fread($myFileReader, filesize("scan_id.txt"));
      $final_tot = $tot + 1;
      fclose($myFileReader);
      $myFile = fopen("scan_id.txt", "w");
      fwrite($myFile, $final_tot);
      fclose($myFile);
      echo "done";
    }
    
    if (isset($_GET['get_id'])) {
      $myFileReader = fopen("scan_id.txt", "r");
      echo fread($myFileReader, filesize("scan_id.txt"));
    }
    
    if (isset($_GET['tot'])) {
    $texdi = $_GET['totr'];
      $myFile = fopen("Constructive.txt", 'w');
      fwrite($myFile, $texdi);
      fclose($myFile);
    }
    
   function ConstructToTable() {
   
   
   }
    echo 'dasda' . "\r\n";
echo "adsdad \r\n";
     
?>

