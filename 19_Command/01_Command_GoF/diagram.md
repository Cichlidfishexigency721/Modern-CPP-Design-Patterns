# Command Pattern (GoF Version)

```mermaid
classDiagram
   class Command {
      <<interface>>
      +execute()*
   }

   class CowCommand {
      -Cow& receiver_
      +execute()
   }

   class DogCommand {
      -Dog& receiver_
      +execute()
   }

   class CarCommand {
      -Car& receiver_
      +execute()
   }

   class Cow {
      +moo()
   }

   class Dog {
      -string name_
      +bark()
   }

   class Car {
      -bool engineOn_
      +turnOn()
      +turnOff()
      +rev()
   }

   class CommandQueue {
      -vector~unique_ptr~Command~~ queue_
      +addCommand(unique_ptr~Command~)
      +runAll()
   }

   class Client {
      +main()
   }

   %% Inheritance (Is_a) - No numbers
   Command <|-- CowCommand
   Command <|-- DogCommand
   Command <|-- CarCommand

   %% The Invoker owns the commands
   %% Composition (Has_a) - Multiplicity "n" at the end
   CommandQueue *-- "n" Command : queue_

   %% Commands depend on their Receivers to do the work
   %% Dependency (..>) - No numbers
   CowCommand ..> Cow
   DogCommand ..> Dog
   CarCommand ..> Car

   %% Client orchestrates everything
   Client ..> CommandQueue
   Client ..> Command
   Client ..> Cow
   Client ..> Dog
   Client ..> Car
```

### Design Note:
In this traditional version, each 'Command' object acts as a bridge. It knows
which 'Receiver' method to call. The 'CommandQueue' (Invoker) remains completely
decoupled from the 'Receivers', as it only interacts with the 'Command'
interface to trigger actions.