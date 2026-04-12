# Mixin Pattern (Advanced)

```mermaid
classDiagram
   class Basic_Entity {
      -string name_
      +print_name()
   }

   class Laser { +laser_fire(), +print() }
   class Walk { +walk(), +print() }
   class Gun { +gun_fire(), +print() }
   class Tank { +tank_load_fuel(), +tank_get_fuel(), +print() }
   class Fly { +fly(auto& entity), +print() }

   class Entity~Mixins~ {
      +visitFeatures(Visitor)
   }

   class Dragon { +fly() }
   class Airplane { +fly() }

   %% Multiple Inheritance (Horizontal Composition)
   %% No numbers used for inheritance
   Basic_Entity <|-- Entity~Mixins~
   Laser <|-- Entity~Mixins~
   Walk <|-- Entity~Mixins~
   Gun <|-- Entity~Mixins~
   Tank <|-- Entity~Mixins~
   Fly <|-- Entity~Mixins~

   %% Specific Entities
   Entity~Fly, Tank, Laser~ <|-- Dragon
   Entity~Fly, Tank, Laser, Gun~ <|-- Airplane

   %% Dependencies
   Fly ..> Tank : requires
   class PrintVisitor { +operator()(Mixins) }
   PrintVisitor ..> Entity~Mixins~ : visits
```

### Design Note:
In this pattern, the 'Entity' class inherits directly from the variadic pack of
'Mixins'. This is 'Static Composition' through Multiple Inheritance. Note that
'Fly' has a dependency on 'Tank', which is resolved at compile-time when both
are mixed into the same Entity.