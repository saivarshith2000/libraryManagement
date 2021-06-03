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
private:
	vector<Student> students;

public:
	void AddStudent(Student student)
	{
		students.push_back(student);
	}
};

class BookRepository
{
private:
	vector<Book> books;

public:
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

int main()
{
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
	cout << b1.Name << endl;
}
