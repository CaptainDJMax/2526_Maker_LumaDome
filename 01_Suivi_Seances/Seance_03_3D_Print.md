# Séance 3 : Impression 3D (FDM)

## Objectifs de la séance
* Comprendre le fonctionnement d'une imprimante 3D FDM (Dépôt de fil).
* Connaître les différents matériaux (PLA, PETG, ABS, TPU) et leurs usages.
* Maîtriser le **Slicing** (Tranchage) pour préparer un fichier à l'impression.

## Résumé du cours

### 1. Principe de fonctionnement (FDM)
La technologie utilisée au FabLab est le **FDM** (Fused Deposition Modeling).
Le principe est de faire fondre un filament plastique pour le déposer couche par couche.
* **Le Bed (Plateau) :** La surface chauffante sur laquelle repose la pièce (axes X/Y ou Z selon les modèles).
* **L'Extruder (Extrudeur) :** Le moteur qui pousse le fil. S'il est déporté, le fil passe dans un tube appelé **Bowden**.
* **La Nozzle (Buse) :** La pièce chaude (environ 200°C) par laquelle sort le plastique. Le diamètre standard est de **0.4mm**.

### 2. Les Matériaux (Filaments)
Nous avons passé en revue les thermoplastiques disponibles :
* **PLA (PolyLactic Acid) :** Le standard. Facile à imprimer, biodégradable, mais craint la chaleur (>60°C). *Utilisé pour la majorité des projets Maker.*
* **PETG :** Plus robuste et résistant aux produits chimiques. Idéal pour des pièces mécaniques.
* **ABS/ASA :** Très résistant (chocs/UV) mais dégage des fumées toxiques et est difficile à imprimer (Warping).
* **TPU :** Matériau flexible (élastomère), utile pour des joints ou pneus, mais s'imprime lentement.

### 3. Règles de conception & Slicing
Pour imprimer, on transforme un fichier 3D (.STL) en instructions machines (.gCode) via un logiciel "Slicer" (PrusaSlicer, Bambu Studio).

**Les paramètres clés retenus :**
* **Remplissage (Infill) :** 15% est suffisant pour la majorité des pièces. Le motif **Gyroid** est recommandé pour une meilleure résistance omnidirectionnelle.
* **Parois (Walls/Shells) :** Mettre 3 ou 4 parois (au lieu de 2) augmente considérablement la solidité de la pièce.
* **Supports :** Nécessaires si une partie de la pièce est "dans le vide". Le mode **Tree (Arbre)** est conseillé car plus facile à retirer et économise de la matière.
* **Tolérances :** Pour emboîter deux pièces, il faut prévoir un jeu fonctionnel d'au moins **0.3mm**.

* ** Astuce Maker :** Pour des assemblages solides, on peut insérer des écrous en métal directement dans le plastique en chauffant l'écrou avec un fer à souder, ou en programmant une pause dans l'impression.

##  Application au Projet LumaDome
Cette séance est critique pour la fabrication de la base de ma lampe.

* **Choix du matériau :** Je partirai sur du **PLA** pour le prototype de la base. Si la chauffe des LEDs est trop importante, je passerai au **PETG**.
* **Stratégie d'impression :**
    * La base cylindrique sera imprimée à plat.
    * Utilisation de **supports "Tree"** uniquement pour les ouvertures (Port USB-C et passage bouton).
    * **Intégration :** Je vais prévoir des plots avec des trous pour insérer des écrous à chaud (heat set inserts) afin de visser le PCB proprement.

##  Tâches effectuées
- [x] Découverte des imprimantes du Labo (Creality, Bambu Lab).
- [x] Configuration du Slicer (taille de buse 0.4mm, Température 210°C).
- [ ] Lancement de la première impression test (Base LumaDome V1).