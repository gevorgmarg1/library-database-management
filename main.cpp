#include <iostream>
#include <string>
using namespace std;

// A function to swap the values of two given variables
void swap(int& a, int& b)
{
    int temp = b;
    b = a;
    a = temp;
}

// A function to partition the array for quick sort
int partition(int arr[], int start, int end)
{
    //Set the last element as the pivot
    int pivot  = arr[end];
    int pIndex = start;

    //Run through the array and sort based on the pivot
    for(int i = start; i<end;i++)
    {
        if(arr[i] <= pivot)
        {
            swap(arr[i], arr[pIndex]);
            pIndex++;
        }
    }
    swap(arr[pIndex], arr[end]);
    return pIndex;
}

// Recursive Funciton to quick sort the given array
void quickSort(int arr[], int start, int end)
{
    // If there are more than one element in the array
    if(start<end)
    {
        //Set the new index based on the last partition
        int pIndex = partition(arr, start, end);
        //Sort the left and right sides of the pivot in the array
        quickSort(arr, start, pIndex-1);
        quickSort(arr, pIndex+1, end);
    }
}

// Define a struct to represent a book
struct Book {
    int id;                // Unique identifier for the book
    int num_copies;        // Number of copies available
    int year;              // Year of publication
    int num_pages;         // Number of pages in the book
    string title;          // Title of the book
    string author;         // Name of the book's author
    long isbn;             // ISBN number of the book
    float rating;          // Rating of the book
    Book* next;            // Pointer to the next book in the linked list

    // Constructor to initialize the book attributes
    Book(int i, string t, string a, long is, int c, int y, float r, int p) {
        id = i;
        title = t;
        author = a;
        isbn = is;
        num_copies = c;
        year = y;
        rating = r;
        num_pages = p;
        next = nullptr;    // Initialize the next pointer to nullptr
    }
};

// Define a class to represent a library
class Library {
private:
    Book* head;   // Pointer to the first book in the linked list
    int id;       // Identifier for the library

public:
    // Constructor to initialize the library
    Library() {
        head = nullptr;   // Initialize the head pointer to nullptr
        id = 0;           // Initialize the library id to 0
    }

    // Function to insert a new book into the library
    void insert(string t, string a, long is, int c, int y, float r, int p) {
        id += 1;   // Increment the library id
        Book* book = new Book(id, t, a, is, c, y, r, p);   // Create a new book object

        if (head == nullptr) {
            // If the library is empty, set the new book as the head
            head = book;
        } else {
            Book* temp = head;
            while (temp->next != NULL) {
                // Traverse the linked list to find the last book
                temp = temp->next;
            }
            // Set the next pointer of the last book to the new book
            temp->next = book;
        }
    }
    

    //Printing the whole information of each book
    void printList() 
    {
        Book* temp = head;
        while(temp != NULL)
        {
            cout<<"ID: "<<temp->id<<" - "<<temp->title<<" by "<<temp->author<<", "<<temp->num_copies<<" available"<<", "<<temp->year<<", "<<temp->rating<<", "<<temp->num_pages<<endl;
            temp = temp->next;
        }
    }

    //Counting the number of books in the library
    int counterList()
    {
        Book* temp = head;
        //set the initial counter to 0
        int counter = 0;
        //run through the library
        while(temp!=NULL)
        {
            //every time found a book, increase the counter by 1
            counter++;
            temp = temp->next;
        }
        return counter;
    }

    //Sort the list based on the year of publication
    void quickSortList()
    {
        int size = counterList();
        int tempArr[size];
        Book* temp = head;
        int i = 0;
        //Run throught the list and set the years of publication in an array
        while(temp!=NULL)
        {
            tempArr[i] = temp->year;
            temp = temp->next;
            i++;
        }
        //Sort the array
        quickSort(tempArr, 0, size-1);

        //Sort the list given the sorted values of the years

        //Set initial variables for previous and temporary books
        Book* tempBook = head;
        Book* prevBook = NULL;
        Book* temphead = NULL;

        //Run throught the list to find the new head element
        while(tempBook != NULL)
        {
            //If the temporary book year is equal to the first in the array set the temporary as the new head
            if(tempBook->year == tempArr[0])
            {
                prevBook = tempBook;
                temphead = tempBook;
                break;
            }
            tempBook = tempBook->next;
        }

        //Start from the start of the list
        tempBook = head;
        //Run through the array
        for(int j = 1; j<size;j++)
        {
            tempBook = head;
            //Find the matching book to the given year
            while(tempBook != NULL)
            {
                if(tempBook->year == tempArr[j])
                {
                    //If found point the previous to the current
                    prevBook->next = tempBook;
                    //Set the previous as the temporary
                    prevBook = tempBook;
                    break;
                }
                tempBook = tempBook->next;
            }
        }
        prevBook->next = NULL;
        head = temphead;
    }
  void checkoutByTitle(const string& bookTitle) {
    Book* temp = head;

    // Traverse the linked list until reaching the end
    while (temp != nullptr) {
        // Check if the current book's title matches the input bookTitle
        if (temp->title == bookTitle) {
            // Check if there are available copies of the book
            if (temp->num_copies > 0) {
                // Decrease the number of available copies by 1
                temp->num_copies--;
                // Print a message indicating successful checkout and the remaining number of copies
                cout << "Checked out: " << temp->title << endl;
                cout << "Remaining copies: " << temp->num_copies << endl;
            }
            else {
                // Print a message indicating no copies are available for checkout
                cout << "No copies available for checkout." << endl;
            }
            // Exit the function after finding and processing the book
            return;
        }
        // Move to the next book in the linked list
        temp = temp->next;
    }

    // If the loop completes without finding the book, print a message indicating it
    cout << "Book not found." << endl;
}
    void printAuthor(const string& authorName) {
        Book* temp = head;
        // Initialize a boolean flag to track if any books are found
        bool found = false;
    
        // Traverse the linked list until reaching the end
        while (temp != nullptr) {
            // Check if the current book's author matches the input authorName
            if (temp->author == authorName) {
                // Print the details of the book
                cout << "ID: " << temp->id << " - " << temp->title << " by "
                     << temp->author << ", " << temp->num_copies << " available"
                     << ", " << temp->year << ", " << temp->rating
                     << ", " << temp->num_pages << endl;
                // Set the flag to true since at least one book is found
                found = true;
            }
            // Move to the next book in the linked list
            temp = temp->next;
        }
    
        // Check if any books were found
        if (!found) {
            // If no books were found, print a message indicating it
            cout << "No books found for the author: " << authorName << endl;
        }
    }
void searchByTitle(string bookTitle) {
        Book* temp = head;

        // Traverse the linked list until reaching the end
        while (temp != nullptr) {
            // Check if the current book's title matches the input bookTitle
            if (temp->title == bookTitle) {
                cout<<"ID: "<<temp->id<<" - "<<temp->title<<" by "<<temp->author<<", "<<temp->num_copies<<" available"<<", "<<temp->year<<", "<<temp->rating<<", "<<temp->num_pages<<endl;
                return;
            }
            // Move to the next book in the linked list
            temp = temp->next;
        }

        cout<<"Book not found!"<<endl;
    }
    float calculateAverageRating() {
        float sum = 0; // Variable to store the sum of ratings
        int count = 0; // Variable to store the count of books
        Book* temp = head; // Start from the head of the linkedlist

        while (temp != NULL) {
            sum += temp->rating; // Adds the rating of the current book to the sum
            count++; // INcrement the count of the books
            temp = temp->next; // Move to the next book in the linkedlist
        }

        if (count > 0) { // Check if there are any books in the library
            return sum / count; // Calculate the average rating
        }
        else {
            return 0; // Returns 0 if there are no books
        }
    }
};



int main() {
    //Initialize the library
    Library library;

    //Insert Books
    library.insert("Hey", "Harper Lee", 9780061120084, 10, 1960, 4.3, 336);
    library.insert("1984", "George Orwell", 9780451524935, 7, 1949, 4.2, 328);
    library.insert("Pride and Prejudice", "Jane Austen", 9780141439518, 15, 1813, 4.5, 432);
    library.insert("The Great Gatsby", "F. Scott Fitzgerald", 9780743273565, 12, 1925, 4.0, 180);
    library.insert("To the Lighthouse", "Virginia Woolf", 9780156907392, 8, 1927, 4.1, 209);
    // library.insert("The Catcher in the Rye", "J.D. Salinger", 9780316769488, 6, 1951, 4.3, 277);
    // library.insert("Moby-Dick", "Herman Melville", 9781853260087, 9, 1851, 4.2, 720);
    // library.insert("Brave New World", "Aldous Huxley", 9780060850524, 11, 1932, 4.0, 288);
    // library.insert("The Lord of the Rings", "J.R.R. Tolkien", 9780345339706, 20, 1954, 4.5, 1178);
    // library.insert("The Chronicles of Narnia", "C.S. Lewis", 9780064404990, 14, 1950, 4.4, 767);
    // library.insert("Jane Eyre", "Charlotte Bronte", 9780141441146, 9, 1847, 4.2, 624);
    // library.insert("Harry Potter and the Sorcerer's Stone", "J.K. Rowling", 9780590353427, 18, 1997, 4.7, 320);
    // library.insert("The Hobbit", "J.R.R. Tolkien", 9780345339683, 16, 1937, 4.6, 366);
    // library.insert("The Alchemist", "Paulo Coelho", 9780062315007, 13, 1988, 4.2, 197);
    // library.insert("The Little Prince", "Antoine de Saint-Exupery", 9780156012195, 7, 1943, 4.4, 96);
    // library.insert("Gone with the Wind", "Margaret Mitchell", 9780446675536, 10, 1936, 4.3, 1037);
    // library.insert("The Kite Runner", "Khaled Hosseini", 9781594631931, 11, 2003, 4.3, 372);
    // library.insert("The Book Thief", "Markus Zusak", 9780375842207, 9, 2005, 4.4, 576);
    // library.insert("Crime and Punishment", "Fyodor Dostoevsky", 9780486415871, 6, 1866, 4.2, 430);

    //Basic interface for using the library functions
    while(true)
    {
        int command;
        cout<<"Type \n 1 - Insert a book \n 2 - Checkout a book \n 3 - Sort the library \n 4 - Search in the library by title \n 5 - Search in the library by author \n 6 - All of the books \n 7 - Average rating of the books \n 8 - The number of books in the library";
        cout<<endl;
        cin >> command;

        if(command == 1)
        {
            int num_copies, year, num_pages;
            string title, author;
            long isbn;
            float rating;
            cout<<"Type the title of the book!"<<endl;
            cin >> title;
            cout<<"Type the name of the author!"<<endl;
            cin >> author;
            cout<<"Type the year of publication!"<<endl;
            cin >> year;
            cout<<"Type the number of copies!"<<endl;
            cin >> num_copies;
            cout<<"Type the rating!"<<endl;
            cin >> rating;
            cout<<"Type the ISBN number!"<<endl;
            cin >> isbn;
            cout<<"Type the number of pages!"<<endl;
            cin >> num_pages;

            library.insert(title, author, isbn, num_copies, year, rating, num_pages);
            cout<<"Your book has been inserted!"<<endl;
        }
        else if(command == 2)
        {
            string title;
            cout<<"Type the title of the book you want to check out!"<<endl;
            cin >> title;
            library.checkoutByTitle(title);
        }
        else if(command == 3)
        {
            library.quickSortList();
            cout<<"The library has been sorted"<<endl;
        }
        else if(command == 4)
        {
            string title;
            cout<<"Type the title of the book you are looking for!"<<endl;
            cin >> title;
            library.searchByTitle(title);
        }
        else if(command == 5)
        {
            string author;
            cout<<"Type the name of the author you are looking for!"<<endl;
            cin >> author;
            library.printAuthor(author);
        }
        else if(command == 6)
        {
            library.printList();
        }
        else if(command == 7)
        {
            cout<<"The average rating of the books in the library is: "<<library.calculateAverageRating()<<endl;
        }
        else if(command == 8)
        {
            cout<<"There are "<<library.counterList()<<" books in the library"<<endl;
        }
        cout<<"---------------------"<<endl;
    }
}