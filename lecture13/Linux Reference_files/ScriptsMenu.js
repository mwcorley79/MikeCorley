/////////////////////////////////////////////////////////////////////
// ScriptsMenu.js - Constructs dropdown menu for top-level pages   //
//                                                                 //
// Jim Fawcett, 25 June 2018                                       //
/////////////////////////////////////////////////////////////////////

//----< called in body.onload to initial menus and footer >----------
/*
 *  This function is specific for the menu on top-level pages 
 */
function initializeMenu() {

  // create top menu

  var topMenu = document.getElementsByTagName("nav");
  topMenu[0].innerHTML = "<div class='navbar'>\
    <div class='dropdown menuItem'>\
      <button class='dropbutton'>Courses &#9662;</button>\
      <div class='dropdown-content'>\
        <a href='../../webpages/CSE775.htm#syllabus'>CSE775&nbsp;Syllabus</a>\
        <a href='../../webpages/CSE681.htm'>CSE681-SMA</a>\
        <a href='../../webpages/CSE686.htm'>CSE686-IP</a>\
        <a href='../../webpages/CSE687.htm'>CSE687-OOD</a>\
        <a href='../../webpages/CSE775.htm'>CSE775-DO</a>\
        <a href='../../webpages/CSE776.htm'>CSE776-DP</a>\
        <a href='../../webpages/Code.htm'>Code</a>\
        <a href='../../webpages/Presentations.htm'>Presentations</a>\
        <a href='../../webpages/OfficeHours.htm'>Office Hours</a>\
        <a href='../../webpages/FawcettHome.htm'>Site Home</a>\
        <a href='../../Webpages/SiteMap.htm'>Site Map</a>\
      </div>\
    </div>\
    <div class='dropdown menuItem'>\
      <button class='dropbutton'>Lectures &#9662;</button>\
      <div class='dropdown-content'>\
        <a class='lectItem' href='CSE775Lect1.htm'>L01&nbsp;-&nbsp;Introduction</a>\
        <a class='lectItem' href='CSE775Lect2.htm'>L02&nbsp;-&nbsp;Windows&nbsp;&amp;&nbsp;Linux&nbsp;Platforms</a>\
        <a class='lectItem' href='CSE775Lect3.htm'>L03&nbsp;-&nbsp;Native&nbsp;code</a>\
        <a class='lectItem' href='CSE775Lect4.htm'>L04&nbsp;-&nbsp;Systems&nbsp;Programming</a>\
        <a class='lectItem' href='CSE775Lect5.htm'>L05&nbsp;-&nbsp;Components</a>\
        <a class='lectItem' href='CSE775Lect6.htm'>L06&nbsp;-&nbsp;Intro&nbsp;to&nbsp;COM</a>\
        <a class='lectItem' href='CSE775Lect7.htm'>L07&nbsp;-&nbsp;Interfaces</a>\
        <a class='lectItem' href='CSE775Lect8.htm'>L08&nbsp;-&nbsp;IDL</a>\
        <a class='lectItem' href='CSE775Lect9.htm'>L09&nbsp;-&nbsp;ATL</a>\
        <a class='lectItem' href='CSE775Lect10.htm'>L10&nbsp;-&nbsp;OutProc&nbsp;Components</a>\
        <a class='lectItem' href='CSE775Lect11.htm'>L11&nbsp;-&nbsp;Apartments</a>\
        <a class='lectItem' href='CSE775JavaScriptAndGo.htm'>L11&nbsp;-&nbsp;JavaScript&nbsp;&amp;&nbsp;Go</a>\
        <a class='lectItem' href='CSE775Projects-TechPres.htm'>L12&nbsp;-&nbsp;Technology&nbsp;Presentations</a>\
        <a class='lectItem' href='CSE775Projects-TechPres.htm'>L13&nbsp;-&nbsp;Technology&nbsp;Presentations</a>\
        <a class='lectItem' href='CSE775Projects-TechPres.htm'>L14&nbsp;-&nbsp;Technology&nbsp;Presentations</a>\
        <a class='lectItem' href='CSE775Projects-TechPres.htm'>L15&nbsp;-&nbsp;Technology&nbsp;Presentations</a>\
        <a class='lectItem' href='CSE775Projects-TechPres.htm'>L16&nbsp;-&nbsp;Technology&nbsp;Presentations</a>\
        <a class='lectItem' href='CSE775Lect17.htm'>L17&nbsp;-&nbsp;Automation</a>\
        <a class='lectItem' href='CSE775Lect18.htm'>L18&nbsp;-&nbsp;COM&nbsp;Technologies</a>\
        <a class='lectItem' href='CSE775Lect19.htm'>L19&nbsp;-&nbsp;Managed&nbsp;Code</a>\
        <a class='lectItem' href='CSE775Lect20.htm'>L20&nbsp;-&nbsp;Interop</a>\
        <a class='lectItem' href='CSE775JavaScriptAndGo.htm'>L21&nbsp;-&nbsp;JavaScript&nbsp;&amp;&nbsp;Go</a>\
        <a class='lectItem' href='CSE775Projects-Probes.htm'>L22&nbsp;-&nbsp;Probes&nbsp;presentations</a>\
        <a class='lectItem' href='CSE775Projects-Probes.htm'>L23&nbsp;-&nbsp;Probes&nbsp;presentations</a>\
        <a class='lectItem' href='CSE775Projects-Probes.htm'>L24&nbsp;-&nbsp;Probes&nbsp;presentations</a>\
        <a class='lectItem' href='CSE775Projects-Probes.htm'>L25&nbsp;-&nbsp;Probes&nbsp;presentations</a>\
        <a class='lectItem' href='CSE775Projects-Probes.htm'>L26&nbsp;-&nbsp;Probes&nbsp;presentations</a>\
        <a class='lectItem' href='CSE775Projects-Probes.htm'>L27&nbsp;-&nbsp;Probes&nbsp;presentations</a>\
        <a class='lectItem' href='CSE775Projects-Final.htm'>Exams</a>\
        <a class='lectItem' href='CSE775Projects-Final.htm'>Exams</a>\
        <div style='padding:0px 10px; margin:0px; font-size:small;'>&nbsp;</div>\
      </div>\
    </div>\
    <div class='dropdown menuItem'>\
      <button class='dropbutton'>Projects &#9662;</button>\
      <div class='dropdown-content'>\
        <a class='projItem' href='Project1-S2019.htm'>Project&nbsp;#1</a>\
        <a class='projItem' href='ProjectFinal-S2019.htm'>Final&nbsp;Projects</a>\
        <a href='../Projects/prgs775.pdf'>Code&nbsp;Grade&nbsp;Sheet</a>\
        <a href='../Projects/Technology Presentation Grade sheet.pdf'>Tech&nbsp;Pres&nbsp;GradeSheet</a>\
        <a href='../Projects/Probes Presentation Grade sheet.pdf'>Probes&nbsp;Pres&nbsp;GradeSheet</a>\
        <a href='../Projects/FinalPresentationGradesheet-S2019.pdf'>Final&nbsp;Pres&nbsp;GradeSheet</a>\
        <a href='../../Repository/Tools/CodeAnalyzerExesAndCleanBat'>CodeAnalExes&nbsp;+&nbsp;Clean.bat</a>\
        <a href='../../webpages/Code.htm'>Code</a>\
        <a href='../../webpages/Presentations.htm'>Presentations</a>\
        <a href='../../webpages/videos.htm'>Lecture&nbsp;Videos</a>\
        <a href='../../webpages/SubmittingProjects.htm'>Submitting&nbsp;Projects</a>\
        <a href='../../webpages/Upload.htm'>Uploading&nbsp;Projects</a>\
        <a href='../../webpages/GradingPolicy.htm'>Grading&nbsp;Policy</a>\
        <a href='https://docs.microsoft.com/en-us/visualstudio/ide/visual-studio-ide'>Visual Studio</a>\
        <a href='https://docs.microsoft.com/en-us/visualstudio/'>Visual&nbsp;Studio&nbsp;Documentation&nbsp;&nbsp;&nbsp;</a>\
        <a href='https://docs.microsoft.com/en-us/visualstudio/#pivot=languages'>Visual&nbsp;Studio&nbsp;Languages</a>\
        <a href='https://en.cppreference.com/w/'>cppreference.com</a>\
        <a href='https://docs.microsoft.com/en-us/dotnet/csharp/'>C#&nbsp;Guide</a>\
        <a href='https://docs.microsoft.com/en-us/dotnet/framework/'>.Net&nbsp;Framework</a>\
        <a href='https://sourcemaking.com/refactoring/smells'>Code&nbsp;Smells</a>\
        <a href='../../webpages/SummerProjects.htm'>Summer&nbsp;Projects</a>\
        <a href='../../webpages/SummerReading.htm'>Summer&nbsp;Reading</a>\
        <div style='padding:0px 10px; margin:0px; font-size:small;'>&nbsp;</div>\
      </div>\
    </div>\
    <div class='dropdown menuItem'>\
      <button class='dropbutton'>CodeSnaps &#9662;</button>\
      <div class='dropdown-content'>\
        <a href='CodeSnap-PointersAndReferences.cpp.htm'>Pointers &amp; References</a>\
        <a href='CodeSnap-ClassAnatomy.h.htm'>Class Anatomy</a>\
        <a href='CodeSnap-Strings.h.htm'>Strings</a>\
        <a href='CodeSnap-Inheritance.h.htm'>Inheritance</a>\
        <a href='CodeSnap-CompoundObjects.cpp.htm'>Compound Objects</a>\
        <a href='CodeSnap-Templates.h.htm'>Templates</a>\
        <a href='CodeSnap-Converter.h.htm'>Converter</a>\
        <a href='CodeSnap-FunctionObjects.cpp.htm'>Function Objects</a>\
        <a href='CodeSnap-LambdaCapture.cpp.htm'>Lambda Capture</a>\
        <a href='CodeSnap-BlockingQueue.h.htm'>Blocking Queue</a>\
        <a href='CodeSnap-TestUtilities.h.htm'>Test Utilities</a>\
      </div>\
    </div>\
    <div class='dropdown menuItem'>\
      <button class='dropbutton'>Notes &#9662;</button>\
      <div class='dropdown-content'>\
        <a href='WebResources.htm'>Web&nbsp;resources</a>\
        <a href='LinuxShellCommands.htm#comms'>Linux&nbsp;Shell&nbsp;commands&nbsp;&nbsp;&nbsp;</a>\
        <a href='LinuxShellCommands.htm#ops'>Linux&nbsp;Shell&nbsp;operations&nbsp;&nbsp;&nbsp;</a>\
        <a href='ProgEnviron.htm'>Programming&nbsp;Environments</a>\
        <a href='COMResources.htm'>COM&nbsp;resources</a>\
        <div style='padding:0px 10px; margin:0px; font-size:small;'>&nbsp;</div>\
      </div>\
    </div>\
    <div class='dropdown menuItem'>\
      <button class='dropbutton'>Resources &#9662;</button>\
      <div class='dropdown-content'>\
        <a href='WebResources.htm'>Web&nbsp;resources</a>\
        <a href='https://chrome.google.com/webstore/detail/gliffy-diagrams/bhmicilclplefnflapjmnngmkkkkpfad?hl=en'>Gliffy&nbsp;Diagramming&nbsp;Chrome&nbsp;Extension</a>\
        <div style='padding:0px 10px; margin:0px; font-size:small;'>-- <strong>Linux Setup</strong> -----------</div>\
        <a href='../presentations/LinuxSetup.pdf'>Help&nbsp;Setting&nbsp;Up&nbsp;Ubuntu&nbsp;Environment</a>\
        <a href='https://www.ubuntu.com/download/desktop'>Installing&nbsp;Ubuntu</a>\
        <a href='https://code.visualstudio.com/docs/?dv=linux64_deb'>Installing&nbsp;Visual&nbsp;Studio&nbsp;Code</a>\
        <a href='https://code.visualstudio.com/docs/languages/cpp'>Configure&nbsp;Visual&nbsp;Studio&nbsp;Code</a>\
        <a href='https://dotnet.microsoft.com/download/linux-package-manager/ubuntu18-04/sdk-2.2.102'>Install&nbsp;.Net&nbsp;Core&nbsp;(optional)</a>\
        <div style='padding:0px 10px; margin:0px; font-size:small;'>-- <strong>Using Linux</strong> -----------</div>\
        <a href='LinuxShellCommands.htm#comms'>Linux&nbsp;Shell&nbsp;commands&nbsp;&nbsp;&nbsp;</a>\
        <a href='LinuxShellCommands.htm#ops'>Linux&nbsp;Shell&nbsp;operations&nbsp;&nbsp;&nbsp;</a>\
        <a href='https://www.tutorialspoint.com/unix/index.htm'>Unix/Linux Tutorial - tutorialspoint.com</a>\
        <a href='https://www.cs.mcgill.ca/~guide/help/man.html'>Using Man Pages</a>\
        <a href='https://www.computerhope.com/unix/uman.htm'>Summary of Man Page Commands</a>\
        <div style='padding:0px 10px; margin:0px; font-size:small;'>-- <strong>Bash Scripts</strong> ----------</div>\
        <a href='https://www.tldp.org/LDP/Bash-Beginners-Guide/html/index.html'>Bash Guide for beginners</a>\
        <a href='https://www.taniarascia.com/how-to-create-and-use-bash-scripts/'>Create and use Bash scripts</a>\
        <div style='padding:0px 10px; margin:0px; font-size:small;'>-- <strong>Linux Tools</strong> -----------</div>\
        <a href='http://man7.org/linux/man-pages/man1/grep.1.html'>Grep</a>\
        <a href='https://www.tldp.org/LDP/Bash-Beginners-Guide/html/sect_04_02.html'>Grep Examples</a>\
        <div style='padding:0px 10px; margin:0px; font-size:small;'>-- <strong>C++</strong> -------------------</div>\
        <a href='https://www.thegeekstuff.com/2012/10/gcc-compiler-options/'>15&nbsp;frequently&nbsp;used&nbsp;gcc&nbsp;options</a>\
        <a href='http://mrbook.org/blog/tutorials/make/'>Makefiles</a>\
        <a href='http://cpprocks.com/files/c++11-regex-cheatsheet.pdf'>C++11 Regex</a>\
        <a href='http://cs.lmu.edu/~ray/notes/regex/'>Regex Examples - lmu.edu</a>\
        <a style='white-space:nowrap;' href='https://www.regular-expressions.info/examples.html'>Regex Examples - regular-expressions.info&nbsp;&nbsp;</a>\
        <div style='padding:0px 10px; margin:0px; font-size:small;'>-- <strong>Miscellaneous</strong> ---------</div>\
        <a href='https://piazza.com'>piazza.com</a>\
        <a href='../../Webpages/SummerReading.htm'>Summer&nbsp;Reading</a>\
        <a href='../../Webpages/SummerProjects.htm'>Summer&nbsp;Projects</a>\
        <div style='padding:0px 10px; margin:0px; font-size:small;'>&nbsp;</div >\
      </div>\
    </div>\
    <div class='dropdown menuItem'>\
      <button class='dropbutton'>Directories &#9662;</button>\
      <div class='dropdown-content'>\
         <a href='../../'>Handouts</a>\
         <a href='../../Coretechnologies/'>CoreTech</a>\
         <a href='../../CSE681/'>CSE681-SMA</a>\
         <a href='../../CSE686/'>CSE686-IP</a>\
         <a href='../../CSE687/'>CSE687-OOD</a>\
         <a href='../../CSE775/'>CSE775-DO</a>\
         <a href='../../CSE776/'>CSE776-DP</a>\
         <a href='../../CSE784/'>CSE784-SS</a>\
         <a href='../../CSE681-OnLine/'>CSE681-SMA-OnLine</a>\
         <a href='../../CSE687-OnLine/'>CSE687-OOD-OnLine</a>\
         <a href='../../SummerProjects/'>Summer Prj</a>\
         <a href='../../ShortCourse/'>Short Course</a>\
      </div>\
    </div>\
    <div class='dropdown menuItem'>\
      <button class='dropbutton'>Blog &#9662;</button>\
      <div class='dropdown-content'>\
        <a href='../../webpages/Blog.htm'>First Things</a>\
        <div style='padding:0px 10px; margin:0px; font-size:small;'>-- Design -----------</div>\
        <a href='../../webpages/BlogDesign.htm'>SW Design</a>\
        <a href='../../webpages/BlogOOD.htm'>OO Design</a>\
        <a href='../../webpages/BlogObjectModels.htm'>Object Models</a>\
        <a href='../../webpages/BlogGlobals.htm'>Scopes and Global Data</a>\
        <div style='padding:0px 10px; margin:0px; font-size:small;'>-- Engineering SW ---</div>\
        <a href='../../webpages/BlogOCD.htm'>Concept Document</a>\
        <a href='../../webpages/BlogTesting.htm'>SW Testing</a>\
        <a href='../../webpages/SummerReading.htm'>Summer Reading</a>\
        <div style='padding:0px 10px; margin:0px; font-size:small;'>-- Software Sys -----</div>\
        <a href='../../webpages/BlogStructure.htm'>SW Structure</a>\
        <a href='../../webpages/BlogMessagePassingComm.htm'>Msg-Passing Comm</a>\
        <a href='../../webpages/BlogActiveObjects.htm'>Active Objects</a>\
        <div style='padding:0px 10px; margin:0px; font-size:small;'>-- Reusable Pkgs ----</div>\
        <a href='../../webpages/BlogNoSql.htm'>noSQL Database</a>\
        <a href='../../webpages/BlogParser.htm'>Parsing</a>\
        <a href='../../webpages/BlogCodeAnalyzer.htm'>Code Analyzer</a>\
        <a href='../../webpages/BlogMTree.htm'>M-ary Trees</a>\
        <a href='../../webpages/BlogGraph.htm'>Directed Graphs</a>\
        <a href='../../webpages/BlogFileSystem.htm'>C++ FileSystem</a>\
      </div>\
    </div>\
    <div class='dropdown menuItem'>\
      <button class='dropbutton'>About &#9662;</button>\
      <div class='dropdown-content'>\
        <a href='../../webpages/FawcettAbout.htm'>Jim Fawcett</a>\
        <a href='../../webpages/Research.htm'>Research</a>\
        <a href='../../webpages/Help.html'>Help</a>\
        <a href='#' onclick='toggleNavKeys()'>Nav Keys</a>\
        <a href='../../webpages/SiteDesign.htm'>Site Design</a>\
        <a href='../../webpages/FawcettHome.htm'>Site Home</a>\
        <a href='../../Webpages/SiteMap.htm' class='menuItem'>Site Map</a>\
      </div>\
    </div>\
    <button class='pageScroll' onclick='scrollPageTop()'>Top</button>\
    <button class='pageScroll' onclick='scrollPageBottom()'>Bottom</button>\
    <a id='prevLink' class='nextprev' href='#'>Prev</a>\
    <a id='nextLink' class='nextprev' href='#'>Next</a>\
    <button class='menuScroll' onclick='scrollMenuLeft()'>&lt;</button>\
    <button class='menuUnscroll' onclick='scrollMenuRight()'>&gt;</button>\
  </div >\
  <div style='clear:all;'></div>"

  // hide Next and Prev links if page has no next or previous pages
  // otherwise load href from page link

  var nxt = document.getElementById("Next");
  if (nxt === null) {
    document.getElementById("nextLink").style.display = "none";
  }
  else {
    document.getElementById("nextLink").href = nxt.href;
  }

  var prv = document.getElementById("Prev");
  if (prv === null) {
    document.getElementById("prevLink").style.display = "none";
  }
  else {
    document.getElementById("prevLink").href = prv.href;
  }
  // show footer with copyright notice and revision date

  var rvsd = document.getElementsByTagName("info-bar");
  var date = document.lastModified;
  rvsd[0].innerHTML = "copyright &copy; Jim Fawcett, 2018&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Page Revised: " + date;

  setNavKeys();

  // listen for keyboard events:
  // - key actions are defined in ScriptsKeyboard.js

  document.addEventListener('keydown', (event) => { keyAction(event); }, false);
  document.addEventListener('mousedown', (event) => { mouseAction(event); }, false);
  //document.oncontextmenu='return false;'
  // bind more-less click event

  var elems = document.getElementsByTagName("more-less");
  for (var i = 0; i < elems.length; ++i) {
    elems[i].addEventListener("click", (event) => { toggleVisibility(event); }, false);
  }
}

//----< load page defined in current page's Prev link >--------------

function loadCour() {
  document.getElementById("Cour").click();
}
//----< load page defined in current page's Prev link >--------------

function loadPrev() {
  document.getElementById("Prev").click();
}
//----< load page defined in current page's Next link >--------------

function loadNext() {
  document.getElementById("Next").click();
}
//----< hide, progressively, menu items on the left >----------------
/*
*  This let's user see menu items that overflow on the right
*  due to page size.
*/
function scrollMenuLeft() {
  var items = document.getElementsByClassName("menuItem");
  var i;
  for (i = 0; i < items.length; ++i) {
    var cpprp = window.getComputedStyle(items[i], null).getPropertyValue("display");
    if (cpprp !== "none") {
      items[i].style.display = "none";
      break;
    }
  }
}
//----< restore, progressively, menu items on the left >-------------
/*
*  This let's user restore menu items hidden by the previous
*  function.
*/

function scrollMenuRight() {
  var items = document.getElementsByClassName("menuItem");
  var len = items.length;
  var i;
  for (i = 0; i < items.length; ++i) {
    var cpprp = window.getComputedStyle(items[len - i - 1], null).getPropertyValue("display");
    if (cpprp !== "block") {
      items[len - i - 1].style.display = "block";
      break;
    }
  }
}
//----< hide, progressively, menu items on the left >----------------
/*
*  This let's user see menu items that overflow on the right
*  due to page size.
*/
function scrollMenuUp() {
  var items = document.getElementsByClassName("lectItem");
  var i;
  for (i = 0; i < items.length; ++i) {
    var cpprp = window.getComputedStyle(items[i], null).getPropertyValue("display");
    if (cpprp !== "none") {
      items[i].style.display = "none";
      break;
    }
  }
}
//----< restore, progressively, menu items on the left >-------------
/*
*  This let's user restore menu items hidden by the previous
*  function.
*/

function scrollMenuDown() {
  var items = document.getElementsByClassName("lectItem");
  var len = items.length;
  var i;
  for (i = 0; i < items.length; ++i) {
    //items[len-i-1].style.display = "block";
    var cpprp = window.getComputedStyle(items[i], null).getPropertyValue("display");
    if (cpprp !== "block") {
      items[i].style.display = "block";
    }
    else {
      break;
    }
  }
}
//----< scroll page to top >-----------------------------------------

function scrollPageTop() {
  window.scrollTo(0, 0);
}
//----< scroll page to bottom >--------------------------------------

function scrollPageBottom() {
  window.scrollTo(0, 10000);
}
//----< toggle nav keys display >------------------------------------

function mouseAction(event) {

  if (event.button === 2) {
    if (event.target.tagName === 'A') {
      window.open(event.target, "_newtab" + Math.floor(Math.random() * 999999));
    }
    else {
      //toggleNavKeys();
    }
  }
}
//----< toggle nav keys display >------------------------------------

function toggleNavKeys() {
  var nkc = document.getElementsByTagName("navKeysContainer");
  var tog = window.getComputedStyle(nkc[0], null).getPropertyValue("display");
  if (tog === "none") {
    nkc[0].style.display = "inline";
    window.localStorage.setItem("navKeyState", "show");
  }
  else {
    nkc[0].style.display = "none";
    window.localStorage.setItem("navKeyState", "hide");
  }
}
//----< setNavKeys display >-----------------------------------------

function setNavKeys() {
  var nkc = document.getElementsByTagName("navKeysContainer");
  var navKeyState = window.localStorage.getItem("navKeyState");
  if (navKeyState === null) {
    nkc[0].style.display = "inline";
    window.localStorage.setItem("navKeyState", "show");
    return;
  }
  if (navKeyState === "show") {
    nkc[0].style.display = "inline";
  }
  else {
    nkc[0].style.display = "none";
  }
}
