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
    ],
    seriesLabels: ["Standby aktiviert", "Standby deaktiviert"]
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
        $tooltip = $("#tooltip"),
        $tooltip_color = $("#tooltip span.color"),
        $tooltip_text = $("#tooltip span.text"),
        $wrapper = $('#chart_wrapper'),
        $chart = $(".chart");

    /*  $("#chart_wrapper").mousemove(function (e) {

          $tooltip.css({
              top: e.pageY + em(0.7),
              left: e.pageX + em(0.7)
          });

      });*/

    $wrapper.on("mouseenter", ".ct-bar", function () {

        if ($(this).parents(".ct-series-a").length === 0) {
            $tooltip_text.text(chartData.seriesLabels[0]);
        } else {
            $tooltip_text.text(chartData.seriesLabels[1]);
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

        $tooltip_text.append(": " + $(this).attr("ct:value"));
        $tooltip_color.css({
            background: $(this).css("stroke")
        });
        $tooltip.show(0);

    }).on("mouseleave", ".ct-bar", function () {
        $tooltip.hide(0);
    });


});