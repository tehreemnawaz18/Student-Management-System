// Name : Tehreem Nawaz
// Roll No : 25212522049
// BSSE ( Self Support ) Semester 2
// OOP Project
// Submitted To : Dr. Mohsin Nazir

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

// 1. Abstraction ( Abstract Base Class )

class Person {
	protected:
		string name;
		int age;

	public:
		Person ( string n, int a) : name (n), age (a) {}
		virtual void displayDetails() = 0 ;     // Pure Virtual Function
		virtual ~Person() {}     // Virtual Destructor

};

// 2. Inheritance ( Student inherits from Person )

class Student : public Person {
	private:

// 3. Encapsulation : Data members are private

		int rollNumber;
		string course;

	public:

// Constructor

		Student (string n, int a, int r, string c) :
			Person (n, a), rollNumber ( r ), course ( c )  {}

// Getters

		int getRoll() {
			return rollNumber ;
		}
		string getName() {
			return name ;
		}
		int getAge() {
			return age ;
		}
		string getCourse() {
			return course ;
		}

// 4. polymorphism ( Runtime Polymorphism / Method Overriding )

		void displayDetails() override {
			cout<< "\t Roll No:" << rollNumber << "\n";
			cout<< "\t Name:" << name << "\n";
			cout<< "\t Age:" << age << "\n";
			cout<< "\t Course:" << course << "\n";
			cout<< "\t ----------------------- \n";
		}
};

// Management Class for CRUD and File Handling

class StudentManager {
	private:
		string filename = "students.txt";

	public:
		void addStudent() {
			string name, course ;
			int age, roll ;

			cout << "\nEnter Roll Number: ";
			cin >> roll;
			cin.ignore();
			cout << "Enter Name: ";
			getline(cin, name);
			cout << "Enter Age: ";
			cin >> age;
			cin.ignore();
			cout << "Enter Course: ";
			getline(cin, course);

			ofstream outFile(filename, ios::app);
			if (outFile.is_open()) {

				outFile << roll << "," << name << "," << age << "," << course << "\n";
				outFile.close();
				cout << "\n[Success] Student record added successfully!\n";
			} else {
				cout << "\n[Error] Unable to open file!\n";
			}
		}

// File Handling: Read and Display Data

		void displayAllStudents() {
			ifstream inFile(filename);
			if (!inFile.is_open()) {
				cout << "\n[Info] No student records found or file does not exist.\n";
				return;
			}

			string line;
			cout << "\n================ STUDENT LIST ================\n";

			while (getline(inFile, line)) {

				size_t pos1 = line.find(',');
				size_t pos2 = line.find(',', pos1 + 1);
				size_t pos3 = line.find(',', pos2 + 1);

				int roll = stoi(line.substr(0, pos1));
				string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
				int age = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
				string course = line.substr(pos3 + 1);

// Polymorphism in action using Base Class Pointer

				Person* personPtr = new Student(name, age, roll, course);
				personPtr->displayDetails();
				delete personPtr;
			}
			inFile.close();
		}

// Search Student by Roll Number

		void searchStudent() {
			int searchRoll;
			cout << "\nEnter Roll Number to search: ";
			cin >> searchRoll;

			ifstream inFile(filename);
			string line;
			bool found = false;

			while (getline(inFile, line)) {
				size_t pos1 = line.find(',');
				int roll = stoi(line.substr(0, pos1));

				if (roll == searchRoll) {
					size_t pos2 = line.find(',', pos1 + 1);
					size_t pos3 = line.find(',', pos2 + 1);
					string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
					int age = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
					string course = line.substr(pos3 + 1);

					cout << "\n[Record Found]:\n";
					Student s(name, age, roll, course);
					s.displayDetails();
					found = true;
					break;
				}
			}

			inFile.close();
			if (!found) cout << "\n[Info] Student with Roll Number " << searchRoll << " not found.\n";
		}

// Delete Student Record (File Handling: Temp file approach)

		void deleteStudent() {
			int deleteRoll;
			cout << "\nEnter Roll Number to delete: ";
			cin >> deleteRoll;

			ifstream inFile(filename);
			ofstream tempFile("temp.txt");
			string line;
			bool found = false;

			while (getline(inFile, line)) {
				size_t pos1 = line.find(',');
				int roll = stoi(line.substr(0, pos1));

				if (roll == deleteRoll) {
					found = true;
					continue;
				}
				tempFile << line << "\n";
			}

			inFile.close();
			tempFile.close();

			remove(filename.c_str());
			rename("temp.txt", filename.c_str());

			if (found) cout << "\n[Success] Student record deleted successfully!\n";
			else cout << "\n[Info] Record not found.\n";
		}
};

// Main Menu

int main() {

	StudentManager manager;
	int choice;

	do {
		cout << "\n=========================================\n";
		cout << "       STUDENT MANAGEMENT SYSTEM         \n";
		cout << "=========================================\n";
		cout << "1. Add New Student\n";
		cout << "2. Display All Students\n";
		cout << "3. Search Student\n";
		cout << "4. Delete Student\n";
		cout << "5. Exit\n";
		cout << "Enter your choice (1-5): ";
		cin >> choice;

		switch (choice) {
			case 1:
				manager.addStudent();
				break;
			case 2:
				manager.displayAllStudents();
				break;
			case 3:
				manager.searchStudent();
				break;
			case 4:
				manager.deleteStudent();
				break;
			case 5:
				cout << "\nThank you for using the system. Goodbye!\n";
				break;
			default:
				cout << "\n[Warning] Invalid choice! Please try again.\n";

		}

	} while (choice != 5);

	return 0;
}