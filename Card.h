#ifndef CARD_H
#define CARD_H

#include<iostream>
#include<string>
using namespace std;

class Card
{
private:
	//member variables
	string color;
	string number;
public:
	//Default Constructor 
	Card();
	//overload Constructor
	Card(string, string);
	//Accessor function
	string get_color() const;
	string get_number() const;

	//Mutator function
	void set_color(string);
	void set_number(string);


	//print the object
	string tostring_card() const;
};

#endif // !CARD_H


