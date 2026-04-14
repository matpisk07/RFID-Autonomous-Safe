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
    * **SCK** -> Pin **ICSP-3** (ou Pin 15 sur l'Arduino Leonardo)
    * **MOSI** -> Pin **ICSP-4** (ou Pin 16 sur l'Arduino Leonardo)
    * **MISO** -> Pin **ICSP-1** (ou Pin 14 sur l'Arduino Leonardo)
    * **RST** -> Pin **2**
    * *Note : Sur Leonardo, le SPI passe par le connecteur ICSP central.*
* **Moteur Pas-à-pas (28BYJ-48) & Driver ULN2003** :
    * **IN1** -> Pin **6**
    * **IN2** -> Pin **7**
    * **IN3** -> Pin **8**
    * **IN4** -> Pin **9**
    * **Alimentation Driver (VCC/GND)** -> Reliée via des **Relais** (pilotés par **A0 et A1**) pour couper le courant hors mouvement et éviter la surchauffe du moteur.
* **Interface utilisateur & Indicateurs** :
    * **LED RGB (Anode commune)** : Rouge (Pin **3**), Verte (Pin **4**), Bleue (Pin **5**).
    * **Buzzer** -> Pin **11**.

### 📺 Démo Vidéo
[▶️ Voir la démonstration vidéo sur YouTube](https://youtu.be/fK-oMV9J1yQ)

### 📄 Licence
Ce projet est sous licence **GNU GPLv3**. Vous êtes libres d'utiliser, modifier et redistribuer ce logiciel, à condition de me créditer et de conserver la même licence libre pour les travaux dérivés.
