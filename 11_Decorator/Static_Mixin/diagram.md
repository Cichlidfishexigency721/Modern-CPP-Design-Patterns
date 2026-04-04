# Decorator Pattern (Static / Mixin Inheritance)

```mermaid
classDiagram
   class Coffee {
      +getDescription() string
      +getCost() double
   }

   class Milk~T~ {
      +getDescription() string
      +getCost() double
   }

   class Sugar~T~ {
      +getDescription() string
      +getCost() double
   }

   class Vanilla~T~ {
      +getDescription() string
      +getCost() double
   }

   %% In Static Decorator, the decorator inherits from the template parameter T.
   %% There is NO composition (*--) and NO multiplicity numbers.
   
   T <|-- Milk~T~ : "is a" T
   T <|-- Sugar~T~ : "is a" T
   T <|-- Vanilla~T~ : "is a" T

   note for Milk~T~ "The template argument T \nbecomes the base class"
```

### Design Note:
In this version, the 'is a' relationship is established at compile-time. There
is no 'has a' relationship because the decorator does not hold a pointer to
another object; it literally inherits the functionality of the class passed as a
template parameter.