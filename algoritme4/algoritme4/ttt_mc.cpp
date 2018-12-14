#include <iostream>
#include <algorithm>
#include <map>
#include "pch.h"

unsigned const n_trials = 1000;
unsigned const mc_match = 1;
unsigned const mc_other = 1;

enum class PlayerType { Human, Computer };

//to implement mctrial, board player
State mcTrial(const State &board)
{
	State trialboard = State(board);
	std::vector<Move> moves;
	std::vector<Move>::iterator move;

	while (1) {
		moves = getMoves(trialboard);

		if (moves.size() == 0) {
			return trialboard; //no more moves
		}

		do {
			moves = getMoves(trialboard);
			move = select_randomly<std::vector<Move>::iterator>(moves.begin(), moves.end()); //moves on the trial
		} while (trialboard[*move] != Player::None);

		trialboard = doMove(trialboard, *move);
	}
}

//to implement update scores, scores board player
void mcUpdateScores(std::array<int, 9> &scores, const State &board, const Player &player)
{
	State::const_iterator boardIte;
	size_t count = 0; //counter

	//if winner is player, score up player
	if (getWinner(board) == player) {
		for (boardIte = board.begin(); boardIte != board.end(); boardIte++) {
			if (*boardIte == Player::None);
			else if (*boardIte == player)
				scores[count] += mc_match;
			else
				scores[count] -= mc_other;
			count++; //increment score
		}
	}
	//else score up not player
	else {
		for (boardIte = board.begin(); boardIte != board.end(); boardIte++) {
			if (*boardIte == Player::None);
			else if (*boardIte == player)
				scores[count] -= mc_match;
			else
				scores[count] += mc_other;
			count++; //increment score
		}
	}
}

//to implement get best move, board scores
Move getBestMove(const std::array<int, 9> &scores, const State &board)
{
	int highScore = -999; //at 1000 trials, minus one
	Move highMove;
	State::const_iterator boardIte;
	std::array<int, 9>::const_iterator scoreIte = scores.begin();

	//loop through moves
	for (boardIte = board.begin(); boardIte != board.end(); boardIte++) {
		if (*scoreIte > highScore && *boardIte == Player::None) {
			highScore = *scoreIte;
			highMove = boardIte - board.begin(); //at which iteration
		}
		scoreIte++;
	}

	return highMove; //return the move with highest score
}

//to implement move, board player trials
Move mcMove(const State &board, const Player &player)
{
	//scores array for trial board
	std::array<int, 9> scoreboard = {
		0, 0, 0, 
		0, 0, 0,
		0, 0, 0
	};

	for (unsigned i = 0; i < n_trials; i++) {
		const State trialboard = mcTrial(board);
		mcUpdateScores(scoreboard, trialboard, player); //score updating
	}

	return getBestMove(scoreboard, board); //best move
}

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
			board = doMove(board, mcMove(board, getCurrentPlayer(board)));
		}
		std::cout << board << std::endl;
		moves = getMoves(board);
	}

	return 0;
}
