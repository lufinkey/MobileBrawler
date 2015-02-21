
#include "CharacterSelect_PlayerPanel.h"
#include "CharacterSelectScreen.h"
#include "CharacterSelect_PlayerChip.h"

namespace SmashBros
{
	namespace Menu
	{
		namespace CharacterSelect
		{
			class PlayerPanel_ModeTapRegion : public WireframeActor
			{
			private:
				PlayerPanel* panel;
				CharacterSelectScreen* charSelectScreen;
				
			public:
				PlayerPanel_ModeTapRegion(PlayerPanel*playerPanel, CharacterSelectScreen*screen) : WireframeActor()
				{
					panel = playerPanel;
					charSelectScreen = screen;
				}

				PlayerPanel_ModeTapRegion(PlayerPanel*playerPanel, CharacterSelectScreen*screen, double x, double y, double width, double height) : WireframeActor(x, y, width, height)
				{
					panel = playerPanel;
					charSelectScreen = screen;
				}
				
				virtual void onMouseRelease(ApplicationData appData, unsigned int touchID) override
				{
					Vector2d touchpos;
					TransformD mouseTransform = appData.getTransform().getInverse();
					if(Multitouch::isAvailable())
					{
						touchpos = mouseTransform.transform(Multitouch::getPreviousPosition(appData.getWindow(), touchID));
					}
					else
					{
						touchpos = mouseTransform.transform(Mouse::getPreviousPosition(appData.getWindow(), touchID));
					}
					
					bool doCycle = true;
					
					const ArrayList<PlayerChip*>& chips = charSelectScreen->getPlayerChips();
					for(unsigned int i=0; i<chips.size(); i++)
					{
						PlayerChip* chip = chips.get(i);
						if(chip->checkPointCollision(touchpos))
						{
							doCycle = false;
							i = chips.size();
						}
					}
					
					if(doCycle)
					{
						PlayerInfo& info = charSelectScreen->getRules()->getPlayerInfo(panel->getPlayerNum());
						info.cyclePlayerMode();
					}
				}
			};
			
			PlayerPanel::PlayerPanel(unsigned int pNum, CharacterSelectScreen*screen, double x, double y, const Dictionary&properties, AssetManager*assetManager)
				: SpriteActor(x, y)
			{
				tapRegion_mode = nullptr;
				
				playerNum = pNum;
				charSelectScreen = screen;
				
				addAnimation("human", new Animation(1, assetManager, (String)"characterselect/panel_background_p" + playerNum + ".png"));
				addAnimation("cpu", new Animation(1, assetManager, (String)"characterselect/panel_background_cpu.png"));
				addAnimation("na", new Animation(1, assetManager, (String)"characterselect/panel_background_na.png"));
				//addAnimation("blank", new Animation(1, assetManager, (String)"characterselect/panel_background_blank.png"));
				changeAnimation("na", Animation::FORWARD);
				
				autoLayout.setFrame(getFrame());
				
				portrait = new SpriteActor(x,y);
				portrait_anim = new Animation(1);
				portrait->addAnimation("default", portrait_anim);
				portrait->changeAnimation("default", Animation::FORWARD);
				autoLayout.add(RectD(0,0,1,1), portrait);
				
				overlay = new SpriteActor(x,y);
				overlay->addAnimation("human", new Animation(1, assetManager, (String)"characterselect/panel_overlay_p" + playerNum + ".png"));
				overlay->addAnimation("cpu", new Animation(1, assetManager, "characterselect/panel_overlay_cpu.png"));
				overlay->addAnimation("na", new Animation(1, assetManager, "characterselect/panel_overlay_na.png"));
				//overlay->addAnimation("blank", new Animation(1, assetManager, "characterselect/panel_overlay_blank.png"));
				overlay->changeAnimation("na", Animation::FORWARD);
				autoLayout.add(RectD(0,0,1,1), overlay);
				
				namebox = new TextActor(x, y, "", assetManager->getFont("fonts/default.ttf"), Color::BLACK, 36, Font::STYLE_PLAIN, TextActor::ALIGN_CENTER);
				autoLayout.add(RectD(0.32, 0.87, 0.91, 0.981), namebox);
				
				tapRegion_mode = new PlayerPanel_ModeTapRegion(this, charSelectScreen);
				tapRegion_mode->setVisible(false);
				
				applyProperties(properties);
			}
			
			PlayerPanel::~PlayerPanel()
			{
				delete namebox;
				delete overlay;
				delete portrait;
				delete tapRegion_mode;
			}
			
			void PlayerPanel::updateSize()
			{
				SpriteActor::updateSize();
				
				RectangleD frame = getFrame();
				autoLayout.setFrame(frame);
				if(tapRegion_mode!=nullptr)
				{
					tapRegion_mode->x = frame.x;
					tapRegion_mode->y = frame.y;
					tapRegion_mode->setSize(frame.width, frame.height);
				}
			}
			
			void PlayerPanel::applyProperties(const Dictionary&properties)
			{
				const Any& portraitDict = properties.get("portrait");
				if(!portraitDict.empty() && portraitDict.is<Dictionary>())
				{
					RectD portrait_bounds = autoLayout.get(portrait);
					applyPlacementDict(&portrait_bounds, portraitDict.as<Dictionary>(false));
					autoLayout.set(portrait, portrait_bounds);
				}
				const Any& overlayDict = properties.get("overlay");
				if(!overlayDict.empty() && overlayDict.is<Dictionary>())
				{
					RectD overlay_bounds = autoLayout.get(overlay);
					applyPlacementDict(&overlay_bounds, overlayDict.as<Dictionary>(false));
					autoLayout.set(overlay, overlay_bounds);
				}
				const Any& nameboxDict = properties.get("namebox");
				if(!nameboxDict.empty() && nameboxDict.is<Dictionary>())
				{
					RectD namebox_bounds = autoLayout.get(namebox);
					const Dictionary&namebox_dict = nameboxDict.as<Dictionary>(false);
					applyPlacementDict(&namebox_bounds, nameboxDict);
					autoLayout.set(namebox, namebox_bounds);
					
					/*const Any& alignment_val = namebox_dict.get("alignment");
					if(!alignment_val.empty() && alignment_val.is<String>())
					{
						String alignment = alignment_val.as<String>(false);
						if(alignment.equals("center"))
						{
							namebox->setAlignment(TextActor::ALIGN_CENTER);
						}
						else if(alignment.equals("bottomleft"))
						{
							namebox->setAlignment(TextActor::ALIGN_BOTTOMLEFT);
						}
						else if(alignment.equals("bottomright"))
						{
							namebox->setAlignment(TextActor::ALIGN_BOTTOMRIGHT);
						}
						else if(alignment.equals("topleft"))
						{
							namebox->setAlignment(TextActor::ALIGN_TOPLEFT);
						}
						else if(alignment.equals("topright"))
						{
							namebox->setAlignment(TextActor::ALIGN_TOPRIGHT);
						}
					}*/
					
					const Any& color_val = namebox_dict.get("color");
					if(!color_val.empty() && color_val.is<Dictionary>())
					{
						const Dictionary& color_dict = color_val.as<Dictionary>(false);
						const Any& r_val = color_dict.get("r");
						const Any& g_val = color_dict.get("g");
						const Any& b_val = color_dict.get("b");
						const Any& a_val = color_dict.get("a");
						Color color = namebox->getColor();
						if(!r_val.empty() && r_val.is<Number>())
						{
							color.r = r_val.as<Number>(false).asUnsignedChar();
						}
						if(!g_val.empty() && g_val.is<Number>())
						{
							color.g = g_val.as<Number>(false).asUnsignedChar();
						}
						if(!b_val.empty() && b_val.is<Number>())
						{
							color.b = b_val.as<Number>(false).asUnsignedChar();
						}
						if(!a_val.empty() && a_val.is<Number>())
						{
							color.a = a_val.as<Number>(false).asUnsignedChar();
						}
						namebox->setColor(color);
					}
				}
			}
			
			void PlayerPanel::applyPlacementDict(RectD*bounds, const Dictionary&dict)
			{
				if(bounds == nullptr)
				{
					return;
				}
				
				const Any& left_val = dict.get("left");
				const Any& top_val = dict.get("top");
				const Any& right_val = dict.get("right");
				const Any& bottom_val = dict.get("bottom");
				if(!left_val.empty() && left_val.is<Number>())
				{
					bounds->left = left_val.as<Number>(false).asDouble();
				}
				if(!top_val.empty() && top_val.is<Number>())
				{
					bounds->top = top_val.as<Number>(false).asDouble();
				}
				if(!right_val.empty() && right_val.is<Number>())
				{
					bounds->right = right_val.as<Number>(false).asDouble();
				}
				if(!bottom_val.empty() && bottom_val.is<Number>())
				{
					bounds->bottom = bottom_val.as<Number>(false).asDouble();
				}
			}
			
			void PlayerPanel::update(ApplicationData appData)
			{
				SpriteActor::update(appData);
				
				tapRegion_mode->update(appData);
				
				PlayerInfo& playerInfo = charSelectScreen->getRules()->getPlayerInfo(playerNum);
				switch(playerInfo.getPlayerMode())
				{
					case PlayerInfo::MODE_OFF:
					changeAnimation("na", Animation::NO_CHANGE);
					overlay->changeAnimation("na", Animation::NO_CHANGE);
					break;
					
					case PlayerInfo::MODE_HUMAN:
					changeAnimation("human", Animation::NO_CHANGE);
					overlay->changeAnimation("human", Animation::NO_CHANGE);
					break;
					
					case PlayerInfo::MODE_CPU:
					changeAnimation("cpu", Animation::NO_CHANGE);
					overlay->changeAnimation("cpu", Animation::NO_CHANGE);
					break;
				}
				
				portrait->update(appData);
				overlay->update(appData);
				namebox->update(appData);
				
				const ArrayList<PlayerChip*>& chips = charSelectScreen->getPlayerChips();
				for(unsigned int i=0; i<chips.size(); i++)
				{
					PlayerChip* chip = chips.get(i);
					if(chip->getPlayerNum() == playerNum)
					{
						if(chip->isDragging())
						{
							portrait->setAlpha(0.5);
						}
						else
						{
							portrait->setAlpha(1.0);
						}
						i = chips.size();
					}
				}
			}
			
			void PlayerPanel::draw(ApplicationData appData, Graphics graphics) const
			{
				SpriteActor::draw(appData, graphics);
				portrait->draw(appData, graphics);
				overlay->draw(appData, graphics);
				namebox->draw(appData, graphics);
				tapRegion_mode->draw(appData, graphics);
			}
			
			unsigned int PlayerPanel::getPlayerNum() const
			{
				return playerNum;
			}
			
			void PlayerPanel::applyCharacterInfo(CharacterInfo*characterInfo)
			{
				if(characterInfo == nullptr)
				{
					namebox->setText("");
					portrait_anim->clear();
					portrait->updateSize();
				}
				else
				{
					namebox->setText(characterInfo->getName());
					portrait_anim->clear();
					AssetManager* characterAssetMgr = charSelectScreen->getCharacterLoader()->getAssetManager();
					//TODO change portrait path when implementing costumes
					String portraitPath = characterInfo->getPath() + "/portrait.png";
					portrait_anim->addFrame(characterAssetMgr, portraitPath);
					portrait->updateSize();
				}
				updateSize();
			}
		}
	}
}
