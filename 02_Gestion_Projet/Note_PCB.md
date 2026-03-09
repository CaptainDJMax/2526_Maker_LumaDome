# Note Technique : Nomenclature (BOM) et Rôle des Composants du PCB

Cette note détaille l'ensemble des composants nécessaires à la conception du circuit imprimé (PCB) du LumaDome, ainsi que leur rôle spécifique dans l'architecture électronique.

## Nomenclature des composants (BOM)

| Catégorie | Composant | Référence / Détails | Rôle principal |
| --- | --- | --- | --- |
| **Énergie** | **Secteur 12V** | Bloc alimentation DC 12V (2.5 A) | Alimentation fixe (Jack DC). |
| **Énergie** | **Batterie 4S** | 4x 18650 Samsung INR18650-35E | Source nomade (**14.8V** nominal). |
| **Énergie** | **Régulateur 5V** |  | Alimente les LEDs (conversion 16V -> 5V). |
| **Énergie** | **Régulateur 3.3V** |  | Alimente l'ESP32 (conversion 5V -> 3.3V). |
| **Cerveau** | **Microcontrôleur** | **ESP32-WROOM-32E-N4** | Cerveau Wi-Fi/BT et gestion des LEDs. |
| **Interface** | **Connecteur JTAG** | **Header 2x5 (10 pins)** | Interface pour l'ESP-Prog 2 (Debug/Flash). |
| **Interface** | **Connecteur LED** | Bornier ou JST SM 3 pins | Sortie vers le ruban Adafruit 1138. |
| **Logique** | **Level Shifter** | **SN74AHCT125** | Traduit le signal Data 3.3V vers 5V. |
| **Contrôle** | **Boutons** | Poussoirs tactiles 6mm | Mode, Luminosité, Reset, Boot. |
| **Outil** | **ESP-Prog 2** | Programmateur | Programmateur externe USB. |

---

## 1.  Le Cerveau et la Programmation

* **Le Microcontrôleur : ESP32-WROOM-32E-N4**
  * *Rôle :* C'est le cerveau du projet. Il exécute le code en C (ESP-IDF), génère les signaux pour animer les LEDs, et lit les appuis sur les boutons. Il intègre nativement le Wi-Fi et le Bluetooth.
* **Le Connecteur JTAG / UART : Header 2x5 pins/broches (Pas de 2.54mm ou 1.27mm)**
  * *Rôle :* C'est la "prise diagnostic" du PCB. Elle permet de relier la carte à l'ordinateur pour injecter le code et lire les erreurs.
* **Le Programmateur Externe : ESP-PROG-2**
  * *Rôle :* Outil physique officiel d'Espressif (qui ne reste pas sur la lampe). Il fait le pont entre le port USB de l'ordinateur et le connecteur JTAG du PCB pour flasher et déboguer le code de l'ESP32.

## 2.  L'Alimentation et l'Énergie

* **L'Entrée Secteur : Connecteur USB-C (avec module Trigger 12V)**
  * *Rôle :* Permet de brancher un chargeur mural standard (fournissant du 12V DC) pour utiliser la lampe à la maison sans vider la batterie.
* **L'Entrée Batterie : Connecteur JST**
  * *Rôle :* Relie le pack batterie maison 4S (14.8V nominal / 16.8V max) au circuit.
* **Le Sélecteur de Source : Interrupteur à bascule (SPDT - 3 broches)**
  * *Rôle :* Sécurité matérielle. Il permet de basculer physiquement l'alimentation de la lampe soit sur la Batterie, soit sur le Secteur, empêchant les deux de se court-circuiter.
* **Le Grand Régulateur 5V**
  * *Rôle :* Il prend le 12V (secteur) ou le 16.8V (batterie) et le rabaisse à un **5V** très puissant (capable de fournir au moins 7 à 10 Ampères) pour alimenter l'intégralité du ruban LED.
* **Le Petit Régulateur 3.3V**
  * *Rôle :* Il prend le 12V et le rabaisse en un **3.3V** très propre et stable, uniquement pour l'ESP32 qui ne supporte pas le 5V.

## 3.  Interface et Lumière

* **Le Level Shifter : SN74AHCT125N (ou 74AHCT125D en CMS)**
  * *Rôle :* Convertisseur de niveau logique ("traducteur"). L'ESP32 envoie les ordres de couleurs en 3.3V, mais les LEDs exigent un signal de 5V. Ce composant rehausse le signal instantanément pour éviter que les LEDs ne clignotent de manière erratique.
* **Le Connecteur Ruban LED : Connecteur JST SM (3 broches) ou Bornier à vis**
  * *Rôle :* Permet de brancher (et débrancher facilement) les 3 fils du ruban Adafruit 1138 (5V, Data, GND) à la carte mère.
* **Boutons Utilisateur : Boutons Poussoirs Tactiles (6x6mm)**
  * *Bouton "Mode" :* Relié à une broche de l'ESP32 pour changer les animations (ex: fondu, clignotement, couleur fixe).
  * *Bouton "Luminosité" :* Relié à une autre broche pour cycler entre différents niveaux d'intensité (ex: 25%, 50%, 100%).
* **Boutons Système : Boutons Poussoirs Tactiles**
  * *Bouton "Reset" (EN) :* Redémarre l'ESP32.

---


##  🛠️ Focus : Le Connecteur JTAG (2x5 pins)

Pour le LumaDome, nous abandonnons le connecteur UART simple pour une interface **JTAG professionnelle**. Cela permet non seulement de flasher le code, mais aussi de faire du **débogage en temps réel** (arrêt sur image du code, lecture des variables).

### A. Choix matériel

* **Type :** Barrette de broches mâle (**Pin Header 2x5**).
* **Pas (Pitch) :** **2.54 mm** (choisi pour la facilité de soudure manuelle).
* **Câblage :** Relié au port "JTAG" de l'**ESP-Prog 2** via une nappe 10 fils.

### B. Plan de connexion (Netlist) vers l'ESP32

Ce tableau définit comment relier le connecteur 2x5 aux broches du module ESP32-WROOM-32E dans KiCad :

| Broche Connecteur (2x5) | Signal JTAG | Broche ESP32-WROOM | Fonction |
| --- | --- | --- | --- |
| **1** | **VDD** | **3V3** | Alimentation logique |
| **2** | **TMS** | **GPIO 14** | Test Mode Select |
| **3** | **GND** | **GND** | Masse |
| **4** | **TCK** | **GPIO 13** | Test Clock |
| **5** | **GND** | **GND** | Masse |
| **6** | **TDO** | **GPIO 15** | Test Data Out |
| **7** | **NC** | - | Non connecté |
| **8** | **TDI** | **GPIO 12** | Test Data In |
| **9** | **GND** | **GND** | Masse |
| **10** | **RESET** | **EN** | Hard Reset automatique |

---

## 3. 💡 Recommandations pour la conception du PCB

###  Routage et Signaux

* **Détrompeur :** Marquer la **broche 1** sur le PCB avec un petit triangle blanc en sérigraphie pour éviter de brancher la nappe à l'envers.
* **Intégrité du signal :** Les pistes JTAG (TDI, TDO, TCK, TMS) transportent des signaux rapides. Il faut les router de manière directe et éviter de les faire passer trop près du régulateur Buck 5V pour limiter les parasites.

###  Gestion de la Puissance

* **Largeur des pistes :** Pour les 112 LEDs (consommation max **7,5 A**), utiliser des pistes de puissance d'au moins **3-4 mm** de large ou un plan de cuivre complet sur la face arrière.

---
