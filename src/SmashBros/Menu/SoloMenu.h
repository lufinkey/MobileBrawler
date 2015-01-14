
#include "BaseMenuScreen.h"

namespace SmashBros
{
	namespace Menu
	{
		class SoloMenu : public BaseMenuScreen
		{
		private:
			Actor* trainingButton;
			
		public:
			SoloMenu(AssetManager*assetManager);
			virtual ~SoloMenu();
			
			virtual void onItemSelect(unsigned int index);
		};
	}
}
