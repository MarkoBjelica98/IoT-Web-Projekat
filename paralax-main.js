const parallax = document.getElementById("parallax");
window.addEventListener("scroll", function(){
    let offset = window.pageYOffset;
   // console.log('Offset:' + offset);
   // console.log('offset * 0.7:' + offset * 0.7);
   parallax.style.backgroundPositionY = offset * 1.4 + "px";
});
