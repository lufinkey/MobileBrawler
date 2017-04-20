
#pragma once

#include "WinCondition.hpp"

namespace BrawlerLibrary
{
	class StockWinCondition : public WinCondition
	{
	private:
		unsigned int stock;
	public:
		StockWinCondition();
		virtual ~StockWinCondition();
		
		void setStock(unsigned int stock);
		unsigned int getStock() const;
	};
}
