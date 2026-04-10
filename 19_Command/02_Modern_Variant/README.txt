# COMMAND PATTERN: MODERN VARIANT (C++17)

## Overview
This version replaces class inheritance with 'std::variant' and 'std::visit'. 
Commands are no longer classes, but simple "Data Labels".

## Key Features
- **Non-Intrusive:** Commands are plain structs. They do not need to inherit 
  from any base class.
- **Value Semantics:** Commands are stored by value in the queue, eliminating 
  the need for 'std::unique_ptr' and heap allocations.
- **Centralized Logic:** The 'CommandExecutor' acts as a Visitor, gathering 
  all execution logic in one place.

## Why use this version?
Use this approach for high-performance systems where you want to avoid the 
overhead of virtual functions and memory fragmentation. It provides 
"Static Safety", as the compiler ensures all commands are handled by the 
executor.

---
# Command Pattern (Modern Variant)

```mermaid
classDiagram
   class CowAction {
      <<struct>>
   }
   class DogAction {
      <<struct>>
   }
   class CarAction {
      <<struct>>
   }

   class Command {
      <<variant>>
   }

   class Cow {
      +moo()
   }

   class Dog {
      +bark()
   }

   class Car {
      +turnOn()
      +turnOff()
      +rev()
   }

   class CommandExecutor {
      -Cow& cow
      -Dog& dog
      -Car& car
      +operator()(CowAction)
      +operator()(DogAction)
      +operator()(CarAction)
   }

   class Client {
      +main()
   }

   %% The Variant is composed of several data types
   %% We use dependency here as there is no inheritance
   Command ..> CowAction
   Command ..> DogAction
   Command ..> CarAction

   %% The Executor (Visitor) holds references to the Receivers
   %% Aggregation (o--) - Multiplicity "1" at the end
   CommandExecutor o-- "1" Cow
   CommandExecutor o-- "1" Dog
   CommandExecutor o-- "1" Car

   %% The Client manages the collection of commands by value
   %% Composition (Has_a) - Multiplicity "n" at the end
   Client *-- "n" Command : queue_

   %% The Client uses the Executor to process the variant
   Client ..> CommandExecutor : via std::visit
```

### Design Note:
In this modern approach, the 'Command' is a type-safe union (std::variant) of
plain structs. There is no base class and no virtual methods. The
'CommandExecutor' gathers all the logic that was previously scattered in command
classes. This ensures 'Value Semantics' (commands are stored directly in the
vector) and 'Static Safety' (the compiler verifies all actions are handled
during visitation).