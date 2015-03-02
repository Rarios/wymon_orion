# Change Log
All notable changes to this project will be documented in this file.
Check out [keepachangelog.com](http://keepachangelog.com/), which we have taken
as an inspiration for our change log.

_Little side note: Development snapshots are marked as 'kismed yyyy_mm_dd'_

## kismed 2015_02_19

### Added

	- Made a change log. Obviously.
	- CMakeLists.txt
	- Namespaces: wo - general WymonOrion namespace; any code will be under
	  this namespace, sys - 'System' module namespace, win - 'Window' module
	  namespace, gfx - 'Graphics' module namespace.
	- 'Include/Namespace.hpp' for WymonOrion specific namespace macros.
	- 'DeveloperTools' folder.
	- 'DeveloperTools/ClearBuild.py', a script to clear the 'Build' folder.
	

### Changed

	- Graphics module follows coding conventions.
	- Renamed folders. Written names out, changed them to uppercase, so they
	  fit the coding conventions. NOTE for repository users: you might have to
	  clear the local repository in order for the name changes to work.
	- Renamed 'wo.doxyfile' to 'WymonOrion.doxyfile'.
	- '.gitignore' file will now make 'git' ignore any files other than the
	  'Resource' folder inside the 'Build' folder. You can now use the normal
	  'Build' folder for debugging.
	- New window icon (thanks to yozoon :3)
	- Rewritten 'README.md'.

### Removed

	- CMakeLists.txt.all, CMakeLists.txt.libsonly, CMakeLists.txt.proj.
	- 'jobs' folder.
