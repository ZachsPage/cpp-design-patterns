# Memento
* Without violating encapsulation the Memento Pattern will capture and externalize an object’s internal state
so that the object can be restored to this state later.

* Though the Gang of Four uses friend as a way to implement this pattern it is not the best design
* It can also be implemented using PIMPL (pointer to implementation or opaque pointer).
    * Best Use case is 'Undo-Redo' in an editor.

* The Originator (the object to be saved) creates a snap-shot of itself as a Memento object and passes that reference to the Caretaker object.
* The Caretaker object keeps the Memento until such a time as the Originator may want to revert to a previous state as recorded in the Memento object.
* [Source Code](main.cc)