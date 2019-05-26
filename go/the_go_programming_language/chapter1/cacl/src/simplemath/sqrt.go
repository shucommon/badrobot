package simplemath

import "math"

func Sqrt(a int) int {
    i := math.Sqrt(float64(a))
    return int(i)
}
