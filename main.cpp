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

int moveProtocol(Client &client, std::string &message_list, Game &game1, Game &game2, int &success1, int &success2, std::string OPPONENT_ID)
{
	std::string message_to_send;
	std::string message;
	values_t message_info;
	Adapter adapter;
	int runTime = 3;
	Tile tmpTile;

	message = getMesssage(client, message_list);

	if (success1 == -1 || success2 == -1 && message.compare(0,1,"M") == 0)
		runTime = 2;
	else if (success1 == -1 || success2 == -1 && message.compare(0,1,"G") == 0)
		runTime = 1;
	else if (success1 == -1 && success2 == -1)
		runTime = 0;

	for (int i = 0; i < runTime; i++)
	{
		if (message.compare(0,1,"M") == 0)
		{
			std::cout<<"SERVER ASKING FOR A MOVE"<<std::endl;
			message_info = adapter.translate(message);
			if (game1.getID() == "")
				game1.setID(message_info.gameId);
			if (message_info.gameId == game1.getID())
			{
				std::cout << "sent our move for tile: " << message_info.tile_num <<  " and game: " << message_info.gameId << std::endl;
				tmpTile = Tile(message_info.tile_num);
				message_to_send = game1.makeMove(tmpTile);
			}
			else if (message_info.gameId == game2.getID())
			{
				std::cout << "sent our move for tile: " << message_info.tile_num <<  " and game: " << message_info.gameId << std::endl;
				tmpTile = Tile(message_info.tile_num);
				message_to_send = game2.makeMove(tmpTile);
			}
			client.sendMessage(message_to_send);
			message = getMesssage(client, message_list);
		}
		else if (message.compare(0,1,"G") == 0)
		{
			std::cout << "GAME MOVES INFORMATION" << std::endl;
			message_info = adapter.translate(message);
			if (message_info.gameId != game1.getID() && game2.getID() == "")
				game2.setID(message_info.gameId);
			if (message_info.forfeit == -1)
			{
				if (game2.getID() == message_info.gameId)
					success2 = -1;
				else if (game1.getID() == message_info.gameId)
					success1 = -1;
			}
			else
			{
				if (message_info.playerId == OPPONENT_ID)
				{
					tmpTile = Tile(message_info.tile_num);
					int i = message_info.coordinates.first;
					int j = message_info.coordinates.second;
					int orientation = message_info.rotation;

					if (message_info.gameId == game1.getID())
					{
						std::cout << "received opponent move for tile: " << message_info.tile_num <<  " and game: " << message_info.gameId << std::endl;
						std::cout << "tile placed at <" << i << ", " << j << "> :" << "with rotation: " << orientation << std::endl;
						std::cout << "croc? " << message_info.croc << "tiger? " << message_info.tiger << "zone " << "[" <<message_info.tiger_spot.first << ", " << message_info.tiger_spot.second << "] " << std::endl;
						tmpTile = Tile(message_info.tile_num);
						game1.enemyMove(tmpTile, i, j, orientation, message_info.tiger, message_info.croc, message_info.tiger_spot);
					}
					else if (message_info.gameId == game2.getID())
					{
						std::cout << "received opponent move for tile: " << message_info.tile_num <<  " and game: " << message_info.gameId << std::endl;
						std::cout << "tile placed at <" << i << ", " << j << "> :" << "with rotation: " << orientation << std::endl;
						std::cout << "croc? " << message_info.croc << "tiger? " << message_info.tiger << "zone " << "[" <<message_info.tiger_spot.first << ", " << message_info.tiger_spot.second << "] " << std::endl;
						tmpTile = Tile(message_info.tile_num);
						std::cout << "DEBUG FLAG" << std::endl; 
						game2.enemyMove(tmpTile, i, j, orientation, message_info.tiger, message_info.croc, message_info.tiger_spot);
						std::cout << "DEBUG FLAG 2" << std::endl; 
					}
				}
			}
			if (i < runTime-1)
				message = getMesssage(client, message_list);
		}
	}
}

void matchProtocol(Client &client, std::string &message_list)
{
	Adapter adapter;
	values_t message_info;
	int number_of_tiles, game1_success, game2_success;
	int count = 0;
	bool lastMessage = true;
	std::string OPPONENT_ID;
	std::string message = getMesssage(client, message_list);
	Tile tile1;
	TileStack tStack;

	while (lastMessage) //while Game is not over
	{
		if (message.compare(0,1,"Y") == 0) //getting opponent player id
		{
			std::cout << "OPPONENT PLAYER INFO" << std::endl;
			//message_info = adapter.translate(message);
			//OPPONENT_ID = message_info.playerId; 					//use opponent player id
			OPPONENT_ID = message.substr(24, std::string::npos-24);
			std::cout << "Opponent ID is: " << OPPONENT_ID << std::endl;
			message = getMesssage(client, message_list);
		}
		else if (message.compare(0,1,"S") == 0) //getting starting tile information
		{
			std::cout << "STARTING TILE INFO: " << message << std::endl;
			message_info = adapter.translate(message);
			tile1 = Tile(message_info.tile_num); //getting first tile
			message = getMesssage(client, message_list);
		}
		else if (message.compare(0,1,"T") == 0) //get tile stack
		{
			std::cout << "TILE STACK INFO" << std::endl;
			message_info = adapter.translate(message);
			number_of_tiles = message_info.number_of_tiles; //gettting the number of tiles
			tStack = TileStack(message_info.tile_stack); //getting tile stack
			message = getMesssage(client, message_list);
		}
		else if (message.compare(0,1,"M") == 0)
		{
			std::cout << "MATCH BEGINS SOON" << std::endl;
			message_info = adapter.translate(message);
			//use planning time
			Player ai, opponent;
			Game game1("", ai, opponent, tStack, tile1, std::pair<int,int> (72,72));
			Game game2("", opponent, ai, tStack, tile1, std::pair<int,int> (72,72));
			for (int i = 0; i < number_of_tiles; i++)
			{
				std::cout<<"Running moveProtocol first time."<<std::endl;
				moveProtocol(client, message_list, game1, game2, game1_success, game2_success, OPPONENT_ID); //client, message_list, game1 and game2
				if (game1_success == -1 && game2_success == -1)	break;				//move must return a value to break from for loop in case of forfeit
				//std::cout<<"Running moveProtocol second time."<<std::endl;
				//moveProtocol(client, message_list, game1, game2, game1_success, game2_success); //client, message_list, game1 and game2
			}
			message = getMesssage(client, message_list);
		}
		else if (message.compare(0,1,"G") != 0)
		{
			count++;
			if (count == 2)
				lastMessage = false;
			else
				message = getMesssage(client, message_list);
		}
		else //hopefully this is never reached
		{
			std::cout << "ERROR: previous message could not be processed correctly. Message skipped!" << std::endl;
			std::cout << "	ERROR message: " << message << std::endl;
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
			std::cout << "BEGINNING ROUND..." << std::endl;
			round_id = stoi(message.substr(12,message.find(" OF")-12));
			matchProtocol(client, message_list); // pass message reference
			message = getMesssage(client, message_list);
		}
		else if (message.compare(0,1,"E") == 0) //waiting for the next round to begin
		{
			std::cout << "END OF ROUND...WAITING FOR THE NEXT MATCH" << std::endl;
			message = getMesssage(client, message_list);
		}
		else //hopefully this is never reached
		{
			std::cout << "ERROR: previous message could not be processed correctly. Message skiped!" << std::endl;
			std::cout << "	ERROR message: " << message << std::endl;
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
				std::cout << "challenge id is: " << challenge_id << " and playing " << rounds << " rounds" << std::endl;
				roundProtocol(client, message_list, rounds); //pass message reference
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
			std::cout << "ERROR: previous message could not be processed correctly. Message skipped!" << std::endl;
			std::cout << "	ERROR message: " << message << std::endl;
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
	serverConnection.connectToServer();


	Tile tile1(19);
	Player p1;
	Player p2;
	TileStack tStack;
	tStack.shuffle();

	PLAYER_ID = authenticationProtocol(serverConnection, TOURNAMENT_PASS, TEAM_ID, TEAM_PASSWORD);
	std::cout << "Player id returned is: " << PLAYER_ID << std::endl;
	challengeProtocol(serverConnection);
	serverConnection.closeConnection();

	//Game game1("123", p1, p2, tStack, tile1, std::pair<int,int> (72,72));
	//game1.play();

	return 0;
};
