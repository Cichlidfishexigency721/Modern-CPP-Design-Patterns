# Mediator Pattern

```mermaid
classDiagram
   class Mediator {
      <<interface>>
      +changed(Colleague*)*
   }

   class Colleague {
      <<abstract>>
      #Mediator* mediator_*
      #notify()*
   }

   class Double {
      -double val_
      +setVal(double) void
      +getVal() double
   }

   class Integer {
      -int val_
      +setVal(int) void
      +getVal() int
   }

   class Expression {
      -Double* a_
      -Double* b_
      -Integer* c_
      -Integer* d_
      -bool doInv_
      -bool doMul_
      -bool doAd1_
      -bool doAd2_
      -double invVal_
      -double mulVal_
      -double ad1Val_
      -double ad2Val_
      +setA(Double*)
      +setB(Double*)
      +setC(Integer*)
      +setD(Integer*)
      +evaluate() double
      +changed(Colleague*)
   }

   class Client {
      +main()
   }

   %% Inheritance (Is_a) - No numbers
   Mediator <|.. Expression
   Colleague <|.. Double
   Colleague <|.. Integer

   %% Bidirectional Relationship
   %% Composition (Has_a) - Multiplicity only at the end
   Colleague *-- Mediator : mediator_
   Expression *-- Double : a_
   Expression *-- Double : b_
   Expression *-- Integer : c_
   Expression *-- Integer : d_

   %% Dependency - No numbers
   Client ..> Expression
```

### Design Note:
In this implementation, the 'Expression' (Mediator) acts as a central coordinator
for the calculation (1/a) * (b+c) + d. Instead of Colleagues interacting with
each other, they notify the Mediator when their values change. The Mediator then
decides which parts of the calculation are "dirty" and need to be recomputed,
effectively managing an internal cache of the equation's steps.
