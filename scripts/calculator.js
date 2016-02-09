/*jslin browser: true*/
/*global $, jQuery, alert*/

var $power, $time, $price;

function validate(e) {

    "use strict";
    this.value = this.value.replace(/[^0-9\,]/g, '');

}

$(document).ready(function () {

    "use strict";

    $power = $("#power");
    $time = $("#time");
    $price = $("#price");


    $("#calculator").submit(function (e) {

        e.preventDefault();
        var power = parseFloat($power.val(), 0),
            time = parseFloat($time.val(), 0),
            price = parseFloat($price.val(), 0);

        if (power > 0 && time > 0 && price > 0 && time <= 24) {

            var day = power * time * price / 100000,
                year = day * 365;

            $("#error").hide(0);
            $("#result, #result + hr").show(0);
            $("#amount_year").text(year.toFixed(2) + "€");
            $("#amount_day").text(day.toFixed(3) + "€");
        } else {
            $("#result").hide(0);
            $('#error, #error + hr').show(0);
        }
    });

    $power.keyup(validate);
    $time.keyup(validate);
    $price.keyup(validate);

});