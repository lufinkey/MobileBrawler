
#include "PhysicalGameObject.h"
#include "../../Loader/CharacterInfo.h"

namespace BrawlerLibrary
{
	class Character : public PhysicalGameObject
	{
	public:
		Character(BrawlGame*gameInstance, const CharacterInfo&info, const GameLibrary::Vector2d&position);
		virtual ~Character();
		
		virtual void update(GameLibrary::ApplicationData appData) override;
		virtual void draw(GameLibrary::ApplicationData appData, GameLibrary::Graphics graphics) const override;
	};
}
