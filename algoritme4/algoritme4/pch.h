// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H

#include <tuple>
#include <array>
#include <vector>
#include <ctime>
#include <random>
#include <iterator>
#include <iostream>

enum class Player { X, O, None };
using Move = int;
using State = std::array<Player, 9>;

// used to get a random element from a container
template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
	std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
	std::advance(start, dis(g));
	return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	return select_randomly(start, end, gen);
}

std::ostream &operator<<(std::ostream &os, const State &state);
std::ostream &operator<<(std::ostream &os, const Player &player);

Player getCurrentPlayer(const State &state);
State doMove(const State &state, const Move &m);
Player getWinner(const State &state);
std::vector<Move> getMoves(const State &state);

// TODO: add headers that you want to pre-compile here

#endif //PCH_H
