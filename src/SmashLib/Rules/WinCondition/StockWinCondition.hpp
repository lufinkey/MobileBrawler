
#pragma once

#include "WinCondition.hpp"

namespace SmashLib
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
