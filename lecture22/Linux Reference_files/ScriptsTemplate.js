// JavaScript source code

function toggleVisibility(event) {

  var caller = event.currentTarget;
  var e = caller.nextElementSibling;

  var toggle = window.getComputedStyle(e, null).getPropertyValue("display");
  if (toggle === 'block') {
    e.style.display = 'none';
    caller.innerHTML = "More";
  }
  else {
    e.style.display = 'block';
    caller.innerHTML = "Less";
  }
}

function incrementSize(id) {
  var e = document.getElementById(id);
  var wdth = window.getComputedStyle(e, null).getPropertyValue("width");
  wdth = wdth.substr(0, wdth.length - 2);
  var size = Number(wdth) + 100;
  e.style.width = size.toString() + "px";
}

function decrementSize(id) {
  var e = document.getElementById(id);
  var wdth = window.getComputedStyle(e, null).getPropertyValue("width");
  wdth = wdth.substr(0, wdth.length - 2);
  var size = Number(wdth) - 100;
  e.style.width = size.toString() + "px";
}

