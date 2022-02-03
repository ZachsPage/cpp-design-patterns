# Design Patterns From Wikibooks
This repo's source files / readme were mainly pulled from the content found on 
[wikibooks](https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns)
* If the Wikiboook content did not cover certain descriptions / code, then it was
  pulled from elsewhere and the link is available in the `readme`
* **Disclaimer** - I adapted these patterns and added personalized comments / 
  changes that were helpful to me. These examples should not be taken as 
  `wikibooks said so`, as they are just interpretations from their examples.

The goal is to have a simple description / reference for each design pattern.

The example programs can be run from `./a_build/bin/<catgory>/<pattern>` after
running `make all`.

# Categories of Design Patterns
Below are descriptions of the each main design pattern categories, with main 
their patterns listed below. 
* The patterns I found the most useful are **in bold**

## Behavioral Patterns
Call encapsulated algorithms & handle responsibilities between objects
* [From here](https://refactoring.guru/design-patterns/behavioral-patterns)
### Patterns
* [**Chain of Responsibility**](./behavioral/chain-of-responsibility/readme.md)
* [Command](./behavioral/command/readme.md)
* [Interpreter](./behavioral/interpreter/readme.md)
* [Iterator](./behavioral/iterator/readme.md)
* [Mediator](./behavioral/mediator/readme.md)
* [Memento](./behavioral/memento/readme.md)
* [Observer](./behavioral/observer/readme.md)
* [**State**](./behavioral/state/readme.md)
* [Strategy](./behavioral/strategy/readme.md)
* [Template Method](./behavioral/template-method/readme.md)
* [**Visitor**](./behavioral/visitor/readme.md)

## Creational Patterns
Simplify/unify object creation mechanisms
### Patterns
* [**Factory / Abstract Factory**](./creational/abstract-factory)
* [**Builder**](./creational/builder)
* [Prototype](./creational/prototype)
* [Singleton](./creational/singleton)

## Structural Patterns
Assemble classes into larger structures while maintaining flexibility/efficiency
* [From here](https://refactoring.guru/design-patterns/structural-patterns)
### Patterns
* [Adapter](./structural/adapter/readme.md)
* [Bridge](./structural/bridge/readme.md)
* [**Composite**](./structural/composite/readme.md)
* [**CRTP**](./structural/curiously-recurring-template/readme.md)
* [**Decorator**](./structural/decorator/readme.md)
* [Facade](./structural/facade/readme.md)
* [**Flyweight**](./structural/flyweight/readme.md)
  * Useful & cool concept, but main use case would be limited system RAM
* [Proxy](./structural/proxy/readme.md)