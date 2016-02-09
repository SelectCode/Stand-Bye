/*jslint browser: true*/
/*global $, jQuery, Chartist, console*/

function em(input) {
    "use strict";
    var emSize = parseFloat($("body").css("font-size"));
    return (emSize * input);
}

var chartData = {
    labels: ["Von Windows-Standby genervt", "Nicht genervt"],
    series: [
        [1, 2],
        [4, 5]
    ]
};

var options = {
    stackBars: true,
    axisX: {
        showGrid: false
    },
    axisY: {
        label: "Benutzer"
    }
};

$(function () {

    "use strict";
    var chart = new Chartist.Bar('.chart', chartData, options),
        $tooltip = $("#tooltip");

    /*$(".ct-bar").hover(function () {

        console.log("hover");
        $tooltip.show(0);

    }, function () {

        $tooltip.hide(0);

    }).mousemove(function (e) {

        console.log("mousemove");

        $tooltip.css({
            top: e.pageY + em(0.7),
            left: e.pageX + em(0.7)
        });

    });*/

    $("#chart_wrapper").mousemove(function (e) {

        $tooltip.css({
            top: e.pageY + em(0.7),
            left: e.pageX + em(0.7)
        });

    });

    $("#chart_wrapper").on("mouseenter", ".ct-bar", function () {
        $tooltip.text($(this).attr("ct:value"));
        $tooltip.show(0);
    }).on("mouseleave", ".ct-bar", function () {
        $tooltip.hide(0);
    });

});