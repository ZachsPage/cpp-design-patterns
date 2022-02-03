# Pattern 
The Singleton pattern ensures that a class has only one instance and provides a 
global point of access to that instance.

This is considered an "anti-pattern" to most, but does have some useful 
applications like:
* Underlying libraries use C-style callbacks (required to be static)
* A system running multiple processes that have their own instance of the
  singleton (opposed to a singleton shared through an entire system)
* The singleton represents something physical in the system where there is only 
  one (like a physical interface)
* [Source Code](main.cc)