/*jslint browser: true*/
/*global $, jQuery, Chartist*/

function em(input) {
    "use strict";
    var emSize = parseFloat($("body").css("font-size"));
    return (emSize * input);
}

var chartData = {
    labels: ["Von Windows-Standby genervt", "Nicht genervt", "Deine Mudda"],
    series: [
        [1, 2, 3],
        [4, 5, 6]
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
    var chart = new Chartist.Bar('.chart', chartData, options);

    chart.on('draw', function (data) {
        if (data.type === 'bar') {
            data.element.attr({
                style: 'stroke-width: 4em'
            });
        }
    });

});