WymonOrion project
==========

The project is currently in its first major release state: **angad 0.0.0**

This is the WymonOrion project repository. It consits of two major parts:
The first part is a set of general purpose libraries. The second part is a set of code files utilizing those libs to build an application.

# Project Branches

Within the project's repository, you will find a couple of different branches. All of which have their own purpose, a short description is listed below:

* **master** - Latest official release, consider it stable.
* **dev** - Latest developement snapshot, may or may not be stable.
* **agx_1** - Personal developer branch.
* **simmac** - Personal developer branch.
* **yozoon** - Personal developer branch.

The **master** branch will always provide you with the latest version of WymonOrion that you can use to work with. However, if you want the latest development snapshot, use the **dev** branch. Internally, we use this branch to work on the next release, merge independent work on the codebase, etc., so the code within this branch may not be fully stable. The other three branches are listed as 'Personal developer branch', because they are used by members of the developing team to work independently on different parts of the project. If you want to get insight into their current work, feel free to dive into one of these branches.

# Libraries

The libraries consist of the _graphics_ and the _utils_ library. The _graphics_ library partly uses the **SFML**, reimplements different classes provided by the **SFML** and adds an animation class on top of it. In addition to that, the _graphics_ lib has special data structures, not provided by the **SFML** itself, taking care of memory management for textures and animation frames.
Note that the libraries can be used without the application, they only depend on the **SFML**.

# Application

It is hard to describe what the main purpose or the main functionality of the application is. At the moment, it is sort of a playground to test different ideas. As already mentioned, the application uses the libraries from above.

# Building

Depending on what you want to do with this project repository, building the main application, building only the libraries or even building your own project with self-written source files utilizing the provided libs, different _CMakeLists.txt_ files are provided in the project root. These files are as follows:

* CMakeLists.txt.all - Builds the application and the libraries
* CMakeLists.txt.libsonly - Builds only the libraries
* CMakeLists.txt.proj - Build your own project with the provided libraries

To activate your preferred build, remove the last part of the filename, so you end up having a _CMakeLists.txt_ file. Read the instructions at the top of the file. After that you should be ready to build.
The recommended way to build the project is to go into the _build_ directory and execute the following commands (on a Linux-like system):

```
cmake ..
make
```

or to use the other ways of building a project that uses CMake.

# Tools

This project uses two well known tools: **CMake** and **Doxygen**. This means that it provides a _CMakeLists.txt_ file, as well as a doxygen configuration file, _wo.doxyfile_. Building has already been covered above, but because the code is (mostly) well documented, you can generate an HTML documentation with just one line in the terminal (on a Linux-like system) as well:

```
doxygen wo.doxyfile
```

or, again, use the other ways to run Doxygen. Note that this documentation may also include graphs related to the code. In order to generate them, simply install **Graphviz** on your computer and make sure it is in the system's _PATH_ variable.

I would also like to mention that this project has been written in **GVIM**, a version of the well known **VIM** editor. I believe that those who have worked only little with the editor will think that this is total madness. I also believe that those who have worked somewhat more with **VIM**-like editors will understand why I think it is the only right choice.

# ToDo

Please note that I am still a student, currently in the year of my final exams. Therefore, my preferred way of working is the **ASAP** style, as soon as possible fixing and implementing of as much as possible. Also note that, even though this repository is fairly young, the code has been written in a couple of months and only recently been made into a git repository.

- [x] Insert the new implementation of the _graphics_ and the _utils_ library.
- [x] Adjust legacy code from application, so it will work with the new library implementation.
- [ ] Use a single, clear coding convention (currently this is not the case, which is due to the code being written over a couple of months).
- [ ] Test builds on different platforms.
- [ ] Remove Herobrine.

If there is anything you want to tell me about the project, from feedback to contribution, here is the address to do so: **wymon.orion@gmail.com**

Best, Sebastian
