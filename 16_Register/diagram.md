# Registry Pattern

```mermaid
classDiagram
   class Processor {
      <<interface>>
      +process(string) string*
      +getName() string*
   }

   class GrayscaleProcessor {
      +process(string) string
      +getName() string
   }

   class BlurProcessor {
      +process(string) string
      +getName() string
   }

   class Registry {
      -static registryMap_
      +registerProcessor(string, Creator)
      +create(string) shared_ptr~Processor~
   }

   class Register~ConcreteProcessor~ {
      +Register(string)
   }

   class Client {
      +main()
   }

   %% Inheritance (Is_a) - No numbers
   Processor <|.. GrayscaleProcessor
   Processor <|.. BlurProcessor

   %% The Registry manages the lifecycle of processors (Singleton/Flyweight)
   %% Composition (Has_a) - Multiplicity "n" at the end
   Registry *-- "n" Processor : manages

   %% Auto-registration mechanism
   %% Dependency (..>) - No numbers
   Register~ConcreteProcessor~ ..> Registry : registers ConcreteProcessor
   GrayscaleProcessor ..> Register~ConcreteProcessor~ : static auto-reg
   BlurProcessor ..> Register~ConcreteProcessor~ : static auto-reg

   %% Client interactions
   Client ..> Registry : look up
   Client ..> Processor : execute
```

### Design Note:
This diagram highlights the decoupled nature of the Registry. The 'Client' has
no direct link to 'GrayscaleProcessor' or 'BlurProcessor'. The 'Register' helper
facilitates a "push" registration during static initialization, populating the
Registry's internal map before the 'main' function starts.