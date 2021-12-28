#ifndef ROUND_H
#define ROUND_H

#include<vector>
#include<string>
#include"Card.h"
#include"Player.h"
#include"windows.h"
using namespace std;

class Round
{
private:
	//member variables
	vector<Player> players;
	vector<Card> deckofcards;
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE); //just once

public:
	//default constructor
	Round();
	//overload constructor
	Round(vector<Player>, vector<Card>);

	//Accessor function
	vector<Player> get_players() const;
	vector<Card> get_cards() const;

	//Mutator function
	void set_Players(vector<Player>&);
	void set_cards(vector<Card>&);

	//shuffle the deckof card
	void shuffle(int);
	void swap(Card&, Card&);
	//void swap(int, int);

	//deal the cards to each players 
	vector<Card> deal_cards();
	void assign_cards();

	//drawing a card from drawpile
	Card  draw_card();

	//print the players before round start
	void print_players();

	//sort the card by its points
	void Sort_cards();
	//Player next_player();
	void start_game(int);
	

	//round score calculating
	int calculate_round_score();

};


#endif // !ROUND_H


