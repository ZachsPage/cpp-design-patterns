# Chain of Responsibility
* Calls a chain of receivers to handle a request / command 
  * Avoids coupling the sender of a request from its receivers
* I liked this example a little better, so adopted it instead:
    * [From here](https://refactoring.guru/design-patterns/chain-of-responsibility/cpp/example)

* **Note**: The pattern / example forces each handler to call the base's handler
(to in turn call the next possible handler). Seems error prone, as one incorrect
handler could break the chain - Instead, there is a class to create the chain, 
and also pass along the request until it was handled.
  * So, technically this example may not be a proper representation (its 
    basically the [Visitor](../visitor/readme.md), actually)

* [Source Code](main.cc)