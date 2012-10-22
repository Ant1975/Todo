#include "SPI.h"
#include "Ethernet.h"
#include "WebServer.h"
#include "aJSON.h"

byte mac[] = { 
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
EthernetClient client;
WebServer webserver("", 80);
aJsonObject* todos;

void indexCmd(WebServer &server, WebServer::ConnectionType type, char *, bool) {
  server.httpSuccess();
  if (type != WebServer::HEAD) {
    P(helloMsg) = 
      "<!doctype html>\n"
      "<html lang=\"en\">\n,"
      "<head>\n"
      "    <meta charset=\"utf-8\">\n    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge,chrome=1\">\n"
      "    <title>Backbone.js \u2022 TodoMVC</title>\n"
      "    <link rel=\"stylesheet\" href=\"http://www.cs.helsinki.fi/u/ljlukkar/todo/css/base.css\">\n"
      "    <!--[if IE]>\n    <script src=\"http://www.cs.helsinki.fi/u/ljlukkar/todo/js/ie.js\"></script>\n"
      "    <![endif]-->\n"
      "</head>\n"
      "<body>\n"
      "    <section id=\"todoapp\">\n"
      "        <header id=\"header\">\n"
      "            <h1>todos</h1>\n"
      "            <input id=\"new-todo\" placeholder=\"What needs to be done?\" autofocus>\n"
      "        </header>\n        <section id=\"main\">\n            <input id=\"toggle-all\" type=\"checkbox\">\n"
      "            <label for=\"toggle-all\">Mark all as complete</label>\n            <ul id=\"todo-list\"></ul>\n"
      "        </section>\n        <footer id=\"footer\"></footer>\n    </section>\n    <div id=\"info\">\n"
      "        <p>Double-click to edit a todo</p>\n"
      "        <p>Written by <a href=\"https://github.com/addyosmani\">Addy Osmani</a></p>\n"
      "        <p>Part of <a href=\"http://todomvc.com\">TodoMVC</a></p>\n"
      "    </div>\n"
      "    <script src=\"http://www.cs.helsinki.fi/u/ljlukkar/todo/js/jquery.min.js\"></script>\n"
      "    <script src=\"http://www.cs.helsinki.fi/u/ljlukkar/todo/js/lodash.min.js\"></script>\n"
      "    <script src=\"http://www.cs.helsinki.fi/u/ljlukkar/todo/js/lib/backbone-min.js\"></script>\n"
      "    <script src=\"http://www.cs.helsinki.fi/u/ljlukkar/todo/js/models/todo.js\"></script>\n"
      "    <script src=\"http://www.cs.helsinki.fi/u/ljlukkar/todo/js/collections/todos.js\"></script>\n"
      "    <script src=\"http://www.cs.helsinki.fi/u/ljlukkar/todo/js/views/todos.js\"></script>\n"
      "    <script src=\"http://www.cs.helsinki.fi/u/ljlukkar/todo/js/views/app.js\"></script>\n"
      "    <script src=\"http://www.cs.helsinki.fi/u/ljlukkar/todo/js/routers/router.js\"></script>\n"
      "    <script src=\"http://www.cs.helsinki.fi/u/ljlukkar/todo/js/app.js\"></script>\n"
      "</body>\n"
      "</html>";
    server.printP(helloMsg);
  }
}

void setup() {

  todos =
    aJson.parse(
  "[{\"title\":\"Arduino JSON REST interface\",\"completed\":true,\"order\":1,\"id\":1}]");


  //	aJsonObject* todo = aJson.createObject();
  //	aJson.addItemToObject(todo, "title", aJson.createItem("Arduino JSON REST interface"));
  //	aJson.addTrueToObject(todo, "completed");
  //	aJson.addNumberToObject(todo,"order", 1);
  //	aJson.addNumberToObject(todo,"id", 1);

  //	aJsonObject* todos = aJson.createArray();
  //	aJson.addItemToArray(todos, todo);

  webserver.addJSONBinding(&todos, "todos.json");
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
}

void loop() {
  webserver.processConnection();
}



