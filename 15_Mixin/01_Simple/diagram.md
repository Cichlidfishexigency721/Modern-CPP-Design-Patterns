# Mixin Pattern (Simple)

```mermaid
classDiagram
   class Basic_Entity {
      -string name_
      +print_name()
   }

   class Laser {
      +laser_fire()
      +laser_set_intensity(int)
   }

   class Walk {
      +walk()
      +walk_set_speed(int)
   }

   class Gun {
      +gun_fire()
      +gun_set_bullets(int)
   }

   class Fly {
      +fly()
      +fly_load_fuel(int)
   }

   class Entity~Mixins~ {
      +Entity(string)
   }

   class Client {
      +main()
   }

   %% Specific Entities defined by type aliases in the code
   class Dragon { Entity~Fly, Laser~ }
   class Elephant { <<Entity~Walk, Gun~>> }
   class Airplane { <<Entity~Fly, Laser, Gun~>> }

   %% Multiple Inheritance (Horizontal Composition)
   %% Inheritance arrows do not use multiplicity numbers
   Basic_Entity <|-- Entity~Mixins~
   Laser <|-- Entity~Mixins~
   Walk <|-- Entity~Mixins~
   Gun <|-- Entity~Mixins~
   Fly <|-- Entity~Mixins~

   %% Relationships for specific types
   Entity~Mixins~ <|-- Dragon
   Entity~Mixins~ <|-- Elephant
   Entity~Mixins~ <|-- Airplane

   %% Dependency - No numbers
   Client ..> Entity~Mixins~
```

### Design Note:
In the Simple Mixin version, the 'Entity' class provides a way to combine
independent features (Mixins) at compile-time. The final objects (Dragon,
Elephant, Airplane) are flat structures that contain all the methods and data
members of their respective base Mixins simultaneously.