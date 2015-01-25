
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

				PlayerPanel_ModeTapRegion(PlayerPanel*playerPanel, CharacterSelectScreen*screen, float x, float y, float width, float height) : WireframeActor(x, y, width, height)
				{
					panel = playerPanel;
					charSelectScreen = screen;
				}
				
				virtual void onMouseRelease(ApplicationData appData, unsigned int touchID) override
				{
					Vector2f touchpos;
					Transform mouseTransform = appData.getTransform().getInverse();
					if(Multitouch::isEnabled())
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
			
			PlayerPanel::PlayerPanel(unsigned int pNum, CharacterSelectScreen*screen, float x, float y, const Dictionary&placementDict, AssetManager*assetManager) : SpriteActor(x, y)
			{
				playerNum = pNum;
				charSelectScreen = screen;
				
				addAnimation("human", new Animation(1, assetManager, (String)"characterselect/panel_background_p" + playerNum + ".png"));
				addAnimation("cpu", new Animation(1, assetManager, (String)"characterselect/panel_background_cpu.png"));
				addAnimation("na", new Animation(1, assetManager, (String)"characterselect/panel_background_na.png"));
				//addAnimation("blank", new Animation(1, assetManager, (String)"characterselect/panel_background_blank.png"));
				changeAnimation("na", Animation::FORWARD);
				
				portrait = new SpriteActor(x,y);
				portrait_anim = new Animation(1);
				portrait->addAnimation("default", portrait_anim);
				portrait->changeAnimation("default", Animation::FORWARD);
				
				overlay = new SpriteActor(x,y);
				overlay->addAnimation("human", new Animation(1, assetManager, (String)"characterselect/panel_overlay_p" + playerNum + ".png"));
				overlay->addAnimation("cpu", new Animation(1, assetManager, "characterselect/panel_overlay_cpu.png"));
				overlay->addAnimation("na", new Animation(1, assetManager, "characterselect/panel_overlay_na.png"));
				//overlay->addAnimation("blank", new Animation(1, assetManager, "characterselect/panel_overlay_blank.png"));
				overlay->changeAnimation("na", Animation::FORWARD);
				
				namebox = new TextActor(x, y, "", assetManager->getFont("fonts/default.ttf"), Color::BLACK, 36, Font::STYLE_PLAIN, TextActor::ALIGN_CENTER);

				tapRegion_mode = new PlayerPanel_ModeTapRegion(this, charSelectScreen);
				tapRegion_mode->setVisible(false);
			}
			
			PlayerPanel::~PlayerPanel()
			{
				delete namebox;
				delete overlay;
				delete portrait;
				delete tapRegion_mode;
			}
			
			void PlayerPanel::applyPlacementProperties(const Dictionary&placementDict)
			{
				const Any& portraitDict = placementDict.get("portrait");
				if(!portraitDict.empty() && portraitDict.is<Dictionary>())
				{
					applyPlacementDict(&portrait_bounds, portraitDict.as<Dictionary>(false));
				}
				const Any& overlayDict = placementDict.get("overlay");
				if(!overlayDict.empty() && overlayDict.is<Dictionary>())
				{
					applyPlacementDict(&overlay_bounds, overlayDict.as<Dictionary>(false));
				}
				const Any& nameboxDict = placementDict.get("namebox");
				if(!nameboxDict.empty() && nameboxDict.is<Dictionary>())
				{
					const Dictionary&namebox_dict = nameboxDict.as<Dictionary>(false);
					applyPlacementDict(&namebox_bounds, nameboxDict);
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
			
			void PlayerPanel::applyPlacementDict(RectF*bounds, const Dictionary&dict)
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
					bounds->left = left_val.as<Number>(false).asFloat();
				}
				if(!top_val.empty() && top_val.is<Number>())
				{
					bounds->top = top_val.as<Number>(false).asFloat();
				}
				if(!right_val.empty() && right_val.is<Number>())
				{
					bounds->right = right_val.as<Number>(false).asFloat();
				}
				if(!bottom_val.empty() && bottom_val.is<Number>())
				{
					bounds->bottom = bottom_val.as<Number>(false).asFloat();
				}
			}
			
			RectangleF PlayerPanel::getPlacementFrame(const RectangleF&container, const RectF&bounds)
			{
				Vector2f overlay_topleft(bounds.left*container.width, bounds.top*container.height);
				Vector2f overlay_bottomright(bounds.right*container.width, bounds.bottom*container.height);
				return RectangleF(container.x+overlay_topleft.x, container.y+overlay_topleft.y, overlay_bottomright.x-overlay_topleft.x, overlay_bottomright.y-overlay_topleft.y);
			}
			
			void PlayerPanel::update(ApplicationData appData)
			{
				SpriteActor::update(appData);
				
				RectangleF frame = getFrame();
				
				tapRegion_mode->x = frame.x;
				tapRegion_mode->y = frame.y;
				tapRegion_mode->setSize(frame.width, frame.height);
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
				
				RectangleF portrait_frame = getPlacementFrame(frame, portrait_bounds);
				portrait->scaleToFit(portrait_frame);
				portrait->update(appData);
				
				RectangleF overlay_frame = getPlacementFrame(frame, overlay_bounds);
				overlay->scaleToFit(overlay_frame);
				overlay->update(appData);
				
				RectangleF namebox_frame = getPlacementFrame(frame, namebox_bounds);
				namebox->scaleToFit(namebox_frame);
				namebox->update(appData);
				
				const ArrayList<PlayerChip*>& chips = charSelectScreen->getPlayerChips();
				for(unsigned int i=0; i<chips.size(); i++)
				{
					PlayerChip* chip = chips.get(i);
					if(chip->getPlayerNum() == playerNum)
					{
						if(chip->isDragging())
						{
							portrait->setAlpha(0.5f);
						}
						else
						{
							portrait->setAlpha(1.0f);
						}
						i = chips.size();
					}
				}
			}
			
			void PlayerPanel::draw(ApplicationData appData, Graphics graphics) const
			{
				SpriteActor::draw(appData, graphics);
				
				RectangleF frame = getFrame();
				
				RectangleF portrait_frame = getPlacementFrame(frame, portrait_bounds);
				portrait->scaleToFit(portrait_frame);
				portrait->draw(appData, graphics);
				
				RectangleF overlay_frame = getPlacementFrame(frame, overlay_bounds);
				overlay->scaleToFit(overlay_frame);
				overlay->draw(appData, graphics);
				
				RectangleF namebox_frame = getPlacementFrame(frame, namebox_bounds);
				namebox->scaleToFit(namebox_frame);
				namebox->draw(appData, graphics);
				
				tapRegion_mode->x = frame.x;
				tapRegion_mode->y = frame.y;
				tapRegion_mode->setSize(frame.width, frame.height);
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
			}
		}
	}
}
