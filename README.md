WymonOrion project
==========

This is the WymonOrion project. Made from real men's sweat and the perfect pinch of love since 1985 <3.

Current stable release: **angad 0.0.0**

Current development snapshot: **kismed 2015_03_02**

## The Project

The name **'WymonOrion'** comes from the greek expression 'wymonere orionibus', meaning 'to be filled with awesomeness'. 

Okay, good, we're just kidding. It's actually latin.

Starting off as a little side project to test the 'time.h' or 'ctime' STL library, WymonOrion has since evolved into a playground for everything that interests us. We're a group of students with a passion for programming so finding a task, working on it and then adding the results to the WymonOrion application is what we love to spend our time with.

## The Purpose

Right now our little developer team is working on the idea of integrating a Python interpeter into WymonOrion, enabling the user to run Python scripts with all the utilities that the main application provides. This includes the SFML Graphics library, with integrated memory management for textures, an animation class, and so forth.

Ultimately, we want to make WymonOrion an application hub for tools written in Python, where either you write them yourself or you take those already provided. It is all open-source, free for anyone to use and code for, so we hope that in future there is a lot of tools to be able to use.

## The Branches

Within the project's git repository, you will find a couple of different branches. All of which have their own purpose; a short description is given below:

* **master** - Latest official release, consider it stable.
* **dev** - Latest developement snapshot, may or may not be stable.
* **agx_1** - Developer branch.
* **simmac** - Developer branch.
* **yozoon** - Developer branch.

The **master** branch will always provide you with the latest version of the WymonOrion project. However, if you want to try out our latest work, use the **dev** branch. Internally, we use this branch to work on the next release, merge independent work on the codebase, and so on. The other three branches are working branches for our developers.

## The Build

Depending on your preferences, whether you're more the 'I look on the code and just appreciate it's beauty' kind of guy or more the 'doer' one, you might want to build the code. Luckily, this is a fairly easy thing to do.

First, make sure you've installed **CMake**, either the command line tool or the GUI application. We recommend the command line tool, but both options are fine and you can start building.

### CMake command line

The following description will assume you have a Linux-type terminal installed on your computer. OS X and Windows users might want to go to the CMake GUI description. 

Put yourself into the 'Build' folder of this project and run the following commands:

```
cmake ..
make
```

Done! Now you see why we prefer the command line tool.

### CMake GUI application

Open the application, click the 'Browse Source...'-button and select the folder with this file in it as the source directory. Then, click the 'Browse Build...'-button and select the 'Build' folder of this this project, which you can find in the directory of this file too. Hit 'Configure' and then 'Generate'. After this, depending on your settings, build it either with the 'make'-utility of the terminal or other applications.

Done, but you might need to find tutorials for your specifc settings.

## The Documentation

Every good code needs a good documentation, so this is what we have packed this project with. We use inline code documentation and **Doxygen** for the final documentation compilation. You can look online for a tutorial on how to use Doxygen. Once you know how to use it, the file you're looking for is 'WymonOrion.doxyfile', which is in the same directory as this file. Feed Doxygen with it and you'll have a full HTML documentation of the project including features like: 

- Short function descriptions
- Long function descriptions
- Trypos and
- Misspelings 

If you want to have additional features like inheritance diagramms, call and caller graphs, and so on, you can also install **GraphViz** and then run Doxygen. This will create those documentation features as well. Note that you might have to put the path to the GraphViz-executable into a PATH variable in order to make sure Doxygen knows where to find GraphViz, so you might want to look this up online. On Unix-type systems, however, this should be done for you.

## The Feedback

There is no such thing as improvement without the right amount of 'Vitamin F', so we're pleased to get feedback of any kind on the WymonOrion project. Send your feedback to the following address: **wymon.orion@gmail.com**

Thank you very much for your patience reading this file and also thank you for using WymonOrion, we do our best to make up for it's latin meaning as much as we can :).

Sincerely,

WymonOrion Developer Team
