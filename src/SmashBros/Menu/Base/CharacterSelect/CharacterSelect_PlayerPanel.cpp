
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
				
				virtual void onMouseRelease(const ActorMouseEvent& evt) override
				{
					Vector2d touchpos;
					const ApplicationData& appData = evt.getApplicationData();
					TransformD mouseTransform = appData.getTransform().getInverse();
					if(Multitouch::isAvailable())
					{
						touchpos = mouseTransform.transform(Multitouch::getPreviousPosition(appData.getWindow(), evt.getMouseIndex()));
					}
					else
					{
						touchpos = mouseTransform.transform(Mouse::getPreviousPosition(appData.getWindow(), evt.getMouseIndex()));
					}
					
					bool doCycle = true;
					
					const ArrayList<PlayerChip*>& chips = charSelectScreen->getPlayerChips();
					for(size_t i=0; i<chips.size(); i++)
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
				portrait = nullptr;
				overlay = nullptr;
				namebox = nullptr;
				
				playerNum = pNum;
				charSelectScreen = screen;
				
				RectangleD frame = getFrame();
				
				addAnimation("human", new Animation(1, assetManager, (String)"characterselect/panel_background_p" + playerNum + ".png"));
				addAnimation("cpu", new Animation(1, assetManager, (String)"characterselect/panel_background_cpu.png"));
				addAnimation("na", new Animation(1, assetManager, (String)"characterselect/panel_background_na.png"));
				//addAnimation("blank", new Animation(1, assetManager, (String)"characterselect/panel_background_blank.png"));
				changeAnimation("na", Animation::FORWARD);
				
				portrait = new SpriteActor(x,y);
				portrait_anim = new Animation(1);
				portrait->addAnimation("default", portrait_anim);
				portrait->changeAnimation("default", Animation::FORWARD);
				portraitLayoutMgr.setOffsetByContainer(true);
				portraitLayoutMgr.setRule(LAYOUTRULE_LEFT,   0, LAYOUTVALUE_RATIO);
				portraitLayoutMgr.setRule(LAYOUTRULE_TOP,    0, LAYOUTVALUE_RATIO);
				portraitLayoutMgr.setRule(LAYOUTRULE_RIGHT,  1, LAYOUTVALUE_RATIO);
				portraitLayoutMgr.setRule(LAYOUTRULE_BOTTOM, 1, LAYOUTVALUE_RATIO);
				portrait->scaleToFit(portraitLayoutMgr.calculateFrame(portrait->getFrame(), frame));
				
				overlay = new SpriteActor(x,y);
				overlay->addAnimation("human", new Animation(1, assetManager, (String)"characterselect/panel_overlay_p" + playerNum + ".png"));
				overlay->addAnimation("cpu", new Animation(1, assetManager, "characterselect/panel_overlay_cpu.png"));
				overlay->addAnimation("na", new Animation(1, assetManager, "characterselect/panel_overlay_na.png"));
				//overlay->addAnimation("blank", new Animation(1, assetManager, "characterselect/panel_overlay_blank.png"));
				overlay->changeAnimation("na", Animation::FORWARD);
				overlayLayoutMgr.setOffsetByContainer(true);
				overlayLayoutMgr.setRule(LAYOUTRULE_LEFT,   0, LAYOUTVALUE_RATIO);
				overlayLayoutMgr.setRule(LAYOUTRULE_TOP,    0, LAYOUTVALUE_RATIO);
				overlayLayoutMgr.setRule(LAYOUTRULE_RIGHT,  1, LAYOUTVALUE_RATIO);
				overlayLayoutMgr.setRule(LAYOUTRULE_BOTTOM, 1, LAYOUTVALUE_RATIO);
				overlay->scaleToFit(overlayLayoutMgr.calculateFrame(overlay->getFrame(), frame));
				
				namebox = new TextActor(x, y, "", assetManager->getFont("fonts/default.ttf"), Color::BLACK, 36, Font::STYLE_PLAIN, TextActor::ALIGN_CENTER);
				nameboxLayoutMgr.setOffsetByContainer(true);
				nameboxLayoutMgr.setRule(LAYOUTRULE_LEFT,   0.320, LAYOUTVALUE_RATIO);
				nameboxLayoutMgr.setRule(LAYOUTRULE_TOP,    0.870, LAYOUTVALUE_RATIO);
				nameboxLayoutMgr.setRule(LAYOUTRULE_RIGHT,  0.910, LAYOUTVALUE_RATIO);
				nameboxLayoutMgr.setRule(LAYOUTRULE_BOTTOM, 0.981, LAYOUTVALUE_RATIO);
				namebox->scaleToFit(nameboxLayoutMgr.calculateFrame(namebox->getFrame(), frame));
				
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
				if(portrait!=nullptr)
				{
					portrait->scaleToFit(portraitLayoutMgr.calculateFrame(portrait->getFrame(), frame));
				}
				if(overlay!=nullptr)
				{
					overlay->scaleToFit(overlayLayoutMgr.calculateFrame(overlay->getFrame(), frame));
				}
				if(namebox!=nullptr)
				{
					namebox->scaleToFit(nameboxLayoutMgr.calculateFrame(namebox->getFrame(), frame));
				}
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
					applyPlacementDict(portraitDict.as<Dictionary>(false), &portraitLayoutMgr);
					if(!portraitLayoutMgr.hasRules())
					{
						portraitLayoutMgr.setRule(LAYOUTRULE_LEFT,   0, LAYOUTVALUE_RATIO);
						portraitLayoutMgr.setRule(LAYOUTRULE_TOP,    0, LAYOUTVALUE_RATIO);
						portraitLayoutMgr.setRule(LAYOUTRULE_RIGHT,  1, LAYOUTVALUE_RATIO);
						portraitLayoutMgr.setRule(LAYOUTRULE_BOTTOM, 1, LAYOUTVALUE_RATIO);
					}
				}
				const Any& overlayDict = properties.get("overlay");
				if(!overlayDict.empty() && overlayDict.is<Dictionary>())
				{
					applyPlacementDict(overlayDict.as<Dictionary>(false), &overlayLayoutMgr);
					if(!overlayLayoutMgr.hasRules())
					{
						overlayLayoutMgr.setRule(LAYOUTRULE_LEFT,   0, LAYOUTVALUE_RATIO);
						overlayLayoutMgr.setRule(LAYOUTRULE_TOP,    0, LAYOUTVALUE_RATIO);
						overlayLayoutMgr.setRule(LAYOUTRULE_RIGHT,  1, LAYOUTVALUE_RATIO);
						overlayLayoutMgr.setRule(LAYOUTRULE_BOTTOM, 1, LAYOUTVALUE_RATIO);
					}
				}
				const Any& nameboxDict = properties.get("namebox");
				if(!nameboxDict.empty() && nameboxDict.is<Dictionary>())
				{
					const Dictionary&namebox_dict = nameboxDict.as<Dictionary>(false);
					applyPlacementDict(nameboxDict, &nameboxLayoutMgr);
					if(!nameboxLayoutMgr.hasRules())
					{
						nameboxLayoutMgr.setRule(LAYOUTRULE_LEFT,   0.320, LAYOUTVALUE_RATIO);
						nameboxLayoutMgr.setRule(LAYOUTRULE_TOP,    0.870, LAYOUTVALUE_RATIO);
						nameboxLayoutMgr.setRule(LAYOUTRULE_RIGHT,  0.910, LAYOUTVALUE_RATIO);
						nameboxLayoutMgr.setRule(LAYOUTRULE_BOTTOM, 0.981, LAYOUTVALUE_RATIO);
					}
					
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
				updateSize();
			}
			
			void PlayerPanel::applyPlacementDict(const Dictionary&dict, AutoLayoutManager*layoutMgr)
			{
				const Any& layoutRules_any = dict.get("layoutRules");
				if(layoutRules_any.empty() || !layoutRules_any.is<Dictionary>())
				{
					return;
				}
				const Dictionary& layoutRules = layoutRules_any.as<Dictionary>(false);
				layoutMgr->setRules(layoutRules);
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
				for(size_t i=0; i<chips.size(); i++)
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
