#include <iostream>
#include "Tournament.h"
#include "UserInterface.h"

Tournament::Tournament() {
	maps = UserInterface::selectTournamentMaps();
	players = UserInterface::selectTournamentComputerPlayers();
	G = UserInterface::selectTournamentGames();
	D = UserInterface::selectTournamentTurns();

	for (const auto& map : maps) {
		winners[map] = std::vector<std::string>();
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
	for (int i = 0; i < G; ++i) {
		std::cout << "Game " << i << " ";
	}
	std::cout << '\n';
	for (const auto& map : maps) {
		const auto mapWinners = winners[map];
		for (const auto& winner : mapWinners) {
			std::cout << winner << ' ';
		}
		std::cout << '\n';
	}
}

std::string Tournament::simulateGame(const std::string& map) const {
	Game game(map, players);

	for (int i = 0; i < D; ++i) {
		if (game.getTurns().size() == 1) {
			const auto& player = game.getTurns()[0];
			switch (i) {
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
			game.removeDeadPlayers();
		}
	}
	return "Draw";
}
