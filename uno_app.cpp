/*****************************************************************************
// CPSC 230			spring 2019			Cumulative Project
// Kukapalini Mathialakan
// UNO Card Game
****************************************************************************/

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"windows.h"
#include "Card.h"
#include "Player.h"
#include"Round.h"
using namespace std;

void create_players(vector<Player>&, int, HANDLE);
void start_playUNO(vector<Card>&, vector<Player>&, HANDLE);
void generate_deckofcard(vector<Card>&);
bool find_gameover(vector<Player>, HANDLE);
void reset_players(vector<Player>&);
int calculate_total_score(vector<int>);
void print_vector(const vector<Card>);
void print_players(const vector<Player>&);
void print_scores(vector<Player>);


//int const MAX = 76;

int main()
{
	vector<Card> carddeck;
	vector<Player> players;
	string name;
	int no_of_players, age(0);
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE); //just once

	SetConsoleTextAttribute(color, 10);
	cout << "\n\n                          LET'S PLAY UNO \n";
	SetConsoleTextAttribute(color, 15);
	
	do
	{
		//cin.ignore();
		cout << "\nEnter the no of players they are going to join this game : ";
		cin >> no_of_players;
		//cout << "\n np: " <<no_of_players;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			SetConsoleTextAttribute(color, 4);
			cout << "\n UNO for 2-10 players. ";
			SetConsoleTextAttribute(color, 15);

		}
		if (no_of_players < 2 || no_of_players>10)
		{
			SetConsoleTextAttribute(color, 4);
			cout << "\n UNO for 2-10 players. ";
			SetConsoleTextAttribute(color, 15);
		}
		
	} while (no_of_players <2 || no_of_players>10 || cin.fail());//To validate the number of players must be a integer between 2 and 10

	create_players(players, no_of_players,color);

	//start
	start_playUNO(carddeck, players,color);
	
	print_scores(players);
	return 0;
}

//pre-condition passing called by reference parameter Player type vector and number of players as int type
//post-condition createing players and push it into the vector players
void create_players(vector<Player>& players, int no_of_players,HANDLE color)
{
	string name;
	int age;
	for (int i = 1; i <= no_of_players; i++)
	{

		cout << "\nPlayer " << i << ":\n\t\tFirst Name :";
		cin >> name;
		cout << "\n\t\t Age :";
		cin >> age;
		if (age<7)
		{
			while ((age < 7)|| cin.fail())//To validate the age of player must not be less than 7
			{
				SetConsoleTextAttribute(color, 4);
				cout << "You are not eligible to play this game !!!!!";
				SetConsoleTextAttribute(color, 15);

				cout << "\nPlayer " << i << ":\n\t\tFirst Name :";
				cin >> name;
				cout << "\n\t\t Age :";
				cin >> age;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore();
					SetConsoleTextAttribute(color, 4);
					cout << "\n Age should be greater than 7. ";
					SetConsoleTextAttribute(color, 15);

				}
			}

		}
		else
		{
			Player newplayer(name, age);
			players.push_back(newplayer);

		}
	}
}
//pre-condition passing two called by reference parameters Card type vector and Player type team_of_players
//post-condition findout the winner of the game
void start_playUNO(vector<Card>& deckofcard, vector<Player>& team_of_players, HANDLE color)
{
	bool gameover = false;
	int round_count = 1;
	//vector<Player> t_players = team_of_players;
	
	do
	{
		//generateing the UNO card
		generate_deckofcard(deckofcard);


		//start to play round
		Round newround(team_of_players, deckofcard);


		//suffle the card
		newround.shuffle(round_count);

		//deal the cards for players 
		newround.assign_cards();

		//start the new round
		newround.start_game(round_count);

		team_of_players = newround.get_players();
		
		//assign total score to the player
		for (unsigned int i = 0; i < team_of_players.size(); i++)
		{
			vector<int> in_scores = team_of_players[i].get_scores();
			
			int tot_score = calculate_total_score(in_scores);
			team_of_players[i].assign_totalscore(tot_score);
		}


		//gameover
		gameover = find_gameover(team_of_players,color);
		
		if (!gameover)
		{
			//reset player
			reset_players(team_of_players);

			
			//reset deck 
			deckofcard.clear();
		}

		round_count++;
		

	} while (!gameover);

	
}
//pre-condition passing called by reference parameters Card type vector
//post-condition generateing a deck of cards
void generate_deckofcard(vector<Card>& deckofcard)
{
	
	ifstream in_stream;
	string colors,num;
	

	//open the input data file
	in_stream.open("cards.txt");
	
			
	if (!in_stream.fail())
	{
		while (!in_stream.eof())
		{
						
			in_stream >> colors;
			in_stream >> num;
			Card newcard(colors,num);
			deckofcard.push_back(newcard);
			
		}
	}
		
	else
	{
		cout << "Fail to open the file";
	}
	in_stream.close();
	
	

}

//pre-condition passing called by reference parameter Player type
//post-condition return boolean value
bool find_gameover(vector<Player> t_players, HANDLE color)
{

	unsigned int size = t_players.size();
	bool gameover = false;
	
	for (unsigned int i = 0; i < size; i++)
	{

		if (t_players[i].get_totalscore() >= 30)
		{
			gameover = true;
			cin.ignore();
			SetConsoleTextAttribute(color, 10);
			cout << "                           CONGRATULATIONS!!!! " << t_players[i].get_name();
			cout << " \n                        YOU WON THE GAME \n";
			SetConsoleTextAttribute(color, 15);

			break;
		}

	}
	
	return gameover;
}
//pre-condition passing called by reference parameter Player type
//post-condition erase the players cards for next round
void reset_players(vector<Player>& p)
{

	unsigned int size = p.size();
	for (unsigned int i = 0; i<size; i++)
	{

		p[i].reset_players();
	}
}
//pre-condition passing players scores as vector
//post-condition returning the total score of specific player
int calculate_total_score(vector<int> scores)
{
	
	int total_score(0);
	
	unsigned int size = scores.size();
	for (unsigned int i = 0; i < size; i++)
	{
		total_score += scores[i];
		
	}
	
	return total_score;
}
//pre-condition passing const vector in Card type
//post-condition display the vector of cards
void print_vector(const vector<Card>& t_deck)
{
	unsigned int size = t_deck.size();
	for (unsigned int i = 0; i<size; ++i)
	{
		cout << t_deck[i].tostring_card() << endl;

	}
	cout << endl;

}
//pre-condition passing  vector in Player type
//post-condition display the scores in the scores text file
void print_scores(vector<Player> players)
{
	vector<int> t_score;
	ofstream out_stream;
	unsigned int size_scores(0), size_players = players.size();
	
	//open the input data file
	out_stream.open("scores.txt");


	if (!out_stream.fail())
	{
		for (unsigned int i = 0; i < size_players; ++i)
		{

			out_stream << players[i].get_name() << " ";
			t_score = players[i].get_scores();
			size_scores = t_score.size();
			for (unsigned int j = 0; j < size_scores; j++)
			{

				out_stream << t_score[j] << " ";
					

			}
			out_stream << ": "<< players[i].get_totalscore() << endl;

		}

	}
	out_stream.close();
}
//pre-condition passing const vector in Player type
//post-condition display the Player object
void print_players(const vector<Player>& team_of_players)
{
	unsigned int size = team_of_players.size();
	for (unsigned int i = 0; i<size; ++i)
	{
		cout << team_of_players[i].tostring_player() << endl;

	}
	cout << endl;
}