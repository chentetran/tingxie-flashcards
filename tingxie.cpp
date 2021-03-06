// tingxie.cpp
// Created by Vincent Tran, 10/4/2015
//
// To help with the hard 听写s of Chinese 21.
// Simulates flashcards.
// Prints pinyin to terminal, user must write in correct hanzi.

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cassert>

using namespace std;

// Simulates flashcards
struct fc {
	string pinyin;
	string hanzi;
};
  
void game_over(int correct, int total, vector<fc> &wrong);
void shuffle(vector<fc> &words);
void run(vector<fc> &words);

int main(int argc, char *argv[])
{	
	if (argc == 1) {
		cout << "No file inputted\n";
		return 0;
	}
	assert(argv[1] != NULL);

	string line;
	fc temp;
	vector<fc> words;
	
	ifstream file(argv[1]);
	while (!file.eof()) {
		getline(file, temp.pinyin, '|');
		getline(file, temp.hanzi);

		words.push_back(temp);
	}
	file.close();

	shuffle(words);
	run(words);

	return 0;
}

// Prints out results and score at end of program C
void game_over(int correct, int total, vector<fc> &wrong)
{
	float score = (float) correct/total;
	char input;

	// prints words that user answered incorrectly
	cout << "Words you got wrong: " << endl;
	for (int i = 0; i < wrong.size(); i++) {
		cout << "\t" << wrong[i].pinyin << " | " << wrong[i].hanzi << endl;
	}

	cout << "Correct: " << correct  << endl;
	cout << "Total: " << total << endl;
	cout << "Your score is " << score*100 << "%\n";

	if (score != 1 || total == 0) {
		review:
		cout << endl << "Review the words you got wrong? (y/n) ";
		cin >> input;
		if (input == 'y') 
			run(wrong);
		else if (input == 'n')
			return;
		else goto review;
	}
}

// Randomizes the order of the words in fc array
void shuffle(vector<fc> &words)
{
	int randi;
	random_device rd;
	mt19937 mt(rd());
	uniform_real_distribution<double> dist(0, words.size());

	for (int i = 0; i < words.size(); i++) {
		randi = dist(mt);
		fc temp = words[i];
		words[i] = words[randi];
		words[randi] = temp;
	}
}

// Conducts the test
void run(vector<fc> &words)
{
	shuffle(words);
	cout << string(100, '\n');

	string input;
	int total = 0, correct = 0;
	vector<fc> wrong;

	for (int i = 0; i < words.size(); i++) {
		cout << i+1 << ".) " << words[i].pinyin << " ";
		cin >> input;

		if (input == words[i].hanzi) {
			cout << "Correct!\n" << endl;
			correct++;
		}
		else {
			if (input == "q") { // user wants to quit
				cout << endl;
				break;
			}
			cout << "Wrong! Correct answer is " << words[i].hanzi
				 << endl << endl;
			wrong.push_back(words[i]);
		}
		total++;
	}

	game_over(correct, total, wrong);
}

