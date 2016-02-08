/*jslint browser: true*/
/*global $, jQuery, Chart, console*/

function em(input) {
    "use strict";
    var emSize = parseFloat($("body").css("font-size"));
    return (emSize * input);
}

var chartData = {
    labels: ["Von Windows-Standby genervt", "Nicht genervt"],
    datasets: [
        {
            fillColor: "rgba(29, 104, 134, 0.75)",
            strokeColor: "rgba(29, 104, 134, 1)",
            highlightFill: "rgba(29, 104, 134, 0.9)",
            highlightStroke: "rgba(29, 104, 134, 1)",
            label: "Standby aktiviert",
            data: [12, 10]
        }, {
            fillColor: "rgba(255, 152, 0, 0.75)",
            strokeColor: "rgba(255, 152, 0, 1)",
            highlightFill: "rgba(255, 152, 0, 0.9)",
            highlightStroke: "rgba(255, 152, 0, 1)",
            label: "Standby deaktiviert",
            data: [22, 10]
        }
    ]
};

var options = {

    responsive: true,
    barValueSpacing: 0,
    barWidth: em(2.5),
    scaleBeginAtZero: true,
    scaleGridLineColor: "#B6B6B6",
    scaleGridLineWidth: 1,
    barShowStroke: true,
    barStrokeWidth: 1,
    relativeBars: false,
    legendTemplate: "<ul class=\"<%=name.toLowerCase()%>-legend\"><% for (var i=0; i<datasets.length; i++){ console.log(datasets[i]);%><li><span style=\"background-color:<%=datasets[i].strokeColor%>\"></span><%if(datasets[i].label){%><%=datasets[i].label%><%}%></li><%}%></ul>"
};

$(function () {

    "use strict";
    var canvas = document.getElementById("chart"),
        $canvas = $("#chart"),
        ctx = canvas.getContext("2d"),
        myBar = new Chart(ctx).StackedBar(chartData, options);

    $("#legend").html(myBar.generateLegend());


    $(window).resize(function (e) {

        $canvas.attr("width", $("#chart_wrapper").width());
        $canvas.attr("height", $("#chart_wrapper").height());
        myBar.draw();

    });
});