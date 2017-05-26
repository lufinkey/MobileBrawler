
#pragma once

#include "../BaseMenuScreen.hpp"
#include <SmashBros/Game/Rules/Rules.hpp>

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
			CharacterSelectScreen(MenuData* menuData, Rules* rules);
			virtual ~CharacterSelectScreen();
			
			virtual bool isReadyToFight() const;
			virtual void proceedToFight();
			
			Rules* getRules() const;
			const fgl::ArrayList<CharacterSelect::PlayerChip*>& getPlayerChips() const;
			const fgl::ArrayList<CharacterSelect::CharacterIcon*>& getCharacterIcons() const;
			
		protected:
			void reloadCharacters();
			void reloadPlayers();

			virtual void onUpdate(const fgl::ApplicationData& appData) override;
			
		private:
			void handlePlayerChipGrabbed(size_t playerIndex);
			void handlePlayerChipReleased(size_t playerIndex);
			void handlePlayerCharacterChanged(size_t playerIndex, const fgl::String& characterIdentifier);

			Rules* rules;

			fgl::ArrayList<CharacterSelect::CharacterIcon*> icons;
			fgl::ArrayList<CharacterSelect::PlayerPanel*> panels;
			fgl::ArrayList<CharacterSelect::PlayerChip*> chips;

			fgl::ScreenElement* iconsElement;
			fgl::ScreenElement* panelsElement;
			fgl::ScreenElement* chipsElement;

			CharacterSelect::ReadyToFightBanner* readyToFightBanner;
		};
	}
}
