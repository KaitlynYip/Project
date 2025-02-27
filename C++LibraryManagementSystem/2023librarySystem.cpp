#include <algorithm>//include this file is to provides a set of pre-defined algorithms for working with data structures, such as sorting, searching, and modifying container elements.
#include <cctype>//include this file provides functions for working with characters and character data, such as testing for character types and converting between upper and lower case.
#include <fstream>//include this file is to provides classes for working with files, such as reading from and writing to files.
#include <iomanip>//include this file is to provides facilities for formatting input and output, such                   //as setting precision and padding.
#include <iostream>  //include tis file is to provides classes for working with input and output     
                      //streams, such as `cout` and `cin`.
#include <list>//include this file is to provides a container class for linked lists, which allows elements to be easily inserted and removed at any position.
#include <map>//include this file is to provides a container class for key-value pairs, which allows for efficient lookups and inserts.
#include <string>//include this file is to provides a class for working with strings of characters, such as concatenation, comparison, and substring extraction.
#include <variant>//include this file is to provides a class for working with variant types
#include <sstream>//include this file is to provides classes for working with input and output string streams
#include <vector>//include this file is to provides a container class for dynamic arrays


using namespace std;//for input and output


//Below is to declares different functions.
void ManageBooks();
void ManageBorrowers();
void ManageBooks();
void BorrowBooks();
void ReturnBook();
void UsefulFeatures();
void MemberList();
void initializeBorrowerIDs();


const int MAX_BOOKS = 1000;//initalize maxmuimum Book List size to 1000
const int BOOK_DETAILS = 6;//initalize Book List column to 6
int book_count = 0;//initalize book number to 0



string u[MAX_BOOKS][BOOK_DETAILS] = {};//inital 2D List for book list
list<int> removed_indexes;


const int MAX_Borrowers = 500;//initalize maxmuimum number of borrower to 500
const int Borrowers_DETAILS = 3 + 2;//initalize borrow list column to 5
int Borrowers_count = 0;//initalize borrower number to 0
int currentID = 0001;//initalize the borrower ID
//list<list<variant<string, list<string>>>> v;

string v[MAX_Borrowers][Borrowers_DETAILS] = {};//initalize the 2D list named v for borrowers

enum ArrayType { BOOKS = 1, BORROWERS = 2 };

string BookList;
string BorrowerList;

using namespace std;

int extractFields(string line, char fields[][101]) {

  int numFields = 0;

  bool inQuote = false;
  bool newWord = true;
  int count;

  for (int i = 0; i < line.length(); i++) {

    char b = line.at(i);

    if (newWord == true) {
      count = 0;
      if (b == '"') {
        inQuote = true;
      } else {
        fields[numFields][count++] = b;
      }
      newWord = false;
    } else {
      if (inQuote == false) {
        if (b != ',') {
          fields[numFields][count] = b;
          count++;
        } else {
          fields[numFields][count] = '\0';
          count = 0;
          numFields++;
          newWord = true;
          inQuote = false;
        }
      } else {
        if (b != '"') {
          fields[numFields][count] = b;
          count++;
        } else {
          if (line.at(i + 1) == '"' && line.at(i + 1) != ',') {
            fields[numFields][count++] = line.at(i + 1);
            i++;
          } else {
            fields[numFields][count] = '\0';
            count = 0;
            numFields++;
            newWord = true;
            inQuote = false;
            i++;
          }
        }
      }
    }
  }

  fields[numFields][count] = '\0';
  numFields++;
  return numFields;
}

void readCSV(string filename, int arrayType) {      //to read the CSV file and and insert the data to the following columns
  fstream inFile;
  string line;
  char fields[10][101] = {};
  int numFields;
  int countRecords = 0;

  inFile.open(filename);
  if (!inFile.is_open()) {
    cout << "Cannot open file \"" << filename << "\"\n";
    return;
  }

  while (getline(inFile, line, '\n')) {
    numFields = extractFields(line, fields);

    if (arrayType == BOOKS) {
      for (int i = 0; i < numFields; i++) {
        u[countRecords][i] = fields[i];
      }
      u[countRecords][5] = "Yes"; // Add "available" to u[i][5] for each row
      book_count++;
    } else if (arrayType == BORROWERS) {
      for (int i = 0; i < numFields; i++) {
        v[countRecords][i] = fields[i];
      }
      if (v[countRecords][3].empty()) {
  stringstream ss;
  ss << "HKCC" << setw(4) << setfill('0') << currentID;
  v[countRecords][3] = ss.str();
  currentID++;
}
Borrowers_count++;
    }

    countRecords++;
  }

  cout << countRecords << " Record(s) imported.\n";
  inFile.close();
}



char prog_choice;    
char confirm;
void Back() {      // to back to the main menu

  string mainMenu = "\n\n\n*** Library Management System ***\n"
                    "[1] Manage books\n"
                    "[2] Manage borrowers\n"
                    "[3] Borrow book(s)\n"
                    "[4] Return book(s)\n"
                    "[5] Useful feature(s) added\n"
                    "[6] Member List\n"
                    "[7] Exit\n"
                    "*********************************\n"
                    "Option (1 - 7): ";

  cout << mainMenu;

  do {

    cin >> prog_choice;
    cout << "\n\n";

    cout << "Are you sure you want to choose option " << prog_choice
         << " ? (y/n) ";
    cin >> confirm;
    cout << "\n\n";

    switch (prog_choice) {
    case '1':
      ManageBooks();
      break;
    case '2':
      ManageBorrowers();
      break;
    case '3':
      BorrowBooks();
      break;
    case '4':
      ReturnBook();
      break;
    case '5':
      UsefulFeatures();
      break;
    case '6':
      MemberList();
      break;
    case '7':
      break;
    default:
      cout << "No such option " << prog_choice << endl;
      cout << mainMenu;
      break;
    }
  } while (prog_choice != '7' || (confirm != 'y' && confirm != 'Y'));
}


////////////////////////////////-- R1 --///////////////////////////////////


void R1Display() {
  cout << "ID" << setw(20) << "Book Details " << setw(30) << "Availability"
       << endl;

  map<string, list<string>> bookDetails;

  for (int i = 0; i < 1000; i++) {                //to prevent not show the empty row, check whether the column is emapty. 
    if (!u[i][0].empty()) {
      bookDetails[u[i][1]] = {u[i][0], u[i][2], u[i][3], u[i][4], u[i][5]};
    }
  }

  for (const auto &book : bookDetails) {
    auto bookInfo = book.second.begin();
    cout << *bookInfo++ << setw(20)  << book.first << " (" << *bookInfo++ << ")"
         << "\n"
         << setw(20) << *bookInfo++ << "\n"
         << setw(20) << *bookInfo++ << "\n"
         << setw(20) << *bookInfo++ << endl;
  }
}      //a function that display the booklist with the format "ID","Book Details","Availabilty" from library system 

list<string> tokenizeWords(const string &input) {
  list<string> words;
  stringstream ss(input);
  string word;

  while (getline(ss, word, ' ')) {
    if (!word.empty()) {
      words.push_back(word);
    }
  }

  return words;
}
bool containsAnyKeywords(const string &bookDetails,
                         const list<string> &keywords) {
  string processedTitle = bookDetails;
  transform(processedTitle.begin(), processedTitle.end(),
            processedTitle.begin(), ::tolower);
  list<string> words = tokenizeWords(processedTitle);

  for (const auto &keyword : keywords) {
    for (const auto &word : words) {
      if (word.find(keyword) != string::npos) {
        return true;
      }
    }
  }

  return false;
}
bool containsExactPhrase(const string &input, const string &phrase) {    //
  size_t pos = input.find(phrase);
  return pos != string::npos;
}

bool containsAnyKeywordsBorrower(const string &borrowersDetails,      
                                 const list<string> &keywords) {
  string processedTitle = borrowersDetails;
  transform(processedTitle.begin(), processedTitle.end(),
            processedTitle.begin(), ::tolower);
  list<string> words = tokenizeWords(processedTitle);

  for (const auto &keyword : keywords) {
    for (const auto &word : words) {
      if (word.find(keyword) != string::npos) {
        return true;
      }
    }
  }

  return false;
}
bool containsExactPhraseBorrower(const string &input, const string &phrase) {
  size_t pos = input.find(phrase);
  return pos != string::npos;
}

void R1SearchBook() {
  string search;
  cout << "Search: ";
  cin.ignore();
  getline(cin, search);

  bool exactPhraseSearch = false;
  string exactPhrase;
  if (search.front() == '"' && search.back() == '"') {
    exactPhraseSearch = true;
    exactPhrase = search.substr(1, search.length() - 2);
  } else {
    transform(search.begin(), search.end(), search.begin(), ::tolower);
  }

  list<string> keywords = tokenizeWords(search);

  int matches = 0;
  for (int i = 0; i < 1000; i++) {
    if (!u[i][0].empty()) {
      string id = u[i][0];
      string bookDetails = u[i][1];

      if (exactPhraseSearch) {
        if (containsExactPhrase(bookDetails, exactPhrase) ||
            id == exactPhrase) {
          cout << "Book ID: " << setw(55) << "Title: " << u[i][1] << endl
               << setw(55) << "Author: " << u[i][2] << endl
               << setw(55) << "Publisher: " << u[i][3] << endl
               << setw(55) << "Year: " << u[i][4] << endl
               << setw(70) << "Availabilty" << u[i][5] << "\n\n\n";
          matches++;
        }
      } else {
        if (containsAnyKeywords(bookDetails, keywords) || id == search) {
          cout << endl
               << "Book ID: " << u[i][0] << setw(55) << "Title: " << u[i][1]
               << endl
               << setw(55) << "Author: " << u[i][2] << endl
               << setw(55) << "Publisher: " << u[i][3] << endl
               << setw(55) << "Year: " << u[i][4] << endl;

          matches++;
        }
      }
    }
  }

  if (matches == 0) {
    cout << "No books found matching the search term." << endl;
  }
}

void R1AddBook(const string &id, const string &title, const string &author,
               const string &publisher) {
  if (book_count < MAX_BOOKS) {
    u[book_count][0] = id;
    u[book_count][1] = title;
    u[book_count][2] = author;
    u[book_count][3] = publisher;
    book_count++;
  } else {
    cout << "The book array is full. Cannot add more books." << endl;
  }
}

void R1RemoveBook(const string &id) {
    for (int i = 0; i < book_count; ++i) {
        if (u[i][0] == id) {
            // Clear the book details
            for (int j = 0; j < BOOK_DETAILS; ++j) {
                u[i][j] = "";
            }

            removed_indexes.push_back(i);
            cout << "Book with ID " << id << " has been removed." << endl;
            return;
        }
    }
    cout << "Book with ID " << id << " not found." << endl;
}

void ManageBooks() {
  string manageBookMenu = "\n\n\n*** Manage Books ***\n"
                          "[1] Display books\n"
                          "[2] Search book\n"
                          "[3] Add book\n"
                          "[4] Remove book\n"
                          "[5] Back\n"
                          "********************\n"
                          "Option (1 - 5):";
  do {
    cout << manageBookMenu;

    cin >> prog_choice;
    cout << "\n\n";

    cout << "Are you sure you want to choose option " << prog_choice
         << " ? (y/n) ";
    cin >> confirm;
    cout << "\n\n";

    switch (prog_choice) {
    case '1':
      R1Display();
      break;
    case '2':
      R1SearchBook();
      break;
    case '3': {
      string id, title, author, publisher, availability;

      cout << "Enter book ID: ";
      cin >> id;
      cout << "Enter book title: ";
      cin.ignore();
      getline(cin, title);
      cout << "Enter book author: ";
      getline(cin, author);
      cout << "Enter book publisher: ";
      getline(cin, publisher);

      R1AddBook(id, title, author, publisher);
      break;
    }
    case '4': {
      string id;
      cout << "Enter book ID: ";
      cin >> id;

      R1RemoveBook(id);
      break;
    }
    case '5':
      Back();
      break;

    default:
      cout << "No such option " << prog_choice << endl;
      cout << manageBookMenu;
      break;
    }
  } while (prog_choice != '5' || (confirm != 'y' && confirm != 'Y'));
}

////////////////////////////////-- R2 --///////////////////////////////////



void R2Display() {
    using namespace std;

    for (int i = 0; i < Borrowers_count - 1; i++) {
        for (int j = 0; j < Borrowers_count - 1 - i; j++) {
            if (v[j][0] > v[j + 1][0] || (v[j][0] == v[j + 1][0] && v[j][1] > v[j + 1][1])) {
                for (int k = 0; k < 5; k++) {
                    swap(v[j][k], v[j + 1][k]);
                }
            }
        }
    }

    for (int i = 0; i < Borrowers_count; i++) {
        // Ensure the first letter of each name part is uppercase and the rest are lowercase
        for (int j = 0; j < 2; j++) {
            for (size_t k = 0; k < v[i][j].size(); k++) {
                if (k == 0) {
                    v[i][j][k] = toupper(v[i][j][k]);
                } else {
                    v[i][j][k] = tolower(v[i][j][k]);
                }
            }
        }

        cout << "ID: " << v[i][3] << endl
             << "Name: " << v[i][0] << " " << v[i][1] << endl
             << "Contact number: " << v[i][2] << endl
             << "List of borrowed books: " << v[i][4] << endl
             << endl;
    }
}  


void R2SearchBorrower() {
  string search;
  cout << "Search: ";
  cin.ignore();
  getline(cin, search);

  transform(search.begin(), search.end(), search.begin(), ::tolower);

  int matches = 0;
  for (int i = 0; i < 500; i++) {
    if (!v[i][0].empty()) {
      string name = v[i][3];
      transform(name.begin(), name.end(), name.begin(), ::tolower);
      if (name == search) {
        cout << "ID: "  << v[i][3] << endl << "Name: " << v[i][0] << " " << v[i][1] << endl
             << "Contact number: " << v[i][2]
             << "List of borrowed books: " << v[i][4] << endl
             << endl;
        matches++;
      }
    }
  }

  if (matches == 0) {
    cout << "No borrower found matching the search term." << endl;
  }
};


bool isValidContactNumber(const string &contact_number) {
    if (contact_number.size() != 8) {
        return false;
    }

    char first_digit = contact_number[0];
    if (first_digit != '2' && first_digit != '3' && first_digit != '5' &&
        first_digit != '6' && first_digit != '9') {
        return false;
    }
    
    for (size_t i = 1; i < contact_number.size(); i++) {
        if (!isdigit(contact_number[i])) {
            return false;
        }
    }

    return true;
}


void R2AddBorrower(const string &lastName, const string &firstName,
                   const string &contact_number) {
    if (Borrowers_count < MAX_Borrowers) {
        // Ensure the last name is uppercase
        string formattedLastName = lastName;
        transform(formattedLastName.begin(), formattedLastName.end(), formattedLastName.begin(), ::toupper);
        // Ensure the first letter of each word in the first name is uppercase and the rest are lowercase
        string formattedFirstName = firstName;
        bool newWord = true;
        for (size_t k = 0; k < formattedFirstName.size(); k++) {
            if (formattedFirstName[k] == ' ') {
                newWord = true;
            } else if (newWord) {
                formattedFirstName[k] = toupper(formattedFirstName[k]);
                newWord = false;
            } else {
                formattedFirstName[k] = tolower(formattedFirstName[k]);
            }
        }

        string final_contact_number;
        if (contact_number.empty()) {
            final_contact_number = "00000000";
        } else if (isValidContactNumber(contact_number)) {
            final_contact_number = contact_number;
        } else {
            cout << "Invalid contact number. Please provide an 8-digit number starting with 2, 3, 5, 6, or 9." << endl;
            return;
        }

        v[Borrowers_count][0] = formattedLastName.substr(0, 10);
        v[Borrowers_count][1] = formattedFirstName.substr(0, 30);
        v[Borrowers_count][2] = final_contact_number;

        Borrowers_count++;

        stringstream ss;
        ss << "HKCC" << setw(4) << setfill('0') << currentID;
        v[Borrowers_count - 1][3] = ss.str();
        currentID++;
    } else {
        cout << "The borrower array is full. Cannot add more borrowers." << endl;
    }
}


void R2RemoveBorrower() {
  string borrowerID;
  cout << "Enter the borrower ID to remove: ";
  cin.ignore();
  getline(cin, borrowerID);

  bool found = false;
  for (int i = 0; i < MAX_Borrowers; i++) {
    if (!v[i][0].empty() && v[i][3] == borrowerID) {
      found = true;

      // Clear the borrower's information
      for (int j = 0; j < 5; j++) {
        v[i][j].clear();
      }

      cout << "Borrower with ID '" << borrowerID << "' has been removed." << endl;
      break;
    }
  }

  if (!found) {
    cout << "Borrower with ID '" << borrowerID << "' not found." << endl;
  }
}

void ManageBorrowers() {
  string ManageBorrowersMenu = "\n\n\n*** Manage Borrowers ***\n"
                               "[1] Display Borrowers\n"
                               "[2] Search Borrowers\n"
                               "[3] Add Borrowers\n"
                               "[4] Remove Borrowers\n"
                               "[5] Back\n"
                               "********************\n"
                               "Option (1 - 5):";
  char prog_choice;
  char confirm;

  do {
    cout << ManageBorrowersMenu;

    cin >> prog_choice;
    cout << "\n\n";

    cout << "Are you sure you want to choose option " << prog_choice
         << " ? (y/n) ";
    cin >> confirm;
    cout << "\n\n";

    switch (prog_choice) {
    case '1':
      R2Display();
      break;
    case '2':
      R2SearchBorrower();
      break;
    case '3': {
      string lastName, firstName, contact_number;

      cout << "Enter last name (press Enter to submit): ";
      cin.ignore();
      getline(cin, lastName);
      lastName.erase(remove(lastName.begin(), lastName.end(), ' '), lastName.end());

      cout << "Enter first name (press Enter to submit): ";
      getline(cin, firstName);
      firstName.erase(remove(firstName.begin(), firstName.end(), ' '), firstName.end());

      cout << "Enter contact number (press Enter to submit): ";
      getline(cin, contact_number);
      contact_number.erase(remove(contact_number.begin(), contact_number.end(), ' '), contact_number.end());

      R2AddBorrower(lastName, firstName, contact_number);
      break;
    }
    case '4':
      R2RemoveBorrower();
      break;
    case '5':
      Back();
      break;

    default:
      cout << "No such option " << prog_choice << endl;
      cout << ManageBorrowersMenu;
      break;
    }
  } while (prog_choice != '5' || confirm != 'y' || confirm != 'Y');
}



////////////////////////////////-- R3 --///////////////////////////////////

//Below function is to update the booklist and borrower list after borrowed
string display_borrowed_books(int borrower_index) {
    string result = "";
    string borrowed_books = v[borrower_index][4];
    size_t pos = 0;
    while ((pos = borrowed_books.find(";")) != string::npos) {
        string book_id = borrowed_books.substr(0, pos);
        borrowed_books.erase(0, pos + 1);
        result += "Book ID: " + book_id + "\n";
    }
    if (!borrowed_books.empty()) {
        result += "Book ID: " + borrowed_books + "\n";
    }
    return result;
}
//Below function is to check user book quota
int checkbookquota(int a) {
    string borrowed_books = v[a - 1][4];
    int sublistLength = std::count(borrowed_books.begin(), borrowed_books.end(), ';');

    if (!borrowed_books.empty()) {
        sublistLength++;
    }

    if (sublistLength >= 5) {
        cout << "We are sorry to inform you that you have not enough book quota"
            << endl;
        Back(); // Uncomment this line if you have defined the Back() function
    }
    return sublistLength;
}

int checkid(string a) {
    int rownumber = 0;
    bool found = false;
    while (rownumber < Borrowers_count) {
      //below is to find borrower list has the id that user input or not
        if (v[rownumber][3].find(a) != string::npos) {
          //if the id is vaild go to the function check boo quota to check his book quota
            cout << "ID is valid" << endl;
            checkbookquota(rownumber + 1);
            found = true;
            break;
        }
        rownumber++;//mark down the row of borrower list that can find the id 
    }

    if (!found) {
        cout << "ID is invalid" << endl;
        return -1; // Return -1 if ID is not found
    }

    return rownumber; // Return the correct row number when ID is found
}
//Below function is to check the book state is ok or not 
void checkbookstate(int a, int borrowerIndex) {
    if (u[a - 1][5] == "Yes") {
        cout << "This book can be borrowed" << endl;
        u[a - 1][5] = "No";
        string book_id = u[a - 1][0]; // Get the book ID

        // If the borrower has borrowed books before, add a delimiter before the new book ID
        if (!v[borrowerIndex][4].empty()) {
            v[borrowerIndex][4] += ";";
        }

        v[borrowerIndex][4] += book_id;
    } else {
        cout << "We are sorry to inform you that this book is not available to borrow" << endl;
    }
}

bool checkbookid(string a, int borrowerIndex) {
    int rownumber = 0;
    bool found = false;
    while (rownumber < book_count) {
        if (u[rownumber][0].find(a) != string::npos) {
            cout << "The book ID is valid" << endl;
            checkbookstate(rownumber + 1, borrowerIndex);
            found = true;
            break;
        }
        rownumber++;
    }

    if (!found) {
        cout << "The book ID is invalid" << endl;
    }

    return found;
}

void BorrowBooks() {
    string borrowerid;
    string bookid;
    char answer;
    int borrowerIndex;
    int borrowedBooksCount;

    do {
        cout << "Enter your borrower ID: ";//Let user input the borrower ID
        cin >> borrowerid;
        borrowerIndex = checkid(borrowerid);//Go to checkid function to Check the Id is vaild or not 
    } while (borrowerIndex == -1);//while the id is invaild ,let user input again

    borrowedBooksCount = checkbookquota(borrowerIndex + 1);
//Check user his boot quota
    // Display borrower details
    cout << "Borrower Details:" << endl
         << "ID: " << v[borrowerIndex][3] << endl
         << "Name: " << v[borrowerIndex][0] << " " << v[borrowerIndex][1] << endl
         << "Contact number: " << v[borrowerIndex][2] << endl
         << "Number of borrowed: " << borrowedBooksCount << endl
         << endl;
    do {
        cout << "Enter the ID of the book you want to borrow: ";//Let user enter the book id that want to borrow
        cin >> bookid;
        checkbookid(bookid, borrowerIndex); //turn to checkbookid functionto check the bookid is vaild or not
        cout << "Do you want to borrow another book? (Y/N): ";//If user answer y can let user input another book 
        cin >> answer;
    } while (answer == 'Y' || answer == 'y');
}


////////////////////////////////-- R4 --///////////////////////////////////



void ReturnBook() {
    string borrowerid;
    string bookid;
    int borrower_index;

    // Prompt for borrower ID and validate
    do {
        cout << "Enter your borrower ID: ";
        cin >> borrowerid;
        borrower_index = checkid(borrowerid);
    } while (borrower_index == -1);

    // Display borrower details
    cout << "Borrower Details:" << endl
         << "ID: " << v[borrower_index][3] << endl
         << "Name: " << v[borrower_index][0] << " " << v[borrower_index][1] << endl
         << "Contact number: " << v[borrower_index][2] << endl
         << "Borrowed books list:\n" << display_borrowed_books(borrower_index)
         << endl;

    // Prompt for book ID to return
    cout << "Enter the ID of the book you want to return: ";
    cin >> bookid;

    // Check if the book ID is in the borrower's list of borrowed books
    size_t pos = v[borrower_index][4].find(bookid);
    if (pos != string::npos) {
        // Remove the book ID from the borrower's list of borrowed books
        v[borrower_index][4].erase(pos, bookid.length());

        // Replace ';' delimiter if there are more books left in the list
        if (pos < v[borrower_index][4].length()) {
            v[borrower_index][4].replace(pos, 1, "");
        }

        // Update the book's status to "Available"
        for (int i = 0; i < book_count; ++i) {
            if (u[i][0] == bookid) {
                u[i][5] = "Yes";
                break;
            }
        }

        cout << "The book has been returned successfully." << endl;
    } else {
        cout << "The book ID is not found in the list of borrowed books." << endl;
    }

    // Display the list of borrowed books after returning a book
    cout << "Updated Borrowed books list:\n" << display_borrowed_books(borrower_index);
}


////////////////////////////////-- R5 --///////////////////////////////////

void UsefulFeatures(){
  int type;
  string Fiction[10] = {
  "Book ID:193156123 Title: Sleep Toward Heaven: A Novel\n"
  "Book ID:HK7432013 Title: Prairie Nocturne : A Novel (Ay Adult - Doig)\n"
  "Book ID:MJ3303204 Title: Starship Troopers: A Company of Stars (Pan Science Fiction)\n"
  "Book ID:330301748 Title: The Circus of Adventure (Adventure Series)\n"
  "Book ID:159017061 Title: The Day of the Owl (New York Review Books Classics)\n"
  "Book ID:60196017 Title: The Doctor: A Novel\n"
  "Book ID:CC7434172 Title: The Last Vampire : A Novel\n"
  "Book ID:451200454 Title: The Nabob's Daughter (Signet Regency Romance)\n"
  "Book ID:MJ3933216 Title: The Salt Letters: A Novel\n"
  "Book ID:NOV812550 Title: The Talk Show Defense (Maggie Van Zandt Novels (Paperback))\n"
  };
  string Science[10] = {
  "Book ID:MJ6718944 Title: FINAL DAYS\n"
  "Book ID:CC5860680 Title: Life goes on\n"
  "Book ID:MJ8024381 Title: Light from Heaven\n"
  "Book ID:REL373094 Title: Moon And Sun\n"
  "Book ID:BK8711321 Title: The Face of War\n"
  "Book ID:158717025 Title: The Magic City\n"
  "Book ID:NOV446324 Title: The November Man\n"
  "Book ID:CN3453260 Title: The Wounded Land\n"
  "Book ID:REL553245 Title: Three Men Out\n"
  "Book ID:REL441009 Title: Tree Girl\n"
  };
  string Horror[10] = {
  "Book ID:380773716 Title: Midnight Rain\n"
  "Book ID:REL735816 Title: Robbie and Ronnie\n"
  "Book ID:REL679405 Title: Skating in the Dark\n"
  "Book ID:NOV723303 Title: The God Boy\n"
  "Book ID:CC7434172 Title: The Last Vampire:A Novel\n"
  "Book ID:CC3071020 Title: The Night Before Christmas \n"
  "Book ID:BK5906156 Title: The Whales\n"
  "Book ID:REL970214 Title: Too Dead To Swing\n"
  "Book ID:916119599 Title: What Do You See?\n"
  "Book ID:NOV316482 Title: Wintering\n"
  };
  string Mystery[10] = {
  "Book ID:CN3854703 Title: We're Off to See the Killer\n"
  "Book ID:CN8836860 Title: The Power of Faith\n"
  "Book ID:451405021 Title: Again\n"
  "Book ID:HK1575664 Title: Backstage Murder\n"
  "Book ID:REL082176 Title: Blood Secrets(Vampire Legacy)\n"
  "Book ID:CN3930364 Title: Black Betty (Easy Rawlins Mysteries(Hardcover))\n"
  "Book ID:CN5904331 Title: Christmas Killer(Point)\n"
  "Book ID:REL451411 Title: Dead Guilty\n"
  "Book ID:MJ3732608 Title: Deadly Promise\n"
  "Book ID:BK0801044 Title: Mystery in Massachusetts (X-Country Adventures)\n"
  };
  string Children[10] = {
  "Book ID:HK7651082 Title: The Story of the House of Wooden Santas\n"
  "Book ID:MJ4401813 Title: The Silver Fox\n"
  "Book ID:NOV449223 Title: The Paper Princess/the Perfect Gentleman(Two Books in One)\n"
  "Book ID:CN0449219 Title: The Gift of Asher Lev\n"
  "Book ID:HK7847085 Title: The Best Thing About Christmas\n"
  "Book ID:NY0590457 Title: A Girl's Best Friend\n"
  "Book ID:BK3499207 Title: Alice im Wunderland\n"
  "Book ID:REL702220 Title: Amy's Children\n"
  "Book ID:BK4465143 Title: Angel Fire\n"
  "Book ID:786832622 Title: Celebrate the Year with Winnie the Pooh (A Disney Holiday Treasury)\n"
  };
  string ComputerBooks[10] = {
      "Book ID:MJ3293201 Title: Learning C++ from \" ABC \"\n",
      "Book ID:HK3492049 Title: Magic of C++ programming\n",
      "Book ID:340414481 Ttile: Object-oriented programming with C++, 1st "
      "edition.\n",
      "Book ID:SEHH2042 Title: C++ Language for Beginners\n",
      "Book ID:IT2042-01A Title: Object-oriented design using C++\n",
      "Book ID:1234C Title: C++: \"Basic\" Syntax\n",
      "Book ID:HK3426701 Title: Comparison between C++ and Java\n",
      "Book ID:NOV357006 Title: Comparison between C++ and Python\n",
      "Book ID:207076175 Title: Learning JAVA from \" ABC \"\n",
      "Book ID:JAVA2233 Title: \" J \", is for Java\"\n"
};
  do {
  cout << "Which type of recommended book you want?(type numbers only)" << endl;
  cout << "(1): Fiction\n" 
          "(2): Science Fiction\n"
          "(3): Horror\n"
          "(4): Mystery\n"
          "(5): Children's Literature\n"
          "(6): Computer Programming\n"
          "(7): Back\n"; // asking user they want which type of book
  cin >> type;
  switch(type) {
    case 1: 
      for (string i : Fiction) {
        cout << i << "\n";
      }
      break;
    case 2: 
      for (string i : Science) {
        cout << i << "\n";
        }
      break;
    case 3: 
      for (string i : Horror) {
        cout << i << "\n";
      }
      break;
    case 4: 
      for (string i : Mystery) {
        cout << i << "\n";
      }
      break;
    case 5: 
      for (string i : Children) {
        cout << i << "\n";
      }
      break;
    case 6: 
      for (string i : ComputerBooks) {
        cout << i << "\n";
      }
      break;
    case 7: 
       { Back();
        
      }
      break;
    default: cout << "No such option.\n\n"; 
    break; //show different types of recommonded book to users
    
  }
  } while ( type != 1-7 );
};

////////////////////////////////-- R6 --///////////////////////////////////

void MemberList() {
    cout << left << setw(30) << "Name" << setw(20) << "Student ID" << setw(10) << "Class" << setw(20) << "Tutorial Group" << endl;
    cout << left << setw(30) << "Kwan Yuen Man" << setw(20) << "22023257A" << setw(10) << " " << setw(20) << "202D" << endl;
    cout << left << setw(30) << "Lai Tin Ching" << setw(20) << "22136288A" << setw(10) << " " << setw(20) << "202C" << endl;
    cout << left << setw(30) << "Wong Chi Wa" << setw(20) << "22143138A" << setw(10) << " " << setw(20) << "" << endl;
    cout << left << setw(30) << "Yip Ka Yiu" << setw(20) << "22008647A" << setw(10) << " " << setw(20) << "" << endl;
    cout << endl << "Tutorial Group: " << "202D, 202C" << endl;
}


int main() {

cout << "\n\n";
cout << "\000[33m   _      _ _  \n";
cout << "  | |    (_| |  \n";
cout << "  | |     _| |__  _ __ __ _ _ __ _   _   \n";
cout << "  | |    | | '_ \\| '__/ _` | '__| | | |   \n";
cout << "  | |____| | |_) | | | (_| | |  | |_| |  \n";
cout << "  |______|_|_.__/|_|  \\__,_|_|   \\__, |                    _\n";
cout << "  |  \\/  |                        __/ |                    | |    \n";
cout << "  | \\  / | __ _ _ __   __ _  __ _|___/ _ __ ___   ___ _ __ | |_   \n";
cout << "  | |\\/| |/ _` | '_ \\ / _` |/ _` |/ _ | '_ ` _ \\ / _ | '_ \\| __| \n";
cout << "  | |  | | (_| | | | | (_| | (_| |  __| | | | | |  __| | | | |_   \n";
cout << "  |_|__|_|\\__,_|_| |_|\\__,_|\\__, |\\___|_| |_| |_|\\___|_| |_|\\__| \n";
cout << "   / ____|         | |       __/ |                                \n";
cout << "  | (___  _   _ ___| |_ ___ |___/___                              \n";
cout << "   \\___ \\| | | / __| __/ _ | '_ ` _ \\                             \n";
cout << "   ____) | |_| \\__ | ||  __| | | | | |                            \n";
cout << "  |_____/ \\__, |___/\\__\\___|_| |_| |_|                            \n";
cout << "           __/ |                                                  \n";
cout << "          |___/                                                   \000[0m\n";



  
  
  string YN;
  char exit;

  cout << "\n\n\n\nImport book list from file? [Y/N]: ";
  cin >> YN;

  if (YN == "Y" || YN == "y") {
    cout << "Input path to CSV file: ";
     cin >> BookList;
   
 
    readCSV(BookList, BOOKS);

    cout << "\n\nImporting book list . . . Done";

  }

  else if (YN == "N" || YN == "n") {
    cout << "No book list is importe";
  }

  cout << "\n\n\nBorrower list from file? [Y/N]: ";
  cin >> YN;
  if (YN == "Y" || YN == "y") {
    cout << "Input path to CSV file: ";
    cin >> BorrowerList;
    
    readCSV(BorrowerList, BORROWERS);
    cout << "Importing borrower list . . . Done";


  } else if (YN == "N" || YN == "n") {
    cout << "No borrower list is importe";
  }

Back();


  return 0;
}
