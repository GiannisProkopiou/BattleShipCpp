#include "Game.h"
#include "AdjacentTilesException.h"
#include "OverlapTilesException.h"
#include "OversizeException.h"
#include "Player.h"
#include "Carrier.h"
#include "Battleship.h"
#include "Cruiser.h"
#include "Submarine.h"
#include "Destroyer.h"
#include "Ship.h"
#include "dir.h"
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <exception>

using namespace std;

void Game::main(vector<string> &args) throw(OversizeException, OverlapTilesException, AdjacentTilesException)
{
	Player *user = new Player();
	Player *computer = new Player();
	computer->playersBoard->setHidden(true);

	cout << "\n - JAVA BATTLESHIP - \n ** Glarakis George - Papadias Epameinondas - Prokipiou John ** \n CEID: 2nd Semester: Object Oriented Programming: Project 2018" << endl;
	system("pause");

	cout << "Let's START!" << endl;
	if (randomPlace())
	{
		user->placeAllShips();
		user->playersBoard->drawboards(computer->playersBoard);
	}
	else
	{
		user->playersBoard->drawboards(computer->playersBoard);
		manualPlace(user, computer);
	}

	computer->placeAllShips();

	int shots = 0;
	bool GameOver = false;
	while (!GameOver && shots < 30)
	{
		cout << "\nMake a hit:" << endl;

		vector<int> coords = getInput();
		cout << "You: ";
		user->fire(computer->playersBoard, coords);

		vector<int> randCoords = getRandInput();
		cout << "Computer: ";
		computer->fire(user->playersBoard, randCoords);

		user->playersBoard->drawboards(computer->playersBoard);

		if (user->playersBoard->allShipsSunk() || computer->playersBoard->allShipsSunk())
		{
			GameOver = true;
		}

		shots++;
	}

	if (computer->playersBoard->allShipsSunk())
	{
		cout << "!!!YOU WIN!!!" << endl;
	}
	else if (user->playersBoard->allShipsSunk())
	{
		cout << "!!!YOU LOSE!!!" << endl;
	}
	else if (shots == 30)
	{
		cout << "!!!YOU ARE OUT OF AMMO. YOU LOSE!!!" << endl;
	}

	cout << "Game Stats:" << endl;
	user->getStats();
}

vector<int> Game::getInput()
{
	vector<int> coord;
	coord = vector<int>(2);
	bool in = true;
	while (in)
	{
		cout << endl;
		cout << "Give the coordinates of the ship(Y / X): ";

		try
		{
			cin >> coord[0] >> coord[1];
			in = false;
		}
		catch (exception ex)
		{
			cout << "Coordinates given are not valid!" << endl;
			in = true;
		}

		if (coord[0] > 6 || coord[0] < 0 || coord[1] > 6 || coord[1] < 0)
		{
			cout << "Coordinates given are not valid!" << endl;
			in = true;
		}
	}
	return coord;
}

vector<int> Game::getRandInput()
{
	vector<int> coord;
	coord = vector<int>(2);

	coord[0] = int (rand() % 7);
	coord[1] = int (rand() % 7);

	return coord;
}

dir Game::getOrientation()
{
	bool orient;
	while (true)
	{
		cout << endl;
		cout << "Give the orientation of the ship." << endl;
		cout << "Press H for Horizontal or V for Vertical: ";
		char a;
		cin >> a;

		if (a == 'H' || a == 'h')
		{
			orient = true;
			break;
		}
		else if (a == 'V' || a == 'v')
		{
			orient = false;
			break;
		}
		else
		{
			cout << "Not valid answer." << endl;
		}
	}
	if (orient)
	{
		return dir::horizontal;
	}
	else
	{
		return dir::vertical;
	}
}

bool Game::randomPlace()
{
	bool answer;
	while (true)
	{
		cout << endl;
		cout << "Do you want random placement of the ships?" << endl;
		cout << "Press Y for Yes or N for No: ";
		char ans;
		cin >> ans;

		if (ans == 'Y' || ans == 'y')
		{
			answer = true;
			break;
		}
		else if (ans == 'N' || ans == 'n')
		{
			answer = false;
			break;
		}
		else
		{
			cout << "Not valid answer." << endl;
		}
	}
	if (answer)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Game::manualPlace(Player *p1, Player *p2)
{
		Carrier *carrier = new Carrier(0, 0, dir::horizontal);
		Battleship *battleship = new Battleship(0, 0, dir::horizontal);
		Cruiser *cruiser = new Cruiser(0, 0, dir::horizontal);
		Submarine *submarine = new Submarine(0, 0, dir::horizontal);
		Destroyer *destroyer = new Destroyer(0, 0, dir::horizontal);

		vector<Ship*> myships;

		myships.push_back(carrier);
		myships.push_back(battleship);
		myships.push_back(cruiser);
		myships.push_back(submarine);
		myships.push_back(destroyer);

		int shipCell = 0;
		int j = 5;
		for (int i = 0; i < 5; i++)
		{
			cout << endl;
			cout << "Your ships:" << endl;
			int k = 1;
			for (auto sh : myships)
			{
				cout << k << ". " << myships[k - 1] << endl;
				k++;
			}

			while (true)
			{
				cout << "Choose a ship to place: ";
				cin >> shipCell;
				if (shipCell > j)
				{
					cout << "Please select one of the given numbers." << endl;
				}
				else
				{
					break;
				}
			}

			bool shipDone = false;
			while (!shipDone)
			{
				vector<int> coords = getInput();

				try
				{
					p1->placeShip(myships[shipCell - 1], coords[0], coords[1], getOrientation());
					shipDone = true;
				}
				catch (OversizeException ex1)
				{
					cout << "\n" << ex1.getmessage() << endl;
				}
				catch (OverlapTilesException ex2)
				{
					cout << "\n" << ex2.getmessage() << endl;
				}
				catch (AdjacentTilesException ex3)
				{
					cout << "\n" << ex3.getmessage() << endl;
				}

				p1->playersBoard->drawboards(p2->playersBoard);
			}
			myships.erase(myships.begin() + shipCell - 1);
			j--;
		}
}



