#include "Player.h"

//default constructor
Player::Player()
{

}
//constructor for create a player with parameter
Player::Player(string t_name, int t_age)
{
	name = t_name;
	age = t_age;

}
//this method returns the name of the player
string Player::get_name() const
{
	return name;
}
//this method returns the age of the player
int Player::get_age() const
{
	return age;
}
//This method returns the cards of player's hand
vector<Card> Player::get_cards() const
{
	return hand_in_cards;
}
//This method returns the scores of the player
vector<int> Player::get_scores()
{
	return scores;
}
//This method returns the Total scores of the player
int Player::get_totalscore()
{
	return total_score;
}

//To set the name of player
void Player::set_name(string t_name)
{
	name = t_name;
}
//set the age of the player
void Player::set_age(int t_age)
{
	age = t_age;
}
//To set the vector of cards to the player
void Player::set_cards(vector<Card>& t_cards)
{
	hand_in_cards = t_cards;

}
//This method assign the score to the player
void Player::assign_score(int t_score)
{
	scores.push_back(t_score);
}
//This method assign the Total score to the player
void Player::assign_totalscore(int t_tscore)
{
	total_score = t_tscore;
}

//This method reset the players for next round
//by clear their cards 
void Player::reset_players()
{
	hand_in_cards.clear();
}

//This method returns string formate of this object
string Player::tostring_player() const
{
	string player;

	unsigned int size = hand_in_cards.size();
	player = "player{" + name + "," + to_string(age) + ",";

	for (unsigned int i = 0; i<size; i++)
	{
		player += hand_in_cards[i].tostring_card() + "\t";
	}
	player += "}";
	return player;
}