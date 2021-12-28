#ifndef PLAYER_H
#define PLAYER_H

#include<iostream>
#include<string>
#include<vector>
#include "Card.h"
using namespace std;

class Player
{
private:
	//member variables
	string name;
	int age, total_score;
	vector<int> scores;
	vector<Card> hand_in_cards;

public:
	//default constructor
	Player();
	//overloaded constructor
	Player(string, int);
	//Accessor function
	string get_name() const;
	int get_age() const;
	vector<Card> get_cards() const;
	//To get the scores of player
	vector<int> get_scores();
	//To get the total score of player
	int get_totalscore();
	

	//Mutator function
	void set_name(string);
	void set_age(int);
	void set_cards(vector<Card>&);

	//assigning score for each player
	void assign_score(int);
	//assigning total score
	void assign_totalscore(int t_tscore);

	//Reset the player for next round
	void reset_players();

	//print the object
	string tostring_player() const;

};









#endif // !PLAYER_H


