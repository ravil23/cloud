package main

import (
  "fmt"
  "log"
  "os"
  "time"
)

func getEnvironmentVariable(name string) string {
  value := os.Getenv(name)
  if (len(value) == 0) {
    log.Fatalf("Environment variable %s not found or empty.", name)
  }
  return value
}

func makeUUID() string {
  return fmt.Sprintf("uuid-%d", time.Now().UnixNano())
}

func makeTimestamp() int64 {
  return time.Now().UnixNano() / 1000000
}
