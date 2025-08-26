package main

import (
	"log"
	"os"
)

func deleteFile() {
	delErr := os.Remove("test.txt")

	if (!os.IsNotExist(delErr)) && delErr != nil {
		log.Fatal(delErr)
	}
}

func main() {
	deleteFile()
}
