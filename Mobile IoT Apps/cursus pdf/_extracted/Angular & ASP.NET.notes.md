# Notes extract: Angular & ASP.NET.pdf

- Pages: 29
- Approx characters extracted: 20441
- Outline items: 29

## Outline (best effort)
- Dia 1: Mobile IoT Apps 2
- Dia 2: Inhoud
- Dia 3: Angular en ASP.NET
- Dia 4: Angular en ASP.NET
- Dia 5: Angular en ASP.NET
- Dia 6: Angular en ASP.NET
- Dia 7: Angular en ASP.NET
- Dia 8: Angular en ASP.NET
- Dia 9: Angular en ASP.NET
- Dia 10: Angular en ASP.NET
- Dia 11: Angular en ASP.NET
- Dia 12: Angular en ASP.NET
- Dia 13: Angular en ASP.NET
- Dia 14: Angular en ASP.NET
- Dia 15: Angular en ASP.NET
- Dia 16: Angular en ASP.NET
- Dia 17: Angular en ASP.NET
- Dia 18: Angular en ASP.NET
- Dia 19: Angular en ASP.NET
- Dia 20: Angular en ASP.NET
- Dia 21: Angular en ASP.NET
- Dia 22: Angular en ASP.NET
- Dia 23: Angular en ASP.NET
- Dia 24: Angular en ASP.NET
- Dia 25: Angular en ASP.NET
- Dia 26: Intermezzo
- Dia 27: Intermezzo
- Dia 28: Angular en ASP.NET
- Dia 29: Angular en ASP.NET

## Per page

### Page 1: ANDERE SLIDE INDELING KIEZEN
- ANDERE SLIDE INDELING KIEZEN
- Gebruik onder de tab ‘Start’ de knop “Indeling”
- om de gewenste slide-indeling te kiezen.
- Indeling
- Opnieuw instellen
- AFBEELDING INVOEGEN/OPMAKEN
- 1 Wanneer nodig, verwijder de bestaande afbeelding d.m.v.
- de ‘Backspace toets’. Klik op het pictogram om een nieuwe
- afbeelding in te voegen (zie onderstaand vb) of ga naar
- Invoegen > Afbeeldingen.
- 2 Selecteer de gewenste afbeelding
- en klik op ‘Invoegen’.

### Page 2: ANDERE SLIDE INDELING KIEZEN
- Web API
- Web API met controllers
- Web API met MongoDB
- Angular App - die gebruik maakt van Web API
- SignalR toevoegen aan Web API
- SignalR toevoegen aan Angular App

### Page 3: ANDERE SLIDE INDELING KIEZEN
- ANDERE SLIDE INDELING KIEZEN
- Gebruik onder de tab ‘Start’ de knop “Indeling”
- om de gewenste slide-indeling te kiezen.
- Indeling
- Opnieuw instellen
- TEKSTNIVEAUS KIEZEN
- Gebruik onder de tab ‘Start’ de lijstniveau-knoppen
- om een tekst niveau te kiezen. Kies uit:
- Start Tekstniveau omhoog
- Tekstniveau omlaag
- Angular en ASP.NET
- Web API

### Page 4: ANDERE SLIDE INDELING KIEZEN
- Nieuw project bevat Weatherforecast controller op
- Standaard geen swagger maar OpenAPI JSON op

### Page 5: ANDERE SLIDE INDELING KIEZEN
- dotnet add package Swashbuckle.AspNetCore
- In Program.cs

### Page 6: ANDERE SLIDE INDELING KIEZEN
- In VSCode: CTRL+F5 => RUN
- voeg /swagger toe aan URL
- Swagger: API documentation

### Page 7: ANDERE SLIDE INDELING KIEZEN
- T oevoegen model "T odoItem" in folder Models

### Page 8: ANDERE SLIDE INDELING KIEZEN
- database context toevoegen in betand T odoContext.cs in de Models folder

### Page 9: ANDERE SLIDE INDELING KIEZEN
- Entity Framework | Microsoft Learn
- Creating a Model - EF6 | Microsoft Learn

### Page 10: ANDERE SLIDE INDELING KIEZEN
- database context registreren in program.cs,

### Page 11: ANDERE SLIDE INDELING KIEZEN
- voeg de nuget packages toe en installeer de code-generator:
- installeer EntityFrameworkCore.T ools:
- genereer de T odoItemsController met de code-generator
- m T odoItem -dc T odoContext -outDir Controllers

### Page 12: ANDERE SLIDE INDELING KIEZEN
- PostT odoItem
- location header URI: GET /api/T odoItems/{id}

### Page 13: ANDERE SLIDE INDELING KIEZEN
- ANDERE SLIDE INDELING KIEZEN
- Gebruik onder de tab ‘Start’ de knop “Indeling”
- om de gewenste slide-indeling te kiezen.
- Indeling
- Opnieuw instellen
- TEKSTNIVEAUS KIEZEN
- Gebruik onder de tab ‘Start’ de lijstniveau-knoppen
- om een tekst niveau te kiezen. Kies uit:
- Start Tekstniveau omhoog
- Tekstniveau omlaag
- Angular en ASP.NET
- Web API met Controllers

### Page 14: ANDERE SLIDE INDELING KIEZEN
- T est web APIs with the HttpRepl | Microsoft Learn
- dotnet tool install -g Microsoft.dotnet-httprepl
- httprepl http://localhost:5008
- get /api/todoitems

### Page 15: ANDERE SLIDE INDELING KIEZEN
- Prevent over-posting
- DTO: Data T ransfer Object
- voeg veld Secret toe aan T odoItem.cs
- maak DTO:
- Maak gebruik van functie ItemT oDTO

### Page 16: ANDERE SLIDE INDELING KIEZEN
- Create a web API with ASP .NET Core and MongoDB | Microsoft Learn
- MongoDB=NoSQL database
- MongoDB is a document database with the scalability and flexibility that you want with the

### Page 17: ANDERE SLIDE INDELING KIEZEN
- Installeer
- MongoDB
- Op laptop MongoDB Community Server | MongoDB: winget install MongoDB.Server -i
- Cloud: MongoDB Atlas | Multi-cloud Developer Data Platform | MongoDB
- MongoDB Shell T ry MongoDB T ools - Download Free Here | MongoDB
- Configuratie van MongoDB
- PATH updaten
- met mongodb: C:\Program Files\MongoDB\Server\<version_number>\bin
- met mongosh: C:\Software\mongosh-1.6.0-win32-x64\bin
- mongod --dbpath <data_directory_path>

### Page 18: ANDERE SLIDE INDELING KIEZEN
- mongosh <connectiestring>
- use BookStore
- db.createCollection('Books')
- db.Books.insertMany([{ "Name": "Design Patterns", "Price": 54.93, "Category": "Computers",
- db.Books.find().pretty()

### Page 19: ANDERE SLIDE INDELING KIEZEN
- Create the ASP .NET Core web API project
- dotnet new webapi -o BookStoreApi
- code BookStoreApi
- dotnet add package MongoDB.Driver
- Add an entity model Models/Book.cs:

### Page 20: ANDERE SLIDE INDELING KIEZEN
- Add a configuration model
- aanpassen appsettings.json
- BookStoreDataBaseSettings class toevoegen onder Models
- in Program.cs - settings van appsettings.json verkrijgen door:
- Add a CRUD operations service
- BooksService in Services folder toevoegen met CRUD opdrachten
- BookService als Singleton toevoegen aan Program.cs
- Add a controller
- Voeg BooksController toe aan de Controllers folder

### Page 21: ANDERE SLIDE INDELING KIEZEN
- T est the web API
- dotnet run
- Configure JSON serialization options
- Wat:
- naamgeving camel casing => Pascal Casing (bvb bookName => BookName)
- de naam van een property wijzigen t.o.v. naamgeving in de code
- Hoe:
- Program.cs: AddJsonOptions aan AddControllers toevoegen
- attribuut [JsonPropertyName("Name")]

### Page 22: ANDERE SLIDE INDELING KIEZEN
- Swagger

### Page 23: ANDERE SLIDE INDELING KIEZEN
- Maak een Angular App die communiceert met de Web API met MongoDB database die:
- een lijst van boeken toont
- een form weergeeft waarmee je een boek kunt toevoegen

### Page 24: ANDERE SLIDE INDELING KIEZEN
- Maak een lege angular App:
- indient geen ntfs:
- ng new angular-webapi
- cd angular-webapi
- ng add @angular/material
- ng g component fetch-data
- CORS fout:

### Page 25: ANDERE SLIDE INDELING KIEZEN
- Als de response van een ander domein geen CORS headers meegeeft => CORS fout
- Waarom CORS => What is CORS (cross-origin resource sharing)? T utorial & Examples | Web
- CORS headers toevoegen aan Web API: Enable Cross-Origin Requests (CORS) in ASP .NET Core |

### Page 26: ANDERE SLIDE INDELING KIEZEN
- problemen bij ophalen packages => controleren of NuGet.config correct is

### Page 27: ANDERE SLIDE INDELING KIEZEN
- Selectie van .NET SDK => via global.json wordt gezocht in werkdirectory en parent folders
- inhoud global.json:

### Page 28: ANDERE SLIDE INDELING KIEZEN
- SignalR: Introduction to SignalR | Microsoft Learn
- SignalR in ASP .NET <-> Socket.io in node.js
- Uitvoeren van de T utorials
- Get started with ASP .NET Core SignalR | Microsoft Learn
- T utorial: Get started with ASP .NET Core SignalR using TypeScript and Webpack | Microsoft Learn

### Page 29: ANDERE SLIDE INDELING KIEZEN
- backend: SignalRChatHub: hans-naert/SignalRChat (github.com)
- angular app: hans-naert/angular-signalr (github.com)
- Voeg SignalR toe aan de Web API (aanpassen hans-naert/ASP .NET-Core-web-API-MongoDB
- Voeg SignalR toe aan de Angular App (aanpassen hans-naert/angular-webapi (github.com))
- T oon een lijst met de TODO's, via SignalR laat je de lijst updaten als er een item wordt toegevoegd
