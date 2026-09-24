/*
 * app.js
 * ---------------------------------------------------------------
 * UI logic for the Farm Manager pixel-art GUI. Vanilla JS, no
 * build step, no external framework — reads GameData (data.js)
 * and draws sprites (sprites.js) into the DOM built in index.html.
 * ---------------------------------------------------------------
 */

(() => {
  'use strict';

  // ---- Section catalog --------------------------------------------
  // Each "book" on the shelf maps 1:1 to a C++ class in /classes.
  const SECTIONS = [
    { key: 'crops',      label: 'Hortalicas',    accentDarkVar: '--accent-crop-dark',      defaultIcon: 'cropSpring' },
    { key: 'villagers',  label: 'Habitantes',    accentDarkVar: '--accent-villager-dark',  defaultIcon: 'villagerBust-0' },
    { key: 'animals',    label: 'Animais',       accentDarkVar: '--accent-animal-dark',    defaultIcon: 'animalChicken' },
    { key: 'buildings',  label: 'Construcoes',   accentDarkVar: '--accent-building-dark',  defaultIcon: 'buildingBarn' },
    { key: 'myfarm',     label: 'Minha Fazenda', accentDarkVar: '--accent-farm-dark',      defaultIcon: 'farmhouse' },
  ];

  // ---- State ---------------------------------------------------
  const state = {
    section: 'crops',
    search: '',
    filters: {
      crops: 'Todas',
      villagers: 'Todos',
    },
  };

  // ---- DOM refs ---------------------------------------------------
  const bookListEl = document.getElementById('bookList');
  const sectionTitleEl = document.getElementById('sectionTitle');
  const filterChipsEl = document.getElementById('filterChips');
  const cardGridEl = document.getElementById('cardGrid');
  const emptyStateEl = document.getElementById('emptyState');
  const searchInputEl = document.getElementById('searchInput');
  const modalOverlayEl = document.getElementById('modalOverlay');
  const modalBodyEl = document.getElementById('modalBody');
  const modalCloseEl = document.getElementById('modalClose');

  // ---- Helpers -----------------------------------------------------
  function cssVar(name) {
    return getComputedStyle(document.body).getPropertyValue(name).trim();
  }

  function normalize(str) {
    return (str || '')
      .toString()
      .normalize('NFD')
      .replace(/[̀-ͯ]/g, '')
      .toLowerCase();
  }

  function sectionDef(key) {
    return SECTIONS.find((s) => s.key === key);
  }

  function heartsRow(value, max = 10, scale = 3) {
    const wrap = document.createElement('div');
    wrap.className = 'card-hearts';
    for (let i = 0; i < max; i++) {
      const name = i < value ? 'heartFull' : 'heartEmpty';
      wrap.appendChild(Sprites.makeImage(name, { scale }));
    }
    return wrap;
  }

  // ---- Bookshelf ----------------------------------------------------
  function renderBookshelf() {
    bookListEl.innerHTML = '';
    SECTIONS.forEach((sec) => {
      const li = document.createElement('li');
      li.className = 'book-item' + (sec.key === state.section ? ' active' : '');
      li.dataset.key = sec.key;

      const icon = Sprites.bookIcon(sec.key, { scale: 3 });

      const label = document.createElement('span');
      label.className = 'book-label';
      label.textContent = sec.label;

      const count = document.createElement('span');
      count.className = 'book-count';
      count.textContent = countFor(sec.key);

      li.append(icon, label, count);
      li.addEventListener('click', () => selectSection(sec.key));
      bookListEl.appendChild(li);
    });
  }

  function countFor(key) {
    if (key === 'myfarm') {
      const f = GameData.myFarm;
      return f.myAnimals.length + f.myBuildings.length + f.myRelationships.length;
    }
    return (GameData[key] || []).length;
  }

  // ---- Filters ----------------------------------------------------
  function renderFilters() {
    filterChipsEl.innerHTML = '';

    if (state.section === 'crops') {
      const seasons = ['Todas', 'Primavera', 'Verao', 'Outono', 'Inverno'];
      seasons.forEach((s) => filterChipsEl.appendChild(makeChip(s, state.filters.crops === s, () => {
        state.filters.crops = s;
        renderFilters();
        renderContent();
      })));
    } else if (state.section === 'villagers') {
      const opts = ['Todos', 'Solteiro(a)', 'Comprometido(a)'];
      opts.forEach((s) => filterChipsEl.appendChild(makeChip(s, state.filters.villagers === s, () => {
        state.filters.villagers = s;
        renderFilters();
        renderContent();
      })));
    }
  }

  function makeChip(label, active, onClick) {
    const chip = document.createElement('button');
    chip.className = 'chip' + (active ? ' active' : '');
    chip.textContent = label;
    chip.addEventListener('click', onClick);
    return chip;
  }

  // ---- Card grid ----------------------------------------------------
  function selectSection(key) {
    state.section = key;
    sectionTitleEl.textContent = sectionDef(key).label;
    renderBookshelf();
    renderFilters();
    renderContent();
  }

  function renderContent() {
    if (state.section === 'myfarm') {
      cardGridEl.hidden = true;
      renderFarmDashboard();
      return;
    }
    cardGridEl.hidden = false;
    document.querySelectorAll('.farm-summary').forEach((n) => n.remove());

    const items = getFilteredItems();
    cardGridEl.innerHTML = '';
    emptyStateEl.hidden = items.length > 0;

    items.forEach((item) => cardGridEl.appendChild(buildCard(state.section, item)));
  }

  function getFilteredItems() {
    const key = state.section;
    let items = [...(GameData[key] || [])];

    if (key === 'crops' && state.filters.crops !== 'Todas') {
      items = items.filter((c) => c.season === state.filters.crops);
    }
    if (key === 'villagers' && state.filters.villagers !== 'Todos') {
      const wantSingle = state.filters.villagers === 'Solteiro(a)';
      items = items.filter((v) => v.single === wantSingle);
    }

    if (state.search) {
      const q = normalize(state.search);
      items = items.filter((item) => normalize(item.name).includes(q));
    }
    return items;
  }

  function buildCard(section, item) {
    const card = document.createElement('div');
    card.className = `card tag-${singularTag(section)}`;
    card.setAttribute('role', 'listitem');
    card.tabIndex = 0;

    const top = document.createElement('div');
    top.className = 'card-top';
    top.appendChild(makeIcon(section, item));

    const name = document.createElement('span');
    name.className = 'card-name';
    name.textContent = item.name;
    top.appendChild(name);
    card.appendChild(top);

    const tag = document.createElement('span');
    tag.className = 'card-tag';
    tag.textContent = tagLabel(section, item);
    card.appendChild(tag);

    const meta = document.createElement('div');
    meta.className = 'card-meta';
    meta.textContent = metaLabel(section, item);
    card.appendChild(meta);

    const open = () => openModal(section, item);
    card.addEventListener('click', open);
    card.addEventListener('keydown', (e) => { if (e.key === 'Enter') open(); });

    return card;
  }

  function singularTag(section) {
    return { crops: 'crop', villagers: 'villager', animals: 'animal', buildings: 'building' }[section] || section;
  }

  function makeIcon(section, item) {
    if (section === 'villagers') {
      return Sprites.villagerBust(item.name, { scale: 5 });
    }
    return Sprites.makeImage(item.icon || sectionDef(section).defaultIcon, { scale: 5 });
  }

  function tagLabel(section, item) {
    switch (section) {
      case 'crops': return item.season;
      case 'villagers': return item.single ? 'Solteiro(a)' : 'Comprometido(a)';
      case 'animals': return item.type;
      case 'buildings': return item.housesAnimals ? 'Abriga animais' : 'Estrutura';
      default: return '';
    }
  }

  function metaLabel(section, item) {
    switch (section) {
      case 'crops': {
        const regrow = item.regrow ? ` • rebrota a cada ${item.daysToRegrowth}d` : '';
        return `${item.daysToHarvest} dias para colher${regrow}`;
      }
      case 'villagers':
        return `Presente favorito: ${item.giftLove}`;
      case 'animals':
        return `Produz: ${item.produces} • ${item.daysToAdult}d ate adulto`;
      case 'buildings':
        return `Tamanho: ${item.size[0]}x${item.size[1]} tiles`;
      default:
        return '';
    }
  }

  // ---- My Farm dashboard ----------------------------------------------------
  function renderFarmDashboard() {
    document.querySelectorAll('.farm-summary').forEach((n) => n.remove());
    const farm = GameData.myFarm;

    const wrap = document.createElement('div');
    wrap.className = 'farm-summary';

    const banner = document.createElement('div');
    banner.className = 'farm-banner';
    banner.appendChild(Sprites.makeImage('farmhouse', { scale: 6 }));
    const bannerText = document.createElement('div');
    bannerText.innerHTML = `<h3>${farm.farmName}</h3><p>Layout: ${farm.farmLayout}</p>`;
    banner.appendChild(bannerText);
    wrap.appendChild(banner);

    const columns = document.createElement('div');
    columns.className = 'farm-columns';

    columns.appendChild(farmBlock('Meus Animais (MyAnimal)', farm.myAnimals.map((a) => {
      const row = document.createElement('div');
      row.className = 'farm-row';
      row.appendChild(Sprites.makeImage(a.icon, { scale: 3 }));
      const grow = document.createElement('span');
      grow.className = 'grow';
      grow.textContent = `${a.animalName} — ${a.animalType}`;
      row.appendChild(grow);
      row.appendChild(heartsRow(a.animalRelationship));
      return row;
    }), 'Nenhum animal registrado ainda. Use o menu "Minha Fazenda" do farm_manager.exe para adicionar um.'));

    columns.appendChild(farmBlock('Minhas Construcoes (MyBuilding)', farm.myBuildings.map((b) => {
      const row = document.createElement('div');
      row.className = 'farm-row';
      row.appendChild(Sprites.makeImage(b.icon, { scale: 3 }));
      const grow = document.createElement('span');
      grow.className = 'grow';
      grow.textContent = `${b.buildingName}`;
      row.appendChild(grow);
      const lvl = document.createElement('span');
      lvl.textContent = `Nivel ${b.buildingLevel}`;
      row.appendChild(lvl);
      return row;
    }), 'Nenhuma construcao registrada ainda. Use o menu "Minha Fazenda" do farm_manager.exe para adicionar uma.'));

    columns.appendChild(farmBlock('Minhas Relacoes (MyRelationship)', farm.myRelationships.map((r) => {
      const row = document.createElement('div');
      row.className = 'farm-row';
      const grow = document.createElement('span');
      grow.className = 'grow';
      grow.textContent = r.villagerName;
      row.appendChild(grow);
      row.appendChild(heartsRow(r.friendship));
      return row;
    }), 'Nenhuma amizade registrada ainda. Use o menu "Minha Fazenda" do farm_manager.exe para adicionar uma.'));

    wrap.appendChild(columns);
    cardGridEl.insertAdjacentElement('afterend', wrap);
    emptyStateEl.hidden = true;
  }

  function farmBlock(title, rows, emptyMessage) {
    const block = document.createElement('div');
    block.className = 'farm-block';
    const h = document.createElement('h4');
    h.textContent = title;
    block.appendChild(h);
    if (rows.length === 0 && emptyMessage) {
      const p = document.createElement('p');
      p.className = 'farm-empty';
      p.textContent = emptyMessage;
      block.appendChild(p);
    } else {
      rows.forEach((r) => block.appendChild(r));
    }
    return block;
  }

  // ---- Modal ("quest log") ----------------------------------------------------
  function openModal(section, item) {
    modalBodyEl.innerHTML = '';

    const h3 = document.createElement('h3');
    h3.textContent = item.name;
    modalBodyEl.appendChild(h3);

    const iconRow = document.createElement('div');
    iconRow.className = 'modal-icon-row';
    iconRow.appendChild(makeIcon(section, item));
    const tag = document.createElement('span');
    tag.className = 'card-tag';
    tag.style.background = cssVar(sectionDef(section).accentDarkVar);
    tag.textContent = tagLabel(section, item);
    iconRow.appendChild(tag);
    modalBodyEl.appendChild(iconRow);

    modalSectionsFor(section, item).forEach(([heading, node]) => {
      const sec = document.createElement('div');
      sec.className = 'modal-section';
      const h5 = document.createElement('h5');
      h5.textContent = heading;
      sec.appendChild(h5);
      sec.appendChild(node);
      modalBodyEl.appendChild(sec);
    });

    modalOverlayEl.hidden = false;
  }

  function listNode(lines) {
    const ul = document.createElement('ul');
    ul.className = 'modal-list';
    if (!lines.length) {
      const li = document.createElement('li');
      li.textContent = 'Nenhum registro.';
      ul.appendChild(li);
      return ul;
    }
    lines.forEach((line) => {
      const li = document.createElement('li');
      li.textContent = line;
      ul.appendChild(li);
    });
    return ul;
  }

  function modalSectionsFor(section, item) {
    switch (section) {
      case 'crops':
        return [
          ['Colheita', listNode([
            `Estacao: ${item.season}`,
            `Dias para colher: ${item.daysToHarvest}`,
            item.regrow ? `Rebrota a cada ${item.daysToRegrowth} dia(s)` : 'Nao rebrota (plantar de novo apos colher)',
          ])],
          ['Valor de venda', listNode(item.sellValue.map(([q, v]) => `${q}: ${v}g`))],
          ['Preco da semente', listNode(item.seedPrice.map(([loja, v]) => `${loja}: ${v}g`))],
          ['Itens artesanais', listNode(item.artisanItems.map(([n, machine, v]) => `${n} (${machine}) — ${v}g`))],
        ];
      case 'villagers':
        return [
          ['Presentes', listNode([
            `Adora: ${item.giftLove}`,
            `Gosta: ${item.giftLike}`,
          ])],
          ['Status', listNode([`Situacao: ${item.single ? 'Solteiro(a)' : 'Comprometido(a)'}`])],
        ];
      case 'animals':
        return [
          ['Producao', listNode([
            `Produz: ${item.produces}`,
            `Dias ate adulto: ${item.daysToAdult}`,
            item.buyPrice != null ? `Preco de compra: ${item.buyPrice}g` : 'Preco de compra: nao vendido na loja (obtido de outra forma)',
          ])],
          ['Itens artesanais', listNode(item.artisanItem.map(([n, machine, v]) => `${n} (${machine}) — ${v}g`))],
        ];
      case 'buildings':
        return [
          ['Construcao', withMaterials(item)],
        ];
      default:
        return [];
    }
  }

  // buildings need two lists (materials + animals housed); build manually
  function withMaterials(item) {
    const frag = document.createElement('div');
    frag.appendChild(listNode([
      `Tamanho: ${item.size[0]}x${item.size[1]} tiles`,
      `Onde conseguir: ${item.whereToGet}`,
    ]));
    const matsHeading = document.createElement('h5');
    matsHeading.textContent = 'Materiais';
    matsHeading.style.marginTop = '10px';
    frag.appendChild(matsHeading);
    frag.appendChild(listNode(item.constructionMaterials.map(([m, q]) => `${m} x${q}`)));

    const animalsHeading = document.createElement('h5');
    animalsHeading.textContent = 'Animais que abriga';
    animalsHeading.style.marginTop = '10px';
    frag.appendChild(animalsHeading);
    frag.appendChild(listNode(item.housesAnimals
      ? [`Capacidade: ${item.animalAmount}`, ...item.animalTypes]
      : []));
    return frag;
  }

  function closeModal() {
    modalOverlayEl.hidden = true;
  }

  // ---- Search ----------------------------------------------------
  function bindGlobalEvents() {
    searchInputEl.addEventListener('input', (e) => {
      state.search = e.target.value;
      renderContent();
    });

    modalCloseEl.addEventListener('click', closeModal);
    modalOverlayEl.addEventListener('click', (e) => { if (e.target === modalOverlayEl) closeModal(); });
    document.addEventListener('keydown', (e) => { if (e.key === 'Escape') closeModal(); });
  }

  // ---- Init ----------------------------------------------------
  function init() {
    renderBookshelf();
    bindGlobalEvents();
    selectSection('crops');
  }

  document.addEventListener('DOMContentLoaded', init);
})();
