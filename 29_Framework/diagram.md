# Framework Design Pattern

```mermaid
classDiagram
    class App {
        <<interface>>
        +start()
        +read()* bool
        +compute()
        +write()
        +result()
        +final()
    }

    class up {
        -char c_
        -ifstream fs_
        +start()
        +read()
        +write()
        +final()
    }

    class wc {
        -char c_
        -int nChar_
        -int nWord_
        -int nLine_
        +read()
        +compute()
        +result()
    }

    class FrameworkCore {
        (main entry point)
        +main()
        +createApp() App*
    }

    %% Inheritance (Is_a) - No numbers
    App <|-- up
    App <|-- wc

    %% The Framework owns the lifecycle of 1 App instance
    %% Composition (Has_a) - Multiplicity "1" at the end
    FrameworkCore *-- "1" App : manages lifecycle

    %% Dependency - No numbers
    FrameworkCore ..> App : creates via factory
```

### Design Note:
This diagram illustrates the "Hollywood Principle" (Inversion of Control). The
'FrameworkCore' (representing the 'libFramework.so' and its 'main.cpp') owns the
execution skeleton. It is responsible for creating exactly one instance of an
'App' and calling its methods in the predefined order: start -> read ->
compute/write -> result -> final. Concrete applications like 'up' and 'wc'
simply plug into this skeleton by inheriting from 'App' and providing their
specific logic, without ever controlling the main loop themselves.
