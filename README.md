# 🔐 Coffre-fort RFID Autonome

### 📝 Description du projet
Un système de contrôle d'accès physique sécurisé. Il intègre une gestion locale des badges autorisés via une Master Card.

### ⚙️ Implémentation Technique
* **Hardware :** Arduino Leonardo, Module RC522 (SPI), Moteur Pas-à-pas (Stepper), LED RGB, Buzzer.
* **Architecture Logicielle :** Basé sur une **Machine à États Finis** pour gérer les états de sécurité (Verrouillé, Ouvert, Alarme, Mode Admin).
* **Fonctionnalité Clé - "Master Card" :** Une carte spéciale permet d'ajouter ou de retirer des badges utilisateurs dynamiquement dans la **RAM** (Mémoire vive).
    * *Note technique :* Les badges utilisateurs sont stockés de manière volatile. À chaque redémarrage du système, la liste est réinitialisée et seul le badge "Admin" (défini dans le code) reste valide, ce qui assure une remise à zéro automatique de la sécurité.

### 🔌 Câblage (Pinout)
* **Lecteur RFID (RC522 - Bus SPI)** :
    * **SDA (SS)** -> Pin **10**
    * **SCK** -> Pin **ICSP-3**
    * **MOSI** -> Pin **ICSP-4**
    * **MISO** -> Pin **ICSP-1**
    * **RST** -> Pin **2**
* **Moteur Pas-à-pas (Driver ULN2003)** :
    * **Signaux de commande** -> Pins **6, 8, 7, 9**
    * **Gestion d'énergie (Alimentation)** -> Pins **A0 et A1** reliées à des **Relais** (ou transistors) pour couper l'alimentation du moteur hors mouvement (évite la chauffe inutile).
* **LED RGB** : Rouge (**3**), Verte (**4**), Bleue (**5**)
* **Buzzer** -> Pin **11**

### 📺 Démo Vidéo
[▶️ Voir la démonstration vidéo sur YouTube](https://youtu.be/fK-oMV9J1yQ)

### 📄 Licence
Ce projet est sous licence **GNU GPLv3**. Vous êtes libres d'utiliser, modifier et redistribuer ce logiciel, à condition de me créditer et de conserver la même licence libre pour les travaux dérivés.
