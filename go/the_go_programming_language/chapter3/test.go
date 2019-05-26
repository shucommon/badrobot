package main

import "fmt"

type Integer int

func (a Integer) Add(b Integer) {
    a += b
}

func (a *Integer) Add1(b Integer) {
    *a += b
}

type Rect struct {
    x, y float64
    width, height float64
}

func (r *Rect) Area() float64 {
    //r.width = 20
    return r.width * r.height
}
func (r Rect) Area1() float64 {
    r.width = 20
    return r.width * r.height
}

func main() {
    var a Integer = 1
    a.Add(2)
    fmt.Println("a = ", a)
    a.Add1(2)
    fmt.Println("a = ", a)

    /*  
    var b Rect
    b.width = 10
    b.height = 10
    */
    b := new(Rect)
    b1 := &Rect{}
    b2 := &Rect{0, 0, 100, 200}
    b3 := &Rect{width: 100, height: 200}

    fmt.Println("area1 = ", b.Area1())
    fmt.Println("area = ", b.Area())
}
