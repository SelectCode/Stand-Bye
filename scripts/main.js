var $active, $slider, $topics, $images, offsets;
var scrollTop, halfWindowHeight;




$(function () {

    offsets = [];

    $active = $("#menu .current_page_item");
    $slider = $("#menu .slider");
    $topics = $("#page div.topic");
    $images = $(".parallax div.background img");

    $slider.css("left", $active.position().left).width($active.outerWidth());

    getImageOffsets();

    $("#menu li.nav_item").click(function (e) {
        setActive($(this));

        var index = $(this).index() + 1;

        scrollToElement($(".topic:nth-of-type(" + index + ")"));
    });

    $("#menu li.nav_item").hover(function (e) {
        slideTo($(this));
    }, function (e) {
        slideTo($active);
    });

    $(window).resize(function (e) {

        $slider.css("left", $active.position().left).width($active.outerWidth());
        getImageOffsets();

        halfWindowHeight = $(window).height() / 2;

    }).scroll(function (e) {

        scrollTop = $(window).scrollTop();

        parallax();
        checkActive();

    });

    $("#icon_github").hover(function (e) {
        slideTo($(this));
    }, function (e) {
        slideTo($active);
    });


    halfWindowHeight = $(window).height() / 2;
});

function setActive($n) {
    if ($active == $n) {
        return;
    }

    $active.removeClass("current_page_item");
    $n.addClass("current_page_item");

    $active = $n;

    //setStart($active);
    slideTo($active);

};

function slideTo($el) {

    var leftPos = $el.position().left;
    var newWidth = $el.outerWidth();

    $slider.stop().animate({
        left: leftPos,
        width: newWidth
    }, 200, "swing");

};

function scrollToElement($el) {
    $('html, body').animate({
        scrollTop: $el.offset().top - $("#menu").outerHeight()
    }, 250);
};


function checkActive() {


    var middle = scrollTop + halfWindowHeight;

    for (var i = 0; i < $topics.length; i++) {
        $element = $topics.eq(i);

        var top = $element.offset().top;
        var bottom = $element.outerHeight() + top;

        if (middle > top && middle < bottom) {
            var $navElement = $("#menu li.nav_item").eq($element.index());
            setActive($navElement);
            return;
        }

    }

}

function parallax() {


    for (var i = 0; i < $images.length; i++) {
        $this = $images.eq(i);

        var delta = (scrollTop - offsets[i]) * 0.2;

        console.log("delta = " + delta);

        $this.css({
            top: $this.data("original_top") + delta
        });
    }

};

function getImageOffsets() {

    for (var i = 0; i < $(".parallax div.background").length; i++) {

        offsets[i] = $images.eq(i).offset().top;

    }

    $images.each(function () {

        $(this).data("original_top", $(this).position().top + $(this).outerHeight() / 2);
    });

};