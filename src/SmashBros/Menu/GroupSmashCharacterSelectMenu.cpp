
#include "GroupSmashCharacterSelectMenu.h"

namespace SmashBros
{
	namespace Menu
	{
		GroupSmashCharacterSelectMenu::GroupSmashCharacterSelectMenu(const SmashData&smashData) : CharacterSelectScreen(smashData)
		{
			reloadIcons(smashData);
			reloadPlayerPanels(smashData);
		}
	}
}
