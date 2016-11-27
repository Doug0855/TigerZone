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

void moveProtocol()
{

}


void matchProtocol(Client &client, std::string &message_list)
{
	std::string opponent_id, starting_tile, substr;
	int x, y, orientation;
	if (message_list.empty())
	{
		message_list = client.receiveMessage();
		message = parseMessageList(message_list);
	}
	else message = parseMessageList(message_list);

	while (message.compare(0,1,"G") != 0) //while Game is not over
	{
		if (message.compare(0,1,"Y") == 0) //getting opponent player id
		{
			opponent_id = message.substr(23,message.end()));
			if (message_list.empty())
			{
				message_list = client.receiveMessage();
				message = parseMessageList(message_list);
			}
			else message = parseMessageList(message_list);
		}
		else if (message.compare(0,1,"S") == 0) //getting starting tile information
		{
			starting_tile = message.substr(17, message.find(" AT")-17);
			substr = message.substr(message.find("AT ")+3,message.find(" ", message.find("AT ")+3, 1)-message.find("AT ")-3);
			x = stoi(substr);
			y = stoi(message.substr());
			orientation = stoi(message.substr());
			//place starting tile
			if (message_list.empty())
			{
				message_list = client.receiveMessage();
				message = parseMessageList(message_list);
			}
			else message = parseMessageList(message_list);
		}
		else if (message.compare(0,1,"E") == 0) //waiting for the next round to begin
		{
			if (message_list.empty())
			{
				message_list = client.receiveMessage();
				message = parseMessageList(message_list);
			}
			else message = parseMessageList(message_list);
		}
		else //hopefully this is never reached
		{
			std::cout << "ERROR: previous message could not be processed correctly. Message skiped!" << std::endl;
			if (message_list.empty())
			{
				message_list = client.receiveMessage();
				message = parseMessageList(message_list);
			}
			else message = parseMessageList(message_list);
		}
	}

}

void roundProtocol(Client &client, std::string &message_list, int rounds)
{
	int round_id;
	std:string TERMINATE_ROUND = "END OF ROUND " + rounds + " OF " + rounds;
	if (message_list.empty())
	{
		message_list = client.receiveMessage();
		message = parseMessageList(message_list);
	}
	else message = parseMessageList(message_list);

	while (message != TERMINATE_ROUND)
	{
		if (message.compare(0,1,"B") == 0) //executing a new round
		{
			round_id = stoi(message.substr(12,message.find(" OF")-12));
			//matchProtocol(); // pass message reference
			if (message_list.empty())
			{
				message_list = client.receiveMessage();
				message = parseMessageList(message_list);
			}
			else message = parseMessageList(message_list);
		}
		else if (message.compare(0,1,"E") == 0) //waiting for the next round to begin
		{
			if (message_list.empty())
			{
				message_list = client.receiveMessage();
				message = parseMessageList(message_list);
			}
			else message = parseMessageList(message_list);
		}
		else //hopefully this is never reached
		{
			std::cout << "ERROR: previous message could not be processed correctly. Message skiped!" << std::endl;
			if (message_list.empty())
			{
				message_list = client.receiveMessage();
				message = parseMessageList(message_list);
			}
			else message = parseMessageList(message_list);
		}
	}
}

void challengeProtocol(Client &client)
{
	int challenge_id, rounds;
	std::string message, message_list;
	message_list = client.receiveMessage();
	message = parseMessageList(message_list);
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
			if (message_list.empty())
			{
				message_list = client.receiveMessage();
				message = parseMessageList(message_list);
			}
			else message = parseMessageList(message_list);
		}
		else if (message.compare(0,1,"P") == 0)	//waiting for the next challenge to begin
		{
			std::cout << "waiting for the next challenge to begin" << std::endl;
			if (message_list.empty())
			{
				message_list = client.receiveMessage();
				message = parseMessageList(message_list);
			}
			else message = parseMessageList(message_list);
		}
		else //hopefully this is never reached
		{
			std::cout << "ERROR: previous message could not be processed correctly. Message skiped!" << std::endl;
			if (message_list.empty())
			{
				message_list = client.receiveMessage();
				message = parseMessageList(message_list);
			}
			else message = parseMessageList(message_list);
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
	serverConnection.connectToServer();
	//serverConnection.sendMessage("Hello World!");
	//std::cout << serverConnection.receiveMessage() << std::endl;
	//std::cout << serverConnection.receiveMessage() << std::endl;
	//serverConnection.closeConnection();
	Tile tile1(19);
	Player p1;
	Player p2;
	TileStack tStack;
	tStack.shuffle();

	PLAYER_ID = authenticationProtocol(serverConnection, TOURNAMENT_PASS, TEAM_ID, TEAM_PASSWORD);
	std::cout << "Player id returned is: " << PLAYER_ID << std::endl;
	challengeProtocol(serverConnection);

	// std::string message, player_id;
	// message = "WELCOME <pid> PLEASE WAIT FOR THE NEXT CHALLENGE\r\n";
	// // player_id = message.substr(8,message.find(" PLEASE")-8);
	// // std::cout << "Player id returned is: " << player_id << " " << message.find(" PLEASE") << std::endl;
	// std::cout << "Comparison is: " << message.compare(0,1,"W") << std::endl;



	//Game game1("123", p1, p2, tStack, tile1, std::pair<int,int> (72,72));
	//game1.play();


	//printBoard(game1.gameboard);

	return 0;
};
