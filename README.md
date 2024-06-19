Example Project

Hello!

Thanks for taking the time to be here! I created this project with the hope that it will aid me obtaining my first position as a software developer.

If you are interested in learning "how I got here" line X:

If you want a basic overview (summary - three (3) parts) of the project: line Y:

If you want an in-depth overview of the project: line Z:





For this project I wanted to showcase many different skills and more specifically have something to specific and accessible to reference for interviews. 

Part 1: 
Launched a Virtual Machine (VM) in Google Compute Engine (GCE) using Google Cloud Platform (GCP)
On that VM run a game that I developed in C++ using the SFML Library
                   *** I made this game for an assignment while obtaining my Computer Science (CS) degree
                   
Part 2:
Created a Django Application capable of displaying information from Google Cloud Storage

Part 3:
Host a Django Application using GCP

Doing these three parts I gained or showcased experience using: VMs, GCP, C++, SFML, Python, Django, SQL, Ubuntu, HTML, CLI, Git


In-Depth Part 1:
Steps I took to achieve the goal of running a C++ game that I developed on a GCP VM

Starting with a Google Cloud account and basic project:

Lauched a VM running Ubuntu
Using the build in tool I uploaded the game files
Installed the compiler and dependencies
Create makefile
Installed ubuntu desktop and display manager
Connected to VM using Chrome Remote Desktop
Run the game


Issues: 
- I was stuck for awhile on the program compiling but not being able to run. I was getting an error involving the $DISLAY environment variable. I manually set it to both :0 and localhost:10 but to no avail. Installing the desktop and connected via Chrome Remote Desktop alleviated the issue.
- In an attempt to resolve this issue another way, I connected to the VM using PuTTy, allowing X11 passthrough, but that also did not fix the issue.
![projectPhoto3](https://github.com/MooreNick/ExampleProject/assets/123336257/e9b5e8f8-f650-484e-9200-fc500e3dc4bd)

In-Depth Part 2:
Steps I took to achieve the goal of creating a Django Application that can display information from Google Cloud Storage

Starting with a Google Cloud account and basic project:

Created a bucket in Google Cloud Storage
Added a .csv file to the bucket
Wrote a brief Python script to rather "random" information for above file [see /ExampleProject/Website/Misc/misc.py]


