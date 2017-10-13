#pragma once

class Die {
	private:
		int _totalRollCount;
		int _occurenceCount[6]; //counts # of occurances for 1,2,3,4,5,6 ex: 1,2,1,4,0,3 means 1 occurance of 1 2 occurances of 2 1 occurance of 3 etc

		static bool _seededRand;

	public:
		Die();
		int roll();
		double getPercentageOccurence(int value);
};
