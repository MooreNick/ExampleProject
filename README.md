Example Project

Hello!

Thanks for taking the time to be here! I created this project with the hope that it will aid me obtaining my first position as a software developer.

If you are interested in learning "how I got here" line X:

If you want a basic overview (summary - three (3) parts) of the project: line Y:

If you want an in-depth overview of the project: line Z:





For this project I wanted to showcase many different skills and more specifically have something to specific and accessible to reference for interviews. I know certain things may not be optimal but I wanted to prove an ability to learn a variety of topics. I look forward to the opportunity to continue to improve upon my abilities.

Part 1: 
Launched a Virtual Machine (VM) in Google Compute Engine (GCE) using Google Cloud Platform (GCP)
On that VM run a game that I developed in C++ using the SFML Library
                   *** I made this game for an assignment while obtaining my Computer Science (CS) degree
                   
Part 2:
Created a Django Application capable of displaying information from Google Cloud Storage

Part 3:
Host a Django Application using GCP

Doing these three parts I gained or showcased experience using: VMs, GCP, C++, SFML, Python, Django, SQL, Ubuntu, HTML, CLI, Git

Z

In-Depth Part 1:
Steps I took to achieve the goal of running a C++ game that I developed on a GCP VM

Starting with a Google Cloud account and basic project:

Lauched a VM running Ubuntu
Using the build in tool I uploaded the game files
Installed the compiler and dependencies
Create makefile
Installed ubuntu desktop and display manager
Connected to VM using Chrome Remote Desktop
Ran the game


Notes: 
- I was stuck for awhile on the program compiling but not being able to run. I was getting an error involving the $DISLAY environment variable. I manually set it to both :0 and localhost:10 but to no avail. Installing the desktop and connected via Chrome Remote Desktop alleviated the issue. In an attempt to resolve this issue another way, I connected to the VM using PuTTy, allowing X11 passthrough, but that also did not fix the issue.
- It was more challenging that I thought. Initially I thought I would be able to just upload the .exe and use wine to run it. That was not working so I installed the compiler and dependencies to run it and created a makefile to compile and link the code. Running that was showing issue with $DISPLAY enrionment variable. So I manually set the $DISPLAY environment variable to both ':0' and "localhost:10' to no avail (same error). Then I got the desktop working (hey, if it can show that?) and that made it work. Assuming now the .exe would also work, considering it should be the same-ish as the one I uploaded.
Possible Upgrades:
- Make it write to bucket (GCS C++ Client library?)
- Make it run more efficienty (upgrade VM?)
![projectPhoto3](https://github.com/MooreNick/ExampleProject/assets/123336257/69d3c7d8-1dfd-4032-ad60-02798bbdd238)


In-Depth Part 2:
Steps I took to achieve the goal of creating a Django Application that can display information from Google Cloud Storage

Starting with a Google Cloud account and basic project:

Created a bucket in Google Cloud Storage
Added a .csv file to the bucket
Create data data for .csv [see /ExampleProject/Website/Misc/misc.py]
Create directory locally
Created django project
Using premade base.html (credits in source) added two other .html pages and did the back-end Django coding
Using Pandas read GCS csv and updated local database to include csv
Ran Django project



Notes:
- I read the data in as a Pandas DataFrame Object directly from GCS
- I then updated the local sqlite to include the items from the above object
  Possible Upgrades:
- pass render() df object directly?
-   If not: upgrade so it does not simply append to sqlite as it currently does


In-Depth Part 3:
Steps I took to achieve the goal of hosting a Django app on GCP

Starting with a Google Cloud accound and basic project:

Enabled appropriate API Access
Ran marketplace Django app

Notes:
- Essentially proof of concept for hosting a Django app
Possible Upgrades:
- Host the files from part 2




