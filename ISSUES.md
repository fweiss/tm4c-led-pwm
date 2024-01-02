# Issues

## Debugger won't start - error
- check that the correct env in platformio.ini is selected

## C++ templates
Goal: A close to zero-cost, fluent API.

This worked pretty well in the small scale.
Static module templates capture offsets at compile time.
Then static members of those are class templates, which provide offset
and opererator=() definitions.
The compiler easily optimizes that to inline, zero-cost code.

But passing references to those class instantiations doesn't seem to work.
Theoretically, the constructor for a component makes the compiler
specialize the correct class for the given template parameters.
So the specialized code can be generated and is available
as component member variables.
It also looks like a function, such as setupPwm(), needs to be templated.
This is messy and gets worse with nested templates (such as TimerBlock::Timer).
Another suggested way is to have a non-template base class for the
specialized template classes, but this introduces vtables and addition
member templates, and duplication of source code.
Not sure if the compiler can optimize out the vtables.

So let's think about the main mechanism.
We're relying on static const members and optimizable member class templates.
The compiler appears to optimize well from that.
The members really only contain code, no data.
The overall structure is more like a tree of classes, not instances.

Maybe we could structure the API as a tree of nested, templated classes.
The class members are either static const primitives, such as 32-bit addresses
or tight member functions, such as operator=() and operator int()().
Can we assume the compiler doesn't generate any compiled code or
allocates any memory.
It is only kept in the compiler internally.
Can we assume the compiler does lazy evaluation, that is code is
only output when a class template is specialized by being "called",
where it is the <> that indicates a compile-time "call".
This structure may strain the compiler's memory usage.
But it may provide a close to zero-cost, fluent API.

