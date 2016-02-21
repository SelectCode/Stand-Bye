/*jslint browser: true*/
/*global $, jQuery, Chartist, console*/

//vars for the slider menu
var $active, $slider, $topics, sliding = false;
//Vars for the parallax effect
var $images, offsets;
var scrollImg, scrollContainter;

var scrollTop, windowHeight, halfWindowHeight;


var disabled;

//Speed for scrolling the page, WindowHeight/s
var scrollSpeed = 2;

function setActive($n) {

    //console.log("set active: " + $n.index());

    "use strict";

    if ($active.is($n)) {
        return;
    }

    $active.removeClass("current_page_item");
    $n.addClass("current_page_item");

    $active = $n;

    //setStart($active);
    slideTo($active);

};

function slideTo($el) {

    "use strict";
    var leftPos = $el.position().left,
        newWidth = $el.outerWidth();

    sliding = true;
    //console.log("started sliding");

    $slider.stop().animate({
        left: leftPos,
        width: newWidth
    }, {
        duration: 200,
        easing: "swing",
        complete: function () {
            sliding = false;
            //console.log("stopped sliding");
        }
    });

};

function scrollToElement($el) {
    disabled = true;

    var elOffset = $el.offset().top;

    // console.log("scroll: " + scrollTop + " offset: " + elOffset + " scrollspeed: " + scrollSpeed);

    var time = Math.abs(scrollTop - elOffset) / (scrollSpeed * windowHeight) * 1000;

    //console.log(time);

    $('html, body').stop().animate({
        scrollTop: elOffset - $("#menu").outerHeight()
    }, {
        duration: time,
        start: function () {
            disabled = true;
        },
        complete: function () {
            disabled = false;
        }
    });
};

function checkActive() {

    if (disabled || sliding) {
        return;
    }

    var middle = scrollTop + halfWindowHeight;

    for (var i = 0; i < $topics.length; i++) {
        $element = $topics.eq(i);

        var top = $element.offset().top;
        var bottom = $element.outerHeight() + top;


        //console.log("middle = " + middle + "| top = " + top + "| bottom = " + bottom);

        if (middle > top && middle < bottom) {
            var $navElement = $("#menu li.nav_item").eq(i);
            setActive($navElement);
            return;
        }

    }

}

function parallax() {

    for (var i = 0; i < $images.length; i++) {
        $this = $images.eq(i);
        var delta = ((scrollTop - offsets[i]) / scrollContainter[i]) * scrollImg[i];
        $this.css({
            top: delta
        });
        if (delta > 0 || delta < $this.parent().outerHeight() - $this.height) {
            getImageOffsets();
            //console.log("recalc offsets");
        }
    }

};

function getImageOffsets() {

    var $cont = $(".parallax .background");

    for (var i = 0; i < $cont.length; i++) {

        var $this = $cont.eq(i);

        var height = $this.outerHeight();
        offsets[i] = $this.offset().top + $this.outerHeight();
        scrollImg[i] = $images.eq(i).outerHeight() - height;
        scrollContainter[i] = windowHeight + height;
    }

};

$(function () {

    "use strict";

    //initialize stuff
    offsets = [];
    scrollContainter = [];
    scrollImg = [];

    $active = $("#menu .current_page_item");
    $slider = $("#menu .slider");
    $topics = $("div.topic");
    $images = $(".parallax div.background img");

    $slider.css("left", $active.position().left).width($active.outerWidth());

    windowHeight = $(window).innerHeight();
    halfWindowHeight = windowHeight / 2;

    scrollTop = $(window).scrollTop();

    getImageOffsets();

    parallax();

    //Menu click listener
    $("#menu li.nav_item").click(function (e) {
        setActive($(this));

        var index = $(this).index();

        //console.log("click: " + index);
        scrollToElement($topics.eq(index));
    });

    //Menu hover listener
    $("#menu li.nav_item, #icon_github").hover(function (e) {
        slideTo($(this));
    }, function (e) {
        slideTo($active);
    });

    //link click listener
    $("a.in_page").click(function (e) {

        var data = $(this).data("goto");

        //console.log("data: " + data);

        if (data != null && data != "") {
            e.preventDefault();
            $("a").each(function () {

                //console.log("name: " + $(this).attr("name"));

                if (data === $(this).attr("name")) {
                    scrollToElement($(this));
                }
            });
        }

    });

    //Resize listener
    $(window).resize(function (e) {

        $slider.css("left", $active.position().left).width($active.outerWidth());

        windowHeight = $(window).innerHeight();
        halfWindowHeight = windowHeight / 2;

        getImageOffsets();

        scrollTop = $(window).scrollTop();
        parallax();
        checkActive();

    }).scroll(function (e) {

        scrollTop = $(window).scrollTop();

        parallax();
        checkActive();

    });


});