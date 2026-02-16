# Séance 6 : 2 Février 2026 - Conception de Circuit Imprimé (PCB)

##  Objectifs de la séance
* Comprendre la structure physique d'un PCB (Couches, FR4, Cuivre).
* Appréhender les bus de communication (UART, I2C, SPI).
* Maîtriser les règles de conception (Schematic & Layout) sous KiCad.
* Focus spécifique sur l'intégration de l'USB-C et les protections ESD.

##  Résumé du cours

### 1. Anatomie d'un PCB
Un circuit imprimé est un sandwich de plusieurs couches[cite: 19]:
* **Substrat  :** L'isolant rigide (fibre de verre + époxy) qui sert de support.
* **Cuivre (Copper) :** Les pistes conductrices. On parle de couches "Top" (Dessus) et "Bottom" (Dessous).
* **Vernis épargne (Soldermask) :** La couche (souvent verte) qui protège le cuivre et empêche l'étain de baver.
* **Sérigraphie (Silkscreen) :** Le texte blanc pour identifier les composants.



### 2. Workflow sous KiCad
La conception se fait en deux temps:
1.  **Schématique (Schematic) :** On dessine la logique du circuit avec des symboles.
2.  **Routage (Layout/PCB New) :** On transforme les symboles en empreintes physiques (Footprints) et on trace les pistes en cuivre.

### 3. Focus Technique : USB-C et Protections
Pour intégrer un port USB-C proprement (exemple pour alimenter notre carte), il faut respecter certaines règles dictées par le standard :
* **Réversibilité :** Pour que le câble fonctionne dans les deux sens, il faut connecter les broches **CC1** et **CC2** à la masse via deux résistances de **5.1kΩ** distinctes. Cela indique au chargeur qu'il doit fournir du 5V.
* **Protection ESD (Électrostatique) :** L'ajout d'un composant comme le **USBLC6-SC6** (réseau de 5 diodes) est recommandé pour protéger les lignes de données contre les pics de tension ou les mauvais branchements.
* **Diode TVS :** À placer sur l'alimentation pour absorber les surtensions transitoires.



### 4. Bonnes pratiques de Routage
* **Découplage :** Les condensateurs de découplage doivent être placés **au plus près** des broches d'alimentation du composant pour être efficaces.

* **Signaux rapides (USB/Data) :** Il faut router les pistes paires (D+/D-) avec la même longueur (Paires différentielles) pour éviter les décalages de signal.
* **Courant & Vias :**
    * Une règle empirique à retenir : **1 Via standard supporte environ 1A**.
    * La largeur des pistes doit être adaptée au courant qui les traverse (utiliser un calculateur).
* **Unités :** Attention aux datasheets !
    * `mm` = Millimètres.
    * `mil` = Millième de pouce (100 mil = 2.54 mm).

### 5. Astuces KiCad
* **PWR_FLAG :** Symbole spécial à ajouter sur le schéma pour dire au logiciel "Ceci est une source d'alimentation" et éviter les erreurs du DRC (Design Rules Checker).
* **MPN (Manufacturer Part Number) :** Pour tout composant non générique (hors résistances/condensateurs classiques), il est crucial de renseigner la référence fabricant exacte dans les propriétés pour faciliter la commande (BOM).

## 🛠️ Travaux Pratiques 
Conception KiCad
1.  **Schématique :**
    * Intégration du CH334F et du Quartz 12 MHz.
    * Ajout des protections ESD (USBLC6-2) sur toutes les lignes de données.
    * Utilisation du symbole `PWR_FLAG` pour valider les entrées d'alimentation lors du check électrique (ERC).
2.  **Routage (Layout) - Règles Avancées :**
    * **Stackup 4 Couches :** Top (Signaux) / In1 (GND Plane) / In2 (Power Plane) / Bottom (Signaux + Pogo).
    * **Signal Integrity (USB High Speed 480Mbps) :**
        * **Length Matching (Skew) :** Ajustement des longueurs de pistes (D+ vs D-) via des "méandres" (zigzags) pour garantir une tolérance < 0.15mm.
    * **Mécanique :** Placement précis des Pogo-pins selon le DXF officiel du Raspberry Pi Zero.

###  État d'avancement
Le projet est en phase finale : Schéma validé, Routage terminé (y compris les méandres), DRC (Design Rule Check) en cours de correction.

##  Impact sur le projet LumaDome
Ce TP m'a permis de valider la conception USB-C. Pour mon projet personnel (LumaDome), j'appliquerai les mêmes règles (Résistances 5.1kΩ + USBLC6) pour la prise de charge et la programmation si besoin dans mon projet.

## ✅ Tâches effectuées
- [x] Cours théorique sur les bus (I2C, UART) et les couches PCB.
- [x] Analyse du schéma de référence pour l'USB-C (Résistances CC + ESD).
- [x] Saisie du schématique complet du Hub CH334F sous KiCad.
- [x] Placement et routage complexe (4 couches + Paires différentielles).
- [ ] Création du projet KiCad pour le LumaDome (À faire).