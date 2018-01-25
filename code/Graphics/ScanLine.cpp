#include "ScanLine.h"


ScanLine::ScanLine()
{
	boundList.resize(100); // Allocate 100
}

void ScanLine::clear()
{
	numBounds = 0; // To clear simply set the number of bounds to 0
}

void ScanLine::addBound(int min, int max)
{
	if(numBounds == 0) // There are no bounds so just insert the boundry
	{
		boundList[numBounds] = Bound(min, max);
		increaseNumBounds();
		return;
	}
	int indexMin1 = getBoundMinIndex(min);
	int indexMin2 = getBoundMaxIndex(min);

	int indexMax1 = getBoundMinIndex(max);
	int indexMax2 = getBoundMaxIndex(max);

	int indexMin = (indexMin1==indexMin2) ? indexMin1 : -1;
	int indexMax = (indexMax1==indexMax2) ? indexMax1 : -1;

	if(indexMin == indexMax && indexMin != -1 && indexMax != -1)
	{
		for(int i = numBounds; i > indexMin; i--)
		{
			boundList[i] = boundList[i-1];
		}
		boundList[indexMin] = Bound(min, max);
		increaseNumBounds();
	}
	else if(indexMin != -1 && indexMax != -1)
	{
		int diff = indexMax-indexMin;
		boundList[indexMin] = Bound(min, max);
		for(int i = indexMin+1; i < numBounds-1; i++)
		{
			boundList[i] = boundList[i+diff-1];
		}
		numBounds -= diff-1;
	}
	else
	{
		if(indexMin == -1 && indexMax != -1)
		{
			boundList[indexMin2].max = max;
			int diff = indexMax - indexMin2;
			for(int i = indexMin2+1; i < numBounds-1; i++)
			{
				boundList[i] = boundList[i+diff-1];
			}
			numBounds -= diff-1;
		}
		else if(indexMin != -1 && indexMax == -1)
		{
			boundList[indexMin] = Bound(min, boundList[indexMax2].max);
			int diff = indexMax1 - indexMin;
			for(int i = indexMin+1; i < numBounds-1; i++)
			{
				boundList[i] = boundList[i+diff-1];
			}
			numBounds -= diff-1;
		}
		else if(indexMin == -1 && indexMax == -1)
		{
			boundList[indexMin2].max = boundList[indexMax2].max;
			int diff = indexMax1 - indexMin2;
			for(int i = indexMin2+1; i < numBounds-1; i++)
			{
				if(i < numBounds)
				{
					boundList[i] = boundList[i+diff-1];
				}
			}
			numBounds -= diff-1;
		}
	}
}

int ScanLine::getMin(int index) const
{
	return boundList[index].min;
}

int ScanLine::getMax(int index) const
{
	return boundList[index].max;
}

int ScanLine::getNumberOfBounds() const
{
	return numBounds;
}

int ScanLine::getBoundMinIndex(int val) const
{
	for(int i = 0; i < numBounds; i++)
	{
		if(boundList[i].min > val)
		{
			return i;
		}
	}
	return numBounds;
}

int ScanLine::getBoundMaxIndex(int val) const
{
	for(int i = 0; i < numBounds; i++)
	{
		if(boundList[i].max >= val)
		{
			return i;
		}
	}
	return numBounds;
}

ScanLine::Bound::Bound(int min, int max) :
min(min), max(max)
{
}

void ScanLine::increaseNumBounds()
{
	numBounds++;
	if(numBounds >= boundList.size())
	{
		boundList.resize(boundList.size() + 100);
	}
}
