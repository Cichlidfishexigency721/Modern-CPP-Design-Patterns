# Iterator Pattern (GoF Version)

```mermaid
classDiagram
    class Book {
        -string title_
        -string author_
        +getTitle() string
        +getAuthor() string
    }

    class Iterator~Book~ {
        <<interface>>
        +first()*
        +next()*
        +isDone()* bool
        +currentItem()* Book
        +clone()* unique_ptr~Iterator~
    }

    class Node {
        +Book book_
        +unique_ptr~Node~ next
    }

    class BookCollection {
        -unique_ptr~Node~ head_
        -Node* tail_
        +addBook(string title, string author)
        +createIterator() unique_ptr~Iterator~
    }

    class BookIterator {
        -BookCollection& collection_
        -Node* current_
        +first()
        +next()
        +isDone() bool
        +currentItem() Book
        +clone() unique_ptr~Iterator~
    }

    class Client {
        +main()
    }

    Iterator~Book~ <|.. BookIterator

    BookCollection *-- "n" Node : head_
    BookCollection ..> Node : tail_
    Node *-- Book : book_
    Node *-- Node : next

    BookIterator ..> BookCollection : collection_
    BookIterator ..> Node : current_
    
    Client ..> BookCollection
    Client ..> Iterator
```

### Design Note:
This diagram illustrates the classic decoupled approach. The 'BookCollection'
(Aggregate) is responsible for storing the data in a linked-list of 'Nodes',
while the 'BookIterator' manages the traversal state. By providing a 'clone()'
method, we allow multiple independent iterators to exist and duplicate their
positions efficiently, as shown in the author's search simulation.
