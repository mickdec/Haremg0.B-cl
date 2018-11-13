<center><img align="center" src="https://raw.githubusercontent.com/mickdec/Haremg0.B-cl/master/READMERES/Haremg0-200x200.png" /></center>
<center><h1 align="center">Haremg0.B!cl</h1></center>
<center><i align="center">A tool for creating a fully obfuscated Trojan Horse for windows.</i></center>

<p align="center">
  <img style="width:70%" src="https://raw.githubusercontent.com/mickdec/Haremg0.B-cl/master/READMERES/01.gif" />
</p>
<h2>REQUIREMENTS</h2>
<ul>
<li>1. A <b>windows operating system</b> (preferably Win10).
<li>2. An <b>external file provider</b> :
could be an <b>apache, on a vps</b> or on your personnal machine, if it can distribute you a file just by the ip you have defined, on WAN or LAN (Like X.X.X.X/MyFile) it will work fine.
<li>3. <b>A Host who will listen for a TCP connection on a defined port.</b> You can use a metasploit framework handler for example, <b>using "multi/handler"</b> and setting your <b>LPORT to the trojan defined port</b>.
<li>4. <b>g++</b> (and gcc if you want to recompile "Source_Code_Generator.cpp") you can install gcc or g++ with <a href="https://cygwin.com/setup-x86_64.exe">CygWin</a>.
</ul>
<h2>DISCLAIMER</h2>
<p><i>
This tool is meant to be used only for benevolent purposes.
<br>I am in no way responsible for your actions and the use you can make of that tool.
</i><p>
<h2>WHAT THIS TOOL DOES</h2>
<p align="center">
  <img src="https://raw.githubusercontent.com/mickdec/Haremg0.B-cl/master/READMERES/00.png" />
</p>
<p>
This tool let you create a fully obfuscated trojan horse. This trojan will :
<ul>
<li>Create a directory on the "Victim".
<li>Download 2 files (FileA and FileB) from the File provider you have specified into the created dir.
<li>Run FileA who will run FileB.
<li>FileB will send by TCP a SHELL from the victim to your specified host IP and PORT.
<li>Create à planified task who will be runned all 5 minutes, who run FileA.
</ul>
</p>
<h2>USAGE</h2>
Run Haremg0.exe and follow the instructions no parameters is needed for now.
<ul>
<li>1. Define the path and the name of the created dir (ex: C:/test)
<li>2. Define the ip of your file provider (ex : X.X.X.X:85/Files)
<li>3. Define the name of the two files who will be downloaded (ex: FileA,FileB)
<li>4. Define the host ip and port who will receive the connection (ex : X.X.X.X and 4499)
<li>5. The exe will be created !
</ul>
<p>
