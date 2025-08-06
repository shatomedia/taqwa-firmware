const char tv_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <title>TAQWA TV</title>

    <style>
        * {
            box-sizing: border-box;
        }

        /* container */
        .left-sidebar {
            display:flex;
            flex-wrap:wrap;
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


        /* columns */
        .left-sidebar > * {
            width:100%;
            padding:0.3rem;
        }

        /* tablet breakpoint */
        @media (min-width:768px) {
            .left-sidebar > *:nth-child(1) {
                width:calc(100% / 3 * 2);
            }
            .left-sidebar > *:nth-child(2) {
                width:calc(100% / 3);
                order:-1;
            }
        }

        ._fontJadwal {
            margin-top: 3.5%;
            margin-bottom: 3.5%;
            /*line-height: 1.2;*/
            font-size: 3.3vw;
            float: left;
            color: #FFFFFF;
            font-family: Arial, Helvetica, sans-serif;
        }

        .fontJadwal {
            margin-top: 3.5%;
            margin-bottom: 3.5%;
            /*line-height: 1.2;*/
            font-size: 3.3vw;
            float: right;
            color: #FFFFFF;
            font-family: Arial, Helvetica, sans-serif;
        }

        .fontNama {
            line-height: 0.5;
            font-size: 5.5vw;
            color: #FFFFFF;
            font-family: Arial, Helvetica, sans-serif;
        }

        .fontAlamat {
            line-height: 1.4;
            font-size: 2.5vw;
            color: #ffffff;
            font-family: Arial, Helvetica, sans-serif;
        }

        .fontJam {
            line-height: 1.4;
            font-size: 12vw;
            color: #FFFFFF;
            font-family: Arial, Helvetica, sans-serif;
        }

        .fontTanggal {
            line-height: 1.3;
            font-size: 3.3vw;
            font-style: normal;
            color: #FFFFFF;
            font-family: Arial, Helvetica, sans-serif;
        }
    </style>
</head>
<body style="background-color: rgb(0, 0, 0);">
    
    <div class="container">
        <p id="getIqomah" class="text-block"></p>
    </div>

    <div class="left-sidebar" >

        <div style="background-color:#000000; text-align: center;">    
            <br>    
            <a  class="fontNama"> <b id="namaMasjid">-</b></a>
            <br><br>
            <a id="alamatMasjid" class="fontAlamat">-</a>
            <br>
            <a id="_alamatMasjid" class="fontAlamat">-</a>
            <br>
            <hr style="width: 90%; margin-top: 4%; margin-bottom: 6%;"/>
            <a id="getJam" class="fontJam" > - </a>
            <hr style="width: 90%; margin-top: 8%; "/>
            <br>
            <a id="getKalender" class="fontTanggal">-</a>
            <br>
            <a id="getHijriyah" class="fontTanggal">-</a>
        </div>

        <div style="background-color:#000000; text-align: center;">

            <a class="_fontJadwal">IMSYAK </a> <a id="getImsyak"  class="fontJadwal">4 : 13</a>
            <hr style=" width: 100%;">
            <a class="_fontJadwal">SHUBUH </a> <a id="getShubuh"  class="fontJadwal">4 : 23</a>
            <hr style=" width: 100%;">
            <a class="_fontJadwal">SYURUQ </a> <a id="getSyuruq"  class="fontJadwal">5 : 41</a>
            <hr style=" width: 100%;">
            <a class="_fontJadwal">DHUHA  </a> <a id="getDhuha"   class="fontJadwal">6 : 10</a>
            <hr style=" width: 100%;">
            <a class="_fontJadwal">DZUHUR </a> <a id="getDzuhur"  class="fontJadwal">11 : 38</a>
            <hr style=" width:100% ;margin-top: 10%;">
            <a class="_fontJadwal">ASHAR  </a> <a id="getAshar"   class="fontJadwal">14 : 58</a>
            <hr style=" width:100% ;margin-top: 10%;">
            <a class="_fontJadwal">MAGHRIB</a> <a id="getMaghrib" class="fontJadwal">17 : 28</a>
            <hr style=" width:100% ;margin-top: 10%;">
            <a class="_fontJadwal">ISYA   </a> <a id="getIsya"    class="fontJadwal">18 : 41</a>
        </div>

    </div>

<!--
    <iframe id="iqomah" src="/Tv/tv.html" style="height: 100%; width: 100%;"></iframe>
-->

    <script type="text/javascript">
        
        function beep() {
            const audioCtx = new (window.AudioContext || window.webkitAudioContext)()
            const oscillator = audioCtx.createOscillator()
            const gainNode = audioCtx.createGain()
            oscillator.connect(gainNode)
            gainNode.connect(audioCtx.destination)
            gainNode.gain.value = 5 // volume;
            oscillator.frequency.value = 3000 // frequency;
            oscillator.type = 'sine' // type;
            console.log('beep')
            oscillator.start()
            setTimeout(
                function () {
                    oscillator.stop()
                },
                1500 // duration
            )
        }


        setInterval(function () { getData()   }, 60000); //1 minute update rate
        setInterval(function () { getWaktu()  }, 1000); //1 Seconds update rate
        setInterval(function () { getJadwal() }, 30000); //1 minute update rate


        
        function getWaktu(){
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
        
        function getJadwal(){
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
                if (this.readyState == 4 && this.status == 200) { document.getElementById("_alamatMasjid").innerHTML = this.responseText }
            };
            xhttp.open("GET", "_getAlamat", true);
            xhttp.send();

            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) { document.getElementById("getKalender").innerHTML = this.responseText }
            };
            xhttp.open("GET", "tvKalender", true);
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