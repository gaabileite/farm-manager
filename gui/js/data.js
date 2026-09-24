/*
 * data.js — GERADO AUTOMATICAMENTE por gui/tools/export-data.js
 * ---------------------------------------------------------------
 * Conteudo real, lido de database/gameData.db (catalogo do jogo)
 * e database/myFarmData.db (progresso salvo do jogador) via
 * node:sqlite. NAO EDITE ESTE ARQUIVO A MAO — as mudancas serao
 * perdidas na proxima execucao do gerador.
 *
 * Para atualizar apos jogar/alterar os bancos:
 *   node gui/tools/export-data.js
 *
 * Gerado em: 2026-09-24T16:56:25.908Z
 * ---------------------------------------------------------------
 */

const GameData = {
  "crops": [
    {
      "name": "Carrot",
      "season": "Primavera",
      "icon": "cropSpring",
      "daysToHarvest": 3,
      "regrow": false,
      "daysToRegrowth": null,
      "sellValue": [
        [
          "Normal",
          35
        ],
        [
          "Prata",
          43
        ],
        [
          "Ouro",
          52
        ],
        [
          "Iridio",
          70
        ]
      ],
      "seedPrice": [
        [
          "Foraging",
          0
        ]
      ],
      "artisanItems": [
        [
          "Pickles",
          "Preserves Jar",
          120
        ],
        [
          "Juice",
          "Keg",
          79
        ]
      ]
    },
    {
      "name": "Cauliflower",
      "season": "Primavera",
      "icon": "cropSpring",
      "daysToHarvest": 12,
      "regrow": false,
      "daysToRegrowth": null,
      "sellValue": [
        [
          "Normal",
          175
        ],
        [
          "Prata",
          218
        ],
        [
          "Ouro",
          262
        ],
        [
          "Iridio",
          350
        ]
      ],
      "seedPrice": [
        [
          "Pierre",
          80
        ],
        [
          "Joja",
          100
        ]
      ],
      "artisanItems": [
        [
          "Pickles",
          "Preserves Jar",
          400
        ],
        [
          "Juice",
          "Keg",
          394
        ]
      ]
    },
    {
      "name": "Green Bean",
      "season": "Primavera",
      "icon": "cropSpring",
      "daysToHarvest": 10,
      "regrow": true,
      "daysToRegrowth": 3,
      "sellValue": [
        [
          "Normal",
          40
        ],
        [
          "Prata",
          50
        ],
        [
          "Ouro",
          60
        ],
        [
          "Iridio",
          80
        ]
      ],
      "seedPrice": [
        [
          "Pierre",
          60
        ],
        [
          "Joja",
          75
        ]
      ],
      "artisanItems": [
        [
          "Pickles",
          "Preserves Jar",
          130
        ],
        [
          "Juice",
          "Keg",
          90
        ]
      ]
    },
    {
      "name": "Parsnip",
      "season": "Primavera",
      "icon": "cropSpring",
      "daysToHarvest": 4,
      "regrow": false,
      "daysToRegrowth": null,
      "sellValue": [
        [
          "Normal",
          35
        ],
        [
          "Prata",
          43
        ],
        [
          "Ouro",
          52
        ],
        [
          "Iridio",
          70
        ]
      ],
      "seedPrice": [
        [
          "Pierre",
          20
        ],
        [
          "Joja",
          25
        ]
      ],
      "artisanItems": [
        [
          "Pickles",
          "Preserves Jar",
          120
        ],
        [
          "Juice",
          "Keg",
          79
        ]
      ]
    },
    {
      "name": "Strawberry",
      "season": "Primavera",
      "icon": "cropSpring",
      "daysToHarvest": 8,
      "regrow": true,
      "daysToRegrowth": 4,
      "sellValue": [
        [
          "Normal",
          120
        ],
        [
          "Prata",
          150
        ],
        [
          "Ouro",
          180
        ],
        [
          "Iridio",
          240
        ]
      ],
      "seedPrice": [
        [
          "Egg Festival",
          100
        ]
      ],
      "artisanItems": [
        [
          "Jelly",
          "Preserves Jar",
          290
        ],
        [
          "Wine",
          "Keg",
          360
        ]
      ]
    },
    {
      "name": "Hops",
      "season": "Verao",
      "icon": "cropSummer",
      "daysToHarvest": 11,
      "regrow": true,
      "daysToRegrowth": 1,
      "sellValue": [
        [
          "Normal",
          25
        ],
        [
          "Prata",
          31
        ],
        [
          "Ouro",
          37
        ],
        [
          "Iridio",
          50
        ]
      ],
      "seedPrice": [
        [
          "Pierre",
          60
        ],
        [
          "Joja",
          75
        ]
      ],
      "artisanItems": [
        [
          "Pickles",
          "Preserves Jar",
          100
        ],
        [
          "Pale Ale",
          "Keg",
          300
        ]
      ]
    },
    {
      "name": "Hot Pepper",
      "season": "Verao",
      "icon": "cropSummer",
      "daysToHarvest": 5,
      "regrow": true,
      "daysToRegrowth": 3,
      "sellValue": [
        [
          "Normal",
          40
        ],
        [
          "Prata",
          50
        ],
        [
          "Ouro",
          60
        ],
        [
          "Iridio",
          80
        ]
      ],
      "seedPrice": [
        [
          "Pierre",
          40
        ],
        [
          "Joja",
          50
        ]
      ],
      "artisanItems": [
        [
          "Pickles",
          "Preserves Jar",
          130
        ],
        [
          "Juice",
          "Keg",
          90
        ]
      ]
    },
    {
      "name": "Melon",
      "season": "Verao",
      "icon": "cropSummer",
      "daysToHarvest": 12,
      "regrow": false,
      "daysToRegrowth": null,
      "sellValue": [
        [
          "Normal",
          250
        ],
        [
          "Prata",
          312
        ],
        [
          "Ouro",
          375
        ],
        [
          "Iridio",
          500
        ]
      ],
      "seedPrice": [
        [
          "Pierre",
          80
        ],
        [
          "Joja",
          100
        ]
      ],
      "artisanItems": [
        [
          "Jelly",
          "Preserves Jar",
          550
        ],
        [
          "Wine",
          "Keg",
          750
        ]
      ]
    },
    {
      "name": "Starfruit",
      "season": "Verao",
      "icon": "cropSummer",
      "daysToHarvest": 13,
      "regrow": false,
      "daysToRegrowth": null,
      "sellValue": [
        [
          "Normal",
          750
        ],
        [
          "Prata",
          937
        ],
        [
          "Ouro",
          1125
        ],
        [
          "Iridio",
          1500
        ]
      ],
      "seedPrice": [
        [
          "The Oasis",
          400
        ]
      ],
      "artisanItems": [
        [
          "Jelly",
          "Preserves Jar",
          1550
        ],
        [
          "Wine",
          "Keg",
          2250
        ]
      ]
    },
    {
      "name": "Tomato",
      "season": "Verao",
      "icon": "cropSummer",
      "daysToHarvest": 11,
      "regrow": true,
      "daysToRegrowth": 4,
      "sellValue": [
        [
          "Normal",
          60
        ],
        [
          "Prata",
          75
        ],
        [
          "Ouro",
          90
        ],
        [
          "Iridio",
          120
        ]
      ],
      "seedPrice": [
        [
          "Pierre",
          50
        ],
        [
          "Joja",
          62
        ]
      ],
      "artisanItems": [
        [
          "Pickles",
          "Preserves Jar",
          170
        ],
        [
          "Juice",
          "Keg",
          135
        ]
      ]
    },
    {
      "name": "Bok Choi",
      "season": "Outono",
      "icon": "cropFall",
      "daysToHarvest": 4,
      "regrow": false,
      "daysToRegrowth": null,
      "sellValue": [
        [
          "Normal",
          80
        ],
        [
          "Prata",
          100
        ],
        [
          "Ouro",
          120
        ],
        [
          "Iridio",
          160
        ]
      ],
      "seedPrice": [
        [
          "Pierre",
          50
        ],
        [
          "Joja",
          62
        ]
      ],
      "artisanItems": [
        [
          "Pickles",
          "Preserves Jar",
          210
        ],
        [
          "Juice",
          "Keg",
          180
        ]
      ]
    },
    {
      "name": "Broccoli",
      "season": "Outono",
      "icon": "cropFall",
      "daysToHarvest": 8,
      "regrow": true,
      "daysToRegrowth": 4,
      "sellValue": [
        [
          "Normal",
          70
        ],
        [
          "Prata",
          87
        ],
        [
          "Ouro",
          105
        ],
        [
          "Iridio",
          140
        ]
      ],
      "seedPrice": [
        [
          "Foraging",
          0
        ]
      ],
      "artisanItems": [
        [
          "Pickles",
          "Preserves Jar",
          190
        ],
        [
          "Juice",
          "Keg",
          158
        ]
      ]
    },
    {
      "name": "Cranberries",
      "season": "Outono",
      "icon": "cropFall",
      "daysToHarvest": 7,
      "regrow": true,
      "daysToRegrowth": 5,
      "sellValue": [
        [
          "Normal",
          75
        ],
        [
          "Prata",
          93
        ],
        [
          "Ouro",
          112
        ],
        [
          "Iridio",
          150
        ]
      ],
      "seedPrice": [
        [
          "Pierre",
          240
        ],
        [
          "Joja",
          300
        ]
      ],
      "artisanItems": [
        [
          "Jelly",
          "Preserves Jar",
          200
        ],
        [
          "Wine",
          "Keg",
          225
        ]
      ]
    },
    {
      "name": "Pumpkin",
      "season": "Outono",
      "icon": "cropFall",
      "daysToHarvest": 13,
      "regrow": false,
      "daysToRegrowth": null,
      "sellValue": [
        [
          "Normal",
          320
        ],
        [
          "Prata",
          400
        ],
        [
          "Ouro",
          480
        ],
        [
          "Iridio",
          640
        ]
      ],
      "seedPrice": [
        [
          "Pierre",
          100
        ],
        [
          "Joja",
          125
        ]
      ],
      "artisanItems": [
        [
          "Pickles",
          "Preserves Jar",
          690
        ],
        [
          "Juice",
          "Keg",
          720
        ]
      ]
    },
    {
      "name": "Grape",
      "season": "Outono",
      "icon": "cropFall",
      "daysToHarvest": 10,
      "regrow": true,
      "daysToRegrowth": 3,
      "sellValue": [
        [
          "Normal",
          80
        ],
        [
          "Prata",
          100
        ],
        [
          "Ouro",
          120
        ],
        [
          "Iridio",
          160
        ]
      ],
      "seedPrice": [
        [
          "Pierre",
          60
        ],
        [
          "Joja",
          75
        ]
      ],
      "artisanItems": [
        [
          "Jelly",
          "Preserves Jar",
          210
        ],
        [
          "Wine",
          "Keg",
          240
        ]
      ]
    },
    {
      "name": "Powdermelon",
      "season": "Inverno",
      "icon": "cropWinter",
      "daysToHarvest": 7,
      "regrow": false,
      "daysToRegrowth": null,
      "sellValue": [
        [
          "Normal",
          60
        ],
        [
          "Prata",
          75
        ],
        [
          "Ouro",
          90
        ],
        [
          "Iridio",
          120
        ]
      ],
      "seedPrice": [
        [
          "Foraging",
          0
        ]
      ],
      "artisanItems": [
        [
          "Jelly",
          "Preserves Jar",
          170
        ],
        [
          "Wine",
          "Keg",
          180
        ]
      ]
    }
  ],
  "villagers": [
    {
      "name": "Abigail",
      "single": true,
      "giftLove": "Amethyst",
      "giftLike": "Frozen Tear"
    },
    {
      "name": "Alex",
      "single": true,
      "giftLove": "Complete Breakfast",
      "giftLike": "Egg"
    },
    {
      "name": "Caroline",
      "single": false,
      "giftLove": "Green Tea",
      "giftLike": "Tea Leaves"
    },
    {
      "name": "Elliot",
      "single": true,
      "giftLove": "Pomegranate",
      "giftLike": "Frozen Tear"
    },
    {
      "name": "Emily",
      "single": true,
      "giftLove": "Cloth",
      "giftLike": "Frozen Tear"
    },
    {
      "name": "Evelyn",
      "single": false,
      "giftLove": "Diamond",
      "giftLike": "Milk"
    },
    {
      "name": "George",
      "single": false,
      "giftLove": "Leek",
      "giftLike": "Daffodil"
    },
    {
      "name": "Haley",
      "single": true,
      "giftLove": "Coconut",
      "giftLike": "Daffodil"
    },
    {
      "name": "Harvey",
      "single": true,
      "giftLove": "Wine",
      "giftLike": "Green Tea"
    },
    {
      "name": "Jodi",
      "single": false,
      "giftLove": "Diamond",
      "giftLike": "Egg"
    },
    {
      "name": "Leah",
      "single": true,
      "giftLove": "Wine",
      "giftLike": "Egg"
    },
    {
      "name": "Lewis",
      "single": false,
      "giftLove": "Green Tea",
      "giftLike": "Diamond"
    },
    {
      "name": "Marnie",
      "single": false,
      "giftLove": "Diamond",
      "giftLike": "Egg"
    },
    {
      "name": "Pam",
      "single": false,
      "giftLove": "Beer",
      "giftLike": "Milk"
    },
    {
      "name": "Penny",
      "single": true,
      "giftLove": "Diamond",
      "giftLike": "Milk"
    },
    {
      "name": "Robin",
      "single": false,
      "giftLove": "Goat Cheese",
      "giftLike": "Milk"
    },
    {
      "name": "Sam",
      "single": true,
      "giftLove": "Pizza",
      "giftLike": "Joja Cola"
    },
    {
      "name": "Sebastian",
      "single": true,
      "giftLove": "Frozen Tear",
      "giftLike": "Green Tea"
    },
    {
      "name": "Shane",
      "single": true,
      "giftLove": "Beer",
      "giftLike": "Egg"
    },
    {
      "name": "Willy",
      "single": false,
      "giftLove": "Diamond",
      "giftLike": "Amethyst"
    },
    {
      "name": "Wizard",
      "single": false,
      "giftLove": "Solar Essence",
      "giftLike": "Frozen Tear"
    }
  ],
  "animals": [
    {
      "name": "Cow",
      "type": "Barn",
      "icon": "animalCow",
      "produces": "Milk",
      "daysToAdult": 5,
      "buyPrice": 1500,
      "artisanItem": [
        [
          "Cheese",
          "Cheese Press",
          322
        ]
      ]
    },
    {
      "name": "Ostrich",
      "type": "Barn",
      "icon": "animalGeneric",
      "produces": "Ostrich Egg",
      "daysToAdult": 7,
      "buyPrice": null,
      "artisanItem": [
        [
          "Mayonnaise",
          "Mayonnaise Machine",
          266
        ]
      ]
    },
    {
      "name": "Goat",
      "type": "Big Barn",
      "icon": "animalGeneric",
      "produces": "Goat Milk",
      "daysToAdult": 5,
      "buyPrice": 4000,
      "artisanItem": [
        [
          "Goat Cheese",
          "Cheese Press",
          560
        ]
      ]
    },
    {
      "name": "Sheep",
      "type": "Deluxe Barn",
      "icon": "animalSheep",
      "produces": "Wool",
      "daysToAdult": 4,
      "buyPrice": 8000,
      "artisanItem": [
        [
          "Cloth",
          "Loom",
          658
        ]
      ]
    },
    {
      "name": "Pig",
      "type": "Deluxe Barn",
      "icon": "animalPig",
      "produces": "Truffle",
      "daysToAdult": 10,
      "buyPrice": 16000,
      "artisanItem": [
        [
          "Truffle Oil",
          "Oil Maker",
          1491
        ]
      ]
    },
    {
      "name": "Chicken",
      "type": "Coop",
      "icon": "animalChicken",
      "produces": "Egg",
      "daysToAdult": 3,
      "buyPrice": 800,
      "artisanItem": [
        [
          "Mayonnaise",
          "Mayonnaise Machine",
          266
        ]
      ]
    },
    {
      "name": "Duck",
      "type": "Big Coop",
      "icon": "animalGeneric",
      "produces": "Duck Egg",
      "daysToAdult": 5,
      "buyPrice": 1200,
      "artisanItem": [
        [
          "Duck Mayonnaise",
          "Mayonnaise Machine",
          525
        ]
      ]
    },
    {
      "name": "Dinosaur",
      "type": "Big Coop",
      "icon": "animalGeneric",
      "produces": "Dinosaur Egg",
      "daysToAdult": 0,
      "buyPrice": null,
      "artisanItem": [
        [
          "Dinosaur Mayonnaise",
          "Mayonnaise Machine",
          1120
        ]
      ]
    },
    {
      "name": "Rabbit",
      "type": "Deluxe Coop",
      "icon": "animalGeneric",
      "produces": "Rabbit'S Foot",
      "daysToAdult": 6,
      "buyPrice": 8000,
      "artisanItem": []
    }
  ],
  "buildings": [
    {
      "name": "Barn",
      "icon": "buildingBarn",
      "constructionMaterials": [
        [
          "Gold",
          6000
        ],
        [
          "Wood",
          350
        ],
        [
          "Stone",
          150
        ]
      ],
      "size": [
        7,
        4
      ],
      "whereToGet": "Robin (Carpintaria)",
      "housesAnimals": true,
      "animalTypes": [
        "Cow",
        "Ostrich"
      ],
      "animalAmount": 4
    },
    {
      "name": "Big Barn",
      "icon": "buildingBarn",
      "constructionMaterials": [
        [
          "Gold",
          12000
        ],
        [
          "Wood",
          450
        ],
        [
          "Stone",
          200
        ]
      ],
      "size": [
        7,
        4
      ],
      "whereToGet": "Robin (Carpintaria)",
      "housesAnimals": true,
      "animalTypes": [
        "Cow",
        "Ostrich",
        "Goat"
      ],
      "animalAmount": 8
    },
    {
      "name": "Deluxe Barn",
      "icon": "buildingBarn",
      "constructionMaterials": [
        [
          "Gold",
          25000
        ],
        [
          "Wood",
          550
        ],
        [
          "Stone",
          300
        ]
      ],
      "size": [
        7,
        4
      ],
      "whereToGet": "Robin (Carpintaria)",
      "housesAnimals": true,
      "animalTypes": [
        "Cow",
        "Ostrich",
        "Goat",
        "Sheep",
        "Pig"
      ],
      "animalAmount": 12
    },
    {
      "name": "Coop",
      "icon": "buildingCoop",
      "constructionMaterials": [
        [
          "Gold",
          4000
        ],
        [
          "Wood",
          300
        ],
        [
          "Stone",
          100
        ]
      ],
      "size": [
        6,
        3
      ],
      "whereToGet": "Robin (Carpintaria)",
      "housesAnimals": true,
      "animalTypes": [
        "Chicken"
      ],
      "animalAmount": 4
    },
    {
      "name": "Big Coop",
      "icon": "buildingCoop",
      "constructionMaterials": [
        [
          "Gold",
          10000
        ],
        [
          "Wood",
          400
        ],
        [
          "Stone",
          150
        ]
      ],
      "size": [
        6,
        3
      ],
      "whereToGet": "Robin (Carpintaria)",
      "housesAnimals": true,
      "animalTypes": [
        "Chicken",
        "Duck",
        "Dinosaur"
      ],
      "animalAmount": 8
    },
    {
      "name": "Deluxe Coop",
      "icon": "buildingCoop",
      "constructionMaterials": [
        [
          "Gold",
          20000
        ],
        [
          "Wood",
          500
        ],
        [
          "Stone",
          200
        ]
      ],
      "size": [
        6,
        3
      ],
      "whereToGet": "Robin (Carpintaria)",
      "housesAnimals": true,
      "animalTypes": [
        "Chicken",
        "Duck",
        "Dinosaur",
        "Rabbit"
      ],
      "animalAmount": 12
    },
    {
      "name": "Fish Pond",
      "icon": "buildingSilo",
      "constructionMaterials": [
        [
          "Gold",
          5000
        ],
        [
          "Stone",
          200
        ],
        [
          "Green Algae",
          5
        ],
        [
          "Seaweed",
          5
        ]
      ],
      "size": [
        5,
        5
      ],
      "whereToGet": "Robin (Carpintaria)",
      "housesAnimals": true,
      "animalTypes": [
        "Fish"
      ],
      "animalAmount": 3
    },
    {
      "name": "Shed",
      "icon": "buildingSilo",
      "constructionMaterials": [
        [
          "Gold",
          15000
        ],
        [
          "Wood",
          300
        ]
      ],
      "size": [
        7,
        3
      ],
      "whereToGet": "Robin (Carpintaria)",
      "housesAnimals": false,
      "animalTypes": [],
      "animalAmount": 0
    },
    {
      "name": "Big Shed",
      "icon": "buildingSilo",
      "constructionMaterials": [
        [
          "Gold",
          20000
        ],
        [
          "Wood",
          550
        ],
        [
          "Stone",
          300
        ]
      ],
      "size": [
        7,
        3
      ],
      "whereToGet": "Robin (Carpintaria)",
      "housesAnimals": false,
      "animalTypes": [],
      "animalAmount": 0
    },
    {
      "name": "Silo",
      "icon": "buildingSilo",
      "constructionMaterials": [
        [
          "Gold",
          100
        ],
        [
          "Clay",
          10
        ],
        [
          "Stone",
          100
        ],
        [
          "Copper Bar",
          5
        ]
      ],
      "size": [
        3,
        3
      ],
      "whereToGet": "Robin (Carpintaria)",
      "housesAnimals": false,
      "animalTypes": [],
      "animalAmount": 0
    },
    {
      "name": "Stable",
      "icon": "buildingSilo",
      "constructionMaterials": [
        [
          "Gold",
          10000
        ],
        [
          "Hardwood",
          100
        ],
        [
          "Iron Bar",
          5
        ]
      ],
      "size": [
        4,
        2
      ],
      "whereToGet": "Robin (Carpintaria)",
      "housesAnimals": true,
      "animalTypes": [
        "Horse"
      ],
      "animalAmount": 1
    },
    {
      "name": "Well",
      "icon": "buildingSilo",
      "constructionMaterials": [
        [
          "Gold",
          1000
        ],
        [
          "Stone",
          75
        ]
      ],
      "size": [
        3,
        3
      ],
      "whereToGet": "Robin (Carpintaria)",
      "housesAnimals": false,
      "animalTypes": [],
      "animalAmount": 0
    },
    {
      "name": "Earth Obelisk",
      "icon": "buildingSilo",
      "constructionMaterials": [
        [
          "Gold",
          500000
        ],
        [
          "Earth Crystal",
          10
        ],
        [
          "Iridium Bar",
          10
        ]
      ],
      "size": [
        3,
        2
      ],
      "whereToGet": "Torre do Mago (Wizard)",
      "housesAnimals": false,
      "animalTypes": [],
      "animalAmount": 0
    },
    {
      "name": "Water Obelisk",
      "icon": "buildingSilo",
      "constructionMaterials": [
        [
          "Gold",
          500000
        ],
        [
          "Coral",
          10
        ],
        [
          "Clam",
          10
        ],
        [
          "Iridium Bar",
          5
        ]
      ],
      "size": [
        3,
        2
      ],
      "whereToGet": "Torre do Mago (Wizard)",
      "housesAnimals": false,
      "animalTypes": [],
      "animalAmount": 0
    },
    {
      "name": "Desert Obelisk",
      "icon": "buildingSilo",
      "constructionMaterials": [
        [
          "Gold",
          1000000
        ],
        [
          "Coconut",
          10
        ],
        [
          "Cactus Fruit",
          10
        ],
        [
          "Iridium Bar",
          20
        ]
      ],
      "size": [
        3,
        2
      ],
      "whereToGet": "Torre do Mago (Wizard)",
      "housesAnimals": false,
      "animalTypes": [],
      "animalAmount": 0
    },
    {
      "name": "Island Obelisk",
      "icon": "buildingSilo",
      "constructionMaterials": [
        [
          "Gold",
          1000000
        ],
        [
          "Dragon Tooth",
          10
        ],
        [
          "Banana",
          10
        ],
        [
          "Iridium Bar",
          10
        ]
      ],
      "size": [
        3,
        2
      ],
      "whereToGet": "Torre do Mago (Wizard)",
      "housesAnimals": false,
      "animalTypes": [],
      "animalAmount": 0
    },
    {
      "name": "Junimo Hut",
      "icon": "buildingSilo",
      "constructionMaterials": [
        [
          "Gold",
          20000
        ],
        [
          "Stone",
          200
        ],
        [
          "Fiber",
          100
        ],
        [
          "Starfruit",
          9
        ]
      ],
      "size": [
        3,
        2
      ],
      "whereToGet": "Torre do Mago (Wizard)",
      "housesAnimals": false,
      "animalTypes": [],
      "animalAmount": 0
    }
  ],
  "myFarm": {
    "farmName": "Minha Fazenda",
    "farmLayout": "Padrao",
    "myAnimals": [],
    "myBuildings": [],
    "myRelationships": []
  }
};
