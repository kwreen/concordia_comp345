#include <iostream>
#include "Tournament.h"
#include "UserInterface.h"

Tournament::Tournament() {
	maps = UserInterface::selectTournamentMaps();
	players = UserInterface::selectTournamentComputerPlayers();
	G = UserInterface::selectTournamentGames();
	D = UserInterface::selectTournamentTurns();

	for (const auto& map : maps) {
		winners[map];
	}
}

void Tournament::startTournament() {
	for (const auto& map : maps) {
		for (int i = 0; i < G; ++i) {
			const auto winner = simulateGame(map);
			winners[map].push_back(winner);
		}
	}
}

void Tournament::displayWinners() {
	std::cout << "\n\nTournament results:\n";

	std::cout << "M: ";
	for (const auto& map : maps) {
		std::cout << map << ' ';
	}
	std::cout << std::endl;

	std::cout << "P: ";
	for (const auto& player : players) {
		switch (player.getIDAsInt()) {
		case 1:
			std::cout << "Aggressive ";
			break;
		case 2:
			std::cout << "Benevolent ";
			break;
		case 3:
			std::cout << "Random ";
			break;
		case 4:
			std::cout << "Cheater ";
		}
	}
	std::cout << std::endl;

	std::cout << "G: " << G << std::endl;
	std::cout << "D: " << D << std::endl << std::endl;

	std::cout << "                         ";
	for (int i = 0; i < G; ++i) {
		std::cout.width(15);
		std::cout << std::left << "Game " + std::to_string(i + 1);
	}
	std::cout << '\n';
	for (const auto& map : maps) {
		const auto mapWinners = winners[map];
		std::cout.width(25);
		std::cout << std::left << map;
		for (const auto& winner : mapWinners) {
			std::cout.width(15);
			std::cout << std::left << winner;
		}
		std::cout << '\n';
	}
}

std::string Tournament::simulateGame(const std::string& map) const {
	Game game("Resources/" + map, players);

	for (int i = 0; i < D; ++i) {
		if (game.getTurns().size() == 1) {
			const auto& player = game.getTurns()[0];
			switch (player.getIDAsInt()) {
				case 1:
					return "Aggressive";
				case 2:
					return "Benevolent";
				case 3:
					return "Random";
				case 4:
					return "Cheater";
				default:
					return "something is really wrong";
			}
		}
		for (auto& player : game.getTurns()) {
			if (!player.getCountries().empty()) {
				game.reinforcementPhase(player);
				game.attackPhase(player);
				game.fortificationPhase(player);
			}
		}
		game.removeDeadPlayers();
	}
	return "Draw";
}
