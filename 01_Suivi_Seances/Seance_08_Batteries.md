# Séance 8 : 19 Février 2026 - Utilisation et Fabrication de Batteries

##  Objectifs de la séance
* Comprendre les différentes chimies de batteries (Li-ion, LiFePO4).
* Maîtriser le dimensionnement électrique (Capacité, Taux de décharge "C", Série/Parallèle).
* Apprendre les règles de sécurité et les étapes de fabrication d'un pack batterie sur mesure.

##  Résumé du cours

### 1. Pourquoi fabriquer sa propre batterie ?
Créer son propre pack présente plusieurs avantages majeurs :
* **Forme sur mesure :** Permet d'adapter parfaitement la batterie à la coque de notre projet (ex: intégration dans un dôme).
* **Maîtrise du processus :** On choisit la qualité des composants et on réduit les coûts.
* **Écologie / Sécurité :** L'usage de piles rechargeables est beaucoup plus pertinent et économique à long terme (notamment pour les jouets d'enfants ou les gros projets).

### 2. Les chimies et tensions nominales
Il est vital de connaître la chimie pour bien configurer son chargeur et son BMS :
* **Lithium-Ion (Li-ion) :** Tension nominale d'environ **3.7V** (varie de 3.0V vide à 4.2V pleine).
* **Lithium Fer Phosphate (LiFePO4) :** Tension nominale d'environ **3.2V** (chimie très stable et sécurisée).

### 3. Le Taux de décharge / charge (Le "C-Rate")
*Note sur la Slide 11 du cours :*
Le "C" représente la **Capacité** de la batterie. Il définit les limites de courant qu'elle peut encaisser.
* **Décharge (Max Discharge Rate) :** Si une batterie de 4000 mAh a une décharge de 30C, le courant maximal autorisé est : $4 \text{ Ah} \times 30 = \mathbf{120 \text{ Ampères}}$.
* **Charge (Max Charge Rate) :** Une indication de "3C" signifie qu'on peut la charger à 3 fois sa capacité (ici 12A). *Règle de sécurité :* Si on ne connaît pas la valeur, on charge toujours à **1C maximum** pour ne pas abîmer la cellule.

### 4. Configuration S et P
L'assemblage des cellules définit la puissance du pack :
* **S (Série) :** Additionne la tension. Exemple : "4S" = 4 batteries à la suite.
* **P (Parallèle) :** Additionne la capacité (et le courant de décharge). "4S1P" signifie un pack de 4 batteries en série, avec une seule rangée (pas de cellules doublées).


## 🛠️ Travaux Pratiques : Le Pack Batterie LumaDome
Pour mon projet, j'ai besoin d'une alimentation capable de délivrer **12V et au moins 5A** pour alimenter le convertisseur Buck des LEDs NeoPixel.

**Choix technique :** J'ai opté pour un **Pack 4S** (4 cellules en série).
* *Cellules utilisées :* Samsung INR18650-35E (3.7V, 3450mAh, décharge 8A).
* *Protection :* Un BMS 4S 20A sera intégré pour équilibrer la charge et protéger contre les courts-circuits.

**État d'avancement du TP :**
Je n'ai pas encore procédé à la soudure par points des lamelles de nickel. Actuellement, je me concentre sur la conception mécanique.
* **Modélisation 3D :** Je suis en train de designer la coque (support de batterie) sur CAD. Cette pièce imprimée en 3D permettra d'accueillir et de caler fermement les 4 piles avant de procéder à l'assemblage définitif (Soudure, BMS, Kapton et Gaine thermorétractable).

## ✅ Tâches effectuées
- [x] Dimensionnement du pack batterie pour le projet (Configuration 4S).
- [x] Début de la conception 3D du support de piles 18650.
- [ ] Impression 3D du support (À faire).
- [ ] Soudure par points et assemblage du pack (À faire).