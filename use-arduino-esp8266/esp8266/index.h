const char mainPage[] PROGMEM = R"=====(
<html>
	<head>
		<meta charset="UTF-8">
		<title>Obstacle Avoiding Car And Controlled Via Wifi</title>
		<style>
			#controller1 th{
				border: 2px solid blue;
			}
			#controller2 th{
				width: 125px;
				height: 125px;
				text-align: center;
			}
			#controller2 button{
				width: 100px;
				height: 100px;
			}
			table,td{
				border-collapse: collapse;
				margin: auto; 
				padding: 10px;
				font-size: 15px;
				font-weight: bold;
			}
			td{
				border: 1px solid blue;
			}
		</style>
	</head>
	<body>
		<div style="width: 510px; margin: 50px auto; border: 1px solid blue;">
			<div style="width: 100%; height: 530px; border: 1px solid blue;">
				<h2 style="text-align: center">*BẢNG ĐIỀU KHIỂN*</h2>
				<table id="controller1" style="border: 1px solid blue; margin: 0 auto;">
					<tr>
						<th>Auto Mode</th>
						<th><a href="onAuto"><button>ON</button></a>&nbsp &nbsp <a href="offAuto"><button>OFF</button></a></p></th>
					</tr>
					<tr>
						<th>&nbsp Custom Speed &nbsp</th>
						<th><a href="minSpeed"><button>MIN</button></a>&nbsp <a href="mediumSpeed"><button>MEDIUM</button></a>&nbsp <a href="maxSpeed"><button>MAX</button></a></p></th>
					</tr>
				</table>
				<p></p>
				<table id="controller2" style="border: 1px solid blue;">
					<tr>
						<th></th>
						<th><a href="up"><button>UP</button></a><br><br></th>
						<th></th>
					</tr>
					<tr>
						<th><a href="left"><button>LEFT</button></a><br><br></th>
						<th><a href="/"><button>STOP</button></a><br><br></th>
						<th><a href="right"><button>RIGHT</button></a><br><br></th>
					</tr>
					<tr>
						<th></th>
						<th><a href="down"><button>DOWN</button></a><br><br></th>
						<th></th>
					</tr>
				</table>
			</div>
			<div style="clear: both"></div>
		</div>
	</body>
</html>
)=====";
