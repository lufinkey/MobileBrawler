
#include "Base/BaseMenuScreen.h"

namespace SmashBros
{
	namespace Menu
	{
		class SoloMenu : public BaseMenuScreen
		{
		private:
			Actor* trainingButton;
			
		public:
			SoloMenu(const SmashData&smashData);
			virtual ~SoloMenu();
			
			virtual void onItemSelect(unsigned int index) override;
		};
	}
}
