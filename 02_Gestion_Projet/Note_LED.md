###  Note Technique : Dimensionnement des LEDs (Ref: Adafruit 1138)

#### 1. Choix du Matériel (Éclairage)
* **Référence retenue :** Adafruit 1138-4m (NeoPixel Digital RGB LED Strip - White PCB).
* **Spécifications :** Alimentation **5V DC**, densité standard de **60 LEDs/mètre**, adressables individuellement (WS2812B/SK6812).
* **Avantages :** La bobine de 4 mètres permet de couvrir le projet avec une seule bande .

#### 2. Calculs de Dimensionnement (Surface & Longueur)
Pour créer une grille lumineuse homogène sur la surface du LumaDome ($31 160.67 \text{ mm}^2$) :
* **Espacement :** À 60 LEDs par mètre, l'écart entre chaque puce LED est de **16.5 mm**.
* **aire LED théorique :** Longueur x largeur = $16,5 * 12,5$ = **206,25 mm²**.
* **Verdict :** Pour tapisser parfaitement la surface, environ $31 160.67 / 206,25 = 152$ LED nécessaires. L'achat de la bobine de 4 mètres garantit d'avoir suffisamment de matière.

#### 3.  Bilan de Puissance & Électronique.
* **Consommation (pour 125 LED) :** Chaque LED consomme jusqu'à 60mA (en blanc luminosité max). $125 \times 0.06\text{A}$ = **7.5 Ampères** (soit environ 37.5 Watts).


#### 4. Intégration sur le PCB
* **Alimentation (Convertisseur Buck) :** Pour passer de la batterie 4S (~14.8V) au 5V requis par les LEDs, un module Step-Down 5V capable de fournir **10 Ampères** de manière stable sera parfait (il y a une bonne marge de sécurité).
* **Routage KiCad :** Un courant de 7.5 A est parfaitement gérable, mais il faut appliquer la règle de dimensionnement vue en cours : **1 Via supporte environ 1 Ampère**. Il faudra donc utiliser des pistes d'alimentation larges et placer plusieurs Vias pour les changements de couche.