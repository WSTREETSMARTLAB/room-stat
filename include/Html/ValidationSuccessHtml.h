#pragma once

const char* validationSuccessHtml = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <title>Success</title>
      <meta name="viewport" content="width=device-width, initial-scale=1">
    </head>
    <body>
      <h2>Tool is almost ready to use</h2>
      <p>Please reboot device to connect to Wi Fi</p>
      <form action="/reboot" method="POST">
        <button type="submit">Reboot</button>
      </form>
    </body>
    </html>
    )rawliteral";