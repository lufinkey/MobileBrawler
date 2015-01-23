
#include "Base/BaseMenuScreen.h"
#include "GroupSmashCharacterSelectMenu.h"

namespace SmashBros
{
	namespace Menu
	{
		class SoloMenu : public BaseMenuScreen
		{
		private:
			Actor* trainingButton;
            GroupSmashCharacterSelectMenu *smashMenu;
			
		public:
			SoloMenu(const SmashData&smashData);
			virtual ~SoloMenu();
			
			virtual void onItemSelect(unsigned int index);
		};
	}
}
