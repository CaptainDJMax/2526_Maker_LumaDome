# 2526_Maker_LumaDome

##  Présentation du projet
**LumaDome** est une lampe d'ambiance connectée et intelligente. L'objectif est d'allier esthétique et technique pour afficher des messages dynamiques. Conçue comme un objet design hybride, elle associe une base imprimée en 3D, un abat-jour textile structuré par découpe laser et l'électronique sur mesure et la gestion d'énergie.

Au-delà de l'esthétique, l'objectif est de créer une interface lumineuse capable de :
* Afficher des **notifications visuelles** (ex: simulateur d'aube au réveil).
* Diffuser des **messages personnalisés** envoyés en Bluetooth depuis un smartphone.
* Être totalement **nomade** grâce à une batterie intégrée.





## 🛠 Architecture Technique
Ce projet mobilise 4 axes principaux :
1.  **Mécanique :** Base cylindrique (Impression 3D) contenant l'électronique + Structure haute (Découpe Laser) supportant le textile.
2.  **Électronique :** PCB sur mesure avec microcontrôleur (type ESP32) pour la gestion LED et Bluetooth.
3.  **Énergie :** Système autonome sur batterie LiPo avec gestion de charge (BMS).
4.  **Habillage :** Travail du textile (Couture) pour la diffusion de la lumière.


##  Rétroplanning Prévisionnel 🔗[02_Gestion_Projet/RetroPlanning.md]

[Cliquez ici pour voir le rétroplanning complet et détaillé](./02_Gestion_Projet/RetroPlanning.md)

Ce planning s'aligne sur les séances de formation technique du semestre.

| Date | Phase | Objectifs spécifiques LumaDome |
| :--- | :--- | :--- |
| **19 Janv** | CAD (Conception) | Modélisation 3D de la base (support PCB) et esquisse de la structure laser. |
| **22 Janv** | 3D Print | Lancement de l'impression du prototype de la base. |
| **26 Janv** | Laser Cut | Découpe du squelette/cadre pour l'abat-jour. |
| **29 Janv** | PCB Design | Conception de la carte électronique (ESP32 + Driver LED). |
| **05 Fév** | Batterie (LiPo) | Dimensionnement de la batterie et intégration du BMS. |
| **09 Fév** | Couture | Patronage et assemblage du tissu sur la structure laser. |
| **Fév - Mars** |  Code & Finalisations| Développement du firmware (Bluetooth & Animations) + finalisation des choses pas terminer|
| **Avril** | Finalisation | Assemblage final, finitions et tournage vidéo. |

```mermaid
gantt
    title Rétro-Planning LumaDome (2026)
    dateFormat  YYYY-MM-DD
    axisFormat  %d/%m
    excludes    weekends

    section Phase 1 : Formation & Proto
    Git & Concept (Fait)       :done,    p1_git, 2026-01-15, 1d
    CAD Base 3D (En cours)     :active,  p1_cad, 2026-01-19, 3d
    3D Print (Lancement)       :         p1_3d,  2026-01-22, 1d
    Laser Cut (Structure)      :         p1_las, 2026-01-26, 3d
    PCB Design (KiCad)         :         p1_pcb, 2026-01-29, 4d
    Soudure & Routage          :         p1_sou, 2026-02-02, 3d
    Batterie LiPo & BMS        :         p1_bat, 2026-02-05, 4d
    Couture (Habillage)        :         p1_cou, 2026-02-09, 5d

    section Phase 2 : Dév. LumaDome
    Intégration Méca/Elec      :         p2_int, 2026-02-16, 3d
    Code (Hello World LED)     :         p2_dev1, 2026-02-19, 10d
    Code (Bluetooth BLE)       :         p2_dev2, 2026-03-09, 3d
    Debug & Tests Autonomie    :         p2_deb, 2026-03-12, 4d
    Finitions Tissu            :         p2_fin, 2026-03-16, 3d
    Code (Animations)          :         p2_dev3, 2026-03-19, 4d
    Assemblage Final           :         p2_ass, 2026-03-23, 3d
    Tournage Vidéo             :         p2_vid, 2026-03-26, 4d
    Derniers ajustements       :         p2_adj, 2026-03-30, 7d
    Prép. Soutenance           :         p2_sou, 2026-04-02, 7d
    
    section Jalons
    SOUTENANCE FINALE          :crit, milestone, 2026-04-13, 0d
```
---
