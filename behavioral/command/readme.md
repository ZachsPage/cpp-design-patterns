# Command
Basically an object oriented equivalent of callback commands.
Can decouple the sender / receiver by encapsulating a `Command` as an object -
thereby letting you parameterize clients with different Commands.
* Dependency injection of the callback object. For something similar but at 
  compile time, see [CRTP](../../structural/curiously-recurring-template/readme.md)
* [Source Code](main.cc)