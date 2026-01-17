# Firebase Real-Time Database (RTDB) Setup - Button State Tracking

## Overview
Dit project stuurt knoptoestanden van een STM32 Nucleo-L476RG microcontroller naar Firebase RTDB wanneer de knoppen veranderen (event-based, niet timer-based).

## Configuratie Steps

### 1. Firebase Project Setup
1. Ga naar [Firebase Console](https://console.firebase.google.com/)
2. Maak een nieuw project aan of selecteer een bestaand project
3. Ga naar: **Build** → **Realtime Database**
4. Klik op **Create Database**
5. Selecteer regio (dichtstbijzijnde regio is aanbevolen)
6. Kies startwaarschuwing: **Start in locked mode** (veiliger)
7. Database zal nu aangemaakt worden

### 2. Database Secret Ophalen
1. Ga naar **Project Settings** (tandwiel-icoon rechtsboven)
2. Selecteer **Service Accounts** tab
3. Klik op **Database Secrets**
4. Kopieeer je **Database Secret** 
5. Voeg dit in in `Core/Inc/wifi.h`:
   ```c
   #define HTTPS_DATABASE_SECRET "YOUR_DATABASE_SECRET_HERE"
   ```

### 3. RTDB Hostname Ophalen
1. Ga terug naar **Realtime Database**
2. In de URL-balk zie je iets als: `https://your-project-id.firebasedatabase.app`
3. Voeg dit in in `Core/Inc/wifi.h`:
   ```c
   #define HTTPS_HOST "your-project-id.firebasedatabase.app"
   ```

### 4. Firebase RTDB Security Rules Configureren

**BELANGRIJK**: De standaard "locked mode" rules moeten gewijzigd worden om schrijftoegang toe te staan met database secret.

1. Ga naar **Realtime Database**
2. Klik op het **Rules** tab
3. Vervang de standaardregels met deze beveiligde regels:

```json
{
  "rules": {
    "buttons": {
      ".write": "root.auth.uid != null || auth.token.database_secret == true",
      ".read": "root.auth.uid != null || auth.token.database_secret == true"
    },
    ".read": false,
    ".write": false
  }
}
```

**Uitleg van de rules:**
- `buttons` path: Alleen schrijfbaar/leesbaar voor:
  - Geauthenticeerde gebruikers (via `uid`)
  - OF verzoeken met geldige database secret
- Alle andere paden: Geen lees-/schrijftoegang

4. Klik op **Publish** om de rules op te slaan

### 5. Firmware Configuratie

In `Core/Inc/wifi.h`:
- Vul je WiFi SSID en wachtwoord in
- Vul je Firebase host in
- Vul je database secret in

Voorbeeld:
```c
#define WIFI_SSID           "your_wifi_ssid"
#define WIFI_PWD            "your_wifi_password"
#define HTTPS_HOST          "your-project-id.firebasedatabase.app"
#define HTTPS_DATABASE_SECRET "your-database-secret-key"
```

## Hoe het werkt

### Knopstatus Updates
Het programma monitort voortdurend de 5 beschikbare knoppen:
- **SW1**: Pin A1
- **SW2**: Pin A4
- **SW3**: Pin B0
- **SW4**: Pin C1
- **User Button**: Pin C13

### Event-Triggered Publishing
- De knopstatus wordt **ALLEEN** naar Firebase verzonden wanneer deze **wijzigt**
- Geen timer-based updates (spaartzaam met dataverkeer)
- JSON-payload: 
  ```json
  {
    "SW1": 0 of 1,
    "SW2": 0 of 1,
    "SW3": 0 of 1,
    "SW4": 0 of 1,
    "UserButton": 0 of 1
  }
  ```

### Request Safety
- Boolean flag `isRequestInProgress` voorkomt concurrente verzoeken
- Volgende update verzonden pas nadat vorige response ontvangen

### Firebase Path
Data wordt geschreven naar: `/buttons.json`

## Testing in Firebase Console

1. Laad je microcontroller op
2. Open je project in Firebase Console
3. Ga naar **Realtime Database**
4. Druk op knoppen van je Nucleo Extension Shield
5. De JSON-data verschijnt in real-time onder het `buttons` node
6. In de Debug Console van Visual Studio Code zie je logs zoals:
   ```
   Button state changed - Sending to Firebase: {"SW1":1,"SW2":0,"SW3":0,"SW4":0,"UserButton":0}
   Firebase response received: {...}
   ```

## Troubleshooting

### "Permission denied" fouten
- Controleer of database secret correct is gekopieerd
- Controleer of RTDB rules correct opgeslagen zijn
- Zorg dat je RTDB in "locked mode" begon of rules manueel ingesteld hebt

### Geen verbinding met Firebase
- Controleer WiFi-verbinding (check SSID/PWD in wifi.h)
- Controleer of HTTPS_HOST correct is (geen "https://" prefix nodig)
- Check of database secret correct is

### Slow Updates
- Dit is normaal bij eerste keer met HTTP/HTTPS handshake
- Vervolgende updates zijn sneller omdat TCP-verbinding behouden blijft

## Security Notes

- Database secret mag **NIET** in productie in firmware staan
- Voor productie: Gebruik Firebase Authentication met custom tokens
- Dit project is geschikt voor lab/prototype-omgevingen

## Zie ook
- [Firebase RTDB Documentation](https://firebase.google.com/docs/database)
- [Firebase Security Rules](https://firebase.google.com/docs/database/security)
