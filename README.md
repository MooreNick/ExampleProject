# Example Project

Hello!

Thanks for taking the time to be here! I created this project with the hope that it will aid me obtaining my first position as a software developer.
This README is in three sections, first a brief summary of the project, second in-depth walkthrough of project, third about me, project motivation.

For this project I wanted to showcase many different skills and more specifically have something specific and accessible to reference for interviews. 
I know certain things may not be optimal but I wanted to prove an ability to learn a variety of topics. I look forward to the opportunity to continue 
to improve upon my abilities. Some of the skills I showcased by doing the below: VMs, GCP, C++, SFML, Python, Django, SQL, Ubuntu, HTML, CLI, Git.



## Summary

Part 1: 
Launched a Virtual Machine (VM) in Google Compute Engine (GCE) using Google Cloud Platform (GCP).
On that VM run a game that I developed in C++ using the SFML Library. I made the game as an assignment
while obtaining my Computer Science (CS) degree. View the source here: ```ExampleProject/Game/game_main.cpp```
                   
Part 2:
Created a Django Application capable of displaying information from Google Cloud Storage

Part 3:
Host a Django Application using GCP



## In-Depth Walkthrugh

#### In-Depth Part 1:
Steps I took to achieve the goal of running a C++ game that I developed on a GCP VM

Starting with a Google Cloud account and basic project:

General Process:
- Lauched a VM running Ubuntu
- Using the built in tool I uploaded the game files
- Installed the compiler and dependencies
- Create makefile
- Installed ubuntu desktop and display manager
- Connected to VM using Chrome Remote Desktop
- Ran the game

Notes: 
- On the desktop:
   I was stuck for awhile on the program compiling but not being able to run. I was getting an error involving the $DISLAY
   environment variable. I manually set it to both ```:0``` and ```localhost:10``` but to no avail. Installing the desktop and connecting
   via Chrome Remote Desktop alleviated the issue. In an attempt to resolve this issue another way, I connected to the VM using
   PuTTy, allowing X11 passthrough, but that also did not fix the issue. It was more challenging than I thought. Initially I
   thought I would be able to just upload the .exe and use wine to run it. That was not working so I installed the compiler and
   the needed dependencies and created a makefile to compile and link the code. Running that was showing the issue with the
   $DISPLAY environment variable. So I manually set the $DISPLAY environment variable to both ':0' and "localhost:10' to no avail
   (same error). Then I got the desktop working (hey, if it can show that?) and that made it work. Assuming now the .exe would also
  work, considering it should be the same-ish as the one I uploaded.

Possible Upgrades:
- Make it write to bucket (name/score) (GCS C++ Client library?)
- Make it run more efficienty (upgrade VM?)
![projectPhoto3](https://github.com/MooreNick/ExampleProject/assets/123336257/69d3c7d8-1dfd-4032-ad60-02798bbdd238)
Photo is screenshot of file running on VM

#### In-Depth Part 2:
Steps I took to achieve the goal of creating a Django Application that can display information from Google Cloud Storage

Starting with a Google Cloud account and basic project:

General Process:
- Created a bucket in Google Cloud Storage
- Added a .csv file to the bucket
- Create data data for .csv ```ExampleProject/Website/Misc/misc.py```
- Create directory locally
- Created django project
- Using premade base.html (credits in source) added two other .html pages and did the back-end Django coding
- Using Pandas read GCS csv and updated local database to include csv ```ExampleProject/Website/App/views.py```
- Ran Django project

Notes:
- I read the data in as a Pandas DataFrame Object directly from GCS
- I then updated the local sqlite to include the items from the above object

Possible Upgrades:
- pass ```render()``` df object directly?
-   If not: upgrade so it does not simply append to sqlite as it currently does
- Add add a .css and corresponding .html
- Add .js for fun content
![projectPhoto1](https://github.com/MooreNick/ExampleProject/assets/123336257/ddfef2c8-e568-473a-a675-7e7f880b6e2c)
Photo is screenshot of output

#### In-Depth Part 3:
Steps I took to achieve the goal of hosting a Django app on GCP

Starting with a Google Cloud accound and basic project:

General Process:
- Enabled appropriate API Access
- Ran marketplace Django app
 
Notes:
- Essentially proof of concept for hosting a Django app

Possible Upgrades:
- Host the files from part 2
![projectPhoto2](https://github.com/MooreNick/ExampleProject/assets/123336257/334879c0-01d2-474b-bfc7-27bd0adf6909)
Photo is screenshot showing that app is running



## About me and motivation

I graduated with a BS in CS last December. This is my third degree, I have another bachelor's 
and an associate's. This is a career change for me and am still looking for my first opportunity. I keep trying to modify 
my strategy to optimize interviews. My intent is to land a job as a developer, but that seems like such a broad term. I 
think AI and ML is an extremely interesting field and would love to learn more about it. I thoroghly enjoy programming 
and am ultimately seeking a position to help me improve my skills, particularly in C++ and/or Python.

I think creating this project and having something I can reference and something I could easily provide for technical clarifications 
will greatly aid in obtaining my first position. Throughout my job search so far, it seems a lack of professional experience has been 
caused me to be prioritized below other candidates. I elected to not apply for internships to graduate at an accelerated rate. My hope 
is that this project can demonstrate the ability to learn and balance many different programming languages and technologies.

I am also excited for the idea to have something like this project at the beginning of my career. It will be fun to look back and see 
progress in different skills.
