/*
 * export-data.js
 * ---------------------------------------------------------------
 * Reads the REAL SQLite databases (database/gameData.db and
 * database/myFarmData.db) using Node's built-in `node:sqlite`
 * module (Node 22+, zero npm dependencies) and regenerates
 * gui/js/data.js with real game data, in the exact shape that
 * gui/js/app.js and gui/js/sprites.js already expect.
 *
 * Run with:  node gui/tools/export-data.js
 * Re-run any time the databases change (e.g. after playing the
 * C++ program and saving progress to myFarmData.db) to refresh
 * the GUI's data.
 * ---------------------------------------------------------------
 */

const { DatabaseSync } = require('node:sqlite');
const path = require('path');
const fs = require('fs');

const ROOT = path.resolve(__dirname, '..', '..');
const GAME_DB = path.join(ROOT, 'database', 'gameData.db');
const FARM_DB = path.join(ROOT, 'database', 'myFarmData.db');
const OUT_FILE = path.join(ROOT, 'gui', 'js', 'data.js');

// ---- small display tweaks -----
// The DB already stores seasons/quality/etc. in English, so no
// translation table is needed — just pick an icon per season and
// capitalize the lowercase "quality" enum for display.
const SEASON_ICON = { Spring: 'cropSpring', Summer: 'cropSummer', Fall: 'cropFall', Winter: 'cropWinter' };
function capitalize(s) { return s.charAt(0).toUpperCase() + s.slice(1); }
const WHERE_TO_GET_EN = { Robin: "Robin (Carpenter's Shop)", Wizard: "Wizard's Tower" };

const ANIMAL_ICON = { Cow: 'animalCow', Sheep: 'animalSheep', Pig: 'animalPig', Chicken: 'animalChicken' };
function animalIcon(name) { return ANIMAL_ICON[name] || 'animalGeneric'; }

function buildingIcon(name) {
  if (/barn/i.test(name)) return 'buildingBarn';
  if (/coop/i.test(name)) return 'buildingCoop';
  return 'buildingSilo'; // generic "other structure" fallback icon
}

// villager portraits are picked client-side, in gui/js/sprites.js,
// from a small set of pre-generated PNG variants (villagerBust-0.png
// .. villagerBust-7.png) by hashing the villager's name — no portrait
// data needs to be exported here.

// which base (smallest) building actually houses each animal type,
// derived from building_animal_types — used as the animal card's tag
const BUILDING_RANK = { Coop: 0, 'Big Coop': 1, 'Deluxe Coop': 2, Barn: 0, 'Big Barn': 1, 'Deluxe Barn': 2 };
function buildHousingMap(db) {
  const rows = db.prepare(`
    SELECT bat.animal_type, bd.name AS building_name
    FROM building_animal_types bat
    JOIN datatype bd ON bd.id = bat.building_id
  `).all();
  const map = {};
  for (const r of rows) (map[r.animal_type] ||= []).push(r.building_name);
  return map;
}
function baseBuilding(housingMap, animalName) {
  const list = housingMap[animalName] || [];
  if (!list.length) return 'Farm';
  return [...list].sort((a, b) => (BUILDING_RANK[a] ?? 99) - (BUILDING_RANK[b] ?? 99))[0];
}

// ---- extractors ---------------------------------------------------
function exportCrops(db) {
  const rows = db.prepare(`
    SELECT d.id, d.name, c.season, c.daysToHarvest, c.regrow, c.regrowDays
    FROM datatype d JOIN crop c ON c.id = d.id ORDER BY d.id
  `).all();
  const sellStmt = db.prepare('SELECT quality, value FROM crop_sell_values WHERE crop_id = ?');
  const seedStmt = db.prepare('SELECT shop_name, price FROM crop_seed_sources WHERE crop_id = ?');
  const artisanStmt = db.prepare('SELECT item_name, machine, value FROM crop_artisan_items WHERE crop_id = ?');

  return rows.map((r) => ({
    name: r.name,
    season: r.season,
    icon: SEASON_ICON[r.season] || 'cropSpring',
    daysToHarvest: r.daysToHarvest,
    regrow: !!r.regrow,
    daysToRegrowth: r.regrow ? r.regrowDays : null,
    sellValue: sellStmt.all(r.id).map((s) => [capitalize(s.quality), s.value]),
    seedPrice: seedStmt.all(r.id).map((s) => [s.shop_name, s.price]),
    artisanItems: artisanStmt.all(r.id).map((a) => [a.item_name, a.machine, a.value]),
  }));
}

function exportVillagers(db) {
  const rows = db.prepare(`
    SELECT d.id, d.name, v.single FROM datatype d JOIN villager v ON v.id = d.id ORDER BY d.id
  `).all();
  const giftStmt = db.prepare('SELECT item_name, reaction FROM villager_gifts WHERE villager_id = ?');

  return rows.map((r) => {
    const gifts = giftStmt.all(r.id);
    const love = gifts.find((g) => g.reaction === 'love');
    const like = gifts.find((g) => g.reaction === 'like');
    return {
      name: r.name,
      single: !!r.single,
      giftLove: love ? love.item_name : 'Not catalogued',
      giftLike: like ? like.item_name : 'Not catalogued',
    };
  });
}

function exportAnimals(db) {
  const rows = db.prepare(`
    SELECT d.id, d.name, a.produces, a.daysToAdult, a.buyPrice
    FROM datatype d JOIN animal a ON a.id = d.id ORDER BY d.id
  `).all();
  const artisanStmt = db.prepare(`
    SELECT item_name, machine, value FROM animal_artisan_items
    WHERE animal_id = ? AND item_name IS NOT NULL
  `);
  const housingMap = buildHousingMap(db);

  return rows.map((r) => ({
    name: r.name,
    type: baseBuilding(housingMap, r.name),
    icon: animalIcon(r.name),
    produces: r.produces,
    daysToAdult: r.daysToAdult,
    buyPrice: r.buyPrice,
    artisanItem: artisanStmt.all(r.id).map((a) => [a.item_name, a.machine, a.value]),
  }));
}

function exportBuildings(db) {
  const rows = db.prepare(`
    SELECT d.id, d.name, b.size_width, b.size_height, b.whereToGet, b.housesAnimals, b.animalAmount
    FROM datatype d JOIN building b ON b.id = d.id ORDER BY d.id
  `).all();
  const matStmt = db.prepare('SELECT material_name, material_amount FROM building_construction_materials WHERE building_id = ?');
  const animalTypeStmt = db.prepare('SELECT animal_type FROM building_animal_types WHERE building_id = ?');

  return rows.map((r) => ({
    name: r.name,
    icon: buildingIcon(r.name),
    constructionMaterials: matStmt.all(r.id).map((m) => [m.material_name, m.material_amount]),
    size: [r.size_width, r.size_height],
    whereToGet: WHERE_TO_GET_EN[r.whereToGet] || r.whereToGet,
    housesAnimals: !!r.housesAnimals,
    animalTypes: r.housesAnimals ? animalTypeStmt.all(r.id).map((a) => a.animal_type) : [],
    animalAmount: r.housesAnimals ? r.animalAmount : 0,
  }));
}

function exportMyFarm(farmDb) {
  const farmRow = farmDb.prepare('SELECT * FROM my_farms ORDER BY id LIMIT 1').get();
  if (!farmRow) {
    return { farmName: 'No farm saved', farmLayout: '-', myAnimals: [], myBuildings: [], myRelationships: [] };
  }
  const animalRows = farmDb.prepare('SELECT animal_name, animal_type, animal_relationship FROM my_animals WHERE farm_id = ?').all(farmRow.id);
  const buildingRows = farmDb.prepare('SELECT building_name, building_type, building_level FROM my_buildings WHERE farm_id = ?').all(farmRow.id);
  const relRows = farmDb.prepare('SELECT villager_name, friendship FROM my_relationships WHERE farm_id = ?').all(farmRow.id);

  return {
    farmName: farmRow.farm_name,
    farmLayout: farmRow.farm_layout,
    myAnimals: animalRows.map((a) => ({
      animalName: a.animal_name, animalType: a.animal_type,
      animalRelationship: a.animal_relationship, icon: animalIcon(a.animal_type),
    })),
    myBuildings: buildingRows.map((b) => ({
      buildingName: b.building_name, buildingType: b.building_type,
      buildingLevel: b.building_level, icon: buildingIcon(b.building_name),
    })),
    myRelationships: relRows.map((r) => ({ villagerName: r.villager_name, friendship: r.friendship })),
  };
}

// ---- main ----------------------------------------------------
function main() {
  const gameDb = new DatabaseSync(GAME_DB, { readOnly: true });
  const farmDb = new DatabaseSync(FARM_DB, { readOnly: true });

  const GameData = {
    crops: exportCrops(gameDb),
    villagers: exportVillagers(gameDb),
    animals: exportAnimals(gameDb),
    buildings: exportBuildings(gameDb),
    myFarm: exportMyFarm(farmDb),
  };

  gameDb.close();
  farmDb.close();

  const header = `/*
 * data.js — AUTO-GENERATED by gui/tools/export-data.js
 * ---------------------------------------------------------------
 * Real content, read from database/gameData.db (the game catalog)
 * and database/myFarmData.db (the player's saved progress) via
 * node:sqlite. DO NOT EDIT THIS FILE BY HAND — changes are lost the
 * next time the generator runs.
 *
 * To refresh after playing/changing the databases:
 *   node gui/tools/export-data.js
 *
 * Generated: ${new Date().toISOString()}
 * ---------------------------------------------------------------
 */

`;
  const body = 'const GameData = ' + JSON.stringify(GameData, null, 2) + ';\n';
  fs.writeFileSync(OUT_FILE, header + body, 'utf8');

  console.log(`OK: ${OUT_FILE}`);
  console.log(`  crops=${GameData.crops.length} villagers=${GameData.villagers.length} animals=${GameData.animals.length} buildings=${GameData.buildings.length}`);
  console.log(`  myFarm: "${GameData.myFarm.farmName}" — animals=${GameData.myFarm.myAnimals.length} buildings=${GameData.myFarm.myBuildings.length} relationships=${GameData.myFarm.myRelationships.length}`);
}

main();
