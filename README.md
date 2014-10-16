WymonOrion project
==========

This is the WymonOrion project repository. In its main structure, two different parts can be found. The first part is a set of general purposelibraries. The other part is a set of code files utilizing those libs to build an application.

# Libraries

The libraries consist of the _graphics_ and the _utils_ library. The _graphics_ library partly uses the **SFML** itself, reimplements different classes provided by the **SFML** and adds an animation class on top of it. In addition to that, the _graphics_ lib has special data structures, not provided by the **SFML** itself, taking care of memory management for textures and animation frames.
Note that the libraries can be used without the application, they only depend on the **SFML**.

# Application

It is hard to define what the main purpose or the main functionality of the application is. At the moment, it is sort of a playground to test different ideas. As already mentioned, the application uses the libraries from above.

# Building

Note that right now the application won't compile, because some code snippets consist of legacy code and have to be adjusted for the new implementations of the utilized libraries. However, the libs themselves should compile without major problems, provided that the **SFML** is installed on the computer. You simply have to remove the code from the _CMakeLists.txt_ file that gives the instructions to build the executable and only leave the code for the libraries if you want to try it out. All include files can be found in the _incl/graphics_ directory.
The recommended way to build the project is to go into the _build_ directory and execute the following commands (on a Linux-like system):

```
cmake ..
make
```

or to use the other ways of building a project that uses CMake.

# Tools

This project uses two well known tools: **CMake** and **Doxygen**. This means that it provides a _CMakeLists.txt_ file, as well as a doxygen configuration file, _wo.doxyfile_. Building has been covered above, but because the code is (mostly) well documented, you can generate an HTML documentation with just one line in the terminal (on a Linux-like system):

```
doxygen wo.doxyfile
```

of, again, use the other ways to run Doxygen.

I would also like to mention, that this project has been written in **GVIM**, a version of the well known **VIM** editor. I believe that those who have worked only little with the editor will think that this is total madness. I also believe that those who have worked somewhat more with **VIM**-like editors will understand why I think it is the only right choice.

# ToDo

Please note that I am a student, currently in the year of my final exams. I will fix and implement as much as possible, but only if I have the time to do it. Also note that, even though this repository is fairly young, the code has been written in a couple of months and only recently been made into a git repository.

- [x] Insert the new implementation of the _graphics_ and the _utils_ library.
- [ ] Adjust legacy code from application, so it will work with the new library implementation.
- [ ] Use one clear coding convention (currently this is not the case, which is due to the code being written over a couple of months).
- [ ] Test builds on different platforms.
- [ ] Remove Herobrine.

Best, Sebastian.
