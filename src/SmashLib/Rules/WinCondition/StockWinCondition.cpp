
#include "StockWinCondition.hpp"

namespace SmashLib
{
	StockWinCondition::StockWinCondition()
	{
		stock = 3;
	}
	
	StockWinCondition::~StockWinCondition()
	{
		//
	}
	
	void StockWinCondition::setStock(unsigned int stockNum)
	{
		stock = stockNum;
	}
	
	unsigned int StockWinCondition::getStock() const
	{
		return stock;
	}
}
