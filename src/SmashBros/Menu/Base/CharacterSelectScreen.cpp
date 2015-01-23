
#include "CharacterSelectScreen.h"

namespace SmashBros
{
	namespace Menu
	{
//CharacterIcon
		CharacterSelectScreen::CharacterIcon::CharacterIcon(CharacterInfo&characterInfo, float x, float y, AssetManager*assetManager) : SpriteActor(x,y)
		{
			info = &characterInfo;
			String icon_path = characterInfo.getPath() + "/icon.png";
			addAnimation("default", new Animation(1, assetManager, icon_path));
			changeAnimation("default", Animation::FORWARD);
		}
		
		CharacterSelectScreen::CharacterIcon::~CharacterIcon()
		{
			//
		}
		
		bool CharacterSelectScreen::CharacterIcon::equals(const CharacterIcon&icon) const
		{
			if(info->getName().equals(icon.info->getName()) && info->getCreator().equals(icon.info->getCreator()))
			{
				return true;
			}
			return false;
		}
		
		const String& CharacterSelectScreen::CharacterIcon::getName() const
		{
			return info->getName();
		}
		
		const String& CharacterSelectScreen::CharacterIcon::getCreator() const
		{
			return info->getCreator();
		}
		
		CharacterInfo* CharacterSelectScreen::CharacterIcon::getCharacterInfo() const
		{
			return info;
		}
		
//PlayerPanel
		CharacterSelectScreen::PlayerPanel::PlayerPanel(unsigned int pNum, CharacterSelectScreen*screen, float x, float y, const Dictionary&placementDict, AssetManager*assetManager) : SpriteActor(x, y)
		{
			playerNum = pNum;
			charSelectScreen = screen;
			
			addAnimation("default", new Animation(1, assetManager, (String)"characterselect/panel_background_p" + playerNum + ".png"));
			addAnimation("cpu", new Animation(1, assetManager, (String)"characterselect/panel_background_cpu.png"));
			addAnimation("na", new Animation(1, assetManager, (String)"characterselect/panel_background_na.png"));
			addAnimation("blank", new Animation(1, assetManager, (String)"characterselect/panel_background_blank.png"));
			changeAnimation("default", Animation::FORWARD);
			
			portrait = new SpriteActor(x,y);
			portrait_anim = new Animation(1);
			portrait->addAnimation("default", portrait_anim, false);
			portrait->changeAnimation("default", Animation::FORWARD);
			
			overlay = new SpriteActor(x,y);
			overlay->addAnimation("default", new Animation(1, assetManager, (String)"characterselect/panel_overlay_p" + playerNum + ".png"));
			overlay->addAnimation("cpu", new Animation(1, assetManager, "characterselect/panel_overlay_cpu.png"));
			overlay->addAnimation("na", new Animation(1, assetManager, "characterselect/panel_overlay_na.png"));
			overlay->addAnimation("blank", new Animation(1, assetManager, "characterselect/panel_overlay_blank.png"));
			overlay->changeAnimation("na", Animation::FORWARD);
			
			namebox = new TextActor(x, y, "", assetManager->getFont("fonts/LemonMilk.ttf"), Color::BLACK, 36, Font::STYLE_PLAIN, TextActor::ALIGN_CENTER);
			
			tapRegion = new WireframeActor();
			tapRegion->setVisible(false);
		}
		
		CharacterSelectScreen::PlayerPanel::~PlayerPanel()
		{
			delete namebox;
			delete overlay;
			delete portrait;
		}
		
		void CharacterSelectScreen::PlayerPanel::applyPlacementProperties(const Dictionary&placementDict)
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
				const Any& alignment_val = namebox_dict.get("alignment");
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
				}
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
		
		void CharacterSelectScreen::PlayerPanel::applyPlacementDict(RectF*bounds, const Dictionary&dict)
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
		
		RectangleF CharacterSelectScreen::PlayerPanel::getPlacementFrame(const RectangleF&container, const RectF&bounds)
		{
			Vector2f overlay_topleft(bounds.left*container.width, bounds.top*container.height);
			Vector2f overlay_bottomright(bounds.right*container.width, bounds.bottom*container.height);
			return RectangleF(container.x+overlay_topleft.x, container.y+overlay_topleft.y, overlay_bottomright.x-overlay_topleft.x, overlay_bottomright.y-overlay_topleft.y);
		}
		
		void CharacterSelectScreen::PlayerPanel::update(ApplicationData appData)
		{
			SpriteActor::update(appData);
			
			RectangleF frame = getFrame();
			
			tapRegion->x = frame.x;
			tapRegion->y = frame.y;
			tapRegion->setSize(frame.width, frame.height);
			tapRegion->update(appData);
			
			if(tapRegion->didMouseRelease())
			{
				//TODO add switching between CPU, Human, and NA
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
		}
		
		void CharacterSelectScreen::PlayerPanel::draw(ApplicationData appData, Graphics graphics) const
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
		}
		
		unsigned int CharacterSelectScreen::PlayerPanel::getPlayerNum() const
		{
			return playerNum;
		}
		
		void CharacterSelectScreen::PlayerPanel::applyCharacterInfo(CharacterInfo*characterInfo)
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
		
//PlayerChip
		CharacterSelectScreen::PlayerChip::PlayerChip(unsigned int pNum, CharacterSelectScreen*screen, float x, float y, AssetManager*assetManager) : SpriteActor(x,y)
		{
			playerNum = pNum;
			charSelectScreen = screen;
			addAnimation("default", new Animation(1, assetManager, (String)"characterselect/chip_p" + playerNum + ".png"));
			addAnimation("cpu", new Animation(1, assetManager, "characterselect/chip_cpu.png"));
			changeAnimation("default", Animation::FORWARD);
			dragging = false;
			dragTouchID = 0;
		}
		
		CharacterSelectScreen::PlayerChip::~PlayerChip()
		{
			//
		}
		
		void CharacterSelectScreen::PlayerChip::onMousePress(Window*window, unsigned int touchID)
		{
			if(!dragging)
			{
				bool touch_alreadyBeingUsed = false;
				for(unsigned int i=0; i<charSelectScreen->chips.size(); i++)
				{
					PlayerChip*chip = charSelectScreen->chips.get(i);
					if(chip != this)
					{
						if(chip->dragging && chip->dragTouchID == touchID)
						{
							touch_alreadyBeingUsed = true;
						}
					}
				}
				if(!touch_alreadyBeingUsed)
				{
					dragging = true;
					dragTouchID = touchID;
					unsigned int index = charSelectScreen->chips.indexOf(this);
					charSelectScreen->chips.remove(index);
					charSelectScreen->chips.add(0,this);
				}
			}
		}
		
		void CharacterSelectScreen::PlayerChip::update(ApplicationData appData)
		{
			//updating dragging
			if(dragging)
			{
				if(Multitouch::isEnabled())
				{
					if(Multitouch::isTouchActive(appData.getWindow(), dragTouchID))
					{
						Vector2f touchpos = appData.getTransform().getInverse().transform(Multitouch::getPosition(appData.getWindow(), dragTouchID));
						x = touchpos.x;
						y = touchpos.y;
					}
					else
					{
						dragging = false;
						dragTouchID = 0;
						//TODO add event for dragging being stopped
					}
				}
				else
				{
					if(Mouse::isButtonPressed(appData.getWindow(), dragTouchID, Mouse::BUTTON_LEFT))
					{
						Vector2f mousepos = appData.getTransform().getInverse().transform(Mouse::getPosition(appData.getWindow(), dragTouchID));
						x = mousepos.x;
						y = mousepos.y;
					}
					else
					{
						dragging = false;
						dragTouchID = 0;
						//TODO add event for dragging being stopped
					}
				}
			}
			SpriteActor::update(appData);
			
			//check if overlapping with any character icons;
			CharacterInfo* overlap_charInfo = nullptr;
			float overlap_area = 0;
			ArrayList<CharacterIcon*>& icons = charSelectScreen->icons;
			RectangleF frame = getFrame();
			for(unsigned int i=0; i<icons.size(); i++)
			{
				CharacterIcon* icon = icons.get(i);
				RectangleF iconFrame = icon->getFrame();
				if(frame.intersects(iconFrame))
				{
					RectangleF overlap = frame.getIntersect(iconFrame);
					float area = overlap.getArea();
					if(area > overlap_area)
					{
						overlap_charInfo = icon->getCharacterInfo();
						overlap_area = area;
					}
				}
			}
			CharacterInfo* oldInfo = charSelectScreen->rules->getPlayerInfo(playerNum).getCharacterInfo();
			charSelectScreen->rules->getPlayerInfo(playerNum).setCharacterInfo(overlap_charInfo);
			if(oldInfo != overlap_charInfo)
			{
				charSelectScreen->whenPlayerCharacterChanges(playerNum, overlap_charInfo);
			}
		}
		
//CharacterSelectScreen
		CharacterSelectScreen::CharacterSelectScreen(const SmashData&smashData) : SmashBros::Menu::BaseMenuScreen(smashData)
		{
			rules = smashData.getRules();
			characterLoader = smashData.getCharacterLoader();
			iconGrid = nullptr;
		}
		
		CharacterSelectScreen::~CharacterSelectScreen()
		{
			if(iconGrid != nullptr)
			{
				delete iconGrid;
			}
			for(unsigned int i=0; i<icons.size(); i++)
			{
				delete icons.get(i);
			}
			for(unsigned int i=0; i<panels.size(); i++)
			{
				delete panels.get(i);
			}
		}
		
		Rules* CharacterSelectScreen::getRules() const
		{
			return rules;
		}
		
		CharacterLoader* CharacterSelectScreen::getCharacterLoader() const
		{
			return characterLoader;
		}
		
		void CharacterSelectScreen::reloadIcons(const SmashData&smashData)
		{
			if(iconGrid != nullptr)
			{
				delete iconGrid;
				iconGrid = nullptr;
			}
			
			for(unsigned int i=0; i<icons.size(); i++)
			{
				delete icons.get(i);
			}
			icons.clear();
			
			ArrayList<CharacterInfo>& characters = smashData.getCharacterLoader()->getCharacters();
			unsigned int total = characters.size();
			float approx_cols = Math::sqrt((3.0f*((float)total))/2.0f);
			float approx_rows = approx_cols*(2.0f/3.0f);
			unsigned int cols = (unsigned int)Math::round(approx_cols);
			unsigned int rows = (unsigned int)Math::round(approx_rows);
			if((cols*rows) < total)
			{
				cols = (unsigned int)Math::ceil(approx_cols);
				if((cols*rows) < total)
				{
					rows = (unsigned int)Math::ceil(approx_rows);
				}
			}
			
			ImageElement* headerbar = getHeaderbarElement();
			RectangleF headerbarFrame = headerbar->getFrame();
			Vector2f screenSize = smashData.getScreenCoords(Vector2f(1.0f,1.0f));
			float frameoffset_y = headerbarFrame.height / screenSize.y;
			
			Vector2f topLeft = smashData.getScreenCoords(0.1f, frameoffset_y);
			Vector2f bottomRight = smashData.getScreenCoords(0.9f, 0.6f);
			RectangleF charSelectRect(topLeft.x, topLeft.y, bottomRight.x-topLeft.x, bottomRight.y-topLeft.y);
			iconGridFrame = charSelectRect;
			
			float icon_width = charSelectRect.width/((float)cols);
			float icon_height = charSelectRect.height/((float)rows);
			Vector2f icon_size(icon_width-1, icon_height);
			
			iconGrid = new ActorGrid(Vector2f(charSelectRect.x+(icon_width/2), charSelectRect.y+(icon_height/2)), cols, Vector2f(icon_width, icon_height));
			
			AssetManager* loaderAssetManager = smashData.getCharacterLoader()->getAssetManager();
			for(unsigned int i=0; i<characters.size(); i++)
			{
				CharacterInfo& info = characters.get(i);
				CharacterIcon* icon = new CharacterIcon(info, 0, 0, loaderAssetManager);
				icon->Actor::scaleToFit(icon_size);
				icons.add(icon);
				iconGrid->add(icon);
			}
		}
		
		void CharacterSelectScreen::reloadPlayerPanels(const SmashData&smashData)
		{
			for(unsigned int i=0; i<panels.size(); i++)
			{
				delete panels.get(i);
			}
			panels.clear();
			for(unsigned int i = 0; i < chips.size(); i++)
			{
				delete chips.get(i);
			}
			chips.clear();
			
			unsigned int playerCount = rules->getPlayerCount();
			if(playerCount==0)
			{
				return;
			}
			
			Vector2f topLeft = smashData.getScreenCoords(0.0f, 0.6f);
			Vector2f bottomRight = smashData.getScreenCoords(1.0f, 1.0f);
			RectangleF frame(topLeft.x, topLeft.y, bottomRight.x-topLeft.x, bottomRight.y-topLeft.y);
			
			float panelframe_width = frame.width/(float)playerCount;
			float panelframe_height = frame.height*(5.0f/6.0f);
			float offsetX = frame.x + (panelframe_width/2);
			float offsetY = frame.y + (frame.height/2);
			
			String menuAssetsRoot = smashData.getMenuData().getAssetManager()->getRootDirectory();
			Dictionary placementDict;
			//TODO change this when implementing themes
			placementDict.loadFromFile(menuAssetsRoot + "/characterselect/panel.plist");
			
			for(unsigned int i = 0; i < playerCount; i++)
			{
				unsigned int playerNum = i+1;
				PlayerPanel* panel = new PlayerPanel(playerNum, this, offsetX + (panelframe_width*(float)i), offsetY, placementDict, smashData.getMenuData().getAssetManager());
				panel->Actor::scaleToFit(Vector2f(panelframe_width, panelframe_height));
				panel->applyPlacementProperties(placementDict);
				panels.add(panel);
				PlayerChip* chip = new PlayerChip(playerNum, this, panel->x-(panel->getWidth()/2), panel->y, smashData.getMenuData().getAssetManager());
				chip->Actor::scaleToFit(Vector2f(panelframe_width/3, panelframe_height/3));
				chips.add(chip);
			}
		}
		
		void CharacterSelectScreen::updateItems(ApplicationData appData)
		{
			BaseMenuScreen::updateItems(appData);
			ArrayList<CharacterIcon*> icons_list = icons;
			for(unsigned int i=0; i<icons_list.size(); i++)
			{
				icons_list.get(i)->update(appData);
			}
			icons_list.clear();
			ArrayList<PlayerChip*> chips_list = chips;
			for(unsigned int i=0; i<chips_list.size(); i++)
			{
				chips_list.get(i)->update(appData);
			}
			chips_list.clear();
			ArrayList<PlayerPanel*> panels_list = panels;
			for(unsigned int i=0; i<panels_list.size(); i++)
			{
				panels_list.get(i)->update(appData);
			}
			panels_list.clear();
		}
		
		void CharacterSelectScreen::drawItems(ApplicationData appData, Graphics graphics) const
		{
			TextureImage* icon_frame = appData.getAssetManager()->getTexture("characterselect/icon_frame.png");
			BaseMenuScreen::drawItems(appData, graphics);
			for(unsigned int i=0; i<icons.size(); i++)
			{
				CharacterIcon* icon = icons.get(i);
				icon->draw(appData, graphics);
				RectangleF frame = icon->getFrame();
				graphics.drawImage(icon_frame, frame);
			}
			for(unsigned int i=0; i<panels.size(); i++)
			{
				PlayerPanel* panel = panels.get(i);
				panel->draw(appData, graphics);
			}
			ArrayList<PlayerChip*> chips_list;
			for(unsigned int i=0; i<chips.size(); i++) //reverse the chips list
			{
				chips_list.add(0, chips.get(i));
			}
			for(unsigned int i=0; i<chips_list.size(); i++)
			{
				chips_list.get(i)->draw(appData, graphics);
			}
		}
		
		void CharacterSelectScreen::whenPlayerCharacterChanges(unsigned int playerNum, CharacterInfo*characterInfo)
		{
			for(unsigned int i=0; i<panels.size(); i++)
			{
				PlayerPanel*panel = panels.get(i);
				if(playerNum == panel->getPlayerNum())
				{
					panel->applyCharacterInfo(characterInfo);
					return;
				}
			}
		}
	}
}
