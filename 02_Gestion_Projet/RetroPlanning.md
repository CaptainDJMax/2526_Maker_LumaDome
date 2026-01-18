# Rétro-Planning : Projet LumaDome

Ce document détaille la feuille de route pour la réalisation du **LumaDome**, de la conception initiale à la soutenance finale. Il est divisé en blocs techniques (WBS - Work Breakdown Structure) suivis du calendrier chronologique.

---

## 1. Décomposition des Tâches Techniques (Détails)

Le travail est découpé par pôles de compétences.

### A. Mécanique & Structure (CAD / 3D / Laser)
L'objectif est de créer une base stable et une structure légère pour le diffuseur.
- [ ] **Modélisation Base :**
    - Conception du logement batterie (dimensions LiPo à vérifier).
    - Fixations pour le PCB (entretoises ou inserts).
    - Passage de câbles et port de charge (USB-C / Jack).
- [ ] **Modélisation Structure Haute :**
    - Design du cadre du dôme pour la découpe laser (Squelette).
    - Système de fixation (clips ou emboîtement) entre la base 3D et le squelette laser.
- [ ] **Prototypage :**
    - Impression 3D basse résolution (Draft) pour valider les dimensions.
    - Test de tolérance pour l'assemblage Base/Dôme.

### B. Électronique (PCB / Alimentation)
Le cœur du système
- [ ] **Conception Schématique (KiCad) :**
    - Intégration Bluetooth.
    - Circuit de gestion puissance.
    - Connecteurs (Batterie, LEDs, Boutons).
- [ ] **Routage PCB :**
    - Placement des composants pour optimiser l'espace dans la base cylindrique.
    - Largeur de pistes adaptée au courant (Ampérage) des LEDs.
    - Plan de masse (GND) pour la stabilité du signal.
- [ ] **Énergie :**
    - Choix de la batterie LiPo.
    - Soudure et gaine thermorétractable du BMS (Battery Management System).

### C. Habillage & Finitions (Couture)
La tissu du projet qui diffusera la lumière.
- [ ] **Recherche matériaux :** Test de diffusion lumière à travers différents tissus (Lycra, Coton, Synthétique).
- [ ] **Patronage :** Création du patron "à plat" correspondant à la forme courbe du dôme.
- [ ] **Assemblage :** Couture et fixation sur la structure découpe laser.

### D. Développement Logiciel (Firmware)
Le code embarqué PCB.
- [ ] **Briques de base :**
    - Driver LED.
    - Gestion du Bluetooth pour communication Smartphone.
- [ ] **Fonctionnalités avancées :**
    - Modes d'animation (Arc-en-ciel, Respiration, Aube).
    - Stockage des préférences (Mémoire EEPROM/SPIFFS).
    - Gestion de l'énergie (Deep Sleep).

---

##  2. Calendrier Prévisionnel (Timeline)

Ce planning respecte les jalons imposés par l'Option Maker.

###  Phase 1 : Apprentissage & Conception (Janvier - Février)

| État | Date | Thème | Tâches LumaDome à valider |
| :---: | :--- | :--- | :--- |
| [x] | **Jeu 15 Janv** | **Git** | Initialisation Repo, Arborescence, Idée validée. |
| [ ] | **Lun 19 Janv** | **CAD** | **LIVRABLE :** Plans 3D de la base (Logement élec). |
| [ ] | **Jeu 22 Janv** | **3D Print** | Lancement impression Base V1 (PLA). |
| [ ] | **Lun 26 Janv** | **Laser** | Découpe du squelette du dôme (Medium/Plexi). |
| [ ] | **Jeu 29 Janv** | **PCB (1)** | Schématique électronique terminée sur KiCad. |
| [ ] | **Lun 02 Fév** | **Soudure** | Routage terminé + Génération fichiers Gerber. |
| [ ] | **Jeu 05 Fév** | **LiPo** | Choix batterie + Test chargeur/BMS. |
| [ ] | **Lun 09 Fév** | **Couture** | Premier essai d'habillage textile sur structure. |

###  Phase 2 : Développement & Intégration (Février - Avril)

| État | Date | Type | Objectifs de séance |
| :---: | :--- | :--- | :--- |
| [ ] | **Lun 16 Fév** | Encadré | **Intégration Méca/Élec :** Vérifier que tout rentre dans la base. |
| [ ] | **Jeu 19 Fév** | Libre | **Code :** Premier allumage des LEDs (Hello World lumineux). |
| [ ] | **Lun 09 Mar** | Encadré | **Code :** Mise en place du Bluetooth (BLE). |
| [ ] | **Jeu 12 Mar** | Libre | **Debug :** Tests d'autonomie batterie. |
| [ ] | **Lun 16 Mar** | Encadré | **Finitions :** Optimisation diffusion lumière (Tissu). |
| [ ] | **Jeu 19 Mar** | Encadré | **Code :** Animations fluides et transitions. |
| [ ] | **Lun 23 Mar** | Encadré | **Assemblage Final :** Collage, vissage, cable management propre. |
| [ ] | **Jeu 26 Mar** | Libre | Tournage et montage **Vidéo Insta (90s)**. |
| [ ] | **Lun 30 Mar** | Encadré | Derniers ajustements code/finitions. |
| [ ] | **Jeu 02 Avr** | Encadré | Préparation support de soutenance. |
| [ ] | **Jeu 09 Avr** | Libre | Répétition générale. |
| [ ] | **Lun 13 Avr** | **JURY** | **SOUTENANCE FINALE** |

---

##  3. Suivi Budgétaire (Budget Max : 100€)


---

