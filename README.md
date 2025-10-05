# Tower Defense

## Cosa stavo facendo

stavo lavorando sullo spawn delle torri che funziona grazie al socket nelle mesh
poi volevo spostare lo spawn dalla grid alla gamemode, che regola tutto, che forse dovrebbe tenere anche la griglia logica (non saprei)

poi volevo lavorare sulle preview delle torri, perché non posso fare blueprint e mesh diverse per ogni torre, bisogna usare le dynamic

fatto questo, volevo fare lo spawn dei nemici alla fase defense
grid deve dire a gamemode dove sono gli spawn dei nemici, e dove è la base alleata
gamemode spawna base alleata e enemyspawner

enemyspawner spawna nemici
base muore

-- sono qui

push su economia e punteggio
fatto - dare soldi a inizio game
fatto - prendere torre e dare costo
fatto - risolvere problema data asset che si ricarica -> passare a tmap
fatto - fare cambio target
fatto - prendere muro e dare costo -> ridurre coins
fatto - prendere nemico e dare punteggio -> dare punteggio
fatto - mostrare vita sopra nemico
qui >>>>>>>>>> - sync vita base con ui + vita sopra base
- creare wave e post-wave (loop)

creare upgrade torri
creare wave sempre più difficili

problema warning nanite
Tip pratico: per torrette e effetti semi-trasparenti (es. glow, selection ring), spesso si crea un componente separato (plane o decal) con materiale traslucido sopra la mesh Nanite. Così la torretta resta Nanite, e l’effetto trasparente è su un componente secondario.

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


-----------------
# GIOCO

voglio poche cose casuali perché non voglio che il giocatore si senta condizionato da fortune o sfortune, come chest, carte, pescaggio eccetera

> fattore "evita probabilità": no pescaggi, no chest, no random items, no probabilità, no fortuna (non voglio che il giocatore re-inizi la run perché non ha pescato per prima una specifica carta per esempio)
> fattore "skill del giocatore": bisogna giocare di velocità, intelligenza e furbizia
> cercare meccaniche che stimolano ciò (ripeto: non chest o pescaggio a fortuna)

il giocatore deve sopravvivere il più tempo possibile

> fattore "infinite run": il gioco non finisce mai

# WAVE

per il fattore "infinite run" ci devono essere infinite wave
se ci sono infinite wave

come generare le wave? ne genero io 100 off-game con script e faccio in modo che arrivare alla 25 sia difficile

# PUNTEGGIO

se tutti arrivano alla 100, hanno lo stesso punteggio? no

punteggio formato da
- numero wave
- vita rimasta alla base
- numero nemici uccisi

# FASI

ci sono due fasi di gioco che si alternano:
- preparazione
- difesa

## preparazione

la preparazione ha un timer di N secondi dopo i quali parte la successiva fase di difesa

in questa fase il giocatore può
- comprare, vendere, piazzare o spostare i muri -> cambia il percorso dei nemici

## difesa

quando la fase di difesa finisce, si entra in fase di preparaione per la difesa successiva

in questa fase il giocatore può
- comprare, vendere, piazzare o spostare le torrette

# STATISTICHE

il giocatore può vedere le statistiche in tempo reale 
- del round
- overall (tutta la partita)

in questo modo capisce cosa va e cosa non va -> bisogna dare al giocatore chance per riparare agli errori

le statistiche possono essere
- maggiore danno
- maggiore cura
- maggiore tank

# TORRETTA

Torretta (base)
- tipo/classe ??
- tier (1 2 3) ??
- nome dato da giocatore (per statistiche)
- danno base
- tipo danno ?? (in conflitto con tipo/classe?)
- vita base
- range
- rateo di fuoco
- inventory (3 o 4 items?)
- target preferito ?? (selezionabile la giocatore?)

# NEMICO

Nemico (base)
- tipo/classe ??
- tier (1 2 3) ??
- danno base
- vita base
- velocità di movimento
- rateo di fuoco
- target preferito (classe torretta, la più vicina)

# V2: MECCANICA DI UPGRADE

itemes alle torri?
upgrade infiniti alle torri?
perks alle torri?
prestigio alle torri?

# V2: PERKS

perks possono essere dati ogni 10 wave, e il giocatore può scegliere

idea perks che possono cambiare la partita (non si possono cambiare in-run):
- più vita alla base
- più nemici
- più danni
- più cure
- più vita alle torri
- più campo di gioco