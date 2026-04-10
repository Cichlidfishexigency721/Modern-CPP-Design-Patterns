# Observer Pattern (CRTP with Smart Pointers)

```mermaid
classDiagram
   class Observer~ConcreteObservable~
   {
      <<interface>>
      +update(ConcreteObservable&)*
   }

   class Observable~ConcreteObservable~
   {
      -vector~weak_ptr~Observer~~ observers_
      +attach(shared_ptr~Observer~&)
      +detach(shared_ptr~Observer~&)
      #notify()
   }

   class Number
   {
      -int val_
      +setVal(int)
      +getVal() int
   }

   class DivObserver
   {
      -int div_
      +update(Number&)
   }

   class ModObserver
   {
      -int div_
      +update(Number&)
   }

   class Client
   {
      +main()
   }

   %% Inheritance (Is_a)
   Observable~Number~ <|-- Number
   Observer~Number~ <|-- DivObserver
   Observer~Number~ <|-- ModObserver

   %% Composition (Has_a) - Multiplicity "n" at the end
   Observable~ConcreteObservable~ *-- "n" Observer~ConcreteObservable~ : weak_ptr collection

   %% Dependency
   Client ..> Number
   Client ..> Observer~Number~ : owns via shared_ptr
```

### Design Note:
This version combines the performance of CRTP with the safety of Modern C++
memory management. The 'Observable' uses a collection of 'std::weak_ptr' to
track its observers without claiming ownership. This prevents circular
references and memory leaks. When 'notify()' is called, the system temporarily
upgrades the weak pointers to ensure the observers are still alive before
calling 'update(Number&)'.
