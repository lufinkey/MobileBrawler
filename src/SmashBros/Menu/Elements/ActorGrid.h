
#pragma once

#include <GameLibrary/GameLibrary.h>

namespace SmashBros
{
	using namespace GameLibrary;
	
	namespace Menu
	{
		class ActorGrid
		{
		private:
			Vector2f position;
			ArrayList<Actor*> actors;
			unsigned int columns;
			Vector2f spacing;
			
		protected:
			void setActorPosition(unsigned int index, Actor*actor);
			
		public:
			ActorGrid(const Vector2f&position, unsigned int columns, const Vector2f&spacing);
			virtual ~ActorGrid();
			
			void add(Actor*actor);
			void clear();
			
			void setPosition(const Vector2f&position);
			
			const Vector2f& getPosition() const;
			const ArrayList<Actor*>& getActors() const;
			unsigned int getColumns() const;
			const Vector2f& getSpacing() const;
		};
	}
}
