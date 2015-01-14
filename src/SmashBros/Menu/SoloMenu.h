
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
			SoloMenu(const MenuData&menuData);
			virtual ~SoloMenu();
			
			virtual void onItemSelect(unsigned int index);
		};
	}
}