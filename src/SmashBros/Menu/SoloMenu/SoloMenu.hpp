
#include "../Base/BaseMenuScreen.hpp"

namespace SmashBros
{
	namespace Menu
	{
		class SoloMenu : public BaseMenuScreen
		{
		private:
			Actor* trainingButton;
			
		public:
			explicit SoloMenu(const SmashData&smashData);
			virtual ~SoloMenu();
			
			virtual void onItemSelect(size_t index) override;
		};
	}
}
