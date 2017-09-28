#pragma once

class Dice {
	private:
		int _totalRollCount;
		int _occurenceCount[6];

		static bool _seededRand;

	public:
		Dice();
		int roll();
		double getPercentageOccurence(int value);
};