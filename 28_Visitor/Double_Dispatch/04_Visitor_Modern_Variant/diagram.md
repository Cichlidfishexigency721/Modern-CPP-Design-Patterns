# Visitor Pattern (Modern Variant Version)

```mermaid
classDiagram
    class Circle {
        +int id_
    }
    class Triangle {
        +int id_
    }

    class Shape {
        <<variant>>
    }

    class CollisionEngine {
        +operator()(Circle, Circle)
        +operator()(Triangle, Triangle)
        +operator()(Circle, Triangle)
        +operator()(Triangle, Circle)
        -intersect(int, int, string)
    }

    class Client {
        +main()
    }

    Shape ..> Circle
    Shape ..> Triangle

    CollisionEngine ..> Circle : processes
    CollisionEngine ..> Triangle : processes

    Client *-- "n" Shape : collection

    Client ..> CollisionEngine : via std::visit
```

### Design Note:
In this modern C++17 implementation, the Visitor pattern achieves Double
Dispatch through 'std::variant' and 'std::visit'. This approach is
non-intrusive, as 'Circle' and 'Triangle' are plain data structures that do not
require inheritance or 'accept' methods. The 'CollisionEngine' acts as the
visitor, centralizing all interaction logic. By using 'std::visit' with multiple
arguments, the system automatically handles the dispatch matrix. This version
also includes an optimization for symmetry (Circle-Triangle being handled the
same as Triangle-Circle) and improved memory locality by storing objects by
value in the collection.
