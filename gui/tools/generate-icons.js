/*
 * generate-icons.js
 * ---------------------------------------------------------------
 * One-time (or "reset to default") generator: bakes the GUI's
 * original pixel-art matrices into real, standalone PNG files at
 * gui/public/icons/*.png. Uses only Node's built-in `fs`/`zlib` —
 * no npm packages, no canvas library.
 *
 * After this runs, the PNG files ARE the artwork: open any of them
 * in an image editor (Aseprite, GIMP, Paint, ...) and overwrite the
 * file to change what the GUI shows — no code edit needed. This
 * script only exists to (re)create a default set from scratch.
 *
 * Run with:  node gui/tools/generate-icons.js
 * ---------------------------------------------------------------
 */

const fs = require('fs');
const path = require('path');
const zlib = require('zlib');

const OUT_DIR = path.resolve(__dirname, '..', 'public', 'icons');

// ---- minimal PNG encoder (RGBA, 8-bit, no interlace) ---------------------
const CRC_TABLE = (() => {
  const table = [];
  for (let n = 0; n < 256; n++) {
    let c = n;
    for (let k = 0; k < 8; k++) c = (c & 1) ? (0xEDB88320 ^ (c >>> 1)) : (c >>> 1);
    table[n] = c >>> 0;
  }
  return table;
})();
function crc32(buf) {
  let crc = 0xFFFFFFFF;
  for (let i = 0; i < buf.length; i++) crc = CRC_TABLE[(crc ^ buf[i]) & 0xFF] ^ (crc >>> 8);
  return (crc ^ 0xFFFFFFFF) >>> 0;
}
function chunk(type, data) {
  const typeBuf = Buffer.from(type, 'ascii');
  const lenBuf = Buffer.alloc(4);
  lenBuf.writeUInt32BE(data.length, 0);
  const crcBuf = Buffer.alloc(4);
  crcBuf.writeUInt32BE(crc32(Buffer.concat([typeBuf, data])), 0);
  return Buffer.concat([lenBuf, typeBuf, data, crcBuf]);
}
function encodePNG(width, height, rgba) {
  const sig = Buffer.from([137, 80, 78, 71, 13, 10, 26, 10]);
  const ihdrData = Buffer.alloc(13);
  ihdrData.writeUInt32BE(width, 0);
  ihdrData.writeUInt32BE(height, 4);
  ihdrData[8] = 8; // bit depth
  ihdrData[9] = 6; // color type: RGBA
  ihdrData[10] = 0; ihdrData[11] = 0; ihdrData[12] = 0;

  const stride = width * 4;
  const raw = Buffer.alloc((stride + 1) * height);
  for (let y = 0; y < height; y++) {
    raw[y * (stride + 1)] = 0; // filter: none
    rgba.copy(raw, y * (stride + 1) + 1, y * stride, y * stride + stride);
  }
  const idatData = zlib.deflateSync(raw, { level: 9 });
  return Buffer.concat([sig, chunk('IHDR', ihdrData), chunk('IDAT', idatData), chunk('IEND', Buffer.alloc(0))]);
}

// ---- rasterize a palette-letter grid into an RGBA buffer -----------------
function hexToRgba(hex) {
  const h = hex.replace('#', '');
  return [parseInt(h.slice(0, 2), 16), parseInt(h.slice(2, 4), 16), parseInt(h.slice(4, 6), 16), 255];
}
function rasterize(rows, palette, w, h) {
  const buf = Buffer.alloc(w * h * 4); // transparent by default
  for (let y = 0; y < h; y++) {
    const row = rows[y] || '';
    for (let x = 0; x < w; x++) {
      const key = row[x] || '.';
      if (key === '.') continue;
      const color = palette[key];
      if (!color) continue;
      const [r, g, b, a] = hexToRgba(color);
      const i = (y * w + x) * 4;
      buf[i] = r; buf[i + 1] = g; buf[i + 2] = b; buf[i + 3] = a;
    }
  }
  return buf;
}
function writeIcon(name, def) {
  const buf = rasterize(def.rows, def.palette, def.w, def.h);
  const png = encodePNG(def.w, def.h, buf);
  fs.writeFileSync(path.join(OUT_DIR, `${name}.png`), png);
}

// ---- shared palette fragments ---------------------------------------------
const wood = { c: '#a9743b', C: '#c98f4f', d: '#5b3a21', y: '#f3d16b' };
const soil = { S: '#7a5230', s: '#5b3a21' };

// ---- sprite matrices (same artwork the GUI used to draw on <canvas>) -----
const DEFS = {
  cropSpring: {
    w: 10, h: 10,
    palette: { G: '#6fae3e', g: '#3f6b2b', ...soil },
    rows: ['.....G....', '....GgG...', '.....g....', '....GgG...', '.....g....', '.....g....', '..SSSSSS..', '.SSssssSS.', '.SssssssS.', '..SSSSSS..'],
  },
  cropSummer: {
    w: 10, h: 10,
    palette: { G: '#6fae3e', g: '#3f6b2b', b: '#3a5fb0', B: '#6f8fd6', ...soil },
    rows: ['..GGGGGG..', '.GGgBGgGG.', 'GGgbGGbgGG', '.GgGGGGgG.', 'GgbGGGGbgG', '.GGGGGGGG.', '..SSSSSS..', '.SSssssSS.', '.SssssssS.', '..SSSSSS..'],
  },
  cropFall: {
    w: 10, h: 10,
    palette: { g: '#3f6b2b', o: '#c9711f', O: '#e8934a', ...soil },
    rows: ['...gg.....', '...gg.....', '..OOOOOO..', '.OooooooO.', 'OooOOooooO', 'OoooooooOO', '.OooooooO.', '..SSSSSS..', '.SssssssS.', '..SSSSSS..'],
  },
  cropWinter: {
    w: 10, h: 10,
    palette: { c: '#bfe3ec', C: '#eaf9fc', g: '#5c8a8f', ...soil },
    rows: ['.....c....', '....cCc...', '.....g....', '....cCc...', '.....g....', '.....g....', '..SSSSSS..', '.SScccSS..', '.ScccccS..', '..SSSSSS..'],
  },
  animalChicken: {
    w: 10, h: 10,
    palette: { w: '#f2ead9', W: '#ffffff', r: '#c23b3b', y: '#e0a83a', k: '#2a1f14' },
    rows: ['...rr.....', '..wwwy....', '.wwWWww...', '.wkWWww...', '.wwwwww...', '..wwwwyw..', '..wwwwww..', '...wwww...', '...y..y...', '..........'],
  },
  animalCow: {
    w: 10, h: 10,
    palette: { w: '#f2ead9', k: '#2a2a2a', p: '#d98a8a' },
    rows: ['..kk..kk..', '.wwwwwwww.', 'wwkwwwwkww', 'wwwwwwwwww', 'wwwwkkwwww', '.wwwwwwww.', '..wppppw..', '..wwwwww..', '..w....w..', '..........'],
  },
  animalPig: {
    w: 10, h: 10,
    palette: { p: '#e8a3a3', P: '#f3c6c6', n: '#7a4a4a' },
    rows: ['..........', '..PPPPPP..', '.pppppppp.', 'ppppppppp.', 'ppnppnpp..', 'ppppppppp.', '.pppppppp.', '..pp..pp..', '..........', '..........'],
  },
  animalSheep: {
    w: 10, h: 10,
    palette: { c: '#f5f0e0', C: '#ffffff', k: '#2a2a2a' },
    rows: ['.CCCCCCCC.', 'CccccccccC', 'ccckkccccc', 'cccccccccc', 'cccccccccc', '.cccccccc.', '..k....k..', '..k....k..', '..........', '..........'],
  },
  animalGeneric: {
    w: 10, h: 10,
    palette: { p: '#a9743b', P: '#c98f4f' },
    rows: ['..........', '.Pp....Pp.', '.pp....pp.', '..........', '...PppP...', '..ppppppp.', '..ppppppp.', '...ppppp..', '..........', '..........'],
  },
  buildingCoop: {
    w: 10, h: 10,
    palette: { r: '#8a3b2a', y: '#f3d16b', ...wood },
    rows: ['..rrrrrr..', '.rrrrrrrr.', 'cccccccccc', 'ccyyccyycc', 'ccyyccyycc', 'cccccccccc', 'cccddccccc', 'cccddccccc', 'cccccccccc', '..........'],
  },
  buildingBarn: {
    w: 10, h: 10,
    palette: { r: '#5c2418', w: '#9c3b2a', l: '#c96b52', d: '#4a2f1c', y: '#f3d16b' },
    rows: ['...rrrr...', '..rrrrrr..', '.rrrrrrrr.', 'wwwwwwwwww', 'wwyllllyww', 'wwlwwwwlww', 'wwlwddwlww', 'wwlwddwlww', 'wwwwwwwwww', '..........'],
  },
  buildingSilo: {
    w: 10, h: 10,
    palette: { g: '#b0aca0', G: '#d8d4c8', r: '#8a3b2a' },
    rows: ['...rrrr...', '..rrrrrr..', '..GgggG...', '..gggggg..', '..GgggG...', '..gggggg..', '..GgggG...', '..gggggg..', '..gggggg..', '..gggggg..'],
  },
  farmhouse: {
    w: 12, h: 10,
    palette: { w: '#e8d9b5', r: '#8a3b2a', d: '#5b3a21', y: '#f3d16b' },
    rows: ['....rrrr....', '...rrrrrr...', '..rrrrrrrr..', '.rrrrrrrrrr.', 'wwwwwwwwwwww', 'wwyy.ww.yyww', 'wwwwwwwwwwww', 'wwwwddwwwwww', 'wwwwddwwwwww', 'wwwwwwwwwwww'],
  },
  heartFull: {
    w: 8, h: 8,
    palette: { r: '#d9435c', R: '#ef7a8e' },
    rows: ['.RR.RR..', 'rrrrrrr.', 'rrrrrrr.', '.rrrrr..', '..rrr...', '...r....', '........', '........'],
  },
  heartEmpty: {
    w: 8, h: 8,
    palette: { o: '#8a6a5a' },
    rows: ['.oo.oo..', 'o..o..o.', 'o......o', '.o....o.', '..o..o..', '...oo...', '........', '........'],
  },
};

const BOOK_ROWS = [
  '.hhhhhhhhh..', 'bcccccccccc.', 'bcppppppppc.', 'bcpppppppc..', 'bcppppppppc.',
  'bcpppppppc..', 'bcppppppppc.', 'bcpppppppc..', 'bcppppppppc.', 'bcccccccccc.', 'bbbbbbbbbbb.',
];
// one book PNG per shelf/section, pre-colored with that section's accent
const BOOK_VARIANTS = {
  bookCrop: '#6b8f3f',
  bookVillager: '#4a6b8a',
  bookAnimal: '#b5482a',
  bookBuilding: '#d9a441',
  bookFarm: '#7a5a8f',
};
for (const [name, cover] of Object.entries(BOOK_VARIANTS)) {
  DEFS[name] = {
    w: 12, h: 14,
    palette: { h: '#f3d16b', c: cover, p: '#f4e4bc', b: '#2a1a10' },
    rows: BOOK_ROWS,
  };
}

const VILLAGER_BUST_ROWS = [
  '..kkkkkk..', '.kkkkkkkk.', '.ksssssk..', '.sseesss..', '.ssssssss.',
  '..smssss..', '..ssssss..', '.cccccccc.', 'cccccccccc', 'cccccccccc',
];
// pre-recolored variants (hair, shirt) — app.js picks one per villager by
// hashing the villager's name, so the same villager always looks the same
const BUST_PAIRS = [
  ['#4a3222', '#6b8f3f'], ['#2a2a2a', '#4a6b8a'], ['#8a3b2a', '#b5482a'], ['#5c3a28', '#d9a441'],
  ['#6b4226', '#7a5a8f'], ['#7a5230', '#3f6b2b'], ['#3a3a3a', '#8a5a45'], ['#4a3222', '#4a6b8a'],
];
BUST_PAIRS.forEach(([hair, shirt], i) => {
  DEFS[`villagerBust-${i}`] = {
    w: 10, h: 10,
    palette: { k: hair, s: '#e0ab7a', e: '#2a1f14', m: '#8a5a45', c: shirt },
    rows: VILLAGER_BUST_ROWS,
  };
});

// ---- main ----------------------------------------------------
fs.mkdirSync(OUT_DIR, { recursive: true });
let count = 0;
for (const [name, def] of Object.entries(DEFS)) {
  writeIcon(name, def);
  count++;
}
console.log(`OK: wrote ${count} PNG icons to ${OUT_DIR}`);
