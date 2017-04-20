
#pragma once

#include <GameLibrary/GameLibrary.hpp>

using namespace fgl;

namespace SmashBros
{
	namespace Menu
	{
		class ActorGrid
		{
		private:
			Vector2d position;
			ArrayList<Actor*> actors;
			unsigned int columns;
			Vector2d spacing;
			
		protected:
			void setActorPosition(size_t index, Actor*actor);
			
		public:
			ActorGrid(const Vector2d&position, unsigned int columns, const Vector2d&spacing);
			virtual ~ActorGrid();
			
			void add(Actor*actor);
			void clear();
			
			void setPosition(const Vector2d&position);
			
			const Vector2d& getPosition() const;
			const ArrayList<Actor*>& getActors() const;
			unsigned int getColumns() const;
			const Vector2d& getSpacing() const;
		};
	}
}
