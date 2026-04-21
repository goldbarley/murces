
package org.codeberg.DeployedReject;

import java.net.MalformedURLException;
import java.util.Properties;
import java.util.Scanner;
import com.google.gson.JsonObject;
import java.lang.System;
import com.google.gson.JsonParser;
import org.codeberg.DeployedReject.errorHelper;
import org.codeberg.DeployedReject.modrinth;
import java.util.Properties;
import java.io.IOException;
import java.io.InputStream;
import org.codeberg.DeployedReject.serverDownload;

public class Main {
  public static void main(String[] args) throws MalformedURLException, IOException, InterruptedException {

    Properties env = new Properties();
    try (InputStream envStream = Main.class.getClassLoader().getResourceAsStream("config.properties")) {
      env.load(envStream);
      env.getProperty("curseAPI");
    }

    Scanner sc = new Scanner(System.in);

    String curseAPI = env.getProperty("curseAPI");
    String email = env.getProperty("email");
    while (true) {
      String temp = sc.nextLine();
      JsonObject request = JsonParser.parseString(temp).getAsJsonObject();
      String type = request.get("type").getAsString();
      if (type.equals("kill"))
        break;
      else if (type.equals("server")) {
        serverDownload.gameVersion = request.get("gameVersion").getAsString();
        serverDownload.serverVersion = request.get("serverVersion").getAsString();
        serverDownload.serverType = request.get("serverType").getAsString();
        serverDownload.type = request.get("subType").getAsString();
        serverDownload.serverHandler();
        continue;
      }
      String modBrowser = request.get("modBrowser").getAsString();

      if (modBrowser.equalsIgnoreCase("modrinth")) {
        modrinth.type = type;
        modrinth.query = request.get("modName").getAsString();
        modrinth.version = request.get("version").getAsString();
        modrinth.loader = request.get("modLoader").getAsString();
        modrinth.email = email;
        modrinth.modrinthHandler();
      } else if (modBrowser.equals("curseForge")) {
        // ToDo
      } else {
        errorHelper.errorJson("Invalid Choice");
      }

    }
    sc.close();
  }
}
