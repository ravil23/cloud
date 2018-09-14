package main

import (
    "fmt"
    "io/ioutil"
    "log"
    "net/http"
    "os"
    "time"

    "github.com/google/uuid"
    "golang.org/x/net/context"
    "google.golang.org/grpc"
    pb "protobuf"
)

func makeUUID() string {
  new_uuid, err := uuid.NewUUID()
  if err != nil {
    log.Fatalf("can't generate new uuid: %v", err)
  }
  return new_uuid.String()
}

func makeTimestamp() int64 {
  return time.Now().UnixNano() / 1000000
}

func main() {
  word_count_analyzer_address := os.Getenv("WORD_COUNT_ANALYZER_ADDRESS")
  frontend_port := ":" + os.Getenv("FRONTEND_PORT")

  // Set up a connection to the server.
  conn, err := grpc.Dial(word_count_analyzer_address, grpc.WithInsecure())
  if err != nil {
    log.Fatalf("did not connect: %v", err)
  }
  defer conn.Close()
  c := pb.NewAnalyzerClient(conn)

  // Create handler.
  word_count_handler := func(w http.ResponseWriter, r *http.Request) {
    // Contact the server and print out its response.
    ctx, cancel := context.WithTimeout(context.Background(), time.Second)
    defer cancel()
    
    body, err := ioutil.ReadAll(r.Body)
    if err != nil {
      log.Fatalf("error reading body: %v", err)
      return
    }

    output, err := c.Analyze(ctx, &pb.AnalyzerInput{
      Id: makeUUID(),
      Timestamp: makeTimestamp(),
      Text: string(body)})
    if err != nil {
      log.Fatalf("could not analyze: %v", err)
    }
    fmt.Fprintf(w, "%s", output)
  }

  // Configure and run server.
  http.HandleFunc("/word_count", word_count_handler)
  log.Fatal(http.ListenAndServe(frontend_port, nil))
}