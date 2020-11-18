/* Magic Mirror Config Sample
 *
 * By Michael Teeuw https://michaelteeuw.nl
 * MIT Licensed.
 *
 * For more information on how you can configure this file
 * See https://github.com/MichMich/MagicMirror#configuration
 *
 */

var config = {
	address: "localhost",
	 	// Address to listen on, can be:
							// - "localhost", "127.0.0.1", "::1" to listen on loopback interface
							// - another specific IPv4/6 to listen on a specific interface
							// - "0.0.0.0", "::" to listen on any interface
							// Default, when address config is left out or empty, is "localhost"
	port: 8080,
	basePath: "/", 	// The URL path where MagicMirror is hosted. If you are using a Reverse proxy
					// you must set the sub path here. basePath must end with a /
	ipWhitelist: ["127.0.0.1", "::ffff:127.0.0.1", "::1"], 	// Set [] to allow all IP addresses
															// or add a specific IPv4 of 192.168.1.5 :
															// ["127.0.0.1", "::ffff:127.0.0.1", "::1", "::ffff:192.168.1.5"],
															// or IPv4 range of 192.168.3.0 --> 192.168.3.15 use CIDR format :
															// ["127.0.0.1", "::ffff:127.0.0.1", "::1", "::ffff:192.168.3.0/28"],

	useHttps: false, 		// Support HTTPS or not, default "false" will use HTTP
	httpsPrivateKey: "", 	// HTTPS private key path, only require when useHttps is true
	httpsCertificate: "", 	// HTTPS Certificate path, only require when useHttps is true

	language: "kr",
	logLevel: ["INFO", "LOG", "WARN", "ERROR"],
	timeFormat: 24,
	units: "metric",
	// serverOnly:  true/false/"local" ,
	// local for armv6l processors, default
	//   starts serveronly and then starts chrome browser
	// false, default for all NON-armv6l devices
	// true, force serveronly mode, because you want to.. no UI on this device

	modules: [
		{
			module: "alert",
		},
		{
			module: "MMM-GoogleAssistant",
			position: "fullscreen",
			classes:"always",
			config: {
			  assistantConfig: {
				lang: "ko-KR",
				latitude: 37.346975,
				longitude:  127.116676,

			  },
			  micConfig: { // put there configuration generated by auto-installer
				recorder: "arecord",
				device: "plughw:2,0",
			  },
  
			   snowboy: {
				audioGain: 2.0,
				Frontend: true,
				Model: "jarvis",
				Sensitivity: null
			  },

			}
		  },

		{
			module: "updatenotification",
			classes:"always",
			position: "top_bar"
		},
		{
			module: "clock",
			position: "top_left",
			classes:"always",
			
		},
		{
			module: "calendar",
			header: "HOLIDAYS",
			position: "top_center",
			classes:"default",
			config: {
				calendars: [
					{
						symbol: "calendar-check",
						url: ""}
				]
			}
		},

		{
			module: 'MMM-google-route',
			position: 'top_left',
			classes:"known",
			config: {
			   key: '',
			   directionsRequest: {
				  origin: '46.815887, -71.208493',
				  destination: '46.810374, -71.225790'
			   }
			}
		 },
		
		{
			module: "currentweather",
			position: "top_right",
			classes:"yongin",
			config: {
				location: "seongnam",
				locationID: "", //ID from http://bulk.openweathermap.org/sample/city.list.json.gz; unzip the gz file and find your city
				appid: ""
			}
		},
		{
			module: "weatherforecast",
			position: "top_right",
			header: "Weather Forecast",
			classes:"yongin",
			config: {
				location: "seongnam",
				locationID: "", //ID from http://bulk.openweathermap.org/sample/city.list.json.gz; unzip the gz file and find your city
				appid: ""
			}
		},
		{
			module: "currentweather",
			position: "top_right",
			classes:"gahyun",
			config: {
				location: "seoul",
				locationID: "", //ID from http://bulk.openweathermap.org/sample/city.list.json.gz; unzip the gz file and find your city
				appid: ""
			}
		},
		{
			module: "weatherforecast",
			position: "top_right",
			header: "Weather Forecast",
			classes:"gahyun",
			config: {
				location: "seoul",
				locationID: "", //ID from http://bulk.openweathermap.org/sample/city.list.json.gz; unzip the gz file and find your city
				appid: ""
			}
		},
		{
			module: "currentweather",
			position: "top_right",
			classes:"jungwon",
			config: {
				location: "seoul",
				locationID: "", //ID from http://bulk.openweathermap.org/sample/city.list.json.gz; unzip the gz file and find your city
				appid: ""
			}
		},
		{
			module: "weatherforecast",
			position: "top_right",
			header: "Weather Forecast",
			classes:"jungwon",
			config: {
				location: "seoul",
				locationID: "", //ID from http://bulk.openweathermap.org/sample/city.list.json.gz; unzip the gz file and find your city
				appid: ""
			}
		},
		{
			module: "newsfeed",
			position: "bottom_bar",
			classes:"known",
			config: {
				feeds: [
					{
						title: "",
						url: "https://news.sbs.co.kr/news/SectionRssFeed.do?sectionId=01&plink=RSSREADER"
					}
				],
				showSourceTitle: true,
				showPublishDate: true,
				broadcastNewsFeeds: true,
				broadcastNewsUpdates: true
			}
		},
		{
			module: "newsfeed",
			position: "bottom_bar",
			classes:"yongin",
			config: {
				feeds: [
					{
						title: "",
						url: "https://news.sbs.co.kr/news/SectionRssFeed.do?sectionId=02&plink=RSSREADER"
					}
				],
				showSourceTitle: true,
				showPublishDate: true,
				broadcastNewsFeeds: true,
				broadcastNewsUpdates: true
			}
		},


		  {
			module: "calendar",
			header: "Schedule",
			position: "top_center",
			classes:"yongin",
			config: {
				calendars: [
					{
						symbol: "calendar-check",
						url: ""
					}
				]
			}
		},
		{
			module: "calendar",
			header: "today's schedule",
			position: "top_center",
			classes:"gahyun",
			config: {
			   calendars: [{
				  symbol: "calendar-check",
				  url:""
			   }]
			}
		 },
		 {
			module: "calendar",
			header: "today's schedule",
			position: "top_center",
			classes:"jungwon",
			config: {
			   calendars: [{
				  symbol: "calendar-check",
				  url:""
			   }]
			}
		 },
		 {
			module: "calendar",
			header: "today's schedule",
			position: "top_center",
			classes:"hyunsoo",
			config: {
			   calendars: [{
				  symbol: "calendar-check",
				  url:""
			   }]
			}
		 },
   

		{
			module: "MMM-Face-Multi-User-Recognition-SMAI",
			position: "top_right",
			classes:"always",
			config: {
			  useMMMFaceRecoDNN: true
			}
		  },
		  {
			module: 'MMM-Face-Reco-DNN',
			config: {
			  // Logout 15 seconds after user was not detected any more                    
			  // If they are detected within this period, the delay will start again
			  logoutDelay: 180000,
			  // How often the recognition starts in milliseconds
			  // With a Raspberry Pi 3+ it works well every 2 seconds
			  checkInterval: 2000,
			  // Module set used for when there is no face detected ie no one is in front of the camera
			  noFaceClass: 'noface',
			  // Module set used for when there is an unknown/unrecognised face detected
			  unknownClass: 'unknown',
			  // Module set used for when there is a known/recognised face detected
			  knownClass: 'known',
			  // Module set used for strangers and if no user is detected
			  defaultClass: 'default',
			  // Set of modules which should be shown for any user ie when there is any face detected
			  everyoneClass: 'everyone',
			  // Set of modules that are always shown - show if there is a face or no face detected
			  alwaysClass: 'always',
			  // XML to recognize with haarcascade
			  cascade: 'modules/MMM-Face-Reco-DNN/tools/haarcascade_frontalface_default.xml',
			  // Pre-encoded pickle with the faces
			  encodings: 'modules/MMM-Face-Reco-DNN/tools/encodings.pickle',
			  // Use Raspberry Pi camera or another type
			  // 1 = RasPi camera, 0 = other camera
			  usePiCamera: 0,
			  // If using another type of camera, you can choose
			  // i.e. 0 = /dev/video0 or 'http://link.to/live'
			  source: 0,
			  // Rotate camera
			  rotateCamera: 0,
			  // Method of facial recognition
			  // dnn = deep neural network, haar = haarcascade
			  method: 'dnn',
			  // Which face detection model to use
			  // "hog" is less accurate but faster on CPUs
			  // "cnn" is a more accurate deep-learning model which is GPU/CUDA accelerated
			  detectionMethod: 'hog',
			  // How long in milliseconds modules take to hide and show
			  animationSpeed: 0,
			  // Path to Python to run the face recognition
			  // null or '' means default path
			  pythonPath: null,
			  // Should a welcome message be shown using the MagicMirror alerts module?
			  welcomeMessage: true,
			  // Capture new pictures of recognized people, if unknown we save it in folder "unknown"
			  // So you can extend your dataset and retrain it afterwards for better recognitions
			  extendDataset: false,
			  // If extendDataset is true, you need to set the full path of the dataset
			  dataset: 'modules/MMM-Face-Reco-DNN/dataset/',
			  // How much distance between faces to consider it a match. Lower is more strict.
			  tolerance: 0.6,
			  // allow multiple concurrent user logins, 0=no, any other number is the maximum number of concurrent logins
			  multiUser: 0,
			}
		},
		{
			module: "MMM-NowPlayingOnSpotify",
			position: "top_center",
			classes:"known",
			config: {
			  clientID: "",
			  clientSecret: "",
			  accessToken: "",
			  refreshToken: ""
			}
		  },
   

		{
			module: 'MMM-MQTT',
			position: 'bottom_right',
			header: 'Bathroom',
			classes:"always",
			config: {
				logging: false,
				useWildcards: false,
				mqttServers: [
					{
						address: '192.168.137.176',  // Server address or IP address
						port: '1883',          // Port number if other than default
						user: 'localhost',          // Leave out for no user
						password: '',  // Leave out for no password
						subscriptions: [
							{
								topic: "sensor/temperature", // Topic to look for
								label: 'Temperature', // Displayed in front of value
								suffix: '°C',         // Displayed after the value
								decimals: 1,          // Round numbers to this number of decimals
								sortOrder: 10,        // Can be used to sort entries in the same table
								maxAgeSeconds: 60,    // Reduce intensity if value is older
								colors: [             // Value dependent colors
									{ upTo: -10, value: "blue", label: "blue", suffix: "blue" },
									{ upTo: 0, value: "#00ccff", label: "#00ccff", suffix: "#00ccff" },
									{ upTo: 10, value: "yellow"},
									{ upTo: 25, label: "green", suffix: "green" },
									// { upTo: 100, label: "red" }, // The last one is used for higher values too
								],
							},
							{
								topic: 'sensor/humidity',
								label: 'Humidity',
								suffix: '%',
								decimals: 0,
								sortOrder: 20,
								maxAgeSeconds: 60
							},
						]
					}
				]
		},
					

		{
			module: 'MMM-PIR-Sensor', 
			position: "top_left", // Remove this line to avoid having an visible indicator
			classes:"always",
			config: {
				sensorPin: 22,
				powerSavingDelay: 60, // Turn HDMI OFF after 60 seconds of no motion, until motion is detected again
				preventHDMITimeout: 60, // Turn HDMI ON and OFF again every 4 minutes when power saving, to avoid LCD/TV timeout
				supportCEC: true, 
				presenceIndicator: "fa-eye", // Customizing the indicator
				presenceOffIndicator: "fa-eye", // Customizing the indicator
				presenceIndicatorColor: "#f51d16", // Customizing the indicator
				presenceOffIndicatorColor: "#2b271c" // Customizing the indicator
			}
		},



	]
};

/*************** DO NOT EDIT THE LINE BELOW ***************/
if (typeof module !== "undefined") {module.exports = config;}
