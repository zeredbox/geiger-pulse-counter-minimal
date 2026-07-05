# geiger-pulse-counter-minimal

Un programme Arduino/ESP32 ultra-léger, non bloquant, pour s'interfacer avec un tube compteur de radiations Geiger-Müller. Ce code sert de base matérielle propre pour des projets plus avancés tels que moniteurs de radioactivité (CPM/µSv/h) ou générateurs de nombres aléatoires quantiques (TRNG).

## 🚀 Caractéristiques
* **Géré par interruptions (ISR) :** Capture les impulsions instantanément sans ralentir la boucle principale.
* **Zéro bloatware :** Ultra-minimaliste, aucune bibliothèque requise.
* **Multi-plateforme :** Pris en charge nativement sur Arduino Uno, Nano et ESP32.
* **Suivi séquentiel :** Envoie les données via le port Série à `115200` bauds.

## ⚙️ Comment ça marche
1. **Interruption matérielle (ISR) :** Chaque fois qu'une particule radioactive frappe le tube Geiger, le module génère une brève chute de tension. Cela déclenche instantanément la fonction `geigerISR()` via les interruptions matérielles externes, contournant la boucle principale.
2. **Flag non bloquant :** L'ISR ne traite pas les données et n'affiche rien sur le port Série (ce qui ferait planter le microcontrôleur). Elle passe simplement la variable `pulseDetected` à `true`.
3. **Traitement dans la boucle principale :** La fonction `loop()` gère l'affichage et incrémente un compteur 32 bits (`pulseCount`) pour enregistrer chaque événement de manière séquentielle (`detection 1`, `detection 2`, etc.).

## 🛠️ Montage électrique

| Broche Module Geiger | Broche Arduino | Rôle / Notes |
| :--- | :--- | :--- |
| **VCC** | 5V (ou 3.3V) | Alimentation positive |
| **GND** | GND | Masse commune |
| **INT / PULSE / VIN** | Broche D3 (Pin 3) | Signal d'impulsion (Déclenchement sur front descendant `FALLING`) |

> ⚠️ **Note Technique :** La broche numérique 3 (D3) est obligatoire sur Arduino Uno/Nano car elle fait partie des rares broches matérielles supportant les interruptions externes.

## 💻 Exemple de sortie
Chaque fois qu'une particule radioactive traverse le tube, le moniteur série affiche :
```text
Geiger pulse counter ready...
detection 1
detection 2
detection 3
