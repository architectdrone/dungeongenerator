# Owen's Dungeon Generator

Just a dungeon generator I cooked up. :) I also started "really" learning git through this repo, so don't be surprised if you look through the history and see some ... questionable commits.

## Definitions
In order to properly explain what I intend for this program to do, we need to first start with some definitions.

**Wall**: Some obstacle that a player character cannot cross.

**Tile**: A tile is a location on a 2D plane that is either a wall, or not a wall. Its location is specified with X and Y coordinates.

**Tileset**: A set of tiles. Each tile may only be included in a tileset once. It may be of arbitrary size.

**Board**:A tileset that contains all tiles within a certain X and Y range.

**Dungeon**: A board in which every non-wall tile is accesible by every other non-wall tile. 


## Dungeon Generation
The simplest dungeon is simply a board of non-walls. (A wall will be represented with a "#", and a non-wall with a " ".)


(there was an ascii dungeon here, but markdown messed it up.)


There are two problems with the above dungeon (yes, there is a dungeon above). First, a player character can wander out of bounds. Second, it is *really boring*. To fix the first problem, we add outer walls:


(Markdown also messed this one up.)


Fixing the second problem is considerably more difficult. We would like to add some obstacles to make the dungeon more interesting, but in so doing, we may accidentally make the board an invalid dungeon. In order to make an interesting dungeon, we must have an algorithim.


## "Optimized" Dungeons
Another thing to consider is how the dungeon is using space. If we have a limited space, we want the player to be able to explore as much as he or she can. This means that there should be no wasted space. That is, walls should only exist to constrict player movement, not to simply take up space. An optimized dungeon is one where every wall is merely a border between two non-walls - meaning that there will be no areas of the board that are just walls.


## Goals
+ Make classes that can be used in other programs regarding dungeon and board creation.
+ Create a prototype optimized dungeon generation alogorithm, and export valid dungeons to the user in ways that they can visualize and use.
