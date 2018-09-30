package main

import (
  "fmt"
  "io/ioutil"
  "log"
  "net/http"
  "time"

  "golang.org/x/net/context"
  "google.golang.org/grpc"
  pb "proto_go"
)

func analyzeWordCount(c pb.AnalyzerClient, w http.ResponseWriter, r *http.Request) {
  // Read request data
  body, err := ioutil.ReadAll(r.Body)
  if err != nil {
    log.Fatalf("error reading body: %v", err)
    return
  }

  // Generate input
  input := pb.AnalyzerInput{
    Id: makeUUID(),
    Timestamp: makeTimestamp(),
    Text: string(body)}

  // Contact the server and print out its response
  ctx, cancel := context.WithTimeout(context.Background(), time.Second)
  defer cancel()

  // Calculate output
  output, err := c.Analyze(ctx, &input)
  if err != nil {
    log.Fatalf("could not analyze: %v", err)
  }

  // Write result
  fmt.Fprintf(w, "%s", output)
}

func run(frontend_port string, word_count_analyzer_address string) {
  // Set up a connection to the server
  log.Printf("Connecting to %s", word_count_analyzer_address)
  conn, err := grpc.Dial(word_count_analyzer_address, grpc.WithInsecure())
  if err != nil {
    log.Fatalf("did not connect: %v", err)
  }
  defer conn.Close()

  // Create client
  c := pb.NewAnalyzerClient(conn)

  // Configure handlers
  http.HandleFunc("/word_count", func(w http.ResponseWriter, r *http.Request) {
    analyzeWordCount(c, w, r)
  })

  // Run server
  log.Printf("Server Frontend listening on localhost:%s", frontend_port)
  log.Fatal(http.ListenAndServe(":" + frontend_port, nil))
}

func main() {
  frontend_port := getEnvironmentVariable("FRONTEND_PORT")
  word_count_analyzer_address := getEnvironmentVariable("WORD_COUNT_ANALYZER_ADDRESS")
  run(frontend_port, word_count_analyzer_address)
}
