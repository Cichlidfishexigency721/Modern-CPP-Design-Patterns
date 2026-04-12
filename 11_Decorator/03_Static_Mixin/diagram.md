# Decorator Pattern (Static / Mixin Inheritance)

```mermaid
classDiagram
   class Coffee {
      +getDescription() string
      +getCost() double
   }

   class Milk~Decoraded~ {
      +getDescription() string
      +getCost() double
   }

   class Sugar~Decoraded~ {
      +getDescription() string
      +getCost() double
   }

   class Vanilla~Decoraded~ {
      +getDescription() string
      +getCost() double
   }

   %% In Static Decorator, the decorator inherits from the template parameter Decoraded.
   %% There is NO composition (*--) and NO multiplicity numbers.
   
   Decoraded <|-- Milk~Decoraded~ : "is a" Decoraded
   Decoraded <|-- Sugar~Decoraded~ : "is a" Decoraded
   Decoraded <|-- Vanilla~Decoraded~ : "is a" Decoraded

%% Client instantiates concrete types
   Client ..> Decorated
```

### Design Note:
In this version, the 'is a' relationship is established at compile-time. There
is no 'has a' relationship because the decorator does not hold a pointer to
another object; it literally inherits the functionality of the class passed as a
template parameter.