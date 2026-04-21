package org.codeberg.DeployedReject;

import com.google.gson.JsonObject;

public class ErrorHelper {
  public void errorJson(String error) {

    JsonObject response = new JsonObject();
    response.addProperty("status", 1);
    response.addProperty("error", error);
    System.out.println(response.toString());
  }
}
