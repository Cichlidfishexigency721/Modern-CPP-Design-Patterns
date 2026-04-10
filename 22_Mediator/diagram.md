# Mediator Pattern

```mermaid
classDiagram
   class Mediator {
      <<interface>>
      +changed(Colleague*)*
   }

   class Colleague {
      <<abstract>>
      #Mediator* mediator_
      #notify()
   }

   class Double {
      -double val_
      +setVal(double)
      +getVal() double
   }

   class Integer {
      -int val_
      +setVal(int)
      +getVal() int
   }

   class Equation {
      -Double* a_
      -Double* b_
      -Integer* c_
      -Integer* d_
      -bool doInv_
      -bool doMul_
      +setA(Double*)
      +setB(Double*)
      +setC(Integer*)
      +setD(Integer*)
      +evaluate() double
   }

   class Client {
      +main()
   }

   %% Inheritance (Is_a) - No numbers
   Mediator <|-- Equation
   Colleague <|-- Double
   Colleague <|-- Integer

   %% Bidirectional Relationship
   %% Composition (Has_a) - Multiplicity only at the end
   Colleague *-- "1" Mediator : mediator_
   Equation *-- "1" Double : a_
   Equation *-- "1" Double : b_
   Equation *-- "1" Integer : c_
   Equation *-- "1" Integer : d_

   %% Dependency - No numbers
   Client ..> Equation
   Client ..> Double
   Client ..> Integer
```

### Design Note:
In this implementation, the 'Equation' (Mediator) acts as a central coordinator
for the calculation (1/a) * (b+c) + d. Instead of Colleagues interacting with
each other, they notify the Mediator when their values change. The Mediator then
decides which parts of the calculation are "dirty" and need to be recomputed,
effectively managing an internal cache of the equation's steps.
