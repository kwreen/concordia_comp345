#include "CheaterPlayer.h"
#include "Game.h"

// Doubles armies on all countries
void CheaterPlayer::reinforcement(Player* playerptr) {
	Player& player = *playerptr;
	
	for (auto& c : player.getCountries()) {
		c.increaseArmiesBy(c.getArmies());
		std::cout << "Cheater Player has reinforced " << c.getName() << " that now has " << c.getArmies() << " armies." << std::endl;
	}
}

// Conquers all neighbours of all its countries
void CheaterPlayer::attack(Player* playerptr) {
	Player& attacker = *playerptr;
	std::vector<Country> attackingCountries = Game::checkAvailableAttackingCountriesToAttack(attacker);

	if (attackingCountries.size() > 0) {
		for (auto& attackingCountry : attacker.getCountries()) {
			for (auto& aCountry : attackingCountries) {
				if (attackingCountry.getName() == aCountry.getName()) {
					std::vector<Country> defendingCountries = Game::checkAvailableDefendingCountriesToAttack(attacker, attackingCountry);

					for (auto& dCountry : defendingCountries) {
						Player& defender = Game::getOwner(dCountry);

						for (auto& defendingCountry : defender.getCountries()) {
							if (defendingCountry.getName() == dCountry.getName()) {
								std::cout << "Cheater Player uses " << attackingCountry.getName() << " to attack Defender on " << defendingCountry.getName() << std::endl;
								std::cout << std::endl;

								// Moving ONE army from attacking country to defending country
								// Giving defeated country to attacker
								defendingCountry.increaseArmiesBy(1);
								attacker.getCountries().push_back(Country(defendingCountry));

								std::cout << defendingCountry.getName() << " has been defeated. Cheater Player has moved 1 army to the newly conquered country." << std::endl;

								// Removing defeated country from defender
								const auto pos = std::find(defender.getCountries().begin(), defender.getCountries().end(), defendingCountry);
								defender.getCountries().erase(pos);
							}
						}
					}
				}
			}
		}
	}
	else {
		std::cout << "No available country found for Cheater Player to attack." << std::endl;
	}
}

// Doubles the number of armies on its countries that have neighbours that belong to other players
void CheaterPlayer::fortify(Player* playerptr) {
	Player& player = *playerptr;
	std::vector<Country> countriesToFortify = Game::checkAvailableCountriesToFortifyForCheater(player);

	for (auto& c : player.getCountries()) {
		for (auto& country : countriesToFortify) {
			if (c.getName() == country.getName()) {
				c.increaseArmiesBy(c.getArmies());
				std::cout << "Cheater Player has fortified " << c.getName() << " that now has " << c.getArmies() << " armies." << std::endl;
			}
		}
	}
}