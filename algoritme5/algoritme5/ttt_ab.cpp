#include "pch.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <limits>

enum class PlayerType { Human, Computer };

#define MIN std::numeric_limits<int>::min() + 1 //min
#define MAX std::numeric_limits<int>::max() //max

using Rating = std::tuple<int, Move>; //rating of move
unsigned const n_trials = 1000; //number of trials

//get random
int getRandomEval(const State &board, Player) {
	return rand() % 101 - 50;
}

//eval, board player
int eval(const State &board, const Player &player)
{
	auto moves = getMoves(board);
	int wins = 0;

	for (int i = 0; i < n_trials; ++i) {
		State mcBoard = board;

		std::random_shuffle(moves.begin(), moves.end()); //do shuffle
		for (const Move &m : moves) mcBoard = doMove(mcBoard, m);

		if (getWinner(mcBoard) == player) wins++; //count up
	}

	return wins - n_trials / 2; //number trials divide by 2,  2 players
}

//rating ab i of move, add min max parameters
Rating alphaBeta(const State &board, int ply, Player player, int min = MIN, int max = MAX) {
	auto moves = getMoves(board);
	Rating bestRating = std::make_tuple(min, Move());

	if (!ply || !moves.size()) return std::make_tuple(eval(board, player), Move());

	for (Move &m : moves) {
		Rating rating;
		Player other = player == Player::O ? Player::X : Player::O;

		rating = alphaBeta(doMove(board, m), ply - 1, other, -max, -min);

		if (-std::get<0>(rating) > min) {
			min = -std::get<0>(rating);
			bestRating = std::make_tuple(min, m);
		}

		if (min >= max) return bestRating;
	}

	return bestRating;
}

/*
//move,
Move alphaBeta(const State &board, int ply)
{
	auto moves = getMoves(board);
	Rating bestRating = std::make_tuple(min, Move());

	if (!ply || !moves.size()) return std::make_tuple(eval(board, player), Move());

	for (Move &m : moves) {
		Rating rating;
		Player other = player == Player::O ? Player::X : Player::O;

		rating = alphaBeta(doMove(board, m), ply - 1, other, -max, -min);

		if (-std::get<0>(rating) > min) {
			min = -std::get<0>(rating);
			bestRating = std::make_tuple(min, m);
		}

		if (min >= max) return bestRating;
	}

	return bestRating;
}
*/

int main()
{
	std::srand(std::time(0));

	std::map<Player, PlayerType> playerType;
	playerType[Player::X] = PlayerType::Human;
	playerType[Player::O] = PlayerType::Computer;

	State board = {
		Player::None, Player::None, Player::None,
		Player::None, Player::None, Player::None,
		Player::None, Player::None, Player::None };
	std::cout << board << std::endl;

	std::vector<Move> moves = getMoves(board);
	while (moves.size() > 0) {
		if (playerType[getCurrentPlayer(board)] == PlayerType::Human) {
			std::cout << "+-+-+-+" << std::endl <<
				"|0|1|2|" << std::endl <<
				"+-+-+-+" << std::endl <<
				"|3|4|5|" << std::endl <<
				"+-+-+-+" << std::endl <<
				"|6|7|8|" << std::endl <<
				"+-+-+-+" << std::endl << std::endl;
			std::cout << "Enter a move ( ";
			for (Move m : moves) std::cout << m << " ";
			std::cout << "): ";
			Move m;
			std::cin >> m;
			board = doMove(board, m);
		}
		else {
			board = doMove(board, alphaBeta(board, 5));
		}
		std::cout << board << std::endl;
		moves = getMoves(board);
	}

	return 0;
}