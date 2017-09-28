#pragma once

class Die {
	private:
		int _totalRollCount;
		int _occurenceCount[6];

		static bool _seededRand;

	public:
		Die();
		int roll();
		double getPercentageOccurence(int value);
};