/**
 * ============================================================================
 * File: Iterator.cpp (Modern STL / Idiomatic C++ Version)
 * 
 * --- DESIGN OVERVIEW:
 * In modern C++, the Iterator pattern is built into the language itself.
 * Instead of using virtual interfaces (first, next, isDone), we use 
 * Operator Overloading (*, ++, !=) and Duck Typing (begin, end).
 * 
 * --- THE "RANGE-BASED FOR" MAGIC:
 * Because our BookCollection provides begin() and end(), and our BookIterator 
 * implements the required operators, we can use the elegant C++11 loop:
 *    for (const auto& book : library) { ... }
 * 
 * This approach has ZERO virtual overhead and provides maximum performance.
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

//--------------------------------------------------------- Internal Node:
struct Node
{
   Book book_;
   std::unique_ptr<Node> next;

   explicit Node(Book book) : book_{std::move(book)}, next{nullptr} { }
};

//--------------------------------------------------------- STL-Style Iterator:
// We don't inherit from any interface. We just provide the expected operators.
class BookIterator
{
private:
   const Node* current_;

public:
   // The iterator acts as a lightweight pointer wrapper
   explicit BookIterator(const Node* node) : current_{node} { }

   // 1. Dereference operator (replaces currentItem())
   const Book& operator*() const
   {
      return current_->book_;
   }

   // 2. Pre-increment operator (replaces next())
   BookIterator& operator++()
   {
      if (current_) current_ = current_->next.get();
      return *this;
   }

   // 3. Inequality operator (replaces !isDone())
   bool operator!=(const BookIterator& other) const
   {
      return current_ != other.current_;
   }
};

//--------------------------------------------------------- Concrete Aggregate:
class BookCollection
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

   // --- The magic methods for C++ Range-based for loops ---
   
   BookIterator begin() const
   {
      return BookIterator{head_.get()};
   }

   BookIterator end() const
   {
      return BookIterator{nullptr}; // The "done" state is a null pointer
   }
};

//--------------------------------------------------------- Main Simulation:
int main()
{
   std::cout << "=== ITERATOR PATTERN (IDIOMATIC C++ / STL) ===\n" << std::endl;

   BookCollection library;
   library.addBook("The C++ Programming Language", "Bjarne Stroustrup");
   library.addBook("Design Patterns", "Gang of Four");
   library.addBook("Clean Code", "Robert C. Martin");
   library.addBook("The Pragmatic Programmer", "Robert C. Martin");
   library.addBook("Effective C++", "Scott Meyers");
   library.addBook("Clean Agile: Back to Basics", "Robert C. Martin");
   library.addBook("Effective Modern C++", "Scott Meyers");

   // --- Test 1: Standard Traversal (The modern way) ---
   std::cout << "--- Library Inventory (Range-based for loop) ---\n";
   
   // This single line replaces: for (iterator->first(); !iterator->isDone(); iterator->next())
   //                            {
   //                               Book book = iterator->currentItem();
   for (const auto& book : library)
      std::cout << " - " << book.getTitle() << " (by " << book.getAuthor() << ")\n";

   // --- Test 2: Multiple Traversals (Finding duplicates) ---
   // We will use two independent iterators to find books by the same author.
   std::cout << "\n--- Finding multiple books by the same author ---\n";

   std::unordered_set<std::string> processedAuthors;

   // We can still use iterators manually if we need fine-grained control
   for (auto outerIt = library.begin(); outerIt != library.end(); ++outerIt)
   {
      const Book& currentBook = *outerIt;

      if (!processedAuthors.contains(currentBook.getAuthor()))
      {
         std::vector<std::string> bookTitlesOfSameAuthor;

         processedAuthors.insert(currentBook.getAuthor());
         bookTitlesOfSameAuthor.push_back(currentBook.getTitle());
      
         // Start inner iterator one step ahead of the outer iterator
         auto innerIt = outerIt;
         ++innerIt;

         while (innerIt != library.end())
         {
            const Book& compareBook = *innerIt;
            if (currentBook.getAuthor() == compareBook.getAuthor())
               bookTitlesOfSameAuthor.push_back(compareBook.getTitle());
            ++innerIt;
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
