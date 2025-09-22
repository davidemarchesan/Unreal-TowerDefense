# Tower Defense

## Links

- https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Slate

## Game

Just a GameMode Play. Player will play a Run.

Each Run will consists in phases:
- Buy&Build
- Wave

Each Wave phase is separated by a Buy&Build phase.

Buy&Build phase let player to buy walls or turrets and place them in the field.
When the Buy&Build phase is over, the player can not buy, build or move anything.

During the Wave phase, the player can only upgrade (or sell) turrets.
Each Wave will be more difficult from the previous one.

Player can buy walls or turrets in the shop during the Buy&Build phase.
Player can queue walls or turrets to buy during the Wave phase. When the Wave phase is over, the queue items will be purchased.

Player will earn money by eliminating enemies.

The game ends when the base health is 0.
The game points are calculated by wave number and enemies eliminated.

Each enemy rewards the player with money and points.

FUTURE:
- Traps
- Turrets items that modify stats (instead of upgrading? nah, together)
- Damage and enemies types (fire, electric, etc.)

## TODO

Refactoring... the whole game. 

Building GameMode that contains the rules of the run.
Building GameState that contains the current state of the run.
Building PlayerState that contains player's infos.
Building PlayerController that controls the controls :)
Building the HUD that displays info.
Building data assets that contain game data, like damage, price etc.

Build on delegates if more components need to access data.
Build on public functions to stay simple.

- [ ] GameMode
- [ ] Phases
- [ ] Enemy and Enemies spawn
- [ ] Turret build -> rename to DefenseUnit
- [ ] Wall build

### Layout editor (deprecated)

- [x] Create controllers
- [x] Spawn walls
- [x] Create AI with NavMesh
- [x] Build and valid path when previewing
- [x] Create simple UI
- [x] Save and load layout
- [ ] Building gamemode, checks and feedbacks
- [ ] [DOING] Main menu with Play, Edit Layout and Exit
- [ ] Blender, build simple roundy assets



### To deprecate

- [ ] topdownplayercontroller
- [ ] topdowncamera
- [ ] enemybase
- [ ] topdowngamemode
- [ ] towerdefenCe GAME INSTANCE

### DOING

Main menu scene