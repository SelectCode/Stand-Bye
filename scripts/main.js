var $active, $slider, $topics;




$(function () {

    $active = $("#menu .current_page_item");
    $slider = $("#menu .slider");
    $topics = $("#page div.topic");

    $slider.css("left", $active.position().left).width($active.outerWidth());

    $slider.width()

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
    }).scroll(function (e) {

        parallax();
        checkActive();

    });


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


    var scrollTop = $(window).scrollTop() + $(window).height() / 2;

    console.log("scroll top = " + scrollTop + " +++++++++++++ ");

    for (var i = 0; i < $topics.length; i++) {
        $element = $topics.eq(i);

        var top = $element.offset().top;
        var bottom = $element.outerHeight() + top;

        console.log("top = " + top + " bottom = " + bottom);

        if (scrollTop > top && scrollTop < bottom) {
            var $navElement = $("#menu li.nav_item").eq($element.index());
            console.log($navElement.text() + " -------------- ");
            setActive($navElement);
            return;
        }

    }

}

function parallax() {

};