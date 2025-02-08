//hw8.cpp CS-1210 Bible Verse Homework
//Caleb Doese
//October 27, 2021

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

int main() {
	//Declare string variables to input book, chapter, and verse
	string userBook;
	string chapter;
	string verse;

	//Declare bool variables to check if book, chapter, and verse is found
	bool foundChapter = false;
	bool foundVerse = false;
	bool foundBook = false;

	//Get reference from user
	cout << "Please enter reference of the verse you want to receive" << endl;
	cout << "Which book?" << endl;
	cin >> userBook;

		//Ensure that each letter in userBook is capitalized to match format of text file
		for (int i=0; i < userBook.size(); i++) {
			userBook.at(i) = toupper(userBook.at(i));
	}
	cout << "Which chapter?" << endl;
	cin >> chapter;
	cout << "Which verse?" << endl;
	cin >> verse;

	//Declare variable of type input file stream
	ifstream theBible;

	//Use .open property to open input file
	theBible.open("Bible.txt");

	//Declare variable to receive each line of the input file
	string line;

	//While loop that goes line by line of the Bible, searching for the reference until it reaches the end of the file
	while (!theBible.eof()) {
		getline(theBible, line);

		//Find correct book
		if (line == "THE BOOK OF " + userBook) {
			foundBook = true;
		}

		//Find correct chapter, special case for Psalms
		if ((userBook == "PSALMS") && (line == "PSALM " + chapter) && (foundBook == true)) {
			foundChapter = true;
		}
		if ((line == "CHAPTER " + chapter) && (foundBook == true)) {
			foundChapter = true;
		}

		//Find correct verse within the chapter
		if ((line.find(verse) == 0) && (foundBook == true) && (foundChapter == true)) {
					foundVerse = true;

					//Re-format userBook to have first letter capitalized and every other letter lowercase
					for (int i=1; i < userBook.size(); i++) {
						userBook.at(i) = tolower(userBook.at(i));
					}

					//Output the verse to the user
					cout << "The verse you want is: " << endl;
					cout << userBook << " " << chapter << ":" << line << endl;

					//Declare variable with type output file stream
					ofstream myTextFile;

					//Open the file for output, ensure that it appends text rather than replaces text
					myTextFile.open("verses.txt", ios::app);

					//Output the verse to the output file
					myTextFile << userBook << " " << chapter << ":" << line << endl;

					//Close output file
					myTextFile.close();
					exit(1);
		}
	}

	//If while loop did not find the book, display error to user
	if (foundBook == false) {
		cout << userBook << " is not in the Bible." << endl;
		exit(1);
	}

	//If while loop did not find the chapter within the book, display error to user
	else if (foundChapter == false) {
		cout << "There is no chapter " << chapter << " in the book of " << userBook << endl;
		exit(1);
	}

	//If while loop did not find the verse within the chapter, display error to user
	else if (foundVerse == false) {
		cout << "There is no verse " << verse << " in chapter " << chapter << " of the book of " << userBook << endl;
		exit(1);
	}

	//Close the input text file
	theBible.close();

	return 0;
}
