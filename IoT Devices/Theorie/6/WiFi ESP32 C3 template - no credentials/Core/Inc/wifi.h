#if !defined(WIFI_DEFINED)
	#define WIFI_DEFINED
	
	// TODO: dit bestand volledig aanpassen aan je eigen noden...
	
	// WiFi-instellingen.	
	#define WIFI_SSID 			"devbit"
	#define WIFI_PWD 				"..."
	
	// De hosts definiëren.
	// Let op: de host name mag maximum 64 bytes lang zijn, anders 'ERROR' bij CIPSTART!
	#define HTTP_HOST 						"....be"
	#define HTTPS_HOST 						"....firebasedatabase.app"  // Deze database link kan je opzoeken in je Firebase console.
	
	// URL's definiëren.
	#define HTTP_URL_GET 			"/iot/esp32c3/index.php"
	#define HTTP_URL_POST			"/iot/esp32c3/index.php"	
	#define HTTPS_URL_GET 		"/advalue.json"							// Wil je in één specifieke waarde lezen, zet dan '/advalue.json'.
	#define HTTPS_URL_PATCH 	"/.json"										// Wil je in de 'root' schrijven, zet dan '/.json'.
	
	// API key voor HTTP.
	#define HTTP_APIKEY 		"..."
	
	// API key voor HTTPS.
	// Om zonder 'authenticatie objecten' te kunnen werken, moet een unieke sleutel mee verzonden worden.
	// Je kan het 'database secret' opvragen via de Firebase console. Zie: Project settings -> Service Accounts -> Database secrets.
	#define HTTPS_DATABASE_SECRET	"..."	
	
	// MQTT defines.	
	#define MQTT_SUB_TOPIC 				"vives/.../advalue"
	#define MQTT_PUB_TOPIC 				"vives/.../advalue"
	#define MQTT_BROKER_ADDRESS 	"test.mosquitto.org"
	#define MQTT_PORT 						1883
	#define MQTT_USER 						""
	#define MQTT_PWD 							""
	#define MQTT_CLIENT_ID 				"ESP32C3_..."
#endif
