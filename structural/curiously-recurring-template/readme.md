# Curiously Recurring Template Pattern (CRTP)
Also known as a `mixin` (class that contains methods for use by other classes 
without having to be the parent class of those other classes - Wikipedia )

Avoids vtable calls - more like `compile time polymorphisim` to check if a 
class implements the correct functions for the interface
* [Source Code](main.cc)