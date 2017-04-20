
#include "PhysicalGameObject.h"
#include "../../Loader/CharacterInfo.h"

namespace BrawlerLibrary
{
	class Character : public PhysicalGameObject
	{
	public:
		Character(BrawlGame*gameInstance, const CharacterInfo&info, const fgl::Vector2d&position);
		virtual ~Character();
		
		virtual void update(fgl::ApplicationData appData) override;
		virtual void draw(fgl::ApplicationData appData, fgl::Graphics graphics) const override;
	};
}
