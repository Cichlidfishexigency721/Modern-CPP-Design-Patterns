# Module Loader / Plugin Pattern

```mermaid
classDiagram
   class IModule {
      <<interface>>
      +processData(int)*
   }

   class Module {
      -string name_
      +processData(int)
   }

   class DynamicLibrary {
      -void* handle_
      +getSymbol(string) void*
   }

   class Client {
      +main()
   }

   %% Inheritance (Is_a) - No numbers
   IModule <|-- Module

   %% The Client owns the RAII wrapper for the library
   %% Composition (Has_a) - Multiplicity "1" at the end
   Client *-- "1" DynamicLibrary : manages library

   %% The Client owns the module instance via unique_ptr
   %% Composition (Has_a) - Multiplicity "1" at the end
   Client *-- "1" IModule : uses plugin

   %% The Client depends on the factory functions exported by the .so
   %% Dependency (..>) - No numbers
   Client --> IModule : creates via symbols
```

### Design Note:
This diagram illustrates the separation between the 'Host' (Client and
DynamicLibrary) and the 'Plugin' (Module). The Client only has a compile-time
dependency on the 'IModule' interface. The concrete 'Module' class is loaded at
runtime from the Shared Object (.so), and its lifecycle is managed through a
smart pointer with a custom deleter provided by the library's symbols.
