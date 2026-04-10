# Iterator Pattern (Modern STL Version)

```mermaid
classDiagram
    class Book {
        -string title_
        -string author_
        +getTitle() string
        +getAuthor() string
    }

    class Node {
        +Book book_
        +unique_ptr~Node~ next
    }

    class BookIterator {
        -Node* current_
        +operator*() Book&
        +operator++() BookIterator&
        +operator!=(BookIterator) bool
    }

    class BookCollection {
        -unique_ptr~Node~ head_
        -Node* tail_
        +addBook(string, string)
        +begin() BookIterator
        +end() BookIterator
    }

    class Client {
        +main()
    }

    %% Relationships using your symbology reference:

    BookCollection *-- "n" Node : head_
    Node *-- "1" Book : book_
    Node *-- "1" Node : next

    BookIterator ..> Node : points to

    Client ..> BookCollection : uses range-for
    Client ..> BookIterator : iterates
```

### Design Note:
In the Modern C++ (STL) version, the Iterator pattern is implemented without
inheritance. The 'BookCollection' provides 'begin()' and 'end()' methods that
return 'BookIterator' instances. The C++ compiler uses these methods and the
overloaded operators (*, ++, !=) to enable the 'Range-based for loop'
syntax. This approach follows the Zero-Overhead Principle, as all calls are
resolved at compile-time without virtual table lookups.
