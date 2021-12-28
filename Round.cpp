#include"Round.h"
#include"Player.h"
#include<string>
#include<ctime>
using namespace std;

//default constructor
Round::Round()
{

}
//constructor to create the round object with parameters
Round::Round(vector<Player> t_players, vector<Card> t_deck)
{
	players = t_players;
	deckofcards = t_deck;
}

//this method returns player from the round
vector<Player> Round::get_players() const
{
	return players;
}
//this method returns cards from the round
vector<Card> Round::get_cards() const
{
	return deckofcards;
}

//set the players to round object
void Round::set_Players(vector<Player>& t_players)
{
	players = t_players;
}
//set the cards to round object
void Round::set_cards(vector<Card>& t_deck)
{
	deckofcards = t_deck;
}

//shuffle the deck of card by geting random number
void Round::shuffle(int round)
{
	int i, j, times = 1000;

	srand(unsigned int(time(NULL)*round));
	while (times > 0)
	{
		i = rand() % 76;
		j = rand() % 76;
		//cout << i << ", "<< j << endl;
		swap(deckofcards.at(i), deckofcards.at(j));
		//swap(i, j);
		times--;
	}

}
//swap the cards for sorting and shuffle
void Round::swap(Card& card1, Card& card2)
{
Card temp = card2;
card2 = card1;
card1 = temp;
}

//deal 7 card to each players
vector<Card> Round::deal_cards()
{
	//vector<Card>::iterator it;
	vector<Card> t_hand_in_cards;
	

	auto it = deckofcards.begin();
	
	for (int i = 0; i<7; i++)
	{
		it = deckofcards.end();
		t_hand_in_cards.push_back(deckofcards.back());
		deckofcards.erase(it - 1);
		
	}
	return t_hand_in_cards;
}
//assigning 7 the cards to each players
void Round::assign_cards()
{

	unsigned int size = players.size();
	for (unsigned int i = 0; i<size; i++)
	{
		players[i].set_cards(deal_cards());

	}
}
//draw acard from draw pile
Card  Round::draw_card()
{
	auto it = deckofcards.end() - 1;
	Card draw = deckofcards.back();
	deckofcards.erase(it);
	return draw;
}
//print out the Players
void Round::print_players()
{
	unsigned int size = players.size();
	for (unsigned int i = 0; i<size; ++i)
	{
		cout << players[i].tostring_player() << endl;

	}
	cout << endl;
}

//To sort the Cards by its number to relese more points cards first
void Round::Sort_cards()
{
	unsigned int size = players.size(),i(0),cards_size(0);
	while (i < size)
	{
		vector<Card> cards = players[i].get_cards();
		cards_size = cards.size();
		
		for (auto it = cards.end()-1; it != cards.begin(); it--)
		{
		
			for (auto itj = cards.begin(); itj < it; itj++)
			{
				if (stoi(itj->get_number()) < stoi((itj + 1)->get_number())) //sort the cards in decending order
				{
					
					swap(*itj, *(itj + 1));
				}
			}
		}
		players[i].set_cards(cards);//To set the sorted cards into the players
		i++;
	}



}
//comparing the draw card with players cards
void  Round::start_game(int round)
{
	
	vector<Card> in_hand;
	bool empty = false;
	Card draw = draw_card();
	unsigned int i = 0, size = players.size(), count = 0, sum_size;
	Sort_cards();

	//print_players();		//To check the players cards
	cout << "\nGAME ROUND No. : " << round;
	cin.ignore();
	cout << "\n\n----------------------------------TOP CARD IN THE DISCARD PILE : " << draw.tostring_card() << endl;
	while (!empty)
	{
		sum_size = 0;
		for (i = 0; i < size; i++)
		{
			in_hand = players[i].get_cards();

			//cout << "----------------------------------TOP CARD IN THE DISCARD PILE : " << draw.tostring_card() << endl;
			//cin.ignore();

			for (auto it = in_hand.begin(); it != in_hand.end(); ++it)
			{

				if (draw.get_color() == it->get_color() || draw.get_number() == it->get_number())
				{
					

					draw = *it; //to update the top of discard pile by the card which is matched with draw card
					in_hand.erase(it); //to discard the card which is matched with draw card
					cout << "----------------------------------TOP CARD IN THE DISCARD PILE : " << draw.tostring_card() << "  by "
						<< players[i].get_name() << endl;
					cin.ignore();
					count = 0;
					players[i].set_cards(in_hand);
						
						
					  if (in_hand.size() == 1)
						{
							SetConsoleTextAttribute(color, 10);
							cout << "**************************************" << players[i].get_name() << "  says UNO!!!" << endl;
							SetConsoleTextAttribute(color, 15);
						}
					
					break;
					
				}

				else
				{


					unsigned int s = in_hand.size();
					sum_size += s;
					

					if (sum_size<count)
					{
						draw = draw_card();
						
					}
				}

				count++;

			}
			if (in_hand.empty())
			{
				empty = true;

				cout << "Winner of this round is : " << players[i].get_name() << endl;
				players[i].assign_score(calculate_round_score());

				break;
			}
			
		}

	}
}
//calculating the round score
int Round::calculate_round_score()
{
	unsigned int size = players.size(), card_count, count;
	int score = 0;
	string num;
	for (unsigned int i = 0; i<size; i++)
	{

		card_count = players[i].get_cards().size();
		count = 0;
		while (count < card_count)
		{
			num = players[i].get_cards().at(count).get_number();
			score += stoi(num);
			count++;
		}
	}
	return score;

}
