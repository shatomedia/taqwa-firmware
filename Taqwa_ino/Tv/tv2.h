const char tv2_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <title>TAQWA-TV</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body,
        html {
            height: 100%;
            margin: 0;
            font-family: Arial, Helvetica, sans-serif;
        }

        

        .container {
            position: absolute;
            font-size: 35vw;
            color: white;
            font-family: Arial, Helvetica, sans-serif;
            text-align: center;
            width: 100%;
            height: 100%;
        }
        .text-block {
            position: relative;
            background-color: rgb(255, 0, 0);
            margin-top: 8%;
        }


        .bg-utama {
            background-position: center;
            background-repeat: no-repeat;
            background-size: cover;
            background-color: black;
            height: 100%;
            width: 100%;
        }

        * {
            box-sizing: border-box;
        }

        #container {
            min-height: 100%;
            position: absolute;
        }

        /* Style the header */
        header {
            width: 100%;
            height: 18%;
            background: rgba(0, 0, 0, 0.9);
            position: absolute;
            top: 0px;
        }

        .kotakTanggal {
            padding-left: 10px;
            width: 20%;
            font-size: 2vw;
            line-height: 0.2vw;
            float: left;
            text-align: left;
        }

        .kotakNama {
            width: 50%;
            line-height: 0.2vw;
            float: left;
            color: #ffffff;
            text-align: center;
        }

        .kotakJam {
            width: 30%;
            font-size: 6vw;
            line-height: 0.2vw;
            float: left;
            text-align: center;
            color: rgb(192, 0, 0)
        }

        /* Style the content */
        article {
            height: 62%;
            width: 100%;
        }

        /* Style the footer */
        footer {
            padding-top: 10px;
            height: 20%;
            width: 100%;
            background: rgba(0, 0, 0, 0.9);
            position: absolute;
            bottom: 0px;
            text-align: center;
        }

        .kotakJadwal {
            padding: 0.2%;
            width: 14.25%;
            height: 5%;
            font-size: 2.6vw;
            line-height: 5vw;
            color: #ffffff;
            float: left;
        }
    </style>
</head>

<body class="bg-utama">





    <header>
        <div class="kotakTanggal">
            <p id="getHari" style="color:rgb(255, 225, 0); font-size: 2.8vw;"></p>
            <p id="getTanggal" style="color:rgb(255, 225, 0)"></p>
            <p id="getHijriyah" style="color:rgb(255, 225, 0)"></p>
        </div>

        <div class="kotakNama">
            <p id="namaMasjid" Style="font-size:4vw;; "></p>
            <p id="alamatMasjid" Style="font-size:1.7vw; color: rgb(138, 179, 255);"></p>
        </div>

        <div class="kotakJam">
            <p id="getJam"></p>
        </div>
    </header>


    <footer>
        <div class="kotakJadwal">
            <div style="background-color: rgb(192, 0, 0);">
                <a>SHUBUH</a>
            </div>
            <div style="background-color: black; font-size: 3.4vw;">
                <a><b id="getShubuh">-</b></a>
            </div>
        </div>

        <div class="kotakJadwal">
            <div style="background-color: rgb(192, 131, 0);">
                <a>SYURUQ</a>
            </div>
            <div style="background-color: black; font-size: 3.4vw;">
                <a><b id="getSyuruq">-</b></a>
            </div>
        </div>

        <div class="kotakJadwal">
            <div style="background-color: rgb(0, 132, 37);">
                <a>DHUHA</a>
            </div>
            <div style="background-color: black; font-size: 3.4vw;">
                <a><b id="getDhuha">-</b></a>
            </div>
        </div>


        <div class="kotakJadwal">
            <div style="background-color: rgb(0, 144, 192);">
                <a>DZUHUR</a>
            </div>
            <div style="background-color: black; font-size: 3.4vw; ">
                <a><b id="getDzuhur">-</b></a>
            </div>
        </div>

        <div class="kotakJadwal">
            <div style="background-color: rgb(0, 0, 192);">
                <a>ASHAR</a>
            </div>
            <div style="background-color: black; font-size: 3.4vw;">
                <a><b id="getAshar">-</b></a>
            </div>
        </div>

        <div class="kotakJadwal">
            <div style="background-color: rgb(109, 0, 192);">
                <a>MAGHRIB</a>
            </div>
            <div style="background-color: black; font-size: 3.4vw;">
                <a><b id="getMaghrib">-</b></a>
            </div>
        </div>

        <div class="kotakJadwal">
            <div style="background-color: rgb(192, 0, 186); ">
                <a>ISYA</a>
            </div>
            <div style="background-color: black; font-size: 3.4vw;">
                <a><b id="getIsya">-</b></a>
            </div>
        </div>

    </footer>

    <div class="container">
        <p id="getIqomah" class="text-block" ></p>
    </div>


    <iframe width="100%" height="100%"
        src="https://www.youtube.com/watch?v=Dru9vk8Cmfg">
    </iframe> 


    <script type="text/javascript">

        setInterval(function () { getData() }, 60000); //1 minute update rate
        setInterval(function () { getWaktu() }, 1000); //1 Seconds update rate
        setInterval(function () { getJadwal() }, 30000); //1 minute update rate

        function getWaktu() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) { document.getElementById("getJam").innerHTML = this.responseText }
            };
            xhttp.open("GET", "tvJam", true);
            xhttp.send();
            
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) { document.getElementById("getIqomah").innerHTML = this.responseText }
            };
            xhttp.open("GET", "tvIqomah", true);
            xhttp.send();
        }

        function getJadwal() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) { document.getElementById("getImsyak").innerHTML = this.responseText }
            };
            xhttp.open("GET", "tvImsyak", true);
            xhttp.send();

            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) { document.getElementById("getShubuh").innerHTML = this.responseText }
            };
            xhttp.open("GET", "tvShubuh", true);
            xhttp.send();

            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) { document.getElementById("getSyuruq").innerHTML = this.responseText }
            };
            xhttp.open("GET", "tvSyuruq", true);
            xhttp.send();

            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) { document.getElementById("getDhuha").innerHTML = this.responseText }
            };
            xhttp.open("GET", "tvDhuha", true);
            xhttp.send();

            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) { document.getElementById("getDzuhur").innerHTML = this.responseText }
            };
            xhttp.open("GET", "tvDzuhur", true);
            xhttp.send();

            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) { document.getElementById("getAshar").innerHTML = this.responseText }
            };
            xhttp.open("GET", "tvAshar", true);
            xhttp.send();

            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) { document.getElementById("getMaghrib").innerHTML = this.responseText }
            };
            xhttp.open("GET", "tvMaghrib", true);
            xhttp.send();

            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) { document.getElementById("getIsya").innerHTML = this.responseText }
            };
            xhttp.open("GET", "tvIsya", true);
            xhttp.send();
        }

        function getData() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) { document.getElementById("namaMasjid").innerHTML = this.responseText }
            };
            xhttp.open("GET", "getMasjid", true);
            xhttp.send();

            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) { document.getElementById("alamatMasjid").innerHTML = this.responseText }
            };
            xhttp.open("GET", "getAlamat", true);
            xhttp.send();

            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) { document.getElementById("getHari").innerHTML = this.responseText }
            };
            xhttp.open("GET", "tvHari", true);
            xhttp.send();

            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) { document.getElementById("getTanggal").innerHTML = this.responseText }
            };
            xhttp.open("GET", "tvTanggal", true);
            xhttp.send();

            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) { document.getElementById("getHijriyah").innerHTML = this.responseText }
            };
            xhttp.open("GET", "tvHijriyah", true);
            xhttp.send();


        }
    </script>

</body>

</html>

)=====";