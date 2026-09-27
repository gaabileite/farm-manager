# Farmpedia - A farm manager for Stardew Valley

## Applying what we learned
Farmpedia is an interactive databank, built in C++ through Object-Oriented Programming. The project is a hands-on application of the concepts covered in Object-Oriented Data Structures (CIN0135), part of the Information Systems program at the Federal University of Pernambuco (UFPE).

## Purpose and Goals
Stardew Valley is a casual game where the player takes on the role of a farmer who inherits a property from their grandfather in a small countryside town, which they need to explore to uncover its mysteries and get to know every corner of the map and its residents. The game, released in 2016, covers a wide range of crops, animal husbandry, and mining. On top of that, there are dozens of NPCs (Non-Playable Characters) the player can interact with to earn rewards and progress.
Given all that, the gameplay can get overwhelming: 34 NPCs to interact with, 54 types of crops, each with its own quirks, countless ores and minerals found in the mines, and more than 30 side quests... the game doesn't feel all that "casual" after all.
That's why this program maps out the crops, villagers, farm animals, and buildings available throughout the game, helping the player have a smoother playthrough without having to uncover every secret of Stardew Valley by trial and error. On top of that, the program also stores information about the player's own farm - which animals they own, which buildings exist on the property, which villagers like or dislike them, and so on.

## Class Diagram
DataType is the parent class that gives rise to the game's reference subclasses, through the inheritance technique covered in class. The player's farm is modeled separately, through composition: MyFarm holds the player's animals, buildings, and relationships as its own collections, rather than inheriting from DataType. In the interface, each of these classes is accessed as a **book**.

    DataType
    	├─ Crop
    	├─ Villager
    	├─ Animal
    	└─ Building

    MyFarm
    	├─ myAnimals (array:MyAnimal)
    	├─ myBuildings (array:MyBuilding)
    	└─ myRelationships (array:MyRelationship)

## Categorization
Since this program is basically a big library, an encyclopedia for navigating the world of Stardew Valley, everything has its place: there's a logic behind how each section is organized and labeled.

#### Book 1: Crops
*Crops* covers everything the player can plant in the game. It's Stardew Valley's main engine, and naturally, every plant, fruit, vegetable, and flower has its own characteristics: its market value (which depends on quality), its seed's sale price, the season it can be planted in, how many days pass between planting and harvest, and so on. That's why the following attribute model was put together.

    DataType(Crop)
    	├─ name (str)
    	├─ season (str)
    	├─ daysToHarvest (int)
    	├─ regrow (bool)
    	├─ sellValue (array:int)
    	├─ seedPrice (array:int)
    	├─ profit (array:int)
    	├─ artisanItems (array:tuple)
    	└─ seedShop (array:str)
    	
#### Book 2: Villagers
The *villagers* - NPCs - are the characters the player interacts with in the game. Just like in real life, the player needs to keep up frequent interaction with each character for their "friendship points" to go up, earning their **heart**. This happens through daily conversation and through gifts: the more a character likes the gift, the more points the player earns with them. These points are tracked through hearts in the game, which are also stored in this program, along with which gifts each *villager* likes, loves, or hates.

    DataType(Villager)
    	├─ name (str)
    	├─ single (bool)
    	├─ routine (array:tuple)
    	├─ giftsLike (array:str)
    	├─ giftsLove (array:str)
    	├─ giftsHate (array:str)
    	└─ giftsNeutral (array:str)

#### Book 3: Animals
Animals in Stardew Valley need specific places to sleep and be cared for, just like real-life pets. Given those two things, each farm animal produces something specific - a chicken produces an egg, a pig produces a truffle... To help the *player*, Farmpedia provides information to support long-term planning around buying animals and understanding which buildings are needed to house each one.

    DataType(Animal)
    	├─ name (str)
    	├─ type (str)
    	├─ produces (str)
    	├─ daysToAdult (int)
    	├─ buyPrice (int)
    	├─ sellValue (int)
    	└─ artisanItem (array:tuple)

#### Book 4: Buildings
As mentioned, each animal needs its own specific *building*, but barns and coops aren't the only things you can build in Stardew Valley. Building a mill requires different materials than building a fish pond, for example, and their prices and construction time also differ.

    DataType(Building)
    	├─ name (str)
    	├─ constructionMaterials (array:tuple)
    	├─ size (array:int)
    	├─ whereToGet (str)
    	├─ housesAnimals (bool)
    	├─ animalTypes (array:str)
    	└─ animalAmount (int)

#### Book 5: My Farm
Besides showing general information about the game, Farmpedia also displays information about the player's own farm, helping them keep track of their relationship with each *villager*, which buildings exist on their farm, and which animals they've already acquired. And, just like in the game, you can keep track of different farms, each with different friendship levels, buildings, and animals.

    MyFarm
    	├─ farmName (str)
    	├─ farmLayout (str)
    	├─ myRelationships (array:tuple)
    	├─ myAnimals (array:tuple)
    	└─ myBuildings (array:tuple)

## Tech stack
- C++17
- SQLite3, bundled in `external/` — nothing to install separately
- Notion, usado para organização backlog — [Projeto EDOO](https://app.notion.com/p/Projeto-EDOO-3cfdc8f6733680b2af54eba2b5b992ac?pvs=21)

## Building
`sqlite3.c` is C, not C++, so it gets compiled separately with `gcc` before being linked with the rest of the program.

```bash
# Linux/Mac
gcc -c external/sqlite3.c -o sqlite3.o
g++ -std=c++17 main.cpp database.cpp filters.cpp menu.cpp sqlite3.o -o farm_manager
./farm_manager
```

```powershell
# Windows (PowerShell)
gcc -c external/sqlite3.c -o sqlite3.o
g++ -std=c++17 main.cpp database.cpp filters.cpp menu.cpp sqlite3.o -o farm_manager.exe
.\farm_manager.exe
```

Always run it from the project root, since the database paths are relative.

## Project structure

    classes/      → DataType and the game's reference subclasses (Crop, Animal, Building, Villager) + MyFarm, MyAnimal, MyBuilding, MyRelationship
    database/     → search filters and navigation menus
    external/     → SQLite3
    database.cpp  → all database access logic (SQL)
    filters.cpp   → filters by name, season, etc.
    menu.cpp      → interactive terminal menus
    main.cpp      → entry point

## Database
The project uses two SQLite databases:
- `gameData.db` — the game's reference data (crops, villagers, animals, buildings), read-only
- `myFarmData.db` — the player's progress (farm, animals, buildings, relationships), which the program reads from and writes to

## Authors

- Gabriela Leite de Andrade Lima
- Kamilla Regina Menezes de Souza
- Sofia Sobreira de Mendonça
