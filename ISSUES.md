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

A new problem cropped up. "Boileplate" code, such as for setting up a digital pin
would tend to be duplicated as it's template code. We'd like to have user functions
that set several RegisterBits, but that can be specialised for digital pins
via run-time parameter instead of compile-time parameter.

For example: a digital pin an be configured via ``theLed.directionOtput = true``.
we'd also like to be able to do this:
```
Digtal
```

Can bottlenect it through a plain class This class does the actual work but doesn't need to be 
tenplated. The current Register* classes would have templated classes, such as
``RegisterBit<base + 0x50c> outputDirectionEnable;``, then ``bitset``, then ``write``.

So, tried a no-template implementation, but it didn't work 100%.
Tried introducing the register addresses as a base class,
but observed unwanted initializtion code, not as slick as the templated version.
You see ``RegisterAddress<portBase>`` is really different than ``RegisterAddress(portBase),
even when the members are const. Quite a bit different than constexpr, even though
the compiler often does a good optimiztion with const and even without.
And trying to use a parent class template whose template parameters come from
the derived class constructor parameters doesn't work.

There is a notion of constexpr constructors that hasn't benn tried.
