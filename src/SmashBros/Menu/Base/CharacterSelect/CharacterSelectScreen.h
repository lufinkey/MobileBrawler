
#pragma once

#include "../BaseMenuScreen.h"
#include "../../Elements/ActorGrid.h"

namespace SmashBros
{
	namespace Menu
	{
		namespace CharacterSelect
		{
			class CharacterIcon;
			class PlayerChip;
			class PlayerPanel;
		}
		
		class CharacterSelectScreen : public BaseMenuScreen
		{
			friend class CharacterSelect::PlayerChip;
		public:
			CharacterSelectScreen(const SmashData&smashData);
			virtual ~CharacterSelectScreen();
			
			Rules* getRules() const;
			CharacterLoader* getCharacterLoader() const;
			
		protected:
			void reloadIcons(const SmashData&smashData);
			void reloadPlayerPanels(const SmashData&smashData);

			virtual void updateItems(ApplicationData appData);
			virtual void drawItems(ApplicationData appData, Graphics graphics) const;
			
		private:
			
			void whenPlayerCharacterChanges(unsigned int playerNum, CharacterInfo*characterInfo);

			Rules*rules;
			CharacterLoader* characterLoader;
			RectangleF iconGridFrame;
			ActorGrid*iconGrid;
			ArrayList<CharacterSelect::CharacterIcon*> icons;
			ArrayList<CharacterSelect::PlayerPanel*> panels;
			ArrayList<CharacterSelect::PlayerChip*> chips;
		};
	}
}
