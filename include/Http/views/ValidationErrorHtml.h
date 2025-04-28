#pragma once

const char* validationErrorHtml = R"rawliteral(
            <html>
            <head><title>Validation Error</title></head>
            <body>
              <h2>Validation Error</h2>
              <button onclick="window.history.back()">Back</button>
            </body>
            </html>
        )rawliteral";