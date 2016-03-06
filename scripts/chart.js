/*jslint browser: true*/
/*global $, jQuery, Chartist, console*/

function em(input) {
    "use strict";
    var emSize = parseFloat($("body").css("font-size"));
    return (emSize * input);
}

var surveyChartData = {
        labels: ["Von Windows-Standby genervt", "Nicht genervt"],
        series: [
        //nervt, !nervt
            [5, 8], // !aktiviert
            [15, 16] //aktiviert
    ],
        seriesLabels: ["Standby aktiviert", "Standby deaktiviert"],
        unit: ""
    },
    example2Data = {
        labels: ["Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag"],
        series: [
            [15, 17, 18, 13, 17],
            [8, 11, 9, 4, 7]
        ],
        seriesLabels: ["Mit Stand-Bye ", "Ohne Stand-Bye "],
        unit: "kWh"
    },
    example1Data = {
        labels: ["Ohne Stand-Bye!", "Mit Stand-Bye!"],
        series: [
            [100, 0],
            [0, 75]
        ],
        seriesLabels: ["Mit Stand-Bye", "Ohne Stand-Bye"],
        unit: "kWh"
    },
    surveyChartOptions = {
        stackBars: true,
        axisX: {
            showGrid: false
        },
        axisY: {
            label: "Benutzer"
        }
    },
    exampleOptions = {
        stackBars: false,
        axisX: {
            showGrid: false
        },
        axisY: {
            label: "kWh"
        }
    };

function tooltip(chart, $wrapper) {

    "use strict";

    var $tooltip = $wrapper.find('#tooltip'),
        $tooltip_color = $tooltip.find("span.color"),
        $tooltip_text = $tooltip.find("span.text"),
        $chart = $wrapper.find('.chart');

    $wrapper.on("mouseenter", ".ct-bar", function () {

        if ($(this).parents(".ct-series-a").length === 0) {
            $tooltip_text.text(chart.data.seriesLabels[0]);
        } else {
            $tooltip_text.text(chart.data.seriesLabels[1]);
        }

        var x1 = parseFloat($(this).attr("x1")),
            y1 = parseFloat($(this).attr("y1")),
            y2 = parseFloat($(this).attr("y2")),
            stroke = parseFloat($(this).css("stroke-width")),
            top = $chart.position().top + parseFloat($chart.css("margin-top")) + parseFloat($chart.css("padding-top")),
            left = $chart.position().left + parseFloat($chart.css("margin-left")) + parseFloat($chart.css("padding-left"));

        $tooltip.css({
            top: (top + y2 + ((y1 - y2) / 2) - ($tooltip.outerHeight() / 2)),
            left: left + (x1 + (stroke / 2))
        });

        $tooltip_text.append(": " + $(this).attr("ct:value") + " " + chart.data.unit);
        $tooltip_color.css({
            background: $(this).css("stroke")
        });
        $tooltip.show(0);

    }).on("mouseleave", ".ct-bar", function () {
        $tooltip.hide(0);
    });


}

$(function () {

    "use strict";

    $(".chart").html("");

    var surveyChart = new Chartist.Bar('.chart#survey', surveyChartData, surveyChartOptions),
        example1Chart = new Chartist.Bar('.chart#example1', example1Data, exampleOptions),
        example2Chart = new Chartist.Bar('.chart#example2', example2Data, exampleOptions);

    tooltip(surveyChart, $('.chart#survey').parent());
    tooltip(example1Chart, $('.chart#example1').parent());
    tooltip(example2Chart, $('.chart#example2').parent());

});