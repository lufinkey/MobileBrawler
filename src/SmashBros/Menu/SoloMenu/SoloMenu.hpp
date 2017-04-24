
#include "../Base/BaseMenuScreen.hpp"

namespace SmashBros
{
	namespace Menu
	{
		class SoloMenu : public BaseMenuScreen
		{
		public:
			explicit SoloMenu(const SmashData&smashData);
			virtual ~SoloMenu();

		private:
			MenuButton* trainingButton;
		};
	}
}
