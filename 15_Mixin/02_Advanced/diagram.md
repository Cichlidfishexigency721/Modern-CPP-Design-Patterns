# Mixin Pattern (Advanced)

```mermaid
classDiagram
%%---------------------------------------------------------------------- Main:
   class Client {
      +main()
   }

%%---------------------------------------------------- Features (Mixin Parts):
   class Laser { +laser_fire(), +print() }
   class Walk { +walk(), +print() }
   class Gun { +gun_fire(), +print() }
   class Tank { +tank_load_fuel(), +tank_get_fuel(), +print() }
   class Fly { +fly(auto& entity), +print() }

%%--------------------------------------------------------------------- Entity:
   class Basic_Entity {
      -string name_
      +print_name()
   }

   class Entity~Mixins~ {
      +visitFeatures(Visitor)
   }

%%------------------------------------------------------------ Mixin Entities:
   class Dragon {
      Dragon~Entity~Fly Tank Laser~~
      +fly()
   }
   class Elephant {
      Elephant~Entity~Walk Gun~~
   }
   class Airplane {
      Airplane~Entity~Fly Tank Laser Gun~~
      +fly()
   }

   class PrintVisitor {
      +operator()(Mixins)
   }

%%----------------------------------------------------------- UML Composition:
   %% Multiple Inheritance (Horizontal Composition)
   %% No numbers used for inheritance
   Basic_Entity <|-- Entity~Mixins~
   Laser <|-- Entity~Mixins~
   Walk <|-- Entity~Mixins~
   Gun <|-- Entity~Mixins~
   Tank <|-- Entity~Mixins~
   Fly <|-- Entity~Mixins~

   %% Specific Entities
   Entity~Mixins~ <|-- Dragon
   Entity~Mixins~ <|-- Elephant
   Entity~Mixins~ <|-- Airplane

   %% Dependencies
   Fly ..> Tank : requires
   PrintVisitor ..> Entity~Mixins~ : visits
   Clien ..> Entity~Mixins~
```

### Design Note:
In this pattern, the 'Entity' class inherits directly from the variadic pack of
'Mixins'. This is 'Static Composition' through Multiple Inheritance. Note that
'Fly' has a dependency on 'Tank', which is resolved at compile-time when both
are mixed into the same Entity.