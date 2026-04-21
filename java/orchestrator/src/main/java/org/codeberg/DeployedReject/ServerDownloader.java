package org.codeberg.DeployedReject;

import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.net.http.HttpResponse.BodyHandlers;
import com.google.gson.JsonArray;
import com.google.gson.JsonParser;

public class ServerDownloader {
  public String gameVersion;
  public String serverVersion;
  public String serverType;
  public String type;
  ErrorHelper er = new ErrorHelper();

  public void serverHandler() {
    if (serverType.equals("fabric")) {
      fabric();
    } else if (serverType.equals("forge")) {
      // To do
    } else {
      er.errorJson("Invalid Server Type");
    }
  }

  public void fabric() {
    if (type.equals("homepage")) {
      String url = "https://meta.fabricmc.net/v2/versions/game";
      HttpRequest homepaging = HttpRequest.newBuilder()
          .uri(URI.create(url))
          .GET()
          .build();// Dont judge my naming sense.
      HttpClient device = HttpClient.newHttpClient();
      try {
        HttpResponse<String> results = device.send(homepaging, BodyHandlers.ofString());
        JsonArray temp = JsonParser.parseString(results.body()).getAsJsonArray();

        JsonArray response = new JsonArray();

        for (int i = 0; i < 10; i++) {
          response.add(temp.get(i));
        }

        System.out.println(response);
      } catch (Exception e) {
        er.errorJson(e.toString());
      }

    }
  }
}
