
#pragma once

#include "WinCondition.hpp"

namespace SmashBros
{
	class StockWinCondition : public WinCondition
	{
	public:
		StockWinCondition();
		virtual ~StockWinCondition();
		
		void setStock(unsigned int stock);
		unsigned int getStock() const;

	private:
		unsigned int stock;
	};
}
