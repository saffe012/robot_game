### CSci-3081W Project Support Code Makefile ###

# This is the main Makefile for the project.  It provides easy access
# to building and testing the whole project, which requires running
# make in subdirectories.

.PHONY: proj01 docs clean

# Build everything that can be built for this project
all: proj01

# Build the bin/proj01 executable by running make in the project's src directory
proj01:
	$(MAKE) -C src all

# Build docs/html, docs/latex by running doxygen in the project's docs directory
docs:
	@doxygen docs/Doxyfile
	@open docs/html/index.html

# Clean everything that has been for a fresh start
clean:
	$(MAKE) -C src clean
