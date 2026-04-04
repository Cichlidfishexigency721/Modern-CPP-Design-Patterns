# Chain of Responsibility Pattern

```mermaid
classDiagram
   class IHandler {
      <<interface>>
      #unique_ptr~IHandler~ next_
      +setNext(unique_ptr~IHandler~)
      +handle(int)
   }

   class Handler {
      -int id_
      -string name_
      +handle(int)
   }

   class Chain {
      -unique_ptr~IHandler~ head_
      -IHandler* tail_
      +add(unique_ptr~IHandler~) Chain&
      +execute(int)
   }

   class Client {
      +main()
   }

   %% Inheritance (Is_a) - No numbers
   IHandler <|-- Handler

   %% Recursive Composition: each handler owns the next one
   %% Composition (Has_a) - Multiplicity "1" only at the end
   IHandler *-- "10" IHandler : next_

   %% The Chain manager owns the head of the list
   Chain *-- "1" IHandler : head_

   %% Client interactions
   Client ..> Chain
```

### Design Note:
This diagram illustrates a linked-list structure. The 'Chain' class acts as a
manager that simplifies the linking process (the builder). Each 'Handler' has a
composition relationship with the next 'IHandler' in the sequence. If a request
cannot be processed by the current node, it is delegated via the 'next_' pointer
until it reaches the end of the chain.
