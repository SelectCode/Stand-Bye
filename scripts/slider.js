var $active, $slider;


$(function () {

    $active = $("#menu .current_page_item");
    $slider = $("#menu .slider");

    $slider.css("left", $active.position().left).width($active.outerWidth());

    $slider.width()

    $("#menu li.nav_item").click(function (e) {
        setActive($(this));
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

    setStart($active);
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

function parallax() {

};