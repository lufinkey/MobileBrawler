
#pragma once

#include "Action.h"

namespace BrawlerLibrary
{
	class ActionPerformer : public GameLibrary::SpriteActor
	{
		friend class Action;
	public:
		ActionPerformer();
		ActionPerformer(const GameLibrary::Vector2d&position);
		virtual ~ActionPerformer();
		
		void addAction(const GameLibrary::String&name, Action*action, bool destruct=true);
		void removeAction(const GameLibrary::String&name);
		bool hasAction(const GameLibrary::String&name) const;
		void performAction(const GameLibrary::String&name);
		void performAction(Action*action);
		void queueAction(const GameLibrary::String&name);
		void queueAction(Action*action);
		
		bool setFaceDirection(const FaceDirection&side);
		const FaceDirection& getFaceDirection() const;
		
	protected:
		virtual void onAnimationFinish(const GameLibrary::String&name, GameLibrary::Animation*animation) override;
		virtual void onActionFinish(const GameLibrary::String&name, Action*action);
		
	private:
		void whenActionFinish(const GameLibrary::String&name, Action*action);
		
		typedef struct
		{
			GameLibrary::String name;
			Action* action;
			bool destruct;
		} ActionInfo;
		
		FaceDirection side;
		GameLibrary::String action_name;
		Action* action_current;
		GameLibrary::ArrayList<ActionInfo> actions;
		GameLibrary::ArrayList<GameLibrary::Pair<GameLibrary::String, Action*> > queue;
	};
}
