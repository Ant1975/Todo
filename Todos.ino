#include "SPI.h"
#include "SD.h"
#include "Ethernet.h"
#include "WebServer.h"
#include "aJSON.h"

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
EthernetClient client;
WebServer webserver("", 80);
aJsonObject* todos;
char * names[3];

void indexCmd(WebServer &server, WebServer::ConnectionType type, char *, bool) {
	server.httpSuccess();
	if (type != WebServer::HEAD) {
		P(helloMsg) = "<!doctype html>\n<html lang=\"en\">\n"
				"<head>\n"
				"\t<meta charset=\"utf-8\">\n"
				"\t<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge,chrome=1\">\n"
				"\t<title>Backbone.js \u2022 TodoMVC</title>\n"
				"\t<link rel=\"stylesheet\" href=\"http://www.cs.helsinki.fi/u/ljlukkar/todo/css/base.css\">\n"
				"\t<!--[if IE]>\n"
				"\t<script src=\"http://www.cs.helsinki.fi/u/ljlukkar/todo/js/ie.js\"></script>\n"
				"\t<![endif]-->\n"
				"</head>\n"
				"<body>\n"
				"\t<section id=\"todoapp\">\n"
				"\t\t<header id=\"header\">\n"
				"\t\t\t<h1>todos</h1>\n"
				"\t\t\t<input id=\"new-todo\" placeholder=\"What needs to be done?\" autofocus>\n"
				"\t\t</header>\n"
				"\t\t<section id=\"main\">\n"
				"\t\t\t<input id=\"toggle-all\" type=\"checkbox\">\n"
				"\t\t\t<label for=\"toggle-all\">Mark all as complete</label>\n"
				"\t\t\t<ul id=\"todo-list\"></ul>\n"
				"\t\t</section>\n"
				"\t\t<footer id=\"footer\"></footer>\n"
				"\t</section>\n"
				"\t<div id=\"info\">\n"
				"\t\t<p>Double-click to edit a todo</p>\n"
				"\t\t<p>Written by <a href=\"https://github.com/addyosmani\">Addy Osmani</a></p>\n"
				"\t\t<p>Part of <a href=\"http://todomvc.com\">TodoMVC</a></p>\n"
				"\t</div>\n"
				"\t<script src=\"http://www.cs.helsinki.fi/u/ljlukkar/todo/js/jquery.min.js\"></script>\n"
				"\t<script src=\"http://www.cs.helsinki.fi/u/ljlukkar/todo/js/lodash.min.js\"></script>\n"
				"\t<script src=\"http://www.cs.helsinki.fi/u/ljlukkar/todo/js/lib/backbone-min.js\"></script>\n"
				"\t<script src=\"http://www.cs.helsinki.fi/u/ljlukkar/todo/js/models/todo.js\"></script>\n"
				"\t<script src=\"http://www.cs.helsinki.fi/u/ljlukkar/todo/js/collections/todos.js\"></script>\n"
				"\t<script src=\"http://www.cs.helsinki.fi/u/ljlukkar/todo/js/views/todos.js\"></script>\n"
				"\t<script src=\"http://www.cs.helsinki.fi/u/ljlukkar/todo/js/views/app.js\"></script>\n"
				"\t<script src=\"http://www.cs.helsinki.fi/u/ljlukkar/todo/js/routers/router.js\"></script>\n"
				"\t<script src=\"http://www.cs.helsinki.fi/u/ljlukkar/todo/js/app.js\"></script>\n"
				"</body>\n"
				"</html>";
		server.printP(helloMsg);
	}
}

void setup() {

	// if we know the key name we can define them to save memory. instead of new char array we use only a pointer
	names[0] = "id";
	names[1] = "title";
	names[2] = "completed";
	names[3] = "order";

	aJson.setNames(names, 4);

	todos = aJson.parse("[{\"title\":\"Arduino JSON REST interface\",\"completed\":true,\"order\":1,\"id\":1}]");

//  Alternative way to create the same object
//	aJsonObject* todo = aJson.createObject();
//	aJson.addItemToObject(todo, "title", aJson.createItem("Arduino JSON REST interface"));
//	aJson.addTrueToObject(todo, "completed");
//	aJson.addNumberToObject(todo,"order", 1);
//	aJson.addNumberToObject(todo,"id", 1);

//	aJsonObject* todos = aJson.createArray();
//	aJson.addItemToArray(todos, todo);

	webserver.addJSONBinding("todos.json", &todos);
	webserver.setDefaultCommand(&indexCmd);

	Serial.begin(9600);
	Ethernet.begin(mac);
	webserver.begin();

	for (byte i = 0; i < 4; i++) {
		// print the value of each byte of the IP address:
		Serial.print(Ethernet.localIP()[i]);
		if (i < 3) {
			Serial.print('.');
		}
	}
	Serial.println();
}

void loop() {
	webserver.processConnection();
}


