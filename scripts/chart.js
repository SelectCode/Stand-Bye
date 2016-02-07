var data = [
    {
        value: 300,
        color: "#F7464A",
        highlight: "#FF5A5E",
        label: "Nicht Genervt"
    },
    {
        value: 50,
        color: "#46BFBD",
        highlight: "#5AD3D1",
        label: "Genervt von Windows-Standby"
    }
]

var ctx = document.getElementById("chart_request").getContext("2d");
var chart = new Chart(ctx).Pie(data);