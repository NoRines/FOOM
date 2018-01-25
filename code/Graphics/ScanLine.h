#ifndef SCANLINE_H
#define SCANLINE_H

#include <vector>

//TODO: skriv om denna klass

class ScanLine
{
public:
	ScanLine();

	/// Clears all bounds from the scan line
	void clear();
	/// Adds a boundry to the scan line
	void addBound(int min, int max);

	/// Gets the min boudry from a index
	int getMin(int index) const;
	/// Gets the max boudry from a index
	int getMax(int index) const;

	/// Returns how many boundrys are stored in the object
	int getNumberOfBounds() const;

	int getBoundMinIndex(int val) const;
	int getBoundMaxIndex(int val) const;

private:
	struct Bound
	{
		Bound() = default;
		Bound(int min, int max);
		int min, max;
	};

	void increaseNumBounds();


	int numBounds = 0;
	std::vector<Bound> boundList;
};

#endif
