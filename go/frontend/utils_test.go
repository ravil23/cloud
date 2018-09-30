package main

import "testing"

func TestGetEnvironmentVariable(t *testing.T) {
  path := getEnvironmentVariable("PATH")
  if len(path) == 0 {
    t.Fatalf("Environment variable PATH not found or empty")
  }
}

func TestMakeUUID(t *testing.T) {
  uuid := makeUUID()
  expected_length := 36

  if len(uuid) != expected_length {
    t.Fatalf("%d != %d", len(uuid), expected_length)
  }
}

func TestMakeTimestamp(t *testing.T) {
  timestamp := makeTimestamp()

  var min_timestamp int64 = 1514764800000
  if timestamp < min_timestamp {
    t.Fatalf("%d < %d (2018-01-01)", timestamp, min_timestamp)
  }

  var max_timestamp int64 = 4102444800000
  if timestamp > max_timestamp {
    t.Fatalf("%d > %d (2100-01-01)", timestamp, max_timestamp)
  }
}
