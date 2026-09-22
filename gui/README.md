# [Nome do programa] — Interface Gráfica do Farm Manager

Protótipo de interface gráfica **pixel art**, feito em HTML/CSS/JS puro (sem build, sem
dependências além de uma fonte do Google Fonts), para o projeto `farm-manager`
(CIN0135 — Estrutura de Dados Orientados a Objetos, UFPE).

A ideia parte de algo que o próprio README principal do projeto já sugeria: *"na
interface gráfica, cada uma dessas classes é acessada como um **livro**"*. Esta pasta
materializa essa metáfora como uma pequena biblioteca pixelada, com "livros" para cada
classe (Hortaliças, Habitantes, Animais, Construções e Minha Fazenda).

> **Nenhum asset original do jogo foi usado.** Todo o pixel art (ícones de cultura,
> animais, construções, livros, corações) é desenhado do zero via `<canvas>`, a partir
> de matrizes de pixels escritas à mão — ver `js/sprites.js`.

Os dados exibidos são **reais**: `js/data.js` é gerado a partir dos bancos SQLite do
projeto (`database/gameData.db` e `database/myFarmData.db`) por um script Node — veja
a seção [Dados](#dados) abaixo.

## Como abrir

Basta abrir `gui/index.html` diretamente no navegador. Não há passo de build nem
servidor obrigatório (embora funcione igual se servido por um `http-server` local).

## Estrutura de arquivos

```
gui/
├── index.html          # esqueleto da página (topo, estante, sala de leitura, modal)
├── css/style.css        # tema pixel art (molduras recortadas, grid de cartões)
├── js/sprites.js         # renderizador de pixel art + todas as matrizes de sprites originais
├── js/data.js              # dados REAIS, gerados por tools/export-data.js (nao editar a mao)
├── js/app.js                 # navegação, busca, filtros, modais e o painel "Minha Fazenda"
├── tools/export-data.js        # le gameData.db + myFarmData.db (node:sqlite) e regenera js/data.js
└── README.md                     # este arquivo
```

## Features

1. **Estante de livros** — navegação lateral com 5 livros, um por classe (`Crop`,
   `Villager`, `Animal`, `Building`, `MyFarm`), cada um com contador de itens.
2. **Busca global** — filtra por nome em qualquer seção, ignorando acentuação
   (`normalize('NFD')`).
3. **Filtros por seção** — estação do ano para Hortaliças; status (solteiro/a ou
   comprometido/a) para Habitantes.
4. **Cartões + modal "diário de missão"** — cada cartão abre um modal detalhado no
   estilo caixa de diálogo de RPG, mostrando **todos** os atributos reais da classe
   correspondente (ex.: em `Building`, materiais de construção, tamanho, onde obter,
   se abriga animais, tipos e capacidade).
5. **Painel "Minha Fazenda"** — dashboard separado (não é um livro de catálogo) que
   reflete `MyFarm` + `MyAnimal` + `MyBuilding` + `MyRelationship`: nome da fazenda,
   animais adquiridos, construções e nível, e amizade com cada habitante — com
   corações pixelados preenchidos conforme o valor de `friendship`/`animalRelationship`.
   Essa separação é intencional: o catálogo de `Villager` (livro 2) mostra presentes
   favoritos, enquanto os corações de amizade **só existem** nos dados salvos da
   fazenda (`MyRelationship`), exatamente como no código C++.
6. **Responsivo** — em telas estreitas a estante desce para baixo da sala de leitura e
   vira uma barra horizontal.
7. **Moldura de pixel reutilizável** — técnica de `clip-path` com cantos recortados
   (`.pixel-frame`), usada no topo, na estante, nos cartões e no modal, para dar a cara
   de caixa de diálogo de RPG 16-bit sem precisar de imagens de borda.

## Dados

`js/data.js` é **gerado automaticamente** por `tools/export-data.js` a partir dos
bancos reais do projeto — `database/gameData.db` (catálogo do jogo: hortaliças,
animais, construções, habitantes) e `database/myFarmData.db` (progresso salvo do
jogador). O script usa o módulo nativo `node:sqlite` (disponível a partir do Node 22,
sem nenhuma dependência de `npm`) para ler os `.db` diretamente — nada é inventado ou
digitado à mão.

Para regenerar os dados (por exemplo, depois de jogar com `farm_manager.exe` e salvar
progresso em `myFarmData.db`):

```
node gui/tools/export-data.js
```

O topo do `js/data.js` gerado traz um aviso "NAO EDITE A MAO" e a data/hora da
geração — qualquer edição manual nesse arquivo é perdida na próxima execução do
script.

**O que é real vs. o que foi preenchido pela GUI:**
- Nomes de hortaliças/animais/construções/habitantes, estações, dias de colheita,
  preços, materiais de construção, presentes favoritos etc. vêm **diretamente** das
  tabelas `crop`, `animal`, `building`, `villager` e suas tabelas satélite
  (`crop_sell_values`, `building_construction_materials`, `villager_gifts`, ...).
- `database/gameData.db` já continha uma tabela `villager` + `villager_gifts`
  totalmente populada (21 habitantes, 42 presentes) que **o programa C++ nunca lê** —
  `Database` não tem nenhum método `getAllVillagers()`. Esta GUI é, portanto, o
  primeiro lugar no projeto onde esses dados de habitantes aparecem.
- Poucos campos não existem no banco e foram preenchidos de forma assumidamente
  sintética, documentada em código (`tools/export-data.js`): a cor do retrato de cada
  habitante (não há dado de aparência na tabela `villager`, então é gerada por hash
  determinístico do nome) e o ícone de alguns animais sem sprite dedicado (Ostrich,
  Goat, Duck, Dinosaur, Rabbit caem num ícone genérico de "pata", em vez de fingir ser
  outro bicho).
- O painel "Minha Fazenda" mostra o estado **real e atualmente vazio** de
  `myFarmData.db` (nenhum animal/construção/relação foi salvo ainda pelo programa
  C++ — é assim mesmo, não é um bug da GUI) com uma mensagem explicando como povoar
  esses dados jogando o `farm_manager.exe`.
- Nomes próprios do jogo (itens, lojas, materiais) foram mantidos em inglês, como
  estão no banco; apenas um vocabulário fechado e pequeno foi traduzido para
  consistência visual com o resto da interface (estações do ano e níveis de
  qualidade — Spring/Summer/Fall/Winter e normal/silver/gold/iridium).

## Limitações conhecidas / próximos passos

- `tools/export-data.js` é uma exportação sob demanda, não um servidor ao vivo: se o
  jogador salvar progresso novo em `myFarmData.db`, é preciso rodar o script de novo
  para atualizar `js/data.js`. Um próximo passo natural seria um servidor HTTP local
  (Node, sem dependências) que sirva os mesmos dados via `fetch()` em tempo real.
- Alternativamente, esta pasta poderia virar a *view* de uma aplicação desktop
  (Electron, Tauri ou uma webview simples) que troque o menu de console atual por
  esta interface, consultando o banco diretamente a cada abertura.
- Não houve testes em múltiplos navegadores/dispositivos reais — recomenda-se revisão
  manual antes de qualquer entrega/avaliação.
- O programa C++ original **não foi alterado**; este é um artefato novo, isolado em
  `gui/`.

## Uso de IA nesta interface

Esta interface foi criada com o **Claude Code** (modelo **Claude Sonnet 5**, da
Anthropic), operando como agente de linha de comando com acesso de leitura/escrita ao
repositório. Abaixo, um relato específico do que a IA fez, para que fique claro o que
foi gerado automaticamente e o que merece revisão humana antes de ser considerado
definitivo — especialmente relevante em um contexto acadêmico.

### O que a IA leu antes de desenhar qualquer coisa
- Todos os headers em `classes/*.h` (`DataType`, `Crop`, `Villager`, `Animal`,
  `Building`, `MyFarm`, `MyAnimal`, `MyBuilding`, `MyRelationship`) e o `main.cpp`, para
  extrair o modelo de dados real (atributos, getters/setters) — garantindo que os
  cartões e modais desta interface mostrem exatamente os campos que existem no código,
  e não uma versão inventada ou baseada só no README.
- O `README.md` do projeto, para reaproveitar a metáfora de "cada classe é um livro"
  já descrita ali, em vez de propor um conceito divergente.
- `database/menu.h` e `database/filters.h`, para entender que o programa já distingue
  entre catálogo estático do jogo (`Crop`/`Animal`/`Building` vindos de `gameData.db`)
  e progresso do jogador (`MyFarm` e afins, em `myFarmData.db`) — distinção que a GUI
  reproduz separando as 4 primeiras "estantes" do painel "Minha Fazenda".

### O que a IA gerou
- **Toda a identidade visual pixel art**, do zero: paleta de cores, a técnica de
  moldura recortada em CSS puro, e as matrizes de sprites (ícones de cultura por
  estação, animais, construções, livros, corações) desenhadas como grades de
  caracteres e renderizadas em `<canvas>` — nenhuma imagem foi baixada ou copiada do
  jogo.
- **Todo o HTML/CSS/JS** (vanilla, sem frameworks): navegação entre seções, busca,
  filtros, cartões, modal de detalhes e o painel "Minha Fazenda".
- **A ponte com os dados reais** (`tools/export-data.js`): antes de escrever qualquer
  linha desse script, a IA leu por completo `classes/database.h`, `database.cpp`,
  `database/filters.h`/`filters.cpp` e `main.cpp` para levantar, com precisão, cada
  método SQL, tabela e coluna realmente usados — e então rodou consultas somente-
  leitura contra os `.db` de verdade (via `node:sqlite`, embutido no Node, sem
  instalar nada) para inspecionar schema, contagens de linhas e amostras de conteúdo
  antes de decidir como mapear cada tabela para o formato que `app.js`/`sprites.js`
  já esperavam. Foi assim que se descobriu, por exemplo, que a tabela `villager` do
  banco tem 21 habitantes e 42 presentes catalogados que **o programa C++ nunca
  consulta** — a GUI passou a ser o primeiro lugar do projeto a exibir esse dado.
- **Este documento**, incluindo a lista de features e esta seção de transparência
  sobre uso de IA.

### O que a IA não fez / limites explícitos
- O script de exportação roda **sob demanda** (`node gui/tools/export-data.js`), não
  automaticamente — não há um servidor ao vivo nem um hook que rode a exportação
  sozinho a cada mudança nos bancos.
- Não alterou nem uma linha do código C++ existente; a GUI vive isolada em `gui/`. A
  leitura dos `.db` durante a exploração foi estritamente somente-leitura (`readOnly:
  true`), sem nenhuma escrita nos arquivos originais.
- Não rodou testes automatizados de interface nem verificação em navegadores reais —
  a validação foi feita por leitura de código, checagem de sintaxe JavaScript
  (`node --check`) e inspeção manual do JSON gerado, não por execução visual
  assistida por humano.
- Alguns campos que **não existem no banco** foram preenchidos de forma sintética e
  isso está sinalizado tanto no código (`tools/export-data.js`) quanto na seção
  [Dados](#dados) acima: a cor do retrato de cada habitante (gerada por hash do nome,
  já que a tabela `villager` não guarda aparência) e o ícone de fallback para animais
  sem sprite dedicado.

## Créditos

Parte do projeto **Farm Manager** (CIN0135, Sistemas de Informação — UFPE),
inspirado tematicamente em *Stardew Valley* (ConcernedApe) apenas como referência de
gameplay/organização de dados — sem uso de nenhum asset visual original do jogo.
