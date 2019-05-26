package main

import "fmt"
import "log"

func test_ret() int {
    i := 1
    if i < 1 {
        fmt.Println("less than 1")
        return 0
    } else {
        //panic("test")
        panic(nil)
        fmt.Println("more than 1")
        return 1
    }
}

func example(x int) int {
    if x  == 0 {
        return 5
    } else {
        return x
    }
}

func main() {
    var array [32] byte

    for i, v := range array {
        fmt.Println("Array element [", i, "],", v)
    }

    myslice := make([]int, 5)
    fmt.Println(myslice)

    myslice1 := make([]int, 5, 10)
    fmt.Println(myslice1)

    defer func() {
        fmt.Println("defer called")
        if r := recover(); r != nil {
            log.Printf("Runtime error caught: %v", r)
        }
    } ()

    fmt.Println(test_ret())
    fmt.Println(example(1))
}
