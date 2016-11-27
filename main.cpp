#include <iostream>
#include <utility>
#include <fstream>
#include <iomanip>

#include "Tile_Structure/Tile.h"
#include "Tile_Structure/Block.h"
#include "Tile_Structure/Face.h"
#include "Tile_Structure/TileStack.h"
#include "Network.h"
//#include "Meeple.h"
#include "Game.h"
#include "Board.h"
#include "Adapter.h"
//#include "Network.h"

#define WHITE   "\033[37m"      /* White */
#define BLUE    "\033[34m"      /* Blue */
#define GREEN   "\033[32m"      /* Green */
#define RED     "\033[31m"      /* Red */
#define BLACK   "\033[30m"      /* Black */
#define RESET   "\033[0m"       /* Reset */
#define BOLD    "\033[1m"       /* Bold */
#define INVERT  "\033[7m"       /* Invert */

#define TERMINATE_CHALLENGE "END OF CHALLENGES"


void printToTextFile(Board gameboard)
{
	std::ofstream out_data("Levels/level.txt");
	out_data << "Level:" << std::endl;
	for (auto& inner : gameboard.m_board)
	{
		for (auto& item : inner)
		{
			if (item != NULL)
				out_data << item->getRotations() << item->getType();
			else
				out_data << '0' << '.';

		}
		out_data << std::endl;
	}
	out_data.close();
}
void printBoard(Board gameBoard) //debugging
{
	std::cout<<"in print board"<<std::endl;
	// Print out gameboard
	std::cout << "size of gameBoard is: " << gameBoard.m_board.size() << " x " << gameBoard.m_board[0].size() << std::endl;
	for(int i = 0; i < gameBoard.m_board.size(); i++)
	{
		std::cout << std::setw(3) << i << ' ';
		for(int j = 0; j < gameBoard.m_board[i].size(); j++)
		{
				if (gameBoard.m_board[i][j] != NULL)
					std::cout << GREEN <<  gameBoard.m_board[i][j]->getRotations() << gameBoard.m_board[i][j]->getType() << WHITE << RESET;
				else
					std::cout << std::setw(2) << '.';
		}
		std::cout<<std::endl;
	}
} 															//debug
void printStack(TileStack stack) //debugging
{
	/*print tile stack content for debugging*/
	std::cout << "TileStack content(" << stack.tiles.size() << "): ";
	for(int i = 0; i < stack.tiles.size(); i++) {
		Tile tile = stack.tiles[i];
		std::cout << tile.getType() << ' ';
	}
	std::cout << std::endl;/**/
}

std::string parseMessageList(std::string &msg)
{
	std::string token;
	std::string delimiter = "\r\n";
	size_t pos = 0;

	pos = msg.find(delimiter);
	token = msg.substr(0, pos);
	msg.erase(0, pos + delimiter.length());

	return token;
}
std::string getMesssage(Client &client, std::string &msg_list)
{
	std::string msg;
	if (msg_list.empty())
	{
		msg_list = client.receiveMessage();
		msg = parseMessageList(msg_list);
	}
	else msg = parseMessageList(msg_list);
	return msg;
}

int moveProtocol(Client &client, std::string &mesagge_list, Game &game1, Game &game2)
{
	std::string message_to_send;
	values_t message_info;

	message = getMesssage(client, message_list);

	if (message.compare(0,1,"M") == 0)
	{
		message_info = adapter.translate(message);
		if (!game1.hasID())
			game1.setID(message_info.gameId);
		//message_to_send = game1.getMove();
		client.sendMessage(message_to_send);
		message = getMesssage(client, message_list);
	}
	else if (message.compare(0,1,"G") == 0)
	{
		message_info = adapter.translate(message);
		if (message_info.tile_num == -1)
		{
			return -1;
		}
	}
}

void matchProtocol(Client &client, std::string &message_list)
{
	Adapter adapter;
	values_t message_info;
	int number_of_tiles, success;
	message = getMesssage(client, message_list);
	Tile tile1;
	TileStack tStack;

	while (message.compare(0,1,"G") != 0) //while Game is not over
	{
		if (message.compare(0,1,"Y") == 0) //getting opponent player id
		{
			message_info = adapter.translate(message);
			//use opponent player id
			message = getMesssage(client, message_list);
		}
		else if (message.compare(0,1,"S") == 0) //getting starting tile information
		{
			message_info = adapter.translate(message);
			tile1 = Tile(message_info.tile_num); //getting first tile
			message = getMesssage(client, message_list);
		}
		else if (message.compare(0,1,"T") == 0) //get tile stack
		{
			message_info = adapter.translate(message);
			number_of_tiles = message_info.number_of_tiles; //gettting the number of tiles
			tStack = TileStack(message_info.tile_stack); //getting tile stack
			message = getMesssage(client, message_list);
		}
		else if (message.compare(0,1,"M") == 0)
		{
			message_info = adapter.translate(message);
			//use planning time
			Player ai, opponent;
			Game game1("", ai, opponent, tStack, tile1, std::pair<int,int> (72,72));
			Game game2("", opponent, ai, tStack, tile1, std::pair<int,int> (72,72));
			for (int i = 0; i < number_of_tiles; i++)
			{
				success = moveProtocol(client, message_list, game1, game2,) //client, message_list, game1 and game2
				if (success == -1)					//move must return a value to break from for loop in case of forfeit
					break;
			}
			message = getMesssage(client, message_list);
		}
		else //hopefully this is never reached
		{
			std::cout << "ERROR: previous message could not be processed correctly. Message skiped!" << std::endl;
			message = getMesssage(client, message_list);
		}
	}
}

void roundProtocol(Client &client, std::string &message_list, int rounds)
{
	int round_id;
	std::string message;
	std::string TERMINATE_ROUND = "END OF ROUND " + std::to_string(rounds) + " OF " + std::to_string(rounds);
	message = getMesssage(client, message_list);

	while (message != TERMINATE_ROUND)
	{
		if (message.compare(0,1,"B") == 0) //executing a new round
		{
			round_id = stoi(message.substr(12,message.find(" OF")-12));
			//matchProtocol(); // pass message reference
			message = getMesssage(client, message_list);
		}
		else if (message.compare(0,1,"E") == 0) //waiting for the next round to begin
		{
			message = getMesssage(client, message_list);
		}
		else //hopefully this is never reached
		{
			std::cout << "ERROR: previous message could not be processed correctly. Message skiped!" << std::endl;
			message = getMesssage(client, message_list);
		}
	}
}

void challengeProtocol(Client &client)
{
	int challenge_id, rounds;
	std::string message;
	std::string message_list = "";
	message = getMesssage(client, message_list);
	while (message != TERMINATE_CHALLENGE)
	{
		if (message.compare(0,1,"N") == 0) //executing a new challenge
		{
			challenge_id = stoi(message.substr(14,message.find(" YOU")-14));
			rounds = stoi(message.substr(message.find("PLAY")+5,message.find(" MATCH")-message.find("PLAY")-5));
			for (int i = 0; i < rounds; i++)
			{
				//roundProtocol(); //pass message reference
				//std::cout << "challenge id is: " << challenge_id << " and playing " << rounds << " rounds" << std::endl;
			}
			message = getMesssage(client, message_list);
		}
		else if (message.compare(0,1,"P") == 0)	//waiting for the next challenge to begin
		{
			std::cout << "waiting for the next challenge to begin" << std::endl;
			message = getMesssage(client, message_list);
		}
		else //hopefully this is never reached
		{
			std::cout << "ERROR: previous message could not be processed correctly. Message skiped!" << std::endl;
			message = getMesssage(client, message_list);
		}
	}
}

std::string authenticationProtocol(Client &client, std::string tournament_password, std::string username, std::string password)
{
	std::string message;
	std::string player_id;
	message = client.receiveMessage();
	if ( message == "THIS IS SPARTA!\r\n") //message to send tournament password
	{
		message = "JOIN " + tournament_password + '\r' + '\n';
		client.sendMessage(message);
	}
	else
	{
		std::cout << "ERROR: first message from server is: " << message;
		client.sendMessage("FAIL");
	}
	message = client.receiveMessage();
	if ( message == "HELLO!\r\n") //message to send team username and password
	{
		message = "I AM " + username + " " + password + '\r' + '\n';
		client.sendMessage(message);
	}
	else
	{
		std::cout << "ERROR: second message from server is: " << message;
		client.sendMessage("FAIL");
	}
	message = client.receiveMessage(); //last authentication message giving player id back
	player_id = message.substr(8,message.find(" PLEASE")-8);
	return player_id;
}

int main(int argc, char *argv[]) {
	std::string SERVER_IP, PORT, TOURNAMENT_PASS, TEAM_ID, TEAM_PASSWORD;
	if( argc == 6 ) {
		SERVER_IP = argv[1];
		PORT = argv[2];
		TOURNAMENT_PASS = argv[3];
		TEAM_ID = argv[4];
		TEAM_PASSWORD = argv[5];
	}
	else if( argc > 6 ) {
		printf("Too many arguments supplied.\n");
		exit (EXIT_FAILURE);
	}
	else {
		printf("Five arguments expected.\n");
		exit (EXIT_FAILURE);
	}
	std::string PLAYER_ID;
	std::cout<<"in game"<<std::endl;
	Board gameboard;
	Client serverConnection(SERVER_IP, PORT);
	//serverConnection.connectToServer();
	//serverConnection.sendMessage("Hello World!");
	//std::cout << serverConnection.receiveMessage() << std::endl;
	//std::cout << serverConnection.receiveMessage() << std::endl;
	//serverConnection.closeConnection();
	Tile tile1(19);
	Player p1;
	Player p2;
	TileStack tStack;
	tStack.shuffle();

	//PLAYER_ID = authenticationProtocol(serverConnection, TOURNAMENT_PASS, TEAM_ID, TEAM_PASSWORD);
	//std::cout << "Player id returned is: " << PLAYER_ID << std::endl;
	//challengeProtocol(serverConnection);


		// if (message.compare(0,1,"Y") == 0) //getting opponent player id
		// {
		// 	//opponent_id = message.substr(23,message.end()));
		// 	message = getMesssage(client, message_list);
		// }
		// else if (message.compare(0,1,"S") == 0) //getting starting tile information
		// {
		// 	starting_tile = message.substr(17, message.find(" AT")-17); //get string where tile description starts until before " AT"
		// 	substr = message.substr(message.find("AT ")+3,message.find(" ", message.find("AT ")+3, 1)-message.find("AT ")-3); //get first string integer
		// 	x = stoi(substr);
		// 	substr = message.erase(0, message.find(substr) + substr.length() + 1); //get string with last two integers
		// 	y = stoi(substr.substr(0,substr.find(" ")));
		// 	substr = substr.erase(0,substr.find(" ")+1); //get string with last int
		// 	substr = substr.substr(0,std::string::npos); //get the last integer
		// 	orientation = stoi(substr);
		// 	std::cout << "starting tile <" << starting_tile << "> at <" << x << ", " << y << ", " << orientation <<std::endl;
		// 	//place starting tile
		// 	message = getMesssage(client, message_list);
		// }
		// else if (message.compare(0,1,"T") == 0) //get tile stack
		// {




	//Game game1("123", p1, p2, tStack, tile1, std::pair<int,int> (72,72));
	//game1.play();


	//printBoard(game1.gameboard);
	// std::string token;
	// std::string delimiter = "\r\n";
	// size_t pos = 0;
	//
	// pos = msg.find(delimiter);
	// token = msg.substr(0, pos);
	// msg.erase(0, pos + delimiter.length());
	return 0;
};
