# 🔐 Coffre-fort RFID Autonome

### 📝 Description du projet
Un système de contrôle d'accès physique sécurisé. Il intègre une gestion locale des badges autorisés via une Master Card.

### ⚙️ Implémentation Technique
* **Hardware :** Arduino Leonardo, Module RC522 (SPI), Moteur Pas-à-pas (Stepper), LED RGB, Buzzer.
* **Architecture Logicielle :** Basé sur une **Machine à États Finis** (FSM) pour gérer les états de sécurité (Verrouillé, Ouvert, Alarme, Mode Admin).
* **Fonctionnalité Clé - "Master Card" :** Une carte spéciale permet d'ajouter des badges utilisateurs dynamiquement dans la **RAM** (Mémoire vive).
    * *Note technique :* Les badges utilisateurs sont stockés de manière volatile. À chaque redémarrage du système, la liste est réinitialisée et seul le badge "Admin" (défini dans le code) reste valide, ce qui assure une remise à zéro automatique de la sécurité.

### 📺 Démo Vidéo
[▶️ Voir la démonstration vidéo sur YouTube](#)

### 📄 Licence
Ce projet est sous licence **GNU GPLv3**. Vous êtes libres d'utiliser, modifier et redistribuer ce logiciel, à condition de me créditer et de conserver la même licence libre pour les travaux dérivés.
