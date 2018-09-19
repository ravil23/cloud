package main

import (
  "log"
  "os"
  "time"

  "github.com/google/uuid"
)

func getEnvironmentVariable(name string) string {
  value := os.Getenv(name)
  if (len(value) == 0) {
    log.Fatalf("Environment variable %s not found or empty.", name)
  }
  return value
}

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