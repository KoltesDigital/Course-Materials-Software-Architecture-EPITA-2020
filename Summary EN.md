# Course Summary

> Summary of the key learnings seen through the course.

Even if the course is focused on a game engine, these takeaways can apply in other domains as well.

## Why architecture anyway?

- Useful for long-term projects, with large teams.
- Allows for a better maintainability and evolution of the code base.
- Allows for reusing modules in other projects.
- Potentially reduces the number of "bugs".

## Hierarchical modularity

For large projects, the code can be split into several modules. Module may mean: function, class, namespace...

They can be organized in a hierarchy, from low-level to high-level. High-level modules rely on lower-level modules, like in building architecture: bricks stand on lower bricks.

Therefore, low-level modules have very simple behaviors, and the higher the module is, the more complex its behavior becomes. For instance in a game engine, from highest to lowest modules:

- editor, tools;
- game-specific subsystems;
- gameplay system;
- sub-engines: graphics, physics, network...
- data (resources/assets);
- core functionalities: debug, file system, math, string...
- platform abstraction, operating system.

## Dependencies

There are dependencies from higher-level modules to lower-level ones.

For instance, a gameplay system surely relies on math functions. There is a strong dependency from the gameplay to the math.

In some cases, it is useful to have a dependency to a set of features, instead to the actual implementation. An interface declares that an object has these needed features, without specifying how they are fulfilled.

For instance, the graphics engine relies on a windowing system, provided by the OS or some other core library. In order to make the game cross-platform, an interface should abstract the windowing system. Each OS will require an actual implementation to make the bridge accordingly.

When the module A has a dependency to B, and B to A, this is called a dependency cycle. This should be avoided because it constrains the two (or more) modules: one module cannot be reused without the others, and if one changes, the others may need to change too.

We can therefore state: modules can access to lower ones, but they shall not access to higher ones. Violating this rule leads to dependency cycles.

To break a dependency cycle, look if you really need to rely on the implementation. If you only rely on features, you can abstract them with an interface.

Beware of the Singleton pattern, which easily creates dependency cycles.

Dependency injection is a global term describing the linking of modules. The dependency inversion principle refers to the set of rules stating that modules should rely on abstractions, thus the linking is done through interfaces.

## Encapsulation

When using a class, you should not know how it works. You should only know the features that it allows.

Failing to properly encapsulate classes may lead to:

- bearing multiple responsibilities in a same class;
- more dependencies than needed;
- harder to test.

## Single responsibility principle

Don't be stingy on classes! Each class should handle a single responsibility. If a class handles multiple responsibilities,

- the implementation will be large, thus may contain more bugs;
- it will be hard to test. And because it may contain more bugs, it's very dangerous!
- it will be hard to insert new features;
- reusing the class means reusing all responsibilities at once.

## RAII

A resource that can be acquired and released may be represented with a class, whose constructor acquires the resource, and destructor releases it.

For instance:

- File access is typically wrapped by a `File` class, which automatically closes the handle at destruction;
- `std::lock_guard` automatically locks and unlocks a mutex;
- `std::unique_ptr` automatically deletes a pointer.

## Memory ownership

The memory owner is responsible for some variables' lifetime, i.e. allocation and freeing.

In case of a simple variable, the owner is the scope of its definition. On a low-level point of view, the variables live on the stack, and going out of scope releases the variables. For instance:

    void function()
    {
    	Object o;
    	o.doSomething();
    	...
    } // o is destroyed here.

In case of a pointer, a memory block is allocated on the heap, and the pointer holds a reference to it. It is especially important that the owner is clearly defined:

- if the memory block is not freed, the program creates memory leaks, and leads to memory overuse;
- if the memory block is freed twice, the second time is unexpected and will trigger a program error (exception).

Moreover, the order of allocation and deallocation is important too.

## Handle

Sometimes, we want to hide some objects, e.g. for control and ownership, but other systems should be able to handle them. In order to do so, these systems are given way to refer to these objects, never accesing them. For instance:

- a file handle is given when the OS opens a file. It is required to perform operations on it, including reading and writing.
- a token is generated when someone logs in their account on a website. Through a cookie, this token is given to the server on every request.

## Specialization

Sometimes, we need to specialize a behavior. In modern OOP languages, there are usually two ways to do that.

Inheritance is a kind of specialization where you enhance already existing features.

Interfaces can be seen as a special case of inheritance, where the features are specified but not implemented.

Composition is another way to specialize a behavior. Making a function which relies on another function can be seen as a specialization.

The Entity-Component pattern genericizes this. The entity is a plain container, with some components. These can be seen as abilities, so by adding a component, the object gains new abilities. This is mostly used to manage composition at runtime.

The Strategy pattern combines the principles of composition and dependency injection, where the host object relies on another object to actually do things.

On a memory point of view, inheritance and composition are essentially the same.

## Visitor pattern

The visitor pattern allows for decoupling the data from the code which handles it.

- The data only declares its values to a visitor interface.
- The actual visitor (implementation of the interface) handles the values accordingly.

This pattern is useful for deconstructing an inheritance model without relying on dynamic casts.

    interface FSVisitor
    	handleFile(FileInfo &)
    	handleDirectory(DirectoryInfo &)

    abstract class FSEntry

    class FileEntry : FSEntry
    	FileInfo info
    	accept(FSVisitor &visitor) => visitor.handleFile(info)

    class DirectoryEntry : FSEntry
    	DirectoryInfo info
    	accept(FSVisitor &visitor) => visitor.handleDirectory(info)

    class Search : FSVisitor
    	handleFile(FileInfo &) ...
    	handleDirectory(DirectoryInfo &) ...

## Model View Controller (MVC)

The MVC idiom allows for decoupling data (model) from its representation (view). The view cannot change the model directly: change actions pass through the controller, which can change the model. Then, the model notifies the view of its changes.

Other variations have subtle changes (MVD, MVVM, MVP...). However, the basic principle is that the model is independent of the view. Typically,

- the model is low-level, because it contains only data and their behaviors;
- the view is high-level, because it relies on rendering a GUI;
- the controller is in-between, because it is executed by the view, handles the model, and needs other active subsystems to do so.

It is then possible to have multiple views of the same model. In this case, there may one or some controllers, depending on the model-view paradigm and whether the views are significantly different.

## Testing (including Unit Tests)

The sooner a bug is avoided, the less it costs to the project. The compiler already avoids bugs (well, if it won't compile, it isn't even runnable). Then come automated tests, then "human" tests (e.g. run by testers in the quality assurance team), then... users. Bugs appearing at the end user side are the most expensive, they might ruin a brand image.

Unit tests are automated tests on unit parts of the code or system. Any class should be accompanied by tests, which check all possible usages and their outcomes (_code coverage_).

Integration tests are higher-level tests, integrate multiple modules or classes, and test that they work well together.

During development, tests are run periodically to ensure that they still pass. Therefore, they are an essential security net. If a regression appears, tests shall catch it.

Any test, whether automated or human-driven, should have the shape: given preconditions, when computations are executed, actual results happen. Writing multiple tests as a scenario could make them more readable.

Be concrete with tests. For instance, when comparing values, use equality comparisons if possible. Because you know the preconditions, you know the expected results.

As a consequence, modules dealing with randomness are really hard to test.

Tests also serve as documentation, because they show how to use the modules, and these examples are guaranteed to always be up-to-date.

It is best to automatize test executions. For instance, you can launch them every time someone commits to the repository. This will help to fix regressions as soon as they appear.

Automatize tests as much as you can, even for other test types. For instance for a video game project, you can launch the game with a bot following a predefined path, in order to ensure that no obstacles appear, that no frame takes more time to render than allowed, etc.

## Test-Driven Development (TDD)

Writing automated tests is actually more about a programming methodology, where one would first write the specifications of their future modules. Because the specifications are eventually runnable, they can check whether they are fulfilled. Therefore, this programming style is deeper than just writing _a posteriori_ tests.

These specifications act as contracts between the programmers and the customers. Always start by writing contracts, which forces to really think about the needs and settle them. Then, do your work and make sure the contracts are fulfiled. As simple as that.

## Metrics

Some metrics can give you insights on the code health. Some of them are;

### Per project

- Code coverage;
- Number of duplicated lines, or duplication ratio;
- Number of bugs, per line of code, or over time;
- Number of external dependencies.

### Per file / class

- Number of lines;
- Number of functions;
- Inheritance depth.

### Per function

- Cyclomatic complexity;
- Number of parameters: when a call has many parameters, it is harder to tell which one does what;
- Number of lines.
