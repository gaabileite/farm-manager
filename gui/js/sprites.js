/*
 * sprites.js
 * ---------------------------------------------------------------
 * Icon resolver for the Farm Manager GUI.
 *
 * Every icon is a real, standalone PNG file under gui/public/icons/.
 * To change how something looks, just overwrite the matching .png
 * file in an image editor — nothing here needs to change. This
 * module only knows each icon's native pixel size (so it can be
 * scaled up crisply via width/height + CSS `image-rendering:
 * pixelated`) and a couple of small name-picking helpers.
 *
 * The default files were generated from scratch (no game assets)
 * by gui/tools/generate-icons.js — see that script if you ever want
 * to regenerate the original placeholder set.
 * ---------------------------------------------------------------
 */

const Sprites = (() => {
    const BASE_PATH = 'public/icons/';

    // native pixel-grid size of each icon file, used to size the
    // <img> so it upscales crisply instead of blurry/smoothed
    const SIZES = {
        cropSpring: [10, 10], cropSummer: [10, 10], cropFall: [10, 10], cropWinter: [10, 10],
        animalChicken: [10, 10], animalCow: [10, 10], animalPig: [10, 10], animalSheep: [10, 10], animalGeneric: [10, 10],
        buildingCoop: [10, 10], buildingBarn: [10, 10], buildingSilo: [10, 10],
        bookCrop: [12, 14], bookVillager: [12, 14], bookAnimal: [12, 14], bookBuilding: [12, 14], bookFarm: [12, 14],
        farmhouse: [12, 10],
        heartFull: [8, 8], heartEmpty: [8, 8],
    };
    const DEFAULT_SIZE = [10, 10];
    const VILLAGER_BUST_VARIANTS = 8;

    const BOOK_BY_SECTION = {
        crops: 'bookCrop',
        villagers: 'bookVillager',
        animals: 'bookAnimal',
        buildings: 'bookBuilding',
        myfarm: 'bookFarm',
    };

    function hashIndex(str, mod) {
        let h = 0;
        for (let i = 0; i < str.length; i++) h = (h * 31 + str.charCodeAt(i)) >>> 0;
        return h % mod;
    }

    // Creates an <img> pointing at public/icons/<name>.png, sized to
    // its native pixel grid times `scale` (default 6x).
    function makeImage(name, { scale = 6 } = {}) {
        const [w, h] = SIZES[name] || DEFAULT_SIZE;
        const img = document.createElement('img');
        img.className = 'pixel-sprite';
        img.src = `${BASE_PATH}${name}.png`;
        img.width = w * scale;
        img.height = h * scale;
        img.alt = '';
        img.setAttribute('aria-hidden', 'true');
        return img;
    }

    // Villager portraits are pre-recolored PNG variants
    // (villagerBust-0.png .. villagerBust-7.png). The same villager
    // name always maps to the same variant, so nobody's portrait
    // changes color between renders.
    function villagerBust(name, opts) {
        const idx = hashIndex(name, VILLAGER_BUST_VARIANTS);
        return makeImage(`villagerBust-${idx}`, opts);
    }

    // Each shelf section has its own pre-colored book cover PNG.
    function bookIcon(sectionKey, opts) {
        return makeImage(BOOK_BY_SECTION[sectionKey] || 'bookCrop', opts);
    }

    return { makeImage, villagerBust, bookIcon, SIZES };
})();
