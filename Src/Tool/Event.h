#ifndef SRC_TOOL_EVENT_H_

#define SRC_TOOL_EVENT_H_

#include <vector>

namespace CC {

// Created by : Arnold the Aardvark : http://www.codeproject.com/Articles/6197/Emulating-C-delegates-in-Standard-C

// Event class - invoke operator() on a collection of objects.
// Note that only one argument is supported for the parameters of
// the target signature. However, it is trivial to extend this to
// multiple arguments by having multiple templates similar to this
// one.
template <typename Return, typename Arg1>
class Event {
 private:
    // Base class - specify the signature.
    class  Base {
     public:
        // Required for polymorphic destruction to work properly.
        virtual ~Base() { }

        // Target signature. Invoked through base class pointers.
        virtual Return operator()(Arg1) = 0;
    };

 public:
    // Derived class - parametrise the implementation so we can specify the
    // target class in client code.
    template <typename Class>
    class T : public Base {
        // Signature applied to a pointer-to-member for target class.
        using Func = Return(Class::*)(Arg1);

     private:
        Class* _this;  // Pointer to the object we are delegating to.
        Func   _func;  // Address of the function on the delegate object.

     public:
        T(Class* pThis, Func pFunc) : _this(pThis), _func(pFunc) { }

        // Invoke the function throught the pointer-to-member.
        Return operator()(Arg1 pArg1) override {
            return (_this->*_func)(pArg1);
        }
    };

 public:
    // Derived class - this is not parametrised and is intended for
    // static and free functions.
    class S : public Base {
        using Func = Return(*)(Arg1);
     private:
        Func _func;

     public:
        explicit S(Func pFunc) : _func(pFunc) { }

        // Invoke the function throught the pointer-to-member.
        Return operator()(Arg1 pArg1) override {
            return _func(pArg1);
        }
    };

 private:
    // Use a vector to make this similar to C# multicast events.
    std::vector<Base*> _ptrs;

 private:
    // Can't allow copying unless we modify the class to make a deep
    // copy of each of the pointers it holds. Base class would need
    // a virtual Clone() method to allow polymorphic copying.
    Event(const Event&);
    Event& operator=(const Event&);

 public:
    // Compiler seems to require this because other default constructors
    // have been made explicit.
    Event() { }

    // Clean up the garbage.
    ~Event() {
        typename std::vector<Base*>::iterator end = _ptrs.end();
        for (typename std::vector<Base*>::iterator i = _ptrs.begin();
            i != end; ++i) {
            delete (*i);
        }
    }

    // Add a new target (callee) to our list.
    Event& operator+=(Base* pPtr) {
        _ptrs.push_back(pPtr);
        return *this;
    }

    void Clear() {
        typename std::vector<Base*>::iterator end = _ptrs.end();
        for (typename std::vector<Base*>::iterator i = _ptrs.begin();
            i != end; ++i) {
            delete (*i);
        }
        _ptrs.clear();
    }

    // Call all the targets - there will be horrible undefined behaviour
    // if the callee object no longer exists. You have been warned!
    Return operator()(Arg1 pArg1) {
        // There are problems here:
        // 1. Which result should the multicast return? I say the last called item.
        // 2. We need to can't store a temporary when Return is void.
        typename std::vector<Base*>::iterator end = _ptrs.end();
        for (typename std::vector<Base*>::iterator i = _ptrs.begin();
            i != end; ++i) {
            // Probably a specialisation for Return == void would be better.
            if ((i + 1) == end)
                return (*(*i))(pArg1);
            else
                (*(*i))(pArg1);
        }
    }
};

}  // namespace CC

#endif  // SRC_TOOL_EVENT_H_
