# [Nome do programa]
## Aplicação dos conhecimentos
[Nome do programa] é um databank interativo, utilizando a linguagem C++ como base, através da técnica de Programação Orientada a Objetos. O projeto é uma materialização dos conhecimentos adquiridos na cadeira de Estrutura de Dados Orientados a Objetos (CIN0135), do curso de Sistemas de Informação, na Universidade Federal de Pernambuco.

## Propósitos e Objetivos
Stardew Valley é um jogo casual, em que o jogador é representado por um(a) fazendeiro(a), que herda uma propriedade de seu avô em uma pequena vila no interior, a qual ele precisa explorar para desvendar mistérios e conhecer cada canto do mapa e seus habitantes. O jogo, de 2016, abrange uma série de variedades de cultivo de hortaliças, pecuária de animais e obtenção de minérios. Além disso, existem diversos NPC's, Non-Playable-Characters, com os quais o jogador pode interagir para conseguir recompensas e avançar no jogo.
Diante de tudo isso, a gameplay pode parecer desafiadora: com 34 NPC's com os quais é possível interagir, 54 tipos de hortaliças, cada uma com suas especificidades, inúmeros minérios e minerais que são encontrados nas minas e ainda mais de 30 missões secundárias... O jogo não parece tão "casual" assim.
Por esse motivo, o seguinte programa mapeia as hortaliças, os villagers, os animais de fazenda e as construções disponíveis em todo o jogo, auxiliando o jogador a ter uma gameplay mais tranquila, sem ter que descobrir todos os segredos de Stardew Valley à força. Além disso, o programa também armazena informações sobre a própria fazenda do jogador - quais animais ele possui, quais construções existem na propriedade, quais villagers gostam ou não dele, etc.

## Diagrama de Classes
A classe DataType é a classe mãe, que dá origem a todas essas subclasses, através da técnica de herança, vista em sala. Na interface gráfica, cada uma dessas classes é acessada como um **livro**.

    DataType
    	├─ Crop
    	├─ Villager
    	├─ Animal
    	├─ Building
    	└─ MyFarm

## Categorização
Como esse programa é uma grande biblioteca, uma enciclopédia de como navegar no universo de Stardew Valley, cada coisa tem o seu lugar: existe uma lógica por trás da padronização e etiquetação das seções.

#### Livro 1: Crops
*Crops*, inglês para "hortaliças", abrange tudo aquilo que o jogador pode plantar dentro do jogo. Esse é o motor principal de Stardew Valley e, claramente, cada planta, fruta, vegetal e flor têm suas características próprias: seu valor de mercado (que depende da qualidade), o preço de venda da sua semente, a estação em que se pode plantá-la, quantos dias se passam entre o momento do plantio e da colheita, etc. Por isso, foi organizada o seguinte modelo de atributos.

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
    	
#### Livro 2: Villagers
Os *villagers* - NPC's - são os personagens com quem o jogador interage dentro do jogo. Assim como na vida real, o jogador precisa manter uma interação frequente com cada personagem, para que seus "pontos de amizade" aumentem, ganhando assim, o **coração** dos *villagers*. Isso é feito através de conversa diária e através de presentes: quanto mais o personagem gostar do presente, maior a quantidade de pontos ganhados com aquele personagem. Esses pontos são medidos através de corações no jogo, que também são armazenados nesse programa, assim como quais presentes cada *villager* gosta, ama ou odeia.

    DataType(Villager)
    	├─ name (str)
    	├─ single (bool)
    	├─ routine (array:tuple)
    	├─ giftsLike (array:str)
    	├─ giftsLove (array:str)
    	├─ giftsHate (array:str)
    	└─ giftsNeutral (array:str)

#### Livro 3: Animals
Os animais, dentro de Stardew Valley, precisam de locais específicos para dormir e amor, assim como pets IRL. Com essas duas coisas, cada animal de fazenda produz algo específico - no caso de uma galinha, um ovo, no caso de um porco, uma trufa... Para auxiliar o *player*, [Nome do programa] fornece informações que possam permitir um planejamento a longo prazo para a compra de animais e entendimento de quais construções são necessárias para abrigar cada um.

    DataType(Animal)
    	├─ name (str)
    	├─ type (str)
    	├─ produces (str)
    	├─ daysToAdult (int)
    	├─ buyPrice (int)
    	├─ sellValue (int)
    	└─ artisanItem (array:tuple)

#### Livro 4: Buildings
Como já dito, cada animal precisa de sua construção (*building*) específico, mas celeiros e galinheiros não são as únicas coisas disponíveis para a construção em Stardew Valley. Para construir um moinho, é preciso materiais diferentes da construção de um lagoa de pesca, por exemplo, e seus preços e tempo de construção também são diferentes. 

    DataType(Building)
    	├─ name (str)
    	├─ constructionMaterials (array:tuple)
    	├─ size (array:int)
    	├─ whereToGet (str)
    	├─ housesAnimals (bool)
    	├─ animalTypes (array:str)
    	└─ animalAmount (int)

#### Livro 5: My Farm
Além de apresentar informações gerais sobre o jogo, [Nome do programa] também mostra as informações sobre a fazenda do próprio jogador, o ajudando a tomar nota de qual o seu relacionamento com cada *villager*, quais construções existem em sua fazenda e quais animais já foram adquiridos. E, assim como no jogo, você pode manter diferentes fazendas, com diferentes níveis de amizade, construções e animais. 

    DataType(MyFarm)
    	├─ farmName (str)
    	├─ myRelationships (array:tuple)
    	├─ myAnimals (array:obj)
    	└─ myBuildings (array:obj)
    	
## Implementação
[Informações sobre a divisão de tarefas do projeto e ferramentas usadas]