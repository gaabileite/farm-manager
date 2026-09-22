/*
 * sprites.js
 * ---------------------------------------------------------------
 * Pixel-art renderer + sprite matrices for the Farm Manager GUI.
 *
 * Every sprite is 100% original: hand-authored as a small grid of
 * palette letters and drawn onto a <canvas> with image-rendering
 * disabled smoothing (crisp pixels). No game assets are used or
 * referenced — this keeps the interface original artwork while
 * still evoking the Stardew Valley / cozy-library mood requested.
 * ---------------------------------------------------------------
 */

const Sprites = (() => {
    const TRANSPARENT = '.';

    /**
     * Draws a sprite matrix onto a canvas.
     * @param {HTMLCanvasElement} canvas
     * @param {string[]} rows - each row is a string of palette keys
     * @param {Object} palette - maps a single character to a CSS color
     * @param {number} width - logical pixel width of the sprite grid
     * @param {number} height - logical pixel height of the sprite grid
     * @param {number} scale - how many screen pixels per sprite pixel
     */
    function draw(canvas, rows, palette, width, height, scale = 6) {
        canvas.width = width * scale;
        canvas.height = height * scale;
        const ctx = canvas.getContext('2d');
        ctx.imageSmoothingEnabled = false;

        for (let y = 0; y < height; y++) {
            const row = rows[y] || '';
            for (let x = 0; x < width; x++) {
                const key = row[x] || TRANSPARENT;
                if (key === TRANSPARENT) continue;
                const color = palette[key];
                if (!color) continue;
                ctx.fillStyle = color;
                ctx.fillRect(x * scale, y * scale, scale, scale);
            }
        }
    }

    // Renders a sprite by name into a freshly created <canvas>,
    // optionally overriding palette entries (used for villager
    // recoloring so one bust matrix can produce many characters).
    function makeCanvas(name, { scale = 6, paletteOverride = {} } = {}) {
        const def = DEFS[name];
        if (!def) throw new Error(`Unknown sprite "${name}"`);
        const canvas = document.createElement('canvas');
        canvas.className = 'pixel-sprite';
        canvas.setAttribute('aria-hidden', 'true');
        const palette = { ...def.palette, ...paletteOverride };
        draw(canvas, def.rows, palette, def.w, def.h, scale);
        return canvas;
    }

    // ---- Palettes ---------------------------------------------------
    const wood = { c: '#a9743b', C: '#c98f4f', d: '#5b3a21', y: '#f3d16b' };
    const soil = { S: '#7a5230', s: '#5b3a21' };

    // ---- Sprite matrices (grid of palette-letter strings) -----------
    const DEFS = {
        cropSpring: {
            w: 10, h: 10,
            palette: { G: '#6fae3e', g: '#3f6b2b', ...soil },
            rows: [
                '.....G....',
                '....GgG...',
                '.....g....',
                '....GgG...',
                '.....g....',
                '.....g....',
                '..SSSSSS..',
                '.SSssssSS.',
                '.SssssssS.',
                '..SSSSSS..',
            ],
        },
        cropSummer: {
            w: 10, h: 10,
            palette: { G: '#6fae3e', g: '#3f6b2b', b: '#3a5fb0', B: '#6f8fd6', ...soil },
            rows: [
                '..GGGGGG..',
                '.GGgBGgGG.',
                'GGgbGGbgGG',
                '.GgGGGGgG.',
                'GgbGGGGbgG',
                '.GGGGGGGG.',
                '..SSSSSS..',
                '.SSssssSS.',
                '.SssssssS.',
                '..SSSSSS..',
            ],
        },
        cropFall: {
            w: 10, h: 10,
            palette: { g: '#3f6b2b', o: '#c9711f', O: '#e8934a', ...soil },
            rows: [
                '...gg.....',
                '...gg.....',
                '..OOOOOO..',
                '.OooooooO.',
                'OooOOooooO',
                'OoooooooOO',
                '.OooooooO.',
                '..SSSSSS..',
                '.SssssssS.',
                '..SSSSSS..',
            ],
        },
        cropWinter: {
            w: 10, h: 10,
            palette: { c: '#bfe3ec', C: '#eaf9fc', g: '#5c8a8f', ...soil },
            rows: [
                '.....c....',
                '....cCc...',
                '.....g....',
                '....cCc...',
                '.....g....',
                '.....g....',
                '..SSSSSS..',
                '.SScccSS..',
                '.ScccccS..',
                '..SSSSSS..',
            ],
        },
        animalChicken: {
            w: 10, h: 10,
            palette: { w: '#f2ead9', W: '#ffffff', r: '#c23b3b', y: '#e0a83a', k: '#2a1f14' },
            rows: [
                '...rr.....',
                '..wwwy....',
                '.wwWWww...',
                '.wkWWww...',
                '.wwwwww...',
                '..wwwwyw..',
                '..wwwwww..',
                '...wwww...',
                '...y..y...',
                '..........',
            ],
        },
        animalCow: {
            w: 10, h: 10,
            palette: { w: '#f2ead9', k: '#2a2a2a', p: '#d98a8a' },
            rows: [
                '..kk..kk..',
                '.wwwwwwww.',
                'wwkwwwwkww',
                'wwwwwwwwww',
                'wwwwkkwwww',
                '.wwwwwwww.',
                '..wppppw..',
                '..wwwwww..',
                '..w....w..',
                '..........',
            ],
        },
        animalPig: {
            w: 10, h: 10,
            palette: { p: '#e8a3a3', P: '#f3c6c6', n: '#7a4a4a' },
            rows: [
                '..........',
                '..PPPPPP..',
                '.pppppppp.',
                'ppppppppp.',
                'ppnppnpp..',
                'ppppppppp.',
                '.pppppppp.',
                '..pp..pp..',
                '..........',
                '..........',
            ],
        },
        animalSheep: {
            w: 10, h: 10,
            palette: { c: '#f5f0e0', C: '#ffffff', k: '#2a2a2a' },
            rows: [
                '.CCCCCCCC.',
                'CccccccccC',
                'ccckkccccc',
                'cccccccccc',
                'cccccccccc',
                '.cccccccc.',
                '..k....k..',
                '..k....k..',
                '..........',
                '..........',
            ],
        },
        // Generic fallback for catalog animals without a dedicated
        // sprite (e.g. Ostrich, Goat, Duck, Dinosaur, Rabbit) — a
        // paw print, deliberately not shaped like any specific
        // creature so it never misrepresents the real animal.
        animalGeneric: {
            w: 10, h: 10,
            palette: { p: '#a9743b', P: '#c98f4f' },
            rows: [
                '..........',
                '.Pp....Pp.',
                '.pp....pp.',
                '..........',
                '...PppP...',
                '..ppppppp.',
                '..ppppppp.',
                '...ppppp..',
                '..........',
                '..........',
            ],
        },
        buildingCoop: {
            w: 10, h: 10,
            palette: { r: '#8a3b2a', y: '#f3d16b', ...wood },
            rows: [
                '..rrrrrr..',
                '.rrrrrrrr.',
                'cccccccccc',
                'ccyyccyycc',
                'ccyyccyycc',
                'cccccccccc',
                'cccddccccc',
                'cccddccccc',
                'cccccccccc',
                '..........',
            ],
        },
        buildingBarn: {
            w: 10, h: 10,
            palette: { r: '#5c2418', w: '#9c3b2a', l: '#c96b52', d: '#4a2f1c', y: '#f3d16b' },
            rows: [
                '...rrrr...',
                '..rrrrrr..',
                '.rrrrrrrr.',
                'wwwwwwwwww',
                'wwyllllyww',
                'wwlwwwwlww',
                'wwlwddwlww',
                'wwlwddwlww',
                'wwwwwwwwww',
                '..........',
            ],
        },
        buildingSilo: {
            w: 10, h: 10,
            palette: { g: '#b0aca0', G: '#d8d4c8', r: '#8a3b2a' },
            rows: [
                '...rrrr...',
                '..rrrrrr..',
                '..GgggG...',
                '..gggggg..',
                '..GgggG...',
                '..gggggg..',
                '..GgggG...',
                '..gggggg..',
                '..gggggg..',
                '..gggggg..',
            ],
        },
        book: {
            w: 12, h: 14,
            palette: { h: '#f3d16b', c: '#7a5a3a', p: '#f4e4bc', b: '#2a1a10' },
            rows: [
                '.hhhhhhhhh..',
                'bcccccccccc.',
                'bcppppppppc.',
                'bcpppppppc..',
                'bcppppppppc.',
                'bcpppppppc..',
                'bcppppppppc.',
                'bcpppppppc..',
                'bcppppppppc.',
                'bcccccccccc.',
                'bbbbbbbbbbb.',
            ],
        },
        farmhouse: {
            w: 12, h: 10,
            palette: { w: '#e8d9b5', r: '#8a3b2a', d: '#5b3a21', y: '#f3d16b' },
            rows: [
                '....rrrr....',
                '...rrrrrr...',
                '..rrrrrrrr..',
                '.rrrrrrrrrr.',
                'wwwwwwwwwwww',
                'wwyy.ww.yyww',
                'wwwwwwwwwwww',
                'wwwwddwwwwww',
                'wwwwddwwwwww',
                'wwwwwwwwwwww',
            ],
        },
        heartFull: {
            w: 8, h: 8,
            palette: { r: '#d9435c', R: '#ef7a8e' },
            rows: [
                '.RR.RR..',
                'rrrrrrr.',
                'rrrrrrr.',
                '.rrrrr..',
                '..rrr...',
                '...r....',
                '........',
                '........',
            ],
        },
        heartEmpty: {
            w: 8, h: 8,
            palette: { o: '#8a6a5a' },
            rows: [
                '.oo.oo..',
                'o..o..o.',
                'o......o',
                '.o....o.',
                '..o..o..',
                '...oo...',
                '........',
                '........',
            ],
        },
        villagerBust: {
            w: 10, h: 10,
            // default palette can be overridden per-villager (hair/shirt)
            palette: { k: '#4a3222', s: '#e0ab7a', e: '#2a1f14', m: '#8a5a45', c: '#4a6b8a' },
            rows: [
                '..kkkkkk..',
                '.kkkkkkkk.',
                '.ksssssk..',
                '.sseesss..',
                '.ssssssss.',
                '..smssss..',
                '..ssssss..',
                '.cccccccc.',
                'cccccccccc',
                'cccccccccc',
            ],
        },
    };

    return { makeCanvas, DEFS };
})();
