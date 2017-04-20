
#pragma once

#include "ActionPerformer/ActionPerformer.h"

namespace BrawlerLibrary
{
	class BrawlGame;
	
	class GameObject : public ActionPerformer
	{
	public:
		GameObject(BrawlGame*gameInstance, const fgl::Vector2d&position);
		virtual ~GameObject();
		
		void setZDepth(double zdepth);
		double getZDepth() const;
		
	private:
		BrawlGame*gameInstance;
		double zdepth;
	};
}
