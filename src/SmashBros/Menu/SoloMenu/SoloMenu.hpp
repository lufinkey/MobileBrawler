
#include "../Base/BaseMenuScreen.hpp"

namespace SmashBros
{
	namespace Menu
	{
		class SoloMenu : public BaseMenuScreen
		{
		public:
			explicit SoloMenu(MenuData* menuData);
			virtual ~SoloMenu();

		private:
			MenuButton* trainingButton;
		};
	}
}
