#pragma once

const char* toolConfigSetupHtmlForm = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <title>Device Setup</title>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <style>
        body { font-family: Arial; padding: 20px; background: #f4f4f4; }
        form { background: white; padding: 20px; border-radius: 8px; max-width: 300px; margin: auto; }
        input[type="text"], input[type="password"] {
          width: 100%; padding: 8px; margin: 6px 0; border: 1px solid #ccc; border-radius: 4px;
        }
        input[type="submit"] {
          background-color: #4CAF50; color: white; padding: 10px;
          border: none; border-radius: 4px; cursor: pointer;
        }
      </style>
    </head>
    <body>
      <h2>Register Device</h2>
      <form action="/submit" method="POST">
        <label>Code:</label>
        <input type="text" name="code" required>
        <label>Wi-Fi SSID:</label>
        <input type="text" name="wifi_ssid" required>
        <label>Wi-Fi Password:</label>
        <input type="password" name="wifi_pass" required>
        <input type="submit" value="Register">
      </form>
    </body>
    </html>
    )rawliteral";