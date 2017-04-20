
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
			class ReadyToFightBanner;
		}
		
		class CharacterSelectScreen : public BaseMenuScreen
		{
			friend class CharacterSelect::PlayerChip;
		public:
			CharacterSelectScreen(const SmashData&smashData, Rules*rules);
			virtual ~CharacterSelectScreen();
			
			virtual void onSizeChange(const Vector2d& oldSize, const Vector2d& newSize) override;
			
			virtual bool isReadyToFight() const;
			virtual void proceedToFight();
			
			Rules* getRules() const;
			CharacterLoader* getCharacterLoader() const;
			const ArrayList<CharacterSelect::PlayerChip*>& getPlayerChips() const;
			const ArrayList<CharacterSelect::CharacterIcon*>& getCharacterIcons() const;
			
		protected:
			void reloadIcons(const SmashData&smashData);
			void reloadPlayerPanels(const SmashData&smashData);

			virtual void onUpdate(const ApplicationData& appData) override;
			virtual void onDraw(const ApplicationData& appData, Graphics graphics) const override;
			
		private:
			void whenPlayerChipGrabbed(unsigned int playerNum);
			void whenPlayerChipReleased(unsigned int playerNum);
			void whenPlayerCharacterChanges(unsigned int playerNum, CharacterInfo*characterInfo);

			Rules*rules;
			CharacterLoader* characterLoader;
			ArrayList<CharacterSelect::CharacterIcon*> icons;
			ArrayList<CharacterSelect::PlayerPanel*> panels;
			ArrayList<CharacterSelect::PlayerChip*> chips;
			CharacterSelect::ReadyToFightBanner* readyToFightBanner;
		};
	}
}
