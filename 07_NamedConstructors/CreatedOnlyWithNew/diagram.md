# Named Constructors (Force Heap Allocation)

```mermaid
classDiagram
   class Fred {
      -int i_
      -Fred()
      -Fred(int)
      +create()` unique_ptr~Fred~
      +create(int)` unique_ptr~Fred~
      +talk()
   }

   class Client {
      +main()
   }

   %% The static methods create and return a unique_ptr to a Fred object
   Fred ..> "1" Fred : creates (heap)
   Client ..> Fred
```
