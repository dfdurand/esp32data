function btnOn() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "on", true);
    xhttp.send();
}

function btnOff() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "off", true);
    xhttp.send();
}

setInterval(function ()
{
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("temperature").innerHTML = this.responseText;
        }
    };

    xhttp.open("GET", "/lireTemperature", true);
    xhttp.send();
}, 2000);

setInterval(function ()
{
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("etat").innerHTML = this.responseText;
        }
    };

    xhttp.open("GET", "/lirEtat", true);
    xhttp.send();
}, 500);