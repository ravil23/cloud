# Architecture

+--------------------------------+ +----------+
|            Endpoint            | |          |
+--------------------------------+ |          |
             ||   /\               |   JSON   |
http-request ||   || http-response |          |
             \/   ||               |          |
+--------------------------------+ |          |
|       Frontend Server (Go)     | +----------+
+--------------------------------+ |          |
             ||   /\               |          |
        task ||   || result        |          |
             \/   ||               |          |
+--------------------------------+ |          |
|       Backend Manager (C++)    | |          |
+--------------------------------+ |          |
             ||   /\               |          |
  input data ||   || output data   | Protobuf |
             \/   ||               |          |
+---------------++---------------+ |          |
|   Analyzers   ||    Analyzers  | |          |
|     (C++)     ||      (C++)    | |          |
+---------------++---------------+ |          |
          \              /         |          |
+--------------------------------+ |          |
|            Storage             | |          |
+--------------------------------+ +----------+

## Docker

All servers, managers and analyzers running in Docker container with Ubuntu.

## Usage example
curl \
  --header "Content-Type: application/json" \
  --request GET
  --data '{"id":"0","message":"0123456789ABCDEF"}' \
  http://localhost:3000/api/login