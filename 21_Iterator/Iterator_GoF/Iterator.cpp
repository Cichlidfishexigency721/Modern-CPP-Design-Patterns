/**
 * ============================================================================
 * File: Iterator.cpp (Classic GoF Version)
 * 
 * --- DESIGN OVERVIEW:
 * This program demonstrates the classic Object-Oriented Iterator pattern.
 * We build a custom collection (a Singly Linked List of Books). The client 
 * interacts only with the 'Iterator' interface (first, next, isDone, current) 
 * without knowing how the Books are stored in memory.
 * 
 * ============================================================================
 */
/**
 * ============================================================================
 * File: Iterator.cpp (Classic GoF Version)
 * 
 * --- DESIGN OVERVIEW:
 * This program demonstrates the classic Object-Oriented Iterator pattern.
 * We build a custom collection (a Singly Linked List of Books). The client 
 * interacts only with the 'Iterator' interface (first, next, isDone, current) 
 * without knowing how the Books are stored in memory.
 * 
 * --- MULTIPLE TRAVERSALS:
 * Because iterators are separate objects (not a cursor inside the collection), 
 * we can instantiate multiple iterators to traverse the same collection 
 * simultaneously at different speeds or starting points.
 *
 * --- CLONING CAPABILITY:
 * To match the efficiency of modern C++ iterators, this implementation 
 * includes a 'clone()' method. This allows creating a new iterator at 
 * the exact same position as an existing one, facilitating efficient 
 * nested traversals.
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <memory>
#include <unordered_set>
#include <vector>

//--------------------------------------------------------- Domain Object:
class Book
{
private:
   std::string title_;
   std::string author_;

public:
   Book(std::string title, std::string author) 
      : title_{std::move(title)}, author_{std::move(author)} { }

   std::string getTitle()  const { return title_; }
   std::string getAuthor() const { return author_; }
};

//--------------------------------------------------------- Iterator Interface:
template <typename T>
class Iterator
{
public:
   virtual ~Iterator() = default;
   virtual void first() = 0;
   virtual void next() = 0;
   virtual bool isDone() const = 0;
   virtual T currentItem() const = 0;

   // Prototype-like method to duplicate the iterator state
   virtual std::unique_ptr<Iterator<T>> clone() const = 0;
};

//--------------------------------------------------------- Aggregate Interface:
template <typename T>
class Aggregate
{
public:
   virtual ~Aggregate() = default;
   virtual std::unique_ptr<Iterator<T>> createIterator() const = 0;
};

//--------------------------------------------------------- Internal Node:
struct Node
{
   Book book_;
   std::unique_ptr<Node> next;

   explicit Node(Book book) : book_{std::move(book)}, next{nullptr} { }
};

//--------------------------------------------------------- Concrete Aggregate:
class BookCollection : public Aggregate<Book>
{
private:
   std::unique_ptr<Node> head_;
   Node* tail_{nullptr}; 

public:
   void addBook(const std::string& title, const std::string& author)
   {
      auto newNode = std::make_unique<Node>(Book{title, author});
      Node* current = newNode.get();

      if (!head_) head_ = std::move(newNode);
      else        tail_->next = std::move(newNode);
      
      tail_ = current;
   }

   const Node* getHead() const { return head_.get(); }

   std::unique_ptr<Iterator<Book>> createIterator() const override;
};

//--------------------------------------------------------- Concrete Iterator:
class BookIterator : public Iterator<Book>
{
private:
   const BookCollection& collection_;
   const Node* current_;

public:
   explicit BookIterator(const BookCollection& collection) 
      : collection_{collection}, current_{collection.getHead()} { }

   // Internal constructor for cloning
   BookIterator(const BookCollection& col, const Node* curr) 
      : collection_{col}, current_{curr} { }

   void first() override { current_ = collection_.getHead(); }

   void next() override
   {
      if (current_) current_ = current_->next.get();
   }

   bool isDone() const override { return current_ == nullptr; }

   Book currentItem() const override
   {
      if (isDone()) throw std::out_of_range("Iterator is out of bounds");
      return current_->book_;
   }

   std::unique_ptr<Iterator<Book>> clone() const override
   {
      return std::make_unique<BookIterator>(collection_, current_);
   }
};

std::unique_ptr<Iterator<Book>> BookCollection::createIterator() const
{
   return std::make_unique<BookIterator>(*this);
}

//--------------------------------------------------------- Main Simulation:
int main()
{
   std::cout << "=== ITERATOR PATTERN (CLASSIC GOF) ===\n" << std::endl;

   BookCollection library;
   library.addBook("The C++ Programming Language", "Bjarne Stroustrup");
   library.addBook("Design Patterns", "Gang of Four");
   library.addBook("Clean Code", "Robert C. Martin");
   library.addBook("The Pragmatic Programmer", "Robert C. Martin");
   library.addBook("Effective C++", "Scott Meyers");
   library.addBook("Clean Agile: Back to Basics", "Robert C. Martin");
   library.addBook("Effective Modern C++", "Scott Meyers");

   // --- Test 1: Standard Traversal ---
   std::cout << "--- Library Inventory ---\n";
   auto iterator = library.createIterator();
   
   for (iterator->first(); !iterator->isDone(); iterator->next())
   {
      Book book = iterator->currentItem();
      std::cout << " - " << book.getTitle() << " (by " << book.getAuthor() << ")\n";
   }

   // --- Test 2: Multiple Traversals (Finding duplicates) ---
   // We will use two independent iterators to find books by the same author.
   std::cout << "\n--- Finding multiple books by the same author ---\n";

   std::unordered_set<std::string> processedAuthors;
   auto outerIt = library.createIterator();

   for (outerIt->first(); !outerIt->isDone(); outerIt->next())
   {
      const Book& currentBook = outerIt->currentItem();

      if (!processedAuthors.contains(currentBook.getAuthor()))
      {
         std::vector<std::string> bookTitlesOfSameAuthor;

         processedAuthors.insert(currentBook.getAuthor());
         bookTitlesOfSameAuthor.push_back(currentBook.getTitle());

         // Use cloning to start the inner iterator at the same position
         auto innerIt = outerIt->clone();
         innerIt->next(); // Move one step ahead

         while (!innerIt->isDone())
         {
            const Book& compareBook = innerIt->currentItem();
            if (currentBook.getAuthor() == compareBook.getAuthor())
               bookTitlesOfSameAuthor.push_back(compareBook.getTitle());
            innerIt->next();
         }

         if (bookTitlesOfSameAuthor.size() > 1)
         {
            std::cout << "Several books found by " << currentBook.getAuthor() << ":\n";
            for (const auto& title : bookTitlesOfSameAuthor)
               std::cout << " - " << title << std::endl;
            std::cout << std::endl;
         }
      } // if
   } // for

   std::cout << "\n=== SIMULATION COMPLETED ===\n";
}

//================================================================================ END
