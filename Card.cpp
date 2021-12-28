
#include "Card.h"

//default constructor with empty parameter
Card::Card()
{

}
//to create Card of object with parameters
Card::Card(string t_color, string t_number)
{
	color = t_color;
	number = t_number;
}

//This method returns the color of the card
string Card::get_color() const
{
	return color;
}
//This method returns number from the card
string Card::get_number() const
{
	return number;
}
//To set the color/suit of the card
void Card::set_color(string t_color)
{
	color = t_color;
	cout << "color: " << color << "\n";
}
//To set the number to the card
void Card::set_number(string t_number)
{
	number = t_number;
}
//This method returns string formate of this object
string Card::tostring_card() const
{
	string card;
	card = "Card{" + get_color() + "," + get_number() + "}";
	return card;
}