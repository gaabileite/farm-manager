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
 * pixelated`) and a small name-picking helper. Which icon each
 * item uses is decided by gui/tools/export-data.js (item.icon).
 *
 * The small default files (books, hearts, season crops) were
 * generated from scratch by gui/tools/generate-icons.js — see that
 * script if you ever want to regenerate a missing placeholder.
 * ---------------------------------------------------------------
 */

const Sprites = (() => {
    const BASE_PATH = 'public/icons/';

    // Icons come in any size (tiny 8x8 pixel art up to hand-drawn
    // ~800px art), so each <img> gets a fixed box of BOX_UNITS * scale
    // pixels and the image is fit inside it keeping its aspect ratio.
    // Only the few non-square defaults need their proportions listed.
    const BOX_UNITS = 10;
    const SIZES = {
        bookCrop: [12, 14], bookVillager: [12, 14], bookAnimal: [12, 14], bookBuilding: [12, 14], bookFarm: [12, 14],
        heartFull: [7, 7], heartEmpty: [7, 7],
    };

    const BOOK_BY_SECTION = {
        crops: 'bookCrop',
        villagers: 'bookVillager',
        animals: 'bookAnimal',
        buildings: 'bookBuilding',
        myfarm: 'bookFarm',
    };

    // Creates an <img> pointing at public/icons/<name>.png, fit into
    // a box of its listed size (or BOX_UNITS square) times `scale`.
    function makeImage(name, { scale = 6 } = {}) {
        const [w, h] = SIZES[name] || [BOX_UNITS, BOX_UNITS];
        const img = document.createElement('img');
        img.className = 'pixel-sprite';
        img.src = `${BASE_PATH}${name}.png`;
        img.width = w * scale;
        img.height = h * scale;
        img.alt = '';
        img.setAttribute('aria-hidden', 'true');
        // nearest-neighbour keeps tiny pixel art crisp when scaled up,
        // but makes big art jagged when scaled down — smooth those
        img.addEventListener('load', () => {
            if (img.naturalWidth > img.width || img.naturalHeight > img.height) {
                img.style.imageRendering = 'auto';
            }
        });
        return img;
    }

    // Each shelf section has its own pre-colored book cover PNG.
    function bookIcon(sectionKey, opts) {
        return makeImage(BOOK_BY_SECTION[sectionKey] || 'bookCrop', opts);
    }

    return { makeImage, bookIcon, SIZES };
})();
