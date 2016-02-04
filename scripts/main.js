//vars for the slider menu
var $active, $slider, $topics;
//Vars for the parallax effect
var $images, offsets;
var scrollImg, scrollContainter;

var scrollTop, windowHeight, halfWindowHeight;


var disabled;

$(function () {

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

    getImageOffsets();


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

    $("a").click(function (e) {

        var data = $(this).data("goto");

        if (data != null) {
            e.preventDefault();
            scrollToElement($topics.eq(parseInt(data)));
        }

    });

    //Resize listener
    $(window).resize(function (e) {

        $slider.css("left", $active.position().left).width($active.outerWidth());

        windowHeight = $(window).innerHeight();
        halfWindowHeight = windowHeight / 2;

        getImageOffsets();

    }).scroll(function (e) {

        scrollTop = $(window).scrollTop();

        parallax();
        checkActive();

    });


});

function setActive($n) {

    //console.log("set active: " + $n.index());

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
    }, {
        duration: 200,
        easing: "swing"
    });

};

function scrollToElement($el) {
    disabled = true;


    $('html, body').animate({
        scrollTop: $el.offset().top - $("#menu").outerHeight()
    }, {
        duration: 250,
        start: function () {
            disabled = true;
        },
        complete: function () {
            disabled = false;
        }
    });
};

function checkActive() {

    if (disabled) {
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

        var delta = -1 * ((scrollTop - offsets[i]) / scrollContainter[i]) - scrollImg[i];

        //var offsetContainer = (scrollTop - offsets[i]) * -1;
        //var delta = (offsetContainer * scrollImg) / scrollContainter;

        console.log(delta);

        $this.css({
            top: delta
        });
    }

};

function getImageOffsets() {

    var $cont = $(".parallax .background");

    for (var i = 0; i < $cont.length; i++) {

        var $this = $cont.eq(i);
        var height = $this.outerHeight();

        offsets[i] = $this.offset().top - $this.outerHeight();

        scrollImg[i] = $images.eq(i).outerHeight() - height;
        do
            scrollContainter[i] = windowHeight + height;

    }

    console.log("offsets: " + offsets);
    console.log("scroll container: " + scrollContainter);
    console.log("scroll Images:" + scrollImg);

    //  $images.each(function () {
    //
    //      $(this).data("original_top", $(this).position().top + $(this).outerHeight() / 2);
    //  });

};