const char mainPage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <title>Obstacle Avoiding Car And Controlled Via Wifi</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />

    <style>
        body{
            background-color: rgb(196, 192, 192);
        }
		.wrap{
            width: 800px;
            height: auto;
            margin: auto;
            background-color: white;
        }
        .header h1{
            padding-top: 30px;
            text-align: center;
        }

        .content h2{
            text-align: center;
            padding-bottom: 10px;
        }

		.content__button{
			display: flex;
            text-align: center;
            justify-content: center;
            margin-top: 10px;
		}
        .button__speed1, .button__speed2, .button__speed3{
			padding: 17px 60px;
			margin: 0px 30px;
            border-radius: 10px;
            font-size: 1.5rem;
            font-weight: bold;
            text-decoration: none;
            color: white;
		}
        .button__speed1{
            background-color: rgb(69, 88, 190);
        }
        .button__speed2{
            background-color: rgb(41, 56, 143);
        }
        .button__speed3{
            background-color: rgb(14, 26, 95);
        }
        
        .button__speed1:hover, .button__speed2:hover, .button__speed3:hover{
            background-color: rgb(150, 160, 209);
            color: rgb(0, 0, 0);
        }
        .content__table{
            margin: auto;
            margin-top: 30px;
            margin-bottom: 30px;
        }
        .button__dk img{
            width: 150px;
        }

        .content__bottom{
            text-align: center;
			display: flex;
            justify-content: center;
            padding-bottom: 25px;
        }
        .button__auto, .button__stop{
            padding: 17px 60px;
			margin: 0px 30px;
            border-radius: 10px;
            font-size: 1.5rem;
            font-weight: bold;
            text-decoration: none;
            color: white;
        }
        .button__auto{
            background-color: rgb(0, 138, 18);
        }
        .button__stop{
            background-color: rgb(187, 6, 6);
        }
        .button__auto:hover{
            background-color: rgb(6, 187, 87);
        }
        .button__stop:hover{
            background-color: rgb(177, 36, 36);
        }
       
    </style>

</head>

<body>
    <div class="wrap">

        <div class="header">
            <h1>BẢNG ĐIỀU KHIỂN XE ARDUINO</h1>
        </div>
        <div class="content">
            <hr>
            <h2>ĐIỀU KHIỂN TỐC ĐỘ</h2>
            <div class="content__button">
                <div>
                    <a class="button__speed1" href="MOT" type="button">1</a>
                </div>
                <div>
                    <a class="button__speed2" href="HAI" type="button">2</a>
                </div>
                <div>
                    <a class="button__speed3" href="BA" type="button">3</a>
                </div>
            </div>

            <div>
                <table class="content__table">
                    <tr>
                        <td></td>
                        <td>
                            <a class="button__dk" href="TIEN"><img src="https://png.pngtree.com/png-vector/20190511/ourlarge/pngtree-vector-arrows-arrow-icon-arrow-vector-icon-arrow-png-image_1005940.jpg" style="transform: rotate(-90deg);"></a>
                        </td>
                        <td></td>
                    </tr>
                    <tr>
                        <td>
                            <a class="button__dk" href="TRAI"><img src="https://png.pngtree.com/png-vector/20190511/ourlarge/pngtree-vector-arrows-arrow-icon-arrow-vector-icon-arrow-png-image_1005940.jpg" style="transform: rotate(180deg);"></a>
                        </td>
                        <td></td>
                        <td>
                            <a class="button__dk" href="PHAI"><img src="https://png.pngtree.com/png-vector/20190511/ourlarge/pngtree-vector-arrows-arrow-icon-arrow-vector-icon-arrow-png-image_1005940.jpg" ></a>
                        </td>
                    </tr>
                    <tr>
                        <td></td>
                        <td>
                            <a class="button__dk" href="LUI"><img src="https://png.pngtree.com/png-vector/20190511/ourlarge/pngtree-vector-arrows-arrow-icon-arrow-vector-icon-arrow-png-image_1005940.jpg" style="transform: rotate(90deg);" /></a>
                        </td>
                        <td></td>
                    </tr>

                </table>
                <div class="content__bottom">
                    <div>
                        <a class="button__auto" href="AUTO" type="button" >AUTO</a>
                    </div>
                    <div>
                        <a class="button__stop" href="STOP" type="button" >STOP</a>
                    </div>
                </div>

            </div>
        </div>
    </div>
</body>
</html>

)=====";
