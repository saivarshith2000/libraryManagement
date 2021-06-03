#include <bits/stdc++.h>
using namespace std;

class Student
{
public:
	string Name;
	int Id;

	Student(string name, int id)
	{
		Name = name;
		Id = id;
	}
};

class Book
{
public:
	string Name;
	int bookId;
	int studentId;

	Book() {
		// default constructor - used for empty book
		bookId = -1;
	}

	Book(string name, int id)
	{
		Name = name;
		bookId = id;
		studentId = -1;
	}
};

class StudentRepository
{
public:
	vector<Student> students;
	void AddStudent(Student student)
	{
		students.push_back(student);
	}
};

class BookRepository
{
public:
	vector<Book> books;
	void AddBook(Book book)
	{
		books.push_back(book);
	}

	Book *FindBook(string BookName)
	{
		if (books.size() == 0)
			return new Book();
		for (int i = 0; i < books.size(); i++)
		{
			if (books[i].Name == BookName)
			{
				return &books[i];
			}
		}
		return new Book();
	}
}
;

class Library
{
private:
	// assume that each book has only one copy - no checks are implemented.
	StudentRepository studentRepository;
	BookRepository bookRepository;

public:
	// dependency injection for repositories
	Library(StudentRepository s, BookRepository b) {
		studentRepository = s;
		bookRepository = b;
	}

	// borrow a copy of the book with name - BookName
	Book *BorrowBook(string BookName, Student student)
	{
		Book *book = bookRepository.FindBook(BookName);
		// if the book is not found, return empty book
		if (book->bookId == -1)
			return book;
		// set studentId of book to student's Id
		book->studentId = student.Id;
		return book;
	}

	void ReturnBook(Book *book)
	{
		book->studentId = -1;
	}
};

void BookRepoTest() {
	// test if book is added to repo
	BookRepository br;
	Book b("A Book", 1);
	br.AddBook(b);
	assert(br.books.size() == 1);
	assert(br.books[0].Name == "A Book");
	assert(br.books[0].bookId == 1);

	assert(br.FindBook("A Book")->Name == b.Name);
}

void StudentRepoTest() {
	StudentRepository sr;
	Student s("Test User", 1);
	sr.AddStudent(s);
	assert(sr.students.size() == 1);
	assert(sr.students[0].Name == "Test User");
	assert(sr.students[0].Id == 1);
}

void LibraryTest() {
	StudentRepository sr;
	BookRepository br;
	Student s("Temp Student", 1);
	Library lb(sr, br);
	// test for empty books
	assert(lb.BorrowBook("Any Name", s)->bookId == -1);
}

void TESTS() {
	BookRepoTest();
	StudentRepoTest();
	LibraryTest();
}

int main()
{
	// Unit tests
	TESTS();
	cout << "ALL UNIT TESTS PASSED!\n" << endl;

	// integration tests
	StudentRepository studentRepo;
	BookRepository bookRepo;
	// Add users to student repository
	Student s1("Test User", 1);
	Student s2("Best User", 2);
	Student s3("Nest User", 3);
	studentRepo.AddStudent(s1);
	studentRepo.AddStudent(s2);
	studentRepo.AddStudent(s3);
	// Add books to books repository
	Book b1("A Book", 1);
	Book b2("Another Book", 2);
	Book b3("Yet Another Book", 3);
	bookRepo.AddBook(b1);
	bookRepo.AddBook(b2);
	bookRepo.AddBook(b3);
	Library lib(studentRepo, bookRepo);
	Book* b = lib.BorrowBook("A Book", s1);
	cout << b->Name << endl;
	Book* bb = lib.BorrowBook("A Book doesn't exist", s1);
	cout << bb->Name << endl;
}
